unit XPathing;

{$IFDEF FPC}
{$MODE Delphi}
{$ENDIF}

{$CODEPAGE UTF8}

{$OPTIMIZATION OFF}

interface

uses
  Common, Classes, SysUtils, xpath, dom, xmlread, xmlwrite, Process;

Type CreateSysFun = function:Pointer; cdecl;
     ExistClassFun = function(Const ClsID: PChar):Boolean; cdecl;
     GetElementFun = function(Sys: Pointer; ID: PChar):Pointer; cdecl;
     CanReachFun = function(Sys: Pointer; _From: Pointer; nTo: Integer; _To: PPointerList): Boolean; cdecl;
     CreateContactsFun = procedure(ClassID: PChar; _Dir: Integer; dom: Pointer; Parent: Pointer; Tag: PChar); cdecl;
     AddElementFun = function(Sys: Pointer; ClassName, ID : PChar; Flags: Integer):Pointer; cdecl;
     AddLinkFun = function(Sys, El: Pointer; ContID: PChar; PEl: Pointer; PContID: PChar; Var S: PChar; Info: Boolean):Pointer; cdecl;
     AnalyzeLinkStatusIsInformFun = function(sys, L: Pointer): Boolean; cdecl;
     SetParameterIfExistsFun = procedure(el: Pointer; PrmName, PrmValue: PChar); cdecl;
     MoveFun = procedure(el: Pointer; X, Y: Integer); cdecl;
     CheckSysFun = function(Sys: Pointer): Integer; cdecl;
     ToStringFun = procedure(Sys: Pointer; Ret: PChar); cdecl;
     GenerateCodeFun = procedure(Sys: Pointer; Ret: PChar); cdecl;
     SaveToXMLFun = procedure(Sys: Pointer; FName: PChar); cdecl;
     _FreeFun = procedure(Obj: Pointer); cdecl;

function XPathInduct(
   _Messaging: Boolean;
   CreateSysF: CreateSysFun;
   ExistClassF: ExistClassFun;
   GetElementF: GetElementFun;
   CanReachF: CanReachFun;
   CreateContactsF: CreateContactsFun;
   AddElementF: AddElementFun;
   AddLinkF: AddLinkFun;
   AnalyzeLinkStatusIsInformF: AnalyzeLinkStatusIsInformFun;
   SetParameterIfExistsF: SetParameterIfExistsFun;
   MoveF: MoveFun;
   CheckSysF: CheckSysFun;
   ToStringF: ToStringFun;
   GenerateCodeF: GenerateCodeFun;
   SaveToXMLF: SaveToXMLFun;
   _FreeF: _FreeFun;
   NodeNameTesterF: TXPathNodeNameTester;
   SelectedMode: PChar;
   UseNNet: Boolean; MainLineAllowed: Boolean;
   _ENV: Pointer;
   inENV, outENV: PChar;
   InXML, OutXML: PChar;
   MaxCPUs: Integer;
   _IDs: PChar;
   OnlyInduceModel: Boolean): Boolean; cdecl;

function CompileXPathing(_Messaging: Boolean;
   _AllowedVersions: PChar;
   FName: PChar; _ENV: Pointer; inENV, outENV: PChar;
   _WorkText: PChar): Boolean; cdecl;
procedure SetInterval(_Interval: Cardinal); cdecl;
procedure ClearRestrictions; cdecl;
procedure ClearRuler; cdecl;
procedure SetDeduceLogFile(LF: PChar); cdecl;
procedure CreateDOMContact(dom: Pointer; Parent: Pointer; Tag: PChar; CntID: PChar); cdecl;

implementation

Uses {$IF DEFINED(UNIX) OR DEFINED(LINUX)}cthreads{$ELSE}Windows{$ENDIF}, Math, Lexique, RegExpr,
     DateUtils, uSemaphore, AutoConsts
     {$IF DEFINED(VCL) OR DEFINED(LCL)}, Forms{$ENDIF};

Var Interval: Cardinal;
    DeduceLogFile: String;

Var CreateSys: CreateSysFun;
    ExistClass: ExistClassFun;
    GetElement: GetElementFun;
    CanReach: CanReachFun;
    CreateContacts: CreateContactsFun;
    AddElement: AddElementFun;
    AddLink: AddLinkFun;
    AnalyzeLinkStatusIsInform: AnalyzeLinkStatusIsInformFun;
    SetParameterIfExists: SetParameterIfExistsFun;
    Move: MoveFun;
    CheckSys: CheckSysFun;
    ToString: ToStringFun;
    GenerateCode: GenerateCodeFun;
    SaveToXML: SaveToXMLFun;
    _Free: _FreeFun;
    NodeNameTester: TXPathNodeNameTester;
    IDs: IDArray;

Const NumThreads: Integer = 8;

Var NumThrSemaphore: TSemaphore = Nil;

Var VariantsCS: TRTLCriticalSection;
    NActiveThreads: Integer = 0;

Var Start: TDateTime;

Var _Restrictions: TObjList;
    Ruler: TStringList;

Type VectorType = Array Of Real;
     MatrixType = Array Of VectorType;
     PMatrixType = ^MatrixType;

Type TTrace = Array Of Integer;
     PTrace = ^TTrace;

Type TWeakResult = Array Of TXMLDocument;

Type
     { TWeakRestriction }

     TWeakRestriction = class
        Expr: DOMString;
        Sign: Char;

        AprP: Real;

        Constructor Create(Const _Expr: DOMString; _Sign: Char; _AprP: Real);

        Function  CopyDOMWithout(dom: TXMLDocument; without: TList): TXMLDocument;
        Procedure DOMWithout(dom: TXMLDocument; without: TList; Del: Boolean);
        Procedure CompleteObjs(dom: TXMLDocument; objs: TNodeSet);
        Function  CheckSign(R: TResultType): TResultType;

        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; virtual; abstract;
        Function Construct(ENV: TXPathEnvironment; Var dom: TXMLDocument): TWeakResult; virtual;
     End;

     { TWeakStatement }

     TWeakStatement = class(TWeakRestriction)
        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; override;
        Function Construct(ENV: TXPathEnvironment; Var dom: TXMLDocument): TWeakResult; override;
     End;

     { TWeakLink }

     TWeakLink = class(TWeakRestriction)
        Expr2: DOMString;
        Ruler: TStringList;

        Constructor Create(Const _Expr, _Expr2: DOMString; _Sign: Char; _AprP: Real; _Ruler: TStringList);

        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; override;
        Function Construct(ENV: TXPathEnvironment; Var dom: TXMLDocument): TWeakResult; override;
     private
       function PresentsBetween(n1, n2: Integer; const BaseClass: String
         ): Boolean;
     End;

     { TWeakOrder }

     TWeakOrder = class(TWeakRestriction)
        Expr2: DOMString;

        Constructor Create(Const _Expr, _Expr2: DOMString; _Sign: Char; _AprP: Real);

        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; override;
     End;

     TWeakOperator = (woEqual, woNonEqual, woLess, woGreater, woLessEqual, woGreaterEqual);

     { TWeakRelation }

     TWeakRelation = class(TWeakRestriction)
        Expr2: DOMString;
        Op: TWeakOperator;

        Constructor Create(Const _Expr, _Expr2: DOMString; _Sign: Char; _Op: TWeakOperator; _AprP: Real);

        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; override;
     End;

     { TWeakTest }
     TWeakTest = class(TWeakRestriction)
        InAttr, OutAttr: DOMString;
        NoSpaces: Boolean;

        Constructor Create(Const _Expr, _InAttr, _OutAttr: DOMString; _NoSpaces: Boolean; _Sign: Char);

        Function Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType; override;

        Function Test(ENV: TXPathEnvironment; dom: TXMLDocument; sys: Pointer; Var Compiled: Boolean; Const Lang: String): Boolean;
     end;

{ TStat }

 TStat = class
        lSeq: TList;
        lWords: TStringList;
        lRels: TStringList;
        INP: TStringList;
        R: Real;
        OUT0, OUT1: MatrixType;
        Trace: TTrace;
        Time: Real;

        Constructor Create(lS, lW, lR: TStringList; Const P0, P1: MatrixType; T: Real; lT: TTrace);
        Destructor Destroy;
     End;

Var Probabilities: MatrixType;
    Variants: TStringList;
    Words: TStringList;
    Stat: TObjList;

Var MetaResult: Pointer = Nil;
    MetaTrace: TTrace;

constructor TWeakTest.Create(const _Expr, _InAttr, _OutAttr: DOMString; _NoSpaces: Boolean; _Sign: Char);
begin
     Inherited Create(_Expr, _Sign, 1.0);
     InAttr := _InAttr;
     OutAttr := _OutAttr;
     NoSpaces := _NoSpaces
end;

function TWeakTest.Check(ENV: TXPathEnvironment; dom: TXMLDocument; const sys: Pointer): TResultType;
begin
     Result := rsOk
end;

