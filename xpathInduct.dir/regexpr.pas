unit RegExpr;

{ Modified by V.V.Pekunov, 2017-2020 }

{$IF DEFINED(UNIX) OR DEFINED(LINUX)}
{$linklib c}
{$linklib stdc++}
{$ENDIF}

{$CODEPAGE UTF8}

{
     TRegExpr class library
     Delphi Regular Expressions

 Copyright (c) 1999-2004 Andrey V. Sorokin, St.Petersburg, Russia

 You can choose to use this Pascal unit in one of the two following licenses:

 Option 1>

 You may use this software in any kind of development,
 including comercial, redistribute, and modify it freely,
 under the following restrictions :
 1. This software is provided as it is, without any kind of
    warranty given. Use it at Your own risk.The author is not
    responsible for any consequences of use of this software.
 2. The origin of this software may not be mispresented, You
    must not claim that You wrote the original software. If
    You use this software in any kind of product, it would be
    appreciated that there in a information box, or in the
    documentation would be an acknowledgement like

     Partial Copyright (c) 2004 Andrey V. Sorokin
                                http://RegExpStudio.com
                                mailto:anso@mail.ru

 3. You may not have any income from distributing this source
    (or altered version of it) to other developers. When You
    use this product in a comercial package, the source may
    not be charged seperatly.
 4. Altered versions must be plainly marked as such, and must
    not be misrepresented as being the original software.
 5. RegExp Studio application and all the visual components as
    well as documentation is not part of the TRegExpr library
    and is not free for usage.

                                    mailto:anso@mail.ru
                                    http://RegExpStudio.com
                                    http://anso.da.ru/

  Option 2>

  The same modified LGPL with static linking exception as the Free Pascal RTL
}


interface

{off $DEFINE DebugSynRegExpr}

{$IFDEF FPC}
 {$MODE DELPHI} // Delphi-compatible mode in FreePascal
{$ENDIF}

// ======== Determine compiler
{$IFDEF VER80} Sorry, TRegExpr is for 32-bits Delphi only. Delphi 1 is not supported (and whos really care today?!). {$ENDIF}
{$IFDEF VER90} {$DEFINE D2} {$ENDIF} // D2
{$IFDEF VER93} {$DEFINE D2} {$ENDIF} // CPPB 1
{$IFDEF VER100} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // D3
{$IFDEF VER110} {$DEFINE D4} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // CPPB 3
{$IFDEF VER120} {$DEFINE D4} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // D4
{$IFDEF VER130} {$DEFINE D5} {$DEFINE D4} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // D5
{$IFDEF VER140} {$DEFINE D6} {$DEFINE D5} {$DEFINE D4} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // D6
{$IFDEF VER150} {$DEFINE D7} {$DEFINE D6} {$DEFINE D5} {$DEFINE D4} {$DEFINE D3} {$DEFINE D2} {$ENDIF} // D7

// ======== Define base compiler options
{$BOOLEVAL OFF}
{$EXTENDEDSYNTAX ON}
{$LONGSTRINGS ON}
{$IFNDEF FPC}
{$OPTIMIZATION ON}
{$ENDIF}
{$IFDEF D6}
  {$WARN SYMBOL_PLATFORM OFF} // Suppress .Net warnings
{$ENDIF}
{$IFDEF D7}
  {$WARN UNSAFE_CAST OFF} // Suppress .Net warnings
  {$WARN UNSAFE_TYPE OFF} // Suppress .Net warnings
  {$WARN UNSAFE_CODE OFF} // Suppress .Net warnings
{$ENDIF}

// ======== Define options for TRegExpr engine
{$DEFINE UniCode} // Unicode support
{$ifdef FPC_OS_UNICODE}
  {$define UNICODE}
{$endif}
{$DEFINE RegExpPCodeDump} // p-code dumping (see Dump method)
{$IFNDEF FPC} // the option is not supported in FreePascal
 {$DEFINE reRealExceptionAddr} // exceptions will point to appropriate source line, not to Error procedure
{$ENDIF}
{$DEFINE ComplexBraces} // support braces in complex cases
{$IFNDEF UniCode} // the option applicable only for non-UniCode mode
 {$IFNDEF FPC_REQUIRES_PROPER_ALIGNMENT}  //sets have to be aligned
 {$DEFINE UseSetOfChar} // Significant optimization by using set of char
 {$ENDIF}
{$ENDIF}
{$IFDEF UseSetOfChar}
 {$DEFINE UseFirstCharSet} // Fast skip between matches for r.e. that starts with determined set of chars
{$ENDIF}

// ======== Define Pascal-language options
// Define 'UseAsserts' option (do not edit this definitions).
// Asserts used to catch 'strange bugs' in TRegExpr implementation (when something goes
// completely wrong). You can swith asserts on/off with help of {$C+}/{$C-} compiler options.
{$IFDEF D3} {$DEFINE UseAsserts} {$ENDIF}
{$IFDEF FPC} {$DEFINE UseAsserts} {$ENDIF}

// Define 'use subroutine parameters default values' option (do not edit this definition).
{$IFDEF D4} {$DEFINE DefParam} {$ENDIF}

// Define 'OverMeth' options, to use method overloading (do not edit this definitions).
{$IFDEF D5} {$DEFINE OverMeth} {$ENDIF}
{$IFDEF FPC} {$DEFINE OverMeth} {$ENDIF}

uses
 Classes,  // TStrings in Split method
 Lexique,
 Common,
 Math,
 StrUtils,
 DateUtils,
 dynlibs,
 SysUtils,
 XPath; // Exception

type
 {$IFDEF UniCode}
 PRegExprChar = PWideChar;
 RegExprString = WideString;
 REChar = WideChar;
 {$ELSE}
 PRegExprChar = PChar;
 RegExprString = AnsiString; //###0.952 was string
 REChar = Char;
 {$ENDIF}
 TREOp = REChar; // internal p-code type //###0.933
 PREOp = ^TREOp;
 TRENextOff = PtrInt; // internal Next "pointer" (offset to current p-code) //###0.933
 PRENextOff = ^TRENextOff; // used for extracting Next "pointers" from compiled r.e. //###0.933
 TREBracesArg = integer; // type of {m,n} arguments
 PREBracesArg = ^TREBracesArg;

const
 dirParallel = 'parallel';
 dirSequential = 'sequential';

const
 fpFast = 'fast';
 fpNearest = 'nearest';
 fpNeuro = 'neuro';

const
 parPreStage = 4;
 parSimpleStage = 30;
 parFirstStage = 7;
 parSecondStage = 8;
 parSerie = parFirstStage+parSecondStage;
 nt1Shift = 0; // 0 -- without const a[0] (use all nt1Koeffs point), 1 -- with const a[0]
 nt1Koeffs = 4;
 ntnPower = 2;

const
 REOpSz = SizeOf (TREOp) div SizeOf (REChar); // size of p-code in RegExprString units
 {$IFDEF FPC_REQUIRES_PROPER_ALIGNMENT}
 // add space for aligning pointer
 // -1 is the correct max size but also needed for InsertOperator that needs a multiple of pointer size
 RENextOffSz = (2 * SizeOf (TRENextOff) div SizeOf (REChar))-1;
 REBracesArgSz = (2 * SizeOf (TREBracesArg) div SizeOf (REChar)); // add space for aligning pointer
 {$ELSE}
 RENextOffSz = (SizeOf (TRENextOff) div SizeOf (REChar)); // size of Next 'pointer' -"-
 REBracesArgSz = SizeOf (TREBracesArg) div SizeOf (REChar); // size of BRACES arguments -"-
 {$ENDIF}

type
 TRegExprInvertCaseFunction = function (const Ch : REChar) : REChar
                               of object;

const
  EscChar = '\'; // 'Escape'-char ('\' in common r.e.) used for escaping metachars (\w, \d etc).
  RegExprModifierI : boolean = False;    // default value for ModifierI
  RegExprModifierR : boolean = True;     // default value for ModifierR
  RegExprModifierS : boolean = True;     // default value for ModifierS
  RegExprModifierG : boolean = True;     // default value for ModifierG
  RegExprModifierM : boolean = False;    // default value for ModifierM
  RegExprModifierX : boolean = False;    // default value for ModifierX
  RegExprSpaceChars : RegExprString =    // default value for SpaceChars
  ' '#$9#$A#$D#$C;
  RegExprWordChars : RegExprString =     // default value for WordChars
    '0123456789' //###0.940
  + 'abcdefghijklmnopqrstuvwxyz'
  + 'ABCDEFGHIJKLMNOPQRSTUVWXYZ_';
  RegExprLineSeparators : RegExprString =// default value for LineSeparators
   #$d#$a{$IFDEF UniCode}+#$b#$c#$2028#$2029#$85{$ENDIF}; //###0.947
  RegExprLinePairedSeparator : RegExprString =// default value for LinePairedSeparator
   #$d#$a;
  { if You need Unix-styled line separators (only \n), then use:
  RegExprLineSeparators = #$a;
  RegExprLinePairedSeparator = '';
  }


const
 NSUBEXP = 150; // max number of subexpression //###0.929
 // Cannot be more than NSUBEXPMAX
 // Be carefull - don't use values which overflow CLOSE opcode
 // (in this case you'll get compiler erorr).
 // Big NSUBEXP will cause more slow work and more stack required
 NSUBEXPMAX = 255; // Max possible value for NSUBEXP. //###0.945
 // Don't change it! It's defined by internal TRegExpr design.

 MaxBracesArg = $7FFFFFFF - 1; // max value for {n,m} arguments //###0.933

 {$IFDEF ComplexBraces}
 LoopStackMax = 10; // max depth of loops stack //###0.925
 {$ENDIF}

 TinySetLen = 3;
 // if range includes more then TinySetLen chars, //###0.934
 // then use full (32 bytes) ANYOFFULL instead of ANYOF[BUT]TINYSET
 // !!! Attension ! If you change TinySetLen, you must
 // change code marked as "//!!!TinySet"


type

{$IFDEF UseSetOfChar}
 PSetOfREChar = ^TSetOfREChar;
 TSetOfREChar = set of REChar;
{$ENDIF}

 TRegExpr = class;

 TRegExprReplaceFunction = function (ARegExpr : TRegExpr): string
                               of object;

 { TVarValue }

 TVarStruct = class;

 TByteSet = Set Of Byte;

 TVarValue = class(TStringList)
 protected
    Num: Integer; // Number of Var
    Parent: TVarValue;
    ParentIdx: Integer;
    baseVal: RegExprString;
    Ref: TRegExpr;
 public
    Constructor Create(_Ref: TRegExpr; _Num: Integer; _Parent: TVarValue; _ParentIdx: Integer; Const bv: RegExprString = '');
    Procedure   Mark(Var M: TByteSet);
    Function    ExportPredicates(Const MacroID: String; Const R:TRegExpr; Var id: Integer; Var L: String): String;
    Function    ExportXML(Const R:TRegExpr): String;
    Function    FindNode(ID: Integer): TVarStruct;
    Procedure   Out(Const Shift: String);
    Procedure   AssignBVal(Var stp, enp: PRegExprChar);
    Destructor  Destroy; override;
 end;

 { TVarStruct }

 TVarStruct = class(TStringList)
 Public
    ID: Integer;
    _First, _Last: Integer;
    Tags: WideString;

    Constructor Create;
    Procedure   Mark(Var M: TByteSet);
    Function    ExportPredicates(Const MacroID: String; Const R:TRegExpr; Var id: Integer; Var L: String): String;
    Function    ExportXML(Const R:TRegExpr): String;
    Function    FindNode(ID: Integer): TVarStruct;
    Procedure   GrammarParse(Const VName: String; command: String; Var text: WideString; Var stp, enp: PRegExprChar);
    Procedure   Out(Const Shift: String);
 end;

 TFastPositionKind = (fpAny, fpBound, fpFree);

 TFastPosition = record
    Kind: TFastPositionKind;
    Logged: Boolean;
    Value: WideString
 end;

 TFastPositions = Array Of TFastPosition;

 TFastPredicate = class
   public
     Function ExportDB(Const Name: String): String; virtual; abstract;
     Function ExportPascalDB(Const ID: String; Var out: TStringList; Const Offs, vDB: String): Boolean; virtual; abstract;

     Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; virtual; abstract;
     Function Assert(Const Descriptor: TFastPositions): Boolean; virtual; abstract;
     Function Retract(Const Descriptor: TFastPositions): Boolean; virtual; abstract;
     Function Learn(Const Descriptor: TFastPositions): Boolean; virtual; abstract;

     Procedure StartTransaction; virtual; abstract;
     Procedure Commit; virtual; abstract;
     Procedure RollBack; virtual; abstract;
 End;

 { TFastTable }

 TFastTable = class(TFastPredicate)
   private
     FThreshold: Integer;
     FName: String;
     FExact: Boolean;

     FJournal: TStringList;
     FJournalled: Boolean;
   public
     Constructor Create(Const FName: String);
     Destructor  Destroy; override;

     Function ExportDB(Const Name: String): String; override;
     function ExportPascalDB(Const ID: String; Var out: TStringList; Const Offs, vDB: String): Boolean; override;

     Function Compare(Const S1, S2: String): Integer; virtual;

     Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
     Function Assert(Const Descriptor: TFastPositions): Boolean; override;
     Function Retract(Const Descriptor: TFastPositions): Boolean; override;
     Function Learn(Const Descriptor: TFastPositions): Boolean; override;

     Procedure StartTransaction; override;
     Procedure Commit; override;
     Procedure RollBack; override;
 End;

 { TFastNearestTable }

 TFastNearestTable = class(TFastTable)
   public
    Constructor Create(Threshold: Integer; Const FName: String);

    Function ExportDB(Const Name: String): String; override;
    function ExportPascalDB(Const ID: String; Var out: TStringList; Const Offs, vDB: String): Boolean; override;

    Function Compare(Const S1, S2: String): Integer; override;
 End;

 TExternalVals = ^PWideChar;

 TExternal = function (N: Integer; Map: PWideChar; Vals: TExternalVals): Boolean; cdecl;

 TFastDB = class;

 { TFastExternal }

 TFastExternal = class(TFastPredicate)
 private
   Caller: TExternal;
 public
  Constructor Create(proc: Pointer);

  Function ExportDB(Const Name: String): String; override;
  function ExportPascalDB(Const ID: String; Var out: TStringList; Const Offs, vDB: String): Boolean; override;

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
  Function Assert(Const Descriptor: TFastPositions): Boolean; override;
  Function Retract(Const Descriptor: TFastPositions): Boolean; override;
  Function Learn(Const Descriptor: TFastPositions): Boolean; override;

  Procedure StartTransaction; override;
  Procedure Commit; override;
  Procedure RollBack; override;
 end;

 { TFastXPath }

 TFastXPath = class(TFastExternal)
 public
  Constructor Create;

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastXPathF }

 TFastXPathF = class(TFastExternal)
 public
  Constructor Create;

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastStopFail }

 TFastStopFail = class(TFastExternal)
 public
  Constructor Create;

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastBoolConst }

 TFastBoolConst = class(TFastExternal)
   Val: Boolean;
 public
  Constructor Create(V: Boolean);

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastEqual }

 TFastEqual = class(TFastExternal)
 public
  Constructor Create(V: Boolean);

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastSimilar }

 TFastSimilar = class(TFastExternal)
 public
  Constructor Create(V: Boolean);

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastSet }

 TFastSet = class(TFastExternal)
 public
  Constructor Create(V: Boolean);

  Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
 end;

 { TFastNet }

 TFastNet = class(TFastPredicate)
 private
   FName: String;
   FDB: TFastDB;
 public
   Constructor Create(Const FName: String; FDB: TFastDB);

   Function ExportDB(Const Name: String): String; override;
   function ExportPascalDB(Const ID: String; Var out: TStringList; Const Offs, vDB: String): Boolean; override;

   Function Unify(R: TRegExpr; ENV: TXPathEnvironment; Var Descriptor: TFastPositions): Boolean; override;
   Function Assert(Const Descriptor: TFastPositions): Boolean; override;
   Function Retract(Const Descriptor: TFastPositions): Boolean; override;
   Function Learn(Const Descriptor: TFastPositions): Boolean; override;

   Procedure StartTransaction; override;
   Procedure Commit; override;
   Procedure RollBack; override;
 end;

 { TFastDB }

 TFastDB = class(TStringList)
   private
      nUses : Integer;

      libs: TStringList;
   public
      Constructor Create;
      Destructor Destroy; override;

      function ExportDB: String;
      function ExportPascalDB(Var out: TStringList; Const Offs, vDB: String): Boolean;

      Procedure Use;
      Procedure Release;

      Function GetIndexOf(Const Predicate: String): Integer;

      function Unify(R: TRegExpr; ENV: TXPathEnvironment; Const Predicate: String; Var Descriptor: TFastPositions): Boolean;
      Function Assert(Const Predicate: String; Const Descriptor: TFastPositions): Boolean;
      Function Retract(Const Predicate: String; Const Descriptor: TFastPositions): Boolean;
      Function Learn(Const Predicate: String; Const Descriptor: TFastPositions): Boolean;

      Procedure StartTransaction;
      Procedure Commit;
      Procedure RollBack;
 end;

 TFastCall = class
   Predicate: String;
   Negate: Boolean;
   Descriptor: TFastPositions;
   References: Array Of Integer; // Номера переменных из дескриптора. -1 для _ или константы
 end;

 RealArray = Array Of Real;
 IntArray = Array Of Integer;

 { TParallelizer }

 TParallelizer = class
   Stage: Integer;
   Counter: Integer;
   t1, tn: RealArray;
   a: RealArray;
   m: RealArray;
   predt1, predtn: Real;

   Constructor Create;
   Procedure Clear;
   Procedure PutT(Parallel: Boolean; T: Real);
   Function InParallel: Boolean;
 end;

 { TFastCalls }

 TFastCallsAction = function(Const Predicate: String; Const Descriptor: TFastPositions): Boolean of Object;

 TFastCalls = class(TList)
 public // Если в списке встречается TFastCalls -- вложенная цепочка
   Constructor Create;
   Destructor Destroy; override;

   procedure ClearAnalyzers;

   function Unify(ENV: TXPathEnvironment; Const DB: TFastDB; const R: TRegExpr; Var valext: TStringList; Var valsp): Boolean;
   Function Assert(Const DB: TFastDB; const R: TRegExpr; Var valext: TStringList; Var valsp): Boolean;
   Function Retract(Const DB: TFastDB; const R: TRegExpr; Var valext: TStringList; Var valsp): Boolean;
   Function Learn(Const DB: TFastDB; const R: TRegExpr; Var valext: TStringList; Var valsp): Boolean;
 private
   Analyzers: TList;
   Alternation: TFastCalls; // Альтернативная цепочка после ';'

   function ARL(const DB: TFastDB; const R: TRegExpr; var valext: TStringList;
     var valsp; Action: TFastCallsAction; makeFillIn: Boolean): Boolean;
   function FillIn(pcall: TFastCall; const R: TRegExpr; var valext: TStringList
     ): Boolean;
   function FillOut(pcall: TFastCall; const R: TRegExpr;
     var _valsp): Boolean;
 end;

 { TRegExpr }
 TRegExpr = class
   private
    startp : array [0 .. NSUBEXP - 1] of PRegExprChar; // founded expr starting points
    endp : array [0 .. NSUBEXP - 1] of PRegExprChar; // founded expr end points

    varsp : array [0 .. NSUBEXP - 1] of PRegExprChar; // Var Names
    valsp : array [0 .. NSUBEXP - 1] of TVarValue; // Var Values

    fcalls : array [0 .. NSUBEXP - 1] of TFastCalls; // Predicate Calls

    valext: TStringList;

    nExecs: Integer;

    db: TFastDB;

    ENV: TXPathEnvironment;

    storedWords: TStringList;
    storedRels: TStringList;

    trash: TList;

    RootID: Integer;

    {$IFDEF ComplexBraces}
    LoopStack : array [1 .. LoopStackMax] of integer; // state before entering loop
    LoopStackIdx : integer; // 0 - out of all loops
    {$ENDIF}

    // The "internal use only" fields to pass info from compile
    // to execute that permits the execute phase to run lots faster on
    // simple cases.
    regstart : REChar; // char that must begin a match; '\0' if none obvious
    reganch : REChar; // is the match anchored (at beginning-of-line only)?
    regmust : PRegExprChar; // string (pointer into program) that match must include, or nil
    regmlen : PtrInt; // length of regmust string
    // Regstart and reganch permit very fast decisions on suitable starting points
    // for a match, cutting down the work a lot. Regmust permits fast rejection
    // of lines that cannot possibly match. The regmust tests are costly enough
    // that regcomp() supplies a regmust only if the r.e. contains something
    // potentially expensive (at present, the only such thing detected is * or +
    // at the start of the r.e., which can involve a lot of backup). Regmlen is
    // supplied because the test in regexec() needs it and regcomp() is computing
    // it anyway.
    {$IFDEF UseFirstCharSet} //###0.929
    FirstCharSet : TSetOfREChar;
    {$ENDIF}

    // work variables for Exec's routins - save stack in recursion}
    reginput : PRegExprChar; // String-input pointer.
    fInputStart : PRegExprChar; // Pointer to first char of input string.
    fInputEnd : PRegExprChar; // Pointer to char AFTER last char of input string

    // work variables for compiler's routines
    regparse : PRegExprChar;  // Input-scan pointer.
    regnpar : PtrInt; // count.
    regdummy : char;
    regcode : PRegExprChar;   // Code-emit pointer; @regdummy = don't.
    regsize : PtrInt; // Code size.

    regexpbeg : PRegExprChar; // only for error handling. Contains
    // pointer to beginning of r.e. while compiling
    fExprIsCompiled : boolean; // true if r.e. successfully compiled

    // programm is essentially a linear encoding
    // of a nondeterministic finite-state machine (aka syntax charts or
    // "railroad normal form" in parsing technology). Each node is an opcode
    // plus a "next" pointer, possibly plus an operand. "Next" pointers of
    // all nodes except BRANCH implement concatenation; a "next" pointer with
    // a BRANCH on both ends of it connects two alternatives. (Here we
    // have one of the subtle syntax dependencies: an individual BRANCH (as
    // opposed to a collection of them) is never concatenated with anything
    // because of operator precedence.) The operand of some types of node is
    // a literal string; for others, it is a node leading into a sub-FSM. In
    // particular, the operand of a BRANCH node is the first node of the branch.
    // (NB this is *not* a tree structure: the tail of the branch connects
    // to the thing following the set of BRANCHes.) The opcodes are:
    programm : PRegExprChar; // Unwarranted chumminess with compiler.

    fExpression : PRegExprChar; // source of compiled r.e.
    fInputString : PRegExprChar; // input string

    fLastError : integer; // see Error, LastError

    fModifiers : integer; // modifiers
    fCompModifiers : integer; // compiler's copy of modifiers
    fProgModifiers : integer; // modifiers values from last programm compilation

    fSpaceChars : RegExprString; //###0.927
    fWordChars : RegExprString; //###0.929
    fInvertCase : TRegExprInvertCaseFunction; //###0.927

    fLineSeparators : RegExprString; //###0.941
    fLinePairedSeparatorAssigned : boolean;
    fLinePairedSeparatorHead,
    fLinePairedSeparatorTail : REChar;
    {$IFNDEF UniCode}
    fLineSeparatorsSet : set of REChar;
    {$ENDIF}

    Trasher: TRTLCriticalSection;

    procedure AddTrash(p: TObject);

    function GetVarName(Idx : integer): PRegExprChar;
    function GetVarValue(Idx : integer): TVarValue;

    // Mark programm as having to be [re]compiled
    procedure InvalidateProgramm;

    // Check if we can use precompiled r.e. or
    // [re]compile it if something changed
    function IsProgrammOk : boolean; //###0.941

    function GetExpression : RegExprString;
    procedure SetExpression (const s : RegExprString);

    function GetModifierStr : RegExprString;
    // Parse AModifiers string and return true and set AModifiersInt
    // if it's in format 'ismxrg-ismxrg'.
    class function ParseModifiersStr (const AModifiers : RegExprString;
      var AModifiersInt : integer) : boolean; //###0.941 class function now
    procedure SetModifierStr (const AModifiers : RegExprString);

    function GetModifier (AIndex : integer) : boolean;
    procedure SetModifier (AIndex : integer; ASet : boolean);

    // Default handler raises exception ERegExpr with
    // Message = ErrorMsg (AErrorID), ErrorCode = AErrorID
    // and CompilerErrorPos = value of property CompilerErrorPos.
    procedure Error (AErrorID : integer); virtual; // error handler.


    {==================== Compiler section ===================}
    // compile a regular expression into internal code
    function CompileRegExpr (exp : PRegExprChar) : boolean;

    // set the next-pointer at the end of a node chain
    procedure Tail (p : PRegExprChar; val : PRegExprChar);

    // regoptail - regtail on operand of first argument; nop if operandless
    procedure OpTail (p : PRegExprChar; val : PRegExprChar);

    // regnode - emit a node, return location
    function EmitNode (op : TREOp) : PRegExprChar;

    // emit (if appropriate) a byte of code
    procedure EmitC (b : REChar);

    // insert an operator in front of already-emitted operand
    // Means relocating the operand.
    procedure InsertOperator (op : TREOp; opnd : PRegExprChar; sz : integer); //###0.90

    // regular expression, i.e. main body or parenthesized thing
    function ParseReg (paren : integer; var flagp : integer) : PRegExprChar;

    // one alternative of an | operator
    function ParseBranch (var flagp : integer) : PRegExprChar;

    // something followed by possible [*+?]
    function ParsePiece (var flagp : integer) : PRegExprChar;

    // the lowest level
    function ParseAtom (var flagp : integer) : PRegExprChar;

    // current pos in r.e. - for error hanling
    function GetCompilerErrorPos : PtrInt;

    {$IFDEF UseFirstCharSet} //###0.929
    procedure FillFirstCharSet (prog : PRegExprChar);
    {$ENDIF}

    {===================== Matching section ===================}
    // repeatedly match something simple, report how many
    function regrepeat (p : PRegExprChar; AMax : PtrInt) : PtrInt;

    // dig the "next" pointer out of a node
    function regnext (p : PRegExprChar) : PRegExprChar;

    // recursively matching routine
    function MatchPrim (context: TVarValue; contextNum: Integer; prog : PRegExprChar; Var Pruning: Boolean) : boolean;

    // Exec for stored InputString
    function ExecPrim (AOffset: PtrInt; Const Anchored: Boolean = False) : boolean;

    {$IFDEF RegExpPCodeDump}
    function DumpOp (op : REChar) : RegExprString;
    {$ENDIF}

    function GetSubExprMatchCount : integer;
    function GetMatchPos (Idx : integer) : PtrInt;
    function GetMatchLen (Idx : integer) : PtrInt;
    function GetMatch (Idx : integer) : RegExprString;

    function GetInputString : RegExprString;
    procedure SetInputString (const AInputString : RegExprString);

    {$IFNDEF UseSetOfChar}
    function StrScanCI (s : PRegExprChar; ch : REChar) : PRegExprChar; //###0.928
    {$ENDIF}

    procedure SetLineSeparators (const AStr : RegExprString);
    procedure SetLinePairedSeparator (const AStr : RegExprString);
    function GetLinePairedSeparator : RegExprString;

   public
    constructor Create; overload;
    constructor Create(AExpression: RegExprString); overload;
    destructor Destroy; override;

    class function VersionMajor : integer; //###0.944
    class function VersionMinor : integer; //###0.944

    // Regular expression.
    // For optimization, TRegExpr will automatically compiles it into 'P-code'
    // (You can see it with help of Dump method) and stores in internal
    // structures. Real [re]compilation occures only when it really needed -
    // while calling Exec[Next], Substitute, Dump, etc
    // and only if Expression or other P-code affected properties was changed
    // after last [re]compilation.
    // If any errors while [re]compilation occures, Error method is called
    // (by default Error raises exception - see below)
    property Expression : RegExprString read GetExpression write SetExpression;

    // Set/get default values of r.e.syntax modifiers. Modifiers in
    // r.e. (?ismx-ismx) will replace this default values.
    // If you try to set unsupported modifier, Error will be called
    // (by defaul Error raises exception ERegExpr).
    property ModifierStr : RegExprString read GetModifierStr write SetModifierStr;

    // Modifier /i - caseinsensitive, initialized from RegExprModifierI
    property ModifierI : boolean index 1 read GetModifier write SetModifier;

    // Modifier /r - use r.e.syntax extended for russian,
    // (was property ExtSyntaxEnabled in previous versions)
    // If true, then а-я  additional include russian letter 'ё',
    // А-Я  additional include 'Ё', and а-Я include all russian symbols.
    // You have to turn it off if it can interfere with you national alphabet.
    // , initialized from RegExprModifierR
    property ModifierR : boolean index 2 read GetModifier write SetModifier;

    // Modifier /s - '.' works as any char (else as [^\n]),
    // , initialized from RegExprModifierS
    property ModifierS : boolean index 3 read GetModifier write SetModifier;

    // Switching off modifier /g switchs all operators in
    // non-greedy style, so if ModifierG = False, then
    // all '*' works as '*?', all '+' as '+?' and so on.
    // , initialized from RegExprModifierG
    property ModifierG : boolean index 4 read GetModifier write SetModifier;

    // Treat string as multiple lines. That is, change `^' and `$' from
    // matching at only the very start or end of the string to the start
    // or end of any line anywhere within the string.
    // , initialized from RegExprModifierM
    property ModifierM : boolean index 5 read GetModifier write SetModifier;

    // Modifier /x - eXtended syntax, allow r.e. text formatting,
    // see description in the help. Initialized from RegExprModifierX
    property ModifierX : boolean index 6 read GetModifier write SetModifier;

    property Execs : Integer read nExecs write nExecs;

    // match a programm against a string AInputString
    // !!! Exec store AInputString into InputString property
    // For Delphi 5 and higher available overloaded versions - first without
    // parameter (uses already assigned to InputString property value)
    // and second that has PtrInt parameter and is same as ExecPos
    function Exec (const AInputString : RegExprString) : boolean; {$IFDEF OverMeth} overload;
    {$IFNDEF FPC} // I do not know why FreePascal cannot overload methods with empty param list
    function Exec : boolean; overload; //###0.949
    {$ENDIF}
    function Exec (AOffset: PtrInt; Const Anchored: Boolean = False) : boolean; overload; //###0.949
    {$ENDIF}

    procedure RewindAndClear;

    function FindNode(ID: Integer): TVarStruct;

    procedure SetDB(base: TFastDB);

    procedure SetENV(_ENV: TXPathEnvironment);

    procedure StartTransaction;
    procedure Commit;
    procedure RollBack;

    // find next match:
    //    ExecNext;
    // works the same as
    //    if MatchLen [0] = 0 then ExecPos (MatchPos [0] + 1)
    //     else ExecPos (MatchPos [0] + MatchLen [0]);
    // but it's more simpler !
    // Raises exception if used without preceeding SUCCESSFUL call to
    // Exec* (Exec, ExecPos, ExecNext). So You always must use something like
    // if Exec (InputString) then repeat { proceed results} until not ExecNext;
    function ExecNext(Const Anchored: Boolean = False): boolean;

    // find match for InputString starting from AOffset position
    // (AOffset=1 - first char of InputString)
    function ExecPos (AOffset: PtrInt {$IFDEF DefParam}= 1{$ENDIF}) : boolean;

    // returns current input string (from last Exec call or last assign
    // to this property).
    // Any assignment to this property clear Match* properties !
    property InputString : RegExprString read GetInputString write SetInputString;

    // Returns ATemplate with '$&' or '$0' replaced by whole r.e.
    // occurence and '$n' replaced by occurence of subexpression #n.
    // Since v.0.929 '$' used instead of '\' (for future extensions
    // and for more Perl-compatibility) and accept more then one digit.
    // If you want place into template raw '$' or '\', use prefix '\'
    // Example: '1\$ is $2\\rub\\' -> '1$ is <Match[2]>\rub\'
    // If you want to place raw digit after '$n' you must delimit
    // n with curly braces '{}'.
    // Example: 'a$12bc' -> 'a<Match[12]>bc'
    // 'a${1}2bc' -> 'a<Match[1]>2bc'.
    function Substitute (const ATemplate : RegExprString) : RegExprString;

    // Split AInputStr into APieces by r.e. occurencies
    // Internally calls Exec[Next]
    procedure Split (AInputStr : RegExprString; APieces : TStrings);

    function Replace (AInputStr : RegExprString;
      const AReplaceStr : RegExprString;
      AUseSubstitution : boolean{$IFDEF DefParam}= False{$ENDIF}) //###0.946
     : RegExprString; {$IFDEF OverMeth} overload;
    function Replace (AInputStr : RegExprString;
      AReplaceFunc : TRegExprReplaceFunction)
     : RegExprString; overload;
    {$ENDIF}
    // Returns AInputStr with r.e. occurencies replaced by AReplaceStr
    // If AUseSubstitution is true, then AReplaceStr will be used
    // as template for Substitution methods.
    // For example:
    //  Expression := '({-i}block|var)\s*\(\s*([^ ]*)\s*\)\s*';
    //  Replace ('BLOCK( test1)', 'def "$1" value "$2"', True);
    //   will return:  def 'BLOCK' value 'test1'
    //  Replace ('BLOCK( test1)', 'def "$1" value "$2"')
    //   will return:  def "$1" value "$2"
    // Internally calls Exec[Next]
    // Overloaded version and ReplaceEx operate with call-back function,
    // so you can implement really complex functionality.
    function ReplaceEx (AInputStr : RegExprString;
      AReplaceFunc : TRegExprReplaceFunction):
      RegExprString;

    // Number of subexpressions has been found in last Exec* call.
    // If there are no subexpr. but whole expr was found (Exec* returned True),
    // then SubExprMatchCount=0, if no subexpressions nor whole
    // r.e. found (Exec* returned false) then SubExprMatchCount=-1.
    // Note, that some subexpr. may be not found and for such
    // subexpr. MathPos=MatchLen=-1 and Match=''.
    // For example: Expression := '(1)?2(3)?';
    //  Exec ('123'): SubExprMatchCount=2, Match[0]='123', [1]='1', [2]='3'
    //  Exec ('12'): SubExprMatchCount=1, Match[0]='12', [1]='1'
    //  Exec ('23'): SubExprMatchCount=2, Match[0]='23', [1]='', [2]='3'
    //  Exec ('2'): SubExprMatchCount=0, Match[0]='2'
    //  Exec ('7') - return False: SubExprMatchCount=-1
    property SubExprMatchCount : integer read GetSubExprMatchCount;

    // pos of entrance subexpr. #Idx into tested in last Exec*
    // string. First subexpr. has Idx=1, last - MatchCount,
    // whole r.e. has Idx=0.
    // Returns -1 if in r.e. no such subexpr. or this subexpr.
    // not found in input string.
    property MatchPos [Idx : integer] : PtrInt read GetMatchPos;

    property VarNames [Idx : integer] : PRegExprChar read GetVarName; // Var Names
    property VarValues [Idx : integer] : TVarValue read GetVarValue; // Var Names

    function ExportPredicates(Const MacroID: String): String;
    function ExportXML: String;
    function ExportDB: String;
    Function ExportPascalDB(Var out: TStringList; Const Offs, vDB: String): Boolean;

    procedure AddExtRegExpr(Const Name: String; Const R: TRegExpr);

    // len of entrance subexpr. #Idx r.e. into tested in last Exec*
    // string. First subexpr. has Idx=1, last - MatchCount,
    // whole r.e. has Idx=0.
    // Returns -1 if in r.e. no such subexpr. or this subexpr.
    // not found in input string.
    // Remember - MatchLen may be 0 (if r.e. match empty string) !
    property MatchLen [Idx : integer] : PtrInt read GetMatchLen;

    // == copy (InputString, MatchPos [Idx], MatchLen [Idx])
    // Returns '' if in r.e. no such subexpr. or this subexpr.
    // not found in input string.
    property Match [Idx : integer] : RegExprString read GetMatch;

    // Returns ID of last error, 0 if no errors (unusable if
    // Error method raises exception) and clear internal status
    // into 0 (no errors).
    function LastError : integer;

    // Returns Error message for error with ID = AErrorID.
    function ErrorMsg (AErrorID : integer) : RegExprString; virtual;

    // Returns position in r.e. where compiler stopped.
    // Useful for error diagnostics
    property CompilerErrorPos : PtrInt read GetCompilerErrorPos;

    // Contains chars, treated as /s (initially filled with RegExprSpaceChars
    // global constant)
    property SpaceChars : RegExprString read fSpaceChars write fSpaceChars; //###0.927

    // Contains chars, treated as /w (initially filled with RegExprWordChars
    // global constant)
    property WordChars : RegExprString read fWordChars write fWordChars; //###0.929

    // line separators (like \n in Unix)
    property LineSeparators : RegExprString read fLineSeparators write SetLineSeparators; //###0.941

    // paired line separator (like \r\n in DOS and Windows).
    // must contain exactly two chars or no chars at all
    property LinePairedSeparator : RegExprString read GetLinePairedSeparator write SetLinePairedSeparator; //###0.941

    // Converts Ch into upper case if it in lower case or in lower
    // if it in upper (uses current system local setings)
    class function InvertCaseFunction  (const Ch : REChar) : REChar;

    // Set this property if you want to override case-insensitive functionality.
    // Create set it to RegExprInvertCaseFunction (InvertCaseFunction by default)
    property InvertCase : TRegExprInvertCaseFunction read fInvertCase write fInvertCase; //##0.935

    // [Re]compile r.e. Useful for example for GUI r.e. editors (to check
    // all properties validity).
    procedure Compile; //###0.941

    {$IFDEF RegExpPCodeDump}
    // dump a compiled regexp in vaguely comprehensible form
    function Dump : RegExprString;
    {$ENDIF}
  end;

 ERegExpr = class (Exception)
   public
    ErrorCode : integer;
    CompilerErrorPos : PtrInt;
  end;

