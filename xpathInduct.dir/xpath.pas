{
    This file is part of the Free Component Library

    Implementation of the XML Path Language (XPath) for Free Pascal
    Copyright (c) 2000 - 2003 by
      Areca Systems GmbH / Sebastian Guenther, sg@freepascal.org

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ Modified by V.V.Pekunov, 2019 }

{$MODE objfpc}
{$H+}

unit XPath;

interface

uses SysUtils, Classes, DOM;

resourcestring
  { XPath variables type names }
  SNodeSet = 'node set';
  SBoolean = 'boolean';
  SNumber = 'number';
  SString = 'string';

  { Variable errors }
  SVarNoConversion = 'Conversion from %s to %s not possible';

  { Scanner errors }
  SScannerUnclosedString = 'String literal was not closed';
  SScannerInvalidChar = 'Invalid character';
  SScannerMalformedQName = 'Expected "*" or local part after colon';
  SScannerExpectedVarName = 'Expected variable name after "$"';

  { Parser errors }
  SParserExpectedLeftBracket = 'Expected "("';
  SParserExpectedRightBracket = 'Expected ")"';
  SParserBadAxisName = 'Invalid axis name';
  SParserBadNodeType = 'Invalid node type';
  SParserExpectedRightSquareBracket = 'Expected "]" after predicate';
  SParserInvalidPrimExpr = 'Invalid primary expression';
  SParserGarbageAfterExpression = 'Unrecognized input after expression';
  SParserInvalidNodeTest = 'Invalid node test (syntax error)';


  { Evaluation errors }
  SEvalUnknownFunction = 'Unknown function: "%s"';
  SEvalUnknownVariable = 'Unknown variable: "%s"';
  SEvalInvalidArgCount = 'Invalid number of function arguments';
  SEvalInvalidExtArgCount = 'Invalid number of function [%s] arguments';
  SEvalNotVarByRef = 'Attempt to pass by reference a non-variable (function ''%s'', argument ''%s''';
  SEvalNestedTransaction = 'Nested transactions are not allowed';
  SEvalCommitNoTransaction = 'Attempt to commit but there is no active transaction';
  SEvalRollbackNoTransaction = 'Attempt to rollback but there is no active transaction';
  SEvalPassedInvalidSet = 'function %s: Attempt to pass an invalid set (length is not equal to 1) into %s';
  SEvalPassedNonSet = 'function %s: Attempt to pass a non-set value into %s';

type

  TXPathContext = class;
  TXPathEnvironment = class;
  TXPathVariable = class;


{ XPath lexical scanner }

  TXPathToken = (               // [28] - [38]
    tkInvalid,
    tkEndOfStream,
    tkIdentifier,
    tkNSNameTest,               // NCName:*
    tkString,
    tkNumber,
    tkVariable,                 // $QName
    tkLeftBracket,              // "("
    tkRightBracket,             // ")"
    tkAsterisk,                 // "*"
    tkPlus,                     // "+"
    tkComma,                    // ","
    tkMinus,                    // "-"
    tkDot,                      // "."
    tkDotDot,                   // ".."
    tkSlash,                    // "/"
    tkSlashSlash,               // "//"
    tkColonColon,               // "::"
    tkLess,                     // "<"
    tkLessEqual,                // "<="
    tkEqual,                    // "="
    tkNotEqual,                 // "!="
    tkGreater,                  // ">"
    tkGreaterEqual,             // ">="
    tkAt,                       // "@"
    tkLeftSquareBracket,        // "["
    tkRightSquareBracket,       // "]"
    tkPipe,                     // "|"
    tkPound,                    // "#"
    tkPoundPound,               // "##"
    tkPound3                    // "###"
  );

  TXPathKeyword = (
    // axis names
    xkNone, xkAncestor,  xkAncestorOrSelf,  xkAttribute,  xkChild,
    xkDescendant, xkDescendantOrSelf, xkFollowing, xkFollowingSibling,
    xkNamespace, xkParent, xkPreceding, xkPrecedingSibling, xkSelf,
    // node tests
    xkComment, xkText, xkProcessingInstruction, xkNode,
    // operators
    xkAnd, xkOr, xkDiv, xkMod,
    // standard functions
    xkLast, xkPosition, xkCount, xkId, xkLocalName, xkNamespaceUri,
    xkName, xkString, xkConcat, xkStartsWith, xkContains,
    xkSubstringBefore, xkSubstringAfter, xkSubstring,
    xkStringLength, xkNormalizeSpace, xkTranslate, xkBoolean,
    xkNot, xkTrue, xkFalse, xkLang, xkNumber, xkSum, xkFloor,
    xkCeiling, xkRound
  );

  { TXMLVarsList }

  TXMLVarsList = class(TStringList)
  public
    destructor Destroy; override;

    function Mul(Arg: TXMLVarsList): TXMLVarsList;
    function Add(Arg: TXMLVarsList): TXMLVarsList;
  end;

