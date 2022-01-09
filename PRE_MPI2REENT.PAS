unit Pre_MPI2REENT;

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

interface

uses
  Common, Classes, Lexique, Evaluat;

procedure PreprocStage(ApplyConds: Boolean; Defines: TStringList; Var Restrictions: TRestrictions);

implementation

uses Consts, SysUtils;

Type TDefItem = Record
        Cond, Any: Boolean;
        IgnoreElse: Boolean;
        FirstLine: Integer
     End;

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

procedure PreprocStage(ApplyConds: Boolean; Defines: TStringList; Var Restrictions: TRestrictions);

Var L: TAnalyser;
    Eval: TEvaluator;
    S, S1: String;
    ID: String;
    DefStack: Array Of TDefItem;
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

  SetLength(DefStack, 0);

  LCounter:=1;
  // First preprocessing stage
  // Handle simple defines: substitute into defines and consts
  While (LCounter <= Lines.Count) And Not L.Error Do
    Begin
      S := Lines.Strings[LCounter-1];
      L.AnlzLine := S;

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
                If S1 = idUndef Then
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
              End;
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
           Else If Flag And (S = idInclude) Then
              Begin
                If L.IsNext(DblQuote) Then
                   Begin
                     L.Check(DblQuote);
                     S := Trim(L.GetBefore(True,[DblQuote]));
                     L.Check(DblQuote);
                     If _IndexOf(Files, Asterisk+S) >= 0 Then
                        WriteLn('Warning: preliminary preprocessing encounters more than one #include "'+S+'"',TLine(Lines.Objects[LCounter-1]).GetDescription)
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
                          LN.Free;
                          Continue // return to loop header without end LCounter incrementing
                        End
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

  SetLength(DefStack, 0);

  L.Free
end;

end.