const
  // default for InvertCase property:
  RegExprInvertCaseFunction : TRegExprInvertCaseFunction = {$IFDEF FPC} nil {$ELSE} TRegExpr.InvertCaseFunction{$ENDIF};

function EscapeString(Const S: String): String;
function UnescapeString(Const S: String): String;
function EscapeText(Const S: String): String;

function pEscapeString(Const S: String): String;

function EscapeProlog(Const S: String): String;

function Levenshtein(Const string1, string2: String): Integer;

// true if string AInputString match regular expression ARegExpr
// ! will raise exeption if syntax errors in ARegExpr
function ExecRegExpr (const ARegExpr, AInputStr : RegExprString; env: TXPathEnvironment) : boolean;

// Split AInputStr into APieces by r.e. ARegExpr occurencies
procedure SplitRegExpr (const ARegExpr, AInputStr : RegExprString; APieces : TStrings; env: TXPathEnvironment);

// Returns AInputStr with r.e. occurencies replaced by AReplaceStr
// If AUseSubstitution is true, then AReplaceStr will be used
// as template for Substitution methods.
// For example:
//  ReplaceRegExpr ('({-i}block|var)\s*\(\s*([^ ]*)\s*\)\s*',
//   'BLOCK( test1)', 'def "$1" value "$2"', True)
//  will return:  def 'BLOCK' value 'test1'
//  ReplaceRegExpr ('({-i}block|var)\s*\(\s*([^ ]*)\s*\)\s*',
//   'BLOCK( test1)', 'def "$1" value "$2"')
//   will return:  def "$1" value "$2"
function ReplaceRegExpr (const ARegExpr, AInputStr, AReplaceStr : RegExprString;
      AUseSubstitution : boolean{$IFDEF DefParam}= False{$ENDIF}) : RegExprString; //###0.947

// Replace all metachars with its safe representation,
// for example 'abc$cd.(' converts into 'abc\$cd\.\('
// This function useful for r.e. autogeneration from
// user input
function QuoteRegExprMetaChars (const AStr : RegExprString) : RegExprString;
// Makes list of subexpressions found in ARegExpr r.e.
// In ASubExps every item represent subexpression,
// from first to last, in format:
//  String - subexpression text (without '()')
//  low word of Object - starting position in ARegExpr, including '('
//   if exists! (first position is 1)
//  high word of Object - length, including starting '(' and ending ')'
//   if exist!
// AExtendedSyntax - must be True if modifier /m will be On while
// using the r.e.
// Useful for GUI editors of r.e. etc (You can find example of using
// in TestRExp.dpr project)
// Returns
//  0      Success. No unbalanced brackets was found;
//  -1     There are not enough closing brackets ')';
//  -(n+1) At position n was found opening '[' without  //###0.942
//         corresponding closing ']';
//  n      At position n was found closing bracket ')' without
//         corresponding opening '('.
// If Result <> 0, then ASubExpr can contain empty items or illegal ones
function RegExprSubExpressions (const ARegExpr : string;
 ASubExprs : TStrings; AExtendedSyntax : boolean{$IFDEF DefParam}= False{$ENDIF}) : PtrInt;

procedure set_default_transformer(Const trans: String);
function get_default_transformer: String;

Var Transformers: TStringList;
Var GDefTrans: String = 'Grammar.ru';

implementation

{$IFDEF FPC}
uses
{$IFDEF UNIX}
 cthreads, cmem,
{$ENDIF}
 dom, xmlread,
{$IF DEFINED(VCL) OR DEFINED(LCL)}
 Dialogs,
{$ENDIF}
 MTProcs;
{$ELSE}
uses
 XPath, dom, xmlread,
{$IF DEFINED(VCL) OR DEFINED(LCL)}
 Dialogs,
{$ENDIF}
{$IFDEF SYN_WIN32}
 Windows; // CharUpper/Lower
{$ELSE}
  Libc; //Qt.pas from Borland does not expose char handling functions
{$ENDIF}
{$ENDIF}

procedure set_default_transformer(Const trans: String);
begin
  GDefTrans := trans
end;

function get_default_transformer: String;
begin
  Result := GDefTrans
end;

