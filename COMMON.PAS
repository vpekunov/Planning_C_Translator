Unit Common;

Interface

{$CODEPAGE UTF8}

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses Classes, Lexique;

Const gpuNone = 0;
      gpuOnly = 1;
      gpuBoth = 2;

Const strGlue = '@glue@';

Const lexer_preproc =
      {$IF NOT DEFINED(UNIX) AND NOT DEFINED(LINUX)}'run_lexer_preproc.bat'
      {$ELSE}'./run_lexer_preproc.sh'
      {$ENDIF}
      ;
      lexer_plc =
      {$IF NOT DEFINED(UNIX) AND NOT DEFINED(LINUX)}'run_lexer_plc.bat'
      {$ELSE}'./run_lexer_plc.sh'
      {$ENDIF}
      ;
      temp_code = '_.code';

Type

{ TLine }

 TLine = Class
        FileIdx: Array Of Integer;
        LineNum: Array Of Integer;
        _ModeGPU: Byte;
        Restricted: Boolean;
        Constructor Create(_FileIdx, _LineNum: Integer; __ModeGPU: Byte);
        constructor Derive(Parent: TLine; _FileIdx, _LineNum: Integer);
        Function    IsMacroResult: Boolean;
        Function    GetOriginalLine: String;
        Function    GetDescription: String;
        Function    GetRef(Var LNum: Integer): String;
        Function    GetLineNumbers: String;
        Destructor  Destroy; Override;
     End;

 TObjList = class(TList)
        procedure  Clear; override;
 End;

 TObjStrList = class(TStringList)
        procedure  Clear; override;
 Public
        destructor Destroy; override;
 End;

Type TRestriction = Record
        First, Last: Integer
     End;

Type TRestrictions = Array Of TRestriction;

Type IDArray = Array Of String;

Type TIODirection  = (dirInput,dirOutput);
Type TIODirections = Set Of TIODirection;

Type TResultType = (rsOk, rsNonStrict, rsStrict);

Type SubstituteHandle = Function(Var S: WideString; Const Word: String; Var Idx: Integer): WideString;

Function TObjectToInteger(S: TObject): Integer;
Function IntegerToTObject(S: Integer): TObject;
Function BooleanToTObject(B: Boolean): TObject;
Function RandomName: String;

Function RemoveCRLF(Const S: String): String;

Procedure StripComments(Var S: WideString; Var Flag: Boolean);
Function GetLineFromLines(Var S: WideString):Boolean;
Function _TrimRight(Const S: String): String;

Procedure GetFBlock(L: TAnalyser; Dividers: TermSet; Var List: TStringList);
Function Substitute(S: WideString; Const Prefix, Postfix: String; Const ID, Subst: String;
                       Const Handler: SubstituteHandle = Nil; Const UseTriagQuotes: Boolean = False): WideString;

Function _IndexOf(L: TStringList; Const What: String): Integer;

Function DelBlanks(Const S: String): String;
Function Escapize(Const S: WideString): String;
Function CRC(Const S: String): LongInt;
Procedure WriteString(Var Out: TextFile; Const V: String; S: TStringList);
Procedure WriteString(Var _Out: TStringList; Const V: String; S: TStringList);
Function InQuotes(Const S: String; L:Integer; Quote:Char): Boolean;

function EncodeStr(Const S:String):String;
function DecodeStr(Const S:String):String;

procedure MakeErrorCommon(Const Msg: String);
procedure MakeInfoCommon(Const Msg: String);

procedure VerifyProgram(PreprocessingMode, Obligatoire, IsVectorized, IsClustered: Boolean);

function RunExtCommand(Const App,Prm,OutFName: String):String;

procedure ProcessGlue(Var _Out: TStringList);

Var LCounter: Integer;
    Files: TStringList;
    Lines: TStringList;
    CommentFlag: Boolean;
    LineDelimiter: String;

Implementation

Uses SysUtils, Consts;

{ TLine }

constructor TLine.Create(_FileIdx, _LineNum: Integer; __ModeGPU: Byte);
begin
  Inherited Create;
  SetLength(FileIdx, 1);
  FileIdx[0] := _FileIdx;
  SetLength(LineNum, 1);
  LineNum[0] := _LineNum;
  _ModeGPU := __ModeGPU;
  Restricted := False
