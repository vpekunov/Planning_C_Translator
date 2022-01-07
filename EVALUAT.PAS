{ (C) 1996,1999-2016 V.V.Pekunov }
{ Number Expression Evaluator    }

{$B-}
{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}
Unit Evaluat;

Interface

Uses Classes, SysUtils, Lexique;

Const MaxOpName = 5;

Const tvNumber   = 'N';

Type  ErrorCodes = (NoError,NoBalans,DivByZero);
      ErrorStr   = String[40];

Type  Operations = (opBracket,opLOr,opLAnd,opOr,opAnd,opEQ,opNonEQ,opLessEQ,opGreatEQ,opShiftRight,
                    opShiftLeft,opLess,opGreat,opPlus,opMinus,opMultiply,opDivide,opRemainder,
                    opLNot,opNot);

Type  Kinds = (knNum,knOp);

Const ErrorMsg:Array[ErrorCodes] Of ErrorStr=
      ('No errors','Expression is not balanced','Division by zero');

Type  RealType = Real;

Type  OpName = String[MaxOpName];

      TValue = class(TObject)
      Private
         FValue:RealType;
      Public
         Constructor Create(V:RealType);
         Property    Value:RealType read FValue write FValue;
      End;

      EArrayError = class(Exception);

      TSpecList = class(TStringList)
      Public
        { Public declarations }
        Procedure  Kill; virtual;
        Destructor Destroy; override;
      End;

      TOperation = Record
         Code:Operations;
         Prior:Byte
      End;
      POperation = ^TOperation;

      Oper = Record
         Name:OpName;
         Prior:Byte
      End;

      TStackItem = Record
         Kind:Kinds;
         Case Kinds Of
              knNum:(Num:RealType);
              knOp: (Oper:TOperation)
      End;

      TStackValue = class(TObject)
      Private
         FValue:TStackItem;
      Public
         Constructor Create(Const Val:TStackItem);
         Property    Value:TStackItem read FValue write FValue;
      End;

      TStack = class(TSpecList)
      Private
         CountB:Integer;
      Public
         Constructor Create;
         Function    Empty:Boolean;
         Function    GetR(Var R:TStackItem):Boolean;
         Function    GetNum(Var R:RealType):Boolean;
         Procedure   PutR(R:TStackItem);
         Procedure   PutItem(Item:Array Of Const);
         Function    GetSerial(Var R:TStackItem):Boolean;
         Procedure   ResetSerial;
      End;

      TEvaluator = class(TAnalyser)
      Private
         ErrorCode:ErrorCodes;
         Postfix:TStack;
      Public
         Constructor Create(Const NTrm,Spc:TermSet);
         Procedure   SetParams(Const S1:String;NL:Word); override;
         Function    GetError:String;
         Function    Convert(Const Separators:TermSet):Boolean;
         Function    Run(Var Rslt:RealType):Boolean;
         Function    EvalExpression(Const Separators:TermSet; Var Rslt:RealType):Boolean;
         Destructor  Destroy; override;
      End;

Const BinaryOperations:Set Of Operations =
         [opOr,opAnd,opEQ,opNonEQ,opLessEQ,opGreatEQ,opLess,
          opGreat,opShiftRight,opShiftLeft,opPlus,opMinus,opMultiply,opDivide,opRemainder,
          opLOr, opLAnd];

Const Opers:Array[Operations] Of Oper=(
      (Name:'(';    Prior:0),
      (Name:'||';   Prior:1),
      (Name:'&&';   Prior:2),
      (Name:'|';    Prior:3),
      (Name:'&';    Prior:4),
      (Name:'==';   Prior:5),
      (Name:'!=';   Prior:5),
      (Name:'<=';   Prior:6),
      (Name:'>=';   Prior:6),
      (Name:'>>';   Prior:7),
      (Name:'<<';   Prior:7),
      (Name:'<';    Prior:6),
      (Name:'>';    Prior:6),
      (Name:'+';    Prior:8),
      (Name:'-';    Prior:8),
      (Name:'*';    Prior:9),
      (Name:'/';    Prior:9),
      (Name:'%';    Prior:9),
      (Name:'!';    Prior:10),
      (Name:'~';    Prior:10)
      );

Implementation

Const ZeroStackItem: TStackItem = (Kind: knNum; Num: 0.0);

Constructor TValue.Create(V:RealType);
Begin
     Inherited Create;
     FValue:=V
End;

Procedure  TSpecList.Kill;

Var F:Integer;
Begin
     For F:=0 To Count-1 Do
         Objects[F].Free;
     Clear
End;

Destructor TSpecList.Destroy;
Begin
     Kill;
     Inherited Destroy
End;

Constructor TStackValue.Create(Const Val:TStackItem);
Begin
     Inherited Create;
     FValue:=Val
End;