const
 // TRegExpr.VersionMajor/Minor return values of these constants:
 TRegExprVersionMajor : integer = 0;
 TRegExprVersionMinor : integer = 952;

 MaskModI = 1;  // modifier /i bit in fModifiers
 MaskModR = 2;  // -"- /r
 MaskModS = 4;  // -"- /s
 MaskModG = 8;  // -"- /g
 MaskModM = 16; // -"- /m
 MaskModX = 32; // -"- /x

 {$IFDEF UniCode}
 XIgnoredChars = ' '#9#$d#$a;
 {$ELSE}
 XIgnoredChars = [' ', #9, #$d, #$a];
 {$ENDIF}

 function AlignToPtr(const p: Pointer): Pointer;
 begin
 {$IFDEF FPC_REQUIRES_PROPER_ALIGNMENT}
   Result := Align(p, SizeOf(Pointer));
 {$ELSE}
   Result := p;
 {$ENDIF}
 end;

 function AlignToInt(const p: Pointer): Pointer;
 begin
 {$IFDEF FPC_REQUIRES_PROPER_ALIGNMENT}
   Result := Align(p, SizeOf(integer));
 {$ELSE}
   Result := p;
 {$ENDIF}
 end;

{=============================================================}
{=================== WideString functions ====================}
{=============================================================}

{$IFDEF UniCode}

function StrPCopy (Dest: PRegExprChar; const Source: RegExprString): PRegExprChar;
 var
  i, Len : PtrInt;
 begin
  Len := length (Source); //###0.932
  for i := 1 to Len do
   Dest [i - 1] := Source [i];
  Dest [Len] := #0;
  Result := Dest;
 end; { of function StrPCopy
--------------------------------------------------------------}

function StrLCopy (Dest, Source: PRegExprChar; MaxLen: PtrUInt): PRegExprChar;
 var i: PtrInt;
 begin
  for i := 0 to MaxLen - 1 do
   Dest [i] := Source [i];
  Result := Dest;
 end; { of function StrLCopy
--------------------------------------------------------------}

function StrLen (Str: PRegExprChar): PtrUInt;
 begin
  Result:=0;
  while Str [result] <> #0
   do Inc (Result);
 end; { of function StrLen
--------------------------------------------------------------}

function StrPos (Str1, Str2: PRegExprChar): PRegExprChar;
 var n: PtrInt;
 begin
  Result := nil;
  n := Pos (RegExprString (Str2), RegExprString (Str1));
  if n = 0
   then EXIT;
  Result := Str1 + n - 1;
 end; { of function StrPos
--------------------------------------------------------------}

function StrLComp (Str1, Str2: PRegExprChar; MaxLen: PtrUInt): PtrInt;
 var S1, S2: RegExprString;
 begin
  S1 := Str1;
  S2 := Str2;
  if Copy (S1, 1, MaxLen) > Copy (S2, 1, MaxLen)
   then Result := 1
   else
    if Copy (S1, 1, MaxLen) < Copy (S2, 1, MaxLen)
     then Result := -1
     else Result := 0;
 end; { function StrLComp
--------------------------------------------------------------}

function StrScan (Str: PRegExprChar; Chr: WideChar): PRegExprChar;
 begin
  Result := nil;
  while (Str^ <> #0) and (Str^ <> Chr)
   do Inc (Str);
  if (Str^ <> #0)
   then Result := Str;
 end; { of function StrScan
--------------------------------------------------------------}

{$ENDIF}


{=============================================================}
{===================== Global functions ======================}
{=============================================================}

Const Specials: Array[1..5] Of String = ('\', #$0D#$0A, #$0D, #$0A, #09);
Const Escaped:  Array[1..5] Of String = ('\\', '\n', '\r', '\r', '\t');

function EscapeString(const S: String): String;

var i: Integer;
begin
   Result := S;
   For i := Low(Specials) To High(Specials) Do
       Result := StringReplace(Result, Specials[i], Escaped[i], [rfReplaceAll])
end;

function UnescapeString(const S: String): String;

var i: Integer;
begin
   Result := StringReplace(S, Escaped[Low(Escaped)], #0, [rfReplaceAll]);
   For i := Low(Specials) + 1 To High(Specials) Do
       Result := StringReplace(Result, Escaped[i], Specials[i], [rfReplaceAll]);
   Result := StringReplace(Result, #0, '\', [rfReplaceAll])
end;

function EscapeText(const S: String): String;

Const NumMetaChars = 5;
      MetaChars: Array[1..NumMetaChars] Of Char = '&<>''"';
      MetaSubsts: Array[1..NumMetaChars] Of PChar = ('amp','lt','gt','apos','quot');

Var F:Integer;
begin
     Result:=S;
     For F:=Low(MetaChars) To High(MetaChars) Do
         Result:=StringReplace(Result,MetaChars[F],'&'+MetaSubsts[F]+';',[rfReplaceAll]);
end;

Const pSpecials: Array[1..4] Of String = ('''', #$0D#$0A, #$0D, #$0A);
Const pEscaped:  Array[1..4] Of String = ('''''', '''+#$0D#$0A+''', '''+#$0D+''', '''+#$0A+''');

function pEscapeString(const S: String): String;

var i: Integer;
begin
   Result := S;
   For i := Low(pSpecials) To High(pSpecials) Do
       Result := StringReplace(Result, pSpecials[i], pEscaped[i], [rfReplaceAll])
end;

Function EscapeProlog(Const S: String): String;
Begin
   Result := StringReplace(S, '\', '\\', [rfReplaceAll])
End;

function Levenshtein(const string1, string2: String): Integer;

Var diff: integer;
    m: Array Of Array Of Integer;
    i, j: Integer;
Begin
 SetLength(m, Length(string1) + 1, Length(string2) + 1);

 for i := 0 To Length(string1) do
     m[i][0] := i;
 for j := 0 To Length(string2) do
     m[0][j] := j;

 for i := 1 to Length(string1) do
   begin
     for j := 1 to Length(string2) do
       begin
         if string1[i] = string2[j] then diff := 0 else diff := 1;

         m[i][j] := Min(Min(m[i - 1, j] + 1,
                                  m[i, j - 1] + 1),
                                  m[i - 1, j - 1] + diff);
       end
   end;
   Result := m[Length(string1)][Length(string2)]
end;

function ExecRegExpr (const ARegExpr, AInputStr : RegExprString; env: TXPathEnvironment) : boolean;
 var r : TRegExpr;
 begin
  r := TRegExpr.Create;
  try
    r.setENV(env);
    r.Expression := ARegExpr;
    Result := r.Exec (AInputStr);
    finally r.Free;
   end;
 end; { of function ExecRegExpr
--------------------------------------------------------------}

procedure SplitRegExpr (const ARegExpr, AInputStr : RegExprString; APieces : TStrings; env: TXPathEnvironment);
 var r : TRegExpr;
 begin
  APieces.Clear;
  r := TRegExpr.Create;
  try
    r.setENV(env);
    r.Expression := ARegExpr;
    r.Split (AInputStr, APieces);
    finally r.Free;
   end;
 end; { of procedure SplitRegExpr
--------------------------------------------------------------}

function ReplaceRegExpr (const ARegExpr, AInputStr, AReplaceStr : RegExprString;
      AUseSubstitution : boolean{$IFDEF DefParam}= False{$ENDIF}) : RegExprString;
 begin
  with TRegExpr.Create do try
    Expression := ARegExpr;
    Result := Replace (AInputStr, AReplaceStr, AUseSubstitution);
    finally Free;
   end;
 end; { of function ReplaceRegExpr
--------------------------------------------------------------}

function QuoteRegExprMetaChars (const AStr : RegExprString) : RegExprString;
 const
  RegExprMetaSet : RegExprString = '^$.[()|?+*'+EscChar+'{'
  + ']}'; // - this last are additional to META.
  // Very similar to META array, but slighly changed.
  // !Any changes in META array must be synchronized with this set.
 var
  i, i0, Len : PtrInt;
 begin
  Result := '';
  Len := length (AStr);
  i := 1;
  i0 := i;
  while i <= Len do begin
    if Pos (AStr [i], RegExprMetaSet) > 0 then begin
      Result := Result + System.Copy (AStr, i0, i - i0)
                 + EscChar + AStr [i];
      i0 := i + 1;
     end;
    inc (i);
   end;
  Result := Result + System.Copy (AStr, i0, MaxInt); // Tail
 end; { of function QuoteRegExprMetaChars
--------------------------------------------------------------}

function RegExprSubExpressions (const ARegExpr : string;
 ASubExprs : TStrings; AExtendedSyntax : boolean{$IFDEF DefParam}= False{$ENDIF}) : PtrInt;
 type
  TStackItemRec =  record //###0.945
    SubExprIdx : integer;
    StartPos : PtrInt;
   end;
  TStackArray = packed array [0 .. NSUBEXPMAX - 1] of TStackItemRec;
 var
  Len, SubExprLen : PtrInt;
  i, i0 : PtrInt;
  Modif : integer;
  bal: Integer;
  Stack : ^TStackArray; //###0.945
  StackIdx, StackSz : PtrInt;
 begin
  Result := 0; // no unbalanced brackets found at this very moment

  ASubExprs.Clear; // I don't think that adding to non empty list
  // can be useful, so I simplified algorithm to work only with empty list

  Len := length (ARegExpr); // some optimization tricks

  // first we have to calculate number of subexpression to reserve
  // space in Stack array (may be we'll reserve more than needed, but
  // it's faster then memory reallocation during parsing)
  StackSz := 1; // add 1 for entire r.e.
  for i := 1 to Len do
   if ARegExpr [i] = '('
    then inc (StackSz);
//  SetLength (Stack, StackSz); //###0.945
  GetMem (Stack, SizeOf (TStackItemRec) * StackSz);
  try

  StackIdx := 0;
  i := 1;
  while (i <= Len) do begin
    case ARegExpr [i] of
      '(': begin
        if (i < Len) and (ARegExpr [i + 1] = '?') then begin
           // this is not subexpression, but comment or other
           // Perl extension. We must check is it (?ismxrg-ismxrg)
           // and change AExtendedSyntax if /x is changed.
           inc (i, 2); // skip '(?'
           i0 := i;
           while (i <= Len) and (ARegExpr [i] <> ')')
            do inc (i);
           if i > Len
            then Result := -1 // unbalansed '('
            else
             if TRegExpr.ParseModifiersStr (System.Copy (ARegExpr, i, i - i0), Modif)
              then AExtendedSyntax := (Modif and MaskModX) <> 0;
          end
         else begin // subexpression starts
           ASubExprs.Add (''); // just reserve space
           with Stack [StackIdx] do begin
             SubExprIdx := ASubExprs.Count - 1;
             StartPos := i;
            end;
           inc (StackIdx);
          end;
       end;
      ')': begin
        if StackIdx = 0
         then Result := i // unbalanced ')'
         else begin
           dec (StackIdx);
           with Stack [StackIdx] do begin
             SubExprLen := i - StartPos + 1;
             ASubExprs.Objects [SubExprIdx] :=
              TObject (StartPos or (SubExprLen ShL 16));
             ASubExprs [SubExprIdx] := System.Copy (
              ARegExpr, StartPos + 1, SubExprLen - 2); // add without brackets
            end;
           if (i + 4 <= Len) And (ARegExpr[i+1] = '-') And (ARegExpr[i+2] = '>') And (ARegExpr[i+3] = '{')  then
              begin
                Inc(i, 4);
                bal := 1;
                While (i <= Len) And (bal <> 0) Do
                  If ARegExpr[i] = '{' Then
                     Begin
                       Inc(bal);
                       Inc(i)
                     End
                  Else If ARegExpr[i] = '}' Then
                     Begin
                       Dec(bal);
                       If bal <> 0 Then
                          Inc(i)
                     End
                  Else
                     Inc(i)
              end
          end;
       end;
      EscChar: inc (i); // skip quoted symbol
      '[': begin
        // we have to skip character ranges at once, because they can
        // contain '#', and '#' in it must NOT be recognized as eXtended
        // comment beginning!
        i0 := i;
        inc (i);
        if ARegExpr [i] = ']' // cannot be 'emty' ranges - this interpretes
         then inc (i);        // as ']' by itself
        while (i <= Len) and (ARegExpr [i] <> ']') do
         if ARegExpr [i] = EscChar //###0.942
          then inc (i, 2) // skip 'escaped' char to prevent stopping at '\]'
          else inc (i);
        if (i > Len) or (ARegExpr [i] <> ']') //###0.942
         then Result := - (i0 + 1); // unbalansed '[' //###0.942
       end;
      '#': if AExtendedSyntax then begin
        // skip eXtended comments
        while (i <= Len) and (ARegExpr [i] <> #$d) and (ARegExpr [i] <> #$a)
         // do not use [#$d, #$a] due to UniCode compatibility
         do inc (i);
        while (i + 1 <= Len) and ((ARegExpr [i + 1] = #$d) or (ARegExpr [i + 1] = #$a))
         do inc (i); // attempt to work with different kinds of line separators
        // now we are at the line separator that must be skipped.
       end;
      // here is no 'else' clause - we simply skip ordinary chars
     end; // of case
    inc (i); // skip scanned char
    // ! can move after Len due to skipping quoted symbol
   end;

  // check brackets balance
  if StackIdx <> 0
   then Result := -1; // unbalansed '('

  // check if entire r.e. added
  if (ASubExprs.Count = 0)
   or ((PtrInt (ASubExprs.Objects [0]) and $FFFF) <> 1)
   or (((PtrInt (ASubExprs.Objects [0]) ShR 16) and $FFFF) <> Len)
    // whole r.e. wasn't added because it isn't bracketed
    // well, we add it now:
    then ASubExprs.InsertObject (0, ARegExpr, TObject ((Len ShL 16) or 1));

  finally FreeMem (Stack);
  end;
 end; { of function RegExprSubExpressions
--------------------------------------------------------------}



const
 MAGIC       = TREOp (216);// programm signature

// name            opcode    opnd? meaning
 EEND        = TREOp (0);  // -    End of program
 BOL         = TREOp (1);  // -    Match "" at beginning of line
 EOL         = TREOp (2);  // -    Match "" at end of line
 ANY         = TREOp (3);  // -    Match any one character
 ANYOF       = TREOp (4);  // Str  Match any character in string Str
 ANYBUT      = TREOp (5);  // Str  Match any char. not in string Str
 BRANCH      = TREOp (6);  // Node Match this alternative, or the next
 BACK        = TREOp (7);  // -    Jump backward (Next < 0)
 EXACTLY     = TREOp (8);  // Str  Match string Str
 NOTHING     = TREOp (9);  // -    Match empty string
 STAR        = TREOp (10); // Node Match this (simple) thing 0 or more times
 PLUS        = TREOp (11); // Node Match this (simple) thing 1 or more times
 ANYDIGIT    = TREOp (12); // -    Match any digit (equiv [0-9])
 NOTDIGIT    = TREOp (13); // -    Match not digit (equiv [0-9])
 ANYLETTER   = TREOp (14); // -    Match any letter from property WordChars
 NOTLETTER   = TREOp (15); // -    Match not letter from property WordChars
 ANYSPACE    = TREOp (16); // -    Match any space char (see property SpaceChars)
 NOTSPACE    = TREOp (17); // -    Match not space char (see property SpaceChars)
 BRACES      = TREOp (18); // Node,Min,Max Match this (simple) thing from Min to Max times.
                           //      Min and Max are TREBracesArg
 COMMENT     = TREOp (19); // -    Comment ;)
 EXACTLYCI   = TREOp (20); // Str  Match string Str case insensitive
 ANYOFCI     = TREOp (21); // Str  Match any character in string Str, case insensitive
 ANYBUTCI    = TREOp (22); // Str  Match any char. not in string Str, case insensitive
 LOOPENTRY   = TREOp (23); // Node Start of loop (Node - LOOP for this loop)
 LOOP        = TREOp (24); // Node,Min,Max,LoopEntryJmp - back jump for LOOPENTRY.
                           //      Min and Max are TREBracesArg
                           //      Node - next node in sequence,
                           //      LoopEntryJmp - associated LOOPENTRY node addr
 ANYOFTINYSET= TREOp (25); // Chrs Match any one char from Chrs (exactly TinySetLen chars)
 ANYBUTTINYSET=TREOp (26); // Chrs Match any one char not in Chrs (exactly TinySetLen chars)
 ANYOFFULLSET= TREOp (27); // Set  Match any one char from set of char
                           // - very fast (one CPU instruction !) but takes 32 bytes of p-code
 BSUBEXP     = TREOp (28); // Idx  Match previously matched subexpression #Idx (stored as REChar) //###0.936
 BSUBEXPCI   = TREOp (29); // Idx  -"- in case-insensitive mode

 // Non-Greedy Style Ops //###0.940
 STARNG      = TREOp (30); // Same as START but in non-greedy mode
 PLUSNG      = TREOp (31); // Same as PLUS but in non-greedy mode
 BRACESNG    = TREOp (32); // Same as BRACES but in non-greedy mode
 LOOPNG      = TREOp (33); // Same as LOOP but in non-greedy mode

 // Multiline mode \m
 BOLML       = TREOp (34);  // -    Match "" at beginning of line
 EOLML       = TREOp (35);  // -    Match "" at end of line
 ANYML       = TREOp (36);  // -    Match any one character

 // Word boundary
 BOUND       = TREOp (37);  // Match "" between words //###0.943
 NOTBOUND    = TREOp (38);  // Match "" not between words //###0.943

 PRUNE       = TREOp (39);  // (*PRUNE)
 FAIL        = TREOp (40);  // (*FAIL)
 STOP        = TREOp (41);  // (*STOP)

 // !!! Change OPEN value if you add new opcodes !!!

 OPEN        = TREOp (42); // -    Mark this point in input as start of \n
                           //      OPEN + 1 is \1, etc.
 CLOSE       = TREOp (ord (OPEN) + NSUBEXP);
                           // -    Analogous to OPEN.

 // !!! Don't add new OpCodes after CLOSE !!!

// We work with p-code through pointers, compatible with PRegExprChar.
// Note: all code components (TRENextOff, TREOp, TREBracesArg, etc)
// must have lengths that can be divided by SizeOf (REChar) !
// A node is TREOp of opcode followed Next "pointer" of TRENextOff type.
// The Next is a offset from the opcode of the node containing it.
// An operand, if any, simply follows the node. (Note that much of
// the code generation knows about this implicit relationship!)
// Using TRENextOff=PtrInt speed up p-code processing.

// Opcodes description:
//
// BRANCH The set of branches constituting a single choice are hooked
//      together with their "next" pointers, since precedence prevents
//      anything being concatenated to any individual branch. The
//      "next" pointer of the last BRANCH in a choice points to the
//      thing following the whole choice. This is also where the
//      final "next" pointer of each individual branch points; each
//      branch starts with the operand node of a BRANCH node.
// BACK Normal "next" pointers all implicitly point forward; BACK
//      exists to make loop structures possible.
// STAR,PLUS,BRACES '?', and complex '*' and '+', are implemented as
//      circular BRANCH structures using BACK. Complex '{min,max}'
//      - as pair LOOPENTRY-LOOP (see below). Simple cases (one
//      character per match) are implemented with STAR, PLUS and
//      BRACES for speed and to minimize recursive plunges.
// LOOPENTRY,LOOP {min,max} are implemented as special pair
//      LOOPENTRY-LOOP. Each LOOPENTRY initialize loopstack for
//      current level.
// OPEN,CLOSE are numbered at compile time.


{=============================================================}
{================== Error handling section ===================}
{=============================================================}

const
 reeOk = 0;
 reeCompNullArgument = 100;
 reeCompRegexpTooBig = 101;
 reeCompParseRegTooManyBrackets = 102;
 reeCompParseRegUnmatchedBrackets = 103;
 reeCompParseRegUnmatchedBrackets2 = 104;
 reeCompParseRegJunkOnEnd = 105;
 reePlusStarOperandCouldBeEmpty = 106;
 reeNestedSQP = 107;
 reeBadHexDigit = 108;
 reeInvalidRange = 109;
 reeParseAtomTrailingBackSlash = 110;
 reeNoHexCodeAfterBSlashX = 111;
 reeHexCodeAfterBSlashXTooBig = 112;
 reeUnmatchedSqBrackets = 113;
 reeInternalUrp = 114;
 reeQPSBFollowsNothing = 115;
 reeTrailingBackSlash = 116;
 reeRarseAtomInternalDisaster = 119;
 reeBRACESArgTooBig = 122;
 reeBracesMinParamGreaterMax = 124;
 reeUnclosedComment = 125;
 reeComplexBracesNotImplemented = 126;
 reeUrecognizedModifier = 127;
 reeBadLinePairedSeparator = 128;
 reeRegRepeatCalledInappropriately = 1000;
 reeMatchPrimMemoryCorruption = 1001;
 reeMatchPrimCorruptedPointers = 1002;
 reeNoExpression = 1003;
 reeCorruptedProgram = 1004;
 reeNoInputStringSpecified = 1005;
 reeOffsetMustBeGreaterThen0 = 1006;
 reeExecNextWithoutExec = 1007;
 reeGetInputStringWithoutInputString = 1008;
 reeDumpCorruptedOpcode = 1011;
 reeModifierUnsupported = 1013;
 reeLoopStackExceeded = 1014;
 reeLoopWithoutEntry = 1015;
 reeBadDirective = 1500;
 reeBadPCodeImported = 2000;
 reeInvalidPredicate = 3000;

{ TParallelizer }

{$OPTIMIZATION REGVAR,CSE,DFA,PEEPHOLE,LEVEL2}

(* LU - разложение  с выбором максимального элемента по диагонали *)
Function _GetLU(NN: Integer; Var iRow: IntArray; Const A: RealArray; Var LU: RealArray): Boolean;

Var i, j, k: Integer;
    Big, size: Real;
    iBig: Integer;
    V: Integer;
    Kf: Real;
    Fact: Real;
begin
 Try
   Move(A[0],LU[0],NN*NN*sizeof(Real));
   for i:=0 to NN-1 do
       iRow[i]:=i;
   for i:=0 to NN-2 do
     begin
      Big := abs(LU[iRow[i]*NN+i]);
      iBig := i;

      for j:=i+1 to NN-1 do
          begin
           size := abs(LU[iRow[j]*NN+i]);

           if (size>Big) then
              begin
               Big := size;
               iBig := j;
              end
          end;
      if (iBig<>i) then
         begin
          V := iRow[i];
          iRow[i] := iRow[iBig];
          iRow[iBig] := V;
         end;
      Kf := 1.0/LU[iRow[i]*NN+i];

      LU[iRow[i]*NN+i] := Kf;
      for j:=i+1 to NN-1 do
          begin
           Fact := Kf*LU[iRow[j]*NN+i];

           LU[iRow[j]*NN+i] := Fact;
           for k:=i+1 to NN-1 do
               LU[iRow[j]*NN+k] := LU[iRow[j]*NN+k] - Fact*LU[iRow[i]*NN+k];
          end
     end;
   LU[(iRow[NN-1]+1)*NN-1] := 1.0/LU[(iRow[NN-1]+1)*NN-1];
 Except
   Exit(False);
 End;
 Result := True;
end;

(* Метод LU - разложения *)
Function _SolveLU(NN: Integer; Var iRow: IntArray; Const LU: RealArray; Const Y: RealArray; Var X: RealArray): Boolean;

 Var i, j, k: Integer;
     V: Real;
 begin
  Try
   X[0] := Y[iRow[0]];
   for i:=1 to NN-1 do
       begin
        V := Y[iRow[i]];

        for j:=0 to i-1 do
            V := V - LU[iRow[i]*NN+j]*X[j];
        X[i] := V;
       end;

   X[NN-1] := X[NN-1]*LU[(iRow[NN-1]+1)*NN-1];

   j := NN-2;
   for i:=1 to NN-1 do
       begin
        V := X[j];

        for k:=j+1 to NN-1 do
            V := V - LU[iRow[j]*NN+k]*X[k];
        X[j] := V*LU[iRow[j]*NN+j];
        Dec(j)
       end
 Except
   Exit(False)
 End;
 Result := True
end;

Function Predictor(M, Shift, Z: Integer; Const t: RealArray; Var a: RealArray): Boolean;

Var iRow: IntArray;
    Shift1: Integer;
    MAT, LU, B: RealArray;
    V: Real;
    i, j, p: Integer;
Begin
   SetLength(iRow, Z+1);
   SetLength(MAT, (Z+1)*(Z+1));
   SetLength(LU, (Z+1)*(Z+1));
   SetLength(B, Z+1);
   Shift1 := 1 - Shift;
   For i := 0 To Z do
       Begin
         B[i] := 0.0;
         For p := Z+Shift1 to M-1 do
             If i < Shift Then
                B[i] := B[i] + t[p]
             Else
                B[i] := B[i] + t[p]*t[p-i-Shift1];
         For j := 0 To Z do
           begin
             V := 0.0;
             If i < Shift Then
                If j < Shift Then
                   V := M - Z
                Else
                   For p := Z to M-1 Do
                       V := V + t[p-j]
             Else
                For p := Z+Shift1 to M-1 Do
                    V := V + t[p-i-Shift1]*t[p-j-Shift1];
             MAT[i*(Z+1)+j] := V
           end
       End;
   Result := _GetLU(Z+1, iRow, MAT, LU) And _SolveLU(Z+1, iRow, LU, B, a)
end;

Function Interpolator(M, Z: Integer; Const t: RealArray; Const y: RealArray; Var a: RealArray): Boolean;

Var iRow: IntArray;
    MAT, LU, B: RealArray;
    pows: RealArray;
    V: Real;
    i, j, k, p: Integer;
Begin
   SetLength(iRow, Z+1);
   SetLength(MAT, (Z+1)*(Z+1));
   SetLength(LU, (Z+1)*(Z+1));
   SetLength(B, Z+1);
   SetLength(pows, Length(t));
   Move(t[0], pows[0], Length(t)*SizeOf(Real));
   For i := 0 To Z do
       Begin
         B[i] := 0.0;
         For p := 0 to M-1 do
             If i = 0 Then
                B[i] := B[i] + y[p]
             Else
                B[i] := B[i] + y[p]*IntPower(t[p], i)
       End;
   For i := 1 To 2*Z do
       Begin
         V := 0.0;
         For j := 0 to M-1 Do
             V := V + pows[j];
         If i <= Z Then
            begin
              j := i;
              k := 0;
            end
         Else
            begin
              j := Z;
              k := i - Z
            end;
         While (j >= 0) And (k <= Z) Do
           begin
             MAT[k*(Z+1)+j] := V;
             Dec(j);
             Inc(k)
           end;
         If i <> 2*Z Then
            For j := 0 To M-1 Do
                pows[j] := pows[j]*t[j]
       End;
   Result := _GetLU(Z+1, iRow, MAT, LU) And _SolveLU(Z+1, iRow, LU, B, a)
end;

{ TFastSet }

constructor TFastSet.Create(V: Boolean);
begin
 Inherited Create(Nil)
end;

function TFastSet.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;
begin
 If Length(Descriptor) = 2 Then
    If (Descriptor[0].Kind = fpBound) Then
       Exit(Descriptor[0].Value = Descriptor[1].Value)
    Else
       Begin
         Descriptor[0].Value := Descriptor[1].Value;
         Exit(True)
       end;
 Exit(False)
end;

{ TFastSimilar }

constructor TFastSimilar.Create(V: Boolean);
begin
 Inherited Create(Nil)
end;

function TFastSimilar.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;

Var Threshold: Integer;
begin
 If Length(Descriptor) = 3 Then
    If (Descriptor[0].Kind = fpBound) And
       (Descriptor[1].Kind = fpBound) And
       (Descriptor[2].Kind = fpBound) Then
       Try
          Threshold := StrToInt(Descriptor[2].Value);
          Exit(Levenshtein(Descriptor[0].Value, Descriptor[1].Value) <= Threshold);
       Except
          Exit(False)
       End;
 Exit(False)
end;

{ TFastEqual }

constructor TFastEqual.Create(V: Boolean);
begin
 Inherited Create(Nil)
end;

function TFastEqual.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;
begin
 If Length(Descriptor) = 2 Then
    If (Descriptor[0].Kind = fpBound) And (Descriptor[1].Kind = fpBound) Then
       Exit(Descriptor[0].Value = Descriptor[1].Value);
 Exit(False)
end;

{ TFastXPathF }

constructor TFastStopFail.Create;
begin
  Inherited Create(Nil)
end;

function TFastStopFail.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;

begin
   If Length(Descriptor) = 1 Then
      If Descriptor[0].Kind = fpBound Then
         R.fInputEnd := R.reginput + StrToInt(Descriptor[0].Value);
   Exit(False)
end;

{ TFastBoolConst }

constructor TFastBoolConst.Create(V: Boolean);
begin
  Inherited Create(Nil);
  Val := V
end;

function TFastBoolConst.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;

begin
   Exit(Val)
end;

{ TFastXPathF }

constructor TFastXPathF.Create;
begin
  Inherited Create(Nil)
end;

function TFastXPathF.Unify(R: TRegExpr; ENV: TXPathEnvironment;
  var Descriptor: TFastPositions): Boolean;

 function GetNodeValue(P: TDOMNode): String;
 begin
    If Not Assigned(P) Then
       Result := ''
    Else
       Result := P.NodeValue
 end;

Var parser: TDOMParser;
    src: TXMLInputSource;
    dom: TXMLDocument;
    expr: String;
    LST: TDOMNodeList;
    S, S1, Rel: String;
    F, G: Integer;
    res: TXPathVariable;
begin
  If Not Assigned(ENV) Then raise Exception.Create('XPath module is not connected');

  If Length(Descriptor) >= 3 Then
     If (Descriptor[0].Kind = fpBound) And (Descriptor[1].Kind = fpBound) Then
        begin
          parser := TDOMParser.Create;
          parser.Options.PreserveWhitespace := True;
          parser.Options.Namespaces := True;

          src := TXMLInputSource.Create('<root>' + {!!!}UTF8Encode(Descriptor[0].Value) + '</root>');
          Result := False;
          try
             parser.Parse(src, dom);
             try
                expr := Descriptor[1].Value + LeftBracket;
                For F := 2 To Length(Descriptor) - 2 Do
                    If Descriptor[F].Kind = fpBound Then
                       AppendStr(expr, '"'+ WideString(Descriptor[F].Value) + '",')
                    Else
                       AppendStr(expr, '$RETURN' + IntToStr(F) + ',');
                If expr[Length(expr)] = Comma Then
                   expr[Length(expr)] := RightBracket
                Else
                   AppendStr(expr, RightBracket);
                res := EvaluateXPathExpression(expr, dom.DocumentElement, ENV.NodeNameTester, [Nil, Nil, dom.DocumentElement], Nil, Nil, ENV);
                For F := 2 To Length(Descriptor) - 2 Do
                    If Descriptor[F].Kind <> fpBound Then
                       begin
                         Descriptor[F].Value := {UTF8Decode}(ENV.VariablesByName['RETURN' + IntToStr(F)].AsText);
                         ENV.RemoveVariable('RETURN' + IntToStr(F))
                       end;
                If Descriptor[Length(Descriptor) - 1].Kind = fpBound Then
                   Result := res.AsText = Descriptor[Length(Descriptor) - 1].Value
                Else
                   begin
                     Descriptor[Length(Descriptor) - 1].Value := {UTF8Decode}(res.AsText);
                     Result := True
                   end;
                res.Free;
                res := EvaluateXPathExpression('/*/Link[Right/Value[@polled] or Left/Value[@polled]]', dom.DocumentElement, Nil, [], Nil, Nil, ENV);
                If res is TXPathNodeSetVariable Then
                   For F := 0 To res.AsNodeSet.Count - 1 Do
                     Begin
                       LST := TDOMNode(res.AsNodeSet[F]).ChildNodes;
                       For G := 0 To LST.Count - 1 Do
                           If TDOMNode(LST[G]).NodeName = 'Name' Then
                              Rel := TDOMNode(LST[G]).FirstChild.NodeValue
                           Else If TDOMNode(LST[G]).NodeName = 'Right' Then
                              S1 := GetNodeValue(TDOMNode(LST[G]).FirstChild.FirstChild)
                           Else If TDOMNode(LST[G]).NodeName = 'Left' Then
                              S := GetNodeValue(TDOMNode(LST[G]).FirstChild.FirstChild);
                       If (Length(S) > 0) Then
                          ENV.LocalWords.Add(S);
                       If (Length(S1) > 0) Then
                          ENV.LocalWords.Add(S1);
                       If Length(Rel) > 0 Then
                          ENV.LocalRels.Add(Rel + '(' + S + ':' + S1 + ')');
                       LST.Free
                     end;
                res.Free;
             finally
                dom.Free
             end;
          finally
             src.Free;
             parser.Free
          end;
          Exit
        end;
  Exit(False)
end;

{ TFastXPath }

constructor TFastXPath.Create;
begin
  Inherited Create(Nil)
end;

function TFastXPath.Unify(R: TRegExpr; ENV: TXPathEnvironment; var Descriptor: TFastPositions
  ): Boolean;

Var parser: TDOMParser;
    src: TXMLInputSource;
    dom: TXMLDocument;
    res: TXPathVariable;
    LST: TDOMNodeList;
    Rel, S, S1: String;
    F, G: Integer;
begin
  If Not Assigned(ENV) Then raise Exception.Create('XPath module is not connected');

  If Length(Descriptor) = 3 Then
     If (Descriptor[0].Kind = fpBound) And (Descriptor[1].Kind = fpBound) Then
        begin
          parser := TDOMParser.Create;
          parser.Options.PreserveWhitespace := True;
          parser.Options.Namespaces := True;

          src := TXMLInputSource.Create('<root>' + {!!!}UTF8Encode(Descriptor[0].Value) + '</root>');
          Result := False;
          try
             parser.Parse(src, dom);
             try
                res := EvaluateXPathExpression(Descriptor[1].Value, dom.DocumentElement, ENV.NodeNameTester, [Nil, Nil, dom.DocumentElement], Nil, Nil, ENV);
                If Descriptor[2].Kind = fpBound Then
                   Result := res.AsText = Descriptor[2].Value
                Else
                   begin
                     Descriptor[2].Value := {UTF8Decode}(res.AsText);
                     Result := True
                   end;
                res.Free;
                res := EvaluateXPathExpression('/*/Link[Right/Value[@polled] or Left/Value[@polled]]', dom.DocumentElement, Nil, [], Nil, Nil, ENV);
                If res is TXPathNodeSetVariable Then
                   For F := 0 To res.AsNodeSet.Count - 1 Do
                     Begin
                       LST := TDOMNode(res.AsNodeSet[F]).ChildNodes;
                       For G := 0 To LST.Count - 1 Do
                           If TDOMNode(LST[G]).NodeName = 'Name' Then
                              Rel := TDOMNode(LST[G]).FirstChild.NodeValue
                           Else If TDOMNode(LST[G]).NodeName = 'Right' Then
                              S1 := TDOMNode(LST[G]).FirstChild.FirstChild.NodeValue
                           Else If TDOMNode(LST[G]).NodeName = 'Left' Then
                              S := TDOMNode(LST[G]).FirstChild.FirstChild.NodeValue;
                       If (Length(S) > 0) Then
                          ENV.LocalWords.Add(S);
                       If (Length(S1) > 0) Then
                          ENV.LocalWords.Add(S1);
                       If Length(Rel) > 0 Then
                          ENV.LocalRels.Add(Rel + '(' + S + ':' + S1 + ')');
                       LST.Free
                     end;
                res.Free;
             finally
                dom.Free
             end;
          finally
             src.Free;
             parser.Free
          end;
          Exit
        end;
  Exit(False)
end;

{ TFastExternal }

constructor TFastExternal.Create(proc: Pointer);
begin
  Inherited Create;
  Caller := TExternal(proc)
end;

function TFastExternal.ExportDB(const Name: String): String;
begin
   Result := ''
end;

function TFastExternal.ExportPascalDB(const ID: String; var out: TStringList;
  const Offs, vDB: String): Boolean;
begin
  Result := True
end;

function TFastExternal.Unify(R: TRegExpr; ENV: TXPathEnvironment; var Descriptor: TFastPositions): Boolean;

Var Map, p: PWideChar;
    Vals: Array Of PWideChar;
    F: Integer;
begin
  GetMem(Map, (Length(Descriptor)+1)*SizeOf(WideChar));
  SetLength(Vals, Length(Descriptor));
  p := Map;
  For F := Low(Descriptor) To High(Descriptor) Do
      begin
        GetMem(Vals[F], Max(Length(Descriptor[F].Value)+2,65536)*SizeOf(WideChar));
        System.Move(Descriptor[F].Value[1], Vals[F]^, Length(Descriptor[F].Value)*SizeOf(WideChar));
        (Vals[F]+Length(Descriptor[F].Value))^ := #0;
        If Descriptor[F].Kind = fpBound Then
           p^ := #0
        Else
           p^ := '*';
        Inc(p)
      end;
  p^ := #0;
  Result := Caller(Length(Descriptor), Map, @Vals[0]);
  For F := Low(Descriptor) To High(Descriptor) Do
      begin
        If Descriptor[F].Kind = fpFree Then
           Descriptor[F].Value := Vals[F];
        FreeMem(Vals[F]);
      end;
  FreeMem(Map)
end;

function TFastExternal.Assert(const Descriptor: TFastPositions): Boolean;
begin
  Result := False
end;

function TFastExternal.Retract(const Descriptor: TFastPositions): Boolean;
begin
  Result := False
end;

function TFastExternal.Learn(const Descriptor: TFastPositions): Boolean;
begin
  Result := False
end;

procedure TFastExternal.StartTransaction;
begin
end;

procedure TFastExternal.Commit;
begin
end;

procedure TFastExternal.RollBack;
begin
end;

{$OPTIMIZATION OFF}

constructor TParallelizer.Create;
begin
   Inherited Create;
   SetLength(a, nt1Koeffs);
   SetLength(m, ntnPower+1);
   SetLength(t1, parFirstStage+parSecondStage);
   SetLength(tn, parFirstStage+parSecondStage);
   Stage := -1;
   Counter := 0
end;

procedure TParallelizer.Clear;
begin
  Stage := -1;
  Counter := 0;
end;

procedure TParallelizer.PutT(Parallel: Boolean; T: Real);

const omega = 0.15;

Var x,y: RealArray;
    p: Integer;
    r, d: Real;
    i, j: Integer;
begin
  If Counter < parFirstStage + parSecondStage Then
     If Parallel Then
        tn[Counter] := T
     Else
        t1[Counter] := T
  Else
     Begin
       Move(t1[1], t1[0], (parFirstStage + parSecondStage - 1)*SizeOf(Real));
       Move(tn[1], tn[0], (parFirstStage + parSecondStage - 1)*SizeOf(Real));
       If Parallel Then
          tn[parFirstStage + parSecondStage - 1] := T
       Else
          t1[parFirstStage + parSecondStage - 1] := T
     End;
  Inc(Counter);
  If Stage = 0 Then
     If (Counter Mod parSimpleStage) = 0 Then
        Begin
          Stage := -1;
          Counter := 0
        End
     Else
        Exit
  Else If Stage < 0 Then
     Begin
       If Counter = parPreStage Then
          Begin
            predt1 := 0.5*(t1[0]+t1[2]);
            predtn := 0.5*(tn[1]+tn[3]);
            if (predt1 >= 1.5*predtn) Or (predt1 <= 0.5*predtn) then
               Stage := 0
            Else
               Begin
                 Stage := 1;
                 Counter := 0
               End
          End
     End
  Else If (Stage = 1) And (Counter = parFirstStage) Then
     Begin
       If Predictor(parFirstStage, nt1Shift, nt1Koeffs-1, t1, a) Then
          Stage := 2
       Else
          Begin
            Move(t1[1], t1[0], (parFirstStage-1)*SizeOf(Real));
            Dec(Counter)
          End
     end
  Else If (Stage = 2) And (Counter = parFirstStage + parSecondStage) Then
     Begin
       // Calc t1 in tn points, get (t1;tn) array
       SetLength(x, parSecondStage);
       SetLength(y, parSecondStage);
       p := 0;
       For i := parFirstStage to parFirstStage+parSecondStage-1 do
           if ((i-parFirstStage) Mod 3) <> 0 then
              begin
                If nt1Shift = 1 Then
                   begin
                     t1[i] := a[0];
                     For j := 1 To nt1Koeffs-1 do
                         t1[i] := t1[i] + a[j]*t1[i-j]
                   end
                Else
                   begin
                     t1[i] := 0.0;
                     For j := 0 To nt1Koeffs-1 do
                         t1[i] := t1[i] + a[j]*t1[i-j-1]
                   end;
                x[p] := t1[i];
                y[p] := tn[i];
                Inc(p)
              end;
       // Calc m,p,q by tn points
       Interpolator(p, ntnPower, x, y, m);
       // Calc tn at t1 points (Stage1, Stage2)
       For i := 0 to parFirstStage - 1 Do
           begin
             tn[i] := 0.0;
             For j := ntnPower Downto 0 Do
                 tn[i] := m[j] + tn[i]*t1[i]
           end;
       For i := parFirstStage to parFirstStage+parSecondStage-1 do
           if ((i-parFirstStage) Mod 3) = 0 then
              begin
                tn[i] := 0.0;
                For j := ntnPower Downto 0 Do
                    tn[i] := m[j] + tn[i]*t1[i]
              end;
       // Recalc predictor by [Counter] of t1 points
       Predictor(parFirstStage+parSecondStage, nt1Shift, nt1Koeffs-1, t1, a);
       Stage := 3
     end
  Else If Stage = 3 Then
     Begin
       if Parallel Then // if tn calc t1
          begin
            If Abs(m[2]) < 1E-6 Then
               t1[parFirstStage+parSecondStage-1] := (T - m[0]) / m[1]
            Else
              begin
                d := m[1]*m[1] - 4.0*(m[0]-T)*m[2];
                if d < 0 Then
                   t1[parFirstStage+parSecondStage-1] := T
                else
                   begin
                     t1[parFirstStage+parSecondStage-1] := (-m[1] + Sqrt(d))/(2.0*m[2]);
                     if (abs(predt1) < 1.0) And (abs(predtn-T) < 1.0) Then
                        begin
                          m[0] := m[0] - omega*(predtn - T);
                          m[1] := m[1] - omega*(predtn - T)*predt1;
                          m[2] := m[2] - omega*(predtn - T)*predt1*predt1
                        end
                   end
              end
          end
       Else
          begin // if t1 calc tn
            r := 0.0;
            For j := ntnPower Downto 0 Do
                r := m[j] + r*T;
            tn[parFirstStage+parSecondStage-1] := r;
            // correct t1 predictor
            if (abs(predt1-T) < 1.0) And (T < 1.0) Then
               begin
                 if nt1Shift = 1 Then
                    begin
                      a[0] := a[0] - omega*(predt1 - T);
                      For j := 1 to nt1Koeffs-1 Do
                          a[j] := a[j] - omega*(predt1 - T)*t1[parFirstStage+parSecondStage-1-j]
                    end
                 else
                    begin
                      For j := 0 to nt1Koeffs-1 Do
                          a[j] := a[j] - omega*(predt1 - T)*t1[parFirstStage+parSecondStage-1-j-1]
                    end
               end;
          end;
       // recalc all each parerie calls
       If (Counter - (parFirstStage + parSecondStage)) Mod parSerie = 0 Then
          begin
            // Calc m,p,q by tn points
            Interpolator(parSerie, ntnPower, t1, tn, m);
            // Recalc predictor
            Predictor(parSerie, nt1Shift, nt1Koeffs-1, t1, a);
          end
     end
end;

function TParallelizer.InParallel: Boolean;

Var j: Integer;
begin
  If Stage < 0 Then
     Result := (Counter Mod 2) <> 0
  Else If Stage = 0 Then
     Result := predtn < predt1
  Else If Stage = 1 Then
     Result := False
  Else If Stage = 2 Then
     Result := ((Counter-parFirstStage) Mod 3) <> 0
  Else If Stage = 3 Then
     Begin
       // Prediction
       If nt1Shift = 1 Then
          begin
            predt1 := a[0];
            For j := 1 To nt1Koeffs-1 do
                predt1 := predt1 + a[j]*t1[parFirstStage+parSecondStage-j]
          end
       Else
          begin
            predt1 := 0.0;
            For j := 0 To nt1Koeffs-1 do
                predt1 := predt1 + a[j]*t1[parFirstStage+parSecondStage-j-1]
          end;
       predtn := 0.0;
       For j := ntnPower Downto 0 Do
           predtn := m[j] + predtn*predt1;
       Result := predtn < predt1;
       {$IF NOT DEFINED(VCL) AND NOT DEFINED(LCL)}
       WriteLn('Parallel:', Result, ' ', predt1, ' ', predtn);
       {$ENDIF}
     end
end;

{ TFastNet }

constructor TFastNet.Create(const FName: String; FDB: TFastDB);
begin
  Inherited Create;
  Self.FName := FName;
  Self.FDB := FDB
end;

function TFastNet.ExportDB(const Name: String): String;
begin
  Result := SpecSymbol + fpNeuro + LeftBracket + Name + Comma + Quote + FName + Quote + RightBracket + Point + #$0D#$0A
end;

function TFastNet.ExportPascalDB(const ID: String; var out: TStringList;
  const Offs, vDB: String): Boolean;
begin
  Result := True;
  out.Add(Offs + vDB + '.AddObject(''' + ID + ''', TFastNet.Create(''' + FName + ''', ' + vDB + '));')
end;

function TFastNet.Unify(R: TRegExpr; ENV: TXPathEnvironment; var Descriptor: TFastPositions): Boolean;

Var L: TStringList;
    I: Integer;
    Treba: String;
    CheckOnly: Boolean;
    S: String;
begin
  Treba := '"[';
  CheckOnly := True;
  For I := Low(Descriptor) To High(Descriptor) Do
      If Descriptor[I].Kind = fpBound Then
         AppendStr(Treba, Descriptor[I].Value + ',')
      Else
         begin
           AppendStr(Treba, '*,');
           CheckOnly := False
         end;
  If Length(Treba) = 1 Then
     AppendStr(Treba, ']')
  Else
     Treba[Length(Treba)] := ']';
  AppendStr(Treba, '"');
  L := TStringList.Create;
  try
     {$IF DEFINED(LCL) OR DEFINED(VCL)}
     RunExtCommand(
        {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
        FName + ' unify ' + Treba + ' _ _ _ _.info',
        '_.info');
     {$ELSE}
     WriteLn(RunExtCommand(
        {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
        FName + ' unify ' + Treba + ' _ _ _ _.info',
        '_.info'));
     {$ENDIF}
     L.LoadFromFile('_.info');
     Result := (L.Count > 0) And (L.Strings[0][1] = '#');
     If Result Then
        Begin
          S := Copy(L.Strings[0], 2, 2048);
          L.Delimiter := ' ';
          L.StrictDelimiter := True;
          L.DelimitedText := S;
          If CheckOnly Then
             Result := Round(StrToFloat(L.Strings[High(Descriptor)])) = Round(StrToFloat(Descriptor[High(Descriptor)].Value))
          Else
            For I := Low(Descriptor) To High(Descriptor) Do
                If Descriptor[I].Kind <> fpBound Then
                   Descriptor[I].Value := IntToStr(Round(StrToFloat(L.Strings[I])));
        End;
  except
     Result := False
  end;
  L.Free
end;

function TFastNet.Assert(const Descriptor: TFastPositions): Boolean;
begin
  Result := False;
end;

function TFastNet.Retract(const Descriptor: TFastPositions): Boolean;
begin
  Result := False
end;

function TFastNet.Learn(const Descriptor: TFastPositions): Boolean;

Var L: TStringList;
    I: Integer;
    Prms: String;
begin
 L := TStringList.Create;
 If Length(Descriptor) = 0 Then
    begin
       try
          {$IF DEFINED(LCL) OR DEFINED(VCL)}
          RunExtCommand(
             {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
             FName + ' teach _ _ _ _ _.info',
             '_.info');
          {$ELSE}
          WriteLn(RunExtCommand(
             {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
             FName + ' teach _ _ _ _ _.info',
              '_.info'));
          {$ENDIF}
          L.LoadFromFile('_.info');
          Result := (L.Count > 0) And (L.Strings[0] = '#')
       except
          Result := False
       end
    end
 Else
   begin
     Prms := FName + ' create ';
     I := FDB.IndexOf(Descriptor[0].Value);
     If (I < 0) Or Not (FDB.Objects[I] is TFastTable) Then
        begin
          L.Free;
          Result := False
        end;
     AppendStr(Prms, TFastTable(FDB.Objects[I]).FName + ' ');
     For I := 1 To High(Descriptor) Do
         AppendStr(Prms, '"' + Descriptor[I].Value + '" ');
     try
        {$IF DEFINED(LCL) OR DEFINED(VCL)}
        RunExtCommand(
           {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
           Prms + ' _.info',
           '_.info');
        {$ELSE}
        WriteLn(RunExtCommand(
           {$IF DEFINED(UNIX) OR DEFINED(LINUX)}'run_nneuronet.sh'{$ELSE}'run_nneuronet.bat'{$ENDIF},
           Prms + ' _.info',
            '_.info'));
        {$ENDIF}
        L.LoadFromFile('_.info');
        Result := (L.Count > 0) And (L.Strings[0] = '#')
     except
        Result := False
     end
   end;
 L.Free
end;

procedure TFastNet.StartTransaction;
begin
end;

procedure TFastNet.Commit;
begin
end;

procedure TFastNet.RollBack;
begin
end;

{ TFastNearestTable }

constructor TFastNearestTable.Create(Threshold: Integer; const FName: String);
begin
  Inherited Create(FName);
  FThreshold := Threshold;
  FExact := False
end;

function TFastNearestTable.ExportDB(const Name: String): String;
begin
  Result := SpecSymbol + fpNearest + LeftBracket + Name + Comma + IntToStr(FThreshold) + Comma + Quote + FName + Quote + RightBracket + Point + #$0D#$0A
end;

function TFastNearestTable.ExportPascalDB(const ID: String;
  var out: TStringList; const Offs, vDB: String): Boolean;
begin
  Result := True;
  out.Add(Offs + vDB + '.AddObject(''' + ID + ''', TFastNearestTable.Create(' + IntToStr(FThreshold) + ', ''' + FName + '''));')
end;

function TFastNearestTable.Compare(const S1, S2: String): Integer;

Var N1, N2: Integer;
begin
  If (Length(S1) = 0) Or (Length(S2) = 0) Or (Not (S1[1] in ['0'..'9'])) Or (Not (S2[1] in ['0'..'9'])) Then
     If Abs(Length(S1)-Length(S2)) > FThreshold Then
        Result := FThreshold + 1
     Else
        Result := Levenshtein(S1, S2)
  Else
    Try
       N1 := StrToInt(S1);
       N2 := StrToInt(S2);
       Result := Abs(N1 - N2);
    Except
       If Abs(Length(S1)-Length(S2)) > FThreshold Then
          Result := FThreshold + 1
       Else
          Result := Levenshtein(S1, S2)
    end
end;

{ TFastTable }

constructor TFastTable.Create(const FName: String);
begin
  Inherited Create;
  Self.FName := FName;
  FThreshold := 0;
  FExact := True;

  FJournal := TStringList.Create;
  FJournalled := False
end;

destructor TFastTable.Destroy;
begin
  FJournal.Free;
  inherited Destroy
end;

function TFastTable.ExportDB(const Name: String): String;
begin
  Result := SpecSymbol + fpFast + LeftBracket + Name + Comma + Quote + FName + Quote + RightBracket + Point + #$0D#$0A
end;

function TFastTable.ExportPascalDB(Const ID: String; var out: TStringList; const Offs, vDB: String
  ): Boolean;
begin
   Result := True;
   out.Add(Offs + vDB + '.AddObject(''' + ID + ''', TFastTable.Create(''' + FName + '''));')
end;

function TFastTable.Compare(const S1, S2: String): Integer;
begin
  If S1 = S2 then
     Result := 0
  Else
     Result := 1
end;

function TFastTable.Unify(R: TRegExpr; ENV: TXPathEnvironment; var Descriptor: TFastPositions): Boolean;

Var L, SRC: TStringList;
    S: String;
    Found: Integer;
    Best: Integer;
    I, J: Integer;
begin
   Try
     If Not FileExists(FName) Then
        FileClose(FileCreate(FName));
     SRC := TStringList.Create;
     SRC.LoadFromFile(FName);
     L := TStringList.Create;
     Best := MaxInt;
     J := 0;
     While J < SRC.Count Do
       Begin
         S := SRC.Strings[J];
         Inc(J);
         L.CommaText := S;
         If L.Count = Length(Descriptor) Then
            Begin
              Found := 0;
              For I := Low(Descriptor) To High(Descriptor) Do
                  If Descriptor[I].Kind = fpBound Then
                     Inc(Found, Compare(L.Strings[I], Descriptor[I].Value));
              If Found < Best Then
                 Begin
                   For I := Low(Descriptor) To High(Descriptor) Do
                       If Descriptor[I].Kind <> fpBound Then
                          Descriptor[I].Value := L.Strings[I];
                   Best := Found;
                   If Best = 0 Then
                      begin
                        L.Free;
                        SRC.Free;
                        Exit(True)
                      end
                 End
            end
       End;
     L.Free;
     SRC.Free;
     Result := (Best <= FThreshold) And Not FExact;
   Finally
     If Result Then
      begin
        For I := Low(Descriptor) To High(Descriptor) Do
            If Descriptor[I].Logged Then
               If Assigned(ENV) Then
                  ENV.LocalWords.Add(Descriptor[I].Value)
      end
   End
end;

function TFastTable.Assert(const Descriptor: TFastPositions): Boolean;

Var SRC, L: TStringList;
    I: Integer;
begin
   SRC := TStringList.Create;
   If FileExists(FName) Then
      SRC.LoadFromFile(FName);
   L := TStringList.Create;
   For I := Low(Descriptor) To High(Descriptor) Do
       L.Add(Descriptor[I].Value);
   SRC.Add(L.CommaText);
   L.Free;
   SRC.SaveTofile(FName);
   If FJournalled Then
      FJournal.Add('-');
   SRC.Free;
   Result := True
end;

function TFastTable.Retract(const Descriptor: TFastPositions): Boolean;

Var L, SRC: TStringList;
    S: String;
    Found: Integer;
    Best: Integer;
    F1: TStringList;
    I, J, P: Integer;
begin
   If Not FileExists(FName) Then
      FileClose(FileCreate(FName));
   SRC := TStringList.Create;
   SRC.LoadFromFile(FName);
   L := TStringList.Create;
   F1 := TStringList.Create;
   Best := MaxInt;
   J := 0;
   While J < SRC.Count Do
     Begin
       S := SRC.Strings[J];
       Inc(J);
       L.CommaText := S;
       If L.Count = Length(Descriptor) Then
          Begin
            Found := 0;
            For I := Low(Descriptor) To High(Descriptor) Do
                If Descriptor[I].Kind = fpBound Then
                   Inc(Found, Compare(L.Strings[I], Descriptor[I].Value));
            If Found < Best Then
               Best := Found;
            F1.AddObject(S, IntegerToTObject(Found))
          end
     End;
   L.Free;
   SRC.Free;
   If ((Best = 0) And FExact) Or ((Best <= FThreshold) And Not FExact) Then
      With F1 Do
        Begin
          I := 0;
          While I < Count Do
            begin
              P := TObjectToInteger(Objects[I]);
              If ((P = 0) And FExact) Or ((P <= FThreshold) And Not FExact) Then
                 Begin
                   If FJournalled Then
                      FJournal.AddObject('+' + Strings[I], IntegerToTObject(I));
                   Delete(I)
                 End
              Else
                 Inc(I)
            end;
          SaveToFile(FName);
          Free
        End
   Else
      F1.Free;
   Result := True
end;

function TFastTable.Learn(const Descriptor: TFastPositions): Boolean;
begin
   Result := True
end;

procedure TFastTable.StartTransaction;
begin
   FJournal.Clear;
   FJournalled := True
end;

procedure TFastTable.Commit;
begin
   If FJournalled Then
      begin
        FJournal.Clear;
        FJournalled := False
      end;
end;

procedure TFastTable.RollBack;

Var L: TStringList;
    S: String;
    F: Integer;
begin
   If FJournalled Then
      begin
        With FJournal Do
          If Count > 0 then
             begin
               L := TStringList.Create;
               L.LoadFromFile(FName);
               For F := Count - 1 DownTo 0 Do
                   begin
                     S := Strings[F];
                     If S[1] = '-' Then
                        L.Delete(L.Count - 1)
                     Else If S[1] = '+' Then
                        L.Insert(TObjectToInteger(Objects[F]), Copy(S, 2, 16384))
                   end;
               L.SaveToFile(FName);
               L.Free;
               Clear
             end;
        FJournalled := False
      end;
end;

{ TFastCalls }

constructor TFastCalls.Create;
begin
  Inherited Create;
  Analyzers := TList.Create;
  Alternation := Nil
end;

destructor TFastCalls.Destroy;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
      TObject(Items[F]).Free;
  With Analyzers Do
    Begin
      For F := 0 To Count - 1 Do
          TParallelizer(Items[F]).Free;
      Free
    end;
  Alternation.Free;
  inherited Destroy;
end;

procedure TFastCalls.ClearAnalyzers;

Var F: Integer;
begin
  With Analyzers Do
    For F := 0 To Count - 1 Do
        TParallelizer(Items[F]).Clear;
end;

function TFastCalls.FillIn(pcall: TFastCall; const R: TRegExpr; var valext: TStringList
  ): Boolean;

Var G: Integer;
    i, j: integer;
    stp, enp: PRegExprChar;
    S: RegExprString;
begin
   For G := 0 To High(pcall.Descriptor) Do
       If pcall.Descriptor[G].Kind = fpBound Then
          if pcall.References[G] >= 0 Then
             begin
               if pcall.References[G] >= 1000 then
                  begin
                    i := (pcall.References[G] Div 1000) - 1;
                    j := pcall.References[G] Mod 1000;
                    stp := TRegExpr(valext.Objects[i]).startp[j];
                    enp := TRegExpr(valext.Objects[i]).endp[j];
                    SetLength(S, enp - stp);
                    System.Move(stp^, S[1], Length(S)*SizeOf(REChar))
                  end
               else
                  begin
                    SetLength(S, R.endp[pcall.References[G]] - R.startp[pcall.References[G]]);
                    System.Move(R.startp[pcall.References[G]]^, S[1], Length(S)*SizeOf(REChar))
                  end;
               pcall.Descriptor[G].Value := UTF8Encode(S)
             end;
   Result := True
end;

function TFastCalls.FillOut(pcall: TFastCall; const R: TRegExpr; var _valsp
  ): Boolean;

Var valsp: Array[0..NSUBEXP-1] of TVarValue Absolute _valsp;
    G: Integer;
    V: TVarValue;
begin
   For G := 0 To High(pcall.Descriptor) Do
       If pcall.Descriptor[G].Kind <> fpBound Then
          if pcall.References[G] >= 0 Then
             begin
               if pcall.References[G] < 1000 then
                  begin
                    if Assigned(valsp[pcall.References[G]]) Then
                       begin
                         EnterCriticalSection(R.Trasher);
                         Try
                            R.addTrash(valsp[pcall.References[G]]);
                         finally
                            LeaveCriticalSection(R.Trasher)
                         end
                       end;
                    V := TVarValue.Create(R, pcall.References[G], Nil, -1, UTF8Decode(pcall.Descriptor[G].Value));
                    valsp[pcall.References[G]] := V;
                    V.AssignBVal(R.startp[pcall.References[G]], R.endp[pcall.References[G]]);
                    V.AddObject(pcall.Descriptor[G].Value, Nil)
                  end
             end;
   Result := True
end;

Type PoolItem = Record
        Call: TFastCalls;
        Action: TFastCallsAction;
        ENV: TXPathEnvironment;
        makeFillIn: Boolean;
        Worker: Integer;
        DB: TFastDB;
        R: TRegExpr;
        valext: TStringList;
        valsp: Pointer;
        inp, outp: Set Of Byte; // Номера локальных переменных на входе и на выходе
        deps: Set Of Byte; // Номера элементов цепочки, от которых есть зависимость
        Result: Boolean
     End;

procedure Unificator(R: TRegExpr; Index: PtrInt; Data: Pointer; Item: TMultiThreadProcItem);

Var Pool: Array Of PoolItem Absolute Data;
    pcall: TFastCall;
    K: Integer;
begin
   For K := 0 To 255 Do
     if K in Pool[Index].deps Then
        Item.WaitForIndex(K);
   pcall := Pool[Index].Call.Items[Pool[Index].Worker];
   Pool[Index].Call.FillIn(pcall, Pool[Index].R, Pool[Index].valext);
   If Pool[Index].DB.Unify(R, Pool[Index].ENV, pcall.Predicate, pcall.Descriptor) = pcall.Negate Then
      begin
        Pool[Index].Result := False;
        Exit
      end;
   Pool[Index].Call.FillOut(pcall, Pool[Index].R, Pool[Index].valsp^);
   Pool[Index].Result := True
end;

function TFastCalls.Unify(ENV: TXPathEnvironment; const DB: TFastDB; const R: TRegExpr; var valext: TStringList; var valsp
  ): Boolean;

 Var Pool: Array Of PoolItem;
     pcall: TFastCall;
     pcalls: TFastCalls;
     F, After, G: Integer;
     pAnalyze, parallel: Boolean;
     pNumber: Integer;
     pTime: TDateTime;
     pms: Int64;
     K: Integer;
 begin
    Result := False;
    F := 0;
    pNumber := 0;
    While F < Count Do
     If TObject(Items[F]) Is TFastCall Then
        begin
          pcall := TFastCall(Items[F]);
          if pcall.Predicate = dirParallel Then
             begin
               pAnalyze := (Length(pcall.Descriptor) = 1) And FillIn(pcall, R, valext) And
                  (pcall.Descriptor[0].Value <> '0') And
                  (pcall.Descriptor[0].Value <> '');
               Inc(F);
               After := F;
               While After < Count Do
                 If TObject(Items[After]) Is TFastCalls Then
                    Exit(False)
                 Else
                    begin
                      pcall := TFastCall(Items[After]);
                      if pcall.Predicate = dirSequential Then
                         Break
                      else if pcall.Predicate = dirParallel Then
                         Exit(False);
                      Inc(After)
                    end;
               If After <> F Then
                  begin
                    SetLength(Pool, After - F);
                    FillChar(Pool[0], Length(Pool)*SizeOf(PoolItem), 0);
                    G := 0;
                    While F < After Do
                      begin
                        pcall := TFastCall(Items[F]);
                        Pool[G].Call := Self;
                        Pool[G].ENV := ENV;
                        Pool[G].DB := DB;
                        Pool[G].R := R;
                        Pool[G].valext := valext;
                        Pool[G].valsp := @valsp;
                        Pool[G].Worker := F;
                        For K := 0 To High(pcall.References) Do
                            if (pcall.References[K] >= 0) And (pcall.References[K] < 1000) Then
                               if pcall.Descriptor[K].Kind = fpBound then
                                  Include(Pool[G].inp, pcall.References[K])
                               else if pcall.Descriptor[K].Kind = fpFree then
                                  Include(Pool[G].outp, pcall.References[K]);
                        For K := 0 To G - 1 Do
                            begin
                              If (Pool[G].inp*Pool[K].outp <> []) Or (Pool[G].outp*(Pool[K].inp+Pool[K].outp) <> []) Then
                                 Include(Pool[G].deps, K);
                            end;
                        For K := 0 To 255 Do
                            if K in Pool[G].deps Then
                               Pool[G].inp := Pool[G].inp + Pool[K].inp;
                        Inc(G);
                        Inc(F)
                      end;
                    If pAnalyze Then
                       begin
                         If Analyzers.Count = pNumber Then
                            Analyzers.Add(TParallelizer.Create);
                         parallel := TParallelizer(Analyzers[Analyzers.Count-1]).InParallel;
                         If parallel Then
                            ProcThreadPool.MaxThreadCount := Length(Pool)
                         Else
                            ProcThreadPool.MaxThreadCount := 1;
                       end
                    Else
                       ProcThreadPool.MaxThreadCount := Length(Pool);
                    if pAnalyze Then pTime := Now;
                    ProcThreadPool.DoParallel(@Unificator, 0, High(Pool), Pool);
                    For K := 0 To High(Pool) Do
                        If Not Pool[K].Result Then
                           Exit(False);
                    if pAnalyze Then
                       begin
                         pms := MilliSecondsBetween(pTime,Now) + Random(6);
                         TParallelizer(Analyzers[Analyzers.Count-1]).PutT(parallel, pms*0.0001)
                       end;
                  end;
               Inc(pNumber)
             end
          else
             begin
               if pcall.Predicate <> dirSequential Then
                  begin
                    FillIn(pcall, R, valext);
                    If DB.Unify(R, ENV, pcall.Predicate, pcall.Descriptor) = pcall.Negate Then
                       If Assigned(Alternation) Then
                          Exit(Alternation.Unify(ENV, DB, R, valext, valsp))
                       Else
                          Exit(False);
                    FillOut(pcall, R, valsp)
                  end;
               Inc(F)
             end;
        end
     Else
        begin
          pcalls := TFastCalls(Items[F]);
          If pcalls.Unify(ENV, DB, R, valext, valsp) Then
             Inc(F)
          Else If Assigned(Alternation) Then
             Exit(Alternation.Unify(ENV, DB, R, valext, valsp))
          Else
             Exit(False)
        end;
    Result := True
 end;

procedure ARLator(Index: PtrInt; Data: Pointer; Item: TMultiThreadProcItem);

Var Pool: Array Of PoolItem Absolute Data;
    pcall: TFastCall;
    K: Integer;
begin
   For K := 0 To 255 Do
     if K in Pool[Index].deps Then
        Item.WaitForIndex(K);
   pcall := Pool[Index].Call.Items[Pool[Index].Worker];
   if (Pool[Index].makeFillIn) Then Pool[Index].Call.FillIn(pcall, Pool[Index].R, Pool[Index].valext);
   If Not Pool[Index].Action(pcall.Predicate, pcall.Descriptor) Then
      begin
        Pool[Index].Result := False;
        Exit
      end;
   Pool[Index].Result := True
end;

function TFastCalls.ARL(const DB: TFastDB; const R: TRegExpr; var valext: TStringList; var valsp;
  Action: TFastCallsAction; makeFillIn: Boolean): Boolean;

 Var Pool: Array Of PoolItem;
     pcall: TFastCall;
     pAnalyze, parallel: Boolean;
     pNumber: Integer;
     pTime: TDateTime;
     pms: Int64;
     F, After, G: Integer;
     K: Integer;
 begin
    Result := False;
    F := 0;
    pNumber := 0;
    While F < Count Do
     If TObject(Items[F]) Is TFastCalls Then
       Exit(False)
     Else
       begin
         pcall := TFastCall(Items[F]);
         if pcall.Predicate = dirParallel Then
            begin
              pAnalyze := (Length(pcall.Descriptor) = 1) And FillIn(pcall, R, valext) And
                 (pcall.Descriptor[0].Value <> '0') And
                 (pcall.Descriptor[0].Value <> '');
              Inc(F);
              After := F;
              While After < Count Do
               If TObject(Items[After]) Is TFastCalls Then
                  Exit(False)
               Else
                  begin
                    pcall := TFastCall(Items[After]);
                    if pcall.Predicate = dirSequential Then
                       Break
                    else if pcall.Predicate = dirParallel Then
                       Exit(False);
                    Inc(After)
                  end;
              If After <> F Then
                 begin
                   SetLength(Pool, After - F);
                   FillChar(Pool[0], Length(Pool)*SizeOf(PoolItem), 0);
                   G := 0;
                   While F < After Do
                     begin
                       pcall := TFastCall(Items[F]);
                       Pool[G].Call := Self;
                       Pool[G].Action := Action;
                       Pool[G].ENV := Nil;
                       Pool[G].makeFillIn := makeFillIn;
                       Pool[G].DB := DB;
                       Pool[G].R := R;
                       Pool[G].valext := valext;
                       Pool[G].valsp := @valsp;
                       Pool[G].Worker := F;
                       For K := 0 To G - 1 Do
                           begin
                             If pcall.Predicate = TFastCall(Items[F - (G - K)]).Predicate Then
                                Include(Pool[G].deps, K);
                           end;
                       Inc(G);
                       Inc(F)
                     end;
                   If pAnalyze Then
                      begin
                        If Analyzers.Count = pNumber Then
                           Analyzers.Add(TParallelizer.Create);
                        parallel := TParallelizer(Analyzers[Analyzers.Count-1]).InParallel;
                        If parallel Then
                           ProcThreadPool.MaxThreadCount := Length(Pool)
                        Else
                           ProcThreadPool.MaxThreadCount := 1;
                      end
                   Else
                      ProcThreadPool.MaxThreadCount := Length(Pool);
                   if pAnalyze Then pTime := Now;
                   ProcThreadPool.DoParallel(@ARLator, 0, High(Pool), Pool);
                   For K := 0 To High(Pool) Do
                       If Not Pool[K].Result Then
                          Exit(False);
                   if pAnalyze Then
                      begin
                         pms := MilliSecondsBetween(pTime,Now) + Random(6);
                         TParallelizer(Analyzers[Analyzers.Count-1]).PutT(parallel, pms*0.0001)
                      end;
                 end;
              Inc(pNumber)
            end
         else
            begin
              if pcall.Predicate <> dirSequential Then
                 begin
                   if makeFillIn Then
                      FillIn(pcall, R, valext);
                   If Not Action(pcall.Predicate, pcall.Descriptor) Then
                      Exit(False);
                 end;
              Inc(F)
            end;
       end;
    Result := True
 end;

function TFastCalls.Assert(const DB: TFastDB; const R: TRegExpr; var valext: TStringList; var valsp
  ): Boolean;
begin
  Result := ARL(DB, R, valext, valsp, DB.Assert, True)
end;

function TFastCalls.Retract(const DB: TFastDB; const R: TRegExpr; var valext: TStringList; var valsp
  ): Boolean;
begin
  Result := ARL(DB, R, valext, valsp, DB.Retract, True)
end;

function TFastCalls.Learn(const DB: TFastDB; const R: TRegExpr; var valext: TStringList; var valsp
  ): Boolean;
begin
  Result := ARL(DB, R, valext, valsp, DB.Learn, False)
end;

{ TFastDB }

constructor TFastDB.Create;
begin
  Inherited Create;
  Sorted := True;
  CaseSensitive := True;
  nUses := 0;

  libs := TStringList.Create;

  AddObject('xpath', TFastXPath.Create);
  AddObject('xpathf', TFastXPathF.Create);
  AddObject('stop_fail', TFastStopFail.Create);
  AddObject('fail', TFastBoolConst.Create(False));
  AddObject('true', TFastBoolConst.Create(True));
  AddObject('eq', TFastEqual.Create(True));
  AddObject('similar', TFastSimilar.Create(True));
  AddObject('set', TFastSet.Create(True))
end;

destructor TFastDB.Destroy;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
      Objects[F].Free;
  With libs Do
    For F := 0 To Count - 1 Do
        FreeLibrary(TLibHandle(TObjectToInteger(Objects[F])));
  inherited Destroy;
end;

function TFastDB.ExportDB: String;

Var F: Integer;
begin
   Result := '';
   For F := 0 To Count-1 Do
       AppendStr(Result, TFastPredicate(Objects[F]).ExportDB(Strings[F]))
end;

function TFastDB.ExportPascalDB(var out: TStringList; const Offs, vDB: String
  ): Boolean;

Var F: Integer;
begin
   Result := True;
   For F := 0 To Count-1 Do
       Result := Result And TFastPredicate(Objects[F]).ExportPascalDB(Strings[F], out, Offs, vDB)
end;

procedure TFastDB.Use;
begin
  Inc(nUses);
end;

procedure TFastDB.Release;
begin
  Dec(nUses);
  if nUses = 0 Then Free
end;

function TFastDB.GetIndexOf(const Predicate: String): Integer;

Var F: Integer;
    lib, p: String;
    H: TLibHandle;
    proc: Pointer;
    L: Integer;
begin
  Result := Inherited IndexOf(Predicate);
  If Result < 0 Then
     begin
        F := Pos('.', Predicate);
        If F > 0 Then
           begin
             lib := Copy(Predicate, 1, F - 1);
             p := Copy(Predicate, F + 1, 2048);
             L := libs.IndexOf(lib);
             If L < 0 Then
                begin
                  H := LoadLibrary({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'./lib' + {$ENDIF}lib + '.' + SharedSuffix);
                  If H = NilHandle Then
                     begin
                       {$IF DEFINED(LCL) OR DEFINED(VCL)}
                       MessageDlg('Can''t load library "' + lib + '"',mtWarning,[mbOk],0);
                       {$ELSE}
                       WriteLn('Can''t load library "' + lib + '"');
                       {$ENDIF}
                       Exit
                     end
                  Else
                     libs.AddObject(lib, IntegerToTObject(H))
                end
             Else
                H := TLibHandle(TObjectToInteger(libs.Objects[L]));
             proc := GetProcedureAddress(H, p);
             If TLibHandle(proc) = NilHandle Then
                begin
                  {$IF DEFINED(LCL) OR DEFINED(VCL)}
                  MessageDlg('Can''t load predicate "' + Predicate + '"',mtWarning,[mbOk],0);
                  {$ELSE}
                  WriteLn('Can''t load predicate "' + Predicate + '"');
                  {$ENDIF}
                  Exit
                end;
             Result := AddObject(Predicate, TFastExternal.Create(proc))
           end
     end
end;

function TFastDB.Unify(R: TRegExpr; ENV: TXPathEnvironment; const Predicate: String; var Descriptor: TFastPositions
  ): Boolean;

Var F: Integer;
begin
   F := GetIndexOf(Predicate);
   If F < 0 Then Exit(False);
   Result := TFastPredicate(Objects[F]).Unify(R, ENV, Descriptor)
end;

function TFastDB.Assert(const Predicate: String;
  const Descriptor: TFastPositions): Boolean;

Var F: Integer;
begin
   F := GetIndexOf(Predicate);
   If F < 0 Then Exit(False);
   Result := TFastPredicate(Objects[F]).Assert(Descriptor)
end;

function TFastDB.Retract(const Predicate: String;
  const Descriptor: TFastPositions): Boolean;

Var F: Integer;
begin
   F := GetIndexOf(Predicate);
   If F < 0 Then Exit(False);
   Result := TFastPredicate(Objects[F]).Retract(Descriptor)
end;

function TFastDB.Learn(const Predicate: String; const Descriptor: TFastPositions
  ): Boolean;

Var F: Integer;
begin
   F := GetIndexOf(Predicate);
   If F < 0 Then Exit(False);
   Result := TFastPredicate(Objects[F]).Learn(Descriptor);
end;

procedure TFastDB.StartTransaction;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
      TFastPredicate(Objects[F]).StartTransaction;
end;

procedure TFastDB.Commit;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
      TFastPredicate(Objects[F]).Commit;
end;

procedure TFastDB.RollBack;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
      TFastPredicate(Objects[F]).RollBack;
end;

{ TVarStruct }

constructor TVarStruct.Create;
begin
  Inherited Create;
  Tags := ''
end;

procedure TVarStruct.Mark(var M: TByteSet);

Var F: Integer;
begin
 For F := 0 To Count - 1 Do
   Begin
     If Assigned(Objects[F]) Then
        TVarValue(Objects[F]).Mark(M)
   End;
end;

function TVarStruct.ExportPredicates(const MacroID: String; const R: TRegExpr;
  var id: Integer; var L: String): String;

Var F: Integer;
    save: Integer;
begin
 Result := '';
 save := id;
 For F := 0 To Count - 1 Do
   Begin
     If Assigned(Objects[F]) Then
        AppendStr(Result, TVarValue(Objects[F]).ExportPredicates(MacroID, R, id, L))
   End;
 if save = id then
    Result := ''
end;

function TVarStruct.ExportXML(const R: TRegExpr): String;

 Var F: Integer;
 begin
  Result := '';
  For F := 0 To Count - 1 Do
    Begin
      If Assigned(Objects[F]) Then
         AppendStr(Result, TVarValue(Objects[F]).ExportXML(R))
    End
 end;

function TVarStruct.FindNode(ID: Integer): TVarStruct;

Var F: Integer;
begin
 If Self.ID = ID Then Exit(Self);
 For F := 0 To Count - 1 Do
     If Assigned(Objects[F]) Then
        Begin
          Result := TVarValue(Objects[F]).FindNode(ID);
          If Assigned(Result) Then Exit
        end;
 Result := Nil
end;

procedure TVarStruct.GrammarParse(const VName: String; command: String;
  var text: WideString; var stp, enp: PRegExprChar);

Type Transformer = function(Const text: PWideChar): PWideChar; cdecl;

Var lib, fn: String;
    T: Transformer;
    p: PWideChar;
    L: Integer;
    H: TLibHandle;
    F: Integer;
begin
 If Length(command) = 0 Then
    command := GDefTrans;
 F := Pos('.', command);
 If F > 0 Then
    begin
      lib := Copy(command, 1, F - 1);
      fn := Copy(command, F + 1, 2048);
      L := Transformers.IndexOf(lib);
      If L < 0 Then
         begin
           H := LoadLibrary({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'./lib' + {$ENDIF}lib + '.' + SharedSuffix);
           If H = NilHandle Then
              begin
                {$IF DEFINED(LCL) OR DEFINED(VCL)}
                MessageDlg('Can''t load library "' + lib + '"',mtWarning,[mbOk],0);
                {$ELSE}
                WriteLn('Can''t load library "' + lib + '"');
                {$ENDIF}
              end
           Else
              Transformers.AddObject(lib, IntegerToTObject(H))
         end
      Else
         H := TLibHandle(TObjectToInteger(Transformers.Objects[L]));
      If H <> NilHandle Then
         begin
            T := GetProcedureAddress(H, fn);
            If TLibHandle(@T) = NilHandle Then
               begin
                 {$IF DEFINED(LCL) OR DEFINED(VCL)}
                 MessageDlg('Can''t load transformer "' + fn + '"',mtWarning,[mbOk],0);
                 {$ELSE}
                 WriteLn('Can''t load transformer "' + fn + '"');
                 {$ENDIF}
                 text := 'Error';
               end
            else
               begin
                 text := utf8encode('#MVv;MVIv#'+text); {!!!}
                 p := T(PWideChar(text));
                 text := p;
                 // FreeMem(p);
               end
         end
      Else
         text := 'Error';
    end
 else
    text := 'Error';

  Tags := '<' + VName + '>' + UTF8Decode(text) + '</' + VName + '>';
  stp := @Tags[3 + Length(VName)];
  enp := @Tags[Length(Tags)-Length(VName)-2]
end;

procedure TVarStruct.out(const Shift: String);

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
    Begin
      WriteLn(Shift, '  [', F, '] = ', Strings[F]);
      If Assigned(Objects[F]) Then
         TVarValue(Objects[F]).Out(Shift + '    ')
    End
end;

{ TVarValue }

constructor TVarValue.Create(_Ref: TRegExpr; _Num: Integer; _Parent: TVarValue;
  _ParentIdx: Integer; const bv: RegExprString);
begin
  Inherited Create;
  Num := _Num;
  Parent := _Parent;
  ParentIdx := _ParentIdx;
  baseVal := bv;
  Ref := _Ref
end;

procedure TVarValue.Mark(var M: TByteSet);

Var F: Integer;
begin
 Include(M, Num);
 For F := 0 To Count - 1 Do
   Begin
     If Assigned(Objects[F]) Then
        TVarStruct(Objects[F]).Mark(M)
   End
end;

function TVarValue.ExportPredicates(const MacroID: String; const R: TRegExpr;
  var id: Integer; var L: String): String;

function split_if_need(S: String; Var S1: String): String;

Var Base, S2: String;
    F, G: Integer;
begin
 Result := '';
 If Length(S) < 8000 Then
    S1 := ''''+S+''''
 Else
    begin
       G := 8192;
       While (G > 0) And (S[G] = '\') Do
          Dec(G);
       S1 := ''''+Copy(S, 1, G)+'''';
       S := Copy(S, G+1, 16*65536);
       Base := UpperCase(RandomName);
       F := 0;
       While Length(S) > 0 Do
         begin
           G := 8192;
           if Length(S) > G Then
              While (G > 0) And (S[G] = '\') Do
                 Dec(G);
           S2 := ''''+Copy(S, 1, G)+'''';
           S := Copy(S, G+1, 16*65536);
           AppendStr(Result, 'atom_concat('+S1+','+S2+','+Base+IntToStr(F)+'),'+#$0D#$0A);
           S1 := Base+IntToStr(F);
           Inc(F)
         end
    end
end;

function export_tags(exprt: Boolean; E: TDOMNode; Var L: String): String;

Var L1: String;
    S, Term: String;
    F: Integer;
begin
  Result := '';

  L1 := '[';
  With E.ChildNodes Do
    begin
      For F := 0 To Count - 1 Do
        If Item[F].NodeName <> '#text' Then
           If exprt Then
              AppendStr(Result, export_tags(True, Item[F], L1))
           Else
              AppendStr(Result, export_tags(True, Item[F], L));
      Free
    end;

  If exprt Then
     Begin
       If Length(L1) > 1 Then L1[Length(L1)] := ']'
       else L1 := L1 + ']';

       S := EscapeProlog(E.TextContent);
       AppendStr(Result, split_if_need(S, Term));
       AppendStr(Result, 'assertz(var(''' + MacroID + ''',' + IntToStr(id) + ',''' + String(E.NodeName) + ''',' + Term + ',' + L1 + ')),' + #$0D#$0A);
       Inc(id);
       L := L + IntToStr(id - 1) + ','
     end
end;

Var F: Integer;
    L1: String;
    parser: TDOMParser;
    src: TXMLInputSource;
    dom: TXMLDocument;
    S, Term: String;
begin
 Result := '';
 if Assigned(R.VarNames[Num]) And Not (R.varsp[Num]^ in [#0, '+', '-', '*', '?', '!', '^']) then
    begin
        For F := 0 To Count - 1 Do
            begin
               L1 := '';
               If Assigned(Objects[F]) Then
                  begin
                    If TVarStruct(Objects[F]).Tags <> '' Then
                       begin
                         src := TXMLInputSource.Create(UTF8Encode(TVarStruct(Objects[F]).Tags));
                         parser := TDOMParser.Create;
                         parser.Parse(src, dom);
                         Try
                            AppendStr(Result, export_tags(False, dom.DocumentElement, L1));
                         finally
                            dom.Free;
                            parser.Free;
                            src.Free
                         end;
                       end;
                    AppendStr(Result, TVarStruct(Objects[F]).ExportPredicates(MacroID, R, id, L1));
                    TVarStruct(Objects[F]).ID := id;
                  end;
               If Assigned(Parent) Or (Length(Strings[F]) > 0) Then
                  S := Strings[F]
               Else
                  S := R.Match[Num];
               L1 := '[' + L1;
               If Length(L1) > 1 Then L1[Length(L1)] := ']'
               else L1 := L1 + ']';
               AppendStr(Result, split_if_need(EscapeProlog(S), Term));
               AppendStr(Result, 'assertz(var(''' + MacroID + ''',' + IntToStr(id) + ',''' + String(R.VarNames[Num]) + ''',' + Term + ',' + L1 + ')),' + #$0D#$0A);
               Inc(id);
               L := L + IntToStr(id - 1) + ','
            end
    end
 else
    begin
      For F := 0 To Count - 1 Do
        Begin
          If Assigned(Objects[F]) Then
             AppendStr(Result, TVarStruct(Objects[F]).ExportPredicates(MacroID, R, id, L))
        End
    end
end;

function TVarValue.ExportXML(const R: TRegExpr): String;

 function export_tags(exprt: Boolean; E: TDOMNode): String;

 Var F: Integer;
 begin
   Result := '';

   With E.ChildNodes Do
     begin
       For F := 0 To Count - 1 Do
         If Item[F].NodeName <> '#text' Then
            If exprt Then
               AppendStr(Result, export_tags(True, Item[F]))
            Else
               AppendStr(Result, export_tags(True, Item[F]));
       Free
     end;

   If exprt Then
      AppendStr(Result, '<' + String(E.NodeName) + '>' + E.TextContent + '</' + String(E.NodeName) + '>' + #$0D#$0A)
 end;

 Var F: Integer;
     parser: TDOMParser;
     src: TXMLInputSource;
     dom: TXMLDocument;
     S: String;
 begin
  Result := '';
  if Assigned(R.VarNames[Num]) And Not (R.varsp[Num]^ in [#0, '+', '-', '*', '?', '!', '^']) then
     begin
         For F := 0 To Count - 1 Do
             begin
               If Assigned(Parent) Or (Length(Strings[F]) > 0) Then
                  S := Strings[F]
               Else
                  S := R.Match[Num];
                AppendStr(Result, '<' + String(R.VarNames[Num]) + ' Value="' + EscapeText(S) + '">');
                If Assigned(Objects[F]) Then
                   begin
                     If TVarStruct(Objects[F]).Tags <> '' Then
                        begin
                          src := TXMLInputSource.Create(UTF8Encode(TVarStruct(Objects[F]).Tags));
                          parser := TDOMParser.Create;
                          parser.Parse(src, dom);
                          Try
                             AppendStr(Result, export_tags(False, dom.DocumentElement));
                          finally
                             dom.Free;
                             parser.Free;
                             src.Free
                          end;
                        end;
                     AppendStr(Result, TVarStruct(Objects[F]).ExportXML(R))
                   end;
                AppendStr(Result, '</' + String(R.VarNames[Num]) + '>' + #$0D#$0A);
             end
     end
  else
     begin
       For F := 0 To Count - 1 Do
         Begin
           If Assigned(Objects[F]) Then
              AppendStr(Result, TVarStruct(Objects[F]).ExportXML(R))
         End
     end
 end;

function TVarValue.FindNode(ID: Integer): TVarStruct;

Var F: Integer;
begin
 For F := 0 To Count - 1 Do
     If Assigned(Objects[F]) Then
        Begin
          Result := TVarStruct(Objects[F]).FindNode(ID);
          If Assigned(Result) Then Exit
        end;
 Result := Nil
end;

procedure TVarValue.out(const Shift: String);

Var F: Integer;
begin
  WriteLn(Shift, Num, ' : ');
  For F := 0 To Count - 1 Do
    Begin
      WriteLn(Shift, '  [', F, '] = ', Strings[F]);
      If Assigned(Objects[F]) Then
         TVarStruct(Objects[F]).Out(Shift + '    ')
    End
end;

procedure TVarValue.AssignBVal(var stp, enp: PRegExprChar);
begin
  if Length(baseVal) > 0 Then
     begin
       stp := @baseVal[1];
       enp := @baseVal[Length(baseVal) + 1]
     end
  else
    begin
      stp := Nil;
      enp := Nil
    end
end;

destructor TVarValue.Destroy;

Var F: Integer;
begin
  For F := 0 To Count - 1 Do
    Objects[F].Free;
  if Num >= 0 Then
     begin
       Ref.startp[Num] := Nil;
       Ref.endp[Num] := Nil;
     end;
  inherited Destroy
end;

function TRegExpr.ErrorMsg (AErrorID : integer) : RegExprString;
 begin
  case AErrorID of
    reeOk: Result := 'No errors';
    reeCompNullArgument: Result := 'TRegExpr(comp): Null Argument';
    reeCompRegexpTooBig: Result := 'TRegExpr(comp): Regexp Too Big';
    reeCompParseRegTooManyBrackets: Result := 'TRegExpr(comp): ParseReg Too Many ()';
    reeCompParseRegUnmatchedBrackets: Result := 'TRegExpr(comp): ParseReg Unmatched ()';
    reeCompParseRegUnmatchedBrackets2: Result := 'TRegExpr(comp): ParseReg Unmatched ()';
    reeCompParseRegJunkOnEnd: Result := 'TRegExpr(comp): ParseReg Junk On End';
    reePlusStarOperandCouldBeEmpty: Result := 'TRegExpr(comp): *+ Operand Could Be Empty';
    reeNestedSQP: Result := 'TRegExpr(comp): Nested *?+';
    reeBadHexDigit: Result := 'TRegExpr(comp): Bad Hex Digit';
    reeInvalidRange: Result := 'TRegExpr(comp): Invalid [] Range';
    reeParseAtomTrailingBackSlash: Result := 'TRegExpr(comp): Parse Atom Trailing \';
    reeNoHexCodeAfterBSlashX: Result := 'TRegExpr(comp): No Hex Code After \x';
    reeHexCodeAfterBSlashXTooBig: Result := 'TRegExpr(comp): Hex Code After \x Is Too Big';
    reeUnmatchedSqBrackets: Result := 'TRegExpr(comp): Unmatched []';
    reeInternalUrp: Result := 'TRegExpr(comp): Internal Urp';
    reeQPSBFollowsNothing: Result := 'TRegExpr(comp): ?+*{ Follows Nothing';
    reeTrailingBackSlash: Result := 'TRegExpr(comp): Trailing \';
    reeRarseAtomInternalDisaster: Result := 'TRegExpr(comp): RarseAtom Internal Disaster';
    reeBRACESArgTooBig: Result := 'TRegExpr(comp): BRACES Argument Too Big';
    reeBracesMinParamGreaterMax: Result := 'TRegExpr(comp): BRACE Min Param Greater then Max';
    reeUnclosedComment: Result := 'TRegExpr(comp): Unclosed (?#Comment)';
    reeComplexBracesNotImplemented: Result := 'TRegExpr(comp): If you want take part in beta-testing BRACES ''{min,max}'' and non-greedy ops ''*?'', ''+?'', ''??'' for complex cases - remove ''.'' from {.$DEFINE ComplexBraces}';
    reeUrecognizedModifier: Result := 'TRegExpr(comp): Urecognized Modifier';
    reeBadLinePairedSeparator: Result := 'TRegExpr(comp): LinePairedSeparator must countain two different chars or no chars at all';

    reeRegRepeatCalledInappropriately: Result := 'TRegExpr(exec): RegRepeat Called Inappropriately';
    reeMatchPrimMemoryCorruption: Result := 'TRegExpr(exec): MatchPrim Memory Corruption';
    reeMatchPrimCorruptedPointers: Result := 'TRegExpr(exec): MatchPrim Corrupted Pointers';
    reeNoExpression: Result := 'TRegExpr(exec): Not Assigned Expression Property';
    reeCorruptedProgram: Result := 'TRegExpr(exec): Corrupted Program';
    reeNoInputStringSpecified: Result := 'TRegExpr(exec): No Input String Specified';
    reeOffsetMustBeGreaterThen0: Result := 'TRegExpr(exec): Offset Must Be Greater Then 0';
    reeExecNextWithoutExec: Result := 'TRegExpr(exec): ExecNext Without Exec[Pos]';
    reeGetInputStringWithoutInputString: Result := 'TRegExpr(exec): GetInputString Without InputString';
    reeDumpCorruptedOpcode: Result := 'TRegExpr(dump): Corrupted Opcode';
    reeLoopStackExceeded: Result := 'TRegExpr(exec): Loop Stack Exceeded';
    reeLoopWithoutEntry: Result := 'TRegExpr(exec): Loop Without LoopEntry !';

    reeBadDirective: Result := 'TRegExpr(comp): Unknown directive or there is no right bracket in the directive';
    reeBadPCodeImported: Result := 'TRegExpr(misc): Bad p-code imported';
    reeInvalidPredicate: Result := 'TRegExpr(comp): Invalid Predicate';
    else Result := 'Unknown error';
   end;
 end; { of procedure TRegExpr.Error
--------------------------------------------------------------}

function TRegExpr.LastError : integer;
 begin
  Result := fLastError;
  fLastError := reeOk;
 end; { of function TRegExpr.LastError
--------------------------------------------------------------}


{=============================================================}
{===================== Common section ========================}
{=============================================================}

class function TRegExpr.VersionMajor : integer; //###0.944
 begin
  Result := TRegExprVersionMajor;
 end; { of class function TRegExpr.VersionMajor
--------------------------------------------------------------}

class function TRegExpr.VersionMinor : integer; //###0.944
 begin
  Result := TRegExprVersionMinor;
 end; { of class function TRegExpr.VersionMinor
--------------------------------------------------------------}

constructor TRegExpr.Create;
 begin
  inherited;

  DecimalSeparator := '.';

  Randomize;

  programm := nil;
  fExpression := nil;
  fInputString := nil;

  regexpbeg := nil;
  fExprIsCompiled := false;

  FillChar(varsp, SizeOf(varsp), 0);
  FillChar(valsp, SizeOf(valsp), 0);
  FillChar(fcalls, SizeOf(fcalls), 0);

  valext := TStringList.Create;

  storedWords := TStringList.Create;
  storedRels := TStringList.Create;

  nExecs := 0;

  db := Nil;

  ENV := Nil;

  InitCriticalSection(Trasher);

  trash := TList.Create;

  RootID := 0;

  ModifierI := RegExprModifierI;
  ModifierR := RegExprModifierR;
  ModifierS := RegExprModifierS;
  ModifierG := RegExprModifierG;
  ModifierM := RegExprModifierM; //###0.940

  SpaceChars := RegExprSpaceChars; //###0.927
  WordChars := RegExprWordChars; //###0.929
  fInvertCase := RegExprInvertCaseFunction; //###0.927

  fLineSeparators := RegExprLineSeparators; //###0.941
  LinePairedSeparator := RegExprLinePairedSeparator; //###0.941
 end; { of constructor TRegExpr.Create
--------------------------------------------------------------}

constructor TRegExpr.Create(AExpression: RegExprString);
begin
  create;
  Expression:=AExpression;
end;

destructor TRegExpr.Destroy;
 var i: Integer;
 begin
  for i := 0 to NSUBEXP - 1 do begin
      FreeAndNil(valsp[i]);
      FreeAndNil(fcalls[i]);
      FreeMem(varsp[i])
  end;
  if programm <> nil then
  begin
    FreeMem (programm);
    programm:=nil;
  end;
  if fExpression <> nil then
  begin
    FreeMem (fExpression);
    fExpression:=nil;
  end;
  if fInputString <> nil then
  begin
    FreeMem (fInputString);
    fInputString:=nil;
  end;
  valext.Free;

  storedWords.Free;
  storedRels.Free;

  if Assigned(db) Then
     begin
       db.Release;
       db := Nil
     end;

  With trash Do
    Begin
      for i := 0 to Count - 1 do
          if Assigned(Items[i]) then
             TObject(Items[i]).Free;
      Free
    end;
  DoneCriticalSection(Trasher)
 end; { of destructor TRegExpr.Destroy
--------------------------------------------------------------}

class function TRegExpr.InvertCaseFunction (const Ch : REChar) : REChar;
 begin
  {$IFDEF UniCode}
  if Ch >= #128
   then Result := Ch
  else
  {$ENDIF}
   begin
    Result := {$IFDEF FPC}AnsiUpperCase (Ch) [1]{$ELSE} {$IFDEF SYN_WIN32}REChar (CharUpper (PChar (Ch))){$ELSE}REChar (toupper (integer (Ch))){$ENDIF} {$ENDIF};
    if Result = Ch
     then Result := {$IFDEF FPC}AnsiLowerCase (Ch) [1]{$ELSE} {$IFDEF SYN_WIN32}REChar (CharLower (PChar (Ch))){$ELSE}REChar(tolower (integer (Ch))){$ENDIF} {$ENDIF};
   end;
 end; { of function TRegExpr.InvertCaseFunction
--------------------------------------------------------------}

function TRegExpr.GetExpression : RegExprString;
 begin
  if fExpression <> nil
   then Result := fExpression
   else Result := '';
 end; { of function TRegExpr.GetExpression
--------------------------------------------------------------}

procedure TRegExpr.SetExpression (const s : RegExprString);
 var
  Len : PtrInt; //###0.950
 begin
  if (s <> fExpression) or not fExprIsCompiled then begin
    fExprIsCompiled := false;
    if fExpression <> nil then begin
      FreeMem (fExpression);
      fExpression := nil;
     end;
    if s <> '' then begin
      Len := length (s); //###0.950
      GetMem (fExpression, (Len + 1) * SizeOf (REChar));
      System.Move(s[1],fExpression^,(Len + 1) * SizeOf (REChar));

      InvalidateProgramm; //###0.941
     end;
   end;
 end; { of procedure TRegExpr.SetExpression
--------------------------------------------------------------}

function TRegExpr.GetSubExprMatchCount : integer;
 begin
  if Assigned (fInputString) then begin
     Result := NSUBEXP - 1;
     while (Result > 0) and ((startp [Result] = nil)
                             or (endp [Result] = nil))
      do dec (Result);
    end
   else Result := -1;
 end; { of function TRegExpr.GetSubExprMatchCount
--------------------------------------------------------------}

function TRegExpr.GetMatchPos (Idx : integer) : PtrInt;
 begin
  if (Idx >= 0) and (Idx < NSUBEXP) and Assigned (fInputString)
     and Assigned (startp [Idx]) and Assigned (endp [Idx]) then begin
     Result := (startp [Idx] - fInputString) + 1;
    end
   else Result := -1;
 end; { of function TRegExpr.GetMatchPos
--------------------------------------------------------------}

function TRegExpr.GetMatchLen (Idx : integer) : PtrInt;
 begin
  if (Idx >= 0) and (Idx < NSUBEXP) and Assigned (fInputString)
     and Assigned (startp [Idx]) and Assigned (endp [Idx]) then begin
     Result := endp [Idx] - startp [Idx];
    end
   else Result := -1;
 end; { of function TRegExpr.GetMatchLen
--------------------------------------------------------------}

function TRegExpr.GetMatch (Idx : integer) : RegExprString;
 begin
  if (Idx >= 0) and (Idx < NSUBEXP) and Assigned (fInputString)
     and Assigned (startp [Idx]) and Assigned (endp [Idx])
     and (endp [Idx] > startp[Idx])
   //then Result := copy (fInputString, MatchPos [Idx], MatchLen [Idx]) //###0.929
   then begin
     //SetString (Result, startp [idx], endp [idx] - startp [idx])
     SetLength(Result,endp [idx] - startp [idx]);
     System.Move(startp [idx]^,Result[1],length(Result)*sizeof(REChar));
   end
   else Result := '';
 end; { of function TRegExpr.GetMatch
--------------------------------------------------------------}

function TRegExpr.GetModifierStr : RegExprString;
 begin
  Result := '-';

  if ModifierI
   then Result := 'i' + Result
   else Result := Result + 'i';
  if ModifierR
   then Result := 'r' + Result
   else Result := Result + 'r';
  if ModifierS
   then Result := 's' + Result
   else Result := Result + 's';
  if ModifierG
   then Result := 'g' + Result
   else Result := Result + 'g';
  if ModifierM
   then Result := 'm' + Result
   else Result := Result + 'm';
  if ModifierX
   then Result := 'x' + Result
   else Result := Result + 'x';

  if Result [length (Result)] = '-' // remove '-' if all modifiers are 'On'
   then System.Delete (Result, length (Result), 1);
 end; { of function TRegExpr.GetModifierStr
--------------------------------------------------------------}

class function TRegExpr.ParseModifiersStr (const AModifiers : RegExprString;
var AModifiersInt : integer) : boolean;
// !!! Be carefull - this is class function and must not use object instance fields
 var
  i : integer;
  IsOn : boolean;
  Mask : integer;
 begin
  Result := true;
  IsOn := true;
  Mask := 0; // prevent compiler warning
  for i := 1 to length (AModifiers) do
   if AModifiers [i] = '-'
    then IsOn := false
    else begin
      if Pos (AModifiers [i], 'iI') > 0
       then Mask := MaskModI
      else if Pos (AModifiers [i], 'rR') > 0
       then Mask := MaskModR
      else if Pos (AModifiers [i], 'sS') > 0
       then Mask := MaskModS
      else if Pos (AModifiers [i], 'gG') > 0
       then Mask := MaskModG
      else if Pos (AModifiers [i], 'mM') > 0
       then Mask := MaskModM
      else if Pos (AModifiers [i], 'xX') > 0
       then Mask := MaskModX
      else begin
        Result := false;
        EXIT;
       end;
      if IsOn
       then AModifiersInt := AModifiersInt or Mask
       else AModifiersInt := AModifiersInt and not Mask;
     end;
 end; { of function TRegExpr.ParseModifiersStr
--------------------------------------------------------------}

procedure TRegExpr.SetModifierStr (const AModifiers : RegExprString);
 begin
  if not ParseModifiersStr (AModifiers, fModifiers)
   then Error (reeModifierUnsupported);
 end; { of procedure TRegExpr.SetModifierStr
--------------------------------------------------------------}

function TRegExpr.GetModifier (AIndex : integer) : boolean;
 var
  Mask : integer;
 begin
  Result := false;
  case AIndex of
    1: Mask := MaskModI;
    2: Mask := MaskModR;
    3: Mask := MaskModS;
    4: Mask := MaskModG;
    5: Mask := MaskModM;
    6: Mask := MaskModX;
    else begin
      Error (reeModifierUnsupported);
      EXIT;
     end;
   end;
  Result := (fModifiers and Mask) <> 0;
 end; { of function TRegExpr.GetModifier
--------------------------------------------------------------}

procedure TRegExpr.SetModifier (AIndex : integer; ASet : boolean);
 var
  Mask : integer;
 begin
  case AIndex of
    1: Mask := MaskModI;
    2: Mask := MaskModR;
    3: Mask := MaskModS;
    4: Mask := MaskModG;
    5: Mask := MaskModM;
    6: Mask := MaskModX;
    else begin
      Error (reeModifierUnsupported);
      EXIT;
     end;
   end;
  if ASet
   then fModifiers := fModifiers or Mask
   else fModifiers := fModifiers and not Mask;
 end; { of procedure TRegExpr.SetModifier
--------------------------------------------------------------}


{=============================================================}
{==================== Compiler section =======================}
{=============================================================}

procedure TRegExpr.InvalidateProgramm;
 begin
  if programm <> nil then begin
    FreeMem (programm);
    programm := nil;
   end;
 end; { of procedure TRegExpr.InvalidateProgramm
--------------------------------------------------------------}

procedure TRegExpr.AddTrash(p: TObject);
begin
  trash.Add(p)
end;

function TRegExpr.GetVarName(Idx : integer): PRegExprChar;
begin
  Result := varsp[Idx];
  If Assigned(Result) And (Result^ = '&') Then
     Begin
       Inc(Result);
       While Result^ <> #0 Do
         Inc(Result);
       Inc(Result)
     end
end;

function TRegExpr.GetVarValue(Idx : integer): TVarValue;
begin
  Result := valsp[Idx]
end;

procedure TRegExpr.SetDB(base: TFastDB);
begin
  if Assigned(db) Then db.Release;
  db := base;
  db.Use
end;

procedure TRegExpr.SetENV(_ENV: TXPathEnvironment);
begin
  ENV := _ENV
end;

procedure TRegExpr.StartTransaction;
begin
  If Assigned(db) Then
     db.StartTransaction;
  If Assigned(ENV) Then
     begin
       storedWords.Assign(ENV.CollectedWords);
       storedRels.Assign(ENV.CollectedRels)
     end;
end;

procedure TRegExpr.Commit;
begin
  If Assigned(db) Then
     db.Commit
end;

procedure TRegExpr.RollBack;
begin
  If Assigned(db) Then
     db.RollBack;
  If Assigned(ENV) Then
     begin
       ENV.CollectedWords.Assign(storedWords);
       ENV.CollectedRels.Assign(storedRels)
     end;
end;

procedure TRegExpr.Compile; //###0.941
 begin
  if fExpression = nil then begin // No Expression assigned
    Error (reeNoExpression);
    EXIT;
   end;
  CompileRegExpr (fExpression);
 end; { of procedure TRegExpr.Compile
--------------------------------------------------------------}

function TRegExpr.IsProgrammOk : boolean;
 {$IFNDEF UniCode}
 var
  i : integer;
 {$ENDIF}
 begin
  Result := false;

  // check modifiers
  if fModifiers <> fProgModifiers //###0.941
   then InvalidateProgramm;

  // can we optimize line separators by using sets?
  {$IFNDEF UniCode}
  fLineSeparatorsSet := [];
  for i := 1 to length (fLineSeparators)
   do System.Include (fLineSeparatorsSet, fLineSeparators [i]);
  {$ENDIF}

  // [Re]compile if needed
  if programm = nil
   then Compile; //###0.941

  // check [re]compiled programm
  if programm = nil
   then EXIT // error was set/raised by Compile (was reeExecAfterCompErr)
  else if programm [0] <> MAGIC // Program corrupted.
   then Error (reeCorruptedProgram)
  else Result := true;
 end; { of function TRegExpr.IsProgrammOk
--------------------------------------------------------------}

procedure TRegExpr.Tail (p : PRegExprChar; val : PRegExprChar);
// set the next-pointer at the end of a node chain
 var
  scan : PRegExprChar;
  temp : PRegExprChar;
//  i : int64;
 begin
  if p = @regdummy
   then EXIT;
  // Find last node.
  scan := p;
  REPEAT
   temp := regnext (scan);
   if temp = nil
    then BREAK;
   scan := temp;
  UNTIL false;
  // Set Next 'pointer'
  if val < scan
   then PRENextOff (AlignToPtr(scan + REOpSz))^ := - (scan - val) //###0.948
   // work around PWideChar subtraction bug (Delphi uses
   // shr after subtraction to calculate widechar distance %-( )
   // so, if difference is negative we have .. the "feature" :(
   // I could wrap it in $IFDEF UniCode, but I didn't because
   // "P – Q computes the difference between the address given
   // by P (the higher address) and the address given by Q (the
   // lower address)" - Delphi help quotation.
   else PRENextOff (AlignToPtr(scan + REOpSz))^ := val - scan; //###0.933
 end; { of procedure TRegExpr.Tail
--------------------------------------------------------------}

procedure TRegExpr.OpTail (p : PRegExprChar; val : PRegExprChar);
// regtail on operand of first argument; nop if operandless
 begin
  // "Operandless" and "op != BRANCH" are synonymous in practice.
  if (p = nil) or (p = @regdummy) or (PREOp (p)^ <> BRANCH)
   then EXIT;
  Tail (p + REOpSz + RENextOffSz, val); //###0.933
 end; { of procedure TRegExpr.OpTail
--------------------------------------------------------------}

function TRegExpr.EmitNode (op : TREOp) : PRegExprChar; //###0.933
// emit a node, return location
 begin
  Result := regcode;
  if Result <> @regdummy then begin
     PREOp (regcode)^ := op;
     inc (regcode, REOpSz);
     PRENextOff (AlignToPtr(regcode))^ := 0; // Next "pointer" := nil
     inc (regcode, RENextOffSz);
     {$IFDEF DebugSynRegExpr}
     if regcode-programm>regsize then
       raise Exception.Create('TRegExpr.EmitNode buffer overrun');
     {$ENDIF}
    end
   else inc (regsize, REOpSz + RENextOffSz); // compute code size without code generation
 end; { of function TRegExpr.EmitNode
--------------------------------------------------------------}

procedure TRegExpr.EmitC (b : REChar);
// emit a byte to code
 begin
  if regcode <> @regdummy then begin
     regcode^ := b;
     inc (regcode);
     {$IFDEF DebugSynRegExpr}
     if regcode-programm>regsize then
       raise Exception.Create('TRegExpr.EmitC buffer overrun');
     {$ENDIF}
    end
   else inc (regsize, REOpSz); // Type of p-code pointer always is ^REChar
 end; { of procedure TRegExpr.EmitC
--------------------------------------------------------------}

procedure TRegExpr.InsertOperator (op : TREOp; opnd : PRegExprChar; sz : integer);
// insert an operator in front of already-emitted operand
// Means relocating the operand.
 var
  src, dst, place : PRegExprChar;
  i : integer;
 begin
  if regcode = @regdummy then begin
    inc (regsize, sz);
    EXIT;
   end;
  // move code behind insert position
  src := regcode;
  inc (regcode, sz);
  {$IFDEF DebugSynRegExpr}
  if regcode-programm>regsize then
    raise Exception.Create('TRegExpr.InsertOperator buffer overrun');
//  if (opnd<regcode) or (opnd-regcode>regsize) then
 //   raise Exception.Create('TRegExpr.InsertOperator invalid opnd');
  {$ENDIF}
  dst := regcode;
  while src > opnd do begin
    dec (dst);
    dec (src);
    dst^ := src^;
   end;
  place := opnd; // Op node, where operand used to be.
  PREOp (place)^ := op;
  inc (place, REOpSz);
  for i := 1 + REOpSz to sz do begin
    place^ := #0;
    inc (place);
   end;
 end; { of procedure TRegExpr.InsertOperator
--------------------------------------------------------------}

function strcspn (s1 : PRegExprChar; s2 : PRegExprChar) : PtrInt;
// find length of initial segment of s1 consisting
// entirely of characters not from s2
 var scan1, scan2 : PRegExprChar;
 begin
  Result := 0;
  scan1 := s1;
  while scan1^ <> #0 do begin
    scan2 := s2;
    while scan2^ <> #0 do
     if scan1^ = scan2^
      then EXIT
      else inc (scan2);
    inc (Result);
    inc (scan1)
   end;
 end; { of function strcspn
--------------------------------------------------------------}

const
// Flags to be passed up and down.
 HASWIDTH =   01; // Known never to match nil string.
 SIMPLE   =   02; // Simple enough to be STAR/PLUS/BRACES operand.
 SPSTART  =   04; // Starts with * or +.
 WORST    =   0;  // Worst case.
 META : array [0 .. 12] of REChar = (
  '^', '$', '.', '[', '(', ')', '|', '?', '+', '*', EscChar, '{', #0);
 // Any modification must be synchronized with QuoteRegExprMetaChars !!!

{$IFDEF UniCode}
 RusRangeLo : array [0 .. 33] of REChar =
  (#$430,#$431,#$432,#$433,#$434,#$435,#$451,#$436,#$437,
   #$438,#$439,#$43A,#$43B,#$43C,#$43D,#$43E,#$43F,
   #$440,#$441,#$442,#$443,#$444,#$445,#$446,#$447,
   #$448,#$449,#$44A,#$44B,#$44C,#$44D,#$44E,#$44F,#0);
 RusRangeHi : array [0 .. 33] of REChar =
  (#$410,#$411,#$412,#$413,#$414,#$415,#$401,#$416,#$417,
   #$418,#$419,#$41A,#$41B,#$41C,#$41D,#$41E,#$41F,
   #$420,#$421,#$422,#$423,#$424,#$425,#$426,#$427,
   #$428,#$429,#$42A,#$42B,#$42C,#$42D,#$42E,#$42F,#0);
 RusRangeLoLow = #$430{'а'};
 RusRangeLoHigh = #$44F{'я'};
 RusRangeHiLow = #$410{'А'};
 RusRangeHiHigh = #$42F{'Я'};
{$ELSE}
 RusRangeLo = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя';
 RusRangeHi = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ';
 RusRangeLoLow = 'а';
 RusRangeLoHigh = 'я';
 RusRangeHiLow = 'А';
 RusRangeHiHigh = 'Я';
{$ENDIF}

function TRegExpr.CompileRegExpr (exp : PRegExprChar) : boolean;
// Compile a regular expression into internal code
// We can't allocate space until we know how big the compiled form will be,
// but we can't compile it (and thus know how big it is) until we've got a
// place to put the code. So we cheat: we compile it twice, once with code
// generation turned off and size counting turned on, and once "for real".
// This also means that we don't allocate space until we are sure that the
// thing really will compile successfully, and we never have to move the
// code and thus invalidate pointers into it. (Note that it has to be in
// one piece because free() must be able to free it all.)
// Beware that the optimization-preparation code in here knows about some
// of the structure of the compiled regexp.
 var
  scan, longest : PRegExprChar;
  len : PtrUInt;
  flags : integer;
 begin
  Result := false; // life too dark

  regparse := nil; // for correct error handling
  regexpbeg := exp;
  try

  if programm <> nil then begin
    FreeMem (programm);
    programm := nil;
   end;

  if exp = nil then begin
    Error (reeCompNullArgument);
    EXIT;
   end;

  fProgModifiers := fModifiers;
  // well, may it's paranoia. I'll check it later... !!!!!!!!

  // First pass: determine size, legality.
  fCompModifiers := fModifiers;
  regparse := exp;
  regnpar := 1;
  regsize := 0;
  regcode := @regdummy;
  EmitC (MAGIC);
  if ParseReg (0, flags) = nil
   then EXIT;

  // Allocate space.
  GetMem (programm, regsize * SizeOf (REChar));

  // Second pass: emit code.
  fCompModifiers := fModifiers;
  regparse := exp;
  regnpar := 1;
  regcode := programm;
  EmitC (MAGIC);
  if ParseReg (0, flags) = nil
   then EXIT;

  // Dig out information for optimizations.
  {$IFDEF UseFirstCharSet} //###0.929
  FirstCharSet := [];
  FillFirstCharSet (programm + REOpSz);
  {$ENDIF}
  regstart := #0; // Worst-case defaults.
  reganch := #0;
  regmust := nil;
  regmlen := 0;
  scan := programm + REOpSz; // First BRANCH.
  if PREOp (regnext (scan))^ = EEND then begin // Only one top-level choice.
    scan := scan + REOpSz + RENextOffSz;

    // Starting-point info.
    if PREOp (scan)^ = EXACTLY
     then regstart := (scan + REOpSz + RENextOffSz)^
     else if PREOp (scan)^ = BOL
           then inc (reganch);

    // If there's something expensive in the r.e., find the longest
    // literal string that must appear and make it the regmust. Resolve
    // ties in favor of later strings, since the regstart check works
    // with the beginning of the r.e. and avoiding duplication
    // strengthens checking. Not a strong reason, but sufficient in the
    // absence of others.
    if (flags and SPSTART) <> 0 then begin
        longest := nil;
        len := 0;
        while scan <> nil do begin
          if (PREOp (scan)^ = EXACTLY)
             and (strlen (scan + REOpSz + RENextOffSz) >= PtrInt(len)) then begin
              longest := scan + REOpSz + RENextOffSz;
              len := strlen (longest);
           end;
          scan := regnext (scan);
         end;
        regmust := longest;
        regmlen := len;
     end;
   end;

  Result := true;

  finally begin
    if not Result
     then InvalidateProgramm;
    regexpbeg := nil;
    fExprIsCompiled := Result; //###0.944
   end;
  end;

 end; { of function TRegExpr.CompileRegExpr
--------------------------------------------------------------}

function TRegExpr.ParseReg (paren : integer; var flagp : integer) : PRegExprChar;
// regular expression, i.e. main body or parenthesized thing
// Caller must absorb opening parenthesis.
// Combining parenthesis handling with the base level of regular expression
// is a trifle forced, but the need to tie the tails of the branches to what
// follows makes it hard to avoid.
 var
  ret, br, ender : PRegExprChar;
  parno : integer;
  flags : integer;
  SavedModifiers : integer;
  beg: PRegExprChar;
  point: PRegExprChar;
  eq, neq: boolean;
  pred: ReChar;
  pcall: TFastCall;
  pmaincalls: TFastCalls;
  pcalls: TList;
  dollarsign: Boolean;
  L: TAnalyser;
  i, j, refno : integer;
  ST, STP, SAP: RegExprString;
  S: PRegExprChar;
  bal, maxbal: Integer;
 begin
  Result := nil;
  flagp := HASWIDTH; // Tentatively.
  parno := 0; // eliminate compiler stupid warning
  SavedModifiers := fCompModifiers;

  // Make an OPEN node, if parenthesized.
  if paren <> 0 then begin
      if regnpar >= NSUBEXP then begin
        Error (reeCompParseRegTooManyBrackets);
        EXIT;
       end;
      parno := regnpar;
      inc (regnpar);
      ret := EmitNode (TREOp (ord (OPEN) + parno));
    end
   else ret := nil;

  // Pick up the branches, linking them together.
  br := ParseBranch (flags);
  if br = nil then begin
    Result := nil;
    EXIT;
   end;
  if ret <> nil
   then Tail (ret, br) // OPEN -> first.
   else ret := br;
  if (flags and HASWIDTH) = 0
   then flagp := flagp and not HASWIDTH;
  flagp := flagp or flags and SPSTART;
  while (regparse^ = '|') do begin
    inc (regparse);
    br := ParseBranch (flags);
    if br = nil then begin
       Result := nil;
       EXIT;
      end;
    Tail (ret, br); // BRANCH -> BRANCH.
    if (flags and HASWIDTH) = 0
     then flagp := flagp and not HASWIDTH;
    flagp := flagp or flags and SPSTART;
   end;

  // Make a closing node, and hook it on the end.
  if paren <> 0
   then ender := EmitNode (TREOp (ord (CLOSE) + parno))
   else ender := EmitNode (EEND);
  Tail (ret, ender);

  // Hook the tails of the branches to the closing node.
  br := ret;
  while br <> nil do begin
    OpTail (br, ender);
    br := regnext (br);
   end;

  // Check for proper termination.
  if paren <> 0 then
   if regparse^ <> ')' then begin
      Error (reeCompParseRegUnmatchedBrackets);
      EXIT;
     end
    else
     begin
       inc (regparse); // skip trailing ')'
       eq := false;
       neq := false;
       pred := #0;
       if (regparse^ = '=') And ((regparse+1)^ = '=') And ((regparse+2)^ = '>') And ((regparse+3)^ = '{') then
          eq := true
       else if (regparse^ = '!') And ((regparse+1)^ = '=') And ((regparse+2)^ = '>') And ((regparse+3)^ = '{') then
          neq := true
       else if (regparse^ in ['?', '+', '*', '-']) And ((regparse+1)^ = '=') And ((regparse+2)^ = '>') And ((regparse+3)^ = '{') then
          pred := regparse^;
       if eq Or neq Or (pred <> #0) Or ((regparse^ = '-') And ((regparse+1)^ = '>') And ((regparse+2)^ = '{')) Then
           begin
             Inc(regparse, 3);
             if eq Or neq Or (pred <> #0) then
                Inc(regparse);
             While (regparse^ <> #0) And (regparse^ = ' ') Do
                Inc(regparse);
             beg := regparse;
             bal := 1;
             maxbal := 1;
             While (regparse^ <> #0) And (bal > 0) Do
                begin
                  If regparse^ = '{' Then
                     Begin
                       Inc(bal);
                       If bal > maxbal Then
                          maxbal := bal;
                       Inc(regparse)
                     End
                  Else If regparse^ = '}' Then
                     Begin
                       Dec(bal);
                       If bal > 0 Then
                          Inc(regparse)
                     End
                  Else If regparse^ = '''' Then
                     begin
                       Inc(regparse);
                       While (regparse^ <> #0) And (regparse^ <> '''') Do
                          Inc(regparse);
                       If regparse^ = '''' Then Inc(regparse)
                     end
                  Else If regparse^ = '"' Then
                     begin
                       Inc(regparse);
                       While (regparse^ <> #0) And (regparse^ <> '"') Do
                          Inc(regparse);
                       If regparse^ = '"' Then Inc(regparse)
                     end
                  Else
                     Inc(regparse);
                end;
             if regparse^ <> #0 Then
                begin
                  If (maxbal = 2) And Not (eq Or neq Or (pred <> #0)) Then
                     Begin
                       GetMem(S, (regparse - beg + 2)*SizeOf(REChar));
                       varsp[parno] := S;
                       S^ := '&';
                       Inc(S)
                     End
                  Else
                     Begin
                       GetMem(S, (regparse - beg + 1)*SizeOf(REChar));
                       varsp[parno] := S
                     End;
                  Move(beg^, S^, (regparse - beg)*SizeOf(REChar));
                  If (maxbal = 2) And Not (eq Or neq Or (pred <> #0)) Then
                     Begin
                       While S^ <> '{' Do
                         Inc(S);
                       S^ := #0;
                       Inc(S);
                       While S^ <> '}' Do
                         Inc(S)
                     End
                  Else
                     Inc(S, regparse - beg);
                  S^ := #0;
                  While (regparse^ <> #0) And (regparse^ <> '}') Do
                     Inc(regparse);
                  If regparse^ <> #0 Then Inc(regparse);
                  if pred <> #0 Then
                     begin
                       pcalls := TList.Create;
                       pmaincalls := TFastCalls.Create;
                       pcalls.Add(pmaincalls);

                       L := TAnalyser.Create(IdentSet + [Lexique.Point], [Space, Tabulation]);
                       L.AnlzLine := RegExprString(VarNames[parno]);

                       If L.Empty Then
                          L.MakeError('Predicate expected : ' + RegExprString(VarNames[parno]));

                       While Not (L.Error Or L.Empty) Do
                         begin
                           If L.IsNext(LeftBracket) Then
                              begin
                                L.Check(LeftBracket);
                                If pred <> '?' Then
                                   Begin
                                     L.MakeError('Only ?=> predicates can contain groups (p1,p2,p3...) : ' + RegExprString(VarNames[parno]));
                                     Break
                                   End;
                                TFastCalls(pcalls[pcalls.Count - 1]).Add(TFastCalls.Create);
                                pcalls.Add(pcalls[pcalls.Count - 1]);
                                Continue
                              end
                           Else If L.IsNext(RightBracket) Then
                              begin
                                L.Check(RightBracket);
                                If pred <> '?' Then
                                   Begin
                                     L.MakeError('Only ?=> predicates can contain groups (p1,p2,p3...) : ' + RegExprString(VarNames[parno]));
                                     Break
                                   End;
                                If pcalls.Count < 2 Then
                                   Begin
                                     L.MakeError('Right bracket without Left bracket. Disbalance : ' + RegExprString(VarNames[parno]));
                                     Break
                                   End;
                                pcalls.Delete(pcalls.Count - 1);
                                If (L.IsNext(Comma) And L.Check(Comma)) Or (L.IsNext(SemiColon) And L.Check(SemiColon)) Then
                                   If L.Empty Then
                                      L.MakeError('Predicate expected : ' + RegExprString(VarNames[parno]));
                                Continue
                              end;
                           pcall := TFastCall.Create;
                           pcall.Negate := L.IsNext(Exclamation) And L.Check(Exclamation);
                           If pcall.Negate And (pred <> '?') Then
                              Begin
                                L.MakeError('Only ?=> predicates can be inverted (!) : ' + RegExprString(VarNames[parno]));
                                Break
                              End;
                           pcall.Predicate := L.GetIdent(False);
                           if L.IsNext(LeftBracket) Then
                              begin
                                L.Check(LeftBracket);
                                While Not (L.Error Or L.Empty Or L.IsNext(RightBracket)) Do
                                  begin
                                    SetLength(pcall.Descriptor, Length(pcall.Descriptor) + 1);
                                    pcall.Descriptor[High(pcall.Descriptor)].Logged := False;
                                    SetLength(pcall.References, Length(pcall.References) + 1);
                                    If (pred <> '+') And L.IsNext(Underscore) Then
                                       begin
                                         L.Check(Underscore);
                                         pcall.Descriptor[High(pcall.Descriptor)].Kind := fpAny;
                                         pcall.References[High(pcall.References)] := -1;
                                       end
                                    Else
                                       begin
                                         dollarsign := L.IsNext(Dollar);
                                         if dollarsign then L.Check(Dollar);
                                         if L.IsNextSet([Comma, SemiColon, RightBracket]) Then
                                            if dollarsign then
                                               begin
                                                 pcall.Descriptor[High(pcall.Descriptor)].Kind := fpBound;
                                                 pcall.Descriptor[High(pcall.Descriptor)].Logged := True;
                                                 pcall.References[High(pcall.References)] := parno;
                                               end
                                            else
                                               L.MakeError('Variable/const/_ expected : ' + RegExprString(VarNames[parno]))
                                         Else
                                           begin
                                             if ((pred in ['+', '-']) Or ((pred = '?') And pcall.Negate)) And dollarsign then
                                                begin
                                                  L.MakeError('Assert/Retract/!Predicate can not contain $refs : ' + RegExprString(VarNames[parno]));
                                                  Break;
                                                end;
                                             ST := L.FindIdent(False);
                                             If Length(ST) > 0 Then
                                                begin
                                                  L.CheckIdent(ST, False);

                                                  if (dollarsign) then
                                                     pcall.Descriptor[High(pcall.Descriptor)].Kind := fpFree
                                                  else
                                                     pcall.Descriptor[High(pcall.Descriptor)].Kind := fpBound;

                                                  refno := -1;
                                                  for i := 0 to NSUBEXP - 1 do
                                                      if (i <> parno) And Assigned(varsp[i]) And (RegExprString(VarNames[i]) = ST) then
                                                         begin
                                                            refno := i;
                                                            break
                                                         end;
                                                  j := Pos('.', ST);
                                                  if (refno < 0) and (j > 0) and not ((pred = '?') and dollarsign) then
                                                     begin
                                                       STP := Copy(ST, 1, j - 1);
                                                       SAP := Copy(ST, j + 1, 2048);
                                                       With valext Do
                                                         for i := 0 to Count - 1 do
                                                           if Strings[i] = STP then
                                                              begin
                                                                for j := 0 to NSUBEXP - 1 do
                                                                  if Assigned(TRegExpr(Objects[i]).VarNames[j]) and (SAP = RegExprString(TRegExpr(Objects[i]).VarNames[j])) then
                                                                     begin
                                                                       refno := 1000*(i + 1) + j;
                                                                       break
                                                                     end;
                                                                if refno >= 0 then
                                                                   break
                                                              end
                                                     end;
                                                  if (refno >= 0) then
                                                     pcall.References[High(pcall.References)] := refno
                                                  else if dollarsign then
                                                     L.MakeError('Unknown variable $' + ST + ' : ' + RegExprString(VarNames[parno]))
                                                  else
                                                     L.MakeError('Unknown variable ' + ST + ' : ' + RegExprString(VarNames[parno]))
                                                end
                                             else if (dollarsign) then
                                                L.MakeError('Variable expected after $ : ' + RegExprString(VarNames[parno]))
                                             else // const
                                                begin
                                                  pcall.Descriptor[High(pcall.Descriptor)].Kind := fpBound;
                                                  ST := L.GetBalancedListItem(False, [Comma, SemiColon, RightBracket]);
                                                  if Length(ST) >= 2 Then
                                                     If ((ST[1] = '''') And (ST[Length(ST)] = '''')) Or ((ST[1] = '"') And (ST[Length(ST)] = '"')) Then
                                                        ST := Copy(ST, 2, Length(ST)-2);
                                                  pcall.Descriptor[High(pcall.Descriptor)].Value := ST;
                                                  pcall.References[High(pcall.References)] := -1
                                                end
                                           end
                                       end;
                                    If Not L.Error Then
                                       If L.IsNext(Comma) And L.Check(Comma) Then
                                          Begin
                                            If L.Empty Then
                                               L.MakeError('Variable/const/_ expected : ' + RegExprString(VarNames[parno]))
                                          End
                                  end;
                                L.Check(RightBracket)
                              end;
                           if Not L.Error Then
                              begin
                                TFastCalls(pcalls[pcalls.Count - 1]).Add(pcall);
                                If L.IsNext(Comma) And L.Check(Comma) Then
                                   Begin
                                     If L.Empty Then
                                        L.MakeError('Predicate expected : ' + RegExprString(VarNames[parno]))
                                   End
                                Else If L.IsNext(SemiColon) And L.Check(SemiColon) Then
                                   Begin
                                     If L.Empty Then
                                        L.MakeError('Predicate expected : ' + RegExprString(VarNames[parno]))
                                     Else
                                        Begin
                                          TFastCalls(pcalls[pcalls.Count - 1]).Alternation := TFastCalls.Create;
                                          pcalls[pcalls.Count - 1] := TFastCalls(pcalls[pcalls.Count - 1]).Alternation
                                        End
                                   End
                              end
                         end;

                       If L.Error Or (pcalls.Count <> 1) Then
                          Begin
                            pcalls.Free;
                            L.Free;
                            Error(reeInvalidPredicate);
                            Exit
                          End;

                       L.Free;
                       pcalls.Free;

                       if Assigned(fcalls[parno]) then
                          FreeAndNil(fcalls[parno]);
                       fcalls[parno] := pmaincalls;
                       ST := hexStr(pmaincalls);
                       FreeMem(varsp[parno]);
                       GetMem(S, (Length(ST) + 2)*SizeOf(REChar));
                       varsp[parno] := S;
                       if pred = '+' then S^ := '!'
                       else if pred = '-' then S^ := '^'
                       else S^ := pred;
                       Inc(S);
                       Move(ST[1], S^, Length(ST)*SizeOf(REChar));
                       Inc(S, Length(ST));
                       S^ := #0;
                     end
                  else if eq Or neq then
                     begin
                       refno := -1;
                       for i := 0 to NSUBEXP - 1 do
                           if (i <> parno) And Assigned(varsp[i]) And (String(VarNames[i]) = String(VarNames[parno])) then
                              begin
                                 refno := i;
                                 break
                              end;
                       point := StrPos(VarNames[parno], '.');
                       if (refno < 0) and Assigned(point) then
                          begin
                            point^ := #0;
                            With valext Do
                              for i := 0 to Count - 1 do
                                if Strings[i] = VarNames[parno] then
                                   begin
                                     for j := 0 to NSUBEXP - 1 do
                                       if Assigned(TRegExpr(Objects[i]).VarNames[j]) and (String(point + 1) = String(TRegExpr(Objects[i]).VarNames[j])) then
                                          begin
                                            refno := 1000*(i + 1) + j;
                                            break
                                          end;
                                     if refno >= 0 then
                                        break
                                   end;
                            point^ := '.'
                          end;
                       if refno >= 0 then
                          begin
                            ST := IntToStr(refno);
                            FreeMem(varsp[parno]);
                            GetMem(S, (Length(ST) + 2)*SizeOf(REChar));
                            varsp[parno] := S;
                            if eq then
                               S^ := '+'
                            else
                               S^ := '-';
                            Inc(S);
                            Move(ST[1], S^, Length(ST)*SizeOf(REChar));
                            Inc(S, Length(ST));
                            S^ := #0
                          end
                     end
                end
           end
     end;
  if (paren = 0) and (regparse^ <> #0) then begin
      if regparse^ = ')'
       then Error (reeCompParseRegUnmatchedBrackets2)
       else Error (reeCompParseRegJunkOnEnd);
      EXIT;
    end;
  fCompModifiers := SavedModifiers; // restore modifiers of parent
  Result := ret;
 end; { of function TRegExpr.ParseReg
--------------------------------------------------------------}

function TRegExpr.ParseBranch (var flagp : integer) : PRegExprChar;
// one alternative of an | operator
// Implements the concatenation operator.
 var
  ret, chain, latest : PRegExprChar;
  flags : integer;
 begin
  flagp := WORST; // Tentatively.

  ret := EmitNode (BRANCH);
  chain := nil;
  while (regparse^ <> #0) and (regparse^ <> '|')
        and (regparse^ <> ')') do begin
    latest := ParsePiece (flags);
    if latest = nil then begin
      Result := nil;
      EXIT;
     end;
    flagp := flagp or flags and HASWIDTH;
    if chain = nil // First piece.
     then flagp := flagp or flags and SPSTART
     else Tail (chain, latest);
    chain := latest;
   end;
  if chain = nil // Loop ran zero times.
   then EmitNode (NOTHING);
  Result := ret;
 end; { of function TRegExpr.ParseBranch
--------------------------------------------------------------}

function TRegExpr.ParsePiece (var flagp : integer) : PRegExprChar;
// something followed by possible [*+?{]
// Note that the branching code sequences used for ? and the general cases
// of * and + and { are somewhat optimized:  they use the same NOTHING node as
// both the endmarker for their branch list and the body of the last branch.
// It might seem that this node could be dispensed with entirely, but the
// endmarker role is not redundant.
 function parsenum (AStart, AEnd : PRegExprChar) : TREBracesArg;
  begin
   Result := 0;
   if AEnd - AStart + 1 > 8 then begin // prevent stupid scanning
     Error (reeBRACESArgTooBig);
     EXIT;
    end;
   while AStart <= AEnd do begin
       Result := Result * 10 + (ord (AStart^) - ord ('0'));
       inc (AStart);
      end;
   if (Result > MaxBracesArg) or (Result < 0) then begin
     Error (reeBRACESArgTooBig);
     EXIT;
    end;
  end;

 var
  op : REChar;
  NonGreedyOp, NonGreedyCh : boolean; //###0.940
  TheOp : TREOp; //###0.940
  NextNode : PRegExprChar;
  flags : integer;
  BracesMin, Bracesmax : TREBracesArg;
  p, savedparse : PRegExprChar;

 procedure EmitComplexBraces (ABracesMin, ABracesMax : TREBracesArg;
   ANonGreedyOp : boolean); //###0.940
  {$IFDEF ComplexBraces}
  var
   off : TRENextOff;
  {$ENDIF}
   begin
   {$IFNDEF ComplexBraces}
   Error (reeComplexBracesNotImplemented);
   {$ELSE}
   if ANonGreedyOp
    then TheOp := LOOPNG
    else TheOp := LOOP;
   InsertOperator (LOOPENTRY, Result, REOpSz + RENextOffSz);
   NextNode := EmitNode (TheOp);
   if regcode <> @regdummy then begin
      off := (Result + REOpSz + RENextOffSz)
       - (regcode - REOpSz - RENextOffSz); // back to Atom after LOOPENTRY
      PREBracesArg (AlignToInt(regcode))^ := ABracesMin;
      inc (regcode, REBracesArgSz);
      PREBracesArg (AlignToInt(regcode))^ := ABracesMax;
      inc (regcode, REBracesArgSz);
      PRENextOff (AlignToPtr(regcode))^ := off;
      inc (regcode, RENextOffSz);
      {$IFDEF DebugSynRegExpr}
      if regcode-programm>regsize then
        raise Exception.Create('TRegExpr.ParsePiece.EmitComplexBraces buffer overrun');
      {$ENDIF}
     end
    else inc (regsize, REBracesArgSz * 2 + RENextOffSz);
   Tail (Result, NextNode); // LOOPENTRY -> LOOP
   if regcode <> @regdummy then
    Tail (Result + REOpSz + RENextOffSz, NextNode); // Atom -> LOOP
   {$ENDIF}
  end;

 procedure EmitSimpleBraces (ABracesMin, ABracesMax : TREBracesArg;
   ANonGreedyOp : boolean); //###0.940
  begin
   if ANonGreedyOp //###0.940
    then TheOp := BRACESNG
    else TheOp := BRACES;
   InsertOperator (TheOp, Result, REOpSz + RENextOffSz + REBracesArgSz * 2);
   if regcode <> @regdummy then begin
     PREBracesArg (AlignToInt(Result + REOpSz + RENextOffSz))^ := ABracesMin;
     PREBracesArg (AlignToInt(Result + REOpSz + RENextOffSz + REBracesArgSz))^ := ABracesMax;
    end;
  end;

 begin
  Result := ParseAtom (flags);
  if Result = nil
   then EXIT;

  op := regparse^;
  if not ((op = '*') or (op = '+') or (op = '?') or (op = '{')) then begin
    flagp := flags;
    EXIT;
   end;
  if ((flags and HASWIDTH) = 0) and (op <> '?') then begin
    Error (reePlusStarOperandCouldBeEmpty);
    EXIT;
   end;

  case op of
    '*': begin
      flagp := WORST or SPSTART;
      NonGreedyCh := (regparse + 1)^ = '?'; //###0.940
      NonGreedyOp := NonGreedyCh or ((fCompModifiers and MaskModG) = 0); //###0.940
      if (flags and SIMPLE) = 0 then begin
         if NonGreedyOp //###0.940
          then EmitComplexBraces (0, MaxBracesArg, NonGreedyOp)
          else begin // Emit x* as (x&|), where & means "self".
            InsertOperator (BRANCH, Result, REOpSz + RENextOffSz); // Either x
            OpTail (Result, EmitNode (BACK)); // and loop
            OpTail (Result, Result); // back
            Tail (Result, EmitNode (BRANCH)); // or
            Tail (Result, EmitNode (NOTHING)); // nil.
           end
        end
       else begin // Simple
         if NonGreedyOp //###0.940
          then TheOp := STARNG
          else TheOp := STAR;
         InsertOperator (TheOp, Result, REOpSz + RENextOffSz);
        end;
      if NonGreedyCh //###0.940
       then inc (regparse); // Skip extra char ('?')
     end; { of case '*'}
    '+': begin
      flagp := WORST or SPSTART or HASWIDTH;
      NonGreedyCh := (regparse + 1)^ = '?'; //###0.940
      NonGreedyOp := NonGreedyCh or ((fCompModifiers and MaskModG) = 0); //###0.940
      if (flags and SIMPLE) = 0 then begin
         if NonGreedyOp //###0.940
          then EmitComplexBraces (1, MaxBracesArg, NonGreedyOp)
          else begin // Emit x+ as x(&|), where & means "self".
            NextNode := EmitNode (BRANCH); // Either
            Tail (Result, NextNode);
            Tail (EmitNode (BACK), Result);    // loop back
            Tail (NextNode, EmitNode (BRANCH)); // or
            Tail (Result, EmitNode (NOTHING)); // nil.
           end
        end
       else begin // Simple
         if NonGreedyOp //###0.940
          then TheOp := PLUSNG
          else TheOp := PLUS;
         InsertOperator (TheOp, Result, REOpSz + RENextOffSz);
        end;
      if NonGreedyCh //###0.940
       then inc (regparse); // Skip extra char ('?')
     end; { of case '+'}
    '?': begin
      flagp := WORST;
      NonGreedyCh := (regparse + 1)^ = '?'; //###0.940
      NonGreedyOp := NonGreedyCh or ((fCompModifiers and MaskModG) = 0); //###0.940
      if NonGreedyOp then begin //###0.940  // We emit x?? as x{0,1}?
         if (flags and SIMPLE) = 0
          then EmitComplexBraces (0, 1, NonGreedyOp)
          else EmitSimpleBraces (0, 1, NonGreedyOp);
        end
       else begin // greedy '?'
         InsertOperator (BRANCH, Result, REOpSz + RENextOffSz); // Either x
         Tail (Result, EmitNode (BRANCH));  // or
         NextNode := EmitNode (NOTHING); // nil.
         Tail (Result, NextNode);
         OpTail (Result, NextNode);
        end;
      if NonGreedyCh //###0.940
       then inc (regparse); // Skip extra char ('?')
     end; { of case '?'}
   '{': begin
      savedparse := regparse;
      // !!!!!!!!!!!!
      // Filip Jirsak's note - what will happen, when we are at the end of regparse?
      inc (regparse);
      p := regparse;
      while Pos (regparse^, '0123456789') > 0  // <min> MUST appear
       do inc (regparse);
      if (regparse^ <> '}') and (regparse^ <> ',') or (p = regparse) then begin
        regparse := savedparse;
        flagp := flags;
        EXIT;
       end;
      BracesMin := parsenum (p, regparse - 1);
      if regparse^ = ',' then begin
         inc (regparse);
         p := regparse;
         while Pos (regparse^, '0123456789') > 0
          do inc (regparse);
         if regparse^ <> '}' then begin
           regparse := savedparse;
           EXIT;
          end;
         if p = regparse
          then BracesMax := MaxBracesArg
          else BracesMax := parsenum (p, regparse - 1);
        end
       else BracesMax := BracesMin; // {n} == {n,n}
      if BracesMin > BracesMax then begin
        Error (reeBracesMinParamGreaterMax);
        EXIT;
       end;
      if BracesMin > 0
       then flagp := WORST;
      if BracesMax > 0
       then flagp := flagp or HASWIDTH or SPSTART;

      NonGreedyCh := (regparse + 1)^ = '?'; //###0.940
      NonGreedyOp := NonGreedyCh or ((fCompModifiers and MaskModG) = 0); //###0.940
      if (flags and SIMPLE) <> 0
       then EmitSimpleBraces (BracesMin, BracesMax, NonGreedyOp)
       else EmitComplexBraces (BracesMin, BracesMax, NonGreedyOp);
      if NonGreedyCh //###0.940
       then inc (regparse); // Skip extra char '?'
     end; // of case '{'
//    else // here we can't be
   end; { of case op}

  inc (regparse);
  if (regparse^ = '*') or (regparse^ = '+') or (regparse^ = '?') or (regparse^ = '{') then begin
    Error (reeNestedSQP);
    EXIT;
   end;
 end; { of function TRegExpr.ParsePiece
--------------------------------------------------------------}

function TRegExpr.ParseAtom (var flagp : integer) : PRegExprChar;
// the lowest level
// Optimization:  gobbles an entire sequence of ordinary characters so that
// it can turn them into a single node, which is smaller to store and
// faster to run. Backslashed characters are exceptions, each becoming a
// separate node; the code is simpler that way and it's not worth fixing.
 var
  ret : PRegExprChar;
  flags : integer;
  RangeBeg, RangeEnd : REChar;
  CanBeRange : boolean;
  len : PtrInt;
  ender : REChar;
  directive: PRegExprChar;
  begmodfs : PRegExprChar;

  {$IFDEF UseSetOfChar} //###0.930
  RangePCodeBeg : PRegExprChar;
  RangePCodeIdx : PtrInt;
  RangeIsCI : boolean;
  RangeSet : TSetOfREChar;
  RangeLen : PtrInt;
  RangeChMin, RangeChMax : REChar;
  {$ENDIF}

 procedure EmitExactly (ch : REChar);
  begin
   if (fCompModifiers and MaskModI) <> 0
    then ret := EmitNode (EXACTLYCI)
    else ret := EmitNode (EXACTLY);
   EmitC (ch);
   EmitC (#0);
   flagp := flagp or HASWIDTH or SIMPLE;
  end;

 procedure EmitStr (const s : RegExprString);
  var i : PtrInt;
  begin
   for i := 1 to length (s)
    do EmitC (s [i]);
  end;

 function HexDig (ch : REChar) : PtrInt;
  begin
   Result := 0;
   if (ch >= 'a') and (ch <= 'f')
    then ch := REChar (ord (ch) - (ord ('a') - ord ('A')));
   if (ch < '0') or (ch > 'F') or ((ch > '9') and (ch < 'A')) then begin
     Error (reeBadHexDigit);
     EXIT;
    end;
   Result := ord (ch) - ord ('0');
   if ch >= 'A'
    then Result := Result - (ord ('A') - ord ('9') - 1);
  end;

 function EmitRange (AOpCode : REChar) : PRegExprChar;
  begin
   {$IFDEF UseSetOfChar}
   case AOpCode of
     ANYBUTCI, ANYBUT:
       Result := EmitNode (ANYBUTTINYSET);
     else // ANYOFCI, ANYOF
       Result := EmitNode (ANYOFTINYSET);
    end;
   case AOpCode of
     ANYBUTCI, ANYOFCI:
       RangeIsCI := True;
     else // ANYBUT, ANYOF
       RangeIsCI := False;
    end;
   RangePCodeBeg := regcode;
   RangePCodeIdx := regsize;
   RangeLen := 0;
   RangeSet := [];
   RangeChMin := #255;
   RangeChMax := #0;
   {$ELSE}
   Result := EmitNode (AOpCode);
   // ToDo:
   // !!!!!!!!!!!!! Implement ANYOF[BUT]TINYSET generation for UniCode !!!!!!!!!!
   {$ENDIF}
  end;

{$IFDEF UseSetOfChar}
 procedure EmitRangeCPrim (b : REChar); //###0.930
  begin
   if b in RangeSet
    then EXIT;
   inc (RangeLen);
   if b < RangeChMin
    then RangeChMin := b;
   if b > RangeChMax
    then RangeChMax := b;
   Include (RangeSet, b);
  end;
 {$ENDIF}

 procedure EmitRangeC (b : REChar);
  {$IFDEF UseSetOfChar}
  var
   Ch : REChar;
  {$ENDIF}
  begin
   CanBeRange := false;
   {$IFDEF UseSetOfChar}
    if b <> #0 then begin
       EmitRangeCPrim (b); //###0.930
       if RangeIsCI
        then EmitRangeCPrim (InvertCase (b)); //###0.930
      end
     else begin
       {$IFDEF UseAsserts}
       Assert (RangeLen > 0, 'TRegExpr.ParseAtom(subroutine EmitRangeC): empty range'); // impossible, but who knows..
       Assert (RangeChMin <= RangeChMax, 'TRegExpr.ParseAtom(subroutine EmitRangeC): RangeChMin > RangeChMax'); // impossible, but who knows..
       {$ENDIF}
       if RangeLen <= TinySetLen then begin // emit "tiny set"
          if regcode = @regdummy then begin
            regsize := RangePCodeIdx + TinySetLen; // RangeChMin/Max !!!
            EXIT;
           end;
          regcode := RangePCodeBeg;
          for Ch := RangeChMin to RangeChMax do //###0.930
           if Ch in RangeSet then begin
             regcode^ := Ch;
             inc (regcode);
            end;
          // fill rest:
          while regcode < RangePCodeBeg + TinySetLen do begin
            regcode^ := RangeChMax;
            inc (regcode);
           end;
          {$IFDEF DebugSynRegExpr}
          if regcode-programm>regsize then
            raise Exception.Create('TRegExpr.ParseAtom.EmitRangeC TinySetLen buffer overrun');
          {$ENDIF}
         end
        else begin
          if regcode = @regdummy then begin
            regsize := RangePCodeIdx + SizeOf (TSetOfREChar);
            EXIT;
           end;
          if (RangePCodeBeg - REOpSz - RENextOffSz)^ = ANYBUTTINYSET
           then RangeSet := [#0 .. #255] - RangeSet;
          PREOp (RangePCodeBeg - REOpSz - RENextOffSz)^ := ANYOFFULLSET;
          regcode := RangePCodeBeg;
          Move (RangeSet, regcode^, SizeOf (TSetOfREChar));
          inc (regcode, SizeOf (TSetOfREChar));
          {$IFDEF DebugSynRegExpr}
          if regcode-programm>regsize then
            raise Exception.Create('TRegExpr.ParseAtom.EmitRangeC non TinySetLen buffer overrun');
          {$ENDIF}
         end;
      end;
   {$ELSE}
   EmitC (b);
   {$ENDIF}
  end;

 procedure EmitSimpleRangeC (b : REChar);
  begin
   RangeBeg := b;
   EmitRangeC (b);
   CanBeRange := true;
  end;

 procedure EmitRangeStr (const s : RegExprString);
  var i : PtrInt;
  begin
   for i := 1 to length (s)
    do EmitRangeC (s [i]);
  end;

 function UnQuoteChar (var APtr : PRegExprChar) : REChar; //###0.934
  begin
   case APtr^ of
     't': Result := #$9;  // \t => tab (HT/TAB)
     'n': Result := #$a;  // \n => newline (NL)
     'r': Result := #$d;  // \r => carriage return (CR)
     'f': Result := #$c;  // \f => form feed (FF)
     'a': Result := #$7;  // \a => alarm (bell) (BEL)
     'e': Result := #$1b; // \e => escape (ESC)
     'x': begin // \x: hex char
       Result := #0;
       inc (APtr);
       if APtr^ = #0 then begin
         Error (reeNoHexCodeAfterBSlashX);
         EXIT;
        end;
       if APtr^ = '{' then begin // \x{nnnn} //###0.936
          REPEAT
           inc (APtr);
           if APtr^ = #0 then begin
             Error (reeNoHexCodeAfterBSlashX);
             EXIT;
            end;
           if APtr^ <> '}' then begin
              if (Ord (Result)
                  ShR (SizeOf (REChar) * 8 - 4)) and $F <> 0 then begin
                Error (reeHexCodeAfterBSlashXTooBig);
                EXIT;
               end;
              Result := REChar ((Ord (Result) ShL 4) or HexDig (APtr^));
              // HexDig will cause Error if bad hex digit found
             end
            else BREAK;
          UNTIL False;
         end
        else begin
          Result := REChar (HexDig (APtr^));
          // HexDig will cause Error if bad hex digit found
          inc (APtr);
          if APtr^ = #0 then begin
            Error (reeNoHexCodeAfterBSlashX);
            EXIT;
           end;
          Result := REChar ((Ord (Result) ShL 4) or HexDig (APtr^));
          // HexDig will cause Error if bad hex digit found
         end;
      end;
     else Result := APtr^;
    end;
  end;

 begin
  Result := nil;
  flagp := WORST; // Tentatively.

  inc (regparse);
  case (regparse - 1)^ of
    '^': if ((fCompModifiers and MaskModM) = 0)
           or ((fLineSeparators = '') and not fLinePairedSeparatorAssigned)
          then ret := EmitNode (BOL)
          else ret := EmitNode (BOLML);
    '$': if ((fCompModifiers and MaskModM) = 0)
           or ((fLineSeparators = '') and not fLinePairedSeparatorAssigned)
          then ret := EmitNode (EOL)
          else ret := EmitNode (EOLML);
    '.':
       if (fCompModifiers and MaskModS) <> 0 then begin
          ret := EmitNode (ANY);
          flagp := flagp or HASWIDTH or SIMPLE;
         end
        else begin // not /s, so emit [^:LineSeparators:]
          ret := EmitNode (ANYML);
          flagp := flagp or HASWIDTH; // not so simple ;)
//          ret := EmitRange (ANYBUT);
//          EmitRangeStr (LineSeparators); //###0.941
//          EmitRangeStr (LinePairedSeparator); // !!! isn't correct if have to accept only paired
//          EmitRangeC (#0);
//          flagp := flagp or HASWIDTH or SIMPLE;
         end;
    '[': begin
        if regparse^ = '^' then begin // Complement of range.
           if (fCompModifiers and MaskModI) <> 0
            then ret := EmitRange (ANYBUTCI)
            else ret := EmitRange (ANYBUT);
           inc (regparse);
          end
         else
          if (fCompModifiers and MaskModI) <> 0
           then ret := EmitRange (ANYOFCI)
           else ret := EmitRange (ANYOF);

        CanBeRange := false;

        if (regparse^ = ']') then begin
          EmitSimpleRangeC (regparse^); // []-a] -> ']' .. 'a'
          inc (regparse);
         end;

        while (regparse^ <> #0) and (regparse^ <> ']') do begin
          if (regparse^ = '-')
              and ((regparse + 1)^ <> #0) and ((regparse + 1)^ <> ']')
              and CanBeRange then begin
             inc (regparse);
             RangeEnd := regparse^;
             if RangeEnd = EscChar then begin
               {$IFDEF UniCode} //###0.935
               if (ord ((regparse + 1)^) < 256)
                  and (char ((regparse + 1)^)
                        in ['d', 'D', 's', 'S', 'w', 'W']) then begin
               {$ELSE}
               if (regparse + 1)^ in ['d', 'D', 's', 'S', 'w', 'W'] then begin
               {$ENDIF}
                 EmitRangeC ('-'); // or treat as error ?!!
                 CONTINUE;
                end;
               inc (regparse);
               RangeEnd := UnQuoteChar (regparse);
              end;

             // r.e.ranges extension for russian
             if ((fCompModifiers and MaskModR) <> 0)
                and (RangeBeg = RusRangeLoLow) and (RangeEnd = RusRangeLoHigh) then begin
               EmitRangeStr (RusRangeLo);
              end
             else if ((fCompModifiers and MaskModR) <> 0)
                 and (RangeBeg = RusRangeHiLow) and (RangeEnd = RusRangeHiHigh) then begin
               EmitRangeStr (RusRangeHi);
              end
             else if ((fCompModifiers and MaskModR) <> 0)
                  and (RangeBeg = RusRangeLoLow) and (RangeEnd = RusRangeHiHigh) then begin
               EmitRangeStr (RusRangeLo);
               EmitRangeStr (RusRangeHi);
              end
             else begin // standard r.e. handling
               if RangeBeg > RangeEnd then begin
                 Error (reeInvalidRange);
                 EXIT;
                end;
               inc (RangeBeg);
               EmitRangeC (RangeEnd); // prevent infinite loop if RangeEnd=$ff
               while RangeBeg < RangeEnd do begin //###0.929
                 EmitRangeC (RangeBeg);
                 inc (RangeBeg);
                end;
              end;
             inc (regparse);
            end
           else begin
             if regparse^ = EscChar then begin
                inc (regparse);
                if regparse^ = #0 then begin
                  Error (reeParseAtomTrailingBackSlash);
                  EXIT;
                 end;
                case regparse^ of // r.e.extensions
                  'd': EmitRangeStr ('0123456789');
                  'w': EmitRangeStr (WordChars);
                  's': EmitRangeStr (SpaceChars);
                  else EmitSimpleRangeC (UnQuoteChar (regparse));
                 end; { of case}
               end
              else EmitSimpleRangeC (regparse^);
             inc (regparse);
            end;
         end; { of while}
        EmitRangeC (#0);
        if regparse^ <> ']' then begin
          Error (reeUnmatchedSqBrackets);
          EXIT;
         end;
        inc (regparse);
        flagp := flagp or HASWIDTH or SIMPLE;
      end;
    '(': begin
        if regparse^ = '*' then begin // (*PRUNE) and so on
           inc(regparse);
           directive := regparse;
           while (regparse^ <> #0) And (regparse^ <> ')') do
             inc(regparse);
           if regparse^ = #0 Then
              begin
                 Error (reeBadDirective);
                 EXIT;
              end;
           if (regparse - directive = 5) and
              (directive^ = 'P') and
              ((directive+1)^ = 'R') and
              ((directive+2)^ = 'U') and
              ((directive+3)^ = 'N') and
              ((directive+4)^ = 'E') then
                begin
                  inc (regparse); // skip ')'
                  ret := EmitNode (PRUNE); // prune backtracking
                end
           else if (regparse - directive = 4) and
              (directive^ = 'F') and
              ((directive+1)^ = 'A') and
              ((directive+2)^ = 'I') and
              ((directive+3)^ = 'L') then
                begin
                  inc (regparse); // skip ')'
                  ret := EmitNode (FAIL); // fail
                end
           else if (regparse - directive = 4) and
              (directive^ = 'S') and
              ((directive+1)^ = 'T') and
              ((directive+2)^ = 'O') and
              ((directive+3)^ = 'P') then
                begin
                  inc (regparse); // skip ')'
                  ret := EmitNode (STOP); // stop
                end
           else
             begin
                Error (reeBadDirective);
                EXIT;
             end
        end
        else if regparse^ = '?' then begin
           // check for extended Perl syntax : (?..)
           if (regparse + 1)^ = '#' then begin // (?#comment)
              inc (regparse, 2); // find closing ')'
              while (regparse^ <> #0) and (regparse^ <> ')')
               do inc (regparse);
              if regparse^ <> ')' then begin
                Error (reeUnclosedComment);
                EXIT;
               end;
              inc (regparse); // skip ')'
              ret := EmitNode (COMMENT); // comment
             end
           else begin // modifiers ?
             inc (regparse); // skip '?'
             begmodfs := regparse;
             while (regparse^ <> #0) and (regparse^ <> ')')
              do inc (regparse);
             if (regparse^ <> ')')
                or not ParseModifiersStr (copy (begmodfs, 1, (regparse - begmodfs)), fCompModifiers) then begin
               Error (reeUrecognizedModifier);
               EXIT;
              end;
             inc (regparse); // skip ')'
             ret := EmitNode (COMMENT); // comment
//             Error (reeQPSBFollowsNothing);
//             EXIT;
            end;
          end
         else begin
           ret := ParseReg (1, flags);
           if ret = nil then begin
             Result := nil;
             EXIT;
            end;
           flagp := flagp or flags and (HASWIDTH or SPSTART);
          end;
      end;
    #0, '|', ')': begin // Supposed to be caught earlier.
       Error (reeInternalUrp);
       EXIT;
      end;
    '?', '+', '*': begin
       Error (reeQPSBFollowsNothing);
       EXIT;
      end;
    EscChar: begin
        if regparse^ = #0 then begin
          Error (reeTrailingBackSlash);
          EXIT;
         end;
        case regparse^ of // r.e.extensions
          'b': ret := EmitNode (BOUND); //###0.943
          'B': ret := EmitNode (NOTBOUND); //###0.943
          'A': ret := EmitNode (BOL); //###0.941
          'Z': ret := EmitNode (EOL); //###0.941
          'd': begin // r.e.extension - any digit ('0' .. '9')
             ret := EmitNode (ANYDIGIT);
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          'D': begin // r.e.extension - not digit ('0' .. '9')
             ret := EmitNode (NOTDIGIT);
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          's': begin // r.e.extension - any space char
             {$IFDEF UseSetOfChar}
             ret := EmitRange (ANYOF);
             EmitRangeStr (SpaceChars);
             EmitRangeC (#0);
             {$ELSE}
             ret := EmitNode (ANYSPACE);
             {$ENDIF}
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          'S': begin // r.e.extension - not space char
             {$IFDEF UseSetOfChar}
             ret := EmitRange (ANYBUT);
             EmitRangeStr (SpaceChars);
             EmitRangeC (#0);
             {$ELSE}
             ret := EmitNode (NOTSPACE);
             {$ENDIF}
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          'w': begin // r.e.extension - any english char / digit / '_'
             {$IFDEF UseSetOfChar}
             ret := EmitRange (ANYOF);
             EmitRangeStr (WordChars);
             EmitRangeC (#0);
             {$ELSE}
             ret := EmitNode (ANYLETTER);
             {$ENDIF}
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          'W': begin // r.e.extension - not english char / digit / '_'
             {$IFDEF UseSetOfChar}
             ret := EmitRange (ANYBUT);
             EmitRangeStr (WordChars);
             EmitRangeC (#0);
             {$ELSE}
             ret := EmitNode (NOTLETTER);
             {$ENDIF}
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
           '1' .. '9': begin //###0.936
             if (fCompModifiers and MaskModI) <> 0
              then ret := EmitNode (BSUBEXPCI)
              else ret := EmitNode (BSUBEXP);
             EmitC (REChar (ord (regparse^) - ord ('0')));
             flagp := flagp or HASWIDTH or SIMPLE;
            end;
          else EmitExactly (UnQuoteChar (regparse));
         end; { of case}
        inc (regparse);
      end;
    else begin
      dec (regparse);
      if ((fCompModifiers and MaskModX) <> 0) and // check for eXtended syntax
          ((regparse^ = '#')
           or ({$IFDEF UniCode}StrScan (XIgnoredChars, regparse^) <> nil //###0.947
               {$ELSE}regparse^ in XIgnoredChars{$ENDIF})) then begin //###0.941 \x
         if regparse^ = '#' then begin // Skip eXtended comment
            // find comment terminator (group of \n and/or \r)
            while (regparse^ <> #0) and (regparse^ <> #$d) and (regparse^ <> #$a)
             do inc (regparse);
            while (regparse^ = #$d) or (regparse^ = #$a) // skip comment terminator
             do inc (regparse); // attempt to support different type of line separators
           end
          else begin // Skip the blanks!
            while {$IFDEF UniCode}StrScan (XIgnoredChars, regparse^) <> nil //###0.947
                  {$ELSE}regparse^ in XIgnoredChars{$ENDIF}
             do inc (regparse);
           end;
         ret := EmitNode (COMMENT); // comment
        end
       else begin
         len := strcspn (regparse, META);
         if len <= 0 then
          if regparse^ <> '{' then begin
             Error (reeRarseAtomInternalDisaster);
             EXIT;
            end
           else len := strcspn (regparse + 1, META) + 1; // bad {n,m} - compile as EXATLY
         ender := (regparse + len)^;
         if (len > 1)
            and ((ender = '*') or (ender = '+') or (ender = '?') or (ender = '{'))
          then dec (len); // Back off clear of ?+*{ operand.
         flagp := flagp or HASWIDTH;
         if len = 1
         then flagp := flagp or SIMPLE;
         if (fCompModifiers and MaskModI) <> 0
          then ret := EmitNode (EXACTLYCI)
          else ret := EmitNode (EXACTLY);
         while (len > 0)
          and (((fCompModifiers and MaskModX) = 0) or (regparse^ <> '#')) do begin
           if ((fCompModifiers and MaskModX) = 0) or not ( //###0.941
              {$IFDEF UniCode}StrScan (XIgnoredChars, regparse^) <> nil //###0.947
              {$ELSE}regparse^ in XIgnoredChars{$ENDIF} )
            then EmitC (regparse^);
           inc (regparse);
           dec (len);
          end;
         EmitC (#0);
        end; { of if not comment}
     end; { of case else}
   end; { of case}

  Result := ret;
 end; { of function TRegExpr.ParseAtom
--------------------------------------------------------------}

function TRegExpr.GetCompilerErrorPos : PtrInt;
 begin
  Result := 0;
  if (regexpbeg = nil) or (regparse = nil)
   then EXIT; // not in compiling mode ?
  Result := regparse - regexpbeg;
 end; { of function TRegExpr.GetCompilerErrorPos
--------------------------------------------------------------}


{=============================================================}
{===================== Matching section ======================}
{=============================================================}

{$IFNDEF UseSetOfChar}
function TRegExpr.StrScanCI (s : PRegExprChar; ch : REChar) : PRegExprChar; //###0.928 - now method of TRegExpr
 begin
  while (s^ <> #0) and (s^ <> ch) and (s^ <> InvertCase (ch))
   do inc (s);
  if s^ <> #0
   then Result := s
   else Result := nil;
 end; { of function TRegExpr.StrScanCI
--------------------------------------------------------------}
{$ENDIF}

function TRegExpr.regrepeat (p : PRegExprChar; AMax : PtrInt) : PtrInt;
// repeatedly match something simple, report how many
 var
  scan : PRegExprChar;
  opnd : PRegExprChar;
  TheMax : integer;
  {Ch,} InvCh : REChar; //###0.931
  sestart, seend : PRegExprChar; //###0.936
 begin
  Result := 0;
  scan := reginput;
  opnd := p + REOpSz + RENextOffSz; //OPERAND
  TheMax := fInputEnd - scan;
  if TheMax > AMax
   then TheMax := AMax;
  case PREOp (p)^ of
    ANY: begin
    // note - ANYML cannot be proceeded in regrepeat because can skip
    // more than one char at once
      Result := TheMax;
      inc (scan, Result);
     end;
    EXACTLY: begin // in opnd can be only ONE char !!!
//      Ch := opnd^; // store in register //###0.931
      while (Result < TheMax) and (opnd^ = scan^) do begin
        inc (Result);
        inc (scan);
       end;
     end;
    EXACTLYCI: begin // in opnd can be only ONE char !!!
//      Ch := opnd^; // store in register //###0.931
      while (Result < TheMax) and (opnd^ = scan^) do begin // prevent unneeded InvertCase //###0.931
        inc (Result);
        inc (scan);
       end;
      if Result < TheMax then begin //###0.931
        InvCh := InvertCase (opnd^); // store in register
        while (Result < TheMax) and
              ((opnd^ = scan^) or (InvCh = scan^)) do begin
          inc (Result);
          inc (scan);
         end;
       end;
     end;
    BSUBEXP: begin //###0.936
      sestart := startp [ord (opnd^)];
      if sestart = nil
       then EXIT;
      seend := endp [ord (opnd^)];
      if seend = nil
       then EXIT;
      REPEAT
        opnd := sestart;
        while opnd < seend do begin
          if (scan >= fInputEnd) or (scan^ <> opnd^)
           then EXIT;
          inc (scan);
          inc (opnd);
         end;
        inc (Result);
        reginput := scan;
      UNTIL Result >= AMax;
     end;
    BSUBEXPCI: begin //###0.936
      sestart := startp [ord (opnd^)];
      if sestart = nil
       then EXIT;
      seend := endp [ord (opnd^)];
      if seend = nil
       then EXIT;
      REPEAT
        opnd := sestart;
        while opnd < seend do begin
          if (scan >= fInputEnd) or
             ((scan^ <> opnd^) and (scan^ <> InvertCase (opnd^)))
           then EXIT;
          inc (scan);
          inc (opnd);
         end;
        inc (Result);
        reginput := scan;
      UNTIL Result >= AMax;
     end;
    ANYDIGIT:
      while (Result < TheMax) and
         (scan^ >= '0') and (scan^ <= '9') do begin
        inc (Result);
        inc (scan);
       end;
    NOTDIGIT:
      while (Result < TheMax) and
         ((scan^ < '0') or (scan^ > '9')) do begin
        inc (Result);
        inc (scan);
       end;
    {$IFNDEF UseSetOfChar} //###0.929
    ANYLETTER:
      while (Result < TheMax) and
       (Pos (scan^, fWordChars) > 0) //###0.940
     {  ((scan^ >= 'a') and (scan^ <= 'z') !! I've forgotten (>='0') and (<='9')
       or (scan^ >= 'A') and (scan^ <= 'Z') or (scan^ = '_'))} do begin
        inc (Result);
        inc (scan);
       end;
    NOTLETTER:
      while (Result < TheMax) and
       (Pos (scan^, fWordChars) <= 0)  //###0.940
     {   not ((scan^ >= 'a') and (scan^ <= 'z') !! I've forgotten (>='0') and (<='9')
         or (scan^ >= 'A') and (scan^ <= 'Z')
         or (scan^ = '_'))} do begin
        inc (Result);
        inc (scan);
       end;
    ANYSPACE:
      while (Result < TheMax) and
         (Pos (scan^, fSpaceChars) > 0) do begin
        inc (Result);
        inc (scan);
       end;
    NOTSPACE:
      while (Result < TheMax) and
         (Pos (scan^, fSpaceChars) <= 0) do begin
        inc (Result);
        inc (scan);
       end;
    {$ENDIF}
    ANYOFTINYSET: begin
      while (Result < TheMax) and //!!!TinySet
       ((scan^ = opnd^) or (scan^ = (opnd + 1)^)
        or (scan^ = (opnd + 2)^)) do begin
        inc (Result);
        inc (scan);
       end;
     end;
    ANYBUTTINYSET: begin
      while (Result < TheMax) and //!!!TinySet
       (scan^ <> opnd^) and (scan^ <> (opnd + 1)^)
        and (scan^ <> (opnd + 2)^) do begin
        inc (Result);
        inc (scan);
       end;
     end;
    {$IFDEF UseSetOfChar} //###0.929
    ANYOFFULLSET: begin
      while (Result < TheMax) and
       (scan^ in PSetOfREChar (opnd)^) do begin
        inc (Result);
        inc (scan);
       end;
     end;
    {$ELSE}
    ANYOF:
      while (Result < TheMax) and
         (StrScan (opnd, scan^) <> nil) do begin
        inc (Result);
        inc (scan);
       end;
    ANYBUT:
      while (Result < TheMax) and
         (StrScan (opnd, scan^) = nil) do begin
        inc (Result);
        inc (scan);
       end;
    ANYOFCI:
      while (Result < TheMax) and (StrScanCI (opnd, scan^) <> nil) do begin
        inc (Result);
        inc (scan);
       end;
    ANYBUTCI:
      while (Result < TheMax) and (StrScanCI (opnd, scan^) = nil) do begin
        inc (Result);
        inc (scan);
       end;
    {$ENDIF}
    else begin // Oh dear. Called inappropriately.
      Result := 0; // Best compromise.
      Error (reeRegRepeatCalledInappropriately);
      EXIT;
     end;
   end; { of case}
  reginput := scan;
 end; { of function TRegExpr.regrepeat
--------------------------------------------------------------}

function TRegExpr.regnext (p : PRegExprChar) : PRegExprChar;
// dig the "next" pointer out of a node
 var offset : TRENextOff;
 begin
  if p = @regdummy then begin
    Result := nil;
    EXIT;
   end;
  offset := PRENextOff (AlignToPtr(p + REOpSz))^; //###0.933 inlined NEXT
  if offset = 0
   then Result := nil
   else Result := p + offset;
 end; { of function TRegExpr.regnext
--------------------------------------------------------------}

function TRegExpr.MatchPrim(context: TVarValue; contextNum: Integer;
  prog: PRegExprChar; var Pruning: Boolean): boolean;
// recursively matching routine
// Conceptually the strategy is simple:  check to see whether the current
// node matches, call self recursively to see whether the rest matches,
// and then act accordingly. In practice we make some effort to avoid
// recursion, in particular by going through "ordinary" nodes (that don't
// need to know whether the rest of the match failed) by a loop instead of
// by recursion.
 var
  scan : PRegExprChar; // Current node.
  next : PRegExprChar; // Next node.
  len : PtrInt;
  opnd : PRegExprChar;
  no : PtrInt;
  save : PRegExprChar;
  nextch : REChar;
  BracesMin, BracesMax : PtrInt; // we use integer instead of TREBracesArg for better support */+
  VV: TVarValue;
  VS, T: TVarStruct;
  S, S1: RegExprString;
  SP: PRegExprChar;
  ref : Integer;
  i, j: Integer;
  stp, enp: PRegExprChar;
  pcalls: TFastCalls;
  locPruning: Boolean;
  {$IFDEF ComplexBraces}
  SavedLoopStack : array [1 .. LoopStackMax] of integer; // :(( very bad for recursion
  SavedLoopStackIdx : integer; //###0.925
  {$ENDIF}
 begin
  Result := false;
  scan := prog;

  while scan <> nil do begin
     len := PRENextOff (AlignToPtr(scan + 1))^; //###0.932 inlined regnext
     if len = 0
      then next := nil
      else next := scan + len;

     case scan^ of
         NOTBOUND, //###0.943 //!!! think about UseSetOfChar !!!
         BOUND:
         if (scan^ = BOUND)
          xor (
          ((reginput = fInputStart) or (Pos ((reginput - 1)^, fWordChars) <= 0))
            and (reginput^ <> #0) and (Pos (reginput^, fWordChars) > 0)
           or
            (reginput <> fInputStart) and (Pos ((reginput - 1)^, fWordChars) > 0)
            and ((reginput^ = #0) or (Pos (reginput^, fWordChars) <= 0)))
          then EXIT;

         BOL: if reginput <> fInputStart
               then EXIT;
         EOL: if reginput^ <> #0
               then EXIT;
         BOLML: if reginput > fInputStart then begin
            nextch := (reginput - 1)^;
            if (nextch <> fLinePairedSeparatorTail)
               or ((reginput - 1) <= fInputStart)
               or ((reginput - 2)^ <> fLinePairedSeparatorHead)
              then begin
               if (nextch = fLinePairedSeparatorHead)
                 and (reginput^ = fLinePairedSeparatorTail)
                then EXIT; // don't stop between paired separator
               if
                 {$IFNDEF UniCode}
                 not (nextch in fLineSeparatorsSet)
                 {$ELSE}
                 (pos (nextch, fLineSeparators) <= 0)
                 {$ENDIF}
                then EXIT;
              end;
           end;
         EOLML: if reginput^ <> #0 then begin
            nextch := reginput^;
            if (nextch <> fLinePairedSeparatorHead)
               or ((reginput + 1)^ <> fLinePairedSeparatorTail)
             then begin
               if (nextch = fLinePairedSeparatorTail)
                 and (reginput > fInputStart)
                 and ((reginput - 1)^ = fLinePairedSeparatorHead)
                then EXIT; // don't stop between paired separator
               if
                 {$IFNDEF UniCode}
                 not (nextch in fLineSeparatorsSet)
                 {$ELSE}
                 (pos (nextch, fLineSeparators) <= 0)
                 {$ENDIF}
                then EXIT;
              end;
           end;
         ANY: begin
            if reginput^ = #0
             then EXIT;
            inc (reginput);
           end;
         ANYML: begin //###0.941
            if (reginput^ = #0)
             or ((reginput^ = fLinePairedSeparatorHead)
                 and ((reginput + 1)^ = fLinePairedSeparatorTail))
             or {$IFNDEF UniCode} (reginput^ in fLineSeparatorsSet)
                {$ELSE} (pos (reginput^, fLineSeparators) > 0) {$ENDIF}
             then EXIT;
            inc (reginput);
           end;
         ANYDIGIT: begin
            if (reginput^ = #0) or (reginput^ < '0') or (reginput^ > '9')
             then EXIT;
            inc (reginput);
           end;
         NOTDIGIT: begin
            if (reginput^ = #0) or ((reginput^ >= '0') and (reginput^ <= '9'))
             then EXIT;
            inc (reginput);
           end;
         {$IFNDEF UseSetOfChar} //###0.929
         ANYLETTER: begin
            if (reginput^ = #0) or (Pos (reginput^, fWordChars) <= 0) //###0.943
             then EXIT;
            inc (reginput);
           end;
         NOTLETTER: begin
            if (reginput^ = #0) or (Pos (reginput^, fWordChars) > 0) //###0.943
             then EXIT;
            inc (reginput);
           end;
         ANYSPACE: begin
            if (reginput^ = #0) or not (Pos (reginput^, fSpaceChars) > 0) //###0.943
             then EXIT;
            inc (reginput);
           end;
         NOTSPACE: begin
            if (reginput^ = #0) or (Pos (reginput^, fSpaceChars) > 0) //###0.943
             then EXIT;
            inc (reginput);
           end;
         {$ENDIF}
         EXACTLYCI: begin
            opnd := scan + REOpSz + RENextOffSz; // OPERAND
            // Inline the first character, for speed.
            if (opnd^ <> reginput^)
               and (InvertCase (opnd^) <> reginput^)
             then EXIT;
            len := strlen (opnd);
            //###0.929 begin
            no := len;
            save := reginput;
            while no > 1 do begin
              inc (save);
              inc (opnd);
              if (opnd^ <> save^)
                 and (InvertCase (opnd^) <> save^)
               then EXIT;
              dec (no);
             end;
            //###0.929 end
            inc (reginput, len);
           end;
         EXACTLY: begin
            opnd := scan + REOpSz + RENextOffSz; // OPERAND
            // Inline the first character, for speed.
            if opnd^ <> reginput^
             then EXIT;
            len := strlen (opnd);
            //###0.929 begin
            no := len;
            save := reginput;
            while no > 1 do begin
              inc (save);
              inc (opnd);
              if opnd^ <> save^
               then EXIT;
              dec (no);
             end;
            //###0.929 end
            inc (reginput, len);
           end;
         BSUBEXP: begin //###0.936
           no := ord ((scan + REOpSz + RENextOffSz)^);
           if startp [no] = nil
            then EXIT;
           if endp [no] = nil
            then EXIT;
           save := reginput;
           opnd := startp [no];
           while opnd < endp [no] do begin
             if (save >= fInputEnd) or (save^ <> opnd^)
              then EXIT;
             inc (save);
             inc (opnd);
            end;
           reginput := save;
          end;
         BSUBEXPCI: begin //###0.936
           no := ord ((scan + REOpSz + RENextOffSz)^);
           if startp [no] = nil
            then EXIT;
           if endp [no] = nil
            then EXIT;
           save := reginput;
           opnd := startp [no];
           while opnd < endp [no] do begin
             if (save >= fInputEnd) or
                ((save^ <> opnd^) and (save^ <> InvertCase (opnd^)))
              then EXIT;
             inc (save);
             inc (opnd);
            end;
           reginput := save;
          end;
         ANYOFTINYSET: begin
           if (reginput^ = #0) or //!!!TinySet
             ((reginput^ <> (scan + REOpSz + RENextOffSz)^)
             and (reginput^ <> (scan + REOpSz + RENextOffSz + 1)^)
             and (reginput^ <> (scan + REOpSz + RENextOffSz + 2)^))
            then EXIT;
           inc (reginput);
          end;
         ANYBUTTINYSET: begin
           if (reginput^ = #0) or //!!!TinySet
             (reginput^ = (scan + REOpSz + RENextOffSz)^)
             or (reginput^ = (scan + REOpSz + RENextOffSz + 1)^)
             or (reginput^ = (scan + REOpSz + RENextOffSz + 2)^)
            then EXIT;
           inc (reginput);
          end;
         {$IFDEF UseSetOfChar} //###0.929
         ANYOFFULLSET: begin
           if (reginput^ = #0)
              or not (reginput^ in PSetOfREChar (scan + REOpSz + RENextOffSz)^)
            then EXIT;
           inc (reginput);
          end;
         {$ELSE}
         ANYOF: begin
            if (reginput^ = #0) or (StrScan (scan + REOpSz + RENextOffSz, reginput^) = nil)
             then EXIT;
            inc (reginput);
           end;
         ANYBUT: begin
            if (reginput^ = #0) or (StrScan (scan + REOpSz + RENextOffSz, reginput^) <> nil)
             then EXIT;
            inc (reginput);
           end;
         ANYOFCI: begin
            if (reginput^ = #0) or (StrScanCI (scan + REOpSz + RENextOffSz, reginput^) = nil)
             then EXIT;
            inc (reginput);
           end;
         ANYBUTCI: begin
            if (reginput^ = #0) or (StrScanCI (scan + REOpSz + RENextOffSz, reginput^) <> nil)
             then EXIT;
            inc (reginput);
           end;
         {$ENDIF}
         NOTHING: ;
         COMMENT: ;
         BACK: ;
         PRUNE:
            Pruning := True;
         FAIL:
            Exit(False);
         STOP:
            begin;
              fInputEnd := reginput;
            end;
         Succ (OPEN) .. TREOp (Ord (OPEN) + NSUBEXP - 1) : begin //###0.929
            no := ord (scan^) - ord (OPEN);
//            save := reginput;
            save := startp [no]; //###0.936
            startp [no] := reginput; //###0.936
            locPruning := False;
            If Assigned(context) Then
               Begin
                   If Not Assigned(context.Objects[contextNum]) Then
                      context.Objects[contextNum] := TVarStruct.Create;
                   VS := TVarStruct(context.Objects[contextNum]);
                   If (VS.Count > 0) And (TVarValue(VS.Objects[VS.Count - 1]).Num = no) Then
                      VV := TVarValue(VS.Objects[VS.Count - 1])
                   else
                      Begin
                         VV := TVarValue.Create(Self, no, context, contextNum);
                         If Assigned(VarNames[no]) Then
                            VS.AddObject(RegExprString(VarNames[no]), VV)
                         Else
                            VS.AddObject('', VV)
                      End;
                   VV.Add('');
                   Result := MatchPrim (VV, VV.Count - 1, next, locPruning);
               end
            Else
              If Assigned(varsp[no]) And Not (varsp[no]^ in ['+', '-', '*', '?', '!', '^', #0]) Then
                 Begin
                   If Not Assigned(valsp[no]) Then
                      valsp[no] := TVarValue.Create(Self, no, Nil, -1);
                   valsp[no].Add('');
                   Result := MatchPrim (valsp[no], valsp[no].Count - 1, next, locPruning);
                 end
              Else
                 Result := MatchPrim (context, contextNum, next, locPruning);
            Pruning := Pruning or locPruning;
            if not Result //###0.936
             then
               Begin
                 If Assigned(context) Then
                    Begin
                       VS := TVarStruct(context.Objects[contextNum]);
                       VV := TVarValue(VS.Objects[VS.Count - 1]);
                       if Assigned(VV.Objects[VV.Count - 1]) then
                          VV.Objects[VV.Count - 1].Free;
                       VV.Delete(VV.Count - 1);
                       If VV.Count = 0 Then
                          VS.Delete(VS.Count - 1);
                       If VS.Count = 0 Then
                          Begin
                            VS.Free;
                            context.Objects[contextNum] := Nil
                          End
                    end
                 Else
                   If Assigned(varsp[no]) And Not (varsp[no]^ in ['+', '-', '*', '?', '!', '^', #0]) Then
                      Begin
                        if Assigned(valsp[no].Objects[valsp[no].Count - 1]) then
                           valsp[no].Objects[valsp[no].Count - 1].Free;
                        valsp[no].Delete(valsp[no].Count - 1);
                        If valsp[no].Count = 0 Then
                           FreeAndNil(valsp[no])
                      End;
                 startp [no] := save
               End;
//            if Result and (startp [no] = nil)
//             then startp [no] := save;
             // Don't set startp if some later invocation of the same
             // parentheses already has.
            EXIT;
           end;
         Succ (CLOSE) .. TREOp (Ord (CLOSE) + NSUBEXP - 1): begin //###0.929
            no := ord (scan^) - ord (CLOSE);
//            save := reginput;
            save := endp [no]; //###0.936
            endp [no] := reginput; //###0.936

            SetLength(S, endp[no] - startp[no]);
            Move(startp[no]^, S[1], Length(S)*SizeOf(REChar));

            Result := True;
            If Assigned(context) Then
               Begin
                 context.Strings[contextNum] := S;
                 if Not Assigned(context.Objects[contextNum]) then
                    context.Objects[contextNum] := TVarStruct.Create;
                 T := TVarStruct(context.Objects[contextNum]);
                 T._First := startp[no] - fInputStart + 1;
                 T._Last := endp[no] - fInputStart;
                 if Assigned(varsp[no]) then
                    if varsp[no]^ = '&' Then
                       Begin
                         SP := varsp[no];
                         Inc(SP);

                         T.GrammarParse(VarNames[no], SP, S, startp[no], endp[no]);

                         context.Strings[contextNum] := S
                       End;
                 contextNum := context.ParentIdx;
                 context := context.Parent
               End;
            if Assigned(varsp[no]) then
               if (varsp[no]^ = '+') Or (varsp[no]^ = '-') then
                  begin
                    ref := StrToInt(varsp[no]+1);
                    if ref >= 1000 then
                       begin
                         i := (ref Div 1000) - 1;
                         j := ref Mod 1000;
                         stp := TRegExpr(valext.Objects[i]).startp[j];
                         enp := TRegExpr(valext.Objects[i]).endp[j];
                         SetLength(S1, enp - stp);
                         Move(stp^, S1[1], Length(S1)*SizeOf(REChar))
                       end
                    else
                       begin
                         SetLength(S1, endp[ref] - startp[ref]);
                         Move(startp[ref]^, S1[1], Length(S1)*SizeOf(REChar))
                       end;
                    Result := (S = S1) Xor (varsp[no]^ = '-')
                  end
               else if varsp[no]^ in ['*', '?', '!', '^'] then
                  begin
                    pcalls := TFastCalls(IntegerToTObject(Hex2Dec(varsp[no]+1)));
                    Result := False;
                    Case varsp[no]^ Of
                        '*' : Result := pcalls.Learn(db, Self, valext, valsp);
                        '?' : Result := pcalls.Unify(ENV, db, Self, valext, valsp);
                        '!' : Result := pcalls.Assert(db, Self, valext, valsp);
                        '^' : Result := pcalls.Retract(db, Self, valext, valsp);
                    End
                  end;

            locPruning := False;
            Result := Result And MatchPrim (context, contextNum, next, locPruning);
            Pruning := Pruning or locPruning;
            if not Result //###0.936
             then endp [no] := save;
//            if Result and (endp [no] = nil)
//             then endp [no] := save;
             // Don't set endp if some later invocation of the same
             // parentheses already has.
            EXIT;
           end;
         BRANCH: begin
            if (next^ <> BRANCH) // No choice.
             then next := scan + REOpSz + RENextOffSz // Avoid recursion
             else begin
               locPruning := False;
               REPEAT
                save := reginput;
                Result := MatchPrim (context, contextNum, scan + REOpSz + RENextOffSz, locPruning);
                Pruning := Pruning or locPruning;
                if Result or locPruning
                 then EXIT;
                reginput := save;
                scan := regnext (scan);
               UNTIL (scan = nil) or (scan^ <> BRANCH);
               EXIT;
              end;
           end;
         {$IFDEF ComplexBraces}
         LOOPENTRY: begin //###0.925
           no := LoopStackIdx;
           inc (LoopStackIdx);
           if LoopStackIdx > LoopStackMax then begin
             Error (reeLoopStackExceeded);
             EXIT;
            end;
           save := reginput;
           LoopStack [LoopStackIdx] := 0; // init loop counter
           locPruning := False;
           Result := MatchPrim (context, contextNum, next, locPruning); // execute LOOP
           Pruning := Pruning or locPruning;
           LoopStackIdx := no; // cleanup
           if Result or locPruning
            then EXIT;
           reginput := save;
           EXIT;
          end;
         LOOP, LOOPNG: begin //###0.940
           if LoopStackIdx <= 0 then begin
             Error (reeLoopWithoutEntry);
             EXIT;
            end;
           opnd := scan + PRENextOff (AlignToPtr(scan + REOpSz + RENextOffSz + 2 * REBracesArgSz))^;
           BracesMin := PREBracesArg (AlignToInt(scan + REOpSz + RENextOffSz))^;
           BracesMax := PREBracesArg (AlignToPtr(scan + REOpSz + RENextOffSz + REBracesArgSz))^;
           save := reginput;
           if LoopStack [LoopStackIdx] >= BracesMin then begin // Min alredy matched - we can work
              if scan^ = LOOP then begin
                 // greedy way - first try to max deep of greed ;)
                 if LoopStack [LoopStackIdx] < BracesMax then begin
                   inc (LoopStack [LoopStackIdx]);
                   no := LoopStackIdx;
                   locPruning := False;
                   Result := MatchPrim (context, contextNum, opnd, locPruning);
                   Pruning := Pruning or locPruning;
                   LoopStackIdx := no;
                   if Result or locPruning
                    then EXIT;
                   reginput := save;
                  end;
                 dec (LoopStackIdx); // Fail. May be we are too greedy? ;)
                 locPruning := False;
                 Result := MatchPrim (context, contextNum, next, locPruning);
                 Pruning := Pruning or locPruning;
                 if not Result
                  then reginput := save;
                 EXIT;
                end
               else begin
                 // non-greedy - try just now
                 locPruning := False;
                 Result := MatchPrim (context, contextNum, next, locPruning);
                 Pruning := Pruning or locPruning;
                 if Result or locPruning
                  then EXIT
                  else reginput := save; // failed - move next and try again
                 if LoopStack [LoopStackIdx] < BracesMax then begin
                   inc (LoopStack [LoopStackIdx]);
                   no := LoopStackIdx;
                   locPruning := False;
                   Result := MatchPrim (context, contextNum, opnd, locPruning);
                   Pruning := Pruning or locPruning;
                   LoopStackIdx := no;
                   if Result or locPruning
                    then EXIT;
                   reginput := save;
                  end;
                 dec (LoopStackIdx); // Failed - back up
                 EXIT;
                end
             end
            else begin // first match a min_cnt times
              inc (LoopStack [LoopStackIdx]);
              no := LoopStackIdx;
              locPruning := False;
              Result := MatchPrim (context, contextNum, opnd, locPruning);
              Pruning := Pruning or locPruning;
              LoopStackIdx := no;
              if Result or locPruning
               then EXIT;
              dec (LoopStack [LoopStackIdx]);
              reginput := save;
              EXIT;
             end;
          end;
         {$ENDIF}
         STAR, PLUS, BRACES, STARNG, PLUSNG, BRACESNG: begin
           // Lookahead to avoid useless match attempts when we know
           // what character comes next.
           nextch := #0;
           if next^ = EXACTLY
            then nextch := (next + REOpSz + RENextOffSz)^;
           BracesMax := MaxInt; // infinite loop for * and + //###0.92
           if (scan^ = STAR) or (scan^ = STARNG)
            then BracesMin := 0  // STAR
            else if (scan^ = PLUS) or (scan^ = PLUSNG)
             then BracesMin := 1 // PLUS
             else begin // BRACES
               BracesMin := PREBracesArg (AlignToPtr(scan + REOpSz + RENextOffSz))^;
               BracesMax := PREBracesArg (AlignToPtr(scan + REOpSz + RENextOffSz + REBracesArgSz))^;
              end;
           save := reginput;
           opnd := scan + REOpSz + RENextOffSz;
           if (scan^ = BRACES) or (scan^ = BRACESNG)
            then inc (opnd, 2 * REBracesArgSz);

           if (scan^ = PLUSNG) or (scan^ = STARNG) or (scan^ = BRACESNG) then begin
             // non-greedy mode
              BracesMax := regrepeat (opnd, BracesMax); // don't repeat more than BracesMax
              // Now we know real Max limit to move forward (for recursion 'back up')
              // In some cases it can be faster to check only Min positions first,
              // but after that we have to check every position separtely instead
              // of fast scannig in loop.
              no := BracesMin;
              while no <= BracesMax do begin
                reginput := save + no;
                // If it could work, try it.
                if (nextch = #0) or (reginput^ = nextch) then begin
                  {$IFDEF ComplexBraces}
                  System.Move (LoopStack, SavedLoopStack, SizeOf (LoopStack)); //###0.925
                  SavedLoopStackIdx := LoopStackIdx;
                  {$ENDIF}
                  locPruning := False;
                  if MatchPrim (context, contextNum, next, locPruning) then begin
                    Pruning := Pruning or locPruning;
                    Result := true;
                    EXIT;
                   end
                  else if locPruning then
                   begin
                     Pruning := True;
                     Result := False;
                     EXIT
                   end;
                  {$IFDEF ComplexBraces}
                  System.Move (SavedLoopStack, LoopStack, SizeOf (LoopStack));
                  LoopStackIdx := SavedLoopStackIdx;
                  {$ENDIF}
                 end;
                inc (no); // Couldn't or didn't - move forward.
               end; { of while}
              EXIT;
             end
            else begin // greedy mode
              no := regrepeat (opnd, BracesMax); // don't repeat more than max_cnt
              while no >= BracesMin do begin
                // If it could work, try it.
                if (nextch = #0) or (reginput^ = nextch) then begin
                  {$IFDEF ComplexBraces}
                  System.Move (LoopStack, SavedLoopStack, SizeOf (LoopStack)); //###0.925
                  SavedLoopStackIdx := LoopStackIdx;
                  {$ENDIF}
                  locPruning := False;
                  if MatchPrim (context, contextNum, next, locPruning) then begin
                    Pruning := Pruning or locPruning;
                    Result := true;
                    EXIT;
                   end
                  else if locPruning then
                   begin
                     Pruning := True;
                     Result := False;
                     EXIT
                   end;
                  {$IFDEF ComplexBraces}
                  System.Move (SavedLoopStack, LoopStack, SizeOf (LoopStack));
                  LoopStackIdx := SavedLoopStackIdx;
                  {$ENDIF}
                 end;
                dec (no); // Couldn't or didn't - back up.
                reginput := save + no;
               end; { of while}
              EXIT;
             end;
          end;
         EEND: begin
           Result := true;  // Success!
           EXIT;
          end;
        else begin
            Error (reeMatchPrimMemoryCorruption);
            EXIT;
          end;
        end; { of case scan^}
        scan := next;
    end; { of while scan <> nil}

  // We get here only if there's trouble -- normally "case EEND" is the
  // terminating point.
  Error (reeMatchPrimCorruptedPointers);
 end; { of function TRegExpr.MatchPrim
--------------------------------------------------------------}

{$IFDEF UseFirstCharSet} //###0.929
procedure TRegExpr.FillFirstCharSet (prog : PRegExprChar);
 var
  scan : PRegExprChar; // Current node.
  next : PRegExprChar; // Next node.
  opnd : PRegExprChar;
  min_cnt : integer;
 begin
  scan := prog;
  while scan <> nil do begin
     next := regnext (scan);
     case PREOp (scan)^ of
         BSUBEXP, BSUBEXPCI: begin //###0.938
           FirstCharSet := [#0 .. #255]; // :((( we cannot
           // optimize r.e. if it starts with back reference
           EXIT;
          end;
         BOL, BOLML: ; // EXIT; //###0.937
         EOL, EOLML: begin //###0.948 was empty in 0.947, was EXIT in 0.937
           Include (FirstCharSet, #0);
           if ModifierM
            then begin
              opnd := PRegExprChar (LineSeparators);
              while opnd^ <> #0 do begin
                Include (FirstCharSet, opnd^);
                inc (opnd);
              end;
            end;
           EXIT;
         end;
         BOUND, NOTBOUND: ; //###0.943 ?!!
         ANY, ANYML: begin // we can better define ANYML !!!
           FirstCharSet := [#0 .. #255]; //###0.930
           EXIT;
          end;
         ANYDIGIT: begin
           FirstCharSet := FirstCharSet + ['0' .. '9'];
           EXIT;
          end;
         NOTDIGIT: begin
           FirstCharSet := FirstCharSet + ([#0 .. #255] - ['0' .. '9']); //###0.948 FirstCharSet was forgotten
           EXIT;
          end;
         EXACTLYCI: begin
           Include (FirstCharSet, (scan + REOpSz + RENextOffSz)^);
           Include (FirstCharSet, InvertCase ((scan + REOpSz + RENextOffSz)^));
           EXIT;
          end;
         EXACTLY: begin
           Include (FirstCharSet, (scan + REOpSz + RENextOffSz)^);
           EXIT;
          end;
         ANYOFFULLSET: begin
           FirstCharSet := FirstCharSet + PSetOfREChar (scan + REOpSz + RENextOffSz)^;
           EXIT;
          end;
         ANYOFTINYSET: begin
           //!!!TinySet
           Include (FirstCharSet, (scan + REOpSz + RENextOffSz)^);
           Include (FirstCharSet, (scan + REOpSz + RENextOffSz + 1)^);
           Include (FirstCharSet, (scan + REOpSz + RENextOffSz + 2)^);
           // ...                                                      // up to TinySetLen
           EXIT;
          end;
         ANYBUTTINYSET: begin
           //!!!TinySet
           FirstCharSet := FirstCharSet + ([#0 .. #255] - [ //###0.948 FirstCharSet was forgotten
            (scan + REOpSz + RENextOffSz)^,
            (scan + REOpSz + RENextOffSz + 1)^,
            (scan + REOpSz + RENextOffSz + 2)^]);
           // ...                                                      // up to TinySetLen
           EXIT;
          end;
         NOTHING: ;
         COMMENT: ;
         BACK: ;
         Succ (OPEN) .. TREOp (Ord (OPEN) + NSUBEXP - 1) : begin //###0.929
            FillFirstCharSet (next);
            EXIT;
           end;
         Succ (CLOSE) .. TREOp (Ord (CLOSE) + NSUBEXP - 1): begin //###0.929
            FillFirstCharSet (next);
            EXIT;
           end;
         BRANCH: begin
            if (PREOp (next)^ <> BRANCH) // No choice.
             then next := scan + REOpSz + RENextOffSz // Avoid recursion.
             else begin
               REPEAT
                FillFirstCharSet (scan + REOpSz + RENextOffSz);
                scan := regnext (scan);
               UNTIL (scan = nil) or (PREOp (scan)^ <> BRANCH);
               EXIT;
              end;
           end;
         {$IFDEF ComplexBraces}
         LOOPENTRY: begin //###0.925
//           LoopStack [LoopStackIdx] := 0; //###0.940 line removed
           FillFirstCharSet (next); // execute LOOP
           EXIT;
          end;
         LOOP, LOOPNG: begin //###0.940
           opnd := scan + PRENextOff (AlignToPtr(scan + REOpSz + RENextOffSz + REBracesArgSz * 2))^;
           min_cnt := PREBracesArg (AlignToPtr(scan + REOpSz + RENextOffSz))^;
           FillFirstCharSet (opnd);
           if min_cnt = 0
            then FillFirstCharSet (next);
           EXIT;
          end;
         {$ENDIF}
         STAR, STARNG: //###0.940
           FillFirstCharSet (scan + REOpSz + RENextOffSz);
         PLUS, PLUSNG: begin //###0.940
           FillFirstCharSet (scan + REOpSz + RENextOffSz);
           EXIT;
          end;
         BRACES, BRACESNG: begin //###0.940
           opnd := scan + REOpSz + RENextOffSz + REBracesArgSz * 2;
           min_cnt := PREBracesArg (AlignToPtr(scan + REOpSz + RENextOffSz))^; // BRACES
           FillFirstCharSet (opnd);
           if min_cnt > 0
            then EXIT;
          end;
         EEND: begin
            FirstCharSet := [#0 .. #255]; //###0.948
            EXIT;
           end;
        else begin
            Error (reeMatchPrimMemoryCorruption);
            EXIT;
          end;
        end; { of case scan^}
        scan := next;
    end; { of while scan <> nil}
 end; { of procedure FillFirstCharSet
--------------------------------------------------------------}
{$ENDIF}

function TRegExpr.Exec (const AInputString : RegExprString) : boolean;
 begin
  InputString := AInputString;
  Result := ExecPrim (1);
 end; { of function TRegExpr.Exec
--------------------------------------------------------------}

{$IFDEF OverMeth}
{$IFNDEF FPC}
function TRegExpr.Exec : boolean;
 begin
  Result := ExecPrim (1);
 end; { of function TRegExpr.Exec
--------------------------------------------------------------}
{$ENDIF}
function TRegExpr.Exec(AOffset: PtrInt; const Anchored: Boolean): boolean;
 begin
  Result := ExecPrim (AOffset, Anchored);
 end; { of function TRegExpr.Exec
--------------------------------------------------------------}
{$ENDIF}

function TRegExpr.ExecPos (AOffset: PtrInt {$IFDEF DefParam}= 1{$ENDIF}) : boolean;
 begin
  Result := ExecPrim (AOffset);
 end; { of function TRegExpr.ExecPos
--------------------------------------------------------------}

function TRegExpr.ExecPrim(AOffset: PtrInt; const Anchored: Boolean): boolean;
 procedure ClearMatchs;
  // Clears matchs array
  var i : integer;
  begin
   for i := 0 to NSUBEXP - 1 do begin
     startp [i] := nil;
     endp [i] := nil;
     FreeAndNil(valsp[i]);
     // Clear fcalls?
    end;
    If Assigned(Env) Then
       begin
         Env.LocalWords.Clear;
         Env.LocalRels.Clear
       end;
    nExecs := 0
  end; { of procedure ClearMatchs;
..............................................................}
 function RegMatch (str : PRegExprChar) : boolean;
  // try match at specific point
  Var Pruning: Boolean;
  begin
   //###0.949 removed clearing of start\endp
   reginput := str;
   Pruning := False;
   Result := MatchPrim (Nil, -1, programm + REOpSz, Pruning);
   if Result then begin
     startp [0] := str;
     endp [0] := reginput;
    end;
  end; { of function RegMatch
..............................................................}
 var
  s : PRegExprChar;
  StartPtr: PRegExprChar;
  InputLen : PtrInt;
 begin
  Result := false; // Be paranoid...

  ClearMatchs; //###0.949
  // ensure that Match cleared either if optimization tricks or some error
  // will lead to leaving ExecPrim without actual search. That is
  // importent for ExecNext logic and so on.

  if not IsProgrammOk //###0.929
   then EXIT;

  // Check InputString presence
  if not Assigned (fInputString) then begin
    Error (reeNoInputStringSpecified);
    EXIT;
   end;

  InputLen := length (fInputString);

  //Check that the start position is not negative
  if AOffset < 1 then begin
    Error (reeOffsetMustBeGreaterThen0);
    EXIT;
   end;
  // Check that the start position is not longer than the line
  // If so then exit with nothing found
  if AOffset > (InputLen + 1) // for matching empty string after last char.
   then EXIT;

  StartPtr := fInputString + AOffset - 1;

  // If there is a "must appear" string, look for it.
  if regmust <> nil then begin
    s := StartPtr;
    REPEAT
     s := StrScan (s, regmust [0]);
     if s <> nil then begin
       if StrLComp (s, regmust, regmlen) = 0
        then BREAK; // Found it.
       inc (s);
      end;
    UNTIL Anchored Or (s = nil);
    if s = nil // Not present.
     then EXIT;
   end;

  // Mark beginning of line for ^ .
  fInputStart := fInputString;

  // Pointer to end of input stream - for
  // pascal-style string processing (may include #0)
  fInputEnd := fInputString + InputLen;

  {$IFDEF ComplexBraces}
  // no loops started
  LoopStackIdx := 0; //###0.925
  {$ENDIF}

  // Simplest case:  anchored match need be tried only once.
  if reganch <> #0 then begin
    Result := RegMatch (StartPtr);
    if Result Then
       begin
         If Assigned(ENV) Then
            ENV.AcceptLocalWordsRels;
         Inc(nExecs)
       end;
    EXIT;
   end;

  // Messy cases:  unanchored match.
  s := StartPtr;
  if regstart <> #0 then // We know what char it must start with.
    REPEAT
     s := StrScan (s, regstart);
     if s <> nil then begin
       Result := RegMatch (s);
       if Result Then
          begin
            If Assigned(ENV) Then
               ENV.AcceptLocalWordsRels;
            Inc(nExecs);
          end;
       if Result
        then EXIT
        else ClearMatchs; //###0.949
       inc (s);
      end;
    UNTIL Anchored Or (s = nil)
   else begin // We don't - general case.
     repeat //###0.948
       {$IFDEF UseFirstCharSet}
       if s^ in FirstCharSet
        then Result := RegMatch (s);
       {$ELSE}
       Result := RegMatch (s);
       {$ENDIF}
       if Result Then
          begin
            If Assigned(ENV) Then
               ENV.AcceptLocalWordsRels;
            Inc(nExecs);
          end;
       if Result or (s^ = #0) // Exit on a match or after testing the end-of-string.
        then EXIT
        else ClearMatchs; //###0.949
       inc (s);
     until Anchored;
(*  optimized and fixed by Martin Fuller - empty strings
    were not allowed to pass through in UseFirstCharSet mode
     {$IFDEF UseFirstCharSet} //###0.929
     while s^ <> #0 do begin
       if s^ in FirstCharSet
        then Result := RegMatch (s);
       if Result
        then EXIT;
       inc (s);
      end;
     {$ELSE}
     REPEAT
      Result := RegMatch (s);
      if Result
       then EXIT;
      inc (s);
     UNTIL s^ = #0;
     {$ENDIF}
*)
    end;
  // Failure
 end; { of function TRegExpr.ExecPrim
--------------------------------------------------------------}

function TRegExpr.ExecNext(const Anchored: Boolean): boolean;
 var offset : PtrInt;
 begin
  Result := false;
  if not Assigned (startp[0]) or not Assigned (endp[0]) then begin
    Error (reeExecNextWithoutExec);
    EXIT;
   end;
//  Offset := MatchPos [0] + MatchLen [0];
//  if MatchLen [0] = 0
  Offset := endp [0] - fInputString + 1; //###0.929
  if endp [0] = startp [0] //###0.929
   then inc (Offset); // prevent infinite looping if empty string match r.e.
  Result := ExecPrim (Offset, Anchored);
 end; { of function TRegExpr.ExecNext
--------------------------------------------------------------}

function TRegExpr.GetInputString : RegExprString;
 begin
  if not Assigned (fInputString) then begin
    Error (reeGetInputStringWithoutInputString);
    EXIT;
   end;
  Result := fInputString;
 end; { of function TRegExpr.GetInputString
--------------------------------------------------------------}

procedure TRegExpr.RewindAndClear;

var i : Integer;
begin
 for i := 0 to NSUBEXP - 1 do begin
   startp [i] := nil;
   endp [i] := nil;
   FreeAndNil(valsp[i])
  end;
 If Assigned(Env) Then
    begin
      Env.LocalWords.Clear;
      Env.LocalRels.Clear
    end;
 nExecs := 0
end;

function TRegExpr.FindNode(ID: Integer): TVarStruct;

var i : Integer;
begin
  for i := 0 to NSUBEXP - 1 do
      if Assigned(valsp[i]) Then
         begin
           Result := valsp[i].FindNode(ID);
           If Assigned(Result) Then
              Exit
         end;
  Result := Nil
end;

procedure TRegExpr.SetInputString (const AInputString : RegExprString);
 var
  Len : PtrInt;
 begin
  // clear Match* - before next Exec* call it's undefined
  RewindAndClear;

  // need reallocation of input string buffer ?
  Len := length (AInputString);
  ReAllocMem(fInputString,(Len + 1) * SizeOf (REChar));
  // copy input string into buffer
  if Len>0 then
    System.Move(AInputString[1],fInputString^,(Len+1)* SizeOf (REChar)) // with #0
  else
    fInputString[0]:=#0;

  {
  fInputString : string;
  fInputStart, fInputEnd : PRegExprChar;

  SetInputString:
  fInputString := AInputString;
  UniqueString (fInputString);
  fInputStart := PChar (fInputString);
  Len := length (fInputString);
  fInputEnd := PRegExprChar (integer (fInputStart) + Len); ??
  !! startp/endp все равно будет опасно использовать ?
  }
 end; { of procedure TRegExpr.SetInputString
--------------------------------------------------------------}

procedure TRegExpr.SetLineSeparators (const AStr : RegExprString);
 begin
  if AStr <> fLineSeparators then begin
    fLineSeparators := AStr;
    InvalidateProgramm;
   end;
 end; { of procedure TRegExpr.SetLineSeparators
--------------------------------------------------------------}

procedure TRegExpr.SetLinePairedSeparator (const AStr : RegExprString);
 begin
  if length (AStr) = 2 then begin
     if AStr [1] = AStr [2] then begin
      // it's impossible for our 'one-point' checking to support
      // two chars separator for identical chars
       Error (reeBadLinePairedSeparator);
       EXIT;
      end;
     if not fLinePairedSeparatorAssigned
      or (AStr [1] <> fLinePairedSeparatorHead)
      or (AStr [2] <> fLinePairedSeparatorTail) then begin
       fLinePairedSeparatorAssigned := true;
       fLinePairedSeparatorHead := AStr [1];
       fLinePairedSeparatorTail := AStr [2];
       InvalidateProgramm;
      end;
    end
   else if length (AStr) = 0 then begin
     if fLinePairedSeparatorAssigned then begin
       fLinePairedSeparatorAssigned := false;
       InvalidateProgramm;
      end;
    end
   else Error (reeBadLinePairedSeparator);
 end; { of procedure TRegExpr.SetLinePairedSeparator
--------------------------------------------------------------}

function TRegExpr.GetLinePairedSeparator : RegExprString;
 begin
  if fLinePairedSeparatorAssigned then begin
     {$IFDEF UniCode}
     // Here is some UniCode 'magic'
     // If You do know better decision to concatenate
     // two WideChars, please, let me know!
     Result := fLinePairedSeparatorHead; //###0.947
     Result := Result + fLinePairedSeparatorTail;
     {$ELSE}
     Result := fLinePairedSeparatorHead + fLinePairedSeparatorTail;
     {$ENDIF}
    end
   else Result := '';
 end; { of function TRegExpr.GetLinePairedSeparator
--------------------------------------------------------------}

function TRegExpr.Substitute (const ATemplate : RegExprString) : RegExprString;
// perform substitutions after a regexp match
// completely rewritten in 0.929
type
  TSubstMode = (smodeNormal, smodeOneUpper, smodeOneLower, smodeAllUpper,
                smodeAllLower);
var
  TemplateLen : PtrInt;
  TemplateBeg, TemplateEnd : PRegExprChar;
  p, p0, p1, ResultPtr : PRegExprChar;
  ResultLen : PtrInt;
  n : PtrInt;
  Ch : REChar;
  Mode: TSubstMode;
  LineEnd: String = LineEnding;

  function ParseVarName (var APtr : PRegExprChar) : PtrInt;
  // extract name of variable (digits, may be enclosed with
  // curly braces) from APtr^, uses TemplateEnd !!!
  const
   Digits = ['0' .. '9'];
  var
   p : PRegExprChar;
   Delimited : boolean;
  begin
   Result := 0;
   p := APtr;
   Delimited := (p < TemplateEnd) and (p^ = '{');
   if Delimited
    then inc (p); // skip left curly brace
   if (p < TemplateEnd) and (p^ = '&')
    then inc (p) // this is '$&' or '${&}'
    else
     while (p < TemplateEnd) and
      {$IFDEF UniCode} //###0.935
      (ord (p^) < 256) and (char (p^) in Digits)
      {$ELSE}
      (p^ in Digits)
      {$ENDIF}
       do begin
       Result := Result * 10 + (ord (p^) - ord ('0')); //###0.939
       inc (p);
      end;
   if Delimited then
    if (p < TemplateEnd) and (p^ = '}')
     then inc (p) // skip right curly brace
     else p := APtr; // isn't properly terminated
   if p = APtr
    then Result := -1; // no valid digits found or no right curly brace
   APtr := p;
  end;

begin
  // Check programm and input string
  if not IsProgrammOk
   then EXIT;
  if not Assigned (fInputString) then begin
    Error (reeNoInputStringSpecified);
    EXIT;
   end;
  // Prepare for working
  TemplateLen := length (ATemplate);
  if TemplateLen = 0 then begin // prevent nil pointers
    Result := '';
    EXIT;
   end;
  TemplateBeg := pointer (ATemplate);
  TemplateEnd := TemplateBeg + TemplateLen;
  // Count result length for speed optimization.
  ResultLen := 0;
  p := TemplateBeg;
  while p < TemplateEnd do begin
    Ch := p^;
    inc (p);
    if Ch = '$'
     then n := ParseVarName (p)
     else n := -1;
    if n >= 0 then begin
      if (n < NSUBEXP) and Assigned (startp [n]) and Assigned (endp [n])
        then inc (ResultLen, endp [n] - startp [n]);
    end
    else begin
      if (Ch = EscChar) and (p < TemplateEnd) then begin // quoted or special char followed
        Ch := p^;
        inc (p);
        case Ch of
          'n' : inc(ResultLen, Length(LineEnding));
          'u', 'l', 'U', 'L': {nothing};
          else inc(ResultLen);
        end;
      end
      else
        inc(ResultLen);
    end;
  end;
  // Get memory. We do it once and it significant speed up work !
  if ResultLen = 0 then begin
    Result := '';
    EXIT;
   end;
  //SetString (Result, nil, ResultLen);
  SetLength(Result,ResultLen);
  // Fill Result
  ResultPtr := pointer (Result);
  p := TemplateBeg;
  Mode := smodeNormal;
  while p < TemplateEnd do begin
    Ch := p^;
    p0 := p;
    inc (p);
    p1 := p;
    if Ch = '$'
     then n := ParseVarName (p)
     else n := -1;
    if (n >= 0) then begin
      p0 := startp[n];
      p1 := endp[n];
      if (n >= NSUBEXP) or not Assigned (p0) or not Assigned (endp [n]) then
        p1 := p0; // empty
    end
    else begin
      if (Ch = EscChar) and (p < TemplateEnd) then begin // quoted or special char followed
        Ch := p^;
        inc (p);
        case Ch of
          'n' : begin
              p0 := @LineEnd[1];
              p1 := p0 + Length(LineEnding);
            end;
          'l' : begin
              Mode := smodeOneLower;
              p1 := p0;
            end;
          'L' : begin
              Mode := smodeAllLower;
              p1 := p0;
            end;
          'u' : begin
              Mode := smodeOneUpper;
              p1 := p0;
            end;
          'U' : begin
              Mode := smodeAllUpper;
              p1 := p0;
            end;
          else
            begin
              inc(p0);
              inc(p1);
            end;
        end;
      end
    end;
    if p0 < p1 then begin
      while p0 < p1 do begin
        case Mode of
          smodeOneLower, smodeAllLower:
            begin
              Ch := p0^;
              if Ch < #128 then
                Ch := AnsiLowerCase(Ch)[1];
              ResultPtr^ := Ch;
              if Mode = smodeOneLower then
                Mode := smodeNormal;
            end;
          smodeOneUpper, smodeAllUpper:
            begin
              Ch := p0^;
              if Ch < #128 then
                Ch := AnsiUpperCase(Ch)[1];
              ResultPtr^ := Ch;
              if Mode = smodeOneUpper then
                Mode := smodeNormal;
            end;
          else
            ResultPtr^ := p0^;
        end;
        inc (ResultPtr);
        inc (p0);
      end;
      Mode := smodeNormal;
    end;
  end;
end; { of function TRegExpr.Substitute
--------------------------------------------------------------}

procedure TRegExpr.Split (AInputStr : RegExprString; APieces : TStrings);
 var PrevPos : PtrInt;
 begin
  PrevPos := 1;
  if Exec (AInputStr) then
   REPEAT
    APieces.Add (System.Copy (AInputStr, PrevPos, MatchPos [0] - PrevPos));
    PrevPos := MatchPos [0] + MatchLen [0];
   UNTIL not ExecNext;
  APieces.Add (System.Copy (AInputStr, PrevPos, MaxInt)); // Tail
 end; { of procedure TRegExpr.Split
--------------------------------------------------------------}

function TRegExpr.Replace (AInputStr : RegExprString; const AReplaceStr : RegExprString;
      AUseSubstitution : boolean{$IFDEF DefParam}= False{$ENDIF}) : RegExprString;
 var
  PrevPos : PtrInt;
 begin
  Result := '';
  PrevPos := 1;
  if Exec (AInputStr) then
   REPEAT
    Result := Result + System.Copy (AInputStr, PrevPos,
      MatchPos [0] - PrevPos);
    if AUseSubstitution //###0.946
    then Result := Result + Substitute (AReplaceStr)
    else Result := Result + AReplaceStr;
    PrevPos := MatchPos [0] + MatchLen [0];
   UNTIL not ExecNext;
  Result := Result + System.Copy (AInputStr, PrevPos, MaxInt); // Tail
 end; { of function TRegExpr.Replace
--------------------------------------------------------------}

function TRegExpr.ReplaceEx (AInputStr : RegExprString;
      AReplaceFunc : TRegExprReplaceFunction)
     : RegExprString;
 var
  PrevPos : PtrInt;
 begin
  Result := '';
  PrevPos := 1;
  if Exec (AInputStr) then
   REPEAT
    Result := Result + System.Copy (AInputStr, PrevPos,
      MatchPos [0] - PrevPos)
     + AReplaceFunc (Self);
    PrevPos := MatchPos [0] + MatchLen [0];
   UNTIL not ExecNext;
  Result := Result + System.Copy (AInputStr, PrevPos, MaxInt); // Tail
 end; { of function TRegExpr.ReplaceEx
--------------------------------------------------------------}

function TRegExpr.ExportPredicates(const MacroID: String): String;

Var i: integer;
    id: integer;
    L: String;
    Dependent: TByteSet;
    Temp: TByteSet;
begin
  Result := 'model(''' + MacroID + '''):-';
  id := 0;
  L := '';
  Dependent := [];
  for i := 0 to NSUBEXP - 1 do
      if Assigned(varsp[i]) And Assigned(valsp[i]) And Not (varsp[i]^ in ['+', '-', '*', '?', '!', '^', #0]) then
         begin
           Temp := [];
           valsp[i].Mark(Temp);
           Exclude(Temp, valsp[i].Num);
           Dependent := Dependent + Temp
         end;
  for i := 0 to NSUBEXP - 1 do
      if Assigned(varsp[i]) And Assigned(valsp[i]) And Not (varsp[i]^ in ['+', '-', '*', '?', '!', '^', #0]) then
         if Not (valsp[i].Num in Dependent) Then
            AppendStr(Result, valsp[i].ExportPredicates(MacroID, Self, id, L));
  L := '[' + L;
  if Length(L) > 1 Then L[Length(L)] := ']'
  else L := L + ']';
  RootID := id;
  AppendStr(Result, 'assertz(var(''' + MacroID + ''',' + IntToStr(id) + ',' + '''root''' + ','''',' + L + ')).' + #$0D#$0A)
end;

function TRegExpr.ExportXML: String;

 Var i: integer;
     Dependent: TByteSet;
     Temp: TByteSet;
 begin
   Result := '<root>';
   Dependent := [];
   for i := 0 to NSUBEXP - 1 do
       if Assigned(varsp[i]) And Assigned(valsp[i]) And Not (varsp[i]^ in ['+', '-', '*', '?', '!', '^', #0]) then
          begin
            Temp := [];
            valsp[i].Mark(Temp);
            Exclude(Temp, valsp[i].Num);
            Dependent := Dependent + Temp
          end;
   for i := 0 to NSUBEXP - 1 do
       if Assigned(varsp[i]) And Assigned(valsp[i]) And Not (varsp[i]^ in ['+', '-', '*', '?', '!', '^', #0]) then
          if Not (valsp[i].Num in Dependent) Then
             AppendStr(Result, valsp[i].ExportXML(Self));
   AppendStr(Result, '</root>' + #$0D#$0A)
 end;

function TRegExpr.ExportDB: String;
begin
  If Assigned(db) Then
     Result := db.ExportDB()
  Else
     Result := ''
end;

function TRegExpr.ExportPascalDB(var out: TStringList; const Offs, vDB: String
  ): Boolean;
begin
  If Assigned(db) Then
     Result := db.ExportPascalDB(out, Offs, vDB)
  Else
     Result := True
end;

procedure TRegExpr.AddExtRegExpr(const Name: String; const R: TRegExpr);
begin
  valext.AddObject(Name, R)
end;


{$IFDEF OverMeth}
function TRegExpr.Replace (AInputStr : RegExprString;
      AReplaceFunc : TRegExprReplaceFunction)
     : RegExprString;
 begin
  {$IFDEF FPC}Result:={$ENDIF}ReplaceEx (AInputStr, AReplaceFunc);
 end; { of function TRegExpr.Replace
--------------------------------------------------------------}
{$ENDIF}

{=============================================================}
{====================== Debug section ========================}
{=============================================================}

{$IFDEF RegExpPCodeDump}
function TRegExpr.DumpOp(op: REChar): RegExprString;
// printable representation of opcode
 begin
  case op of
    BOL:          Result := 'BOL';
    EOL:          Result := 'EOL';
    BOLML:        Result := 'BOLML';
    EOLML:        Result := 'EOLML';
    BOUND:        Result := 'BOUND'; //###0.943
    NOTBOUND:     Result := 'NOTBOUND'; //###0.943
    ANY:          Result := 'ANY';
    ANYML:        Result := 'ANYML'; //###0.941
    ANYLETTER:    Result := 'ANYLETTER';
    NOTLETTER:    Result := 'NOTLETTER';
    ANYDIGIT:     Result := 'ANYDIGIT';
    NOTDIGIT:     Result := 'NOTDIGIT';
    ANYSPACE:     Result := 'ANYSPACE';
    NOTSPACE:     Result := 'NOTSPACE';
    ANYOF:        Result := 'ANYOF';
    ANYBUT:       Result := 'ANYBUT';
    ANYOFCI:      Result := 'ANYOF/CI';
    ANYBUTCI:     Result := 'ANYBUT/CI';
    BRANCH:       Result := 'BRANCH';
    EXACTLY:      Result := 'EXACTLY';
    EXACTLYCI:    Result := 'EXACTLY/CI';
    NOTHING:      Result := 'NOTHING';
    COMMENT:      Result := 'COMMENT';
    BACK:         Result := 'BACK';
    EEND:         Result := 'END';
    BSUBEXP:      Result := 'BSUBEXP';
    BSUBEXPCI:    Result := 'BSUBEXP/CI';
    Succ (OPEN) .. TREOp (Ord (OPEN) + NSUBEXP - 1): //###0.929
                  Result := Format ('OPEN[%d]', [ord (op) - ord (OPEN)]);
    Succ (CLOSE) .. TREOp (Ord (CLOSE) + NSUBEXP - 1): //###0.929
                  Result := Format ('CLOSE[%d]', [ord (op) - ord (CLOSE)]);
    STAR:         Result := 'STAR';
    PLUS:         Result := 'PLUS';
    BRACES:       Result := 'BRACES';
    {$IFDEF ComplexBraces}
    LOOPENTRY:    Result := 'LOOPENTRY'; //###0.925
    LOOP:         Result := 'LOOP'; //###0.925
    LOOPNG:       Result := 'LOOPNG'; //###0.940
    {$ENDIF}
    ANYOFTINYSET: Result:= 'ANYOFTINYSET';
    ANYBUTTINYSET:Result:= 'ANYBUTTINYSET';
    {$IFDEF UseSetOfChar} //###0.929
    ANYOFFULLSET: Result:= 'ANYOFFULLSET';
    {$ENDIF}
    STARNG:       Result := 'STARNG'; //###0.940
    PLUSNG:       Result := 'PLUSNG'; //###0.940
    BRACESNG:     Result := 'BRACESNG'; //###0.940
    else Error (reeDumpCorruptedOpcode);
   end; {of case op}
  Result := ':' + Result;
 end; { of function TRegExpr.DumpOp
--------------------------------------------------------------}

function TRegExpr.Dump : RegExprString;
// dump a regexp in vaguely comprehensible form
 var
  s : PRegExprChar;
  op : TREOp; // Arbitrary non-END op.
  next : PRegExprChar;
  i : PtrInt;
  Diff : PtrInt;
{$IFDEF UseSetOfChar} //###0.929
  Ch : REChar;
{$ENDIF}
 begin
  if not IsProgrammOk //###0.929
   then EXIT;

  op := EXACTLY;
  Result := '';
  s := programm + REOpSz;
  while op <> EEND do begin // While that wasn't END last time...
     op := s^;
     Result := Result + Format ('%2d%s', [s - programm, DumpOp (s^)]); // Where, what.
     next := regnext (s);
     if next = nil // Next ptr.
      then Result := Result + ' (0)'
      else begin
        if next > s //###0.948 PWideChar subtraction workaround (see comments in Tail method for details)
         then Diff := next - s
         else Diff := - (s - next);
        Result := Result + Format (' (%d) ', [(s - programm) + Diff]);
       end;
     inc (s, REOpSz + RENextOffSz);
     if (op = ANYOF) or (op = ANYOFCI) or (op = ANYBUT) or (op = ANYBUTCI)
        or (op = EXACTLY) or (op = EXACTLYCI) then begin
         // Literal string, where present.
         while s^ <> #0 do begin
           Result := Result + s^;
           inc (s);
          end;
         inc (s);
      end;
     if (op = ANYOFTINYSET) or (op = ANYBUTTINYSET) then begin
       for i := 1 to TinySetLen do begin
         Result := Result + s^;
         inc (s);
        end;
      end;
     if (op = BSUBEXP) or (op = BSUBEXPCI) then begin
       Result := Result + ' \' + IntToStr (Ord (s^));
       inc (s);
      end;
     {$IFDEF UseSetOfChar} //###0.929
     if op = ANYOFFULLSET then begin
       for Ch := #0 to #255 do
        if Ch in PSetOfREChar (s)^ then
         if Ch < ' '
          then Result := Result + '#' + IntToStr (Ord (Ch)) //###0.936
          else Result := Result + Ch;
       inc (s, SizeOf (TSetOfREChar));
      end;
     {$ENDIF}
     if (op = BRACES) or (op = BRACESNG) then begin //###0.941
       // show min/max argument of BRACES operator
       Result := Result + Format ('{%d,%d}', [PREBracesArg (AlignToInt(s))^, PREBracesArg (AlignToInt(s + REBracesArgSz))^]);
       inc (s, REBracesArgSz * 2);
      end;
     {$IFDEF ComplexBraces}
     if (op = LOOP) or (op = LOOPNG) then begin //###0.940
       Result := Result + Format (' -> (%d) {%d,%d}', [
        (s - programm - (REOpSz + RENextOffSz)) + PRENextOff (AlignToPtr(s + 2 * REBracesArgSz))^,
        PREBracesArg (AlignToInt(s))^, PREBracesArg (AlignToInt(s + REBracesArgSz))^]);
       inc (s, 2 * REBracesArgSz + RENextOffSz);
      end;
     {$ENDIF}
     Result := Result + #$d#$a;
   end; { of while}

  // Header fields of interest.

  if regstart <> #0
   then Result := Result + 'start ' + regstart;
  if reganch <> #0
   then Result := Result + 'anchored ';
  if regmust <> nil
   then Result := Result + 'must have ' + regmust;
  {$IFDEF UseFirstCharSet} //###0.929
  Result := Result + #$d#$a'FirstCharSet:';
  for Ch := #0 to #255 do
   if Ch in FirstCharSet
    then begin
      if Ch < ' '
       then Result := Result + '#' + IntToStr(Ord(Ch)) //###0.948
       else Result := Result + Ch;
    end;
  {$ENDIF}
  Result := Result + #$d#$a;
 end; { of function TRegExpr.Dump
--------------------------------------------------------------}
{$ENDIF}

{$IFDEF reRealExceptionAddr}
{$OPTIMIZATION ON}
// ReturnAddr works correctly only if compiler optimization is ON
// I placed this method at very end of unit because there are no
// way to restore compiler optimization flag ...
{$ENDIF}
procedure TRegExpr.Error (AErrorID : integer);
{$IFDEF reRealExceptionAddr}
 function ReturnAddr : pointer; //###0.938
  asm
   mov  eax,[ebp+4]
  end;
{$ENDIF}
 var
  e : ERegExpr;
 begin
  fLastError := AErrorID; // dummy stub - useless because will raise exception
  if AErrorID < 1000 // compilation error ?
   then e := ERegExpr.Create (ErrorMsg (AErrorID) // yes - show error pos
             + ' (pos ' + IntToStr (CompilerErrorPos) + ')')
   else e := ERegExpr.Create (ErrorMsg (AErrorID));
  e.ErrorCode := AErrorID;
  e.CompilerErrorPos := CompilerErrorPos;
  raise e
   {$IFDEF reRealExceptionAddr}
   At ReturnAddr; //###0.938
   {$ENDIF}
 end; { of procedure TRegExpr.Error
--------------------------------------------------------------}

(*
  PCode persistence:
   FirstCharSet
   programm, regsize
   regstart // -> programm
   reganch // -> programm
   regmust, regmlen // -> programm
   fExprIsCompiled
*)

// be carefull - placed here code will be always compiled with
// compiler optimization flag

Var F: Integer;

initialization
{$IFDEF FPC}
 RegExprInvertCaseFunction := TRegExpr.InvertCaseFunction;

{$ENDIF}

 Transformers := TStringList.Create;

finalization
 If Assigned(Transformers) Then
    begin
      For F := 0 To Transformers.Count - 1 Do
          FreeLibrary(TLibHandle(Transformers.Objects[F]));
      Transformers.Free
    end;

end.

