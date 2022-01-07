unit Preproc;

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

{$IF DEFINED(UNIX) OR DEFINED(LINUX)}
{$linklib c}
{$linklib stdc++}
{$ENDIF}

{$CODEPAGE UTF8}

interface

uses
  Common, Classes, Lexique, Evaluat;

Const PassCount: Integer = 0;
Const PreprocPasses: Integer = 1;

procedure PreprocStage1(ApplyConds: Boolean;
                        Defines: TStringList;
                        ProgGPU: TStringList;
                        Var IsClustered, IsVectorized: Boolean;
                        Var Restrictions: TRestrictions);
procedure PreprocStage1a(Var Restrictions: TRestrictions);
procedure PreprocStage2(Var Restrictions: TRestrictions);

Type PatternModes = (pmNone, pmScan, pmParse);

Var PatternsMode: PatternModes = pmNone;
    PatternsOrder: TStringList = Nil;

implementation

uses SysUtils, dynlibs, Consts, regexpr, xpath, xmlread, dom, Math;

(* *)
Type run_gprolog7 = Function(Dir, ConsultScript, OutFName, MainGoal, gprolog_console_out, DoneGoal, GID: PChar):Integer; cdecl;
    switch_gprolog7 = Function(gprolog_console_out: PChar): Integer; cdecl;

Var Prologer: TLibHandle = 0;
    (* *)runer: run_gprolog7; (* *)
    (* *)initer: switch_gprolog7; (* *)

(* *)

Const gpuNone = 0;
      gpuOnly = 1;
      gpuBoth = 2;

Const BracketsOff = '$brackets_off$';
      PrefixOff   = '$prefix_off$';
      Pruning     = '$prune$';

Const Predicates: PChar =
'brackets_off:-write('''+BracketsOff+''').'+CRLF+
'prefix_off:-write('''+PrefixOff+''').'+CRLF+
'prune:-write('''+Pruning+''').'+CRLF+
'plan_parallel_chain(A,B):-write(''plan_parallel_chain(''),write(A),write('',''),write(B),write('');''),nl.'+CRLF+
'plan_parallel_reverse(A,B):-write(''plan_parallel_reverse(''),write(A),write('',''),write(B),write('');''),nl.'+CRLF;

Type TDefItem = Record
        Cond, Any: Boolean;
        IgnoreElse: Boolean;
        FirstLine: Integer
     End;

Type

{ TModule }

 TModule = Class
        Params: TStringList;
        Prefix: String;
        Body: String;

        Constructor Create(_Params: TStringList; Const Pref, _Body: String);
        Destructor  Destroy; Override;
     End;

 { TPattern }
 TPattern = Class
        ActionID: String;
        Fact: Boolean;
        Params: TObjStrList;
        Context1, Needle, Context2: String;

        Constructor Create(Line: Integer; Const ModID: String; IsFact: Boolean; ModParams: TObjStrList; Const Body: String);
        Function GetReplacement(ENV: TXPathEnvironment; Const S: RawByteString): WideString;
        Destructor Destroy; Override;
     End;

constructor TPattern.Create(Line: Integer; const ModID: String;
  IsFact: Boolean; ModParams: TObjStrList; const Body: String);

Var L: TStringList;
    F: Integer;
begin
   ActionID := ModID;
   Fact := IsFact;
   Params := ModParams;

   L := TStringList.Create;
   L.Text := Body;

   Context1 := '';
   Needle := '';
   Context2 := '';

   F := 0;
   While (F < L.Count) And (UpperCase(Trim(L[F])) <> SpecSymbol + idbegin) Do
     begin
       If Trim(L[F]) <> '' Then
          AppendStr(Context1, Trim(L[F]));
       Inc(F)
     end;
   If F < L.Count Then
      begin
        Inc(F);
        While (F < L.Count) And (UpperCase(Trim(L[F])) <> SpecSymbol + idend) Do
          begin
            If Trim(L[F]) <> '' Then
               AppendStr(Needle, Trim(L[F]));
            Inc(F)
          end;
        If Needle = '' Then
           begin
             WriteLn('Needle part between '+SpecSymbol+idbegin, ' and '+SpecSymbol+idend, ' can''t be empty', TLine(Lines.Objects[Line]).GetDescription);
             Halt(-52)
           end;
        If F = L.Count Then
           begin
             WriteLn(idend, ' expected in pattern definition ', TLine(Lines.Objects[Line]).GetDescription);
             Halt(-51)
           end;
        Inc(F);
        While F < L.Count Do
          begin
            If Trim(L[F]) <> '' Then
               AppendStr(Context2, Trim(L[F]));
            Inc(F)
          end;
      end;
   L.Free
end;

function TPattern.GetReplacement(ENV: TXPathEnvironment; const S: RawByteString): WideString;

Var src: TXMLInputSource;
    parser: TDOMParser;
    dom: TXMLDocument;
    res: TXPathVariable;

function GetList(Const First, Last: String; _Params: TObjStrList): String;

Var K, M: Integer;
Begin
   Result := First;

   For K := 0 To _Params.Count-1 Do
     If Assigned(_Params.Objects[K]) Then
       Result := Result + GetList('[',']', TObjStrList(_Params.Objects[K])) + ','
     Else
       Begin
         res := EvaluateXPathExpression(_Params[K], dom.DocumentElement, Nil, [], Nil, Nil, ENV);
         ENV.commitUndo(0);
         If res is TXPathNodeSetVariable Then
            If res.AsNodeSet.Count = 0 Then
               Result := Result + ''''','
            Else
              Begin
                If res.AsNodeSet.Count > 1 Then Result := Result + '[';
                For M := 0 To res.AsNodeSet.Count-1 Do
                    Result := Result + '''' + TDOMNode(res.AsNodeSet[M]).TextContent + ''',';
                If res.AsNodeSet.Count > 0 Then
                   System.Delete(Result, Length(Result), 1);
                If res.AsNodeSet.Count > 1 Then Result := Result + ']';
                Result := Result + ','
              End
         Else
            Result := Result + '''' + res.AsText + ''',';
         res.Free
       End;
   If _Params.Count > 0 Then
      System.Delete(Result, Length(Result), 1);
   Result := Result + Last
End;

begin
  Result := UnescapeString(ActionID);

  src := TXMLInputSource.Create(S);
  parser := TDOMParser.Create;
  parser.Parse(src, dom);

  Try
     If (Params.Count > 0) Or Not Fact Then
        Result := Result + GetList('(', ')', Params)
     Else
        Result := Result + GetList('', '', Params)
  finally
     dom.Free;
     parser.Free;
     src.Free
  end
end;

destructor TPattern.Destroy;
begin
   Params.Free;
   Inherited Destroy
end;

 { TModule }

 Constructor TModule.Create(_Params: TStringList; const Pref, _Body: String);
 Begin
    Inherited Create;
    Params := _Params;
    Prefix := Pref;
    Body   := _Body
 End;

 Destructor TModule.Destroy;
 begin
    Params.Free;
    Inherited Destroy
 end;

Function HandleDefined(Const S: String): String;

Var F: Integer;
Begin
  Result := StringReplace(S, ' ', '', [rfReplaceAll]);
  Result := StringReplace(Result,'defined(1)','1',[rfReplaceAll]);
  // Other defined(id) = 0
  Repeat
     F := Pos('defined(',Result);
     If F > 0 Then
        Begin
          Inc(F, 8);
          While (F < Length(Result)) And (Result[F] in IdentSet) Do
            Delete(Result, F, 1);
          Delete(Result, F-8, 9);
          Insert('0', Result, F-8)
        End
  Until F = 0
