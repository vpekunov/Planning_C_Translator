Unit Common;

Interface

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses Classes, Lexique;

Type

{ TLine }

 TLine = Class
        FileIdx: Array Of Integer;
        LineNum: Array Of Integer;
        Restricted: Boolean;
        Constructor Create(_FileIdx, _LineNum: Integer);
        constructor Derive(Parent: TLine; _FileIdx, _LineNum: Integer);
        Function    IsMacroResult: Boolean;
        Function    GetOriginalLine: String;
        Function    GetDescription: String;
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

Type SubstituteHandle = Function(Var S: String; Const Word: String; Var Idx: Integer): String;

Function TObjectToInteger(S: TObject): Integer;
Function IntegerToTObject(S: Integer): TObject;
Function BooleanToTObject(B: Boolean): TObject;
Function RandomName: String;

Procedure StripComments(Var S: String; Var Flag: Boolean);
Function GetLineFromLines(Var S:String):Boolean;
Function _TrimRight(Const S: String): String;

Procedure GetFBlock(L: TAnalyser; Dividers: TermSet; Var List: TStringList);
Function Substitute(S: String; Const Prefix, Postfix: String; Const ID, Subst: String; Const Handler: SubstituteHandle = Nil): String;

Function _IndexOf(L: TStringList; Const What: String): Integer;

Function DelBlanks(Const S: String): String;
Function CRC(Const S: String): LongInt;
Procedure WriteString(Var Out: TextFile; Const V: String; S: TStringList);
Function InQuotes(Const S: String; L:Integer; Quote:Char): Boolean;

function RunExtCommand(Const App,Prm,OutFName: String):String;

Var LCounter: Integer;
    Files: TStringList;
    Lines: TStringList;
    CommentFlag: Boolean;
    LineDelimiter: String;

Implementation

Uses SysUtils, Consts;

{ TLine }

constructor TLine.Create(_FileIdx, _LineNum: Integer);
begin
  Inherited Create;
  SetLength(FileIdx, 1);
  FileIdx[0] := _FileIdx;
  SetLength(LineNum, 1);
  LineNum[0] := _LineNum;
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

function TLine.GetLineNumbers: String;

Var S: String;
    F: Integer;
begin
   Result := '';
   For F := High(FileIdx) DownTo Low(FileIdx) Do
     Begin
       S := Copy(Files.Strings[FileIdx[F]],2,255);
       If (Length(S) > 0) And (S[Length(S)] = '\') Then
          S := S + ' ';
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

Function InQuotes(Const S: String; L:Integer; Quote:Char): Boolean;

Var F: Integer;
Begin
  If L > Length(S) Then L := Length(S);
  Result := False;
  For F := 1 To L Do
    If S[F] = Quote Then
       Result := Not Result
End;

Procedure StripComments(Var S: String; Var Flag: Boolean);

Var S1:String;
    F: Integer;
begin
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
               If (F+1 <= Length(S)) And (S[F] = '/') And (S[F+1] = '/') Then
                  Break
               Else
                  AppendStr(S1, S[F]);
            Inc(F)
          end;
     S := S1
end;

Function GetLineFromLines(Var S:String):Boolean;

Var L:String;
Begin
     Result:=LCounter < Lines.Count;
     If Result Then
        Begin
          Repeat
             Inc(LCounter);
             L := Lines.Strings[LCounter-1];
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
    LD: String;
    S, S1: String;
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

Function Substitute(S: String; Const Prefix, Postfix: String; Const ID, Subst: String; Const Handler: SubstituteHandle = Nil): String;

Const qtNone   = 0;
      qtSingle = 1;
      qtDouble = 2;

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
      WriteLn(Out, '"' + StringReplace(S.Strings[F],'"','\"',[rfReplaceAll]) + '"', ',');
  WriteLn(Out, 'NULL');
  WriteLn(Out, '};')
end;

End.
