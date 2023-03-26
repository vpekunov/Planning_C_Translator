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
        Destructor  Destroy; Override;
     End;

Type
    IDArray = Array Of String;

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

Type TIODirection  = (dirInput,dirOutput);
Type TIODirections = Set Of TIODirection;

Type TResultType = (rsOk, rsNonStrict, rsStrict);

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

Procedure CreateStrFile(Const FName,Content: String);

function RunExtCommand(Const App,Prm,OutFName: String):String; overload;
function RunExtCommand(Const App,Prm,OutFName,SignalStr:String; Const WaitFile: String = ''):String; overload;

function EncodeStr(Const S:String):String;
function DecodeStr(Const S:String):String;

procedure MakeErrorCommon(Const _Msg: String);
procedure MakeInfoCommon(Const _Msg: String);

function GetMSG: PChar; cdecl;

Var LCounter: Integer;
    Files: TStringList;
    Lines: TStringList;
    CommentFlag: Boolean;
    LineDelimiter: String;

Const Messaging: Boolean = True;

Var MSG: PChar; cvar; export;

Implementation

Uses SysUtils, Consts{$IF DEFINED(LCL) OR DEFINED(VCL)}, Dialogs{$ENDIF}, Process;

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

Procedure CreateStrFile(Const FName,Content: String);

Var F:TextFile;
begin
     AssignFile(F,FName);
     Rewrite(F);
     Write(F,Content);
     CloseFile(F)
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
      {$IF DEFINED(LCL) OR DEFINED(VCL)}
      MessageDlg('Unknown pointer size',mtError,[mbOk],0);
      {$ELSE}
      WriteLn('Unknown pointer size');
      {$ENDIF}
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
      {$IF DEFINED(LCL) OR DEFINED(VCL)}
      MessageDlg('Unknown pointer size',mtError,[mbOk],0);
      {$ELSE}
      WriteLn('Unknown pointer size');
      {$ENDIF}
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
  While (Length(Result) > 0) And (Result[Length(Result)] in [Space, Tabulation, #$0D, #$0A]) Do
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

function RunExtCommand(Const App,Prm,OutFName,SignalStr:String; Const WaitFile: String = ''):String;

Var AProcess: TProcess;
    P:Integer;
begin
     AProcess := TProcess.Create(nil);
     AProcess.CommandLine := App + ' ' + Prm;
     If Length(WaitFile) = 0 Then
       AProcess.Options := AProcess.Options + [poWaitOnExit]
     Else
       DeleteFile(WaitFile);
     AProcess.Execute;
     AProcess.Free;

     While (Length(WaitFile) > 0) And Not FileExists(WaitFile) Do
        Sleep(100);

     Result:='';
     If (Length(OutFName)>0) And FileExists(OutFName) Then
        With TStringList.Create Do
          begin
            LoadFromFile(OutFName);
            Result:=DecodeStr(Text);
            Free
          end
     Else
        Result:='';
     P:=Pos(SignalStr,Result);
     If P>0 Then Delete(Result,1,P+Length(SignalStr)-1)
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

procedure MakeErrorCommon(const _Msg: String);
begin
   StrPCopy(MSG, String('Error: ' + _Msg))
end;


procedure MakeInfoCommon(const _Msg: String);
begin
  StrPCopy(MSG, String('Info: ' + _Msg))
end;

function GetMSG: PChar; cdecl;
begin
  Result := MSG
end;

Initialization
  MSG := GetMem(32768*SizeOf(Char));
  StrPCopy(MSG, '');

Finalization
  FreeMem(MSG);

End.