end;

constructor TLine.Derive(Parent: TLine; _FileIdx, _LineNum: Integer);
begin
  FileIdx := Copy(Parent.FileIdx,0,Length(Parent.FileIdx));
  SetLength(FileIdx, Length(FileIdx)+1);
  FileIdx[High(FileIdx)] := _FileIdx;
  LineNum := Copy(Parent.LineNum,0,Length(Parent.LineNum));
  SetLength(LineNum, Length(LineNum)+1);
  LineNum[High(LineNum)] := _LineNum;
  _ModeGPU := Parent._ModeGPU;
  Restricted := False
end;

function TLine.IsMacroResult: Boolean;
begin
  Result := Files.Strings[FileIdx[High(FileIdx)]][1] = Underscore
end;

function TLine.GetOriginalLine: String;
begin
  Result := TStringList(Files.Objects[FileIdx[High(FileIdx)]]).Strings[LineNum[High(LineNum)]-1]
end;

function TLine.GetDescription: String;

Var F: Integer;
begin
   Result := '';
   For F := High(FileIdx) DownTo Low(FileIdx) Do
       Result := Result + ' in line '+IntToStr(LineNum[F])+'['+Copy(Files.Strings[FileIdx[F]],2,255)+']';
   For F := High(FileIdx) DownTo Low(FileIdx) Do
       If Files.Strings[FileIdx[F]][1] = UnderScore Then
          Result := Result + CRLF + '[' + Copy(Files.Strings[FileIdx[F]],2,255) +'] is [' + CRLF +
                    TStringList(Files.Objects[FileIdx[F]]).Text + ']'
end;

function TLine.GetRef(Var LNum: Integer): String;

function Normalize(Const S: String): String;
Begin
   Result := S;
   If Length(S) > 0 Then
      If S[Length(S)] = BackSlash Then
         If Length(S) > 1 Then
            If S[Length(S)-1] = BackSlash Then
               Exit
            Else
               System.Delete(Result, Length(S), 1)
         Else
            System.Delete(Result, Length(S), 1)
end;

