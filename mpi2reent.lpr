program mpi2reent;

{$IF (NOT DEFINED(UNIX)) AND (NOT DEFINED(LINUX))}
{$APPTYPE CONSOLE}
{$ENDIF}

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses SysUtils, Classes,
     Lexique       in 'LEXIQUE.PAS',
     Consts        in 'CONSTS.PAS',
     Common        in 'COMMON.PAS',
     Pre_MPI2REENT in 'Pre_MPI2REENT.PAS';

Const idmpi_h     = 'mpi.h';
      idclass     = 'CLASS';
      idstruct    = 'STRUCT';
      idunion     = 'UNION';
      idenum      = 'ENUM';
      idtemplate  = 'TEMPLATE';
      idnamespace = 'NAMESPACE';
      idusing     = 'USING';
      idexport    = 'EXPORT';
      idconst     = 'CONST';
      idextern    = 'EXTERN';

Const _idextern = 'extern';
      _idmain   = '_main';

Const idmpi_included = 'MPI_INCLUDED';

Const idmain = 'main';
      idvoid = 'void';

Type TKind = (knNone, knVar, knDeclaration, knFunction);

Function ExtractLastID(S: String; Var Before, After: String): String;

Var F,G: Integer;
begin
  S := Trim(S);
  F := Length(S);
  After := '';
  While (F >= 1) And (S[F] = RightSqrBracket) Do
    Begin
      While (F >= 1) And (S[F] <> LeftSqrBracket) Do
        Begin
          After := S[F] + After;
          Dec(F)
        End;
      If F >= 1 Then
         Begin
           After := S[F] + After;
           Dec(F)
         End
    End;
  G := F;
  While (F >= 1) And (S[F] In IdentSet) Do
    Dec(F);
  Before := Copy(S, 1, F);
  Result := Copy(S, F+1, G-F)
end;

Function HandleParams(L1: TAnalyser; Var Prms: String): TStringList;

Var Before, V, After: String;
Begin
  Result := TStringList.Create;
  If (Length(Prms) = 0) Or (Prms = idvoid) Then
     Prms := ''
  Else
     Begin
       L1.AnlzLine := Prms + Comma;
       While Not L1.Empty Do
         Begin
           Before := '';
           After := '';
           V := ExtractLastID(L1.GetBalancedListItem(True, [Comma]), Before, After);
           Result.Add(V)
         End
     End
End;

Function AnalyzeVars(Vars, Defs: TStringList; L: TAnalyser; Const Tp: String): String;

Var Body: String;
    S, Before, V, After: String;
    Init, InitV: String;
    Flag: Boolean;
Begin
  Result := '';
  Repeat // Переменные
    Init := '';
    InitV := '';
    Before := '';
    After := '';
    Body := L.GetBalancedListItem(False,[Equal, Comma, SemiColon], @GetLineFromLines);
    If L.IsNext(Equal) Then
       Begin
         L.Check(Equal);
         Init := L.GetBalancedListItem(False, [Comma, SemiColon], @GetLineFromLines)
       End;
    V := ExtractLastID(Body, Before, After);
    Result := Result + Tp + ' __' + V + '__[__NPROCS__]' + After + SemiColon + CRLF;
    Init := Trim(Init);
    If Length(Init) > 0 Then
       If Init[1] In [LeftFBracket, Quote, DblQuote] Then
          InitV := Pound + Tp + ' init__' + V + '__' + After + ' = ' + Init + SemiColon
       Else
          InitV := Init;
    S := '#define '+V+' __'+V+'__[__id__]' + CRLF;
    Result := Result + S;
    After := Trim(After);
    If (Length(InitV) > 0) And (Length(After) > 0) Then InitV := SpecSymbol + InitV;
    Vars.AddObject(V, TObject(NewStr(InitV)));
    Defs.AddObject(V, TObject(NewStr(S)));
    Flag := L.IsNext(SemiColon);
    L.CheckSet([Comma, SemiColon])
  Until Flag Or L.Error
End;

Function InStr(Const S: String; L: Integer): Boolean;

Var F: Integer;
Begin
  Result := False;
  For F := 1 To L Do
      If S[F] = DblQuote Then
         Result := Not Result