function TWeakTest.Test(ENV: TXPathEnvironment; dom: TXMLDocument; sys: Pointer; var Compiled: Boolean;
  const Lang: String): Boolean;

  function DelSpaces(Const S: WideString): WideString;

  Var F: Integer;
  Begin
       Result := S;
       If NoSpaces Then
          Begin
             F := 1;
             While F <= Length(Result) Do
               If Not (Result[F] in [Space, Tabulation, #$0D, #$0A, #$00]) Then
                  Inc(F)
               Else
                  System.Delete(Result, F, 1)
          End
  End;

Var res: TXPathVariable;
    txt: String;
    inp, outp: String;
    L: TextFile;
    LL: TStringList;
    F: Integer;
    Err: Integer;
begin
   Result := Sign = '+';

   res := EvaluateXPathExpression(Expr, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
   ENV.commitUndo(0);

   If res is TXPathNodeSetVariable Then
      For F := 0 To res.AsNodeSet.Count - 1 Do
        If TObject(res.AsNodeSet[F]) is TDOMElement Then
          Begin
            inp := TDOMElement(res.AsNodeSet[F]).AttribStrings[InAttr];
            outp := TDOMElement(res.AsNodeSet[F]).AttribStrings[OutAttr];

            AssignFile(L, '_.in');
            Rewrite(L);
            Write(L, inp);
            CloseFile(L);
            // AssignFile(L, '_.out');
            // Rewrite(L);
            // CloseFile(L);

            If Compiled Then
               RunExtCommandAsAdmin({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'bash ./start_'+Lang+'.sh'{$ELSE}'start_'+Lang+'.bat'{$ENDIF},'nocompile _.xout _.in','_.xout','$##$!','_.result')
            Else
               Begin
                 RunExtCommandAsAdmin({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'bash ./start_'+Lang+'.sh'{$ELSE}'start_'+Lang+'.bat'{$ENDIF},'_.' + Lang + ' _.xout _.in','_.xout','$##$!','_.result');
                 Compiled := True
               End;

            AssignFile(L, '_.result');
            Reset(L);
            ReadLn(L, Err);
            CloseFile(L);
            If Err <> 0 Then
               Begin
                 res.Free;
                 Exit(Sign = '-')
               End;

            LL := TStringList.Create;
            Try
               LL.LoadFromFile('_.xout');
               txt := LL.Text;
            Except
               txt := '';
            end;
            LL.Free;

            // Check Result
            outp := DelSpaces(outp);
            txt := DelSpaces(txt);
            If outp <> txt Then
               Begin
                 res.Free;
                 Exit(Sign = '-')
               End;
          End;

   res.Free
end;

{ TWeakRelation }

constructor TWeakRelation.Create(const _Expr, _Expr2: DOMString; _Sign: Char; _Op: TWeakOperator; _AprP: Real);
begin
   Inherited Create(_Expr, _Sign, _AprP);
   Expr2 := _Expr2;
   Op := _Op
end;

function TWeakRelation.Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType;

Var res1, res2: TXPathVariable;
begin
   res1 := EvaluateXPathExpression(Expr, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
   ENV.commitUndo(0);
   res2 := EvaluateXPathExpression(Expr2, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
   ENV.commitUndo(0);

   Result := rsStrict;

   If res1 is TXPathNodeSetVariable Then
      If res2 is TXPathNumberVariable Then
         Case Op Of
           woEqual: If res1.AsNodeSet.Count = res2.AsNumber Then Result := rsOk
                    Else If res1.AsNodeSet.Count < res2.AsNumber Then Result := rsNonStrict;
           woNonEqual: If res1.AsNodeSet.Count <> res2.AsNumber Then Result := rsOk;
           woLess: If res1.AsNodeSet.Count < res2.AsNumber Then Result := rsOk;
           woLessEqual: If res1.AsNodeSet.Count <= res2.AsNumber Then Result := rsOk;
           woGreater: If res1.AsNodeSet.Count > res2.AsNumber Then Result := rsOk
                      Else Result := rsNonStrict;
           woGreaterEqual: If res1.AsNodeSet.Count >= res2.AsNumber Then Result := rsOk
                           Else Result := rsNonStrict;
         End
      Else
         Result := rsStrict
   Else If res1 is TXPathNumberVariable Then
      If res2 is TXPathNumberVariable Then
         Case Op Of
           woEqual: If res1.AsNumber = res2.AsNumber Then Result := rsOk;
           woNonEqual: If res1.AsNumber <> res2.AsNumber Then Result := rsOk;
           woLess: If res1.AsNumber < res2.AsNumber Then Result := rsOk;
           woLessEqual: If res1.AsNumber <= res2.AsNumber Then Result := rsOk;
           woGreater: If res1.AsNumber > res2.AsNumber Then Result := rsOk;
           woGreaterEqual: If res1.AsNumber >= res2.AsNumber Then Result := rsOk;
         End
      Else
         Result := rsStrict
  Else If res1 is TXPathStringVariable Then
     If res2 is TXPathStringVariable Then
        Case Op Of
          woEqual: If res1.AsText = res2.AsText Then Result := rsOk;
          woNonEqual: If res1.AsText <> res2.AsText Then Result := rsOk;
          woLess: If res1.AsText < res2.AsText Then Result := rsOk;
          woLessEqual: If res1.AsText <= res2.AsText Then Result := rsOk;
          woGreater: If res1.AsText > res2.AsText Then Result := rsOk;
          woGreaterEqual: If res1.AsText >= res2.AsText Then Result := rsOk;
        End
     Else
        Result := rsStrict;
   Result := CheckSign(Result)
end;

{ TWeakOrder }

constructor TWeakOrder.Create(const _Expr, _Expr2: DOMString; _Sign: Char; _AprP: Real);
begin
   Inherited Create(_Expr, _Sign, _AprP);
   Expr2 := _Expr2
end;

function TWeakOrder.Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType;

  Function XPath2Objs(Const XPath: DOMString): TList;

  Var res: TXPathVariable;
      S: Pointer;
      F: Integer;
  Begin
       Result := TList.Create;

       res := EvaluateXPathExpression(XPath, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
       ENV.commitUndo(0);
       If res is TXPathNodeSetVariable Then
          Begin
            For F := 0 To res.AsNodeSet.Count - 1 Do
                With TObject(res.AsNodeSet.Items[F]) As TDOMElement Do
                  Begin
                    S := GetElement(sys, PChar(String(AttribStrings['ID'])));

                    If Assigned(S) Then
                       Result.Add(S)
                    Else
                       Begin
                         FreeAndNil(Result);
                         res.Free;
                         Exit
                       End
                  End
          End;
       res.Free
  End;

Var set1, set2: TList;
    F: Integer;
begin
     Result := CheckSign(rsStrict);

     set1 := XPath2Objs(Expr);
     If Not Assigned(set1) Then Exit;
     set2 := XPath2Objs(Expr2);
     If Not Assigned(set2) Then
        Begin
          set1.Free;
          Exit
        end;
     Try
       Result := CheckSign(rsOk);
       For F := 0 To set1.Count - 1 Do
           If Not CanReach(sys, set1[F], set2.Count, set2.List) Then
              Begin
                Result := CheckSign(rsNonStrict);
                Break
              end;
       For F := 0 To set2.Count - 1 Do
           If CanReach(sys, set2[F], set1.Count, set1.List) Then
              Exit(CheckSign(rsStrict));
     Finally
       set1.Free;
       set2.Free
     end;
end;

{ TWeakRestriction }

constructor TWeakRestriction.Create(const _Expr: DOMString; _Sign: Char; _AprP: Real);
Begin
     Inherited Create;
     Expr := _Expr;
     Sign := _Sign;
     AprP := _AprP
End;

function TWeakRestriction.CopyDOMWithout(dom: TXMLDocument; without: TList
  ): TXMLDocument;

Var doctypenode: TDOMNode;
    Owner: TDOMDocument;

  function process(el: TDOMNode): TDOMNode;

  Var F: Integer;
  Begin
       If Not Assigned(Owner) Then
          Begin
            Result := el.CloneNode(False);
            Owner := Result As TDOMDocument
          End
       Else
          Result := el.CloneNode(False, Owner);
       With el.ChildNodes Do
         begin
           For F := 0 To Count - 1 Do
             If without.IndexOf(Item[F]) < 0 Then
               If Item[F] <> doctypenode Then
                 Result.AppendChild(process(Item[F]));
           Free
         end;
  End;

begin
     doctypenode := dom.DocType;
     Owner := Nil;
     Result := process(dom) As TXMLDocument
end;

procedure TWeakRestriction.DOMWithout(dom: TXMLDocument; without: TList; Del: Boolean);

  procedure process(el: TDOMNode);

  Var F: Integer;
      p: TDOMNode;
  Begin
       With el.ChildNodes Do
         begin
           For F := 0 To Count-1 Do
             If without.IndexOf(Item[F]) >= 0 Then
                Begin
                  p := Item[F];
                  el.RemoveChild(p);
                  If Del Then
                     p.Free;
                end
             Else
                process(Item[F]);
           Free
         end;
  End;

begin
   process(dom)
end;

procedure TWeakRestriction.CompleteObjs(dom: TXMLDocument; objs: TNodeSet);

Var F: Integer;
begin
   For F := 0 To objs.Count - 1 Do
       If Assigned(TDOMNode(objs[F]).ParentNode) And
          (TDOMElement(TDOMNode(objs[F]).ParentNode).TagName = 'OBJS') And
          ExistClass(PChar(String(TDOMElement(objs[F]).TagName))) Then
          With TDOMElement(objs[F]) Do
            Begin
              CreateContacts(PChar(String(TagName)), Integer(dirInput), dom, TDOMElement(objs[F]), 'I');
              CreateContacts(PChar(String(TagName)), Integer(dirOutput), dom, TDOMElement(objs[F]), 'O');
            End
end;

function TWeakRestriction.CheckSign(R: TResultType): TResultType;
begin
     If Sign = '+' Then
        Result := R
     Else If R = rsOk Then
        Result := rsStrict
     Else
        Result := rsOk
end;

function TWeakRestriction.Construct(ENV: TXPathEnvironment; var dom: TXMLDocument): TWeakResult;
Begin
   SetLength(Result, 0)
end;

{ TWeakStatement }

function TWeakStatement.Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType;

Var res: TXPathVariable;
begin
   res := EvaluateXPathExpression(Expr, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
   ENV.commitUndo(0);
   If res is TXPathNodeSetVariable Then
      If res.AsNodeSet.Count > 0 Then
          Result := CheckSign(rsOk)
      Else
          Result := CheckSign(rsNonStrict)
   Else If ((res is TXPathNumberVariable) And (res.AsNumber > 0)) Or
            ((res is TXPathBooleanVariable) And (res.AsBoolean)) Or
            ((res is TXPathStringVariable) And (Length(res.AsText) > 0)) Then
      Result := CheckSign(rsOk)
   Else
      Result := CheckSign(rsStrict)
end;

function TWeakStatement.Construct(ENV: TXPathEnvironment; Var dom: TXMLDocument): TWeakResult;

Var res: TXPathVariable;
    d: TXMLDocument;
    root: TDOMElement;
    new_objs: TList;
    obj: TDOMElement;
    C: TNodeSet;
    F, G: Integer;
begin
   Result := Inherited Construct(ENV, dom);

   If Assigned(dom) Then
      Begin
         C := TNodeSet.Create;
         d := dom.CloneNode(True) As TXMLDocument;

         res := EvaluateXPathExpression(Expr, d.DocumentElement, NodeNameTester, [], C, Nil, ENV);
         ENV.commitUndo(0);
         CompleteObjs(d, C);
         If ((res is TXPathNumberVariable) And (res.AsNumber > 0)) Or
            ((res is TXPathBooleanVariable) And (res.AsBoolean)) Or
            ((res is TXPathStringVariable) And (Length(res.AsText) > 0)) Or
            ((res is TXPathNodeSetVariable) And (res.AsNodeSet.Count > 0)) Then
            If C.Count > 0 then
               Begin
                 new_objs := TList.Create;
                 root := d.DocumentElement;
                 With root.ChildNodes Do
                   begin
                     For F := 0 To Count - 1 Do
                         If (Copy(TDOMElement(Item[F]).TagName, 1, 3) = 'cls') And
                            ExistClass(PChar(String(TDOMElement(Item[F]).TagName))) And
                            (C.IndexOf(Item[F]) >= 0) Then
                            new_objs.Add(Item[F]);
                     Free
                   end;
                 If new_objs.Count = 0 Then
                    Begin
                      SetLength(Result, 1);
                      Result[0] := d.CloneNode(True) As TXMLDocument
                    End
                 Else
                    Begin
                      SetLength(Result, new_objs.Count);
                      For F := 0 To new_objs.Count - 1 Do
                          Begin
                            obj := TObject(new_objs[F]) As TDOMElement;
                            new_objs.Delete(F);
                            Result[F] := CopyDOMWithout(d, new_objs);
                            new_objs.Insert(F, obj)
                          End
                    End;
                 new_objs.Free
               End;

         res.Free;
         d.Free;
         C.Free
      End
end;

{ TWeakLink }

constructor TWeakLink.Create(const _Expr, _Expr2: DOMString; _Sign: Char; _AprP: Real; _Ruler: TStringList);
begin
     Inherited Create(_Expr, _Sign, _AprP);
     Expr2 := _Expr2;
     Ruler := _Ruler
end;

function TWeakLink.PresentsBetween(n1, n2: Integer; Const BaseClass: String): Boolean;
begin
   Result := False;
   While (n1 <= n2) And Not Result Do
     begin
       Result := NodeNameTester(PChar(PString(Ruler.Objects[n1])^), PChar(BaseClass));
       Inc(n1)
     end
end;

function TWeakLink.Check(ENV: TXPathEnvironment; dom: TXMLDocument; Const sys: Pointer = Nil): TResultType;

  function SubCheck(Const Expr1, Expr2: DOMString; Reverse: Boolean): TResultType;

  Var res1, res2: TXPathVariable;
      has: Integer;
      has_el: TDOMElement;
      obj1, obj2, cont2: TDOMElement;
      n1, n2: Integer;
      C: TNodeSet;
      objs: TList;
      F, G: Integer;
  Begin
     res2 := EvaluateXPathExpression(Expr2, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
     ENV.commitUndo(0);
     If (res2 is TXPathNodeSetVariable) And (res2.AsNodeSet.Count > 0) Then
        Begin
          Result := rsOk;
          C := TNodeSet.Create;
          objs := TList.Create;
          For F := 0 To res2.AsNodeSet.Count - 1 Do
              Begin
                cont2 := TDOMElement(res2.AsNodeSet[F]);
                obj2 := TDOMElement(cont2.ParentNode);
                While Assigned(obj2.ParentNode) And (TDOMElement(obj2.ParentNode).TagName <> 'OBJS') Do
                   obj2 := TDOMElement(obj2.ParentNode);
                C.Clear;
                res1 := EvaluateXPathExpression(Expr1, dom.DocumentElement, NodeNameTester, [obj2, cont2, dom.DocumentElement], C, Nil, ENV);
                ENV.commitUndo(0);
                objs.Clear;
                For G := 0 To C.Count - 1 Do // Up in DOM, for created items we ignore their created child's chain
                    If C.IndexOf(TDOMElement(C[G]).ParentNode) < 0 Then
                       objs.Add(C[G]);
                If res1 is TXPathNodeSetVariable Then
                   Begin
                      has := 0;
                      For G := 0 To res1.AsNodeSet.Count - 1 Do
                          If C.IndexOf(res1.AsNodeSet[G]) < 0 Then
                             Begin
                               has_el := TDOMElement(res1.AsNodeSet[G]);
                               Inc(has)
                             End;
                      If has > 1 Then
                        Begin
                          DOMWithout(dom, objs, True);
                          res1.Free;
                          res2.Free;
                          C.Free;
                          objs.Free;
                          Exit(CheckSign(rsStrict))
                        End
                      Else If res1.AsNodeSet.Count > 0 Then
                        Begin
                           If has = 0 Then
                              Result := rsNonStrict
                           Else
                             If Assigned(Ruler) then
                                Begin
                                  obj1 := TDOMElement(has_el);
                                  While Assigned(obj1.ParentNode) And (TDOMElement(obj1.ParentNode).TagName <> 'OBJS') Do
                                     obj1 := TDOMElement(obj1.ParentNode);
                                  n1 := Ruler.IndexOf(obj1.AttribStrings['ID']);
                                  n2 := Ruler.IndexOf(obj2.AttribStrings['ID']);
                                  If (n1 >= 0) And (n2 >= 0) Then
                                     If Reverse Then
                                        Begin
                                          If (n1 <= n2) Or PresentsBetween(n2+1, n1-1, obj1.TagName) Then
                                             Begin
                                               Result := rsStrict;
                                               Break
                                             End
                                        End
                                     Else
                                        If (n1 >= n2) Or PresentsBetween(n1+1, n2-1, obj1.TagName) Then
                                           Begin
                                             Result := rsStrict;
                                             Break
                                           End
                                  End
                        End
                   End
                Else
                   Begin
                     DOMWithout(dom, objs, True);
                     res1.Free;
                     res2.Free;
                     C.Free;
                     objs.Free;
                     Exit(CheckSign(rsStrict))
                   End;
                DOMWithout(dom, objs, True);
                res1.Free
              End;
          C.Free;
          objs.Free;
          res2.Free
        End
     Else
        Begin
          res2.Free;
          Exit(CheckSign(rsOk))
        End;
     Result := CheckSign(Result)
  End;

Var C1, C2: Boolean;
begin
   C1 := Pos('##', Expr) > 0;
   C2 := Pos('##', Expr2) > 0;
   If (C1 Xor C2) = False Then
      Exit(rsStrict);

   If C1 Then
      Result := SubCheck(Expr, Expr2, False)
   Else
      Result := SubCheck(Expr2, Expr, True)
end;

function TWeakLink.Construct(ENV: TXPathEnvironment; Var dom: TXMLDocument): TWeakResult;

  function SubConstruct(Const Expr1, Expr2: DOMString; Reverse: Boolean): TWeakResult;

  Var res1, res2: TXPathVariable;
      obj1, obj2, cont2: TDOMElement;
      C: TNodeSet;
      objs: TList;
      good: Boolean;
      n1, n2: Integer;
      has: Integer;
      F, G: Integer;
  Begin
     SetLength(Result, 0);

     res2 := EvaluateXPathExpression(Expr2, dom.DocumentElement, NodeNameTester, [], Nil, Nil, ENV);
     ENV.commitUndo(0);
     If (res2 is TXPathNodeSetVariable) And (res2.AsNodeSet.Count > 0) Then
        Begin
          C := TNodeSet.Create;
          objs := TList.Create;
          For F := 0 To res2.AsNodeSet.Count - 1 Do
              Begin
                cont2 := TDOMElement(res2.AsNodeSet[F]);
                obj2 := TDOMElement(cont2.ParentNode);
                While Assigned(obj2.ParentNode) And (TDOMElement(obj2.ParentNode).TagName <> 'OBJS') Do
                   obj2 := TDOMElement(obj2.ParentNode);

                C.Clear;
                objs.Clear;

                res1 := EvaluateXPathExpression(Expr1, dom.DocumentElement, NodeNameTester, [obj2, cont2, dom.DocumentElement], C, Nil, ENV);
                ENV.commitUndo(0);
                If (res1 is TXPathNodeSetVariable) And (C.Count > 0) Then
                   Begin
                      CompleteObjs(dom, C);
                      For G := 0 To C.Count - 1 Do // Up in DOM, for created items we ignore their created child's chain
                          If C.IndexOf(TDOMElement(C[G]).ParentNode) < 0 Then
                             begin
                               obj1 := TDOMElement(C[G]);
                               While Assigned(obj1.ParentNode) And (TDOMElement(obj1.ParentNode).TagName <> 'OBJS') Do
                                  obj1 := TDOMElement(obj1.ParentNode);
                               if (Copy(obj1.TagName, 1, 3) = 'cls') And ExistClass(PChar(String(obj1.TagName))) Then
                                  objs.Add(C[G])
                             end;
                      has := 0;
                      For G := 0 To res1.AsNodeSet.Count - 1 Do
                          If C.IndexOf(res1.AsNodeSet[G]) < 0 Then
                             Inc(has);
                      If (has = 0) And (res1.AsNodeSet.Count > 0) Then
                         For G := 0 To C.Count - 1 Do
                          If objs.IndexOf(C[G]) >= 0 Then
                           Begin
                             objs.Remove(C[G]);
                             good := Not Assigned(Ruler);
                             If Not good Then
                                Begin
                                  obj1 := TDOMElement(C[G]);
                                  While Assigned(obj1.ParentNode) And (TDOMElement(obj1.ParentNode).TagName <> 'OBJS') Do
                                     obj1 := TDOMElement(obj1.ParentNode);
                                  if (Copy(obj1.TagName, 1, 3) = 'cls') And ExistClass(PChar(String(obj1.TagName))) Then
                                     Begin
                                        n1 := Ruler.IndexOf(obj1.AttribStrings['ID']);
                                        n2 := Ruler.IndexOf(obj2.AttribStrings['ID']);
                                        good := True;
                                        If (n1 >= 0) And (n2 >= 0) Then
                                           If Reverse Then
                                              good := (n1 > n2) And Not PresentsBetween(n2+1, n1-1, obj1.TagName)
                                           Else
                                              good := (n1 < n2) And Not PresentsBetween(n1+1, n2-1, obj1.TagName)
                                     End
                                End;
                             If good Then
                                Begin
                                  SetLength(Result, Length(Result) + 1);
                                  Result[High(Result)] := CopyDOMWithout(dom, objs)
                                End;
                             objs.Add(C[G])
                           End;
                      DOMWithout(dom, objs, True)
                   End;
                res1.Free
              End;
          res2.Free;
          objs.Free;
          C.Free
        End
     Else
        Begin
          res2.Free;
          Exit
        End
  End;

Var C1, C2: Boolean;
begin
   Result := Inherited Construct(ENV, dom);

   If Assigned(dom) Then
      Begin
        C1 := Pos('##', Expr) > 0;
        C2 := Pos('##', Expr2) > 0;
        If (C1 Xor C2) = False Then
           Exit;

        If C1 Then
           Result := SubConstruct(Expr, Expr2, False)
        Else
           Result := SubConstruct(Expr2, Expr, True)
      End
end;

{ TStat }

constructor TStat.Create(lS, lW, lR: TStringList; const P0, P1: MatrixType; T: Real; lT: TTrace);

Var F, G: Integer;
begin
  lSeq := TList.Create;
  For F := 0 To lS.Count - 1 Do
      lSeq.Add(IntegerToTObject(StrToInt(lS[F])));
  lWords := TStringList.Create;
  lWords.Assign(lW);
  lRels := TStringList.Create;
  lRels.Assign(lR);
  INP := TStringList.Create;
  R := 0.0;
  SetLength(OUT0, _Restrictions.Count, _Restrictions.Count);
  For F := 0 To _Restrictions.Count - 1 Do
      For G := 0 To _Restrictions.Count - 1 Do
          OUT0[F, G] := P0[F, G];
  SetLength(OUT1, _Restrictions.Count, _Restrictions.Count);
  For F := 0 To _Restrictions.Count - 1 Do
      For G := 0 To _Restrictions.Count - 1 Do
          OUT1[F, G] := P1[F, G];
  SetLength(Trace, Length(lT));
  For F := Low(lT) To High(lT) Do
      Trace[F] := lT[F];
  Time := T
end;

destructor TStat.Destroy;

Var F: Integer;
begin
   For F := 0 To INP.Count-1 Do
       If Assigned(INP.Objects[F]) Then
          Dispose(PMatrixType(INP.Objects[F]));
   INP.Free;
   lSeq.Free;
   lWords.Free;
   lRels.Free
end;

procedure CreateDOMContact(dom: Pointer; Parent: Pointer; Tag: PChar; CntID: PChar); cdecl;

Var Exists: Boolean;
    L: TDOMElement;
    G: Integer;
Begin
   Exists := False;
   With TDOMElement(Parent).ChildNodes Do
     begin
       For G := 0 To Count - 1 Do
           If TDOMElement(Item[G]).AttribStrings['ID'] = String(CntID) Then
              Begin
                Exists := True;
                Break
              End;
       Free
     end;
   If Not Exists Then
      Begin
        L := TDOMElement(TDOMElement(Parent).AppendChild(TXMLDocument(dom).CreateElement(String(Tag))));
        L.AttribStrings['ID'] := String(CntID);
        L.AttribStrings['Ref'] := IntToStr(Random(100000))
      end
end;

function ExtractSystemFromDOM(dom: TXMLDocument; Var res: TXPathVariable; ENV: TXPathEnvironment): Pointer;

  function CreateLinks(sys: Pointer; obj: TDOMElement; Cont: TDOMElement; Const PartnerTag: String): Boolean;

  Var F, G: Integer;
      ID, ContID: DOMString;
      El, PEl: Pointer;
      PID, PContID: DOMString;
      retS: PChar;
      res: TXPathVariable;
      L: Pointer;
      Ref: DOMString;
      Info: Boolean;
      S: String;
  Begin
     Result := False;
     ID := obj.AttribStrings['ID'];
     ContID := Cont.AttribStrings['ID'];
     El := GetElement(sys, PChar(String(ID)));
     With Cont.ChildNodes Do
       begin
         For F := 0 To Length - 1 Do
             If TDOMElement(Item[F]).TagName = 'Link' Then
                Begin
                  Ref := TDOMElement(Item[F]).AttribStrings['Code'];
                  S := TDOMElement(Item[F]).AttribStrings['Informational'];
                  Info := (CompareText(S, 'true') = 0) Or (CompareText(S, '1') = 0);
                  res := EvaluateXPathExpression('/OBJS/*/' + PartnerTag + '[@Ref=' + Ref + ']', dom.DocumentElement, Nil, [], Nil, Nil, ENV);
                  ENV.commitUndo(0);
                  If res Is TXPathNodeSetVariable Then
                     With res.AsNodeSet Do
                       If Count > 0 then
                          Begin
                            PID := TDOMElement(TDOMElement(Items[0]).ParentNode).AttribStrings['ID'];
                            PContID := TDOMElement(Items[0]).AttribStrings['ID'];
                            PEl := GetElement(sys, PChar(String(PID)));
                            If PartnerTag = 'I' Then
                               L := AddLink(Sys, El, PChar(String(ContID)), PEl, PChar(String(PContID)), retS, Info)
                            Else
                               L := AddLink(Sys, PEl, PChar(String(PContID)), El, PChar(String(ContID)), retS, Info);
                            If Not Info Then
                               Begin
                                 If AnalyzeLinkStatusIsInform(sys, L) Then
                                    Begin
                                      _Free(L);
                                      L := Nil
                                    End
                               End;
                            If Not Assigned(L) Then
                               Begin
                                 res.Free;
                                 Exit(False)
                               End
                          End;
                  res.Free
                end;
         Free
       end;
     Result := True
  End;

Var objs: TNodeSet;
    obj: TDOMElement;
    el: Pointer;
    ID: String;
    C: TNodeSet;
    F, G: Integer;
    X: Integer;
Begin
   Result := Nil;
   res := EvaluateXPathExpression('/OBJS/*', dom.DocumentElement, Nil, [], Nil, Nil, ENV);
   ENV.commitUndo(0);
   If res is TXPathNodeSetVariable Then
      Try
        Result := CreateSys();
        objs := res.AsNodeSet;
        X := 50;
        For F := 0 To objs.Count - 1 Do
            If TObject(objs[F]) is TDOMElement then
               Begin
                 obj := TObject(objs[F]) as TDOMElement;
                 If ExistClass(PChar(String(obj.TagName))) Then
                    Begin
                      ID := obj.AttribStrings['ID'];
                      If (Length(ID) = 0) Or Assigned(GetElement(Result, PChar(ID))) Then
                         Begin
                           _Free(Result);
                           Exit(Nil)
                         End;
                      el := AddElement(Result, PChar(String(obj.TagName)), PChar(ID), Integer(flShowClass + flShowName));
                      If Not Assigned(el) Then
                         Begin
                           _Free(Result);
                           Exit(Nil)
                         End;
                      For G := 0 To obj.Attributes.Length - 1 Do
                          SetParameterIfExists(el, PChar(String(obj.Attributes[G].NodeName)), PChar(String(obj.Attributes[G].NodeValue)));
                      XPathing.Move(el, X, 50);
                      Inc(X, 120)
                    End;
               End;
        For F := 0 To objs.Count - 1 Do
            If TObject(objs[F]) is TDOMElement then
               Begin
                 obj := TObject(objs[F]) as TDOMElement;
                 With obj.ChildNodes Do
                   begin
                     For G := 0 To Length - 1 Do
                      If TDOMElement(Item[G]).TagName = 'I' Then
                        Begin
                          If Not CreateLinks(Result, obj, TDOMElement(Item[G]), 'O') Then
                             Begin
                               _Free(Result);
                               Free;
                               Exit(Nil)
                             end
                        End
                      Else If TDOMElement(Item[G]).TagName = 'O' Then
                        Begin
                          If Not CreateLinks(Result, obj, TDOMElement(Item[G]), 'I') Then
                             Begin
                               _Free(Result);
                               Free;
                               Exit(Nil)
                             end
                        End;
                     Free
                   End
               End
      Except
         _Free(Result);
         Result := Nil
      End
end;

Type

{ TDeducer }

 TDeducer = class(TThread)
        Result: Pointer;
        dom: TXMLDocument;
        semaphored: Boolean;
        in_stage: Integer;
        in_tr: TTrace;
        parent: Integer;
        trace: TTrace;
        out_tr: TTrace;
        ENV: TXPathEnvironment;
        OnlyInduceModel: Boolean;
        DEBUG_OFFS: String;

        constructor Create(Const _OFFS: String; _OnlyInduceModel: Boolean; _ENV: TXPathEnvironment; _dom: TXMLDocument; _semaphored: Boolean; _parent: Integer; Const tr: TTrace; _in_stage: Integer; Const _in_tr: TTrace);
        destructor Destroy; override;
        procedure Execute; override;

        procedure Process;
     End;

function Deduce(Const OFFS: String; OnlyInduceModel: Boolean; ENV: TXPathEnvironment; var dom: TXMLDocument; semaphored: Boolean; T: TDeducer;
  parent: Integer; Var tr: TTrace; Var outtr: TTrace;
  _in_stage: Integer; Const _in_tr: TTrace): Pointer;

Var res: TXPathVariable;
    CRes: TResultType;
    hash: String;
    vars: TWeakResult;
    nums: Array Of Integer;
    threads: Array Of TDeducer;
    started: Array Of Boolean;
    vv: TWeakResult;
    ttrs: TTrace;
    rres: Array Of TResultType;
    Buffer: PChar;
    P, TotalP, q: Real;
    NonStricts: Array Of Integer;
    rnds: Array Of Real;
    pp, pp1: Real;
    ones: Integer;
    AllOk: Boolean;
    Prog, Gen: String;
    TaskFile: TextFile;
    StartLanguage: String;
    Compiled: Boolean;
    S: String;
    F, G, K: Integer;
Begin
//   if semaphored then
//      NumThrSemaphore.Wait;

   SetLength(tr, Length(tr) + 1);
   tr[High(tr)] := parent;

   Try
     Result := ExtractSystemFromDOM(dom, res, ENV);
     res.Free;
     (* If Not Assigned(Result) Then WriteLn(OFFS, ' STOP'); *)
     If Assigned(T) Then {T.Synchronize(}T.Process{)};
     If Assigned(Result) Then
        Begin
          CRes := TResultType(CheckSys(Result));
          (*WriteLn(OFFS, ' ', CRes);*)
          If CRes = rsStrict Then
             Begin
               _Free(Result);
               Result := Nil;
               Exit
             End;

          Buffer := GetMem(8*65536*SizeOf(Char));
          ToString(Result, Buffer);
          hash := Buffer;
          FreeMem(Buffer);

          EnterCriticalSection(VariantsCS);
          If Variants.IndexOf(hash) >= 0 Then
             Begin
               LeaveCriticalSection(VariantsCS);
               _Free(Result);
               Result := Nil;
               Exit
             End;
          Variants.Add(hash);
          SetLength(rnds, _Restrictions.Count);
          For F := Low(rnds) To High(rnds) Do
              rnds[F] := Random; // In critical section!
          LeaveCriticalSection(VariantsCS);

          If CRes = rsOk Then
             Begin
               Prog:='';
               If Assigned(T) Then {T.Synchronize(}T.Process{)};
               EnterCriticalSection(VariantsCS);
               Buffer := GetMem(8*65536*SizeOf(WideChar));
               GenerateCode(Result, Buffer);
               Prog := Buffer;
               FreeMem(Buffer);
               If Length(Prog) > 0 Then
                  begin
                    SaveToXML(Result, '_.xml');
                    If Not OnlyInduceModel Then
                       Begin
                          CreateStrFile('_.php3',Prog);
                          {$IF DEFINED(LCL) OR DEFINED(VCL)}
                          Gen := RunExtCommandAsAdmin(
                             {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'sh ./run_php.sh'{$ELSE}'run_php.bat'{$ENDIF},
                             '_.php3 _.gen','_.gen',DBLLINE,'');
                          {$ELSE}
                          Gen := RunExtCommandAsAdmin(
                             {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'sh ./run_php.sh'{$ELSE}'run_php.bat'{$ENDIF},
                             '_.php3 _.gen','_.gen',DBLLINE,'');
                          {$ENDIF}
                          If Pos(errPHP,Gen) <> 0 Then
                             Begin
                               _Free(Result);
                               Result := Nil;
                               LeaveCriticalSection(VariantsCS);
                               If Assigned(T) Then {T.Synchronize(}T.Process{)};
                               Exit
                             End;
                          StartLanguage := '';
                          If FileExists('_.start') Then
                             begin
                               AssignFile(TaskFile,'_.start');
                               Reset(TaskFile);
                               ReadLn(TaskFile,StartLanguage);
                               CloseFile(TaskFile);
                               DeleteFile(PChar('_.start'));
                             end
                          Else
                             Begin
                               _Free(Result);
                               Result := Nil;
                               LeaveCriticalSection(VariantsCS);
                               If Assigned(T) Then {T.Synchronize(}T.Process{)};
                               Exit
                             End;
                          CreateStrFile('_.'+StartLanguage,Gen);
                          DeleteFile(PChar('_.exe'));
                          Compiled := False;
                          For F := 0 To _Restrictions.Count - 1 Do
                              If TObject(_Restrictions[F]) is TWeakTest Then
                                 If Not TWeakTest(_Restrictions[F]).Test(ENV, dom, Result, Compiled, StartLanguage) Then
                                    Begin
                                      _Free(Result);
                                      Result := Nil;
                                      LeaveCriticalSection(VariantsCS);
                                      If Assigned(T) Then {T.Synchronize(}T.Process{)};
                                      Exit
                                    End
                       End;
                    If Assigned(MetaResult) Then
                       Begin
                         _Free(Result);
                         Result := Nil
                       End;
                    LeaveCriticalSection(VariantsCS);
                    If Assigned(T) Then {T.Synchronize(}T.Process{)};
                    SetLength(outtr, Length(tr));
                    If Length(tr) > 0 Then
                       System.Move(tr[0], outtr[0], Length(tr)*SizeOf(Integer));
                    Exit
                  end
               Else
                  Begin
                    _Free(Result);
                    Result := Nil;
                    LeaveCriticalSection(VariantsCS);
                    Exit
                  End
             End
          Else
             Begin
               if (Length(_in_tr) > 0) And (_in_stage >= Length(_in_tr)) Then
                  begin
                    _Free(Result);
                    Result := Nil;
                    Exit
                  end;

               SetLength(vars, 0);
               SetLength(rres, _Restrictions.Count);
               AllOk := True;
               EnterCriticalSection(VariantsCS);
               If Assigned(MetaResult) Then
                  begin
                    LeaveCriticalSection(VariantsCS);
                    _Free(Result);
                    Result := Nil;
                    Exit
                  end;
               LeaveCriticalSection(VariantsCS);

               If Assigned(T) Then {T.Synchronize(}T.Process{)};
               TotalP := 0.0;
               ones := 0;
               SetLength(NonStricts, 0);
               For F := 0 To _Restrictions.Count - 1 Do
                   If (Length(_in_tr) = 0) Or (_in_tr[_in_stage] = F) Then
                      begin
                        rres[F] := TWeakRestriction(_Restrictions[F]).Check(ENV, dom, Result);
                        If rres[F] = rsStrict Then
                           Begin
                             _Free(Result);
                             Result := Nil;
                             Exit
                           End
                        Else If rres[F] = rsNonStrict Then
                           Begin
                             pp := TWeakRestriction(_Restrictions[F]).AprP;
                             if parent >= 0 Then
                                pp := pp * Probabilities[parent][F];
                             TotalP := TotalP + pp;
                             If ones = 0 Then
                                Inc(ones)
                             Else
                                If Abs(pp - pp1) < 1E-7 Then
                                   Inc(ones);
                             SetLength(NonStricts, Length(NonStricts) + 1);
                             NonStricts[High(NonStricts)] := F;
                             pp1 := pp;
                             AllOk := False
                           End
                      end
                   Else
                      rres[F] := rsOk;
               _Free(Result);
               Result := Nil;
               If AllOk Then // No non-strict weak violations but the strong violations present
                  Exit;
               If Assigned(T) Then {T.Synchronize(}T.Process{)};
               EnterCriticalSection(VariantsCS);
               If Assigned(MetaResult) Then
                  begin
                    LeaveCriticalSection(VariantsCS);
                    Exit
                  end;
               LeaveCriticalSection(VariantsCS);
               If ones <> Length(NonStricts) Then
                  For F := Low(NonStricts) To High(NonStricts) Do
                      Begin
                        G := F;
                        P := 0.0;
                        If G < High(NonStricts) Then
                           Begin
                             if parent >= 0 Then
                                q := Probabilities[parent][NonStricts[G]]
                             Else
                                q := 1.0;
                             q := q * TWeakRestriction(_Restrictions[NonStricts[G]]).AprP/TotalP
                           End;
                        While (G < High(NonStricts)) And (P + q < rnds[F]) Do
                          Begin
                            P := P + q;
                            Inc(G);
                            If G < High(NonStricts) Then
                               Begin
                                 if parent >= 0 Then
                                    q := Probabilities[parent][NonStricts[G]]
                                 Else
                                    q := 1.0;
                                 q := q * TWeakRestriction(_Restrictions[NonStricts[G]]).AprP/TotalP
                               End;
                          End;
                        If G <> F Then
                           Begin
                             K := NonStricts[F];
                             NonStricts[F] := NonStricts[G];
                             NonStricts[G] := K
                           End;
                        pp := TWeakRestriction(_Restrictions[NonStricts[F]]).AprP;
                        if parent >= 0 Then
                           pp := pp * Probabilities[parent][NonStricts[F]];
                        TotalP := TotalP - pp;
                        If TotalP < 0.0 Then
                           TotalP := 0.0
                      End;
               SetLength(nums, 0);
               For K := Low(NonStricts) To High(NonStricts) Do
                   Begin
                     F := NonStricts[K];
                     vv := TWeakRestriction(_Restrictions[F]).Construct(ENV, dom);
                     If Assigned(vv) And (Length(vv) > 0) Then
                        Begin
                          SetLength(vars, Length(vars) + Length(vv));
                          SetLength(nums, Length(nums) + Length(vv));
                          For G := Low(vv) To High(vv) Do
                              Begin
                                vars[High(vars) - High(vv) + G] := vv[G];
                                nums[High(nums) - High(vv) + G] := F;
                              End
                        End
                   End;
                If Assigned(T) Then {T.Synchronize(}T.Process{)};
                EnterCriticalSection(VariantsCS);
                If Assigned(MetaResult) Then
                   begin
                     LeaveCriticalSection(VariantsCS);
                     Exit
                   end;
                LeaveCriticalSection(VariantsCS);
                SetLength(threads, Length(vars));
                SetLength(started, Length(vars));
                If Length(vars) > 0 Then
                   FillChar(started[0], Length(vars)*SizeOf(Boolean), 0);
                For F := 0 To Length(vars)-1 Do
                    Begin
                      started[F] := NumThrSemaphore.AttemptWait;
                      if started[F] Then
                         begin
                           threads[F] := TDeducer.Create(OFFS + ' ' + IntToStr(GetCurrentThreadId), OnlyInduceModel, ENV, vars[F], true, nums[F], tr, _in_stage+1, _in_tr);
                           threads[F].Resume;
                           // NumThrSemaphore.Post;
                         end
                      else
                         begin
                           SetLength(ttrs, Length(tr));
                           If Length(ttrs) > 0 Then
                              System.Move(tr[0], ttrs[0], Length(tr)*SizeOf(Integer));
                           Result := Deduce(OFFS + ' ' + IntToStr(GetCurrentThreadId), OnlyInduceModel, ENV, vars[F], false, T, nums[F], ttrs, outtr, _in_stage+1, _in_tr);
                           FreeAndNil(vars[F]);

                           If Assigned(T) Then {T.Synchronize(}T.Process{)};
                           EnterCriticalSection(VariantsCS);
                           If Assigned(MetaResult) Or Assigned(Result) Then
                              Begin
                                If Assigned(Result) Then
                                   If Not Assigned(MetaResult) Then
                                      Begin
                                        SetLength(MetaTrace, Length(outtr));
                                        If Length(outtr) > 0 Then
                                           System.Move(outtr[0], MetaTrace[0], Length(outtr)*SizeOf(Integer));
                                        MetaResult := Result
                                      End
                                   Else
                                      If Result <> MetaResult Then
                                         Begin
                                           _Free(Result);
                                           Result := Nil
                                         End;
                                LeaveCriticalSection(VariantsCS);
                                Break
                              End;
                           LeaveCriticalSection(VariantsCS);
                         end
                    End;
                For F := 0 To Length(vars)-1 Do
                  If started[F] then
                    Begin
                      threads[F].WaitFor;
                      Result := threads[F].Result;
                      vars[F] := threads[F].dom;
                      FreeAndNil(vars[F]);
                      If Assigned(Result) Then
                         Begin
                           EnterCriticalSection(VariantsCS);
                           If Not Assigned(MetaResult) Then
                              Begin
                                SetLength(MetaTrace, Length(threads[F].out_tr));
                                If Length(threads[F].out_tr) > 0 Then
                                   System.Move(threads[F].out_tr[0], MetaTrace[0], Length(threads[F].out_tr)*SizeOf(Integer));
                                MetaResult := Result
                              End
                           Else
                              If Result <> MetaResult Then
                                 Begin
                                   _Free(Result);
                                   Result := Nil
                                 End;
                           LeaveCriticalSection(VariantsCS);
                         End;
                      If Assigned(T) Then {T.Synchronize(}T.Process{)};
                      FreeAndNil(threads[F]);
                    End
                  Else If Assigned(vars[F]) Then
                    FreeAndNil(vars[F])
             End
        End
   Finally
     if semaphored then
        NumThrSemaphore.Post;
   End
End;

{ Deducer }

constructor TDeducer.Create(Const _OFFS: String; _OnlyInduceModel: Boolean; _ENV: TXPathEnvironment; _dom: TXMLDocument;
  _semaphored: Boolean; _parent: Integer; const tr: TTrace;
  _in_stage: Integer; Const _in_tr: TTrace);
begin
   Inherited Create(True);
   FreeOnTErminate := False;
   EnterCriticalSection(VariantsCS);
   Inc(NActiveThreads);
   LeaveCriticalSection(VariantsCS);
   dom := _dom;
   DEBUG_OFFS := _OFFS;

   semaphored := _semaphored;
   OnlyInduceModel := _OnlyInduceModel;
   SetLength(trace, Length(tr));
   If Length(tr) > 0 Then
      System.Move(tr[0], trace[0], Length(tr)*SizeOf(Integer));
   in_stage := _in_stage;
   SetLength(in_tr, Length(_in_tr));
   If Length(_in_tr) > 0 Then
      System.Move(_in_tr[0], in_tr[0], Length(_in_tr)*SizeOf(Integer));
   parent := _parent;
   SetLength(out_tr, 0);
   ENV := _ENV.Clone
end;

destructor TDeducer.Destroy;
begin
   ENV.Free;
   EnterCriticalSection(VariantsCS);
   Dec(NActiveThreads);
   LeaveCriticalSection(VariantsCS);
   inherited Destroy;
end;

procedure TDeducer.Execute;
begin
  Result := Deduce(DEBUG_OFFS, OnlyInduceModel, ENV, dom, semaphored, Self, parent, trace, out_tr, in_stage, in_tr)
end;

procedure TDeducer.Process;
begin
  If Interval > 0 Then
     begin
       EnterCriticalSection(VariantsCS);
       If MilliSecondsBetween(XPathing.Start, Now) >= Interval Then
          begin
            If Not Assigned(MetaResult) Then
               MetaResult := Pointer($0FFFFFFFF);
            XPathing.Start := Now
          end;
       LeaveCriticalSection(VariantsCS)
     end
end;

function XPathInduct(
   _Messaging: Boolean;
   CreateSysF: CreateSysFun;
   ExistClassF: ExistClassFun;
   GetElementF: GetElementFun;
   CanReachF: CanReachFun;
   CreateContactsF: CreateContactsFun;
   AddElementF: AddElementFun;
   AddLinkF: AddLinkFun;
   AnalyzeLinkStatusIsInformF: AnalyzeLinkStatusIsInformFun;
   SetParameterIfExistsF: SetParameterIfExistsFun;
   MoveF: MoveFun;
   CheckSysF: CheckSysFun;
   ToStringF: ToStringFun;
   GenerateCodeF: GenerateCodeFun;
   SaveToXMLF: SaveToXMLFun;
   _FreeF: _FreeFun;
   NodeNameTesterF: TXPathNodeNameTester;
   SelectedMode: PChar;
   UseNNet: Boolean; MainLineAllowed: Boolean;
   _ENV: Pointer;
   inENV, outENV: PChar;
   InXML, OutXML: PChar;
   MaxCPUs: Integer;
   _IDs: PChar;
   OnlyInduceModel:Boolean): Boolean; cdecl;

Const MaxBaumWelch = 5;

// Y[T+1], A[N*N], B[L*N], _pi[N], delta[T*L]
procedure BaumWelch(L, T, N: Integer; Const Y: TTrace; Var A, B: MatrixType; Var _pi: VectorType; Const delta: MatrixType);

Const maxIters = 200;
      eps = 1E-2;

Var alpha, betta, gamma: MatrixType;
    epsilon: Array Of MatrixType;
    sum, old, disb: Real;
    i, j, k, tt: Integer;
    iters: Integer;
begin
   SetLength(alpha, N, T);
   SetLength(betta, N, T);
   SetLength(gamma, N, T);
   SetLength(epsilon, N, N, T);
   iters := 0;
   Repeat
      For i := 0 To N-1 Do
        alpha[i][0] := _pi[i]*B[Y[1]][i];
      For tt := 1 To T-1 Do
        For j := 0 To N-1 Do
          begin
            alpha[j][tt] := 0.0;
            For i := 0 To N-1 Do
              alpha[j][tt] := alpha[j][tt] + alpha[i][tt-1]*A[i][j];
            alpha[j][tt] := alpha[j][tt]*B[Y[tt+1]][j]
          end;
      For i := 0 To N-1 Do
        betta[i][T-1] := 1.0;
      For tt := T-2 DownTo 0 Do
        For i := 0 To N-1 Do
          begin
            betta[i][tt] := 0.0;
            For j := 0 To N-1 Do
              betta[i][tt] := betta[i][tt] + betta[j][tt+1]*A[i][j]*B[Y[tt+2]][j]
          end;
      For tt := 0 To T-1 Do
        begin
          sum := 0.0;
          For i := 0 To N-1 Do
            begin
              gamma[i][tt] := alpha[i][tt]*betta[i][tt];
              sum := sum + gamma[i][tt]
            end;
          If sum <> 0.0 Then
             For i := 0 To N-1 Do
                 gamma[i][tt] := gamma[i][tt]/sum;
        end;
      For tt := 0 To T-2 Do
        begin
          sum := 0.0;
          For i := 0 To N-1 Do
            For j := 0 To N-1 Do
              begin
                epsilon[i][j][tt] := alpha[i][tt]*A[i][j]*betta[j][tt+1]*B[Y[tt+2]][j];
                sum := sum + epsilon[i][j][tt]
              end;
          If sum <> 0.0 Then
             For i := 0 To N-1 Do
               For j := 0 To N-1 Do
                 epsilon[i][j][tt] := epsilon[i][j][tt]/sum;
        end;
      For i := 0 To N-1 Do
        _pi[i] := gamma[i][0];
      disb := 0.0;
      For i := 0 To N-1 Do
        begin
          sum := 0.0;
          For tt := 0 To T-2 Do
            sum := sum + gamma[i][tt];
          For j := 0 To N-1 Do
            begin
              old := A[i][j];
              A[i][j] := 0.0;
              For tt := 0 To T-2 Do
                A[i][j] := A[i][j] + epsilon[i][j][tt];
              If Abs(sum) > 0.001*eps Then A[i][j] := A[i][j] / sum;
              disb := disb + Abs(A[i][j] - old)
            end;
          sum := sum + gamma[i][T-1];
          For k := 0 To L-1 Do
            begin
              old := B[k][i];
              B[k][i] := 0.0;
              For tt := 0 To T-1 Do
                B[k][i] := B[k][i] + delta[tt][k]*gamma[i][tt];
              If Abs(sum) > 0.001*eps Then B[k][i] := B[k][i] / sum;
              disb := disb + Abs(B[k][i] - old)
            end
        end;
      Inc(iters);
      If iters = maxIters Then
         Raise Exception.Create('Too many iterations')
   until disb < eps;
end;

function ReadStr(Var Log: TextFile): String;

Var F: Integer;
    C: Char;
begin
   Read(Log, F); // Читаем количество символов
   Result := '';
   While F > 0 Do
     begin
       Read(Log, C);
       If Not (C in [' ', #9, #$0D, #$0A]) Then
          begin
            AppendStr(Result, C);
            Dec(F)
          end
     end
end;

procedure AddWords(locWords: TStringList);

Var S: String;
    Found: Boolean;
    F, G: Integer;
begin
   With locWords Do
     For F := 0 To Count - 1 Do
       begin
         S := locWords[F];
         Found := False;
         For G := 0 To Words.Count - 1 Do
           If Levenshtein(S, Words[G]) <= 2 Then
              begin
                Found := True;
                Break
              end;
         If Not Found Then
            Words.Add(S)
       end
end;

procedure AddRels(LL: TAnalyser; RelsMap: TStringList; lRels: TStringList);

Var S: String;
    G, K: Integer;
begin
   For G := 0 To lRels.Count -1 Do
     begin
       LL.AnlzLine := lRels[G];
       S := LL.GetIdent(False);
       If Not RelsMap.Find(S, K) Then
          RelsMap.Add(S)
     end;
end;

procedure NormalizeProbabilities(MIN: Real; Const N: Integer; Var P: MatrixType);

Var max: Real;
    F, G: Integer;
begin
   max := 0.0;
   For F := 0 To N - 1 Do
       For G := 0 To N - 1 Do
           If P[F][G] > max Then
              max := P[F][G];
   If max > 0.0 Then
      For F := 0 To N - 1 Do
          For G := 0 To N - 1 Do
              P[F][G] := MIN + (1.0 - MIN) * P[F][G] / max;
end;

function LevenshteinWords(const s1, s2: TStringList): Integer;

Var diff: integer;
    m: Array Of Array Of Integer;
    i, j: Integer;
Begin
 SetLength(m, s1.Count + 1, s2.Count + 1);

 for i := 0 To s1.Count do
     m[i][0] := i;
 for j := 0 To s2.Count do
     m[0][j] := j;

 for i := 1 to s1.Count do
   begin
     for j := 1 to s2.Count do
       begin
         if Levenshtein(s1[i-1],s2[j-1]) <= 2 then diff := 0 else diff := 1;

         m[i][j] := Min(Min(m[i - 1, j] + 1,
                                  m[i, j - 1] + 1),
                                  m[i - 1, j - 1] + diff);
       end
   end;
   Result := m[s1.Count][s2.Count]
end;

procedure SetProbabilities(LL: TAnalyser; INP: TStringList; lSeq: TList; lWords, lRels, templateWords: TStringList; TT: Real);

Var S: String;
    PP: PMatrixType;
    KP, KS, KT: Integer;
    G, K, M, P: Integer;
begin
   KP := INP.IndexOf('PRESENT');
   KS := INP.IndexOf('SEQ');
   KT := INP.IndexOf('TIME');
   For G := 0 To INP.Count -1 Do
     begin
       New(PP);
       If G = KP Then
          SetLength(PP^, 1, Words.Count)
       Else If G = KS Then
          SetLength(PP^, 1, 1)
       Else If G = KT Then
          SetLength(PP^, 1, 1)
       Else
          SetLength(PP^, Words.Count, Words.Count);
       For K := 0 To Length(PP^) - 1 Do
         For P := 0 To Length(PP^[K]) - 1 Do
           PP^[K][P] := 0.0;
       INP.Objects[G] := TObject(PP)
     end;
   PP := PMatrixType(INP.Objects[KP]);
   For G := 0 To lWords.Count - 1 Do
     begin
       S := lWords.Strings[G];
       For P := 0 To Words.Count - 1 Do
         If Levenshtein(S, Words[P]) <= 2 Then
            begin
              PP^[0][P] := PP^[0][P] + 0.1;
              Break
            end
     end;
   PP := PMatrixType(INP.Objects[KS]);
   P := LevenshteinWords(lWords, templateWords);
   PP^[0][0] := 1.0*P/(2*Words.Count);
   PP := PMatrixType(INP.Objects[KT]);
   PP^[0][0] := TT/600.0;
   For G := 0 To lRels.Count - 1 Do
     begin
       LL.AnlzLine := lRels.Strings[G];
       S := LL.GetIdent(False);
       K := INP.IndexOf(S);
       If K < 0 Then
          MakeErrorCommon('Unknown relation "'+S+'"')
       Else
          begin
            LL.Check(LeftBracket);
            If Not LL.Error Then
               begin
                 S := LL.GetBefore(True, [Colon]);
                 LL.Check(Colon);
                 For P := 0 To Words.Count - 1 Do
                   If Levenshtein(S, Words[P]) <= 2 Then
                      begin
                        S := LL.GetBefore(True, [RightBracket]);
                        LL.Check(RightBracket);
                        If Not LL.Error Then
                           begin
                             For M := 0 To Words.Count - 1 Do
                               If Levenshtein(S, Words[M]) <= 2 Then
                                  begin
                                    PP := PMatrixType(INP.Objects[K]);
                                    PP^[P][M] := PP^[P][M] + 0.1;
                                    Break
                                  end
                           end;
                        Break
                      end
               end
          end
     end
end;

function CalcDist(P1, P2: TStringList; Const IgnoreTime: Boolean = False): Real;

Var F, G, H: Integer;
    D: Real;
begin
   Result := 0.0;
   For F := 0 To P1.Count - 1 Do
     If (Not IgnoreTime) Or (P1.Strings[F] <> 'TIME') Then
      For G := 0 To Length(PMatrixType(P1.Objects[F])^) - 1 Do
         For H := 0 To Length(PMatrixType(P1.Objects[F])^[G]) - 1 Do
           begin
             D := PMatrixType(P1.Objects[F])^[G][H] - PMatrixType(P2.Objects[F])^[G][H];
             Result := Result + D*D
           end;
   // Result := Sqrt(Result)
end;

Function HexDigit(C: Char): Integer;
Begin
  If (Ord(C) >= Ord('0')) And (Ord(C) <= Ord('9')) Then
     Result := Ord(C) - Ord('0')
  Else If (Ord(C) >= Ord('A')) And (Ord(C) <= Ord('F')) Then
     Result := 10 + Ord(C) - Ord('A')
  Else If (Ord(C) >= Ord('a')) And (Ord(C) <= Ord('f')) Then
     Result := 10 + Ord(C) - Ord('a')
  Else
     Result := 0
End;

var
  parser: TDOMParser;
  L: TStringList;
  src: TXMLInputSource;
  deducer: TDeducer;
  dom, init_dom: TXMLDocument;
  ENV: TXPathEnvironment;
  tr: TTrace;
  Log: TextFile;
  prev, this: Integer;
  Time: TDateTime;
  S, S1, S2: String;
  lProbabilities0, lProbabilities1: MatrixType;
  lTrace: TTrace;
  MainLine: TTrace;
  Mode: String;
  C: Char;
  TT: Real;
  LL: TAnalyser;
  RelsMap: TStringList;
  Found: Boolean;
  locSeq, locWords, locRels, locP: TStringList;
  RulerClasses: TStringList;
  Seq: TList;
  Dists: Array Of Real;
  W, W1, WT: Real;
  Buf: Real;
  F, G, K, M, P, H: Integer;
  _pi: VectorType;
  res: TXPathVariable;
  (* C: TNodeSet; *)
begin
   Result := False;

   Messaging := _Messaging;

   CreateSys := CreateSysF;
   ExistClass := ExistClassF;
   GetElement := GetElementF;
   CanReach := CanReachF;
   CreateContacts := CreateContactsF;
   AddElement := AddElementF;
   AddLink := AddLinkF;
   AnalyzeLinkStatusIsInform := AnalyzeLinkStatusIsInformF;
   SetParameterIfExists := SetParameterIfExistsF;
   Move := MoveF;
   CheckSys := CheckSysF;
   ToString := ToStringF;
   GenerateCode := GenerateCodeF;
   SaveToXML := SaveToXMLF;
   _Free := _FreeF;
   NodeNameTester := NodeNameTesterF;
   With TStringList.Create Do
     Begin
       Text := String(_IDs);
       SetLength(IDs, Count);
       For F := 0 To Count-1 Do
           IDs[F] := Strings[F];
       Free
     End;
   If Assigned(_ENV) Then
      ENV := _ENV
   Else
      Begin
        ENV := TXPathEnvironment.Create;
        If (inENV <> Nil) And (String(inENV) <> '') Then
           ENV.Import(inENV)
      End;

   For F := 0 To Ruler.Count - 1 Do
     DisposeStr(PString(Ruler.Objects[F]));
   Ruler.Clear;

   FreeAndNil(Words);

   parser := TDOMParser.Create;
   L := TStringList.Create;
   try
     parser.Options.PreserveWhitespace := True;
     parser.Options.Namespaces := True;
     L.LoadFromFile(InXML);
     If (L.Count > 0) And (L[0] <> '<OBJS>') Then
        Begin
          L.Insert(0, '<OBJS>');
          L.Add('</OBJS>')
        End;
     src := TXMLInputSource.Create(L.Text); // '<a><b><list data="1"><list data="2"></list></list></b><c><list data="3"><list data="4"></list></list></c></a>'
     try
       parser.Parse(src, dom);
(*       C := TNodeSet.Create; *)
(**)
//       ENV.AddFunction('loop', Nil, true, ['$I','$max','$body'], '($I <= $max and set($I, $I+1) and eval($body) and loop($I,$max,$body)) or true()');
//       ENV.AddFunction('depth', Nil, true, ['&$OUT1'], 'set($OUT1,0) and (self::*[set($OUT1,1) and *[depth($OUT0) and set($OUT1,max($OUT0+1,$OUT1))]] or true())');
//       res := EvaluateXPathExpression('loop(0,3,"true()") and depth($A)', dom.DocumentElement, Nil, [Nil,Nil,dom.DocumentElement], Nil, Nil, ENV);
//       ENV.AddFunction('make_loop', Nil, true, [], 'self::*[@counter <= @max and create(loop[@counter = ###/@counter+1 and @max = ###/@max]) and loop[make_loop()] or true()] or true()');
//       res := EvaluateXPathExpression('create(loop[@counter = 0 and @max = 3]) and loop[make_loop()] and delete(loop)', dom.DocumentElement, Nil, [Nil,Nil,dom.DocumentElement], Nil, Nil, ENV);
//       res := EvaluateXPathExpression('transaction(create(/OBJS/saccura) and delete(/OBJS/*) and false())', dom.DocumentElement, Nil, [Nil,Nil,dom.DocumentElement], Nil, Nil, ENV);
//       res := EvaluateXPathExpression('transaction(create(/OBJS/clsSimpleTerminator[@ID="END" and I[@ID="End"]]))', dom.DocumentElement, Nil, [Nil,Nil,dom.DocumentElement], Nil, Nil, ENV);
//         ENV.AddFunction('depth_list', Nil, true, ['$#','&$OUT1'], 'set($OUT1,0) and (#/list[set($OUT1,1) and depth_list(#/list,$OUT0) and set($OUT1,max($OUT0+1,$OUT1))]) or true()');
//         ENV.AddFunction('concat_list', Nil, true, ['$#', '$##'], 'add_list(#/self::*) and add_list(##/self::*)');
//         ENV.AddFunction('add_list', Nil, true, ['$#'], 'count(list) = 0 and copy_list(#/self::*) or list[add_list(#/self::*)] or true()');
//         ENV.AddFunction('copy_list', Nil, true, ['$#'], 'count(#/list) = 0 or create(list[@data = #/list/@data]) and (list[copy_list(#/list)] or true())');
//         res := EvaluateXPathExpression('transaction(concat_list(/a/b,/a/c) and depth_list(/a,$A) or true())', dom.DocumentElement, Nil, [Nil,Nil,dom.DocumentElement], Nil, Nil, ENV);
//         F := Round(ENV.VariablesByName['A'].AsNumber);
(**)
//       res := EvaluateXPathExpression('/doc/av/v/x/p[(@ID = 1 or @ID = 2) and @ID < 2]/node/@ID', dom.DocumentElement, [dom.DocumentElement,dom.DocumentElement], C);
       res := EvaluateXPathExpression('/OBJS/*[@ID != ""]', dom.DocumentElement, Nil, [], Nil, Nil, ENV);
       Seq := TList.Create;
       RulerClasses := TStringList.Create;
       If res is TXPathNodeSetVariable Then
          For F := 0 To res.AsNodeSet.Count - 1 Do
            Begin
              S := TDOMElement(res.AsNodeSet[F]).AttribStrings['GID'];
              If Length(S) > 0 Then
                 Begin
                   G := StrToInt(S);
                   If G >= 0 Then
                      Begin
                        For K := Low(IDs) To High(IDs) Do
                            If IDs[K] = S Then
                               Begin
                                 G := K;
                                 Break
                               End;
                        Ruler.AddObject(TDOMElement(res.AsNodeSet[F]).AttribStrings['ID'], IntegerToTObject(G));
                        RulerClasses.Add(TDOMElement(res.AsNodeSet[F]).TagName);
                        Seq.Add(TStringList.Create);
                        With TStringList(Seq[Seq.Count - 1]) Do
                          Begin
                            S := TDOMElement(res.AsNodeSet[F]).AttribStrings['WORDS'];
                            S1 := '';
                            For K := 1 To Length(S) Do
                                If S[K] = ' ' Then
                                   Begin
                                     If Length(S1) > 0 Then
                                        Begin
                                          S2 := '';
                                          For M := 1 To Length(S1) Div 2 Do
                                              S2 := S2 + Chr(HexDigit(S1[M*2-1])*16 + HexDigit(S1[M*2]));
                                          Add(S2)
                                        End;
                                     S1 := ''
                                   End
                                Else
                                   S1 := S1 + S[K];
                          End;
                      End
                 end
            end;
       res.Free;
       ENV.CollectedWords.Clear;
       For F := 0 To Ruler.Count - 2 Do
         Begin
           K := TObjectToInteger(Ruler.Objects[F]);
           P := F;
           For G := F + 1 To Ruler.Count - 1 Do
             Begin
               M := TObjectToInteger(Ruler.Objects[G]);
               If M < K Then
                  Begin
                    K := M;
                    P := G
                  End
             End;
           If P <> F Then
              begin
                Ruler.Exchange(P, F);
                Seq.Exchange(P, F);
                RulerClasses.Exchange(P, F)
              end
         End;
       For F := 0 To Ruler.Count - 1 Do
         begin
           Ruler.Objects[F] := TObject(NewStr(RulerClasses.Strings[F]));
           Seq.Add(IntegerToTObject(ENV.CollectedWords.Count));
           ENV.CollectedWords.AddStrings(TStringList(Seq[F]));
           Seq.Add(IntegerToTObject(ENV.CollectedWords.Count))
         end;
       For F := 0 To Ruler.Count - 1 Do
         Seq.Delete(0);
       RulerClasses.Free;
       Variants := TStringList.Create;
       Variants.Sorted := True;

       Stat := TObjList.Create;

       NumThreads := MaxCPUs;
       MetaResult := Nil;

       SetLength(MetaTrace, 0);
       SetLength(Probabilities, _Restrictions.Count, _Restrictions.Count);
       SetLength(lProbabilities0, _Restrictions.Count, _Restrictions.Count);
       SetLength(lProbabilities1, _Restrictions.Count, _Restrictions.Count);
       For F := 0 To _Restrictions.Count - 1 Do
           For G := 0 To _Restrictions.Count - 1 Do
               Probabilities[F][G] := 1.0;
       If Length(DeduceLogFile) > 0 Then
          If FileExists(DeduceLogFile) Then
             Begin
               AssignFile(Log, DeduceLogFile);
               Reset(Log);
               If Not Eof(Log) Then
                 begin
                   Words := TStringList.Create;
                   Words.CaseSensitive := False;
                   Words.Sorted := True;

                   AddWords(ENV.CollectedWords);

                   locWords := TStringList.Create;
                   locWords.Delimiter := SemiColon;
                   locRels := TStringList.Create;
                   locRels.Delimiter := SemiColon;
                   locSeq := TStringList.Create;
                   locSeq.Delimiter := Colon;
                   prev := -1;
                   While Not Eof(Log) Do
                     begin
                       Read(Log, this);
                       If this = -11 Then
                          begin
                            Mode := '';
                            Repeat
                               Read(Log, C);
                               If C = '*' Then
                                  Break
                               Else
                                  AppendStr(Mode, C)
                            Until Eof(Log);
                            Mode := Trim(Mode);
                            If Mode = SelectedMode Then
                               this := -10
                          end;
                       If this = -10 Then
                          begin
                            If UseNNet Then
                               begin
                                 locWords.DelimitedText := ReadStr(Log);
                                 locRels.DelimitedText := ReadStr(Log);
                                 locSeq.DelimitedText := ReadStr(Log);
                                 AddWords(locWords)
                               end
                            Else
                               begin
                                 ReadStr(Log);
                                 ReadStr(Log);
                                 ReadStr(Log)
                               end;
                            locP := TStringList.Create;
                            locP.Delimiter := ';';
                            locP.DelimitedText := ReadStr(Log);
                            K := 0;
                            For F := 0 To _Restrictions.Count - 1 Do
                                For G := 0 To _Restrictions.Count - 1 Do
                                    begin
                                      Val(locP.Strings[K], lProbabilities0[F][G], P);
                                      Inc(K)
                                    end;
                            locP.DelimitedText := ReadStr(Log);
                            K := 0;
                            For F := 0 To _Restrictions.Count - 1 Do
                                For G := 0 To _Restrictions.Count - 1 Do
                                    begin
                                      Val(locP.Strings[K], lProbabilities1[F][G], P);
                                      Inc(K)
                                    end;
                            locP.Free;
                            Read(Log, TT);
                            If UseNNet Then
                               begin
                                 If TT < 0.0 Then
                                    begin
                                      Read(Log, G);
                                      SetLength(lTrace, G);
                                      For F := 0 To G-1 Do
                                          Read(Log, lTrace[F]);
                                      Read(Log, TT)
                                    end
                                 Else
                                    SetLength(lTrace, 0);
                                 Stat.Add(TStat.Create(locSeq, locWords, locRels, lProbabilities0, lProbabilities1, TT, lTrace))
                               end
                            Else
                               For F := 0 To _Restrictions.Count - 1 Do
                                   For G := 0 To _Restrictions.Count - 1 Do
                                       Probabilities[F][G] := Probabilities[F][G] + (lProbabilities1[F][G] - 0.7)
                          end
                       Else
                          ReadLn(Log, S);
                       if (prev >= 0) And (this >= 0) Then
                          Probabilities[prev][this] := Probabilities[prev][this] + 0.3;
                       prev := this
                     end;
                   NormalizeProbabilities(0.25, _Restrictions.Count, Probabilities);
                   locRels.Free;
                   locWords.Free;
                   locSeq.Free
                 end;
               CloseFile(Log)
             end;

       SetLength(MainLine, 0);

       If Stat.Count > 0 Then // Some magic...
          begin
            RelsMap := TStringList.Create;
            RelsMap.Sorted := True;

            // Add PRESENT Type - frequences of local words;
            RelsMap.Add('PRESENT');
            // Add SEQ Type - Levenshtein task difference;
            RelsMap.Add('SEQ');
            // Add TIME Type
            RelsMap.Add('TIME');

            LL := TAnalyser.Create(LettersSet, [Space, Tabulation]);

            AddRels(LL, RelsMap, ENV.CollectedRels);

            For F := 0 To Stat.Count - 1 Do
                With TStat(Stat[F]) Do
                  AddRels(LL, RelsMap, lRels);
            // In each Stat[F] create RelsMap copy with local matrices
            For F := 0 To Stat.Count - 1 Do
                With TStat(Stat[F]) Do
                  begin
                    INP.Assign(RelsMap);
                    SetProbabilities(LL, INP, lSeq, lWords, lRels, ENV.CollectedWords, Time)
                  end;
            // Calculate Radiuses
            SetLength(Dists, Stat.Count - 1);
            For F := 0 To Stat.Count - 1 Do
                With TStat(Stat[F]) Do
                  begin
                    K := 0;
                    For G := 0 To Stat.Count - 1 Do
                      If F <> G Then
                         begin
                           Dists[K] := CalcDist(INP, TStat(Stat[G]).INP);
                           If Dists[K] > 0.0 Then Inc(K)
                         end;
                    // Find First 5 minimal dists
                    M := Min(K, 5);
                    R := 0.0;
                    For G := 0 To M-1 Do
                      begin
                        P := G;
                        For H := G+1 To K - 1 Do
                          If Dists[P] > Dists[H] Then
                             P := H;
                        R := R + Dists[P];
                        If P <> G Then
                           begin
                             Buf := Dists[P];
                             Dists[P] := Dists[G];
                             Dists[G] := Buf
                           end
                      end;
                    If R > 0 Then R := 2.0*M/R;
                    R := Math.Max(0.1, Math.Min(2.0, R))
                  end;
            SetProbabilities(LL, RelsMap, Seq, ENV.CollectedWords, ENV.CollectedRels, ENV.CollectedWords, 0.0);
            // Calc Probabilities based on RelsMap.OBJS x Stat[F].Objs[INP=>Probabilities]
            For F := 0 To _Restrictions.Count - 1 Do
                For G := 0 To _Restrictions.Count - 1 Do
                    Probabilities[F][G] := 0.0;

            W := 0.0;
            For K := 0 To Stat.Count - 1 Do
                With TStat(Stat[K]) Do
                  begin
                    W1 := Exp(-R*CalcDist(INP, RelsMap, False));
                    If MainLineAllowed And (Length(Trace) > Length(MainLine)) And (CalcDist(INP, RelsMap, True) = 0.0) Then
                       begin
                         SetLength(MainLine, Length(Trace));
                         If Length(Trace) > 0 Then
                            System.Move(Trace[0], MainLine[0], Length(Trace)*SizeOf(Integer))
                       end;
                    WT := 0.5 + 0.25*Math.Min(1.0, Time/100.0);
                    For F := 0 To _Restrictions.Count - 1 Do
                        For G := 0 To _Restrictions.Count - 1 Do
                            Probabilities[F][G] := Probabilities[F][G] +
                               W1*((1-WT)(*0.3*)*OUT0[F][G]+WT*(*0.7*)OUT1[F][G]);
                    W := W+W1
                  end;
            If W > 0.0 Then
               For F := 0 To _Restrictions.Count - 1 Do
                   For G := 0 To _Restrictions.Count - 1 Do
                       Probabilities[F][G] := Probabilities[F][G]/W;
            NormalizeProbabilities(0.0, _Restrictions.Count, Probabilities);

            LL.Free;
            With RelsMap Do
              begin
                For F := 0 To Count - 1 Do
                  If Assigned(Objects[F]) Then
                     Dispose(PMatrixType(Objects[F]));
                Free
              end
          end;

       NumThrSemaphore := TSemaphore.Create(NumThreads - 1);
       InitCriticalSection(VariantsCS);

       Messaging := False;
       Randomize;

       Time := Now;
       init_dom := dom.CloneNode(True) As TXMLDocument;
       Repeat
          MetaResult := Nil;

          SetLength(tr, 0);
          Start := Now;
          NActiveThreads := 0;
          deducer := TDeducer.Create('', OnlyInduceModel, ENV, dom, false, -1, tr, 0, MainLine);
          deducer.Resume;
          deducer.WaitFor;
          dom := deducer.dom;
          deducer.Free;

          Repeat
             EnterCriticalSection(VariantsCS);
             If NActiveThreads = 0 Then Break;
             LeaveCriticalSection(VariantsCS);
             Sleep(100)
          Until False;
          LeaveCriticalSection(VariantsCS);

          If MetaResult = Pointer($0FFFFFFFF) Then
             begin
               dom.Free;
               dom := init_dom.CloneNode(True) As TXMLDocument;
               Variants.Clear;
               {$IF DEFINED(VCL) OR DEFINED(LCL)}
               Application.ProcessMessages
               {$ELSE}
               Sleep(0)
               {$ENDIF}
             end
          Else
             init_dom.Free;
       Until MetaResult <> Pointer($0FFFFFFFF);
       Time := 0.001*MilliSecondsBetween(Time, Now);

       FreeAndNil(NumThrSemaphore);
       DoneCriticalSection(VariantsCS);

       Variants.Free;
       FreeAndNil(Stat);
       FreeAndNil(Words);
       If Assigned(MetaResult) Then
          Begin
            If (Length(DeduceLogFile) > 0) And (Length(MainLine) = 0) Then
               Begin
                 AssignFile(Log, DeduceLogFile);
                 If FileExists(DeduceLogFile) Then
                    Append(Log)
                 Else
                    Rewrite(Log);
                 Write(Log, -11, ' ', SelectedMode, '* ');
                 S := ENV.CollectedWords.DelimitedText;
                 Write(Log, ' ', Length(S), ' ', S, ' ');
                 S := ENV.CollectedRels.DelimitedText;
                 Write(Log, ' ', Length(S), ' ', S, ' ');
                 S := '';
                 For F := 0 To Seq.Count-1 Do
                   begin
                     AppendStr(S, IntToStr(TObjectToInteger(Seq[F])));
                     If F < Seq.Count-1 Then
                        AppendStr(S, ':')
                   end;
                 Write(Log, ' ', Length(S), ' ', S, ' ');
                 locP := TStringList.Create;
                 locP.Delimiter := ';';
                 For F := 0 To _Restrictions.Count - 1 Do
                     For G := 0 To _Restrictions.Count - 1 Do
                         begin
                           Str(Probabilities[F][G]:5:3, S);
                           locP.Add(Trim(S))
                         end;
                 S := locP.DelimitedText;
                 Write(Log, Length(S), ' ', S, ' ');

                 For F := 0 To _Restrictions.Count - 1 Do
                     For G := 0 To _Restrictions.Count - 1 Do
                         Probabilities[F][G] := Random;

                 { Baum-Welch }
                 // BaumWelch(L, T, N, Y[T+1], A[N*N], B[L*N], _pi[N], delta[T*L]);
                 SetLength(lProbabilities0, _Restrictions.Count, _Restrictions.Count);
                 For F := 0 To _Restrictions.Count - 1 Do
                     For G := 0 To _Restrictions.Count - 1 Do
                         lProbabilities0[F][G] := Random;
                 SetLength(_pi, _Restrictions.Count);
                 For F := 0 To _Restrictions.Count - 1 Do
                     _pi[F] := Random;
                 SetLength(lProbabilities1, High(MetaTrace), _Restrictions.Count);
                 For F := 0 To High(MetaTrace) - 1 Do
                     For G := 0 To _Restrictions.Count - 1 Do
                         If MetaTrace[F+1] = G Then
                            lProbabilities1[F][G] := 1.0
                         Else
                            lProbabilities1[F][G] := 0.0;

                 BaumWelch(_Restrictions.Count, High(MetaTrace), _Restrictions.Count,
                     MetaTrace,
                     Probabilities, lProbabilities0, _pi, lProbabilities1);

                 SetLength(lProbabilities1, _Restrictions.Count, _Restrictions.Count);
                 { Переходим от наблюдений к вероятностям состояний, применяем матрицу переходов между состояниями,
                   переходим от состояний к наблюдениям, в-общем P = B*A*transp(B) }
                 For F := 0 To _Restrictions.Count - 1 Do
                   For G := 0 To _Restrictions.Count - 1 Do
                     begin
                       lProbabilities1[F][G] := 0.0;
                       For K := 0 To _Restrictions.Count - 1 Do
                           lProbabilities1[F][G] := lProbabilities1[F][G] +
                              lProbabilities0[F][K]*Probabilities[K][G]
                     end;
                 For F := 0 To _Restrictions.Count - 1 Do
                   For G := 0 To _Restrictions.Count - 1 Do
                     begin
                       Probabilities[F][G] := 0.0;
                       For K := 0 To _Restrictions.Count - 1 Do
                           Probabilities[F][G] := Probabilities[F][G] +
                              lProbabilities1[F][K]*lProbabilities0[G][K]
                     end;

                 For F := 0 To _Restrictions.Count - 1 Do
                   begin
                     W := 0.0;
                     For G := 0 To _Restrictions.Count - 1 Do
                       If Probabilities[F][G] > W Then
                          W := Probabilities[F][G];
                     If W > 0.0 Then
                        For G := 0 To _Restrictions.Count - 1 Do
                            Probabilities[F][G] := Probabilities[F][G]/W;
                     For G := 0 To _Restrictions.Count - 1 Do
                         Probabilities[F][G] := 0.7 + 0.3*Probabilities[F][G];
                   end;

                 locP.Clear;
                 For F := 0 To _Restrictions.Count - 1 Do
                     For G := 0 To _Restrictions.Count - 1 Do
                         begin
                           Str(Probabilities[F][G]:5:3, S);
                           locP.Add(Trim(S))
                         end;

                 S := locP.DelimitedText;
                 locP.Free;
                 Write(Log, Length(S), ' ', S, ' ', -20, ' ');
                 Write(Log, Length(MetaTrace)-1, ' ');
                 For F := 1 To High(MetaTrace) Do
                     Write(Log, MetaTrace[F], ' ');
                 WriteLn(Log, Time:5:2);
                 CloseFile(Log)
               End;
            SaveToXML(MetaResult, OutXML);
            _Free(MetaResult);
            MakeInfoCommon('Deduced successfully in ' + FloatToStrF(Time, ffGeneral, 3, 6) + ' sec!')
          End
       Else
          MakeErrorCommon('Unsuccessfull XPath Deducing in ' + FloatToStrF(Time, ffGeneral, 3, 6) + ' sec...');
       Seq.Free;
       dom.Free;
     finally
       src.Free;
       Messaging := True
     end;
   finally
     If Not Assigned(_ENV) Then
        Begin
          ENV.Export(outENV);
          ENV.Free
        End;
     parser.Free;
     L.Free
   end;

   Result := True
end;

function CheckXPath(Var L: TAnalyser; Const XPath: String): Boolean;

Var Scan: TXPathScanner;
    Node: TXPathExprNode;
Begin
   Scan := TXPathScanner.Create(XPath);
   Node := Nil;
   Try
     Try
       Node := Scan.ParseOrExpr;
       If Scan.CurToken <> tkEndOfStream Then
          Begin
            L.MakeError('Garbage after XPath');
            Exit(False)
          end;
     Except
        L.MakeError('Incorrect XPath');
        Exit(False)
     end;
   finally
     Node.Free;
     Scan.Free
   end;
   Result := True
end;

function CompileXPathing(
   _Messaging: Boolean;
   _AllowedVersions: PChar;
   FName: PChar; _ENV: Pointer; inENV, outENV: PChar;
   _WorkText: PChar): Boolean; cdecl;

function Intersecting(L1, L2: TStringList): Boolean;

Var F: Integer;
Begin
   Result := True;
   For F := 0 To L1.Count-1 Do
       If L2.IndexOf(L1.Strings[F]) >= 0 Then
          Exit;
   Result := False
end;

Var ENV: TXPathEnvironment;
    AllowedVersions, CurrentVersions: TStringList;
    WorkText: String;
    LL:TStringList;
    LM:TMemoryStream;
    L: TAnalyser;
    S, S1, S2: String;
    Allowed: Boolean;
    Args: Array Of String;
    Ref: Boolean;
    Sign: Char;
    _AprP: Real;
    _Ruler: TStringList;
    Op: TWeakOperator;
    F, G: Integer;
begin
     Messaging := _Messaging;
     If Assigned(_ENV) Then
        ENV := _ENV
     Else
        Begin
          ENV := TXPathEnvironment.Create;
          If (inENV <> Nil) And (String(inENV) <> '') Then
             ENV.Import(inENV)
        End;
     AllowedVersions := TStringList.Create;
     AllowedVersions.Text := String(_AllowedVersions);
     CurrentVersions := TStringList.Create;
     CurrentVersions.Text := String(_AllowedVersions);
     LL := TStringList.Create;
     L := TAnalyser.Create(IdentSet, [Space, Tabulation]);
     L.CurFile := FName;
     Try
       WorkText := String(_WorkText);
       If Length(WorkText) > 0 Then
          begin
            LM := TMemoryStream.Create;
            LM.Write(WorkText[1], Length(WorkText)*SizeOf(Char));
            LM.Seek(0, soBeginning);
            LL.LoadFromStream(LM);
            LM.Free
          end
       else
          LL.LoadFromFile(FName);

       F := 0;
       While F < LL.Count Do
           Begin
             Allowed := (AllowedVersions.Count = 0) Or InterSecting(CurrentVersions, AllowedVersions);
             L.AnlzLine := TrimRight(LL.Strings[F]);
             L.NumLine := F + 1;
             If Not (L.Empty Or L.Error) Then
                Begin
                  If L.IsNext(Percent) Then
                     begin
                       Inc(F);
                       Continue
                     end;

                  If L.IsNext(SpecSymbol) Then
                     Begin
                       L.Check(SpecSymbol);
                       S := L.GetIdent(False);
                       If (S = dirVersions) And L.Check(LeftBracket) Then
                          begin
                            CurrentVersions.Clear;
                            While Not (L.Error Or L.IsNext(RightBracket)) Do
                              begin
                                S := L.GetBalancedListItem(False, [RightBracket, Comma]);
                                CurrentVersions.Add(S);
                                If L.Empty Then
                                   L.ExpectSet([RightBracket, Comma])
                                Else If L.IsNext(Comma) Then
                                   L.Check(Comma);
                              end;
                            L.Check(RightBracket);
                            If Not L.Error Then
                               begin
                                 Inc(F);
                                 Continue
                               end
                          end
                     End;

                  If Not Allowed Then
                     begin
                       Inc(F);
                       Continue
                     end;

                  If L.IsNext(Asterisk) And L.Check(Asterisk) Then
                     begin
                       S := L.GetIdent(False);
                       If Length(S) = 0 Then
                          begin
                            L.Expect('Function identifier');
                            Inc(F);
                            Continue
                          end;
                       SetLength(Args, 0);
                       If L.IsNext(LeftBracket) Then
                          begin
                            L.Check(LeftBracket);
                            If L.Error Then
                               begin
                                 Inc(F);
                                 Continue
                               end;
                            While Not (L.Error Or L.IsNext(RightBracket)) Do
                               begin
                                 SetLength(Args, Length(Args) + 1);
                                 Ref := L.IsNext(Ampersand) And L.Check(Ampersand);
                                 L.Check(Dollar);
                                 If Not L.Error Then
                                    begin
                                      If L.IsNext(Pound) And L.Check(Pound) Then
                                         begin
                                           If Ref Then
                                              begin
                                                L.MakeError('# or ## can not be passed by reference (&)');
                                                Break
                                              end;
                                           If L.IsNext(Pound) And L.Check(Pound) Then
                                              S1 := Pound + Pound
                                           Else
                                              S1 := Pound
                                         end
                                      Else
                                         S1 := L.GetIdent(False);
                                      If Ref Then
                                         Args[High(Args)] := Ampersand + Dollar + S1
                                      Else
                                         Args[High(Args)] := Dollar + S1;
                                      If Length(Args[High(Args)]) = 0 Then
                                         L.MakeError('Empty argument name in function ' + S)
                                      Else If L.IsNext(Comma) Then
                                         L.Check(Comma)
                                      Else If Not L.IsNext(RightBracket) Then
                                         L.ExpectSet([Comma, RightBracket])
                                    end
                               end;
                            L.Check(RightBracket)
                          end;
                       If (Not L.Error) And L.Check(Colon) Then
                          begin
                            S1 := TrimRight(L.AnlzLine);
                            While ((Length(S1) = 0) Or (S1[Length(S1)] <> Lexique.Point)) And (F + 1 < LL.Count) Do
                              begin
                                Inc(F);
                                AppendStr(S1, ' ' + TrimRight(TrimLeft(LL.Strings[F])))
                              end;
                            If (Length(S1) = 0) Or (S1[Length(S1)] <> Lexique.Point) Then
                               begin
                                 L.Expect(Lexique.Point);
                                 Inc(F);
                                 Continue
                               end;
                            S1 := Copy(S1, 1, Length(S1) - 1);
                            If Not CheckXPath(L, S1) Then
                               begin
                                 Inc(F);
                                 Continue
                               end;
                            ENV.AddFunction(S, Nil, true, Args, S1)
                          end;
                       Inc(F);
                       Continue
                     end;

                  If L.IsNextSet([Plus, Dash]) Then
                     Begin
                       Sign := L.AnlzLine[1];
                       L.DelFirst
                     End
                  Else
                     Sign := '+';

                  _AprP := 1.0;
                  If L.IsNext(LeftFBracket) And L.Check(LeftFBracket) Then
                     Begin
                        If L.GetNumber(False, _AprP) Then
                           L.Check(RightFBracket)
                     End;

                  If (Length(L.AnlzLine) = 0) Or (L.AnlzLine[Length(L.AnlzLine)] <> Lexique.Point) Then
                     Begin
                       L.MakeError('Expected last ''.''');
                       Inc(F);
                       Continue
                     End;

                  If L.IsNext(LeftSqrBracket) And L.Check(LeftSqrBracket) Then
                     Begin
                       S := L.GetBalancedListItem(True, [RightSqrBracket]);
                       If L.Error Then
                          begin
                            Inc(F);
                            Continue
                          end;
                       If Not CheckXPath(L, S) Then
                          begin
                            Inc(F);
                            Continue
                          end;
                       L.DelSpaces;
                       If L.IsNext(Colon) And L.Check(Colon) Then // Test
                          Begin
                            L.Check(LeftFBracket);
                            S1 := L.GetIdent(False);
                            L.Check(Comma);
                            S2 := L.GetIdent(False);
                            If L.Error Then
                               begin
                                 Inc(F);
                                 Continue
                               end;
                            If L.IsNext(Comma) And L.Check(Comma) Then
                               Begin
                                 L.CheckIdent('NOSPACES', True);
                                 If L.Error Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 _Restrictions.Add(TWeakTest.Create(S, S1, S2, True, Sign))
                               End
                            Else
                               _Restrictions.Add(TWeakTest.Create(S, S1, S2, False, Sign))
                          End
                       Else If (Copy(L.AnlzLine, 1, 2) = '=>') Or (Copy(L.AnlzLine, 1, 3) = '=>>') Then // Link
                          Begin
                            L.Check(Equal);
                            L.Check(Greater);
                            If L.IsNext(Greater) And L.Check(Greater) Then
                               _Ruler := Ruler
                            Else
                               _Ruler := Nil;
                            If L.IsNext(LeftSqrBracket) And L.Check(LeftSqrBracket) Then
                               Begin
                                 S1 := L.GetBalancedListItem(True, [RightSqrBracket]);
                                 L.Check(Lexique.Point);
                                 If L.Error Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 If Not CheckXPath(L, S1) Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 If (Pos('##', S) <> 0) Xor (Pos('##', S1) <> 0) Then
                                    _Restrictions.Add(TWeakLink.Create(S, S1, Sign, _AprP, _Ruler))
                                 Else
                                    Begin
                                      L.MakeError('Suspicious: only one of XPaths in LINK-operator must contain "##"-step');
                                      Inc(F);
                                      Continue
                                    End;
                               End
                            Else
                               Begin
                                 L.MakeError('Expected "[XPath]" after "[XPath] rel"');
                                 Inc(F);
                                 Continue
                               End
                          End
                       Else If Copy(L.AnlzLine, 1, 2) = '>>' Then // Order
                          Begin
                            L.Check(Greater);
                            L.Check(Greater);
                            If L.IsNext(LeftSqrBracket) And L.Check(LeftSqrBracket) Then
                               Begin
                                 S1 := L.GetBalancedListItem(True, [RightSqrBracket]);
                                 L.Check(Lexique.Point);
                                 If L.Error Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 If Not CheckXPath(L, S1) Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 _Restrictions.Add(TWeakOrder.Create(S, S1, Sign, _AprP));
                               End
                            Else
                               Begin
                                 L.MakeError('Expected "[XPath]" after "[XPath] rel"');
                                 Inc(F);
                                 Continue
                               End
                          End
                       Else // Relation
                          Begin
                            Op := woEqual;
                            If Copy(L.AnlzLine, 1, 2) = '>=' Then
                               Op := woGreaterEqual
                            Else If Copy(L.AnlzLine, 1, 2) = '<=' Then
                               Op := woLessEqual
                            Else If Copy(L.AnlzLine, 1, 2) = '!=' Then
                               Op := woNonEqual
                            Else If L.IsNext(Greater) Then
                               Op := woGreater
                            Else If L.IsNext(Less) Then
                               Op := woLess
                            Else If L.IsNext(Equal) Then
                               Op := woEqual
                            Else
                               Begin
                                 L.MakeError('Expected "[XPath] relation [XPath]."');
                                 Inc(F);
                                 Continue
                               End;

                            L.DelFirst;
                            If Op in [woGreaterEqual, woLessEqual, woNonEqual] Then
                               L.DelFirst;
                            If L.IsNext(LeftSqrBracket) And L.Check(LeftSqrBracket) Then
                               Begin
                                 S1 := L.GetBalancedListItem(True, [RightSqrBracket]);
                                 L.Check(Lexique.Point);
                                 If L.Error Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 If Not CheckXPath(L, S1) Then
                                    begin
                                      Inc(F);
                                      Continue
                                    end;
                                 _Restrictions.Add(TWeakRelation.Create(S, S1, Sign, Op, _AprP));
                               End
                            Else
                               Begin
                                 L.MakeError('Expected "[XPath]" after "[XPath] rel"');
                                 Inc(F);
                                 Continue
                               End
                          End
                     End
                  Else // Statement
                     Begin
                       L.AnlzLine := TrimLastSymbol(L.AnlzLine, Lexique.Point);
                       If Not CheckXPath(L, L.AnlzLine) Then
                          begin
                            Inc(F);
                            Continue
                          end;
                       _Restrictions.Add(TWeakStatement.Create(L.AnlzLine, Sign, _AprP))
                     End
                End;
             Inc(F)
           End;
     finally
       If Not Assigned(_ENV) Then
          Begin
            ENV.Export(outENV);
            ENV.Free
          End;
       Result := Not L.Error;
       L.Free;
       LL.Free;
       AllowedVersions.Free;
       CurrentVersions.Free
     end;
end;

procedure SetInterval(_Interval: Cardinal); cdecl;
begin
  Interval := _Interval;
end;

procedure ClearRestrictions; cdecl;
begin
   _Restrictions.Clear;
end;

procedure ClearRuler; cdecl;

Var F: Integer;
begin
   For F := 0 To Ruler.Count - 1 Do
     DisposeStr(PString(Ruler.Objects[F]));
   Ruler.Clear;
end;

procedure SetDeduceLogFile(LF: PChar); cdecl;
begin
   DeduceLogFile := String(LF)
end;

Var F: Integer;

Initialization
  _Restrictions := TObjList.Create;
  Ruler := TStringList.Create;
  DeduceLogFile := '';

Finalization
  FreeAndNil(_Restrictions);
  For F := 0 To Ruler.Count - 1 Do
      DisposeStr(PString(Ruler.Objects[F]));
  FreeAndNil(Ruler);

end.