Constructor TStack.Create;
Begin
     Inherited Create;
     ResetSerial
End;

Function  TStack.Empty:Boolean;
Begin
     Empty := Count=0
End;

Function  TStack.GetR(Var R:TStackItem):Boolean;

Var S:TStackValue;
Begin
     Result:=Count>0;
     If Result Then
        Begin
          S:=(Objects[Count-1]) As TStackValue;
          Delete(Count-1);
          R:=S.Value;
          S.Free
        End
End;

Function  TStack.GetNum(Var R:RealType):Boolean;

Var V:TStackItem;
Begin
     GetNum:=False;
     V := ZeroStackItem;
     If GetR(V) Then
        Case V.Kind Of
          knNum: Begin
                   R:=V.Num;
                   GetNum:=True
                 End
        End
End;

Procedure TStack.PutR(R:TStackItem);
Begin
     AddObject(IntToStr(Count),TStackValue.Create(R))
End;

Procedure TStack.PutItem(Item:Array Of Const);

Var R:TStackItem;
Begin
     With Item[0] Do
       Begin
         Case VType Of
           vtExtended:
             Begin
               R.Kind:=knNum;
               R.Num :=VExtended^
             End;
           vtBoolean:
             Begin
               R.Kind:=knNum;
               If VBoolean Then
                  R.Num:=1.0
               Else
                  R.Num:=0.0
             End;
           vtPointer:
             Begin
               R.Kind:=knOp;
               R.Oper:=POperation(VPointer)^
             End;
         Else
           Begin
             Raise
               EListError.Create('TStack.PutItem : Unknown item is pushed');
             Exit
           End
         End;
         PutR(R)
       End
End;

Function  TStack.GetSerial(Var R:TStackItem):Boolean;
Begin
     If CountB<Count Then
        Begin
          R:=(Objects[CountB] As TStackValue).Value;
          Inc(CountB);
          GetSerial:=True
        End
     Else GetSerial:=False
End;

Procedure TStack.ResetSerial;
Begin
     CountB:=0
End;

Constructor TEvaluator.Create(Const NTrm,Spc:TermSet);
Begin
     Inherited Create(NTrm,Spc);

     Postfix:=TStack.Create;
     ErrorCode:=NoError
End;

Procedure TEvaluator.SetParams(Const S1:String;NL:Word);
Begin
     Inherited SetParams(S1,NL);
     Postfix.Kill;
     ErrorCode:=NoError
End;

Function TEvaluator.GetError:String;
Begin
     GetError:=ErrorMsg[ErrorCode];
     ErrorCode:=NoError
End;

Function  TEvaluator.Convert(Const Separators:TermSet):Boolean;

Var Prom:TStack;

Function Main:Boolean;

Function PutNum:Boolean;

Var Str:String;
    V:RealType;
    K:Integer;
Begin {PutNum}
     PutNum:=False;
     If IsNextSet(NumberSet) Then
        Begin
          Str:=FindNumber;
          Val(Str,V,K);
          If K=0 Then
             Begin
               Delete(S,1,Length(Str));
               Prom.PutItem([V]);
               PutNum:=True
             End
          Else
            MakeError('Incorrect number : '+Str)
        End
End;  {PutNum}

Function PutOper:Boolean;

Var F:Operations;
    K:Integer;
    Flag:Boolean;
    P:TOperation;
Begin {PutOper}
     DelSpaces;
     Flag:=False;
     For F:=Low(Operations) To High(Operations) Do
         Begin
           K:=Length(Opers[F].Name);
           If Length(S)>=K Then
              Flag:=UpperCase(Copy(S,1,K))=Opers[F].Name;
           If Flag Then
              Begin
                P.Prior:=Opers[F].Prior;
                P.Code:=F;
                Break
              End
         End;
     If Flag Then
        Begin
          Prom.PutItem([@P]);
          Delete(S,1,K)
        End;
     PutOper:=Flag
End; {PutOper}

Function CheckBracket(Var BracketLevel:Integer;Right:Char;Left:Operations):Boolean;

Var K:TStackItem;
Begin
     Result:=IsNext(Right);
     If Result Then
        Begin
          Dec(BracketLevel);
          K := ZeroStackItem;
          If Prom.GetR(K) Then
             Begin
               While Not ((K.Kind=knOp) And (K.Oper.Code=Left)) Do
                 Begin
                   Postfix.PutR(K);
                   If Not Prom.GetR(K) Then Exit
                 End
             End
          Else
            Begin
              ErrorCode:=NoBalans;
              Exit
            End;
          DelFirst
        End
End;

Var BracketLevel:Integer;
    K,K1:TStackItem;
    Flag:Boolean;
