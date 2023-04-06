
#include <map>


// Generated from ReentLexer.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  ReentLexer : public antlr4::Lexer {
public:
  enum {
    IntegerLiteral = 1, CharacterLiteral = 2, FloatingLiteral = 3, StringLiteral = 4, 
    BooleanLiteral = 5, PointerLiteral = 6, UserDefinedLiteral = 7, PlanPragma = 8, 
    DoNotCheck = 9, BlockComment = 10, OtherPragma = 11, Line = 12, MultiLineMacro = 13, 
    Directive = 14, Alignas = 15, Alignof = 16, Asm = 17, Auto = 18, Begin = 19, 
    Bool = 20, Break = 21, Case = 22, Catch = 23, Cfunnel = 24, Chain = 25, 
    Char = 26, Char16 = 27, Char32 = 28, Cilk_for = 29, Cilk_for_ = 30, 
    Cilk_spawn = 31, Cilk_spawn_ = 32, Cilk_sync = 33, Cilk_sync_ = 34, 
    Class = 35, Clear_plan = 36, Clustered = 37, Common = 38, Const = 39, 
    Constexpr = 40, Const_cast = 41, Continue = 42, Csem = 43, Cvar = 44, 
    Decltype = 45, Default = 46, Delete = 47, Depends = 48, Do = 49, Double = 50, 
    Dynamic_cast = 51, Else = 52, End = 53, Enum = 54, Explicit = 55, Export = 56, 
    Extern = 57, False_ = 58, Final = 59, Float = 60, For = 61, Friend = 62, 
    Funnel = 63, Global = 64, Gpu = 65, Goto = 66, GpuGlobal = 67, GpuLocal = 68, 
    Id = 69, If = 70, In = 71, Inline = 72, Int = 73, Local = 74, Long = 75, 
    MarkPreCondition = 76, MarkState = 77, Markupdef = 78, Mutable = 79, 
    Namespace = 80, New = 81, Noexcept = 82, Nullptr = 83, Operator = 84, 
    Out = 85, Override = 86, Plan = 87, Plan_atomize = 88, Plan_chain = 89, 
    Plan_critical = 90, Plan_first = 91, Plan_get_first = 92, Plan_get_last = 93, 
    Plan_group_atomize = 94, Plan_group_first = 95, Plan_group_last = 96, 
    Plan_group_parallelize = 97, Plan_group_soft_atomize = 98, Plan_group_vectorize = 99, 
    Plan_item_type = 100, Plan_last = 101, Plan_parallel_chain = 102, Plan_parallel_reverse = 103, 
    Plan_register = 104, Plan_registered_barrier = 105, Plan_stop = 106, 
    Plan_topology = 107, Plan_type = 108, Private = 109, Protected = 110, 
    Public = 111, Reduction = 112, Reenterable = 113, Register = 114, Reinterpret_cast = 115, 
    Reset = 116, Return = 117, Set = 118, Short = 119, Signed = 120, Sizeof = 121, 
    Soft_transact_array = 122, Soft_transact_in = 123, Soft_transact_out = 124, 
    Soft_transact_var = 125, Static = 126, Static_assert = 127, Static_cast = 128, 
    Struct = 129, Switch = 130, Template = 131, This = 132, Thread_local = 133, 
    Throw = 134, Throw_first = 135, Throw_last = 136, Transaction_atomic = 137, 
    True_ = 138, Try = 139, Typedef = 140, Typeid_ = 141, Typename_ = 142, 
    Union = 143, Unsigned = 144, Using = 145, Vectorized = 146, Virtual = 147, 
    Void = 148, Volatile = 149, Wchar = 150, While = 151, At = 152, Dollar = 153, 
    Is = 154, LeftParen = 155, RightParen = 156, LeftBracket = 157, RightBracket = 158, 
    LeftBrace = 159, RightBrace = 160, Underscore = 161, Plus = 162, Minus = 163, 
    Star = 164, Div = 165, Mod = 166, Caret = 167, And = 168, Or = 169, 
    Tilde = 170, Not = 171, Assign = 172, Less = 173, Greater = 174, PlusAssign = 175, 
    MinusAssign = 176, StarAssign = 177, DivAssign = 178, ModAssign = 179, 
    XorAssign = 180, AndAssign = 181, OrAssign = 182, LeftShiftAssign = 183, 
    RightShiftAssign = 184, Equal = 185, NotEqual = 186, LessEqual = 187, 
    GreaterEqual = 188, AndAnd = 189, OrOr = 190, PlusPlus = 191, MinusMinus = 192, 
    Comma = 193, ArrowStar = 194, Arrow = 195, Question = 196, Colon = 197, 
    Doublecolon = 198, Semi = 199, Dot = 200, DotStar = 201, Ellipsis = 202, 
    Identifier = 203, DecimalLiteral = 204, OctalLiteral = 205, HexadecimalLiteral = 206, 
    BinaryLiteral = 207, Integersuffix = 208, UserDefinedIntegerLiteral = 209, 
    UserDefinedFloatingLiteral = 210, UserDefinedStringLiteral = 211, UserDefinedCharacterLiteral = 212, 
    Whitespace = 213, Newline = 214, LineComment = 215
  };

  explicit ReentLexer(antlr4::CharStream *input);
  ~ReentLexer();


  	std::map<int, std::string> __lines;

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

  virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;
  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.
  void LineAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.
  bool DoNotCheckSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool LineSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