End;

Function HandleReturn(Var S: String; Const Word: String; Var Idx: Integer): String;

Var L: TAnalyser;
    Arg: String;
Begin
  If Word = 'return' Then
     Begin
       L := TAnalyser.Create(IdentSet,[Space,Tabulation]);
       L.AnlzLine := Copy(S, Idx, Length(S));
       Arg := L.GetBalancedListItem(True, [SemiColon]);
       Result := LeftFBracket +
                 'while(__stopped__); __fcalls__[__id__].pop_back(); return ' + Arg + SemiColon +
                 RightFBracket;
       S := Copy(S, 1, Idx - 1) + Space + L.AnlzLine;
       L.Free
     End
  Else
     Result := Word
End;

Function HandleReturns(Const S: String): String;
Begin
  Result := Substitute(S, '', '', 'return', '', @HandleReturn) + 'while(__stopped__); __fcalls__[__id__].pop_back();' +CRLF
End;

Function HandleExtern(Const S: String): String;

Var Before, V, After: String;
    Start: Integer;
    F, G: Integer;
begin
  Result := '';
  Start := 1;
  Repeat
    F := Pos(_idextern, Copy(S, Start, Length(S)));
    If (F > 0) And ((Start-1+F = 1) Or Not (S[Start-1+F-1] In IdentSet)) And
                   ((Start-1+F+Length(_idextern) > Length(S)) Or Not (S[Start-1+F+Length(_idextern)] in IdentSet)) And
                   Not InStr(S, Start-1+F-1) Then
       Begin
         G := Start - 1 + F + Length(_idextern);
         While (G <= Length(S)) And (S[G] <> SemiColon) Do
           Inc(G);
         Dec(G);
         Before := '';
         After := '';
         V := ExtractLastID(Copy(S, Start-1+F, G-(Start-1)-F+1), Before, After);
         Result := Result + Copy(S, Start, F - 1) + Before + ' __' + V + '__[__NPROCS__]' + After;
         Start := G + 1
       End
    Else If F = 0 Then
       Result := Result + Copy(S, Start, Length(S))
    Else
       Begin
         Result := Result + Copy(S, Start, F);
         Start := Start + F
       End
  Until F = 0
end;

Var Globs: TStringList;
    idNeeded: Boolean;

Function HandleUseID(Var S: String; Const Word: String; Var Idx: Integer): String;
Begin
  Result := Word + Copy(S, Idx, 0); // Чтобы не было сообщений о неиспользуемых параметрах
  If Not idNeeded Then
     Begin
       idNeeded := Word = '__id__';
       If Not idNeeded Then
          idNeeded := _IndexOf(Globs, Word) >= 0
     End
End;

Function UseID(Const S: String): Boolean;
Begin
  idNeeded := False;
  Substitute(S, '', '', '', '', @HandleUseID);
  Result := idNeeded
End;

Var Inp, Out: TextFile;
    OldName, NewName: String;
    nProcs: Integer;
    Restrictions: TRestrictions;
    Defines: TStringList;
    S, S1, S2: String;
    ID, Prefix, Body: String;
    Before, After: String;
    Tp, V, Prms: String;
    Kind: TKind;
    Vars, Funcs, Defs: TStringList;
    DebugThreads: Boolean;
    BufSize: String;
    ParamNames: TStringList;
    LST: TStringList;
    L, L1: TAnalyser;
    FL: TStringList;
    F, G, K: Integer;
    FollowDefs: Boolean;
    ParamNameNum: Integer;
    C: Char;
    Flag: Boolean;
