
#include <map>


// Generated from ReentPreLexer.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  ReentPreLexer : public antlr4::Lexer {
public:
  enum {
    Regexp_fragment = 1, Regexp_set = 2, IntegerLiteral = 3, CharacterLiteral = 4, 
    FloatingLiteral = 5, StringLiteral = 6, EmptyAtom = 7, BooleanLiteral = 8, 
    PointerLiteral = 9, UserDefinedLiteral = 10, DefModule = 11, DefMemoization = 12, 
    DoNotCheck = 13, DefOtherPragma = 14, PreprocPasses = 15, AddScan = 16, 
    Scan = 17, AddParse = 18, Parse = 19, DefPattern = 20, Line = 21, MultiLineMacro = 22, 
    Directive = 23, AtValue = 24, Conditions = 25, Controlled = 26, Div_ = 27, 
    False_ = 28, Feed_forward = 29, GetText = 30, Goal = 31, Lin_extrapolator = 32, 
    Mgua = 33, Mod_ = 34, Nullptr = 35, Regexp_analyze = 36, Regexp_begin = 37, 
    Regexp_end = 38, Regexp_parallel = 39, Regexp_sequential = 40, Rem = 41, 
    True_ = 42, Plc_regexp_var = 43, Plc_regexp_equal = 44, Plc_regexp_not_equal = 45, 
    Plc_regexp_query = 46, LeftParen = 47, RightParen = 48, LeftBracket = 49, 
    RightBracket = 50, LeftBrace = 51, RightBrace = 52, AssignGreater = 53, 
    DivDiv = 54, Pound = 55, And_ = 56, Or_ = 57, At = 58, Is = 59, Is_ = 60, 
    Prolog_not = 61, Prolog_not_equal = 62, Slash = 63, ConstructAtom = 64, 
    Regexp_ref = 65, Underscore = 66, Plus = 67, Minus = 68, Star = 69, 
    Div = 70, Mod = 71, Caret = 72, And = 73, Or = 74, Tilde = 75, Not = 76, 
    Assign = 77, Less = 78, Greater = 79, Equal = 80, NotEqual = 81, LessEqual = 82, 
    GreaterEqual = 83, AndAnd = 84, OrOr = 85, Comma = 86, Arrow = 87, Question = 88, 
    Colon = 89, Doublecolon = 90, Semi = 91, Dot = 92, DotStar = 93, Ellipsis = 94, 
    Identifier = 95, DecimalLiteral = 96, OctalLiteral = 97, HexadecimalLiteral = 98, 
    BinaryLiteral = 99, Integersuffix = 100, UserDefinedIntegerLiteral = 101, 
    UserDefinedFloatingLiteral = 102, UserDefinedStringLiteral = 103, UserDefinedCharacterLiteral = 104, 
    Whitespace = 105, Newline = 106, BlockComment = 107, LineComment = 108, 
    PrologComment = 109
  };

  explicit ReentPreLexer(antlr4::CharStream *input);
  ~ReentPreLexer();


  	int def_pattern_state = 0;
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
  void DefPatternAction(antlr4::RuleContext *context, size_t actionIndex);
  void LineAction(antlr4::RuleContext *context, size_t actionIndex);
  void Plc_regexp_varAction(antlr4::RuleContext *context, size_t actionIndex);
  void Plc_regexp_equalAction(antlr4::RuleContext *context, size_t actionIndex);
  void Plc_regexp_not_equalAction(antlr4::RuleContext *context, size_t actionIndex);
  void Plc_regexp_queryAction(antlr4::RuleContext *context, size_t actionIndex);
  void LeftBraceAction(antlr4::RuleContext *context, size_t actionIndex);
  void RightBraceAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.
  bool Regexp_fragmentSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool Regexp_setSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefModuleSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefMemoizationSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DoNotCheckSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefOtherPragmaSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PreprocPassesSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool AddScanSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ScanSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool AddParseSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ParseSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefPatternSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool LineSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool MultiLineMacroSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DirectiveSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PrologCommentSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