Var F: Integer;
begin
   Result := Normalize(Copy(Files.Strings[FileIdx[High(FileIdx)]],2,255));
   LNum := LineNum[High(FileIdx)];
   For F := High(FileIdx)-1 DownTo Low(FileIdx) Do
       Result := Result + '(' + IntToStr(LineNum[F])+')['+Normalize(Copy(Files.Strings[FileIdx[F]],2,255))+']';
   Result := StringReplace(Result, '"', '''', [rfReplaceAll]);
end;

function TLine.GetLineNumbers: String;

Var S: String;
    F: Integer;
begin
   Result := '';
   For F := High(FileIdx) DownTo Low(FileIdx) Do
     Begin
       S := StringReplace(Copy(Files.Strings[FileIdx[F]],2,255),'"','*',[rfReplaceAll]);
       If (Length(S) > 0) And (S[Length(S)] = '\') Then
          System.Delete(S, Length(S), 1);
       Result := Result + '#line '+IntToStr(LineNum[F])+' "'+S+'"' + CRLF
     End
end;

destructor TLine.Destroy;
begin
  SetLength(FileIdx, 0);
  SetLength(LineNum, 0);
  Inherited Destroy
end;

{ TObjList }

procedure TObjList.Clear;

Var F:Integer;
begin
     For F:=0 To Count-1 Do
         TObject(Items[F]).Free;
     Inherited
end;

{ TObjStrList }

procedure TObjStrList.Clear;

Var F:Integer;
begin
     For F:=0 To Count-1 Do
         Objects[F].Free;
     Inherited
end;

destructor TObjStrList.Destroy;
begin
     Clear;
     Inherited
end;

Function TObjectToInteger(S: TObject): Integer;

Var V64: Int64 Absolute S;
    V32: Integer Absolute S;
Begin
  {$WARN 6018 OFF}
  If SizeOf(S) = 4 Then Result := V32
  Else If SizeOf(S) = 8 Then Result := V64
  Else
    Begin
      WriteLn('Unknown pointer size');
      Halt(-1)
    End;
  {$WARN 6018 ON}
End;

Function IntegerToTObject(S: Integer): TObject;

Var V64: Int64 Absolute Result;
    V32: Integer Absolute Result;
Begin
  {$WARN 6018 OFF}
  If SizeOf(Result) = 4 Then V32 := S
  Else If SizeOf(Result) = 8 Then V64 := S
  Else
    Begin
      WriteLn('Unknown pointer size');
      Halt(-1)
    End;
  {$WARN 6018 ON}
End;

Function BooleanToTObject(B: Boolean): TObject;
Begin
  Result := IntegerToTObject(Integer(B))
End;

Function RandomName: String;

Const L = 6;

Var F: Integer;
Begin
  SetLength(Result, L);
  For F := 1 To L Do
    Result[F] := Chr(Ord('a')+Random(26))
End;

Function RemoveCRLF(Const S: String): String;
Begin
  Result := StringReplace(StringReplace(S, #$0D, '', [rfReplaceAll]), #$0A, '', [rfReplaceAll]);
End;

Function InQuotes(Const S: String; L:Integer; Quote:Char): Boolean;

Var F: Integer;
Begin
  If L > Length(S) Then L := Length(S);
  Result := False;
  For F := 1 To L Do
    If S[F] = Quote Then
       Result := Not Result
End;

Procedure StripComments(Var S: WideString; Var Flag: Boolean);

Const ProbablyXPathF: Boolean = False;

Var S1:WideString;
    ProbablyPattern: Boolean;
    ByPass: Boolean;
    F: Integer;
begin
     S1 := Trim(S);
     ProbablyPattern := Pos('#def_pattern', S1) = 1;
     If ProbablyXPathF Then
        ProbablyXPathF := Pos('}', S1) <> 1
     Else
        ProbablyXPathF := Pos('#def_xpath', S1) = 1;
     ByPass := ProbablyPattern Or ProbablyXPathF;
     S1 := '';
     F := 1;
     While F <= Length(S) Do
       If (F+1 <= Length(S)) And (S[F] = '/') And (S[F+1] = '*') Then
          begin
            Flag := True;
            Inc(F,2)
          end
       Else If (F+1 <= Length(S)) And (S[F] = '*') And (S[F+1] = '/') Then
          begin
            Flag := False;
            Inc(F,2)
          end
       Else
          begin
            If Not Flag Then
               If (F+1 <= Length(S)) And (S[F] = '/') And (S[F+1] = '/') And Not ByPass Then
                  Break
               Else
                  S1 := S1 + S[F];
            Inc(F)
          end;
     S := S1
end;

Function GetLineFromLines(Var S:WideString):Boolean;

Var L:WideString;
Begin
     Result:=LCounter < Lines.Count;
     If Result Then
        Begin
          Repeat
             Inc(LCounter);
             L := UTF8Decode(Lines.Strings[LCounter-1]);
             L := L+LineDelimiter;
             StripComments(L, CommentFlag);
             L:=Trim(L);
          Until (Length(L)>0) Or (LCounter >= Lines.Count);
          S:=S+' '+LineDelimiter+L
        End
End;

Function _TrimRight(Const S: String): String;
Begin
  Result := S;
  While (Length(Result) > 0) And (Result[Length(Result)]=Space) Do
    SetLength(Result, Length(Result)-1)
End;

Procedure GetFBlock(L: TAnalyser; Dividers: TermSet; Var List: TStringList);

Var LST: TStringList;
    LD: WideString;
    S, S1: WideString;
    F, G: Integer;
Begin
  LST := TStringList.Create;
  S:='';
  If L.Empty And GetLineFromLines(S) Then
     L.AnlzLine:=S;
  L.Check(LeftFBracket);
  S:='';
  If L.Empty And GetLineFromLines(S) Then
     L.AnlzLine:=S;
  List.Clear;
  LD := LineDelimiter;
  While (Not L.IsNext(RightFBracket)) And Not L.Error Do
    Begin
      G := LCounter;
      LineDelimiter := '###';
      S:=L.GetBalancedListItem(False, Dividers + [RightFBracket], @GetLineFromLines);
      LineDelimiter := LD;
      L.AnlzLine := StringReplace(L.AnlzLine, '###', LD, [rfReplaceAll]);
      L.DelSpaces;
      If L.Error Then Exit;
      If Not L.IsNext(RightFBracket) Then
         Begin
           S:=S+L.AnlzLine[1];
           L.CheckSet(Dividers)
         End;
      S1 := StringReplace(S, '###', CRLF, [rfReplaceAll]);
      LST.Text := S1;
      For F := 0 To LST.Count-1 Do
          If Length(Trim(LST.Strings[F])) > 0 Then
             List.AddObject(LST.Strings[F], IntegerToTObject(F+G));
      S:='';
      If L.Empty And GetLineFromLines(S) Then
         L.AnlzLine:=S;
    End;
  S:='';
  If L.Empty And GetLineFromLines(S) Then
     L.AnlzLine:=S;
  L.Check(RightFBracket);
  LST.Free
End;

Function Substitute(S: WideString; Const Prefix, Postfix: String; Const ID, Subst: String;
            Const Handler: SubstituteHandle = Nil; Const UseTriagQuotes: Boolean = False): WideString;

Const qtNone   = 0;
      qtSingle = 1;
      qtDouble = 2;
      qtTriag = 3;

Var Word: String;
    _Quote:Byte;
    F: Integer;
Begin
  Result := '';
  Word := '';
  _Quote:=qtNone;
  F := 1;
  While F <= Length(S) Do
    Begin
      If (S[F] in IdentSet) And (_Quote = qtNone) Then
         Word := Word + S[F]
      Else
         Begin
           If Length(Word) > 0 Then
              Begin
                If Assigned(Handler) Then
                   Result := Result + Handler(S, Word, F)
                Else If Word = ID Then
                   Result := Result + Prefix + Subst + Postfix
                Else
                   Result := Result + Word;
                Word := ''
              End;
           If S[F] = Quote Then
              Begin
                If _Quote = qtSingle Then
                   _Quote:=qtNone
                Else If _Quote = qtNone Then
                   _Quote:=qtSingle
              End
           Else If S[F] = DblQuote Then
              Begin
                If _Quote = qtDouble Then
                   _Quote:=qtNone
                Else If _Quote = qtNone Then
                   _Quote:=qtDouble
              End
           Else If UseTriagQuotes And (S[F] = Less) Then
              Begin
                If _Quote = qtNone Then
                   _Quote:=qtTriag
              End
           Else If UseTriagQuotes And (S[F] = Greater) Then
              Begin
                If _Quote = qtTriag Then
                   _Quote:=qtNone
              End;
           Result := Result + S[F]
         End;
      Inc(F)
    End;
  If Length(Word) > 0 Then
     If Assigned(Handler) Then
        Result := Result + Handler(S, Word, F)
     Else If Word = ID Then
        Result := Result + Prefix + Subst + Postfix
     Else
        Result := Result + Word
End;

Function _IndexOf(L: TStringList; Const What: String): Integer;

Var F: Integer;
Begin
  If Assigned(L) Then
     With L Do
       For F := 0 To Count - 1 Do
           If Strings[F] = What Then
              Begin
                Result := F;
                Exit
              End;
  Result := -1
End;

Function DelBlanks(Const S: String): String;

Var _Quote: Char;
    F: Integer;
Begin
  Result := '';
  _Quote := #0;
  For F := 1 To Length(S) Do
      If (S[F] <> Space) Or (_Quote <> #0) Then
         Begin
           If S[F] in [Quote, DblQuote] Then
              If _Quote = #0 Then
                 _Quote := S[F]
              Else If Quote = S[F] Then
                 _Quote := #0;
           Result := Result + S[F]
         End
End;

Function Escapize(Const S: WideString): String;

Var _Quote: WideChar;
    F: Integer;
Begin
  Result := '';
  _Quote := #0;
  For F := 1 To Length(S) Do
      If _Quote = #0 Then
         Begin
           If S[F] in [Quote, DblQuote] Then
              _Quote := S[F];
           Result := Result + S[F]
         End
      Else
         Begin
           If _Quote = S[F] Then
              _Quote := #0;
           Case S[F] Of
             #9: AppendStr(Result, '\t');
             #$0A: If (F = 1) Or (S[F-1] <> #$0D) Then
                      AppendStr(Result, '\n');
             #$0D: If (F <> Length(S)) And (S[F+1] = #$0A) Then
                      AppendStr(Result, '\n')
                   Else
                      AppendStr(Result, '\r');
             Else Result := Result + S[F]
           end;
         End
End;

function RunExtCommand(Const App,Prm,OutFName: String):String;
begin
     ExecuteProcess(App, Prm, []);
     Result:='';
     If Length(OutFName)>0 Then
        With TStringList.Create Do
          begin
            LoadFromFile(OutFName);
            Result:=Text;
            Free
          end
     Else
        Result:=''
end;

procedure ProcessGlue(var _Out: TStringList);

Var F: Integer;
begin
     F := 0;
     While F < _Out.Count Do
       If (F > 0) And (_Out.Strings[F] = strGlue) Then
          Begin
            _Out.Strings[F - 1] := _Out.Strings[F - 1] + _Out.Strings[F + 1];
            _Out.Delete(F);
            _Out.Delete(F)
          end
       Else
          Inc(F)
end;

procedure VerifyProgram(PreprocessingMode, Obligatoire, IsVectorized, IsClustered: Boolean);

Var Checker: String;
    LN: Integer; FS: String;
    Result: String;
    G: Integer;
begin
     If PreprocessingMode Then
        Checker := lexer_preproc
     Else
        Checker := lexer_plc;
     If FileExists(Checker) Then
        Begin
          With TStringList.Create Do
            Begin
              If IsVectorized Then
                 Add('#pragma plan vectorized');
              If IsClustered Then
                 Add('#pragma plan clustered');
              For G := 0 To Lines.Count-1 Do
                  If Not TLine(Lines.Objects[G]).Restricted Then
                     Begin
                       FS := TLine(Lines.Objects[G]).GetRef(LN);
                       Add('#line ' + IntToStr(LN) + ' "' + FS + '"');
                       Add(Lines[G])
                     End;
              SaveToFile(temp_code);
              Free
            End;
          Result := _TrimRight(RunExtCommand(Checker, temp_code + ' _.result', '_.result'));
          If Length(Result) > 0 Then
             If Obligatoire Then
                Begin
                  MakeErrorCommon(Trim(Result));
                  Halt(1000)
                End
             Else
                MakeInfoCommon('+++ Errors treated as warnings +++' + CRLF +
                    Trim(Result) + CRLF + '++++++++++++++++++++++++++++++++++')
        end
     Else
        MakeErrorCommon('Lexer "' + Checker + '" not found!')
end;

Function CRC(Const S: String): LongInt;

Var F: Integer;
Begin
  Result := 0;
  For F := 1 To Length(S) Do
      Inc(Result, Ord(S[F]))
End;

Procedure WriteString(Var Out: TextFile; Const V: String; S: TStringList);

Var F: Integer;
begin
  WriteLn(Out, 'const char * ', V, '[] = {');
  For F := 0 To S.Count-1 Do
      WriteLn(Out, '"' + StringReplace(StringReplace(S.Strings[F],'\','\\',[rfReplaceAll]),'"','\"',[rfReplaceAll]) + '"', ',');
  WriteLn(Out, 'NULL');
  WriteLn(Out, '};')
end;

Procedure WriteString(Var _Out: TStringList; Const V: String; S: TStringList);

Var F: Integer;
begin
  _Out.Add( 'const char * ' + V + '[] = {');
  For F := 0 To S.Count-1 Do
      _Out.Add( '"' + StringReplace(StringReplace(S.Strings[F],'\','\\',[rfReplaceAll]),'"','\"',[rfReplaceAll]) + '"' + ',');
  _Out.Add( 'NULL');
  _Out.Add( '};')
end;

{$IFDEF FPC}

function EncodeStr(Const S:String):String;
Begin
     Result:=S
End;

function DecodeStr(Const S:String):String;
Begin
     Result:=S
End;

{$ELSE}
{ The part of the following code is excluded (with gratitude) from FreePascal
  sources and slightly modified by VP. }

function UnicodeToUtf8(Dest: PChar; MaxDestBytes: Integer; Source: PWideChar; SourceChars: Integer): Integer;
  var
    i,j : Integer;
    w : word;
  begin
    result:=0;
    if source=nil then
      exit;
    i:=0;
    j:=0;
    if assigned(Dest) then
      begin
        while (i<SourceChars) and (j<MaxDestBytes) do
          begin
            w:=word(Source[i]);
            case w of
              0..$7f:
                begin
                  Dest[j]:=char(w);
                  inc(j);
                end;
              $80..$7ff:
                begin
                  if j+1>=MaxDestBytes then
                    break;
                  Dest[j]:=char($c0 or (w shr 6));
                  Dest[j+1]:=char($80 or (w and $3f));
                  inc(j,2);
                end;
              else
                begin
                    if j+2>=MaxDestBytes then
                      break;
                    Dest[j]:=char($e0 or (w shr 12));
                    Dest[j+1]:=char($80 or ((w shr 6)and $3f));
                    Dest[j+2]:=char($80 or (w and $3f));
                    inc(j,3);
                end;
            end;
            inc(i);
          end;

        if j>MaxDestBytes-1 then
          j:=MaxDestBytes-1;

        Dest[j]:=#0;
      end
    else
      begin
        while i<SourceChars do
          begin
            case word(Source[i]) of
              $0..$7f:
                inc(j);
              $80..$7ff:
                inc(j,2);
              else
                inc(j,3);
            end;
            inc(i);
          end;
      end;
    result:=j+1;
  end;

function Utf8ToUnicode(Dest: PWideChar; MaxDestChars: Integer; Source: PChar; SourceBytes: Integer): Integer;

var
  i,j,mask : Integer;
  w : Integer;
  b : byte;
begin
  if not assigned(Source) then
  begin
    result:=0;
    exit;
  end;
  result:=Integer(-1);
  i:=0;
  j:=0;
  if assigned(Dest) then
    begin
      while (j<MaxDestChars) and (i<SourceBytes) do
        begin
          b:=byte(Source[i]);
          w:=b;
          inc(i);
          if b>=$80 then
            begin
              w:=b and $3f;
              if i>=SourceBytes then
                exit;
              mask:=$C0;
              while (mask>1) and ((b and mask)=mask) do
                begin
                  if (byte(Source[i]) and $c0)<>$80 then
                     exit;
                  w:=(w shl 6) or (byte(Source[i]) and $3f);
                  mask:=mask shr 1;
                  inc(i)
                end
            end;
          Dest[j]:=WideChar(w);
          inc(j);
        end;
      if j>=MaxDestChars then
         j:=MaxDestChars-1;
      Dest[j]:=#0;
    end
  else
    begin
      while i<SourceBytes do
        begin
          b:=byte(Source[i]);
          inc(i);
          if b>=$80 then
            begin
              if i>=SourceBytes then
                exit;
              mask:=$c0;
              while (mask>1) and ((b and mask)=mask) do
                begin
                  if (byte(Source[i]) and $c0)<>$80 then
                     exit;
                  mask:=mask shr 1;
                  inc(i)
                end
            end;
          inc(j)
        end;
    end;
  result:=j+1;
end;

function EncodeStr(Const S:String):String;

Var Buf:PWideChar;
    Len:Integer;
Begin
     Buf:=AllocMem((Length(S)+1)*2);
     StringToWideChar(S,Buf,Length(S)+1);
     Len:=UnicodeToUtf8(Nil,0,Buf,Length(S));
     If Len<1 Then
        Result:=S
     Else
        Begin
          SetLength(Result,Len);
          UnicodeToUtf8(PChar(Result),Len,Buf,Length(S));
          Delete(Result,Length(Result),1)
        End;
     FreeMem(Buf)
End;

function DecodeStr(Const S:String):String;

Var Len:Integer;
    Buf:PWideChar;
Begin
     Len:=Utf8ToUnicode(Nil,0,PChar(S),Length(S));
     If Len<1 Then
        Result:=S
     Else
        Begin
          Buf:=AllocMem((Len+1)*2);
          Utf8ToUnicode(Buf,Len,PChar(S),Length(S));
          Result:=WideCharToString(Buf);
          FreeMem(Buf)
        End
End;

{$ENDIF}

procedure MakeErrorCommon(const Msg: String);
begin
     {$IF DEFINED(LCL) OR DEFINED(VCL)}
     MessageDlg(Msg,mtError,[mbOk],0);
     {$ELSE}
     WriteLn(Msg);
     {$ENDIF}
end;


procedure MakeInfoCommon(const Msg: String);
begin
     {$IF DEFINED(LCL) OR DEFINED(VCL)}
     MessageDlg(Msg, mtInformation,[mbOk],0);
     {$ELSE}
     WriteLn(Msg);
     {$ENDIF}
end;

End.