begin
  If ParamCount<2 Then
     Begin
       WriteLn('MPI to Planning C (R) Translator V0.1beta');
       WriteLn('free for any purposes. Original author: V.V.Pekunov, 2016');
       WriteLn('Usage: mpi2reent.exe <num_of_procs> [-followdefines] [-debugthreads] [-bufsize=N] [-Dmacro[=val]] <inputfile.cpp> [outputfile]');
       WriteLn('   -followdefines    If used then the translator performs conditional');
       WriteLn('                     preprocessing using directives define, undef, if and so on.');
       WriteLn('                     Only an active lines are put into the resulting code.');
       WriteLn('   -Dmacro[=val]     Defines macro symbols. It can be very useful when your code');
       WriteLn('                     depends on the symbols that are defined by your main compiler');
       WriteLn('                     but aren''t known to this translator, e.g. _WIN32, _OPENMP ...');
       WriteLn('   -debugthreads     If used then translator traces all functions calls to provide');
       WriteLn('                     possibility of demonstrating a call stack when you inaccurately');
       WriteLn('                     use threads and get an error "Unknown thread"');
       WriteLn('   -bufsize=N        Determines the size of each send/receive buffer in KBytes by default')
     End
  Else
     Begin
       ChDir(ExcludeTrailingBackSlash(ExtractFilePath(ParamStr(0))));

       FollowDefs := False;
       DebugThreads := False;
       BufSize := '(2*1024)';
       Defines := TStringList.Create;
       ParamNameNum := 2;

       While (ParamNameNum <= ParamCount) And
             (Length(ParamStr(ParamNameNum)) >= 3) And
             (ParamStr(ParamNameNum)[1] = Dash) Do
          Begin
            S := ParamStr(ParamNameNum);
            If S[2] = 'D' Then
               Begin
                 F := Pos(Equal, S);
                 If F > 0 Then
                    Defines.AddObject(Copy(S, 3, F - 3), TObject(NewStr(Copy(S, F + 1, Length(S)))))
                 Else
                    Defines.AddObject(Copy(S, 3, Length(S)), TObject(NewStr('1')))
               End
            Else If Copy(S, 2, Length('followdefines')) = 'followdefines' Then
               FollowDefs := True
            Else If Copy(S, 2, Length('debugthreads')) = 'debugthreads' Then
               DebugThreads := True
            Else If Copy(S, 2, Length('bufsize=')) = 'bufsize=' Then
               BufSize := '(' + Copy(S, 2+Length('bufsize='), Length(S)) + ')'
            Else
              Begin
                WriteLn('Unknown parameter ', S);
                Halt(-1)
              End;
            Inc(ParamNameNum)
          End;

       If ParamCount = ParamNameNum Then
          Begin
            OldName:=ChangeFileExt(ParamStr(ParamNameNum),'.bak');
            NewName:=ParamStr(ParamNameNum);
            SysUtils.DeleteFile(OldName);
            RenameFile(NewName,OldName);
          End
       Else
          Begin
            OldName:=ParamStr(ParamNameNum);
            NewName:=ParamStr(ParamNameNum+1)
          End;

       Try
          nProcs := StrToInt(ParamStr(1));
          If nProcs <= 0 Then
             Raise Exception.Create('Incorrect processors number')
       Except
          WriteLn('Error in parameters: incorrect number of processors');
          Halt(-1)
       End;

       Assign(Inp,OldName);
       Try
          Reset(Inp);
       Except
          WriteLn('Can''t open input file ', OldName, ' for reading');
          Halt(-1)
       End;
       If FileExists(NewName) Then
          Begin
            S := ChangeFileExt(NewName, '.bak');
            SysUtils.DeleteFile(S);
            RenameFile(NewName, S)
          End;
       Assign(Out,NewName);
       Try
          Rewrite(Out);
       Except
          WriteLn('Can''t open output file ', NewName, ' for writing');
          Halt(-1)
       End;

       LineDelimiter := '';

       L:=TAnalyser.Create(IdentSet,[Space,Tabulation]);
       L1:=TAnalyser.Create(IdentSet,[Space,Tabulation]);

       Lines := TStringList.Create;
       // Preprocessing
       CommentFlag := False;
       // Read file into Lines
       Files := TStringList.Create;
       F := 1;
       While Not Eof(Inp) Do
         Begin
           ReadLn(Inp,S);
           StripComments(S, CommentFlag);
           Lines.AddObject(S, TLine.Create(0, F));
           Inc(F)
         End;
       FL := TStringList.Create;
       FL.Assign(Lines);
       Files.AddObject(Asterisk+ParamStr(ParamNameNum), FL);

       CloseFile(Inp);

       SetLength(Restrictions, 0);
       Defines.AddObject('__MPI2REENT__', TObject(NewStr('1')));
       Defines.AddObject('__BUF_SIZE__', TObject(NewStr(BufSize)));
       PreprocStage(FollowDefs, Defines, Restrictions);

       If L.Error Then
          Begin
            WriteLn('Parse error',TLine(Lines.Objects[LCounter-2]).GetDescription);
            Halt(-1)
          End;

       If _IndexOf(Defines, idmpi_included) < 0 Then
          Begin
            WriteLn('There is no active #include"'+idmpi_h+'" in program',TLine(Lines.Objects[LCounter-2]).GetDescription);
            Halt(-1)
          End;

       // Restore primary lines from file (not from results of macromodules apply)
       CommentFlag := False;
       For F := 0 To Lines.Count-1 Do
          Begin
            S := TLine(Lines.Objects[F]).GetOriginalLine;
            StripComments(S, CommentFlag);
            Lines.Strings[F] := S
          End;

       Vars := TStringList.Create;

       Funcs := TStringList.Create;
       // Funcs.Sorted := True;

       Defs := TStringList.Create;

       LST := TStringList.Create;

       WriteLn(Out,'#define __NPROCS__ (', nProcs, ')');
       WriteLn(Out,'#define __MPI2REENT__');
       WriteLn(Out,'#define __BUF_SIZE__ ', BufSize);
       WriteLn(Out,'#include <stdlib.h>');
       WriteLn(Out,'#include <vector>');
       WriteLn(Out,'#include <iostream>');
       WriteLn(Out,'using namespace std;');
       WriteLn(Out,'vector<plan_thread_t> __ids__(__NPROCS__);');
       If DebugThreads Then
          Begin
            WriteLn(Out,'vector<char *> __fcalls__[__NPROCS__];');
            WriteLn(Out,'volatile char __stopped__ = 0;')
          End;
       WriteLn(Out,'int __get_id(plan_thread_t tid, const char * Fun) {');
       WriteLn(Out,'  for (int i = 0; i < __NPROCS__; i++)');
       WriteLn(Out,'      if (CompareTID(__ids__[i], tid))');
       WriteLn(Out,'         return i;');
       If DebugThreads Then
          WriteLn(Out,'  __stopped__ = 1;');
       WriteLn(Out,'  plan_critical(err_tid_out) {');
       WriteLn(Out,'    cout<<"Error: Unknown thread in function "<<Fun<<". Probably you have used omp parallel clause or have created thread in any other manner."<<endl;');
       If DebugThreads Then
          Begin
            WriteLn(Out,'    for (int __id__ = 0; __id__ < __NPROCS__; __id__++) {');
            WriteLn(Out,'        cout<<"Stack["<<__id__<<"] = ";');
            WriteLn(Out,'        for (int i = 0; i < __fcalls__[__id__].size(); i++)');
            WriteLn(Out,'            cout<<__fcalls__[__id__][i]<<" ";');
            WriteLn(Out,'        cout<<endl;');
            WriteLn(Out,'    }')
          End;
       WriteLn(Out,'  }');
       WriteLn(Out,'  exit(-1);');
       WriteLn(Out,'  return -1;');
       WriteLn(Out,'}');
       WriteLn(Out);
       CommentFlag := False;
       LCounter:=1;
       While Not ((LCounter > Lines.Count) Or L.Error) Do
         Begin
           // Bypass restricted lines (if presents)
           If TLine(Lines.Objects[LCounter-1]).Restricted Then
              Begin
                Inc(LCounter);
                Continue
              End;
           S := Lines.Strings[LCounter-1];
           StripComments(S, CommentFlag);

           If Length(Trim(S)) = 0 Then
              Begin
                WriteLn(Out);
                Inc(LCounter);
                Continue
              End;

           L.AnlzLine := S;

           If L.IsNext(Pound) Then
              Begin
                L.Check(Pound);
                If L.IsNextIdent(idinclude, True) Then
                   Begin
                     L.CheckIdent(idinclude, True);
                     Flag := L.IsNext(DblQuote);
                     L.CheckSet([Less, DblQuote]);
                     S1 := L.GetBefore(True, [Greater, DblQuote]);
                     L.CheckSet([Greater, DblQuote]);
                     If S1 = idmpi_h Then
                        If Flag Then
                           Begin
                             S := '';
                             L.AnlzLine := S
                           End
                        Else
                           Begin
                             WriteLn('Error: '+S1+' in include must be enclosed in double quotes',TLine(Lines.Objects[LCounter-1]).GetDescription);
                             Halt(-1)
                           End
                   End
                Else If L.IsNextIdent(iddefine, True) Then
                   Begin
                     L.CheckIdent(iddefine, True);
                     While (Not L.Empty) And (L.AnlzLine[Length(L.AnlzLine)] = BackSlash) Do
                       Begin
                         WriteLn(Out, S);
                         Inc(LCounter);
                         If LCounter > Lines.Count Then
                            Begin
                              WriteLn('#define macro without end', TLine(Lines.Objects[LCounter-2]).GetDescription);
                              Halt(-1)
                            End;
                         S := Lines.Strings[LCounter-1];
                         StripComments(S, CommentFlag);
                         L. AnlzLine := S
                       End
                   End
              End
           Else
              Begin
                S1 := L.FindIdent(True);
                If (S1 = idclass) Or (S1 = idstruct) Or (S1 = idunion) Or (S1 = idenum) Then
                   Begin
                     // Тип или переменная
                     ID := L.GetIdent(False);
                     Prefix := L.GetBalancedListItem(False,[LeftFBracket, Equal, Comma, SemiColon], @GetLineFromLines);
                     If L.IsNext(LeftFBracket) Then
                        Begin
                          If S1 = idenum Then
                             GetFBlock(L, [Comma], LST)
                          Else
                             GetFBlock(L, [SemiColon], LST);
                          Prefix := Prefix + ' ' + LeftFBracket + CRLF + LST.Text + RightFBracket + ' ' +
                                    L.GetBalancedListItem(False,[Equal, Comma, SemiColon], @GetLineFromLines)
                        End;
                     Before := '';
                     After := '';
                     V := Trim(ExtractLastID(Prefix, Before, After));
                     Prefix := Before;
                     L.AnlzLine := V + After + L.AnlzLine;
                     If L.IsNext(SemiColon) Then // Тип
                        S := ID + ' ' + Prefix + L.AnlzLine
                     Else
                       Begin
                         S := AnalyzeVars(Vars, Defs, L, ID + ' ' + Prefix);
                         S := S + L.AnlzLine
                       End
                   End
                Else If S1 = idtypedef Then
                   S := L.GetBalancedListItem(False, [SemiColon], @GetLineFromLines) + L.AnlzLine
                Else If S1 = idextern Then
                   S := HandleExtern(L.AnlzLine)
                Else If (S1 = idtemplate) Or // Шаблон или Пространство имен
                        (S1 = idnamespace) Or
                        (S1 = idusing) Or
                        (S1 = idexport) Or
                        (S1 = idconst) Then
                   Begin
                     ID := L.GetIdent(False);
                     Prefix := L.GetBalancedListItem(False,[LeftFBracket, SemiColon], @GetLineFromLines);
                     If L.IsNext(LeftFBracket) Then
                        Begin
                          WriteLn('Warning: '+ID+' definitions are bypassed',TLine(Lines.Objects[LCounter-1]).GetDescription);
                          GetFBlock(L, [SemiColon], LST);
                          Body := LeftFBracket + CRLF + LST.Text + RightFBracket
                        End
                     Else
                        Begin
                          L.Check(SemiColon);
                          Body := SemiColon
                        End;
                     S := ID + ' ' + Prefix + ' ' + Body + L.AnlzLine
                   End
                Else // Переменная или функция
                   Begin
                     Tp := '';
                     V := '';
                     Prms := '';
                     Body := '';
                     After := '';
                     Kind := knNone;
                     Repeat
                       S1 := L.GetBalancedListItem(False,[LeftBracket, Equal, Comma, SemiColon], @GetLineFromLines);
                       S2 := '';
                       If L.Empty And GetLineFromLines(S2) Then
                          L.AnlzLine := S2;
                       If L.IsNext(LeftBracket) Then
                          Begin
                            L.Check(LeftBracket);
                            Prms := L.GetBalancedListItem(True, [RightBracket], @GetLineFromLines);
                            S2 := '';
                            If L.Empty And GetLineFromLines(S2) Then
                               L.AnlzLine := S2;
                            If L.IsNext(SemiColon) Then // Декларация функции
                               Begin
                                 L.Check(SemiColon);
                                 V := ExtractLastID(S1, Before, After);
                                 Tp := Tp + ' ' + Before;
                                 Kind := knDeclaration
                               End
                            Else If L.IsNext(LeftFBracket) Then // Функция
                               Begin
                                 GetFBlock(L, [SemiColon], LST);
                                 V := ExtractLastID(S1, Before, After);
                                 Tp := Tp + ' ' + Before;
                                 If V = idmain Then
                                    Begin
                                      V := '_' + V;
                                      Prms := 'int argc, char ** argv';
                                      Tp := 'chain ';
                                      With LST Do
                                        For G := 0 To Count-1 Do
                                           Begin
                                             S1 := Substitute(Strings[G], '', '', 'return', '%$%');
                                             Repeat
                                               K := Pos('%$%', S1);
                                               If K > 0 Then
                                                  Begin
                                                    L1.AnlzLine := Copy(S1, K + Length('%$%'), Length(S1));
                                                    S2 := L1.GetBalancedListItem(False, [SemiColon]);
                                                    S1 := Copy(S1, 1, K - 1) + S2 + SemiColon +
                                                          'return' + L1.AnlzLine
                                                  End
                                             Until K = 0;
                                             Strings[G] := S1
                                           End;
                                      LST.Insert(0, 'int __id__ = throw_stage();');
                                      LST.Insert(1, 'plan_critical(gettid) {');
                                      LST.Insert(2, '  __ids__[__id__] = GetTID();');
                                      LST.Insert(3, '};');
                                      LST.Insert(4, 'plan_registered_barrier(topology);');
                                      K := 5;
                                      If DebugThreads Then
                                         Begin
                                           LST.Insert(K, 'while(__stopped__); __fcalls__[__id__].push_back("main");');
                                           Inc(K)
                                         End;
                                      Flag := False;
                                      With Vars Do
                                        For F := 0 To Count-1 Do
                                          If Assigned(Objects[F]) And (Length(PString(Objects[F])^) > 0) Then
                                             Begin
                                               Flag := True;
                                               Break
                                             End;
                                      If Flag Then
                                         With Vars Do
                                           For F := 0 To Count-1 Do
                                             If Assigned(Objects[F]) And (Length(PString(Objects[F])^) > 0) Then
                                                Begin
                                                  S := PString(Objects[F])^;
                                                  C := S[1];
                                                  If C = SpecSymbol Then
                                                     System.Delete(S, 1, 1);
                                                  If S[1] = Pound Then
                                                     Begin
                                                       LST.Insert(K, Copy(S, 2, Length(S)));
                                                       S := 'init__' + Strings[F] + '__';
                                                       Inc(K)
                                                     End;
                                                  If C = SpecSymbol Then
                                                     LST.Insert(K, 'memmove(&__'+Strings[F]+'__[__id__],&'+S+',sizeof('+S+'));')
                                                  Else
                                                     LST.Insert(K, '     __'+Strings[F]+'__[__id__] = '+S+';');
                                                  Inc(K)
                                                End
                                    End;
                                 F := _IndexOf(Funcs, V);
                                 If F < 0 Then
                                    K := Funcs.Add(V);
                                 Body := HandleExtern(LST.Text);
                                 If DebugThreads Then
                                    Body := HandleReturns(Body);
                                 If F < 0 Then
                                    Funcs.Delete(K);
                                 Kind := knFunction
                               End
                            Else
                               Tp := Tp + ' ' + S1 + LeftBracket + Prms + RightBracket + ' '
                          End
                       Else
                          Begin
                            // Переменная
                            V := ExtractLastID(S1, Before, After);
                            Tp := Tp + ' ' + Before;
                            L.AnlzLine := V + After + L.AnlzLine;
                            S := AnalyzeVars(Vars, Defs, L, Tp);
                            Kind := knVar
                          End
                     Until (Kind <> knNone) Or L.Error Or L.Empty;
                     Tp := Trim(Tp);
                     If (Kind = knFunction) Or (Kind = knDeclaration) Then
                        Begin
                          Prms := Trim(Prms);
                          S := '';
                          ParamNames := Nil;
                          If V <> _idmain Then
                             Begin
                               ParamNames := HandleParams(L1, Prms);
                               If _IndexOf(Funcs, V) < 0 Then
                                  Funcs.Add(V);
                               With ParamNames Do
                                 For G := 0 To Count-1 Do
                                    Begin
                                      K := _IndexOf(Defs, Strings[G]);
                                      If K >= 0 Then
                                         S := S + '#undef ' + Strings[G] + CRLF
                                    End
                             End;
                          If Kind = knFunction Then
                             Begin
                               If V <> _idmain Then
                                  Begin
                                    Globs := TStringList.Create;
                                    Globs.Assign(Vars);
                                    If Assigned(ParamNames) Then
                                       For G := 0 To ParamNames.Count - 1 Do
                                         Begin
                                           K := _IndexOf(Globs, ParamNames.Strings[G]);
                                           If K >= 0 Then
                                              Globs.Delete(K)
                                         End;
                                    If DebugThreads Then
                                       Body := 'while(__stopped__); __fcalls__[__id__].push_back("'+V+'");' + CRLF + Body;
                                    If _IndexOf(ParamNames, '__id__') < 0 Then // Если нет явного параметра __id__
                                       If DebugThreads Or UseID(Body) Then
                                          Body := 'int __id__ = __get_id(GetTID(),"'+V+'");' + CRLF + Body;
                                    Globs.Free
                                  End;
                               S := S + Tp + ' ' + V + LeftBracket + Prms + RightBracket +
                                    ' ' + LeftFBracket + CRLF +
                                          Body +
                                          RightFBracket + CRLF
                             End
                          Else
                             S := S + Tp + ' ' + V + LeftBracket + Prms + RightBracket + SemiColon +CRLF;
                          If Assigned(ParamNames) Then
                             With ParamNames Do
                               Begin
                                 For G := 0 To Count-1 Do
                                    Begin
                                      K := _IndexOf(Defs, Strings[G]);
                                      If K >= 0 Then
                                         S := S + PString(Defs.Objects[K])^
                                    End;
                                 Free
                               End
                        End
                   End
              End;
           WriteLn(Out, S);
           Inc(LCounter)
         End;
       If L.Error Then
          Begin
            WriteLn('Parse error',TLine(Lines.Objects[LCounter-2]).GetDescription);
            Halt(-1)
          End;

       WriteLn(Out);
       WriteLn(Out,'int main(int argc, char ** argv) {');
       WriteLn(Out,'  plan_parallel_chain(1, __NPROCS__, _main(argc, argv));');
       WriteLn(Out,'  return 0;');
       WriteLn(Out,'}');

       SetLength(Restrictions, 0);

       With Vars Do
         Begin
           WriteLn('--- Global Vars ---');
           For F := 0 To Count-1 Do
               Begin
                 Write(Strings[F]);
                 If Assigned(Objects[F]) And (Length(PString(Objects[F])^) > 0) Then
                    WriteLn(' = ', PString(Objects[F])^)
                 Else
                    WriteLn;
                 DisposeStr(PString(Objects[F]))
               End;
           WriteLn('-------------------');
           Free
         End;

       Funcs.Free;

       With Defs Do
         Begin
           For F := 0 To Count - 1 Do
               DisposeStr(PString(Objects[F]));
           Free
         End;

       LST.Free;

       L.Free;
       L1.Free;
       With Lines Do
         Begin
           For F := 0 To Count - 1 Do
               If Assigned(Objects[F]) Then
                  Objects[F].Free;
           Free
         End;
       With Files Do
         Begin
           For F := 0 To Count - 1 Do
               If Assigned(Objects[F]) Then
                  Objects[F].Free;
           Free
         End;
       With Defines Do
         Begin
           For F := 0 To Count - 1 Do
               DisposeStr(PString(Objects[F]));
           Free
         End;

       Close(Out)
     End
end.