{ XPath expression parse tree }

  TXPathNodeNameTester = function(Const NodeName, NodeTestString: PChar): Boolean; cdecl;

  TXPathExprNode = class
  protected
    function EvalPredicate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): Boolean;
  public
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; virtual; abstract;
  end;

  TXPathNodeArray = array of TXPathExprNode;

  TXPathConstantNode = class(TXPathExprNode)
  private
    FValue: TXPathVariable;
  public
    constructor Create(AValue: TXPathVariable);
    destructor Destroy; override;
    function Evaluate(AContext: TXPathContext;
       AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  TXPathVariableNode = class(TXPathExprNode)
  private
    FName: DOMString;
  public
    constructor Create(const AName: DOMString);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  { TXPathFunctionNode }

  TXPathFunctionNode = class(TXPathExprNode)
  private
    FName: DOMString;
    FArgs: TXPathNodeArray;
    function GetArg(i: Integer): TXPathExprNode;
    function GetArgsCount: Integer;
  public
    constructor Create(const AName: DOMString; const Args: TXPathNodeArray);
    destructor Destroy; override;
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;

    property ArgsCount: Integer read GetArgsCount;
    property ArgNodes[i: Integer]: TXPathExprNode read GetArg;
  end;


  TXPathNegationNode = class(TXPathExprNode)
  private
    FOperand: TXPathExprNode;
  public
    constructor Create(AOperand: TXPathExprNode);
    destructor Destroy; override;
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;

  // common ancestor for binary operations

  TXPathBinaryNode = class(TXPathExprNode)
  protected
    FOperand1, FOperand2: TXPathExprNode;
  public
    destructor Destroy; override;   
  end;

  // Node for (binary) mathematical operation

  TXPathMathOp = (opAdd, opSubtract, opMultiply, opDivide, opMod);

  TXPathMathOpNode = class(TXPathBinaryNode)
  private
    FOperator: TXPathMathOp;
  public
    constructor Create(AOperator: TXPathMathOp;
      AOperand1, AOperand2: TXPathExprNode);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;

  // Node for comparison operations

  TXPathCompareOp = (opEqual, opNotEqual, opLess, opLessEqual, opGreater,
    opGreaterEqual);

  TXPathCompareNode = class(TXPathBinaryNode)
  private
    FOperator: TXPathCompareOp;
  public
    constructor Create(AOperator: TXPathCompareOp;
      AOperand1, AOperand2: TXPathExprNode);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  // Node for boolean operations (and, or)

  TXPathBooleanOp = (opOr, opAnd);

  TXPathBooleanOpNode = class(TXPathBinaryNode)
  private
    FOperator: TXPathBooleanOp;
  public
    constructor Create(AOperator: TXPathBooleanOp;
      AOperand1, AOperand2: TXPathExprNode);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  // Node for unions (see [18])

  TXPathUnionNode = class(TXPathBinaryNode)
  public
    constructor Create(AOperand1, AOperand2: TXPathExprNode);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  TNodeSet = TFPList;

  // Filter node (for [20])

  TXPathFilterNode = class(TXPathExprNode)
  private
    FLeft: TXPathExprNode;
    FPredicates: TXPathNodeArray;
    procedure ApplyPredicates(Parent: TDOMNode; Nodes: TNodeSet; AEnvironment: TXPathEnvironment; const Ptrs: array of TDOMNode; const Construct: TNodeSet);
  public
    constructor Create(AExpr: TXPathExprNode);
    destructor Destroy; override;
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;


  // Node for location paths

  TAxis = (axisInvalid, axisAncestor, axisAncestorOrSelf, axisAttribute,
    axisChild, axisDescendant, axisDescendantOrSelf, axisFollowing,
    axisFollowingSibling, axisNamespace, axisParent, axisPreceding,
    axisPrecedingSibling, axisSelf, axisRoot, axisPartner, axisContact, axisBase);

  TNodeTestType = (ntAnyPrincipal, ntName, ntTextNode,
    ntCommentNode, ntPINode, ntAnyNode);

  TStep = class(TXPathFilterNode)
  private
    procedure SelectNodes(ANode: TDOMNode; const Ptrs: array of TDOMNode; const Construct: TNodeSet; NodeNameTester: TXPathNodeNameTester; out ResultNodes: TNodeSet);
  public
    Axis: TAxis;
    NodeTestType: TNodeTestType;
    NodeTestString: DOMString;
    NSTestString: DOMString;
    constructor Create(aAxis: TAxis; aTest: TNodeTestType);
    function Evaluate(AContext: TXPathContext;
      AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable; override;
  end;

{ Exceptions }

  EXPathEvaluationError = class(Exception);

  procedure EvaluationError(const Msg: String);
  procedure EvaluationError(const Msg: String; const Args: array of const);


type

{ XPath variables and results classes }

  { TXPathVariable }

  TXPathVariable = class
  protected
    FRefCount: Integer;
    FBound: Boolean;
    procedure Error(const Msg: String; const Args: array of const);
  public
    class function TypeName: String; virtual; abstract;
    function IsBound: Boolean;
    procedure MarkPolled; virtual;
    procedure Release;
    function Clone: TXPathVariable; virtual; abstract;
    function AsNodeSet: TNodeSet; virtual;
    function AsBoolean: Boolean; virtual; abstract;
    function AsNumber: Extended; virtual; abstract;
    function AsText: DOMString; virtual; abstract;
    function Export: DOMString; virtual; abstract;
    class function Import(Const From: String): TXPathVariable;
  end;

  { TXPathNodeSetVariable }

  TXPathNodeSetVariable = class(TXPathVariable)
  private
    FValue: TNodeSet;
  public
    constructor Create(AValue: TNodeSet; Const bound: Boolean = True);
    destructor Destroy; override;
    procedure MarkPolled; override;
    class function TypeName: String; override;
    function Clone: TXPathVariable; override;
    function AsNodeSet: TNodeSet; override;
    function AsText: DOMString; override;
    function AsBoolean: Boolean; override;
    function AsNumber: Extended; override;
    property Value: TNodeSet read FValue;
    function Export: DOMString; override;
  end;

  { TXPathBooleanVariable }

  TXPathBooleanVariable = class(TXPathVariable)
  private
    FValue: Boolean;
  public
    constructor Create(AValue: Boolean; Const bound: Boolean = True);
    class function TypeName: String; override;
    function Clone: TXPathVariable; override;
    function AsBoolean: Boolean; override;
    function AsNumber: Extended; override;
    function AsText: DOMString; override;
    property Value: Boolean read FValue;
    function Export: DOMString; override;
  end;

  { TXPathNumberVariable }

  TXPathNumberVariable = class(TXPathVariable)
  private
    FValue: Extended;
  public
    constructor Create(AValue: Extended; Const bound: Boolean = True);
    class function TypeName: String; override;
    function Clone: TXPathVariable; override;
    function AsBoolean: Boolean; override;
    function AsNumber: Extended; override;
    function AsText: DOMString; override;
    property Value: Extended read FValue;
    function Export: DOMString; override;
  end;

  { TXPathStringVariable }

  TXPathStringVariable = class(TXPathVariable)
  private
    FValue: DOMString;
  public
    constructor Create(const AValue: DOMString; Const bound: Boolean = True);
    class function TypeName: String; override;
    function Clone: TXPathVariable; override;
    function AsBoolean: Boolean; override;
    function AsNumber: Extended; override;
    function AsText: DOMString; override;
    property Value: DOMString read FValue;
    function Export: DOMString; override;
  end;

  TXPathNSResolver = class
  protected
    FNode: TDOMNode;
  public
    constructor Create(aNode: TDOMNode);
    function LookupNamespaceURI(const aPrefix: DOMString): DOMString; virtual;
  end;

{ XPath lexical scanner }

  TXPathScanner = class
  private
    FExpressionString, FCurData: DOMPChar;
    FCurToken: TXPathToken;
    FCurTokenString: DOMString;
    FTokenStart: DOMPChar;
    FTokenLength: Integer;
    FPrefixLength: Integer;
    FTokenId: TXPathKeyword;
    FResolver: TXPathNSResolver;
    procedure Error(const Msg: String);
    procedure ParsePredicates(var Dest: TXPathNodeArray);
    function ParseStep: TStep;          // [4]
    function ParseNodeTest(axis: TAxis): TStep; // [7]
    function ParsePrimaryExpr: TXPathExprNode; // [15]
    function ParseFunctionCall: TXPathExprNode; // [16]
    function ParseUnionExpr: TXPathExprNode;   // [18]
    function ParsePathExpr: TXPathExprNode;    // [19]
    function ParseFilterExpr: TXPathExprNode;  // [20]
    function ParseAndExpr: TXPathExprNode;     // [22]
    function ParseEqualityExpr: TXPathExprNode;    // [23]
    function ParseRelationalExpr: TXPathExprNode;  // [24]
    function ParseAdditiveExpr: TXPathExprNode;    // [25]
    function ParseMultiplicativeExpr: TXPathExprNode;  // [26]
    function ParseUnaryExpr: TXPathExprNode;   // [27]
    function GetToken: TXPathToken;
    function ScanQName: Boolean;
  public
    constructor Create(const AExpressionString: DOMString);

    function ParseOrExpr: TXPathExprNode;      // [21]

    function NextToken: TXPathToken;
    function PeekToken: TXPathToken;
    function SkipToken(tok: TXPathToken): Boolean;
    property ExpressionString: DOMPChar read FExpressionString;
    property CurToken: TXPathToken read FCurToken;
    property CurTokenString: DOMString read FCurTokenString;
  end;


{ XPath context }

  TXPathContext = class
  public
    ContextNode: TDOMNode;
    ContextPosition: Integer;
    ContextSize: Integer;

    Ptrs: Array Of TDOMNode;
    Construct: TNodeSet;

    constructor Create(AContextNode: TDOMNode;
      AContextPosition, AContextSize: Integer; const _Ptrs: array of TDOMNode; const _Construct: TNodeSet);
  end;


{ XPath environments (not defined in XPath standard: an environment contains
  the variables and functions, which are part of the context in the official
  standard). }

  TXPathVarList = TFPList;

  TXPathFunction = function(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList):
    TXPathVariable of object;

  { TXPathEnvironment }

  PFunctionInfo = ^TFunctionInfo;
  TFunctionInfo = record
    Name: String;
    ArgNames: Array Of String;
    ArgRefs: Array Of Boolean;
    Body: String;
    Fn: TXPathFunction;
    EvalArgs: Boolean
  end;

  PUndoInfo = ^TUndoInfo;
  TUndoInfo = record
    Inserted: Boolean;
    ParentNode: TDOMNode;
    ThisNode: TDOMNode;
    NextNode: TDOMNode
  end;

  TXPathEnvironment = class
  private
    FFunctions: TFPList;
    FVariables: TFPList;
    FVariablesStack: TList;
    FUndoStack: TFPList;
    FTransaction: Integer;
    FNodeNameTester: TXPathNodeNameTester;
    FCollectedWords: TStringList;
    FLocalWords : TStringList;
    FCollectedRels: TStringList;
    FLocalRels : TStringList;
    FGID: Integer;
    function GetFunctionCount: Integer;
    function GetVariableCount: Integer;
    function GetFunction(Index: Integer): PFunctionInfo;
    function GetFunction(const AName: String): PFunctionInfo;
    function GetVariable(Index: Integer): TXPathVariable;
    function GetVariable(const AName: String): TXPathVariable;
    procedure SetVariable(Index: Integer; Const Val: TXPathVariable);
    procedure SetVariable(const AName: String; Const Val: TXPathVariable);
  protected
    // Special functions
    function spEval(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spMin(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spMax(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spTransaction(AContext: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spSet(AContext: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spCreate(AContext: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function spDelete(AContext: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    // XPath Core Function Library:
    function xpLast(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpPosition(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpCount(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpId(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpLocalName(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpNamespaceURI(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpName(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpString(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpConcat(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpStartsWith(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpContains(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpSubstringBefore(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpSubstringAfter(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpSubstring(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpStringLength(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpNormalizeSpace(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpTranslate(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpBoolean(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpNot(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpTrue(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpFalse(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpLang(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpNumber(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpSum(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpFloor(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpCeiling(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpRound(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpGID(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpRandom(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
    function xpRandomID(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
  public
    constructor Create;
    destructor Destroy; override;
    procedure setGID(GID: Integer);
    function   Clone: TXPathEnvironment;
    procedure startTransaction;
    procedure commitTransaction;
    procedure rollbackTransaction(Const Construct: TNodeSet);
    procedure pushUndo(Inserted: Boolean; ThisNode, NextNode, ParentNode: TDOMNode);
    function  getUndoLabel: Integer;
    procedure commitUndo(ToLabel: Integer);
    procedure rollbackUndo(ToLabel: Integer; Const Construct: TNodeSet);
    procedure pushVariables; virtual;
    procedure popVariables; virtual;
    function GetFunctionIndex(const AName: String): Integer;
    function GetVariableIndex(const AName: String): Integer;
    procedure AddFunction(const AName: String; AFunction: TXPathFunction; EvalArgs: Boolean; Const Args: Array Of String; Const Body: String = '');
    procedure AddVariable(const AName: String; AVariable: TXPathVariable; Const local: Boolean = False);
    procedure RemoveFunction(Index: Integer);
    procedure RemoveFunction(const AName: String);
    procedure RemoveVariable(Index: Integer);
    procedure RemoveVariable(const AName: String);
    procedure AcceptLocalWordsRels;
    procedure Export(outS: PChar);
    procedure Import(inS: PChar);
    property FunctionCount: Integer read GetFunctionCount;
    property VariableCount: Integer read GetVariableCount;
    property Functions[Index: Integer]: PFunctionInfo read GetFunction;
    property FunctionsByName[const AName: String]: PFunctionInfo
       read GetFunction;
    property Variables[Index: Integer]: TXPathVariable read GetVariable write SetVariable;
    property VariablesByName[const AName: String]: TXPathVariable read GetVariable write SetVariable;
    property NodeNameTester: TXPathNodeNameTester read FNodeNameTester write FNodeNameTester;
    property LocalWords: TStringList read FLocalWords;
    property CollectedWords: TStringList read FCollectedWords;
    property LocalRels: TStringList read FLocalRels;
    property CollectedRels: TStringList read FCollectedRels;
  end;


{ XPath expressions }

  TXPathExpression = class
  private
    FRootNode: TXPathExprNode;
  public
    { CompleteExpresion specifies wether the parser should check for gargabe
      after the recognised part. True => Throw exception if there is garbage }
    constructor Create(AScanner: TXPathScanner; CompleteExpression: Boolean;
      AResolver: TXPathNSResolver = nil);
    destructor Destroy; override;
    function Evaluate(AContextNode: TDOMNode; NodeNameTester: TXPathNodeNameTester; const Ptrs: array of TDOMNode; const Construct: TNodeSet): TXPathVariable;
    function Evaluate(AContextNode: TDOMNode;
      AEnvironment: TXPathEnvironment; const Ptrs: array of TDOMNode; const Construct: TNodeSet): TXPathVariable;
  end;


function EvaluateXPathExpression(const AExpressionString: DOMString;
  AContextNode: TDOMNode; NodeNameTester: TXPathNodeNameTester;
  const Ptrs: array of TDOMNode; const Construct: TNodeSet = Nil;
  AResolver: TXPathNSResolver = nil;
  AEnv: TXPathEnvironment = Nil): TXPathVariable;


// ===================================================================
// ===================================================================

implementation

uses {$IF (NOT DEFINED(UNIX)) AND (NOT DEFINED(LINUX))}Windows, {$ELSE}CThreads, {$ENDIF}Math, xmlutils, Common, syncobjs;

{$i xpathkw.inc}

Const BoolVals:Array[Boolean] Of PChar = ('False','True');

Var Cache: TObjStrList;
    CS: TRTLCriticalSection;

const
  AxisNameKeywords = [xkAncestor..xkSelf];
  AxisNameMap: array[xkAncestor..xkSelf] of TAxis = (
    axisAncestor, axisAncestorOrSelf, axisAttribute, axisChild,
    axisDescendant, axisDescendantOrSelf, axisFollowing,
    axisFollowingSibling, axisNamespace, axisParent, axisPreceding,
    axisPrecedingSibling, axisSelf
  );
  NodeTestKeywords = [xkComment..xkNode];
  NodeTestMap: array[xkComment..xkNode] of TNodeTestType = (
    ntCommentNode, ntTextNode, ntPINode, ntAnyNode
  );

  FunctionKeywords = [xkLast..xkRound];

{ Helper functions }

function EscapeCRLF(Const Txt: String): String;
Begin
  With TStringList.Create Do
    Begin
      Text := Txt;
      Result := CommaText;
      Free
    End
End;

function UnEscapeCRLF(Const Txt: String): String;
Begin
  With TStringList.Create Do
    Begin
      CommaText := Txt;
      Result := Text;
      Free
    End
End;

function NodeToText(Node: TDOMNode): DOMString;
var
  Child: TDOMNode;
begin
  case Node.NodeType of
    DOCUMENT_NODE, DOCUMENT_FRAGMENT_NODE{, ELEMENT_NODE}:
      begin
        SetLength(Result, 0);
        Child := Node.FirstChild;
        while Assigned(Child) do
        begin
	  if Result <> '' then
	    Result := Result + LineEnding;
          Result := Result + NodeToText(Child);
          Child := Child.NextSibling;
        end;
      end;
    ELEMENT_NODE:
      Result := Node.TextContent;
    ATTRIBUTE_NODE, PROCESSING_INSTRUCTION_NODE, COMMENT_NODE, TEXT_NODE,
      CDATA_SECTION_NODE, ENTITY_REFERENCE_NODE:
      Result := Node.NodeValue;
  end;
  // !!!: What to do with 'namespace nodes'?
end;

function StrToNumber(const s: DOMString): Extended;
var
  Code: Integer;
begin
  Val(s, Result, Code);
{$push}
{$r-,q-}
  if Code <> 0 then
    Result := NaN;
{$pop}
end;

procedure TranslateWideString(var S: DOMString; const SrcPat, DstPat: DOMString);
var
  I, J, L: Integer;
  P, Start: DOMPChar;
begin
  UniqueString(S);
  L := Length(DstPat);
  P := DOMPChar(S);
  if Length(SrcPat) > L then  // may remove some chars
  begin
    Start := P;
    for I := 1 to Length(S) do
    begin
      J := Pos(S[I], SrcPat);
      if J > 0 then
      begin
        if J <= L then
        begin
          P^ := DstPat[J];
          Inc(P);
        end;
      end
      else
      begin
        P^ := S[I];
        Inc(P);
      end;
    end;
    SetLength(S, P-Start);
  end
  else  // no char removal possible
    for I := 1 to Length(S) do
    begin
      J := Pos(S[I], SrcPat);
      if J > 0 then
        P^ := DstPat[J]
      else
        P^ := S[I];
      Inc(P);  
    end;
end;

function GetNodeLanguage(aNode: TDOMNode): DOMString;
var
  Attr: TDomAttr;
begin
  Result := '';
  if aNode = nil then
    Exit;
  case aNode.NodeType of
    ELEMENT_NODE: begin
      Attr := TDomElement(aNode).GetAttributeNode('xml:lang');
      if Assigned(Attr) then
        Result := Attr.Value
      else
        Result := GetNodeLanguage(aNode.ParentNode);
    end;
    TEXT_NODE, CDATA_SECTION_NODE, ENTITY_REFERENCE_NODE,
    PROCESSING_INSTRUCTION_NODE, COMMENT_NODE:
      Result := GetNodeLanguage(aNode.ParentNode);
    ATTRIBUTE_NODE:
      Result := GetNodeLanguage(TDOMAttr(aNode).OwnerElement);
  end;
end;

procedure AddNodes(var Dst: TXPathNodeArray; const Src: array of TXPathExprNode;
  var Count: Integer);
var
  L: Integer;
begin
  if Count > 0 then
  begin
    L := Length(Dst);
    SetLength(Dst, L + Count);
    Move(Src[0], Dst[L], Count*sizeof(TObject));
    Count := 0;
  end;
end;

{ TXMLVarsList }

destructor TXMLVarsList.Destroy;

Var I: Integer;
begin
  For I := 0 To Count - 1 Do
      Objects[I].Free;
  inherited Destroy
end;

function TXMLVarsList.Mul(Arg: TXMLVarsList): TXMLVarsList;

Var I, J: Integer;
    R: TStringList;
begin
  Result := TXMLVarsList.Create;
  If (Not Assigned(Arg)) Or (Arg.Count = 0) Then
     For I := 0 To Count - 1 Do
         begin
           R := TStringList.Create;
           R.Assign(TStringList(Objects[I]));
           Result.AddObject('', R)
         end
  Else If Count = 0 Then
      For I := 0 To Arg.Count - 1 Do
          begin
            R := TStringList.Create;
            R.Assign(TStringList(Arg.Objects[I]));
            Result.AddObject('', R)
          end
  Else
     If Assigned(Arg) Then
       For I := 0 To Count - 1 Do
           For J := 0 To Arg.Count - 1 do
               begin
                 R := TStringList.Create;
                 R.Assign(TStringList(Objects[I]));
                 R.AddStrings(TStringList(Arg.Objects[J]));
                 Result.AddObject('', R)
               end
end;

function TXMLVarsList.Add(Arg: TXMLVarsList): TXMLVarsList;

Var I: Integer;
    R: TStringList;
begin
  Result := TXMLVarsList.Create;
  For I := 0 To Count - 1 Do
      begin
        R := TStringList.Create;
        R.Assign(TStringList(Objects[I]));
        Result.AddObject('', R)
      end;
  If Assigned(Arg) Then
    For I := 0 To Arg.Count - 1 Do
        begin
          R := TStringList.Create;
          R.Assign(TStringList(Arg.Objects[I]));
          Result.AddObject('', R)
        end
end;

{ XPath parse tree classes }

function TXPathExprNode.EvalPredicate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): Boolean;
var
  resvar: TXPathVariable;
begin
  resvar := Evaluate(AContext, AEnvironment, Variants);
  try
    if resvar.InheritsFrom(TXPathNumberVariable) then
      Result := resvar.AsNumber = AContext.ContextPosition   // TODO: trunc/round?
    else
      Result := resvar.AsBoolean;
  finally
    resvar.Release;
  end;
end;

constructor TXPathConstantNode.Create(AValue: TXPathVariable);
begin
  inherited Create;
  FValue := AValue;
end;

destructor TXPathConstantNode.Destroy;
begin
  FValue.Release;
  inherited Destroy;
end;

function TXPathConstantNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
begin
  Result := FValue.Clone;
  // Inc(Result.FRefCount);
  Variants := TXMLVarsList.Create
end;


constructor TXPathVariableNode.Create(const AName: DOMString);
begin
  inherited Create;
  FName := AName;
end;

function TXPathVariableNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
begin
  Result := AEnvironment.VariablesByName[FName];
  Variants := TXMLVarsList.Create;
  if not Assigned(Result) then
     // EvaluationError(SEvalUnknownVariable, [FName]);
     begin
       AEnvironment.AddVariable(FName, TXPathStringVariable.Create('', False), True);
       Result := Evaluate(AContext, AEnvironment, Variants)
     end
  else
     Result := Result.Clone
end;

function TXPathFunctionNode.GetArg(i: Integer): TXPathExprNode;
begin
  Result := FArgs[i]
end;

function TXPathFunctionNode.GetArgsCount: Integer;
begin
  Result := Length(FArgs)
end;

constructor TXPathFunctionNode.Create(const AName: DOMString; const Args: TXPathNodeArray);
begin
  inherited Create;
  FName := AName;
  FArgs := Args;
end;

destructor TXPathFunctionNode.Destroy;
var
  i: Integer;
begin
  for i := Low(FArgs) to High(FArgs) do
    FArgs[i].Free;
  inherited Destroy;
end;

function TXPathFunctionNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  Fn: PFunctionInfo;
  Args: TXPathVarList;
  PPtrs: Array Of TDOMNode;
  Changed: TStringList;
  R: TXMLVarsList;
  i: Integer;
begin
  Fn := AEnvironment.FunctionsByName[FName];
  Variants := TXMLVarsList.Create;
  if not (Assigned(Fn)) then
     EvaluationError(SEvalUnknownFunction, [FName]);

  If Length(Fn^.Body) = 0 Then
     If Fn^.EvalArgs Then
        Try
          Args := TXPathVarList.Create;
          for i := Low(FArgs) to High(FArgs) do
            begin
              Args.Add(FArgs[i].Evaluate(AContext, AEnvironment, R));
              R.Free
            end;
          Result := Fn^.Fn(AContext, Self, Args);
          for i := Low(FArgs) to High(FArgs) do
              TXPathVariable(Args[i]).Release;
        finally
          Args.Free
        end
     Else
        Result := Fn^.Fn(AContext, Self, Nil)
  Else
     Begin
       If Length(FArgs) <> Length(Fn^.ArgNames) Then
          EvaluationError(SEvalInvalidExtArgCount, [FName]);
       Args := TXPathVarList.Create;
       try
         for i := Low(FArgs) to High(FArgs) do
             begin
               Args.Add(FArgs[i].Evaluate(AContext, AEnvironment, R));
               R.Free
             end;
         SetLength(PPtrs, 3);
         PPtrs[2] := AContext.ContextNode;
         AEnvironment.pushVariables;
         for i := Low(Fn^.ArgNames) To High(Fn^.ArgNames) Do
           If (Fn^.ArgNames[i] = '#') Or (Fn^.ArgNames[i] = '##') Then
              If TObject(Args.Items[i]) is TXPathNodeSetVariable Then
                 If TXPathNodeSetVariable(Args.Items[i]).AsNodeSet.Count = 1 Then
                    If Fn^.ArgNames[i] = '#' Then
                       PPtrs[0] := TDOMNode(TXPathNodeSetVariable(Args.Items[i]).AsNodeSet.Items[0])
                    Else
                       PPtrs[1] := TDOMNode(TXPathNodeSetVariable(Args.Items[i]).AsNodeSet.Items[0])
                 Else
                    EvaluationError(SEvalPassedInvalidSet, [FName, Fn^.ArgNames[i]])
              Else
                 EvaluationError(SEvalPassedNonSet, [FName, Fn^.ArgNames[i]])
           Else
             AEnvironment.AddVariable(Fn^.ArgNames[i], TXPathVariable(Args.Items[i]), True);
         Result := EvaluateXPathExpression(Fn^.Body, AContext.ContextNode, AEnvironment.NodeNameTester, PPtrs, AContext.Construct, Nil, AEnvironment);
         Changed := TStringList.Create;
         try
           for i := Low(Fn^.ArgNames) To High(Fn^.ArgNames) Do
               if Fn^.ArgRefs[i] then
                  If FArgs[i] is TXPathVariableNode Then
                     Changed.AddObject(TXPathVariableNode(FArgs[i]).FName, AEnvironment.VariablesByName[Fn^.ArgNames[i]].Clone)
                  Else
                     EvaluationError(SEvalNotVarByRef, [FName, Fn^.ArgNames[i]]);
         finally
           AEnvironment.popVariables;
           for i := 0 To Changed.Count - 1 Do
               AEnvironment.VariablesByName[Changed.Strings[i]] := Changed.Objects[i] As TXPathVariable;
           Changed.Free
         end;
       finally
         Args.Free
       end;
     end;
end;

constructor TXPathNegationNode.Create(AOperand: TXPathExprNode);
begin
  inherited Create;
  FOperand := AOperand;
end;

destructor TXPathNegationNode.Destroy;
begin
  FOperand.Free;
  inherited Destroy;
end;

function TXPathNegationNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  OpResult: TXPathVariable;
  R: TXMLVarsList;
begin
  OpResult := FOperand.Evaluate(AContext, AEnvironment, R);
  R.Free;
  Variants := TXMLVarsList.Create;
  try
    Result := TXPathNumberVariable.Create(-OpResult.AsNumber);
  finally
    OpResult.Release;
  end;
end;

destructor TXPathBinaryNode.Destroy;
begin
  FOperand1.Free;
  FOperand2.Free;
  inherited Destroy;
end;

constructor TXPathMathOpNode.Create(AOperator: TXPathMathOp;
  AOperand1, AOperand2: TXPathExprNode);
begin
  inherited Create;
  FOperator := AOperator;
  FOperand1 := AOperand1;
  FOperand2 := AOperand2;
end;

function TXPathMathOpNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  Op1Result, Op2Result: TXPathVariable;
  Op1, Op2, NumberResult: Extended;
  R: TXMLVarsList;
begin
  Variants := TXMLVarsList.Create;
  Op1Result := FOperand1.Evaluate(AContext, AEnvironment, R);
  R.Free;
  try
    Op2Result := FOperand2.Evaluate(AContext, AEnvironment, R);
    R.Free;
    try
      Op1 := Op1Result.AsNumber;
      Op2 := Op2Result.AsNumber;
      case FOperator of
        opAdd:
          NumberResult := Op1 + Op2;
        opSubtract:
          NumberResult := Op1 - Op2;
        opMultiply:
          NumberResult := Op1 * Op2;
        opDivide:
          NumberResult := Op1 / Op2;
        opMod: if IsNan(Op1) or IsNan(Op2) then
{$push}
{$r-,q-}
          NumberResult := NaN
{$pop}
        else
          NumberResult := Trunc(Op1) mod Trunc(Op2);
      end;
    finally
      Op2Result.Release;
    end;
  finally
    Op1Result.Release;
  end;
  Result := TXPathNumberVariable.Create(NumberResult);
end;

const
  reverse: array[TXPathCompareOp] of TXPathCompareOp = (
    opEqual, opNotEqual,
    opGreaterEqual, //opLess
    opGreater,      //opLessEqual
    opLessEqual,    //opGreater
    opLess          //opGreaterEqual
  );
  
function CmpNumbers(const n1, n2: Extended; op: TXPathCompareOp): Boolean;
begin
  result := (op = opNotEqual);
  if IsNan(n1) or IsNan(n2) then
    Exit;    // NaNs are not equal
  case op of
    // TODO: should CompareValue() be used here?
    opLess:         result := n1 < n2;
    opLessEqual:    result := n1 <= n2;
    opGreater:      result := n1 > n2;
    opGreaterEqual: result := n1 >= n2;
  else
    if IsInfinite(n1) or IsInfinite(n2) then
      result := n1 = n2
    else
      result := SameValue(n1, n2);
    result := result xor (op = opNotEqual);
  end;
end;

function CmpStrings(const s1, s2: DOMString; op: TXPathCompareOp): Boolean;
begin
  case op of
    opEqual:    result := s1 = s2;
    opNotEqual: result := s1 <> s2;
  else
    result := CmpNumbers(StrToNumber(s1), StrToNumber(s2), op);
  end;
end;

function CmpNodesetWithString(ns: TNodeSet; const s: DOMString; op: TXPathCompareOp): Boolean;
var
  i: Integer;
begin
  Result := True;
  for i := 0 to ns.Count - 1 do
  begin
    if CmpStrings(NodeToText(TDOMNode(ns[i])), s, op) then
      exit;
  end;
  Result := False;
end;

function CmpNodesetWithNumber(ns: TNodeSet; const n: Extended; op: TXPathCompareOp): Boolean;
var
  i: Integer;
begin
  Result := True;
  for i := 0 to ns.Count - 1 do
  begin
    if CmpNumbers(StrToNumber(NodeToText(TDOMNode(ns[i]))), n, op) then
      exit;
  end;
  Result := False;
end;

function CmpNodesetWithBoolean(ns: TNodeSet; b: Boolean; op: TXPathCompareOp): Boolean;
begin
// TODO: handles only equality
  result := ((ns.Count <> 0) = b) xor (op = opNotEqual);
end;

function CmpNodesets(ns1, ns2: TNodeSet; op: TXPathCompareOp): Boolean;
var
  i, j: Integer;
  s: DOMString;
begin
  Result := True;
  for i := 0 to ns1.Count - 1 do
  begin
    s := NodeToText(TDOMNode(ns1[i]));
    for j := 0 to ns2.Count - 1 do
    if CmpStrings(s, NodeToText(TDOMNode(ns2[j])), op) then
      exit;
  end;
  Result := False;
end;

constructor TXPathCompareNode.Create(AOperator: TXPathCompareOp;
  AOperand1, AOperand2: TXPathExprNode);
begin
  inherited Create;
  FOperator := AOperator;
  FOperand1 := AOperand1;
  FOperand2 := AOperand2;
end;

function TXPathCompareNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  Op1, Op2: TXPathVariable;
  BoolResult: Boolean;
  R: TXMLVarsList;
  A1, A2: Boolean;
  Attr: WideString;
  L: TXPathVariable;
  LL: TNodeSet;
  LS: TStringList;
  I: Integer;
  nsnum: Integer;
begin
  Variants := TXMLVarsList.Create;
  If Assigned(AContext.Construct) And (FOperator = opEqual) Then
     begin
       A1 := (FOperand1 is TStep) And (TStep(FOperand1).Axis = axisAttribute) And
                  (Not Assigned(TStep(FOperand1).FLeft)) And
                  (TStep(FOperand1).NodeTestType = ntName);
       A2 := (FOperand2 is TStep) And (TStep(FOperand2).Axis = axisAttribute) And
                  (Not Assigned(TStep(FOperand2).FLeft)) And
                  (TStep(FOperand2).NodeTestType = ntName);
       if A1 Xor A2 Then
          begin
            If A1 Then
               begin
                 Attr := TStep(FOperand1).NodeTestString;
                 L := FOperand2.Evaluate(AContext, AEnvironment, R)
               end
            else
               begin
                 Attr := TStep(FOperand2).NodeTestString;
                 L := FOperand1.Evaluate(AContext, AEnvironment, R)
               end;
            if Not (L is TXPathNodeSetVariable) then
               begin
                 LS := TStringList.Create;
                 LS.Add(Attr + '=' + L.AsText);
                 Variants.AddObject('', LS)
               end
            else
              begin
                LL := L.AsNodeSet;
                For I := 0 To LL.Count - 1 Do
                    begin
                      LS := TStringList.Create;
                      LS.Add(Attr + '=' + NodeToText(TDOMNode(LL[i])));
                      Variants.AddObject('', LS)
                    end
              end;
            R.Free;
            L.Release;
            Exit(TXPathBooleanVariable.Create(True))
          end;
     end;
  Op1 := FOperand1.Evaluate(AContext, AEnvironment, R);
  R.Free;
  try
    Op2 := FOperand2.Evaluate(AContext, AEnvironment, R);
    R.Free;
    try
      nsnum := ord(Op1 is TXPathNodeSetVariable) or
       (ord(Op2 is TXPathNodeSetVariable) shl 1);
      case nsnum of
        0: begin  // neither op is a nodeset
          if (FOperator in [opEqual, opNotEqual]) then
          begin
            if (Op1 is TXPathBooleanVariable) or (Op2 is TXPathBooleanVariable) then
              BoolResult := (Op1.AsBoolean = Op2.AsBoolean) xor (FOperator = opNotEqual)
            else if (Op1 is TXPathNumberVariable) or (Op2 is TXPathNumberVariable) then
              BoolResult := CmpNumbers(Op1.AsNumber, Op2.AsNumber, FOperator)
            else
              BoolResult := (Op1.AsText = Op2.AsText) xor (FOperator = opNotEqual);
          end
          else
            BoolResult := CmpNumbers(Op1.AsNumber, Op2.AsNumber, FOperator);
        end;

        1: // Op1 is nodeset
          if Op2 is TXPathNumberVariable then
            BoolResult := CmpNodesetWithNumber(Op1.AsNodeSet, Op2.AsNumber, FOperator)
          else if Op2 is TXPathStringVariable then
            BoolResult := CmpNodesetWithString(Op1.AsNodeSet, Op2.AsText, FOperator)
          else
            BoolResult := CmpNodesetWithBoolean(Op1.AsNodeSet, Op2.AsBoolean, FOperator);

        2: // Op2 is nodeset
          if Op1 is TXPathNumberVariable then
            BoolResult := CmpNodesetWithNumber(Op2.AsNodeSet, Op1.AsNumber, reverse[FOperator])
          else if Op1 is TXPathStringVariable then
            BoolResult := CmpNodesetWithString(Op2.AsNodeSet, Op1.AsText, reverse[FOperator])
          else
            BoolResult := CmpNodesetWithBoolean(Op2.AsNodeSet, Op1.AsBoolean, reverse[FOperator]);

      else  // both ops are nodesets
        BoolResult := CmpNodesets(Op1.AsNodeSet, Op2.AsNodeSet, FOperator);
      end;
      If BoolResult And (FOperator = opEqual) Then
         begin
           Op1.MarkPolled;
           Op2.MarkPolled
         end;
    finally
      Op2.Release;
    end;
  finally
    Op1.Release;
  end;
  Result := TXPathBooleanVariable.Create(BoolResult);
end;

constructor TXPathBooleanOpNode.Create(AOperator: TXPathBooleanOp;
  AOperand1, AOperand2: TXPathExprNode);
begin
  inherited Create;
  FOperator := AOperator;
  FOperand1 := AOperand1;
  FOperand2 := AOperand2;
end;

function TXPathBooleanOpNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  res: Boolean;
  Op1, Op2: TXPathVariable;
  R, R1, R2: TXMLVarsList;
begin
  Variants := TXMLVarsList.Create;
  If Assigned(AContext.Construct) And (FOperator in [opAnd, opOr]) Then
     begin
       Op1 := FOperand1.Evaluate(AContext, AEnvironment, R1);
       Op2 := FOperand2.Evaluate(AContext, AEnvironment, R2);
       If Not Assigned(R1) Then R1 := TXMLVarsList.Create;
       If Not Assigned(R2) Then R2 := TXMLVarsList.Create;
       If FOperator = opAnd Then
          Variants := R1.Mul(R2)
       Else
          Variants := R1.Add(R2);
       R1.Free;
       R2.Free;
       Op1.Release;
       Op2.Release;
       Exit(TXPathBooleanVariable.Create(True))
     end;
  { don't evaluate second arg if result is determined by first one }
  Op1 := FOperand1.Evaluate(AContext, AEnvironment, R);
  R.Free;
  try
    res := Op1.AsBoolean;
  finally
    Op1.Release;
  end;
  if not (((FOperator = opAnd) and (not res)) or ((FOperator = opOr) and res)) then
  begin
    Op2 := FOperand2.Evaluate(AContext, AEnvironment, R);
    R.Free;
    try
      case FOperator of
        opAnd: res := res and Op2.AsBoolean;
        opOr:  res := res or Op2.AsBoolean;
      end;
    finally
      Op2.Release;
    end;
  end;
  Result := TXPathBooleanVariable.Create(res);
end;

constructor TXPathUnionNode.Create(AOperand1, AOperand2: TXPathExprNode);
begin
  inherited Create;
  FOperand1 := AOperand1;
  FOperand2 := AOperand2;
end;

function TXPathUnionNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  Op1Result, Op2Result: TXPathVariable;
  NodeSet, NodeSet2: TNodeSet;
  CurNode: Pointer;
  R: TXMLVarsList;
  i: Integer;
begin
  Variants := TXMLVarsList.Create;
{ TODO: result must be sorted by document order, i.e. 'a|b' yields the
  same nodeset as 'b|a' }
  Op1Result := FOperand1.Evaluate(AContext, AEnvironment, R);
  R.Free;
  try
    Op2Result := FOperand2.Evaluate(AContext, AEnvironment, R);
    R.Free;
    try
      NodeSet := Op1Result.AsNodeSet;
      NodeSet2 := Op2Result.AsNodeSet;
      for i := 0 to NodeSet2.Count - 1 do
      begin
        CurNode := NodeSet2[i];
        if NodeSet.IndexOf(CurNode) < 0 then
          NodeSet.Add(CurNode);
      end;
    finally
      Op2Result.Release;
    end;
  finally
    Result := Op1Result;
  end;
end;


constructor TXPathFilterNode.Create(AExpr: TXPathExprNode);
begin
  inherited Create;
  FLeft := AExpr;
end;

destructor TXPathFilterNode.Destroy;
var
  i: Integer;
begin
  FLeft.Free;
  for i := 0 to High(FPredicates) do
    FPredicates[i].Free;
  inherited Destroy;
end;

function TXPathFilterNode.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  NodeSet: TNodeSet;
  R: TXMLVarsList;
begin
  Variants := TXMLVarsList.Create;
  Result := FLeft.Evaluate(AContext, AEnvironment, R);
  R.Free;
  NodeSet := Result.AsNodeSet;
  ApplyPredicates(Nil, NodeSet, AEnvironment, AContext.Ptrs, AContext.Construct);
end;


constructor TStep.Create(aAxis: TAxis; aTest: TNodeTestType);
begin
  Axis := aAxis;
  NodeTestType := aTest;
end;

procedure TStep.SelectNodes(ANode: TDOMNode; const Ptrs: array of TDOMNode; const Construct: TNodeSet; NodeNameTester: TXPathNodeNameTester; out ResultNodes: TNodeSet);
var
  Node, Node2: TDOMNode;
  Attr: TDOMNamedNodeMap;
  i: Integer;

  procedure DoNodeTest(Node: TDOMNode);

  Var F: Integer;
      Found: Boolean;
  begin
    case NodeTestType of
      ntAnyPrincipal:
        // !!!: Probably this isn't ready for namespace support yet
        if (Axis <> axisAttribute) and
          (Node.NodeType <> ELEMENT_NODE) then
          exit;
      ntName:
        if NSTestString <> '' then
        begin
          if Node.namespaceURI <> NSTestString then
            exit;
          if (NodeTestString <> '') and (Node.localName <> NodeTestString) then
            exit;
        end
        else if Node.NodeName <> NodeTestString then
           If Not (Assigned(NodeNameTester) And NodeNameTester(PChar(String(Node.NodeName)), PChar(String(NodeTestString)))) Then
              exit;
      ntTextNode:
        if not Node.InheritsFrom(TDOMText) then
          exit;
      ntCommentNode:
        if Node.NodeType <> COMMENT_NODE then
          exit;
      ntPINode:
        if (Node.NodeType <> PROCESSING_INSTRUCTION_NODE) or
         ((NodeTestString <> '') and (Node.nodeName <> NodeTestString)) then
          exit;
    end;
    if ResultNodes.IndexOf(Node) < 0 then
      ResultNodes.Add(Node);
  end;

  procedure AddDescendants(CurNode: TDOMNode);
  var
    Child: TDOMNode;
  begin
    Child := CurNode.FirstChild;
    while Assigned(Child) do
    begin
      DoNodeTest(Child);
      AddDescendants(Child);
      Child := Child.NextSibling;
    end;
  end;

  procedure AddDescendantsReverse(CurNode: TDOMNode);
  var
    Child: TDOMNode;
  begin
    Child := CurNode.LastChild;
    while Assigned(Child) do
    begin
      AddDescendantsReverse(Child);
      DoNodeTest(Child);
      Child := Child.PreviousSibling;
    end;
  end;

begin
  ResultNodes := TNodeSet.Create;
  case Axis of
    axisAncestor:
      begin
        // TODO: same check needed for XPATH_NAMESPACE_NODE
        if ANode.nodeType = ATTRIBUTE_NODE then
          Node := TDOMAttr(ANode).ownerElement
        else
          Node := ANode.ParentNode;
        while Assigned(Node) do
        begin
          DoNodeTest(Node);
          Node := Node.ParentNode;
        end;
      end;
    axisAncestorOrSelf:
      begin
        DoNodeTest(ANode);
        // TODO: same check needed for XPATH_NAMESPACE_NODE
        if ANode.nodeType = ATTRIBUTE_NODE then
          Node := TDOMAttr(ANode).ownerElement
        else
          Node := ANode.ParentNode;
        while Assigned(Node) do
        begin
          DoNodeTest(Node);
          Node := Node.ParentNode;
        end;
      end;
    axisAttribute:
      begin
        Attr := ANode.Attributes;
        if Assigned(Attr) then
          for i := 0 to Attr.Length - 1 do
            DoNodeTest(Attr[i]);
      end;
    axisChild:
      begin
        Node := ANode.FirstChild;
        while Assigned(Node) do
        begin
          DoNodeTest(Node);
          Node := Node.NextSibling;
        end;
      end;
    axisDescendant:
      AddDescendants(ANode);
    axisDescendantOrSelf:
      begin
        DoNodeTest(ANode);
        AddDescendants(ANode);
      end;
    axisFollowing:
      begin
        Node := ANode;
        repeat
          Node2 := Node.NextSibling;
          while Assigned(Node2) do
          begin
            DoNodeTest(Node2);
            AddDescendants(Node2);
            Node2 := Node2.NextSibling;
          end;
          Node := Node.ParentNode;
        until not Assigned(Node);
      end;
    axisFollowingSibling:
      begin
        Node := ANode.NextSibling;
        while Assigned(Node) do
        begin
          DoNodeTest(Node);
          Node := Node.NextSibling;
        end;
      end;
    {axisNamespace: !!!: Not supported yet}
    axisParent:
      if ANode.NodeType=ATTRIBUTE_NODE then
      begin
        if Assigned(TDOMAttr(ANode).OwnerElement) then
          DoNodeTest(TDOMAttr(ANode).OwnerElement);
      end
      else if Assigned(ANode.ParentNode) then
        DoNodeTest(ANode.ParentNode);
    axisPreceding:
      begin
        Node := ANode;
        repeat
          Node2 := Node.PreviousSibling;
          while Assigned(Node2) do
          begin
            AddDescendantsReverse(Node2);
            DoNodeTest(Node2);
            Node2 := Node2.PreviousSibling;
          end;
          Node := Node.ParentNode;
        until not Assigned(Node);
      end;
    axisPrecedingSibling:
      begin
        Node := ANode.PreviousSibling;
        while Assigned(Node) do
        begin
          DoNodeTest(Node);
          Node := Node.PreviousSibling;
        end;
      end;
    axisSelf:
      DoNodeTest(ANode);
    axisRoot:
      if ANode.nodeType = DOCUMENT_NODE then
        ResultNodes.Add(ANode)
      else
        ResultNodes.Add(ANode.ownerDocument);
    axisPartner:
      if (Length(Ptrs) > 0) And Assigned(Ptrs[0]) then
         DoNodeTest(Ptrs[0]);
    axisContact:
      if (Length(Ptrs) > 1) And Assigned(Ptrs[1]) then
         DoNodeTest(Ptrs[1]);
    axisBase:
      if (Length(Ptrs) > 2) And Assigned(Ptrs[2]) then
         DoNodeTest(Ptrs[2]);
  end;
end;

{ Filter the nodes of this step using the predicates: The current
  node set is filtered, nodes not passing the filter are replaced
  by nil. After one filter has been applied, Nodes is packed, and
  the next filter will be processed. }

procedure TXPathFilterNode.ApplyPredicates(Parent: TDOMNode; Nodes: TNodeSet; AEnvironment: TXPathEnvironment; const Ptrs: array of TDOMNode; const Construct: TNodeSet);
var
  i, j, k, m: Integer;
  NewContext: TXPathContext;
  Exists: Boolean;
  S: String;
  This: TDOMElement;
  Res: Boolean;
  R: TXMLVarsList;
begin
  If Assigned(Construct) And (Self Is TStep) And Assigned(Parent) And (Length(FPredicates) = 0) And (Nodes.Count = 0) Then
     begin // Creation of single node when predicates are absent
       This := Parent.OwnerDocument.CreateElement(TStep(Self).NodeTestString);
       Parent.AppendChild(This);
       Nodes.Add(This);
       Construct.Add(This);
       AEnvironment.pushUndo(True, This, Nil, Parent);
       Exit
     end;
  for i := 0 to High(FPredicates) do
  begin
    NewContext := TXPathContext.Create(nil, 0, Nodes.Count, Ptrs, Nil);
    try
      for j := 0 to Nodes.Count - 1 do
      begin
        NewContext.ContextPosition := j+1;
        NewContext.ContextNode := TDOMNode(Nodes[j]);
        if not FPredicates[i].EvalPredicate(NewContext, AEnvironment, R) then
          Nodes[j] := nil;
        R.Free
      end;
      Nodes.Pack
    finally
      NewContext.Free;
    end
  end;
  If Assigned(Construct) And (Self Is TStep) And Assigned(Parent) Then
     begin
       for i := 0 to High(FPredicates) do
       begin
         This := Parent.OwnerDocument.CreateElement(TStep(Self).NodeTestString);
         Parent.AppendChild(This);
         Nodes.Add(This);
         NewContext := TXPathContext.Create(nil, 0, Nodes.Count, Ptrs, Construct);
         NewContext.ContextPosition := 1;
         NewContext.ContextNode := This;
         try
            Res := FPredicates[i].EvalPredicate(NewContext, AEnvironment, R);
            // Parent.RemoveChild(This);
            Nodes.Remove(This);
            This.Free;
            If Res And (R.Count > 0) Then
              begin
                For j := 0 To R.Count - 1 Do
                    begin
                      // Check already exists
                      Exists := False;
                      For k := 0 To Nodes.Count - 1 Do
                          Begin
                            This := TDOMElement(Nodes.Items[k]);
                            Exists := True;
                            With TStringList(R.Objects[j]) Do
                              For m := 0 To Count - 1 Do
                                  begin
                                    S := Names[m];
                                    If This.AttribStrings[S] <> Values[S] Then
                                       begin
                                         Exists := False;
                                         Break
                                       end
                                  end;
                            If Exists Then Break
                          end;
                      If Exists Then Continue;
                      This := Parent.OwnerDocument.CreateElement(TStep(Self).NodeTestString);
                      With TStringList(R.Objects[j]) Do
                        For k := 0 To Count - 1 Do
                            This.SetAttribute(Names[k], Values[Names[k]]);
                      Parent.AppendChild(This);
                      Nodes.Add(This);
                      Construct.Add(This);
                      AEnvironment.pushUndo(True, This, Nil, Parent);
                    end
              end;
            R.Free;
         finally
           NewContext.Free;
         end;
       end;
       for i := 0 to High(FPredicates) do
       begin
         NewContext := TXPathContext.Create(nil, 0, Nodes.Count, Ptrs, Nil);
         try
           for j := 0 to Nodes.Count - 1 do
           begin
             NewContext.ContextPosition := j+1;
             NewContext.ContextNode := TDOMNode(Nodes[j]);
             if not FPredicates[i].EvalPredicate(NewContext, AEnvironment, R) then
                Begin
                  If Assigned(Construct) And (Self Is TStep) And Assigned(Parent) Then
                     If Construct.IndexOf(Nodes[j]) >= 0 Then
                        Begin
                          Construct.Remove(Nodes[j]);
                          AEnvironment.pushUndo(False, TDOMNode(Nodes[j]), TDOMNode(Nodes[j]).NextSibling, TDOMNode(Nodes[j]).ParentNode);
                          TDOMNode(Nodes[j]).ParentNode.RemoveChild(TObject(Nodes[j]) As TDOMNode);
                          // TObject(Nodes[j]).Free
                        End;
                  Nodes[j] := nil
                End;
             R.Free
           end;
           Nodes.Pack
         finally
           NewContext.Free;
         end
       end
     end
end;

function TStep.Evaluate(AContext: TXPathContext;
  AEnvironment: TXPathEnvironment; out Variants: TXMLVarsList): TXPathVariable;
var
  ResultNodeSet: TNodeSet;
  LeftResult: TXPathVariable;
  i: Integer;

  procedure EvaluateStep(AContextNode: TDOMNode);
  var
    StepNodes: TFPList;
    Validated: TFPList;
    Node: TDOMNode;
    Beg: Integer;
    i: Integer;
  begin
    SelectNodes(AContextNode, AContext.Ptrs, AContext.Construct, AEnvironment.NodeNameTester, StepNodes);
    try
      If Assigned(AContext.Construct) Then
         begin
           If Axis = axisAttribute Then
              begin
                If StepNodes.Count = 0 Then
                   begin
                     Node := AContextNode.OwnerDocument.CreateAttribute(NodeTestString);
                     StepNodes.Add(Node);
                     // AContext.Construct.Add(Node);
                     Node := AContextNode.Attributes.SetNamedItem(Node);
                     If Assigned(Node) Then
                        Node.Free
                   end
              end
           Else
              begin
                 Beg := AContext.Construct.Count; // Number of first constructed node
                 ApplyPredicates(AContextNode, StepNodes, AEnvironment, AContext.Ptrs, AContext.Construct);
                 If Beg < AContext.Construct.Count Then // If some elements has been created
                    begin // check elements constructed for validity
                      Validated := TFPList.Create;
                      For i := Beg To AContext.Construct.Count - 1 Do
                          If TDOMNode(AContext.Construct[i]).ParentNode = AContextNode Then
                             Validated.Add(AContext.Construct[i]);
                      i := Validated.Count;
                      // Check in non-constructing mode
                      ApplyPredicates(AContextNode, Validated, AEnvironment, AContext.Ptrs, Nil);
                      if Validated.Count < i Then // if sequestration
                         begin
                           For i := Beg To AContext.Construct.Count - 1 Do
                             If (TDOMNode(AContext.Construct[i]).ParentNode = AContextNode) And (Validated.IndexOf(AContext.Construct[i]) < 0) Then
                                begin
                                  StepNodes.Remove(AContext.Construct[i]);
                                  // If Assigned(AContextNode) Then
                                  //   AContextNode.RemoveChild(TDOMNode(AContext.Construct[i]));
                                  AEnvironment.pushUndo(False, TDOMNode(AContext.Construct[i]), TDOMNode(AContext.Construct[i]).NextSibling, TDOMNode(AContext.Construct[i]).ParentNode);
                                  TDOMNode(AContext.Construct[i]).ParentNode.RemoveChild(TObject(AContext.Construct[i]) As TDOMNode);
                                  // TDOMNode(AContext.Construct[i]).Free;
                                  AContext.Construct[i] := Nil
                                end;
                           AContext.Construct.Pack
                         end;
                      Validated.Free
                    end
              end
         end
      else
         ApplyPredicates(AContextNode, StepNodes, AEnvironment, AContext.Ptrs, Nil);
      if Axis in [axisAncestor, axisAncestorOrSelf,
        axisPreceding, axisPrecedingSibling] then
      for i := StepNodes.Count - 1 downto 0 do
      begin
        Node := TDOMNode(StepNodes[i]);
        if ResultNodeSet.IndexOf(Node) < 0 then
          ResultNodeSet.Add(Node);
      end
      else for i := 0 to StepNodes.Count - 1 do
      begin
        Node := TDOMNode(StepNodes[i]);
        if ResultNodeSet.IndexOf(Node) < 0 then
          ResultNodeSet.Add(Node);
      end;
    finally
      StepNodes.Free;
    end;
  end;

Var R: TXMLVarsList;
begin
  Variants := TXMLVarsList.Create;
  ResultNodeSet := TNodeSet.Create;
  try
    if Assigned(FLeft) then
    begin
      LeftResult := FLeft.Evaluate(AContext, AEnvironment, R);
      R.Free;
      try
        with LeftResult.AsNodeSet do
          for i := 0 to Count-1 do
            EvaluateStep(TDOMNode(Items[i]));
      finally
        LeftResult.Release;
      end;
    end
    else  
      EvaluateStep(AContext.ContextNode);
  except
    ResultNodeSet.Free;
    raise;
  end;
  Result := TXPathNodeSetVariable.Create(ResultNodeSet);
end;

{ Exceptions }

procedure EvaluationError(const Msg: String);
begin
  raise EXPathEvaluationError.Create(Msg) at get_caller_addr(get_frame), get_caller_frame(get_frame);
end;

procedure EvaluationError(const Msg: String; const Args: array of const);
begin
  raise EXPathEvaluationError.CreateFmt(Msg, Args)
    at get_caller_addr(get_frame), get_caller_frame(get_frame);
end;


{ TXPathVariable and derived classes}

procedure TXPathVariable.Release;
begin
  if FRefCount <= 0 then
    Free
  else
    Dec(FRefCount);
end;

function TXPathVariable.AsNodeSet: TNodeSet;
begin
  Error(SVarNoConversion, [TypeName, TXPathNodeSetVariable.TypeName]);
  Result := nil;
end;

class function TXPathVariable.Import(const From: String): TXPathVariable;

Var F, P: Integer;
    V: TNodeSet;
    Tp: String;
begin
  P := Pos(':', From);
  If P = 0 Then
     raise Exception.Create(From + ' : can''t import variable!');
  Tp := Copy(From, 1, P-1);
  If Tp = 'NODESET' Then
     With TStringList.Create Do
       Begin
         CommaText := Copy(From, P+1, 32768);
         V := TNodeSet.Create;
         For F := 0 To Count-1 Do
             V.Add(IntegerToTObject(StrToInt(Strings[F])));
         Result := TXPathNodeSetVariable.Create(V);
         Free
       end
  Else If Tp = 'BOOLEAN' Then
     If Copy(From, P+1, 8192) = 'true' Then
        Result := TXPathBooleanVariable.Create(True)
     Else
        Result := TXPathBooleanVariable.Create(False)
  Else If Tp = 'NUMBER' Then
     Result := TXPathNumberVariable.Create(StrToFloat(Copy(From, P+1, 8192)))
  Else If Tp = 'STRING' Then
     Result := TXPathStringVariable.Create(Copy(From, P+1, 8192))
  Else
    raise Exception.Create(From + ' : Unknown Type : can''t import variable!')
end;

procedure TXPathVariable.Error(const Msg: String; const Args: array of const);
begin
  raise Exception.CreateFmt(Msg, Args) at get_caller_addr(get_frame), get_caller_frame(get_frame);
end;

function TXPathVariable.IsBound: Boolean;
begin
  Result := FBound
end;

procedure TXPathVariable.MarkPolled;
begin
end;


constructor TXPathNodeSetVariable.Create(AValue: TNodeSet; const bound: Boolean
  );
begin
  inherited Create;
  FValue := AValue;
  FBound := bound
end;

destructor TXPathNodeSetVariable.Destroy;
begin
  FValue.Free;
  inherited Destroy;
end;

procedure TXPathNodeSetVariable.MarkPolled;

Var F: Integer;
begin
  inherited MarkPolled;
  For F := 0 To FValue.Count - 1 Do
      If TDOMElement(FValue.Items[F]).InheritsFrom(TDOMText) Then
         If Assigned(TDOMElement(FValue.Items[F]).ParentNode) Then
            TDOMElement(TDOMNode(FValue.Items[F]).ParentNode).AttribStrings['polled'] := '1';
end;

class function TXPathNodeSetVariable.TypeName: String;
begin
  Result := SNodeSet;
end;

function TXPathNodeSetVariable.Clone: TXPathVariable;
begin
  Result := Self;
  Inc(FRefCount)
end;

function TXPathNodeSetVariable.AsNodeSet: TNodeSet;
begin
  Result := FValue;
end;

function TXPathNodeSetVariable.AsText: DOMString;
begin
  if FValue.Count = 0 then
    Result := ''
  else
    Result := NodeToText(TDOMNode(FValue.First));
end;

function TXPathNodeSetVariable.AsBoolean: Boolean;
begin
  Result := FValue.Count <> 0;
end;

function TXPathNodeSetVariable.AsNumber: Extended;
begin
  Result := StrToNumber(AsText);
end;

function TXPathNodeSetVariable.Export: DOMString;

Var F: Integer;
begin
  Result := 'NODESET:';
  With TStringList.Create Do
    Begin
      For F := 0 To FValue.Count-1 Do
          Add(IntToStr(TObjectToInteger(TObject(FValue[F]))));
      Result := Result + CommaText;
      Free
    end;
end;

constructor TXPathBooleanVariable.Create(AValue: Boolean; const bound: Boolean);
begin
  inherited Create;
  FValue := AValue;
  FBound := bound
end;

class function TXPathBooleanVariable.TypeName: String;
begin
  Result := SBoolean;
end;

function TXPathBooleanVariable.Clone: TXPathVariable;
begin
  Result := TXPathBooleanVariable.Create(FValue, FBound)
end;

function TXPathBooleanVariable.AsBoolean: Boolean;
begin
  Result := FValue;
end;

function TXPathBooleanVariable.AsNumber: Extended;
begin
  if FValue then
    Result := 1
  else
    Result := 0;
end;

function TXPathBooleanVariable.AsText: DOMString;
begin
  if FValue then
    Result := 'true'    // Do not localize!
  else
    Result := 'false';  // Do not localize!
end;

function TXPathBooleanVariable.Export: DOMString;
begin
  Result := 'BOOLEAN:' + AsText
end;


constructor TXPathNumberVariable.Create(AValue: Extended; const bound: Boolean);
begin
  inherited Create;
  FValue := AValue;
  FBound := bound
end;

class function TXPathNumberVariable.TypeName: String;
begin
  Result := SNumber;
end;

function TXPathNumberVariable.Clone: TXPathVariable;
begin
  Result := TXPathNumberVariable.Create(FValue, FBound)
end;

function TXPathNumberVariable.AsBoolean: Boolean;
begin
  Result := not (IsNan(FValue) or IsZero(FValue));
end;

function TXPathNumberVariable.AsNumber: Extended;
begin
  Result := FValue;
end;

function TXPathNumberVariable.AsText: DOMString;
var
  frec: TFloatRec;
  i, nd, reqlen: Integer;
  P: DOMPChar;
begin
  FloatToDecimal(frec, FValue, fvExtended, 17, 9999);

  if frec.Exponent = -32768 then
  begin
    Result := 'NaN';          // do not localize
    Exit;
  end
  else if frec.Exponent = 32767 then
  begin
    if frec.Negative then
      Result := '-Infinity'   // do not localize
    else
      Result := 'Infinity';   // do not localize
    Exit;  
  end
  else if frec.Digits[0] = #0 then
  begin
    Result := '0';
    Exit;
  end
  else
  begin
    nd := StrLen(@frec.Digits[0]);
    reqlen := nd + ord(frec.Negative);  // maybe minus sign
    if frec.Exponent > nd then
      Inc(reqlen, frec.Exponent - nd)   // add this much zeroes at the right
    else if frec.Exponent < nd then
    begin
      Inc(reqlen);                      // decimal point
      if frec.Exponent <= 0 then
        Inc(reqlen, 1 - frec.Exponent); // zeroes at the left + one more for the int part
    end;
    SetLength(Result, reqlen);
    P := DOMPChar(Result);
    if frec.Negative then
    begin
      P^ := '-';
      Inc(P);
    end;
    if frec.Exponent <= 0 then          // value less than 1, put zeroes at left
    begin
      for i := 0 to 1-frec.Exponent do
        P[i] := '0';
      P[1] := '.';
      for i := 0 to nd-1 do
        P[i+2-frec.Exponent] := WideChar(ord(frec.Digits[i]));
    end
    else if frec.Exponent > nd then    // large integer, put zeroes at right
    begin
      for i := 0 to nd-1 do
        P[i] := WideChar(ord(frec.Digits[i]));
      for i := nd to reqlen-1-ord(frec.Negative) do
        P[i] := '0';
    end
    else  // 0 < exponent <= digits, insert decimal point into middle
    begin
      for i := 0 to frec.Exponent-1 do
        P[i] := WideChar(ord(frec.Digits[i]));
      if frec.Exponent < nd then
      begin
        P[frec.Exponent] := '.';
        for i := frec.Exponent to nd-1 do
          P[i+1] := WideChar(ord(frec.Digits[i]));
      end;
    end;
  end;
end;

function TXPathNumberVariable.Export: DOMString;
begin
  Result := 'NUMBER:' + FloatToStr(FValue)
end;


constructor TXPathStringVariable.Create(const AValue: DOMString;
  const bound: Boolean);
begin
  inherited Create;
  FValue := AValue;
  FBound := bound
end;

class function TXPathStringVariable.TypeName: String;
begin
  Result := SString;
end;

function TXPathStringVariable.Clone: TXPathVariable;
begin
  Result := TXPathStringVariable.Create(FValue, FBound)
end;

function TXPathStringVariable.AsBoolean: Boolean;
begin
  Result := Length(FValue) > 0;
end;

function TXPathStringVariable.AsNumber: Extended;
begin
  Result := StrToNumber(FValue);
end;

function TXPathStringVariable.AsText: DOMString;
begin
  Result := FValue;
end;

function TXPathStringVariable.Export: DOMString;
begin
  Result := 'STRING:' + FValue;
end;


{ XPath lexical scanner }

constructor TXPathScanner.Create(const AExpressionString: DOMString);
begin
  inherited Create;
  FExpressionString := DOMPChar(AExpressionString);
  FCurData := FExpressionString;
  NextToken;
end;

function TXPathScanner.PeekToken: TXPathToken;
var
  save: DOMPChar;
begin
  save := FCurData;
  Result := GetToken;
  FCurData := save;
end;

function TXPathScanner.NextToken: TXPathToken;
begin
  Result := GetToken;
  FCurToken := Result;
  if Result in [tkIdentifier, tkNSNameTest, tkNumber, tkString, tkVariable] then
    SetString(FCurTokenString, FTokenStart, FTokenLength);
  if Result = tkIdentifier then
    FTokenId := LookupXPathKeyword(FTokenStart, FTokenLength)
  else
    FTokenId := xkNone;
end;

function TXPathScanner.SkipToken(tok: TXPathToken): Boolean; { inline? }
begin
  Result := (FCurToken = tok);
  if Result then
    NextToken;
end;

// TODO: no surrogate pairs/XML 1.1 support yet
function TXPathScanner.ScanQName: Boolean;
var
  p: DOMPChar;
begin
  FPrefixLength := 0;
  p := FCurData;
  repeat
    if (Byte(p^) in NamingBitmap[NamePages[hi(Word(p^))]]) then
      Inc(p)
    else
    begin
      // either the first char of name is bad (it may be a colon),
      // or a colon is not followed by a valid NameStartChar
      Result := False;
      Break;
    end;

    while Byte(p^) in NamingBitmap[NamePages[$100+hi(Word(p^))]] do
      Inc(p);

    Result := True;
    if (p^ <> ':') or (p[1] = ':') or (FPrefixLength > 0) then
      Break;
    // first colon, and not followed by another one -> remember its position
    FPrefixLength := p-FTokenStart;
    Inc(p);
  until False;
  FCurData := p;
  FTokenLength := p-FTokenStart;
end;

function TXPathScanner.GetToken: TXPathToken;

  procedure GetNumber(HasDot: Boolean);
  begin
    FTokenLength := 1;
    while ((FCurData[1] >= '0') and (FCurData[1] <= '9')) or ((FCurData[1] = '.') and not HasDot) do
    begin
      Inc(FCurData);
      Inc(FTokenLength);
      if FCurData[0] = '.' then
        HasDot := True;
    end;
    Result := tkNumber;
  end;

var
  Delim: WideChar;
begin
  // Skip whitespace
  while (FCurData[0] < #255) and (char(ord(FCurData[0])) in [#9, #10, #13, ' ']) do
    Inc(FCurData);

  FTokenStart := FCurData;
  FTokenLength := 0;
  Result := tkInvalid;

  case FCurData[0] of
    #0:
      Result := tkEndOfStream;
    '!':
      if FCurData[1] = '=' then
      begin
        Inc(FCurData);
        Result := tkNotEqual;
      end;
    '"', '''':
      begin
        Delim := FCurData^;
        Inc(FCurData);
        FTokenStart := FCurData;
        while FCurData[0] <> Delim do
        begin
          if FCurData[0] = #0 then
            Error(SScannerUnclosedString);
          Inc(FCurData);
        end;
        FTokenLength := FCurData-FTokenStart;
        Result := tkString;
      end;
    '$':
      begin
        Inc(FCurData);
        Inc(FTokenStart);
        if ScanQName then
          Result := tkVariable
        else
          Error(SScannerExpectedVarName);
        Exit;
      end;
    '(':
      Result := tkLeftBracket;
    ')':
      Result := tkRightBracket;
    '*':
      Result := tkAsterisk;
    '+':
      Result := tkPlus;
    ',':
      Result := tkComma;
    '-':
      Result := tkMinus;
    '.':
      if FCurData[1] = '.' then
      begin
        Inc(FCurData);
        Result := tkDotDot;
      end else if (FCurData[1] >= '0') and (FCurData[1] <= '9') then
        GetNumber(True)
      else
        Result := tkDot;
    '/':
      if FCurData[1] = '/' then
      begin
        Inc(FCurData);
        Result := tkSlashSlash;
      end else
        Result := tkSlash;
    '#':
      if FCurData[1] = '#' then
      begin
        Inc(FCurData);
        if FCurData[1] = '#' then
           begin
             Inc(FCurData);
             Result := tkPound3
           end
        else
           Result := tkPoundPound;
      end else
        Result := tkPound;
    '0'..'9':
      GetNumber(False);
    ':':
      if FCurData[1] = ':' then
      begin
        Inc(FCurData);
        Result := tkColonColon;
      end;
    '<':
      if FCurData[1] = '=' then
      begin
        Inc(FCurData);
        Result := tkLessEqual;
      end else
        Result := tkLess;
    '=':
      Result := tkEqual;
    '>':
      if FCurData[1] = '=' then
      begin
        Inc(FCurData);
        Result := tkGreaterEqual;
      end else
        Result := tkGreater;
    '@':
      Result := tkAt;
    '[':
      Result := tkLeftSquareBracket;
    ']':
      Result := tkRightSquareBracket;
    '|':
      Result := tkPipe;
  else
    if ScanQName then
    begin
      Result := tkIdentifier;
      Exit;
    end
    else if FPrefixLength > 0 then
    begin
      if FCurData^ = '*'  then
      begin
        Inc(FCurData);
        Dec(FTokenLength);        // exclude ':'
        Result := tkNSNameTest;
        Exit;
      end
      else
        Error(SScannerMalformedQName);
    end;
  end;

  if Result = tkInvalid then
    Error(SScannerInvalidChar);
  // We have processed at least one character now; eat it:
  if Result > tkEndOfStream then
    Inc(FCurData);
end;

procedure TXPathScanner.Error(const Msg: String);
begin
  raise Exception.Create(Msg) at get_caller_addr(get_frame), get_caller_frame(get_frame);
end;

procedure TXPathScanner.ParsePredicates(var Dest: TXPathNodeArray);
var
  Buffer: array[0..15] of TXPathExprNode;
  I: Integer;
begin
  I := 0;
  // accumulate nodes in local buffer, then add all at once
  // this reduces amount of ReallocMem's
  while SkipToken(tkLeftSquareBracket) do
  begin
    Buffer[I] := ParseOrExpr;
    Inc(I);
    if I > High(Buffer) then
      AddNodes(Dest, Buffer, I);  // will reset I to zero
    if not SkipToken(tkRightSquareBracket) then
      Error(SParserExpectedRightSquareBracket);
  end;
  AddNodes(Dest, Buffer, I);
end;

function TXPathScanner.ParseStep: TStep;  // [4]
var
  Axis: TAxis;
begin
  if CurToken = tkDot then          // [12] Abbreviated step, first case
  begin
    NextToken;
    Result := TStep.Create(axisSelf, ntAnyNode);
  end
  else if CurToken = tkDotDot then  // [12] Abbreviated step, second case
  begin
    NextToken;
    Result := TStep.Create(axisParent, ntAnyNode);
  end
  else		// Parse [5] AxisSpecifier
  begin
    if CurToken = tkAt then         // [13] AbbreviatedAxisSpecifier
    begin
      Axis := axisAttribute;
      NextToken;
    end
    else if (CurToken = tkIdentifier) and (PeekToken = tkColonColon) then  // [5] AxisName '::'
    begin
      if FTokenId in AxisNameKeywords then
        Axis := AxisNameMap[FTokenId]
      else
        Error(SParserBadAxisName);
      NextToken;  // skip identifier and the '::'
      NextToken;
    end
    else
      Axis := axisChild;

    Result := ParseNodeTest(Axis);
    ParsePredicates(Result.FPredicates);
  end;
end;

function TXPathScanner.ParseNodeTest(Axis: TAxis): TStep; // [7]
var
  nodeType: TNodeTestType;
  nodeName: DOMString;
  nsURI: DOMString;
begin
  nodeName := '';
  nsURI := '';
  if CurToken = tkAsterisk then   // [37] NameTest, first case
  begin
    nodeType := ntAnyPrincipal;
    NextToken;
  end
  else if CurToken = tkNSNameTest then // [37] NameTest, second case
  begin
    if Assigned(FResolver) then
      nsURI := FResolver.lookupNamespaceURI(CurTokenString);
    if nsURI = '' then
      // !! localization disrupted by DOM exception specifics
      raise EDOMNamespace.Create('TXPathScanner.ParseStep');
    NextToken;
    nodeType := ntName;
  end
  else if CurToken = tkIdentifier then
  begin
    // Check for case [38] NodeType
    if PeekToken = tkLeftBracket then
    begin
      if FTokenId in NodeTestKeywords then
      begin
        nodeType := NodeTestMap[FTokenId];
        if FTokenId = xkProcessingInstruction then
        begin
          NextToken;
          if NextToken = tkString then
          begin
            nodeName := CurTokenString;
            NextToken;
          end;
        end
        else
        begin
          NextToken;
          NextToken;
        end;
        if CurToken <> tkRightBracket then
          Error(SParserExpectedRightBracket);
        NextToken;
      end
      else
        Error(SParserBadNodeType);
    end
    else  // [37] NameTest, third case
    begin
      nodeType := ntName;
      if FPrefixLength > 0 then
      begin
        if Assigned(FResolver) then
          nsURI := FResolver.lookupNamespaceURI(Copy(CurTokenString, 1, FPrefixLength));
        if nsURI = '' then
          raise EDOMNamespace.Create('TXPathScanner.ParseStep');
        nodeName := Copy(CurTokenString, FPrefixLength+2, MaxInt);
      end
      else
        nodeName := CurTokenString;
      NextToken;
    end;
  end
  else
    Error(SParserInvalidNodeTest);

  Result := TStep.Create(Axis, nodeType);
  Result.NodeTestString := nodeName;
  Result.NSTestString := nsURI;
end;

function TXPathScanner.ParsePrimaryExpr: TXPathExprNode;  // [15]
begin
  case CurToken of
    tkVariable:         // [36] Variable reference
        Result := TXPathVariableNode.Create(CurTokenString);
    tkLeftBracket:
      begin
        NextToken;
        Result := ParseOrExpr;
        if CurToken <> tkRightBracket then
          Error(SParserExpectedRightBracket);
      end;
    tkString:         // [29] Literal
      Result := TXPathConstantNode.Create(
        TXPathStringVariable.Create(CurTokenString));
    tkNumber:         // [30] Number
      Result := TXPathConstantNode.Create(
        TXPathNumberVariable.Create(StrToNumber(CurTokenString)));
    tkIdentifier:     // [16] Function call
      Result := ParseFunctionCall;
  else
    Error(SParserInvalidPrimExpr);
    Result := nil; // satisfy compiler
  end;
  NextToken;
end;

function TXPathScanner.ParseFunctionCall: TXPathExprNode;
var
  Name: DOMString;
  Args: TXPathNodeArray;
  Buffer: array[0..15] of TXPathExprNode;
  I: Integer;
begin
  Name := CurTokenString;
  I := 0;
  if NextToken <> tkLeftBracket then
    Error(SParserExpectedLeftBracket);
  NextToken;
  // Parse argument list
  if CurToken <> tkRightBracket then
  repeat
    Buffer[I] := ParseOrExpr;
    Inc(I);
    if I > High(Buffer) then
      AddNodes(Args, Buffer, I);
  until not SkipToken(tkComma);
  if CurToken <> tkRightBracket then
    Error(SParserExpectedRightBracket);

  AddNodes(Args, Buffer, I);
  Result := TXPathFunctionNode.Create(Name, Args);
end;

function TXPathScanner.ParseUnionExpr: TXPathExprNode;  // [18]
begin
  Result := ParsePathExpr;
  while SkipToken(tkPipe) do
    Result := TXPathUnionNode.Create(Result, ParsePathExpr);
end;

function AddStep(Left: TXPathExprNode; Right: TStep): TXPathExprNode;
begin
  Right.FLeft := Left;
  Result := Right;
end;

function TXPathScanner.ParsePathExpr: TXPathExprNode;  // [19]
var
  tok: TXPathToken;
begin
  Result := nil;
  // Try to detect whether a LocationPath [1] or a FilterExpr [20] follows
  if ((CurToken = tkIdentifier) and (PeekToken = tkLeftBracket) and
    not (FTokenId in NodeTestKeywords)) or
    (CurToken in [tkVariable, tkLeftBracket, tkString, tkNumber]) then
  begin
    // second, third or fourth case of [19]
    Result := ParseFilterExpr;
    if SkipToken(tkSlash) then { do nothing }
    else if SkipToken(tkSlashSlash) then
      Result := AddStep(Result, TStep.Create(axisDescendantOrSelf, ntAnyNode))
    else
      Exit;
  end
  else if CurToken in [tkSlash, tkSlashSlash] then
  begin
    tok := CurToken;
    NextToken;
    Result := TStep.Create(axisRoot, ntAnyNode);
    if tok = tkSlashSlash then
      Result := AddStep(Result, TStep.Create(axisDescendantOrSelf, ntAnyNode))
    else if not (CurToken in [tkDot, tkDotDot, tkAt, tkAsterisk, tkIdentifier, tkNSNameTest]) then
      Exit;  // allow '/' alone
  end
  else if CurToken in [tkPound, tkPoundPound, tkPound3] then
  begin
    tok := CurToken;
    NextToken;
    if tok = tkPound then
       Result := AddStep(Result, TStep.Create(axisPartner, ntAnyNode))
    else if tok = tkPoundPound then
       Result := AddStep(Result, TStep.Create(axisContact, ntAnyNode))
    else Result := AddStep(Result, TStep.Create(axisBase, ntAnyNode));
    if not SkipToken(tkSlash) then
      Exit
  end;
  // Continue with parsing of [3] RelativeLocationPath
  repeat
    Result := AddStep(Result, ParseStep);
    if CurToken = tkSlashSlash then
    begin
      NextToken;
      // Found abbreviated step ("//" for "descendant-or-self::node()")
      Result := AddStep(Result, TStep.Create(axisDescendantOrSelf, ntAnyNode));
    end
    else if not SkipToken(tkSlash) then
      break;
  until False;
end;

function TXPathScanner.ParseFilterExpr: TXPathExprNode;  // [20]
begin
  Result := ParsePrimaryExpr;
  // Parse predicates
  if CurToken = tkLeftSquareBracket then
  begin
    Result := TXPathFilterNode.Create(Result);
    ParsePredicates(TXPathFilterNode(Result).FPredicates);
  end;
end;

function TXPathScanner.ParseOrExpr: TXPathExprNode;  // [21]
begin
  Result := ParseAndExpr;
  while FTokenId = xkOr do
  begin
    NextToken;
    Result := TXPathBooleanOpNode.Create(opOr, Result, ParseAndExpr);
  end;
end;

function TXPathScanner.ParseAndExpr: TXPathExprNode;  // [22]
begin
  Result := ParseEqualityExpr;
  while FTokenId = xkAnd do
  begin
    NextToken;
    Result := TXPathBooleanOpNode.Create(opAnd, Result, ParseEqualityExpr);
  end;
end;

function TXPathScanner.ParseEqualityExpr: TXPathExprNode;  // [23]
var
  op: TXPathCompareOp;
begin
  Result := ParseRelationalExpr;
  repeat
    case CurToken of
      tkEqual:    op := opEqual;
      tkNotEqual: op := opNotEqual;
    else
      Break;
    end;
    NextToken;
    Result := TXPathCompareNode.Create(op, Result, ParseRelationalExpr);
  until False;
end;

function TXPathScanner.ParseRelationalExpr: TXPathExprNode;  // [24]
var
  op: TXPathCompareOp;
begin
  Result := ParseAdditiveExpr;
  repeat
    case CurToken of
      tkLess:      op := opLess;
      tkLessEqual: op := opLessEqual;
      tkGreater:   op := opGreater;
      tkGreaterEqual: op := opGreaterEqual;
    else
      Break;
    end;
    NextToken;
    Result := TXPathCompareNode.Create(op, Result, ParseAdditiveExpr);
  until False;
end;

function TXPathScanner.ParseAdditiveExpr: TXPathExprNode;  // [25]
var
  op: TXPathMathOp;
begin
  Result := ParseMultiplicativeExpr;
  repeat
    case CurToken of
      tkPlus: op := opAdd;
      tkMinus: op := opSubtract;
    else
      Break;
    end;
    NextToken;
    Result := TXPathMathOpNode.Create(op, Result, ParseMultiplicativeExpr);
  until False;
end;

function TXPathScanner.ParseMultiplicativeExpr: TXPathExprNode;  // [26]
var
  op: TXPathMathOp;
begin
  Result := ParseUnaryExpr;
  repeat
    case CurToken of
      tkAsterisk:
        op := opMultiply;
      tkIdentifier:
        if FTokenId = xkDiv then
          op := opDivide
        else if FTokenId = xkMod then
          op := opMod
        else
          break;
    else
      break;
    end;
    NextToken;
    Result := TXPathMathOpNode.Create(op, Result, ParseUnaryExpr);
  until False;
end;

function TXPathScanner.ParseUnaryExpr: TXPathExprNode;  // [27]
var
  NegCount: Integer;
begin
  NegCount := 0;
  while SkipToken(tkMinus) do
    Inc(NegCount);
  Result := ParseUnionExpr;

  if Odd(NegCount) then
    Result := TXPathNegationNode.Create(Result);
end;

{ TXPathContext }

constructor TXPathContext.Create(AContextNode: TDOMNode;
  AContextPosition, AContextSize: Integer; const _Ptrs: array of TDOMNode; const _Construct: TNodeSet);
Var I: Integer;
begin
  inherited Create;
  ContextNode := AContextNode;
  ContextPosition := AContextPosition;
  ContextSize := AContextSize;
  SetLength(Ptrs, Length(_Ptrs));
  for I := Low(_Ptrs) To High(_Ptrs) Do
      Ptrs[I] := _Ptrs[I];
  Construct := _Construct
end;


{ TXPathEnvironment }

type
  PVariableInfo = ^TVariableInfo;
  TVariableInfo = record
    Name: String;
    Variable: TXPathVariable;
    Local: Boolean
  end;


constructor TXPathEnvironment.Create;
begin
  inherited Create;
  FFunctions := TFPList.Create;
  FVariables := TFPList.Create;
  FVariablesStack := TList.Create;
  FUndoStack := TFPList.Create;

  FCollectedWords := TStringList.Create;
  FCollectedWords.CaseSensitive:=False;
  FCollectedWords.Delimiter := ';';
  FLocalWords := TStringList.Create;
  FLocalWords.CaseSensitive:=False;

  FCollectedRels := TStringList.Create;
  FCollectedRels.Delimiter := ';';
  FLocalRels := TStringList.Create;

  FTransaction := -1;

  // Add the functions of the XPath Core Function Library

  // Special functions
  AddFunction('eval', @spEval, true, []);
  AddFunction('min', @spMin, true, []);
  AddFunction('max', @spMax, true, []);
  AddFunction('set', @spSet, true, []);
  AddFunction('create', @spCreate, false, []);
  AddFunction('delete', @spDelete, false, []);
  AddFunction('transaction', @spTransaction, false, []);
  // Node set functions
  AddFunction('last', @xpLast, true, []);
  AddFunction('position', @xpPosition, true, []);
  AddFunction('count', @xpCount, true, []);
  AddFunction('id', @xpId, true, []);
  AddFunction('local-name', @xpLocalName, true, []);
  AddFunction('namespace-uri', @xpNamespaceURI, true, []);
  AddFunction('name', @xpName, true, []);
  // String functions
  AddFunction('string', @xpString, true, []);
  AddFunction('concat', @xpConcat, true, []);
  AddFunction('starts-with', @xpStartsWith, true, []);
  AddFunction('contains', @xpContains, true, []);
  AddFunction('substring-before', @xpSubstringBefore, true, []);
  AddFunction('substring-after', @xpSubstringAfter, true, []);
  AddFunction('substring', @xpSubstring, true, []);
  AddFunction('string-length', @xpStringLength, true, []);
  AddFunction('normalize-space', @xpNormalizeSpace, true, []);
  AddFunction('translate', @xpTranslate, true, []);
  // Boolean functions
  AddFunction('boolean', @xpBoolean, true, []);
  AddFunction('not', @xpNot, true, []);
  AddFunction('true', @xpTrue, true, []);
  AddFunction('false', @xpFalse, true, []);
  AddFunction('lang', @xpLang, true, []);
  // Number functions
  AddFunction('number', @xpNumber, true, []);
  AddFunction('sum', @xpSum, true, []);
  AddFunction('floor', @xpFloor, true, []);
  AddFunction('ceiling', @xpCeiling, true, []);
  AddFunction('round', @xpRound, true, []);
  AddFunction('gid', @xpGID, true, []);
  AddFunction('random', @xpRandom, true, []);
  AddFunction('randomid', @xpRandomID, true, []);
end;

destructor TXPathEnvironment.Destroy;
var
  i: Integer;
  FunctionInfo: PFunctionInfo;
  VariableInfo: PVariableInfo;
begin
  for i := 0 to FFunctions.Count - 1 do
  begin
    FunctionInfo := PFunctionInfo(FFunctions[i]);
    FreeMem(FunctionInfo);
  end;
  FFunctions.Free;
  for i := 0 to FVariables.Count - 1 do
  begin
    VariableInfo := PVariableInfo(FVariables[i]);
    If VariableInfo^.Local Then
       VariableInfo^.Variable.Release;
    FreeMem(VariableInfo);
  end;
  FVariables.Free;
  FVariablesStack.Free;
  for i := 0 to FUndoStack.Count - 1 Do
    begin
      If Not PUndoInfo(FUndoStack[i])^.Inserted Then
         PUndoInfo(FUndoStack[i])^.ThisNode.Free;
      Dispose(PUndoInfo(FUndoStack[i]))
    end;
  FUndoStack.Free;
  FLocalWords.Free;
  FCollectedWords.Free;
  FLocalRels.Free;
  FCollectedRels.Free;
  inherited Destroy;
end;

procedure TXPathEnvironment.setGID(GID: Integer);
begin
  FGID := GID
end;

function TXPathEnvironment.Clone: TXPathEnvironment;

Var F, G: Integer;
    Nm: Array Of String;
begin
  Result := TXPathEnvironment.Create;

  Result.FLocalWords.Assign(LocalWords);
  Result.FCollectedWords.Assign(CollectedWords);
  Result.FLocalRels.Assign(LocalRels);
  Result.FCollectedRels.Assign(CollectedRels);

  Result.FNodeNameTester := NodeNameTester;
  For F := 0 To FVariables.Count - 1 Do
      Result.AddVariable(PVariableInfo(FVariables[F])^.Name, PVariableInfo(FVariables[F])^.Variable.Clone, PVariableInfo(FVariables[F])^.Local);
  For F := 0 To FFunctions.Count - 1 Do
    If Not Assigned(PFunctionInfo(FFunctions[F])^.Fn) Then
      begin
        SetLength(Nm, Length(PFunctionInfo(FFunctions[F])^.ArgNames));
        For G := Low(PFunctionInfo(FFunctions[F])^.ArgNames) To High(PFunctionInfo(FFunctions[F])^.ArgNames) Do
          begin
            Nm[G] := '$' + PFunctionInfo(FFunctions[F])^.ArgNames[G];
            if PFunctionInfo(FFunctions[F])^.ArgRefs[G] Then
               Nm[G] := '&' + Nm[G]
          end;
        Result.AddFunction(PFunctionInfo(FFunctions[F])^.Name, Nil, PFunctionInfo(FFunctions[F])^.EvalArgs, Nm, PFunctionInfo(FFunctions[F])^.Body)
      end;
end;

procedure TXPathEnvironment.startTransaction;
begin
  if FTransaction >= 0 Then
     EvaluationError(SEvalNestedTransaction);
  FTransaction := getUndoLabel
end;

procedure TXPathEnvironment.commitTransaction;

Var Level: Integer;
begin
  if FTransaction < 0 Then
     EvaluationError(SEvalCommitNoTransaction);
  Level := FTransaction;
  FTransaction := -1;
  commitUndo(Level)
end;

procedure TXPathEnvironment.rollbackTransaction(const Construct: TNodeSet);

Var Level: Integer;
begin
  if FTransaction < 0 Then
     EvaluationError(SEvalRollbackNoTransaction);
  Level := FTransaction;
  FTransaction := -1;
  rollbackUndo(Level, Construct)
end;

procedure TXPathEnvironment.pushUndo(Inserted: Boolean; ThisNode, NextNode,
  ParentNode: TDOMNode);

Var P: PUndoInfo;
begin
  New(P);
  P^.Inserted := Inserted;
  P^.ThisNode := ThisNode;
  P^.NextNode := NextNode;
  P^.ParentNode := ParentNode;
  FUndoStack.Add(P);
end;

function TXPathEnvironment.getUndoLabel: Integer;
begin
  Result := FUndoStack.Count
end;

procedure TXPathEnvironment.commitUndo(ToLabel: Integer);

Var P: PUndoInfo;
begin
  If FTransaction >= 0 Then Exit;
  While ToLabel <> FUndoStack.Count Do
    Begin
      P := PUndoInfo(FUndoStack[ToLabel]);
      If Not P^.Inserted Then
         P^.ThisNode.Free;
      Dispose(P);
      FUndoStack.Delete(ToLabel)
    End
end;

procedure TXPathEnvironment.rollbackUndo(ToLabel: Integer;
  const Construct: TNodeSet);

Var P: PUndoInfo;
    F: Integer;
begin
  If FTransaction >= 0 Then Exit;
  While ToLabel <> FUndoStack.Count Do
    Begin
      P := PUndoInfo(FUndoStack[FUndoStack.Count - 1]);
      If P^.Inserted Then
         Begin
           P^.ParentNode.RemoveChild(P^.ThisNode);
           P^.ThisNode.Free;
           If Assigned(Construct) Then
              begin
                 F := Construct.IndexOf(P^.ThisNode);
                 If F >= 0 Then
                    Construct.Delete(F)
              end
         end
      Else
         P^.ParentNode.InsertBefore(P^.ThisNode, P^.NextNode);
      Dispose(P);
      FUndoStack.Delete(FUndoStack.Count - 1)
    End;
end;

procedure TXPathEnvironment.pushVariables;
begin
  FVariablesStack.Add(FVariables);
  FVariables := TFPList.Create
end;

procedure TXPathEnvironment.popVariables;

Var i: Integer;
    VariableInfo: PVariableInfo;
begin
  for i := 0 to FVariables.Count - 1 do
  begin
    VariableInfo := PVariableInfo(FVariables[i]);
    If VariableInfo^.Local Then
       VariableInfo^.Variable.Release;
    FreeMem(VariableInfo);
  end;
  FVariables.Free;
  FVariables := TFPList(FVariablesStack.Last);
  FVariablesStack.Delete(FVariablesStack.Count - 1)
end;

function TXPathEnvironment.GetFunctionIndex(const AName: String): Integer;
var
  i: Integer;
begin
  for i := 0 to FFunctions.Count - 1 do
    if PFunctionInfo(FFunctions[i])^.Name = AName then
    begin
      Result := i;
      exit;
    end;
  Result := -1;
end;

function TXPathEnvironment.GetVariableIndex(const AName: String): Integer;
var
  i: Integer;
begin
  for i := 0 to FVariables.Count - 1 do
    if PVariableInfo(FVariables[i])^.Name = AName then
    begin
      Result := i;
      exit;
    end;
  Result := -1;
end;

procedure TXPathEnvironment.AddFunction(const AName: String;
  AFunction: TXPathFunction; EvalArgs: Boolean;
  const Args: array of String; const Body: String);
var
  NewFunctionInfo: PFunctionInfo;
  S: String;
  F: Integer;
begin
  // !!!: Prevent the addition of duplicate functions
  If Assigned(FunctionsByName[AName]) Then
     Exit;
  New(NewFunctionInfo);
  NewFunctionInfo^.Name := AName;
  NewFunctionInfo^.Fn := AFunction;
  NewFunctionInfo^.EvalArgs := EvalArgs;
  NewFunctionInfo^.Body := Body;
  If Length(Args) > 0 Then
     Begin
       SetLength(NewFunctionInfo^.ArgNames, Length(Args));
       SetLength(NewFunctionInfo^.ArgRefs, Length(Args));
       For F := Low(Args) To High(Args) Do
         Begin
           NewFunctionInfo^.ArgRefs[F] := False;
           NewFunctionInfo^.ArgNames[F] := '';
           If Length(Args[F]) > 1 Then
              Begin
                If Args[F][1] = '&' Then
                   Begin
                     NewFunctionInfo^.ArgRefs[F] := True;
                     S := Copy(Args[F], 2, 1024)
                   end
                Else
                   S := Args[F];
                If S[1] = '$' Then
                   NewFunctionInfo^.ArgNames[F] := Copy(S, 2, 1024)
                Else
                   NewFunctionInfo^.ArgNames[F] := S
              End;
         End
     End
  Else
     Begin
       SetLength(NewFunctionInfo^.ArgNames, 0);
       SetLength(NewFunctionInfo^.ArgRefs, 0);
     End;
  FFunctions.Add(NewFunctionInfo);
end;

procedure TXPathEnvironment.AddVariable(const AName: String;
  AVariable: TXPathVariable; const local: Boolean);
var
  NewVariableInfo: PVariableInfo;
begin
  // !!!: Prevent the addition of duplicate variables
  If Assigned(VariablesByName[AName]) Then
     Exit;
  New(NewVariableInfo);
  NewVariableInfo^.Name := AName;
  NewVariableInfo^.Variable := AVariable;
  NewVariableInfo^.Local := local;
  FVariables.Add(NewVariableInfo);
end;

procedure TXPathEnvironment.RemoveFunction(Index: Integer);
var
  FunctionInfo: PFunctionInfo;
begin
  FunctionInfo := PFunctionInfo(FFunctions[Index]);
  Dispose(FunctionInfo);
  FFunctions.Delete(Index);
end;

procedure TXPathEnvironment.RemoveFunction(const AName: String);
var
  i: Integer;
begin
  for i := 0 to FFunctions.Count - 1 do
    if PFunctionInfo(FFunctions[i])^.Name = AName then
    begin
      RemoveFunction(i);
      exit;
    end;
end;

procedure TXPathEnvironment.RemoveVariable(Index: Integer);
var
  VariableInfo: PVariableInfo;
begin
  VariableInfo := PVariableInfo(FVariables[Index]);
  If VariableInfo^.Local Then
     VariableInfo^.Variable.Free;
  Dispose(VariableInfo);
  FVariables.Delete(Index);
end;

procedure TXPathEnvironment.RemoveVariable(const AName: String);
var
  Index: Integer;
begin
  Index := GetVariableIndex(AName);
  if Index >= 0 then
    RemoveVariable(Index);
end;

procedure TXPathEnvironment.AcceptLocalWordsRels;
begin
  CollectedWords.AddStrings(LocalWords);
  LocalWords.Clear;
  CollectedRels.AddStrings(LocalRels);
  LocalRels.Clear
end;

procedure TXPathEnvironment.Export(outS: PChar);

Var F, G: Integer;
begin
  With TStringList.Create Do
    Begin
      Add(IntToStr(FFunctions.Count));
      For F := 0 To FFunctions.Count-1 Do
          Begin
            Add(PFunctionInfo(FFunctions[F])^.Name);
            Add(IntToStr(Length(PFunctionInfo(FFunctions[F])^.ArgNames)));
            For G := 0 To Length(PFunctionInfo(FFunctions[F])^.ArgNames)-1 Do
                Add(PFunctionInfo(FFunctions[F])^.ArgNames[G]);
            Add(IntToStr(Length(PFunctionInfo(FFunctions[F])^.ArgRefs)));
            For G := 0 To Length(PFunctionInfo(FFunctions[F])^.ArgRefs)-1 Do
                Add(BoolVals[PFunctionInfo(FFunctions[F])^.ArgRefs[G]]);
            Add(EscapeCRLF(PFunctionInfo(FFunctions[F])^.Body));
            Add(BoolVals[PFunctionInfo(FFunctions[F])^.EvalArgs])
          End;
      Add(IntToStr(FVariables.Count));
      For F := 0 To FVariables.Count-1 Do
          Begin
            Add(PVariableInfo(FVariables[F])^.Name);
            Add(BoolVals[PVariableInfo(FVariables[F])^.Local]);
            Add(PVariableInfo(FVariables[F])^.Variable.Export());
          End;
      Add(IntToStr(FCollectedWords.Count));
      AddStrings(FCollectedWords);
      Add(IntToStr(FLocalWords.Count));
      AddStrings(FLocalWords);
      Add(IntToStr(FCollectedRels.Count));
      AddStrings(FCollectedRels);
      Add(IntToStr(FLocalRels.Count));
      AddStrings(FLocalRels);
      StrPCopy(outS, String(Text));
      Free
    End
end;

procedure TXPathEnvironment.Import(inS: PChar);

Var F, G, K: Integer;
    Name: String;
    ArgNames: Array Of String;
    ArgRefs: Array Of Boolean;
    Body: String;
    Local: Boolean;
    EvalArgs: Boolean;
begin
  With TStringList.Create Do
    Begin
      Text := String(inS);
      F := 0;
      G := StrToInt(Strings[F]); Inc(F);
      While G > 0 Do
          Begin
            Name := Strings[F]; Inc(F);
            SetLength(ArgNames, StrToInt(Strings[F])); Inc(F);
            For K := 0 To Length(ArgNames)-1 Do
                Begin
                  ArgNames[K] := Strings[F]; Inc(F)
                End;
            SetLength(ArgRefs, StrToInt(Strings[F])); Inc(F);
            For K := 0 To Length(ArgRefs)-1 Do
                Begin
                  If Strings[F] = BoolVals[True] Then
                     ArgRefs[K] := True
                  Else If Strings[F] = BoolVals[False] Then
                     ArgRefs[K] := False
                  Else
                     raise Exception.Create('ArgRefs : ? ' + Strings[F]);
                  Inc(F)
                End;
            Body := UnEscapeCRLF(Strings[F]); Inc(F);
            If Strings[F] = BoolVals[True] Then
               EvalArgs := True
            Else If Strings[F] = BoolVals[False] Then
               EvalArgs := False
            Else
               raise Exception.Create('EvalArgs : ? ' + Strings[F]);
            Inc(F);
            For K := 0 To Length(ArgNames)-1 Do
                If ArgRefs[K] Then
                   ArgNames[K] := '&' + ArgNames[K];
            AddFunction(Name, Nil, EvalArgs, ArgNames, Body);
            Dec(G)
          End;
      G := StrToInt(Strings[F]); Inc(F);
      While G > 0 Do
          Begin
            Name := Strings[F]; Inc(F);
            If Strings[F] = BoolVals[True] Then
               Local := True
            Else If Strings[F] = BoolVals[False] Then
               Local := False
            Else
               raise Exception.Create('Local : ? ' + Strings[F]);
            Inc(F);
            If Not Assigned(VariablesByName[Name]) Then
               AddVariable(Name, TXPathVariable.Import(Strings[F]), Local)
            Else
               Begin
                 VariablesByName[Name].Free;
                 VariablesByName[Name] := TXPathVariable.Import(Strings[F])
               end;
            Inc(F);
            Dec(G)
          End;
      G := StrToInt(Strings[F]); Inc(F);
      FCollectedWords.Clear;
      While G > 0 Do
        Begin
          FCollectedWords.Add(Strings[F]); Inc(F);
          Dec(G)
        end;
      G := StrToInt(Strings[F]); Inc(F);
      FLocalWords.Clear;
      While G > 0 Do
        Begin
          FLocalWords.Add(Strings[F]); Inc(F);
          Dec(G)
        end;
      G := StrToInt(Strings[F]); Inc(F);
      FCollectedRels.Clear;
      While G > 0 Do
        Begin
          FCollectedRels.Add(Strings[F]); Inc(F);
          Dec(G)
        end;
      G := StrToInt(Strings[F]); Inc(F);
      FLocalRels.Clear;
      While G > 0 Do
        Begin
          FLocalRels.Add(Strings[F]); Inc(F);
          Dec(G)
        end;
      Free
    End
end;

function TXPathEnvironment.GetFunctionCount: Integer;
begin
  Result := FFunctions.Count;
end;

function TXPathEnvironment.GetVariableCount: Integer;
begin
  Result := FVariables.Count;
end;

function TXPathEnvironment.GetFunction(Index: Integer): PFunctionInfo;
begin
  Result := PFunctionInfo(FFunctions[Index])
end;

function TXPathEnvironment.GetFunction(const AName: String): PFunctionInfo;
var
  i: Integer;
begin
  for i := 0 to FFunctions.Count - 1 do
    if PFunctionInfo(FFunctions[i])^.Name = AName then
    begin
      Result := PFunctionInfo(FFunctions[i]);
      exit;
    end;
  Result := nil;
end;

function TXPathEnvironment.GetVariable(Index: Integer): TXPathVariable;
begin
  Result := PVariableInfo(FVariables[Index])^.Variable;
end;

function TXPathEnvironment.GetVariable(const AName: String): TXPathVariable;
var
  i: Integer;
begin
  for i := 0 to FVariables.Count - 1 do
    if PVariableInfo(FVariables[i])^.Name = AName then
    begin
      Result := PVariableInfo(FVariables[i])^.Variable;
      exit;
    end;
  Result := nil;
end;

procedure TXPathEnvironment.SetVariable(Index: Integer;
  const Val: TXPathVariable);
begin
  If Assigned(PVariableInfo(FVariables[Index])^.Variable) Then
     PVariableInfo(FVariables[Index])^.Variable.Release;
  PVariableInfo(FVariables[Index])^.Variable := Val.Clone
end;

procedure TXPathEnvironment.SetVariable(const AName: String;
  const Val: TXPathVariable);
begin
  SetVariable(GetVariableIndex(AName), Val)
end;

function TXPathEnvironment.spEval(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList
  ): TXPathVariable;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  Result := EvaluateXPathExpression(TXPathVariable(Args[0]).AsText, Context.ContextNode, NodeNameTester, [Nil, Nil, Context.ContextNode], Context.Construct, Nil, Self);
end;

function TXPathEnvironment.spMin(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList
  ): TXPathVariable;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  if (TObject(Args[0]) is TXPathStringVariable) And (TObject(Args[1]) is TXPathStringVariable) Then
     if TXPathStringVariable(Args[0]).AsText < TXPathStringVariable(Args[1]).AsText Then
        Result := TXPathStringVariable.Create(TXPathStringVariable(Args[0]).AsText)
     else
        Result := TXPathStringVariable.Create(TXPathStringVariable(Args[1]).AsText)
  else if (TObject(Args[0]) is TXPathNodeSetVariable) And (TObject(Args[1]) is TXPathNodeSetVariable) Then
     Result := TXPathNumberVariable.Create(Math.Min(TXPathNodeSetVariable(Args[0]).AsNodeSet.Count, TXPathNodeSetVariable(Args[1]).AsNodeSet.Count))
  else Result := TXPathNumberVariable.Create(Math.Min(TXPathVariable(Args[0]).AsNumber, TXPathVariable(Args[1]).AsNumber))
end;

function TXPathEnvironment.spMax(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList
  ): TXPathVariable;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  if (TObject(Args[0]) is TXPathStringVariable) And (TObject(Args[1]) is TXPathStringVariable) Then
     if TXPathStringVariable(Args[0]).AsText > TXPathStringVariable(Args[1]).AsText Then
        Result := TXPathStringVariable.Create(TXPathStringVariable(Args[0]).AsText)
     else
        Result := TXPathStringVariable.Create(TXPathStringVariable(Args[1]).AsText)
  else if (TObject(Args[0]) is TXPathNodeSetVariable) And (TObject(Args[1]) is TXPathNodeSetVariable) Then
     Result := TXPathNumberVariable.Create(Math.Max(TXPathNodeSetVariable(Args[0]).AsNodeSet.Count, TXPathNodeSetVariable(Args[1]).AsNodeSet.Count))
  else Result := TXPathNumberVariable.Create(Math.Max(TXPathVariable(Args[0]).AsNumber, TXPathVariable(Args[1]).AsNumber))
end;

function TXPathEnvironment.spTransaction(AContext: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  Context: TXPathContext;
  PPtrs: Array Of TDOMNode;
  R: TXMLVarsList;
  i: Integer;
begin
   if Ref.ArgsCount <> 1 then
     EvaluationError(SEvalInvalidArgCount);
   SetLength(PPtrs, 3);
   For i := 0 To Length(AContext.Ptrs) Do
       PPtrs[i] := AContext.Ptrs[i];
   PPtrs[2] := AContext.ContextNode;
   Context := TXPathContext.Create(AContext.ContextNode, AContext.ContextPosition, AContext.ContextSize, PPtrs, Nil);
   try
     startTransaction;
     Result := Ref.ArgNodes[0].Evaluate(Context, Self, R);
     R.Free;
     If Result.AsBoolean Then
        commitTransaction
     Else
        rollbackTransaction(Nil);
   finally
     Context.Free;
   end
end;

function TXPathEnvironment.spSet(AContext: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Ref.ArgsCount <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  if Not (Ref.ArgNodes[0] is TXPathVariableNode) Then
    EvaluationError(SEvalNotVarByRef, ['set', 'arg1']);
  TXPathVariable(Args.Items[1]).MarkPolled;
  Variables[TXPathVariableNode(Ref.ArgNodes[0]).FName] := TXPathVariable(Args.Items[1]);
  Result := TXPathBooleanVariable.Create(True);
end;

function TXPathEnvironment.spCreate(AContext: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  Context: TXPathContext;
  Construct: TNodeSet;
  PPtrs: Array Of TDOMNode;
  R: TXMLVarsList;
  Level: Integer;
  i: Integer;
begin
   if Ref.ArgsCount <> 1 then
     EvaluationError(SEvalInvalidArgCount);
   Construct := TNodeSet.Create;
   SetLength(PPtrs, 3);
   For i := 0 To Length(AContext.Ptrs) Do
       PPtrs[i] := AContext.Ptrs[i];
   PPtrs[2] := AContext.ContextNode;
   Context := TXPathContext.Create(AContext.ContextNode, AContext.ContextPosition, AContext.ContextSize, PPtrs, Construct);
   try
     Level := getUndoLabel;
     Result := Ref.ArgNodes[0].Evaluate(Context, Self, R);
     R.Free;
     commitUndo(Level);
     Result.Release;
     Result := TXPathBooleanVariable.Create(True)
   finally
     Context.Free;
     Construct.Free;
   end
end;

function TXPathEnvironment.spDelete(AContext: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  Context: TXPathContext;
  PPtrs: Array Of TDOMNode;
  R: TXMLVarsList;
  This: TDOMElement;
  Level: Integer;
  i: Integer;
begin
   if Ref.ArgsCount <> 1 then
     EvaluationError(SEvalInvalidArgCount);
   SetLength(PPtrs, 3);
   For i := 0 To Length(AContext.Ptrs) Do
       PPtrs[i] := AContext.Ptrs[i];
   PPtrs[2] := AContext.ContextNode;
   Context := TXPathContext.Create(AContext.ContextNode, AContext.ContextPosition, AContext.ContextSize, PPtrs, Nil);
   try
     Level := getUndoLabel;
     Result := Ref.ArgNodes[0].Evaluate(Context, Self, R);
     R.Free;
     If Result is TXPathNodeSetVariable Then
        begin
           for i := 0 To Result.AsNodeSet.Count - 1 Do
               begin
                 This := TObject(Result.AsNodeSet[i]) As TDOMElement;
                 pushUndo(False, This, This.NextSibling, This.ParentNode);
                 This.ParentNode.RemoveChild(This)
               end;
        end;
     commitUndo(Level);
     Result.Release;
     Result := TXPathBooleanVariable.Create(True)
   finally
     Context.Free;
   end
end;

function TXPathEnvironment.xpLast(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 0 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathNumberVariable.Create(Context.ContextSize);
end;

function TXPathEnvironment.xpPosition(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 0 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathNumberVariable.Create(Context.ContextPosition);
end;

function TXPathEnvironment.xpCount(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathNumberVariable.Create(TXPathVariable(Args[0]).AsNodeSet.Count);
end;

function TXPathEnvironment.xpId(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  i: Integer;
  ResultSet: TNodeSet;
  TheArg: TXPathVariable;
  doc: TDOMDocument;

  procedure AddId(ns: TNodeSet; const s: DOMString);
  var
    Head, Tail, L: Integer;
    Token: DOMString;
    Element: TDOMNode;
  begin
    Head := 1;
    L := Length(s);

    while Head <= L do
    begin
      while (Head <= L) and IsXmlWhiteSpace(s[Head]) do
        Inc(Head);

      Tail := Head;
      while (Tail <= L) and not IsXmlWhiteSpace(s[Tail]) do
        Inc(Tail);
      SetString(Token, @s[Head], Tail - Head);
      Element := doc.GetElementById(Token);
      if Assigned(Element) then
        ns.Add(Element);

      Head := Tail;
    end;
  end;

begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  // TODO: probably have doc as member of Context
  if Context.ContextNode.NodeType = DOCUMENT_NODE then
    doc := TDOMDocument(Context.ContextNode)
  else
    doc := Context.ContextNode.OwnerDocument;

  ResultSet := TNodeSet.Create;
  TheArg := TXPathVariable(Args[0]);
  if TheArg is TXPathNodeSetVariable then
  begin
    with TheArg.AsNodeSet do
      for i := 0 to Count-1 do
        AddId(ResultSet, NodeToText(TDOMNode(Items[i])));
  end
  else
    AddId(ResultSet, TheArg.AsText);
  Result := TXPathNodeSetVariable.Create(ResultSet);
end;

function TXPathEnvironment.xpLocalName(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  n: TDOMNode;
  NodeSet: TNodeSet;
  s: DOMString;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  n := nil;
  if Args.Count = 0 then
    n := Context.ContextNode
  else
  begin
    NodeSet := TXPathVariable(Args[0]).AsNodeSet;
    if NodeSet.Count > 0 then
      n := TDOMNode(NodeSet[0]);
  end;
  s := '';
  if Assigned(n) then
  begin
    case n.NodeType of
      ELEMENT_NODE,ATTRIBUTE_NODE:
        with TDOMNode_NS(n) do
          s := Copy(NSI.QName^.Key, NSI.PrefixLen+1, MaxInt);
      PROCESSING_INSTRUCTION_NODE:
        s := TDOMProcessingInstruction(n).Target;
      // TODO: NAMESPACE_NODE: must return prefix part
    end;
  end;
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpNamespaceURI(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  n: TDOMNode;
  NodeSet: TNodeSet;
  s: DOMString;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  n := nil;
  if Args.Count = 0 then
    n := Context.ContextNode
  else
  begin
    NodeSet := TXPathVariable(Args[0]).AsNodeSet;
    if NodeSet.Count > 0 then
      n := TDOMNode(NodeSet[0]);
  end;
  if Assigned(n) then
    s := n.namespaceUri
  else
    s := '';
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpName(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  n: TDOMNode;
  NodeSet: TNodeSet;
  s: DOMString;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  n := nil;
  if Args.Count = 0 then
    n := Context.ContextNode
  else
  begin
    NodeSet := TXPathVariable(Args[0]).AsNodeSet;
    if NodeSet.Count > 0 then
      n := TDOMNode(NodeSet[0]);
  end;
  s := '';
  if Assigned(n) then
  begin
    case n.NodeType of
      ELEMENT_NODE,ATTRIBUTE_NODE:
        s := TDOMNode_NS(n).NSI.QName^.Key;
      PROCESSING_INSTRUCTION_NODE:
        s := TDOMProcessingInstruction(n).Target;
      // TODO: NAMESPACE_NODE: must return prefix part
    end;
  end;
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpString(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s: DOMString;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  if Args.Count = 0 then
    s := NodeToText(Context.ContextNode)
  else
    s := TXPathVariable(Args[0]).AsText;
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpConcat(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  i: Integer;
  s: DOMString;
begin
  if Args.Count < 2 then
    EvaluationError(SEvalInvalidArgCount);
  SetLength(s, 0);
  for i := 0 to Args.Count - 1 do
    s := s + TXPathVariable(Args[i]).AsText;
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpStartsWith(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s1, s2: DOMString;
  res: Boolean;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  s1 := TXPathVariable(Args[0]).AsText;
  s2 := TXPathVariable(Args[1]).AsText;
  if s2 = '' then
    res := True
  else
    res := Pos(s2, s1) = 1;
  Result := TXPathBooleanVariable.Create(res);
end;

function TXPathEnvironment.xpContains(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s1, s2: DOMString;
  res: Boolean;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  s1 := TXPathVariable(Args[0]).AsText;
  s2 := TXPathVariable(Args[1]).AsText;
  if s2 = '' then
    res := True
  else
    res := Pos(s2, s1) <> 0;
  Result := TXPathBooleanVariable.Create(res);
end;

function TXPathEnvironment.xpSubstringBefore(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s, substr: DOMString;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  s := TXPathVariable(Args[0]).AsText;
  substr := TXPathVariable(Args[1]).AsText;
  Result := TXPathStringVariable.Create(Copy(s, 1, Pos(substr, s)-1));
end;

function TXPathEnvironment.xpSubstringAfter(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s, substr: DOMString;
  i: Integer;
begin
  if Args.Count <> 2 then
    EvaluationError(SEvalInvalidArgCount);
  s := TXPathVariable(Args[0]).AsText;
  substr := TXPathVariable(Args[1]).AsText;
  i := Pos(substr, s);
  if i <> 0 then
    Result := TXPathStringVariable.Create(Copy(s, i + Length(substr), MaxInt))
  else
    Result := TXPathStringVariable.Create('');
end;

function TXPathEnvironment.xpSubstring(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s: DOMString;
  i, n1, n2: Integer;
  e1, e2: Extended;
  empty: Boolean;
begin
  if (Args.Count < 2) or (Args.Count > 3) then
    EvaluationError(SEvalInvalidArgCount);
  s := TXPathVariable(Args[0]).AsText;
  e1 := TXPathVariable(Args[1]).AsNumber;
  n1 := 1;  // satisfy compiler
  n2 := MaxInt;
  empty := IsNaN(e1) or IsInfinite(e1);
  if not empty then
    n1 := floor(0.5 + e1);
  if Args.Count = 3 then
  begin
    e2 := TXPathVariable(Args[2]).AsNumber;
    if IsNaN(e2) or (IsInfinite(e2) and (e2 < 0)) then
      empty := True
    else if not IsInfinite(e2) then
      n2 := floor(0.5 + e2);
  end;
  i := Max(n1, 1);
  if empty then
    n2 := -1
  else if n2 < MaxInt then
    n2 := n2 + (n1 - i);
  Result := TXPathStringVariable.Create(Copy(s, i, n2));
end;

function TXPathEnvironment.xpStringLength(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s: DOMString;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  if Args.Count = 0 then
    s := NodeToText(Context.ContextNode)
  else
    s := TXPathVariable(Args[0]).AsText;
  Result := TXPathNumberVariable.Create(Length(s));
end;

function TXPathEnvironment.xpNormalizeSpace(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  s: DOMString;
  p: DOMPChar;
  i: Integer;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  if Args.Count = 0 then
    s := NodeToText(Context.ContextNode)
  else
    s := TXPathVariable(Args[0]).AsText;
  UniqueString(s);
  p := DOMPChar(s);
  for i := 1 to Length(s) do
  begin
    if (p^ = #10) or (p^ = #13) or (p^ = #9) then
      p^ := #32;
    Inc(p);  
  end;
  NormalizeSpaces(s);
  Result := TXPathStringVariable.Create(s);
end;

function TXPathEnvironment.xpTranslate(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  S: DOMString;
begin
  if Args.Count <> 3 then
    EvaluationError(SEvalInvalidArgCount);
  S := TXPathVariable(Args[0]).AsText;
  TranslateWideString(S, TXPathVariable(Args[1]).AsText, TXPathVariable(Args[2]).AsText);
  Result := TXPathStringVariable.Create(S);
end;

function TXPathEnvironment.xpBoolean(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathBooleanVariable.Create(TXPathVariable(Args[0]).AsBoolean);
end;

function TXPathEnvironment.xpNot(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathBooleanVariable.Create(not TXPathVariable(Args[0]).AsBoolean);
end;

function TXPathEnvironment.xpTrue(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 0 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathBooleanVariable.Create(True);
end;

function TXPathEnvironment.xpFalse(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count <> 0 then
    EvaluationError(SEvalInvalidArgCount);
  Result := TXPathBooleanVariable.Create(False);
end;

function TXPathEnvironment.xpLang(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  L: Integer;
  TheArg, NodeLang: DOMString;
  res: Boolean;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  TheArg := TXPathVariable(Args[0]).AsText;
  NodeLang := GetNodeLanguage(Context.ContextNode);

  L := Length(TheArg);
  res := (L <= Length(NodeLang)) and
    (WStrLIComp(DOMPChar(NodeLang), DOMPChar(TheArg), L) = 0) and
    ((L = Length(NodeLang)) or (NodeLang[L+1] = '-'));

  Result := TXPathBooleanVariable.Create(res);
end;

function TXPathEnvironment.xpNumber(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
  if Args.Count > 1 then
    EvaluationError(SEvalInvalidArgCount);
  if Args.Count = 0 then
    Result := TXPathNumberVariable.Create(StrToNumber(NodeToText(Context.ContextNode)))
  else
    Result := TXPathNumberVariable.Create(TXPathVariable(Args[0]).AsNumber);
end;

function TXPathEnvironment.xpSum(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  i: Integer;
  ns: TNodeSet;
  sum: Extended;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  ns := TXPathVariable(Args[0]).AsNodeSet;
  sum := 0.0;
  for i := 0 to ns.Count-1 do
    sum := sum + StrToNumber(NodeToText(TDOMNode(ns[i])));
  Result := TXPathNumberVariable.Create(sum);
end;

function TXPathEnvironment.xpFloor(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  n: Extended;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  n := TXPathVariable(Args[0]).AsNumber;
  if not IsNan(n) then
    n := floor(n);
  Result := TXPathNumberVariable.Create(n);
end;

function TXPathEnvironment.xpCeiling(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  n: Extended;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  n := TXPathVariable(Args[0]).AsNumber;
  if not IsNan(n) then
    n := ceil(n);
  Result := TXPathNumberVariable.Create(n);
end;

function TXPathEnvironment.xpRound(Context: TXPathContext; Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
var
  num: Extended;
begin
  if Args.Count <> 1 then
    EvaluationError(SEvalInvalidArgCount);
  num := TXPathVariable(Args[0]).AsNumber;
  if not (IsNan(num) or IsInfinite(num)) then
    num := floor(0.5 + num);
  Result := TXPathNumberVariable.Create(num);
end;

function TXPathEnvironment.xpGID(Context: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
    if Args.Count <> 0 then
      EvaluationError(SEvalInvalidArgCount);
    Result := TXPathNumberVariable.Create(FGID);
end;

function TXPathEnvironment.xpRandom(Context: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;
begin
    if Args.Count <> 0 then
      EvaluationError(SEvalInvalidArgCount);
    Result := TXPathNumberVariable.Create(Random);
end;

function TXPathEnvironment.xpRandomID(Context: TXPathContext;
  Ref: TXPathFunctionNode; Args: TXPathVarList): TXPathVariable;

Const LEN = 8;

Var V: DOMString;
    F: Integer;
begin
    if Args.Count <> 0 then
      EvaluationError(SEvalInvalidArgCount);
    SetLength(V, LEN);
    For F := 1 To LEN Do
        V[F] := Chr(Ord('a') + Random(26));
    Result := TXPathStringVariable.Create(V);
end;

{ TXPathNSResolver }

constructor TXPathNSResolver.Create(aNode: TDOMNode);
begin
  inherited Create;
  FNode := aNode;
end;

function TXPathNSResolver.LookupNamespaceURI(const aPrefix: DOMString): DOMString;
begin
  if assigned(FNode) then
    result := FNode.LookupNamespaceURI(aPrefix)
  else
    result := '';
end;

function GetParsedExpression(Scanner: TXPathScanner; Var Created: Boolean): TXPathExprNode;

Var F: Integer;
    S: String;
Begin
   EnterCriticalSection(CS);
   S := UTF8Encode(WideString(Scanner.ExpressionString));
   F := Cache.IndexOf(S);
   Created := F < 0;
   If Not Created Then
      Result := Cache.Objects[F] As TXPathExprNode
   Else
      begin
        Result := Scanner.ParseOrExpr;
        Cache.AddObject(S, Result)
      end;
   LeaveCriticalSection(CS)
end;

{ TXPathExpression }

constructor TXPathExpression.Create(AScanner: TXPathScanner;
  CompleteExpression: Boolean; AResolver: TXPathNSResolver);

Var Created: Boolean;
begin
  inherited Create;
  AScanner.FResolver := AResolver;
  FRootNode := GetParsedExpression(AScanner, Created);
  If Created Then
     if CompleteExpression and (AScanner.CurToken <> tkEndOfStream) then
        EvaluationError(SParserGarbageAfterExpression);
end;

function TXPathExpression.Evaluate(AContextNode: TDOMNode; NodeNameTester: TXPathNodeNameTester; const Ptrs: array of TDOMNode; const Construct: TNodeSet): TXPathVariable;
var
  Environment: TXPathEnvironment;
begin
  Environment := TXPathEnvironment.Create;
  Environment.NodeNameTester := NodeNameTester;
  try
    Result := Evaluate(AContextNode, Environment, Ptrs, Construct);
  finally
    Environment.Free;
  end;
end;

destructor TXPathExpression.Destroy;
begin
  // FRootNode.Free;
  inherited Destroy;
end;

function TXPathExpression.Evaluate(AContextNode: TDOMNode;
  AEnvironment: TXPathEnvironment; const Ptrs: array of TDOMNode; const Construct: TNodeSet): TXPathVariable;
var
  Context: TXPathContext;
  mask: TFPUExceptionMask;
  R: TXMLVarsList;
begin
  if Assigned(FRootNode) then
  begin
    mask := GetExceptionMask;
    SetExceptionMask(mask + [exInvalidOp, exZeroDivide]);
    Context := TXPathContext.Create(AContextNode, 1, 1, Ptrs, Construct);
    try
      Result := FRootNode.Evaluate(Context, AEnvironment, R);
      R.Free;
    finally
      Context.Free;
      SetExceptionMask(mask);
    end;
  end else
    Result := nil;
end;

function EvaluateXPathExpression(const AExpressionString: DOMString;
  AContextNode: TDOMNode; NodeNameTester: TXPathNodeNameTester;
  const Ptrs: array of TDOMNode; const Construct: TNodeSet; AResolver: TXPathNSResolver;
  AEnv: TXPathEnvironment): TXPathVariable;
var
  Scanner: TXPathScanner;
  Expression: TXPathExpression;
  Res: TXPathVariable;
begin
  Scanner := TXPathScanner.Create(AExpressionString);
  try
    Expression := TXPathExpression.Create(Scanner, True, AResolver);
    try
      If Not Assigned(AEnv) Then
         Result := Expression.Evaluate(AContextNode, NodeNameTester, Ptrs, Construct)
      Else
        begin
          AEnv.NodeNameTester := NodeNameTester;
          Result := Expression.Evaluate(AContextNode, AEnv, Ptrs, Construct)
        end;
      If Assigned(AEnv) Then
         begin
            Res := AEnv.VariablesByName['result'];
            If Assigned(Res) And Res.IsBound Then
               begin
                 Result.Release;
                 Result := Res.Clone
               end
         end;
    finally
      Expression.Free;
    end;
  finally
    Scanner.Free;
  end;
end;

Initialization
   Cache := TObjStrList.Create;
   Cache.Sorted := True;
   Cache.CaseSensitive := True;
   InitCriticalSection(CS);

Finalization
   // Cache.Free;
   DoneCriticalSection(CS);

end.