End;

procedure PreprocStage1(ApplyConds: Boolean;
                        Defines: TStringList;
                        ProgGPU: TStringList;
                        Var IsClustered, IsVectorized: Boolean;
                        Var Restrictions: TRestrictions);

Var L: TAnalyser; Eval: TEvaluator;
    S, S1, S2: String;
    ID: String;
    DefStack: Array Of TDefItem;
    ModeGPU: Byte;
    FL: TStringList;
    LN: TLine;
    Rslt: Real;
    UseLine: Boolean;
    Original: String;
    Flag: Boolean;
    F, K: Integer;
begin
  L:=TAnalyser.Create(IdentSet,[Space,Tabulation]);

  SetLength(Restrictions, 0);

  IsClustered := False;
  IsVectorized := False;

  SetLength(DefStack, 0);

  ModeGPU := gpuNone;

  LCounter:=1;
  // First preprocessing stage
  // Handle simple defines: substitute into defines and consts
  While (LCounter <= Lines.Count) And Not L.Error Do
    Begin
      S := Lines.Strings[LCounter-1];
      L.AnlzLine := S;

      // Check gpu/common directives
      If L.IsNext(Pound) Then // #...
         Begin
           L.Check(Pound);
           S1 := L.GetIdent(True);
           If S1 = idpragma Then
              Begin
                If L.FindIdent(True) = idplan Then
                   Begin
                     L.GetIdent(True);
                     S1 := L.FindIdent(True);
                     If (S1 = idgpu) Or (S1 = idcommon) Then
                        Begin
                          L.GetIdent(True);
                          If (ModeGPU = gpuBoth) And (S1 = idgpu) Or
                             (ModeGPU = gpuOnly) And (S1 = idcommon) Then
                             Begin
                               WriteLn('Unexpected mode: previous gpu/common section is not closed',TLine(Lines.Objects[LCounter-1]).GetDescription);
                               Halt(-1)
                             End;
                          S2 := L.GetIdent(True);
                          If (S2 = idbegin) And (ModeGPU <> gpuNone) Then
                             Begin
                               WriteLn('Unexpected begin: gpu/common section is already open',TLine(Lines.Objects[LCounter-1]).GetDescription);
                               Halt(-1)
                             End;
                          If ModeGPU = gpuNone Then
                             If S2 = idbegin Then
                                If S1 = idgpu Then
                                   ModeGPU := gpuOnly
                                Else
                                   ModeGPU := gpuBoth
                             Else If S2 = idend Then
                                Begin
                                  WriteLn('Unexpected end: there is no opened gpu/common section',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                  Halt(-1)
                                End
                             Else
                                Begin
                                  WriteLn('begin expected',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                  Halt(-1)
                                End
                          Else If S2 = idend Then
                             ModeGPU := gpuNone
                          Else
                             Begin
                               WriteLn('end expected',TLine(Lines.Objects[LCounter-1]).GetDescription);
                               Halt(-1)
                             End;
                          TLine(Lines.Objects[LCounter-1]).Free;
                          Lines.Delete(LCounter-1);
                          Continue // return to big preprocessing loop header
                        End
                   End
              End
         End;

      S := Lines.Strings[LCounter-1];
      L.AnlzLine := S;

      // Check is this line common or gpu line
      If ModeGPU <> gpuNone Then
         ProgGPU.Add(S);
      If ModeGPU = gpuOnly Then
         Begin
           TLine(Lines.Objects[LCounter-1]).Free;
           Lines.Delete(LCounter-1);
           Continue // return to big preprocessing loop header
         End;

      // Check if #defs allows compilation: -> Flag
      Flag := True;
      For F := 0 To High(DefStack) Do
          If Not DefStack[F].Cond Then
             Begin
               Flag := False;
               Break
             End;

      UseLine := Flag;

      If Flag Then
         Begin
           If L.IsNext(Pound) Then // #...
              Begin
                L.Check(Pound);
                S1 := L.GetIdent(True);
                If S1 = idpragma Then
                   Begin
                     If L.FindIdent(True) = idplan Then
                        Begin
                          L.GetIdent(True);
                          S2 := L.FindIdent(True);
                          If S2 = idclustered Then
                             Begin
                               IsClustered := True;
                               WriteLn('Warning: clustering mode is on',TLine(Lines.Objects[LCounter-1]).GetDescription);
                               TLine(Lines.Objects[LCounter-1]).Free;
                               Lines.Delete(LCounter-1);
                               Continue // return to big preprocessing loop header
                             End
                          Else If (S2 = idvectorized) Or (S2 = idtypized) Then
                             Begin
                               IsVectorized := True;
                               WriteLn('Warning: vectorizing mode is on',TLine(Lines.Objects[LCounter-1]).GetDescription);
                               TLine(Lines.Objects[LCounter-1]).Free;
                               Lines.Delete(LCounter-1);
                               Continue // return to big preprocessing loop header
                             End
                        End
                   End
                Else If S1 = idUndef Then
                   Begin
                     ID := L.GetIdent(False);
                     F := _IndexOf(Defines, ID);
                     If F >= 0 Then
                        Begin
                          DisposeStr(PString(Defines.Objects[F]));
                          Defines.Delete(F)
                        End;
                     Inc(LCounter);
                     Continue
                   End
              End
         End;

      Original := S;
      For F := 0 To Defines.Count-1 Do
          S := Substitute(S, '', '', Defines.Strings[F], PString(Defines.Objects[F])^);
      Lines.Strings[LCounter-1] := S;
      L.AnlzLine := S;

      If L.IsNext(Pound) Then // #...
         Begin
           L.Check(Pound);
           S := L.GetIdent(True);
           If Flag And (S = idDefine) Then
              Begin
                ID := L.GetIdent(False);
                S1 := '';
                S := Trim(L.AnlzLine);
                Repeat
                  Flag := (Length(S) > 0) And (S[Length(S)] = BackSlash);
                  If Flag Then
                     Begin
                       SetLength(S, Length(S)-1);
                       S := TrimRight(S)
                     End;
                  S1 := S1 + S;
                  If Flag Then
                     Begin
                       Inc(LCounter);
                       S := Lines.Strings[LCounter-1];
                       S := ' '+Trim(S)
                     End
                Until Not Flag;
                ID := Trim(ID);
                If Length(ID) = 0 Then
                   WriteLn('Warning: #define is not recognized (may be duplicate). Compilation may be incorrect',TLine(Lines.Objects[LCounter-1]).GetDescription)
                Else
                   Begin
                      // Substitutions
                      F := _IndexOf(Defines, ID);
                      If F >= 0 Then
                         WriteLn('Panic: #define ', ID, ' encountered more than once. Compilation may be incorrect',TLine(Lines.Objects[LCounter-1]).GetDescription)
                      Else
                         Begin
                           S1 := Trim(S1);
                           For F := 0 To Defines.Count-1 Do
                               S1 := Substitute(S1, '', '', Defines.Strings[F], PString(Defines.Objects[F])^);
                           If Length(S1) = 0 Then
                              S1 := '1';
                           Defines.AddObject(ID, TObject(NewStr(S1)))
                         End
                   End
              End
           Else If Flag And (S = idPreprocPasses) Then
              Begin
                If L.Check(LeftBracket) And L.GetCheckedNumber(True, Rslt, 1.0, 100.0) And L.Check(RightBracket) Then
                   PreprocPasses := Round(Rslt);

                If Assigned(Lines.Objects[LCounter-1]) Then
                   Lines.Objects[LCounter-1].Free;
                Lines.Delete(LCounter-1);
                Continue
              End
           Else If Flag And (S = idInclude) Then
              Begin
                If L.IsNext(DblQuote) Then
                   Begin
                     L.Check(DblQuote);
                     S := Trim(L.GetBefore(True,[DblQuote]));
                     L.Check(DblQuote);

                     K := _IndexOf(Files, Asterisk+S);
                     If K >= 0 Then
                        Begin
                          WriteLn('Warning: preliminary preprocessing encounters more than one #include "'+S+'"',TLine(Lines.Objects[LCounter-1]).GetDescription);
                          Lines.Delete(LCounter-1)
                        End
                     Else
                        Begin
                          FL := TStringList.Create;
                          Try
                             FL.LoadFromFile(S);
                          Except
                             WriteLn('Error: can''t open file "'+S+'"',TLine(Lines.Objects[LCounter-1]).GetDescription);
                             Halt(-1);
                          End;
                          K := Files.AddObject(Asterisk+S, FL);
                          LN := TLine(Lines.Objects[LCounter-1]);
                          Lines.Delete(LCounter-1);
                          For F := 0 To FL.Count-1 Do
                              Lines.InsertObject(LCounter-1+F,FL.Strings[F], TLine.Derive(LN,K,F+1));
                          LN.Free
                        End;
                     Continue // return to loop header without end LCounter incrementing
                   End
                Else
                   WriteLn('Warning: #include'+L.AnlzLine+' is bypassed at the preliminary incremental preprocessing',TLine(Lines.Objects[LCounter-1]).GetDescription)
              End
           Else If (S = idIfdef) Or (S = idIfndef) Then
              Begin
                SetLength(DefStack, Length(DefStack)+1);
                L.AnlzLine := Original;
                L.Check(Pound);
                L.CheckIdent(S, True);
                S1 := Trim(L.AnlzLine);
                If Length(S1) = 0 Then
                  DefStack[High(DefStack)].Cond := S = idIfndef
                Else
                  Begin
                    ID := L.FindIdent(False);
                    If Length(ID) = 0 Then
                       DefStack[High(DefStack)].Cond := False
                    Else
                       DefStack[High(DefStack)].Cond := _IndexOf(Defines, ID) >= 0;
                    DefStack[High(DefStack)].Cond := DefStack[High(DefStack)].Cond Xor (S = idIfndef)
                  End;
                DefStack[High(DefStack)].Any := False;
                DefStack[High(DefStack)].IgnoreElse := False;
                DefStack[High(DefStack)].FirstLine := LCounter+1;
                UseLine := False
              End
           Else If S = idIf Then
              Begin
                L.AnlzLine := Original;
                L.Check(Pound);
                L.CheckIdent(S, True);
                S1 := Trim(L.AnlzLine);
                For F := 0 To Defines.Count-1 Do
                    S1 := Substitute(S1, '', '', 'defined('+Defines.Strings[F]+')', '1');
                For F := 0 To Defines.Count-1 Do
                    S1 := Substitute(S1, '', '', Defines.Strings[F], PString(Defines.Objects[F])^);
                S1 := HandleDefined(S1);
                Eval := TEvaluator.Create(IdentSet,[Space, Tabulation]);
                Eval.AnlzLine := S1;
                SetLength(DefStack, Length(DefStack)+1);
                Rslt := 0.0;
                If Eval.EvalExpression([],Rslt) Then
                   Begin
                     DefStack[High(DefStack)].Cond := Abs(Rslt)>1E-8;
                     DefStack[High(DefStack)].Any := False;
                   End
                Else
                   Begin
                     DefStack[High(DefStack)].Cond := True;
                     DefStack[High(DefStack)].Any := True;
                   End;
                DefStack[High(DefStack)].IgnoreElse := False;
                DefStack[High(DefStack)].FirstLine := LCounter+1;
                If Eval.Error Then
                   WriteLn('Evaluator error',TLine(Lines.Objects[LCounter-1]).GetDescription);
                Eval.Free;
                UseLine := DefStack[High(DefStack)].Any
              End
           Else If S = idElse Then
              Begin
                If Length(DefStack) = 0 Then
                   Begin
                     WriteLn('#else without #if',TLine(Lines.Objects[LCounter-1]).GetDescription);
                     Halt(-1)
                   End;
                If Not (DefStack[High(DefStack)].Any Or DefStack[High(DefStack)].IgnoreElse) Then
                   Begin
                     If Not DefStack[High(DefStack)].Cond Then
                        Begin
                          SetLength(Restrictions, Length(Restrictions)+1);
                          Restrictions[High(Restrictions)].First := DefStack[High(DefStack)].FirstLine;
                          Restrictions[High(Restrictions)].Last := LCounter-1
                        End;
                     DefStack[High(DefStack)].Cond := Not DefStack[High(DefStack)].Cond;
                     DefStack[High(DefStack)].IgnoreElse := False;
                     DefStack[High(DefStack)].FirstLine := LCounter+1
                   End;
                UseLine := DefStack[High(DefStack)].Any
              End
           Else If S = idElif Then
              Begin
                If Length(DefStack) = 0 Then
                   Begin
                     WriteLn('#else without #if',TLine(Lines.Objects[LCounter-1]).GetDescription);
                     Halt(-1)
                   End;
                If Not (DefStack[High(DefStack)].Any Or DefStack[High(DefStack)].IgnoreElse) Then
                   Begin
                     If Not DefStack[High(DefStack)].Cond Then
                        Begin
                          L.AnlzLine := Original;
                          L.Check(Pound);
                          L.CheckIdent(S, True);
                          S1 := Trim(L.AnlzLine);
                          For F := 0 To Defines.Count-1 Do
                              S1 := Substitute(S1, '', '', 'defined('+Defines.Strings[F]+')', '1');
                          For F := 0 To Defines.Count-1 Do
                              S1 := Substitute(S1, '', '', Defines.Strings[F], PString(Defines.Objects[F])^);
                          S1 := HandleDefined(S1);
                          Eval := TEvaluator.Create(IdentSet,[Space, Tabulation]);
                          Eval.AnlzLine := S1;
                          If Eval.EvalExpression([],Rslt) Then
                             Begin
                               DefStack[High(DefStack)].Cond := Abs(Rslt)>1E-8;
                               DefStack[High(DefStack)].Any := False;
                             End
                          Else
                             Begin
                               DefStack[High(DefStack)].Cond := True;
                               DefStack[High(DefStack)].Any := True;
                             End;
                          If DefStack[High(DefStack)].Cond Then
                             Begin
                               SetLength(Restrictions, Length(Restrictions)+1);
                               Restrictions[High(Restrictions)].First := DefStack[High(DefStack)].FirstLine;
                               Restrictions[High(Restrictions)].Last := LCounter-1;
                               DefStack[High(DefStack)].FirstLine := LCounter+1;
                             End;
                          DefStack[High(DefStack)].IgnoreElse := False;
                          If Eval.Error Then
                             WriteLn('Evaluator error',TLine(Lines.Objects[LCounter-1]).GetDescription);
                          Eval.Free
                        End
                     Else
                        Begin
                           DefStack[High(DefStack)].Cond := False;
                           DefStack[High(DefStack)].IgnoreElse := True;
                           DefStack[High(DefStack)].FirstLine := LCounter+1
                        End
                   End;
                UseLine := DefStack[High(DefStack)].Any
              End
           Else If S = idEndif Then
              Begin
                If Length(DefStack) = 0 Then
                   Begin
                     WriteLn('#endif without #if',TLine(Lines.Objects[LCounter-1]).GetDescription);
                     Halt(-1)
                   End;
                If Not (DefStack[High(DefStack)].Cond Or DefStack[High(DefStack)].Any)Then
                   Begin
                     SetLength(Restrictions, Length(Restrictions)+1);
                     Restrictions[High(Restrictions)].First := DefStack[High(DefStack)].FirstLine;
                     Restrictions[High(Restrictions)].Last := LCounter-1
                   End;
                UseLine := DefStack[High(DefStack)].Any;
                SetLength(DefStack, Length(DefStack)-1)
              End
         End;
      If ApplyConds And Not UseLine Then
         Begin
            If Assigned(Lines.Objects[LCounter-1]) Then
               Lines.Objects[LCounter-1].Free;
            Lines.Delete(LCounter-1)
         End
      Else
         Inc(LCounter)
    End;

  If Length(DefStack) > 0 Then
     Begin
       WriteLn('#endif expected in line ',LCounter);
       Halt(-1)
     End;

  If ModeGPU <> gpuNone Then
     Begin
       WriteLn('Unclosed gpu/common section in line ',LCounter);
       Halt(-1)
     End;

  SetLength(DefStack, 0);

  L.Free
end;

procedure MakeConsultation(Const FL, GOAL: String);

Var S: String;
    I: Integer;
Begin
  S:=StringReplace(ExcludeTrailingBackSlash(ExtractFilePath(ParamStr(0))),'\','/',[rfReplaceAll]);
  (* *)
  If Prologer = 0 Then
     Begin
       Prologer := LoadLibrary({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'./lib' + {$ENDIF}'PrologIntrf.' + SharedSuffix);
       If Prologer = NilHandle Then
          Prologer := DWORD(-1)
       Else
          Begin
            initer := switch_gprolog7(GetProcedureAddress(Prologer, 'init_gprolog7'));
            if Assigned(initer) Then
               initer('_.info')
            Else
               Begin
                 FreeLibrary(Prologer);
                 Prologer := DWORD(-1)
               End
          End
     End;
  If Prologer <> DWORD(-1) Then
     runer := run_gprolog7(GetProcedureAddress(Prologer, 'run_gprolog7'))
  Else
     runer := Nil;
  If Assigned(runer) Then
     begin
       I := runer(PChar(S), PChar(FL), '_.out', PChar(GOAL), '_.info', 'true', PChar(''''''(*GID*)));
       If I <> 5 Then
          begin
            WriteLn('Error executing gprolog library : "' + BinStr(I,16) + '"');
            Halt(-50)
          end
     end
  Else
  (* *)
     WriteLn(RunExtCommand(
        {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_gprolog.sh'{$ELSE}'run_gprolog.bat'{$ENDIF},
        S+' '+FL+' _.out '+GOAL+' _.info',
        '_.info'));
End;

procedure PreprocStage1a(Var Restrictions: TRestrictions);

Type SmallINtArray = Array Of SmallInt;

function CountBrackets(Const S: String): Integer;

Var F: Integer;
begin
   Result := 0;

   F := 1;
   While F <= Length(S) Do
     Begin
       If S[F] = LeftBracket Then
          Inc(Result)
       Else If S[F] = '\' Then
          Inc(F)
       Else If S[F] = LeftSqrBracket Then
          While (F <= Length(S)) And (S[F] <> RightSqrBracket) Do
            Begin
              If S[F] = '\' Then
                 Inc(F);
              Inc(F)
            End;
       Inc(F)
     end
end;

function MakeReplacements(Var Map: SmallIntArray;
                        Begs, Ends: TList;
                        Replacers: TStringList; HayStack: WideString): WideString;

Var Start, Stop: Integer;
    Replacement: WideString;
    LL: TStringList;
    LN: TLine;
    F, G, K, M: Integer;
Begin
  Result := '';

  F := 1;
  While F < Length(Map) Do
    Begin
      While (F < Length(Map)) And (Map[F] < 0) Do
        Inc(F);
      If F = Length(Map) Then Break;

      Start := F;
      Stop := F+1;
      While (Stop < Length(Map)) And (Map[Stop] = Map[Start]) Do
        Inc(Stop);
      Dec(Stop);
      Replacement := Replacers[Map[Start]];
      If Replacers.Objects[Map[Start]] <> Nil Then
         Result := Result + 'assertz(' + Replacement + '),';

      If Start > Length(HayStack) Then
         Begin
           K := Files.AddObject(Underscore+'END', Nil);
           Lines.AddObject(Replacement, TLine.Create(K, 10000));
           Break
         End;

      If Replacers.Objects[Map[Start]] <> Nil Then
         Begin
           F := Stop + 1;
           Continue
         End;

      K := 0;
      While K < Begs.Count Do
        Begin
          If TObjectToInteger(TObject(Begs[K])) <= TObjectToInteger(TObject(Ends[K])) Then
             If (TObjectToInteger(TObject(Begs[K])) <= Start) And (TObjectToInteger(TObject(Ends[K])) >= Start) Then
                Break;
          Inc(K)
        End;
      If K <> Begs.Count Then
         Begin
           LL := TStringList.Create;
           LL.Text := Replacement;
           G := Files.AddObject(Underscore+'PATTERN['+IntToStr(Map[Start])+']',LL);

           If TObjectToInteger(TObject(Ends[K])) > Stop Then
              Begin
                Lines.InsertObject(K+1, UnescapeString(Copy(HayStack, Stop+1, TObjectToInteger(TObject(Ends[K]))-Stop)), TLine.Create(G, 1));
                Begs.Insert(K+1, IntegerToTObject(Stop+1));
                Ends.Insert(K+1, Ends[K])
              End;

           Ends[K] := IntegerToTObject(Start - 1);
           If Ends[K] < Begs[K] Then
              Begin
                Ends.Delete(K);
                Begs.Delete(K);
                LN := TLine(Lines.Objects[K]);
                Lines.Delete(K);
                LN.Free
              End
           Else
              Begin
                Lines[K] := UnescapeString(Copy(HayStack, TObjectToInteger(TObject(Begs[K])), Start-TObjectToInteger(TObject(Begs[K]))));
                LN := TLine(Lines.Objects[K]);
                Lines.Objects[K] := TLine.Derive(LN, G, 1);
                LN.Free;
                Inc(K)
              End;
           // K = position of insertion of replacement
           While (K < Begs.Count) And (TObjectToInteger(TObject(Ends[K])) <= Stop) Do
             Begin
               Ends.Delete(K);
               Begs.Delete(K);
               LN := TLine(Lines.Objects[K]);
               Lines.Delete(K);
               LN.Free
             End;
           If K < Begs.Count Then
              Begin
                Lines[K] := UnescapeString(Copy(HayStack, Stop+1, TObjectToInteger(TObject(Ends[K]))-Stop));
                LN := TLine(Lines.Objects[K]);
                Lines.Objects[K] := TLine.Derive(LN, G, 1000);
                LN.Free;
                Begs[K] := IntegerToTObject(Start + Length(Replacement));
                Ends[K] := IntegerToTObject(TObjectToInteger(TObject(Begs[K])) + (TObjectToInteger(TObject(Ends[K]))-Stop) - 1);
                For M := K+1 To Begs.Count-1 Do
                    Begin
                       Begs[M] := IntegerToTObject(TObjectToInteger(TObject(Begs[M])) - (Stop - Start + 1) + Length(Replacement));
                       Ends[M] := IntegerToTObject(TObjectToInteger(TObject(Ends[M])) - (Stop - Start + 1) + Length(Replacement))
                    End
              End;
           If Length(Replacement) > 0 Then
              Begin
                Lines.InsertObject(K, Replacement, TLine.Create(G, 1));
                Begs.Insert(K, IntegerToTObject(Start));
                Ends.Insert(K, IntegerToTObject(Start + Length(Replacement) - 1))
              End;

           System.Delete(HayStack, Start, Stop-Start+1);
           Move(Map[Stop+1], Map[Start], (Length(Map)-(Stop+1))*SizeOf(Map[0]));
           System.Insert(Replacement, HayStack, Start);
           SetLength(Map, Length(Map) - (Stop-Start+1) + Length(Replacement));
           Move(Map[Start], Map[Start+Length(Replacement)], (Length(Map)-(Start+Length(Replacement)))*SizeOf(Map[0]));
           F := Start + Length(Replacement)
         End
    End
end;

procedure GetScheme(M: PatternModes; L: TAnalyser; Const AddMode: Boolean = False);
Begin
  L.GetIdent(True);
  L.Check(LeftBracket);
  If Not AddMode Then PatternsOrder.Clear;
  PatternsMode := M;
  While Not (L.Error Or L.IsNext(RightBracket)) Do
    Begin
      PatternsOrder.Add(L.GetIdent(False));
      If L.IsNext(Comma) Then
         L.Check(Comma)
      Else If Not L.IsNext(RightBracket) Then
         L.Expect(RightBracket);
    End;
  L.Check(RightBracket);
  TLine(Lines.Objects[LCounter-1]).Restricted := True
End;

function ParseComplexParam(Const S: String): TObjStrList;

Var L: TAnalyser;
    S1: String;
    Flag: Boolean;
Begin
  L:=TAnalyser.Create(IdentSet,[Space,Tabulation], True);

  L.AnlzLine := S;
  If L.IsNext(LeftSqrBracket) Then
     Begin
       L.Check(LeftSqrBracket);
       Result := TObjStrList.Create;
       Flag := False;
       While Not (Flag Or L.Error Or L.Empty) Do
         Begin
           S1 := L.GetBalancedListItem(False, [Comma, RightSqrBracket]);
           If Length(S1) = 0 Then
              Begin
                WriteLn('Incorrect parameters list',TLine(Lines.Objects[LCounter-1]).GetDescription);
                Halt(-1)
              End;
           Result.AddObject(S1, ParseComplexParam(S1));
           If L.IsNext(Comma) Then
              L.Check(Comma)
           Else If L.IsNext(RightSqrBracket) Then
              Flag := L.Check(RightSqrBracket)
         End;
       If L.Error Then
          Begin
            WriteLn('Incorrect parameters list',TLine(Lines.Objects[LCounter-1]).GetDescription);
            Halt(-1)
          End
     End
  Else
     Result := Nil;

  L.Free
End;

Var L: TAnalyser;
    S, S1: String;
    ID, ModID: String;
    ModParams: TObjStrList;
    Patterns: TStringList;
    Pattern: TPattern;
    HayStack, P: WideString;
    Replacement: WideString;
    Context1Num, NeedleNum, Context2Num: Integer;
    ByPass: Boolean;
    Begs, Ends: TList;
    Start, Stop: Integer;
    R: TRegExpr;
    ENV: TXPathEnvironment;
    Facts: WideString;
    Map: SmallIntArray;
    RS: Array Of TRegExpr;
    Replacers: TStringList;
    db: TFastDB;
    GID: Integer;
    LN: TLine;
    F, G, K, M, PP: Integer;
    LL: TStringList;
    IsFact: Boolean;
    Flag: Boolean;
begin
  L:=TAnalyser.Create(IdentSet,[Space,Tabulation], True);

  Patterns := TStringList.Create;

  LCounter:=1;
  // PreSecond preprocessing phase
  // Handle patterns
  While (LCounter <= Lines.Count) And Not L.Error Do
    Begin
      S := Lines.Strings[LCounter-1];
      L.AnlzLine := S;

      ByPass := False;
      For F := 0 To High(Restrictions) Do
          If (LCounter >= Restrictions[F].First) And (LCounter <= Restrictions[F].Last) Then
             Begin
               ByPass := True;
               Break
             End;

      If L.IsNext(Pound) Then
         Begin
           L.Check(Pound);
           If (L.FindIdent(True) = idparse) And Not ByPass Then
              GetScheme(pmParse, L)
           Else If (L.FindIdent(True) = idscan) And Not ByPass Then
              GetScheme(pmScan, L)
           Else If (L.FindIdent(True) = idadd_parse) And Not ByPass Then
              GetScheme(pmParse, L, True)
           Else If (L.FindIdent(True) = idadd_scan) And Not ByPass Then
              GetScheme(pmScan, L, True)
           Else If (L.FindIdent(True) = iddef_pattern) And Not ByPass Then
              Begin
                G := LCounter;

                L.GetIdent(True);
                ID := L.GetIdent(False);
                L.Check(Equal);
                L.Check(Greater);
                If L.IsNext(LeftSqrBracket) Then
                   begin
                     L.Check(LeftSqrBracket);
                     IsFact := True;
                     ModID := L.GetIdent(False);
                     L.Check(RightSqrBracket)
                   end
                Else
                   begin
                     IsFact := False;
                     ModID := L.GetIdent(False);
                   end;
                L.Check(LeftBracket);

                F := _IndexOf(Patterns, ID);
                If F >= 0 Then
                   Begin
                     WriteLn('"'+ID+'" pattern: redefinition',TLine(Lines.Objects[LCounter-1]).GetDescription);
                     Halt(-1)
                   End;

                ModParams := TObjStrList.Create;
                Flag := L.IsNext(RightBracket);
                LineDelimiter := CRLF;
                If Flag Then
                   L.Check(RightBracket)
                Else
                  While Not (Flag Or L.Error Or L.Empty) Do
                    Begin
                      S1 := L.GetBalancedListItem(False, [Comma, RightBracket], @GetLineFromLines);
                      If Length(S1) = 0 Then
                         Begin
                           WriteLn('Incorrect parameters list',TLine(Lines.Objects[LCounter-1]).GetDescription);
                           Halt(-1)
                         End;
                      ModParams.AddObject(S1, ParseComplexParam(S1));
                      If L.IsNext(Comma) Then
                         L.Check(Comma)
                      Else If L.IsNext(RightBracket) Then
                         Flag := L.Check(RightBracket)
                    End;
                S1 := Trim(L.GetBalancedListItem(True, [SemiColon], @GetLineFromLines));
                LineDelimiter := '';
                If Length(S1) > 1 Then
                   If S1[1] = LeftFBracket Then
                      Begin
                        System.Delete(S1,1,1);
                        If (Length(S1) > 0) And (S1[Length(S1)] = RightFBracket) Then
                           SetLength(S1,Length(S1)-1)
                        Else
                           Begin
                             WriteLn('Probably closing bracket "}" absent in pattern "',ID,'"',TLine(Lines.Objects[LCounter-1]).GetDescription);
                             Halt(-1)
                           End
                      End;
                Pattern := TPattern.Create(G-1, ModID, IsFact, ModParams, Trim(S1));
                For F := G To LCounter Do
                    TLine(Lines.Objects[F-1]).Restricted := True;
                Patterns.AddObject(ID, Pattern);
                ModParams := Nil
              End
           Else If (L.FindIdent(True) = iddef_module) And Not ByPass Then
              Begin
                G := LCounter;
                L.GetBalancedListItem(True, [SemiColon], @GetLineFromLines);
                For F := G To LCounter Do
                    TLine(Lines.Objects[F-1]).Restricted := True
              End
         End;

      If L.Error Then
         Begin
           WriteLn('Patterns preprocessing: errors encountered', TLine(Lines.Objects[LCounter-1]).GetDescription);
           Halt(-1)
         End;

      Inc(LCounter)
    End;

  If PatternsMode <> pmNone Then
     Begin
        M := 0;
        For F := 0 To PatternsOrder.Count-1 Do
          Begin
            G := Patterns.IndexOf(PatternsOrder[F]);
            If G >= 0 Then
               Begin
                 S := Patterns[M];
                 Pattern := TPattern(Patterns.Objects[M]);
                 Patterns[M] := Patterns[G];
                 Patterns[G] := S;
                 Patterns.Objects[M] := Patterns.Objects[G];
                 Patterns.Objects[G] := Pattern;
                 Inc(M)
               End
          End;
        While M < Patterns.Count Do
          Begin
            Patterns.Objects[M].Free;
            Patterns.Delete(M)
          End;

        Begs := TList.Create;
        Ends := TList.Create;

        HayStack := '';

        LCounter:=1;
        G := 1;
        While LCounter <= Lines.Count Do
          Begin
            S := Lines.Strings[LCounter-1];

            If TLine(Lines.Objects[LCounter-1]).Restricted Then
               Begin
                 Begs.Add(IntegerToTObject(G));
                 Ends.Add(IntegerToTObject(G-1))
               End
            Else
              Begin
                ByPass := False;
                For F := 0 To High(Restrictions) Do
                    If (LCounter >= Restrictions[F].First) And (LCounter <= Restrictions[F].Last) Then
                       Begin
                         ByPass := True;
                         Break
                       End;
                If ByPass Then
                   Begin
                     Begs.Add(IntegerToTObject(G));
                     Ends.Add(IntegerToTObject(G-1))
                   End
                Else
                   Begin
                     S := EscapeString(S) + '\n';
                     HayStack := HayStack + S;
                     Begs.Add(IntegerToTObject(G));
                     Inc(G, Length(S));
                     Ends.Add(IntegerToTObject(G-1))
                   End
              End;

            Inc(LCounter)
          End;

        ENV := TXPathEnvironment.Create;
        GID := 1;
        ENV.setGID(GID);

        db := TFastDB.Create;
        db.Use;

        SetLength(Map, Length(HayStack)+1);
        For F := 0 To Length(HayStack) Do
          Map[F] := -1;
        Replacers := TStringList.Create;

        If PatternsMode = pmParse Then
           Begin
             SetLength(RS, Patterns.Count);
             For F := 0 To Patterns.Count-1 Do
                 Begin
                   With TPattern(Patterns.Objects[F]) Do
                     P := '(' + Context1 + ')(' + Needle + ')(' + Context2 + ')';
                   RS[F] := TRegExpr.Create(P);
                   RS[F].Compile;
                   RS[F].SetENV(ENV);
                   RS[F].SetDB(db);
                   RS[F].InputString := HayStack
                 End;

             G := 1;
             PP := 0;
             M := 1;
             While G <= Length(HayStack) Do
               Begin
                 F := 0;
                 While F < Patterns.Count Do
                   Begin
                     Context1Num := 1;
                     NeedleNum := Context1Num + 1 + CountBrackets(TPattern(Patterns.Objects[F]).Context1);
                     Context2Num := NeedleNum + 1 + CountBrackets(TPattern(Patterns.Objects[F]).Needle);

                     K := G;
                     Repeat
                       Flag := RS[F].ExecPos(K);
                       If Not Flag Then Break;
                       If (RS[F].MatchPos[NeedleNum] >= M) Then Break;
                       Inc(K)
                     Until False;
                     If Flag And
                        (RS[F].MatchPos[NeedleNum] > PP) And
                        (Trim(UnescapeString(Copy(HayStack, M, RS[F].MatchPos[NeedleNum] - M))) = '')
                        Then
                        Break;
                     Inc(F)
                   End;
                 If F = Patterns.Count Then
                    If Trim(UnescapeString(Copy(HayStack, M, 16*65536))) = '' Then
                       Break
                    Else
                       Begin
                         WriteLn('Pattern parsing: unrecognized near [', UnescapeString(Copy(HayStack, M, 300)), ']');
                         Halt(-300)
                       End;

                 Start := RS[F].MatchPos[NeedleNum];
                 Stop := Start + RS[F].MatchLen[NeedleNum] - 1;

                 K := Start;
                 While (K <= Stop) And (Map[K] < 0) Do
                   Inc(K);

                 If K > Stop Then
                    Begin
                      Replacement := TPattern(Patterns.Objects[F]).GetReplacement(ENV, UTF8Encode(RS[F].ExportXML));
                      If (Stop < Start) And (Start >= Length(HayStack)) Then
                         Begin
                           SetLength(Map, Length(Map)+1);
                           Map[Length(Map)-1] := Replacers.Count
                         End
                      Else
                          For K := Start To Stop Do
                              Map[K] := Replacers.Count;
                      If TPattern(Patterns.Objects[F]).Fact Then
                         Begin
                           Replacers.AddObject(Replacement, IntegerToTObject(1));
                           Replacement := ''
                         End
                      Else
                         Replacers.AddObject(Replacement, Nil);

                      Inc(GID);
                      ENV.setGID(GID);
                      G := Max(1, Stop-10);
                      If (Stop > 1) And (HayStack[Stop-1] = '\') Then
                         Inc(G);
                      PP := Start;
                      M := Stop+1;
                    End;
                 Inc(G)
               End;

             For F := 0 To Patterns.Count-1 Do
               RS[F].Free
           End
        Else If PatternsMode = pmScan Then
           Begin
              For F := 0 To Patterns.Count-1 Do
                  Begin
                    With TPattern(Patterns.Objects[F]) Do
                      P := '(' + Context1 + ')(' + Needle + ')(' + Context2 + ')';
                    Context1Num := 1;
                    NeedleNum := Context1Num + 1 + CountBrackets(TPattern(Patterns.Objects[F]).Context1);
                    Context2Num := NeedleNum + 1 + CountBrackets(TPattern(Patterns.Objects[F]).Needle);
                    R := TRegExpr.Create(P);
                    R.Compile;
                    R.SetENV(ENV);
                    R.SetDB(db);
                    R.InputString := HayStack;
                    G := 1;
                    While (G <= Length(HayStack)) And R.ExecPos(G) Do
                      Begin
                        Start := R.MatchPos[NeedleNum];
                        Stop := Start + R.MatchLen[NeedleNum] - 1;

                        K := Start;
                        While (K <= Stop) And (Map[K] < 0) Do
                          Inc(K);

                        If K > Stop Then
                           Begin
                             Replacement := TPattern(Patterns.Objects[F]).GetReplacement(ENV, UTF8Encode(R.ExportXML));
                             If (Stop < Start) And (Start >= Length(HayStack)) Then
                                Begin
                                  SetLength(Map, Length(Map)+1);
                                  Map[Length(Map)-1] := Replacers.Count
                                End
                             Else
                                 For K := Start To Stop Do
                                     Map[K] := Replacers.Count;
                             If TPattern(Patterns.Objects[F]).Fact Then
                                Begin
                                  Replacers.AddObject(Replacement, IntegerToTObject(1));
                                  Replacement := ''
                                End
                             Else
                                Replacers.AddObject(Replacement, Nil);
                             Inc(GID);
                             ENV.setGID(GID);
                             G := Start
                           End;
                        Inc(G)
                      End;
                    R.Free;
                  End
           End;

        Facts := 'init_facts:-' + MakeReplacements(Map, Begs, Ends, Replacers, HayStack) + 'true.';
        Replacers.Free;

        LL := TStringList.Create;
        LL.Text := Facts;
        LL.SaveToFile('_.pl');
        LL.Free;
        MakeConsultation('_.pl', 'init_facts');

        ENV.Free;

        db.Release;

        Begs.Free;
        Ends.Free
     End;

  With Patterns Do
    Begin
      For F := 0 To Count - 1 Do
          Objects[F].Free;
      Free
    End;

  L.Free
end;

procedure PreprocStage2(Var Restrictions: TRestrictions);

Var ConsultFile, OutFile: TextFile;
    L, L1: TAnalyser;
    Eval: TEvaluator;
    S, S1, S2, S3: String;
    ID: String;
    Modules: TStringList;
    Module: TModule;
    ModulePrefix: String;
    ModParams: TStringList;
    LN: TLine;
    Consult, TextModule: String;
    Goals, Expanded: TStringList;
    _Consts: TStringList;
    ByPass: Boolean;
    I,F,G,K,H,Q: Integer;
    Rslt: Real;
    Flag: Boolean;
begin
  L:=TAnalyser.Create(IdentSet,[Space,Tabulation]);
  L1:=TAnalyser.Create(IdentSet,[Space,Tabulation]);

  Modules := TStringList.Create;

  _Consts := TStringList.Create;

  LCounter:=1;
  // Second preprocessing phase
  // Handle consts and macromodules (early topologies)
  While (LCounter <= Lines.Count) And Not L.Error Do
    Begin
      S := Lines.Strings[LCounter-1];
      L.AnlzLine := S;

      ByPass := False;
      For F := 0 To High(Restrictions) Do
          If (LCounter >= Restrictions[F].First) And (LCounter <= Restrictions[F].Last) Then
             Begin
               ByPass := True;
               Break
             End;

      If L.IsNext(Pound) Then
         Begin
           L.Check(Pound);
           If (L.FindIdent(True) = iddef_module) And Not ByPass Then
              Begin
                G := LCounter;
                L.GetIdent(True);
                L.Check(LeftBracket);
                S := L.GetBalancedListItem(True,[RightBracket]); // Prefix
                ID := L.GetIdent(False);
                F := _IndexOf(Modules, ID);
                If F >= 0 Then
                   Begin
                     WriteLn('"'+ID+'" macromodule: redefinition',TLine(Lines.Objects[LCounter-1]).GetDescription);
                     Halt(-1)
                   End;
                L.Check(LeftBracket);
                ModParams := TStringList.Create;
                Flag := L.IsNext(RightBracket);
                If Flag Then
                   L.Check(RightBracket)
                Else
                  While Not (Flag Or L.Error Or L.Empty) Do
                    Begin
                      S1 := L.GetIdent(False);
                      If Length(S1) = 0 Then
                         Begin
                           WriteLn('Incorrect parameters list',TLine(Lines.Objects[LCounter-1]).GetDescription);
                           Halt(-1)
                         End;
                      ModParams.Add(S1);
                      If L.IsNext(Comma) Then
                         L.Check(Comma)
                      Else If L.IsNext(RightBracket) Then
                         Flag := L.Check(RightBracket)
                    End;
                LineDelimiter := #$07;
                S1 := Trim(L.GetBalancedListItem(True, [SemiColon], @GetLineFromLines));
                LineDelimiter := '';
                If Length(S1) > 1 Then
                   If S1[1] = LeftFBracket Then
                      Begin
                        System.Delete(S1,1,1);
                        If (Length(S1) > 0) And (S1[Length(S1)] = RightFBracket) Then
                           SetLength(S1,Length(S1)-1)
                        Else
                           Begin
                             WriteLn('Probably closing bracket "}" absent in module "',ID,'"',TLine(Lines.Objects[LCounter-1]).GetDescription);
                             Halt(-1)
                           End
                      End;
                Module := TModule.Create(ModParams, S, Trim(S1));
                For F := G To LCounter Do
                    TLine(Lines.Objects[F-1]).Restricted := True;
                Modules.AddObject(ID, Module);
                ModParams := Nil
              End
         End
      Else
         Begin
            S := L.AnlzLine;
            Flag := False;
            F := 0;
            While (F < Modules.Count) And Not Flag Do
              Begin
                G := 0;
                K := 1;
                ID := Modules.Strings[F];
                Q := 0; // Counter of double quotes
                H := 1; // Previous K+G-1 value
                Repeat
                  G := Pos(ID,Copy(S,K,Length(S)));
                  If G > 0 Then
                     Begin
                       Flag := ((K+G-1 = 1) Or Not (S[K+G-2] in IdentSet)) And
                               (((K+G-1+Length(ID)-1 = Length(S)) Or (S[K+G-1+Length(ID)] in [Space, Tabulation, LeftBracket])));
                       While H < K+G-1 Do
                         Begin
                           If S[H] = DblQuote Then
                              Inc(Q);
                           Inc(H)
                         End;
                       Flag := Flag And ((Q Mod 2)=0);
                       If Not Flag Then
                          K := K+G
                     End
                Until (G = 0) Or Flag;
                If Not Flag Then
                   Inc(F)
              End;
            If Flag Then
               Begin
                 ModulePrefix := Copy(S, 1, K+G-2);
                 L.AnlzLine := Copy(S, K+G-1, Length(S));
                 Module := TModule(Modules.Objects[F]);
                 S := Module.Body;
                 L.GetIdent(False);
                 L.Check(LeftBracket);
                 S3 := ID + LeftBracket;
                 Flag := L.IsNext(RightBracket);
                 G := 0;
                 If Flag Then
                    Begin
                      L.Check(RightBracket);
                      If Module.Params.Count > 0 Then
                         Begin
                           WriteLn('Incorrect parameters number',TLine(Lines.Objects[LCounter-1]).GetDescription);
                           Halt(-1)
                         End
                    End
                 Else
                   While Not (Flag Or L.Error Or L.Empty) Do
                     Begin
                       If G >= Module.Params.Count Then
                          Begin
                            WriteLn('Incorrect parameters number',TLine(Lines.Objects[LCounter-1]).GetDescription);
                            Halt(-1)
                          End;
                       S1 := L.GetBalancedListItem(False,[Comma,RightBracket], @GetLineFromLines);
                       If Length(S1) = 0 Then
                          Begin
                            WriteLn('Incorrect parameters list',TLine(Lines.Objects[LCounter-1]).GetDescription);
                            Halt(-1)
                          End;
                       // Substitutes consts into S1
                       For K := 0 To _Consts.Count - 1 Do
                           S1 := Substitute(S1, '(', ')', _Consts.Strings[K], PString(_Consts.Objects[K])^);
                       // Calculate S1 if necessary
                       L1.AnlzLine := S1;
                       If Not L1.IsNextSet([Quote, DblQuote, LeftSqrBracket]) Then
                          Begin
                            Eval := TEvaluator.Create(IdentSet,[Space, Tabulation]);
                            Eval.AnlzLine := S1;
                            Rslt := 0.0;
                            If Eval.EvalExpression([],Rslt) Then
                               If Abs(Rslt-Round(Rslt)) < 1E-8 Then
                                  S1 := IntToStr(Round(Rslt))
                               Else
                                  S1 := FloatToStr(Rslt)
                            Else
                               Begin
                                 WriteLn('"'+S1+'" -- can''t evauate to the numerical constant',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                 Halt(-1)
                               End;
                            If Eval.Error Then
                               WriteLn('Evaluator error',TLine(Lines.Objects[LCounter-1]).GetDescription);
                            Eval.Free
                          End;
                       S3 := S3 + S1 + Comma;
                       // Substitute S1
                       S := Substitute(S, '', '', Module.Params.Strings[G], S1);
                       If L.IsNext(Comma) Then
                          L.Check(Comma)
                       Else If L.IsNext(RightBracket) Then
                          Flag := L.Check(RightBracket);
                       Inc(G)
                     End;
                 If S3[Length(S3)] = Comma Then
                    S3[Length(S3)] := RightBracket
                 Else
                    S3 := S3 + RightBracket;

                 Goals := TStringList.Create;

                 S1 := L.AnlzLine;
                 L.AnlzLine := S;
                 Consult := Predicates;
                 TextModule := '';
                 While Not (L.Empty Or L.Error) Do
                   Begin
                     S := L.GetBefore(False,[At]);
                     If L.IsNext(At) Then
                        Begin
                          L.Check(At);
                          L1.AnlzLine := S;
                          While (Not L1.Empty) And L1.IsNext(#$07) Do
                            L1.Check(#$07);
                          If L1.Empty Then
                             S := ' '
                          Else
                             S := L1.AnlzLine;
                          TextModule := TextModule + StringReplace(S,#$07,CRLF,[rfReplaceAll]);
                          S := '';
                          Repeat
                            S := S + L.GetBalancedListItem(True, [Point]);
                            If L.Empty Or L.IsNext(#$07) Then
                               Break;
                            S := S + Point
                          Until L.Error Or L.Empty;
                          L1.AnlzLine := S;
                          While (Not L1.Empty) And L1.IsNext(#$07) Do
                            L1.Check(#$07);
                          If L1.FindIdent(True) = idgoal Then
                             Begin
                               L1.GetIdent(False);
                               L1.Check(Colon);
                               L1.Check(Dash);
                               K := Goals.Add(DelBlanks(StringReplace(L1.AnlzLine,#$07,'',[rfReplaceAll])));
                               TextModule := TextModule + Chr(1) + IntToStr(K+1) + Chr(2)
                             End
                          Else
                             Begin
                               S := StringReplace(S,#$07,CRLF,[rfReplaceAll]) + Point;
                               Consult := Consult + S + CRLF
                             End
                        End
                     Else
                        TextModule := TextModule + StringReplace(S,#$07,CRLF,[rfReplaceAll])
                   End;
                 // Create consult file
                 For K := 0 To Goals.Count-1 Do
                     Consult := Consult + 'goal'+IntToStr(K)+':-'+Goals.Strings[K]+',!.'+CRLF;
                 AssignFile(ConsultFile, '_.pl');
                 Rewrite(ConsultFile);
                 WriteLn(ConsultFile, Consult);
                 CloseFile(ConsultFile);
                 // Execute goals and substitute results into TextModule at characters[1..31]
                 For K := 0 To Goals.Count-1 Do
                     Begin
                       MakeConsultation('_.pl', 'goal'+IntToStr(K));
                       AssignFile(OutFile, '_.out');
                       Reset(OutFile);
                       S:='';
                       While Not Eof(OutFile) Do
                          Begin
                            ReadLn(OutFile, S2);
                            S := S + S2;
                            If Not Eof(OutFile) Then AppendStr(S,CRLF)
                          End;
                       CloseFile(OutFile);
                       TextModule := StringReplace(TextModule,Chr(1)+IntToStr(K+1)+Chr(2),S,[rfReplaceAll])
                     End;
                 // Analyze special markers, collect text.
                 If Pos(BracketsOff, TextModule) > 0 Then
                    TextModule := StringReplace(TextModule,BracketsOff,'',[rfReplaceAll])
                 Else
                    TextModule := '{'+CRLF+TextModule+CRLF+'}';
                 If Pos(PrefixOff, TextModule) > 0 Then
                    TextModule := StringReplace(TextModule,PrefixOff,'',[rfReplaceAll])
                 Else
                    TextModule := Module.Prefix + ' ' + TextModule;
                 If Pos(Pruning, TextModule) > 0 Then
                    Begin
                      TextModule := StringReplace(TextModule,Pruning,'',[rfReplaceAll]);
                      PassCount := PreprocPasses
                    End;
                 Expanded := TStringList.Create;
                 Expanded.Text := TextModule;
                 With Expanded Do
                    Begin
                      If Count = 0 Then Add('');
                      Strings[Count-1] := Strings[Count-1] + S1;
                      Strings[0] := ModulePrefix + Strings[0]
                    End;
                 F := 0;
                 While F < Expanded.Count Do
                   If Trim(Expanded.Strings[F]) = '' Then
                      Expanded.Delete(F)
                   Else
                      Inc(F);
                 K := Files.AddObject(Underscore+S3,Expanded);
                 LN := TLine(Lines.Objects[LCounter-1]);
                 Lines.Delete(LCounter-1);
                 For F := 0 To Expanded.Count-1 Do
                     Lines.InsertObject(LCounter-1+F,Expanded.Strings[F], TLine.Derive(LN,K,F+1));
                 LN.Free;
                 Goals.Free;
                 Continue // go to the loop header without LCounter incrementing
               End
            Else
              Begin
                Flag := False;
                Repeat
                  If (L.FindIdent(True) = idConst) And Not ByPass Then
                     Begin
                       L.GetIdent(True);
                       Repeat
                         Repeat
                           ID := L.GetIdent(False);
                           If Length(ID) = 0 Then
                              L.DelFirst
                         Until L.IsNext(Equal) Or L.Error Or L.Empty;
                         If Length(ID) > 0 Then
                            Begin
                              L.Check(Equal);
                              S1 := L.GetBalancedListItem(False,[Comma,SemiColon],@GetLineFromLines);
                              // Substitutions. We substitute all defined above consts into current const
                              F := _IndexOf(_Consts, ID);
                              If F >= 0 Then
                                 WriteLn('Panic: const ', ID, ' encountered more than once. Compilation may be incorrect');
                              For F := 0 To _Consts.Count - 1 Do
                                  S1 := Substitute(S1, '(', ')', _Consts.Strings[F], PString(_Consts.Objects[F])^);
                              _Consts.AddObject(ID, TObject(NewStr(S1)));
                              If L.IsNext(Comma) Then
                                 L.Check(Comma)
                            End
                       Until (Length(ID) = 0) Or L.Empty Or L.Error Or L.IsNext(SemiColon);
                       If L.IsNext(SemiColon) Then
                          L.Check(SemiColon)
                     End
                  Else
                     Flag := True
                Until Flag Or L.Empty Or L.Error
              End
         End;
      Inc(LCounter)
    End;

  If _Consts.Count > 0 Then
     Begin
       WriteLn('Collected constants:');
       WriteLn('--------------------');
       For F:=0 to _Consts.Count-1 do
           WriteLn(_Consts.Strings[F],' = ',PString(_Consts.Objects[F])^);
       WriteLn('--------------------')
     End;

  _Consts.Free;

  SetLength(Restrictions, 0);

  With Modules Do
    Begin
      For F := 0 To Count - 1 Do
          Objects[F].Free;
      Free
    End;

  L.Free;
  L1.Free
end;

(* *)
Var doner: switch_gprolog7;
(* *)

Initialization
  PatternsOrder := TStringList.Create;

Finalization
  (* *)
  If (Prologer <> 0) And (Prologer <> DWORD(-1)) Then
     begin
       doner := switch_gprolog7(GetProcedureAddress(Prologer, 'done_gprolog7'));
       if Assigned(doner) Then
          doner('_.info');
       FreeLibrary(Prologer)
     end;
  (* *)
  PatternsOrder.Free
end.