Begin {Main}
     Main:=False;
     BracketLevel:=0;
     K := ZeroStackItem;
     K1 := ZeroStackItem;
     While Not ((ErrorCode<>NoError) Or Empty Or ((BracketLevel=0) And IsNextSet(Separators))) Do
       If Not CheckBracket(BracketLevel,RightBracket,opBracket) Then
           If Not PutNum Then
              If PutOper Then
                 If Prom.GetR(K) Then
                    Begin
                      If K.Oper.Code=opBracket Then
                         Inc(BracketLevel)
                      Else
                         Begin
                            Flag:=Not Prom.Empty;
                            If Prom.GetR(K1) Then
                               While Flag And Not ((K1.Kind=knOp) And (K1.Oper.Prior<K.Oper.Prior)) Do
                                 Begin
                                   Postfix.PutR(K1);
                                   If Not Prom.GetR(K1) Then Flag:=False
                                 End;
                            If Flag Then Prom.PutR(K1)
                         End;
                      Prom.PutR(K)
                    End
                 Else Exit
              Else Exit;
     If ErrorCode=NoError Then
        Begin
          While Prom.GetR(K) Do
            Postfix.PutR(K);
          Main:=True
        End
End;  {Main}

Begin {Convert}
     ErrorCode:=NoError;
     Postfix.Kill;
     DelSpaces;
     Prom:=TStack.Create;
     Result:=Main;
     Prom.Free;
     If Not Result Then
        Begin
          ErrorCode:=NoBalans;
          MakeError(GetError)
        End
End;  {Convert}

Function  TEvaluator.Run(Var Rslt:RealType):Boolean;

Var Runer:TStack;
    K:TStackItem;
    P,P1:RealType;
    Flag:Boolean;
Begin
     Postfix.ResetSerial;
     Runer:=TStack.Create;
     Flag:=Not Error;
     ErrorCode:=NoBalans;
     K := ZeroStackItem;
     P := 0.0;
     P1 := 0.0;
     While Postfix.GetSerial(K) Do
       If Flag Then
          Case K.Kind Of
            knNum: Runer.PutR(K);
            knOp:
             Begin
               Flag:=Runer.GetNum(P);
               If Flag Then
                  Begin
                    If K.Oper.Code In BinaryOperations Then
                       Flag:=Runer.GetNum(P1);
                    If Flag Then
                       Case K.Oper.Code Of
                         opLOr:
                           Runer.PutItem([(Abs(P)>1E-8) Or (Abs(P1)>1E-8)]);
                         opLAnd:
                           Runer.PutItem([(Abs(P)>1E-8) And (Abs(P1)>1E-8)]);
                         opOr:
                           Runer.PutItem([1.0*(Round(Int(P)) Or Round(Int(P1)))]);
                         opAnd:
                           Runer.PutItem([1.0*(Round(Int(P)) And Round(Int(P1)))]);
                         opEQ:       Runer.PutItem([P1=P]);
                         opNonEQ:    Runer.PutItem([P1<>P]);
                         opLessEQ:   Runer.PutItem([P1<=P]);
                         opGreatEQ:  Runer.PutItem([P1>=P]);
                         opLess:     Runer.PutItem([P1<P]);
                         opGreat:    Runer.PutItem([P1>P]);
                         opShiftRight: Runer.PutItem([1.0*(Round(Int(P1)) Shr Round(Int(P)))]);
                         opShiftLeft: Runer.PutItem([1.0*(Round(Int(P1)) Shl Round(Int(P)))]);
                         opPlus:     Runer.PutItem([P1+P]);
                         opMinus:    Runer.PutItem([P1-P]);
                         opMultiply: Runer.PutItem([P1*P]);
                         opDivide:
                           Begin
                             Flag:=P<>0;
                             If Flag Then Runer.PutItem([P1/P])
                             Else ErrorCode:=DivByZero
                           End;
                         opRemainder:
                           Begin
                             Flag:=P<>0;
                             If Flag Then Runer.PutItem([1.0*(Round(Int(P1)) Mod Round(Int(P)))])
                             Else ErrorCode:=DivByZero
                           End;
                         opLNot: Runer.PutItem([Not (Abs(P)>1E-8)]);
                         opNot: Runer.PutItem([1.0*(Not Round(Int(P)))]);
                         Else
                           Flag:=False
                       End
                  End
             End
          End;
     If Flag Then
        Flag:=Runer.GetNum(Rslt);
     Flag:=Flag And Runer.Empty;
     Runer.Free;
     If Flag Then
        ErrorCode:=NoError
     Else
        MakeError(GetError);
     Run:=Flag
End;

Function    TEvaluator.EvalExpression(Const Separators:TermSet;Var Rslt:RealType):Boolean;
Begin
     Result:=(Not Error) And Convert(Separators) And Run(Rslt)
End;

Destructor  TEvaluator.Destroy;
Begin
     PostFix.Free;
     Inherited Destroy
End;

End.

