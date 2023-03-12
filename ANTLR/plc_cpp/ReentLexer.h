
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
    Char = 26, Char16 = 27, Char32 = 28, Class = 29, Clear_plan = 30, Clustered = 31, 
    Common = 32, Const = 33, Constexpr = 34, Const_cast = 35, Continue = 36, 
    Csem = 37, Cvar = 38, Decltype = 39, Default = 40, Delete = 41, Depends = 42, 
    Do = 43, Double = 44, Dynamic_cast = 45, Else = 46, End = 47, Enum = 48, 
    Explicit = 49, Export = 50, Extern = 51, False_ = 52, Final = 53, Float = 54, 
    For = 55, Friend = 56, Funnel = 57, Global = 58, Gpu = 59, Goto = 60, 
    GpuGlobal = 61, GpuLocal = 62, Id = 63, If = 64, In = 65, Inline = 66, 
    Int = 67, Local = 68, Long = 69, MarkPreCondition = 70, MarkState = 71, 
    Markupdef = 72, Mutable = 73, Namespace = 74, New = 75, Noexcept = 76, 
    Nullptr = 77, Operator = 78, Out = 79, Override = 80, Plan = 81, Plan_atomize = 82, 
    Plan_chain = 83, Plan_critical = 84, Plan_first = 85, Plan_get_first = 86, 
    Plan_get_last = 87, Plan_group_atomize = 88, Plan_group_first = 89, 
    Plan_group_last = 90, Plan_group_parallelize = 91, Plan_group_soft_atomize = 92, 
    Plan_group_vectorize = 93, Plan_item_type = 94, Plan_last = 95, Plan_parallel_chain = 96, 
    Plan_parallel_reverse = 97, Plan_register = 98, Plan_registered_barrier = 99, 
    Plan_stop = 100, Plan_topology = 101, Plan_type = 102, Private = 103, 
    Protected = 104, Public = 105, Reduction = 106, Reenterable = 107, Register = 108, 
    Reinterpret_cast = 109, Reset = 110, Return = 111, Set = 112, Short = 113, 
    Signed = 114, Sizeof = 115, Soft_transact_array = 116, Soft_transact_in = 117, 
    Soft_transact_out = 118, Soft_transact_var = 119, Static = 120, Static_assert = 121, 
    Static_cast = 122, Struct = 123, Switch = 124, Template = 125, This = 126, 
    Thread_local = 127, Throw = 128, Throw_first = 129, Throw_last = 130, 
    Transaction_atomic = 131, True_ = 132, Try = 133, Typedef = 134, Typeid_ = 135, 
    Typename_ = 136, Union = 137, Unsigned = 138, Using = 139, Vectorized = 140, 
    Virtual = 141, Void = 142, Volatile = 143, Wchar = 144, While = 145, 
    At = 146, Dollar = 147, Is = 148, LeftParen = 149, RightParen = 150, 
    LeftBracket = 151, RightBracket = 152, LeftBrace = 153, RightBrace = 154, 
    Underscore = 155, Plus = 156, Minus = 157, Star = 158, Div = 159, Mod = 160, 
    Caret = 161, And = 162, Or = 163, Tilde = 164, Not = 165, Assign = 166, 
    Less = 167, Greater = 168, PlusAssign = 169, MinusAssign = 170, StarAssign = 171, 
    DivAssign = 172, ModAssign = 173, XorAssign = 174, AndAssign = 175, 
    OrAssign = 176, LeftShiftAssign = 177, RightShiftAssign = 178, Equal = 179, 
    NotEqual = 180, LessEqual = 181, GreaterEqual = 182, AndAnd = 183, OrOr = 184, 
    PlusPlus = 185, MinusMinus = 186, Comma = 187, ArrowStar = 188, Arrow = 189, 
    Question = 190, Colon = 191, Doublecolon = 192, Semi = 193, Dot = 194, 
    DotStar = 195, Ellipsis = 196, Identifier = 197, DecimalLiteral = 198, 
    OctalLiteral = 199, HexadecimalLiteral = 200, BinaryLiteral = 201, Integersuffix = 202, 
    UserDefinedIntegerLiteral = 203, UserDefinedFloatingLiteral = 204, UserDefinedStringLiteral = 205, 
    UserDefinedCharacterLiteral = 206, Whitespace = 207, Newline = 208, 
    LineComment = 209
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

