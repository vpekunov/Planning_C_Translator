
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
    DoNotCheck = 13, DefOtherPragma = 14, Introduce = 15, MetaSentence = 16, 
    Stop = 17, PreprocPasses = 18, AddScan = 19, Scan = 20, AddParse = 21, 
    Parse = 22, DefPattern = 23, DefXPath = 24, Line = 25, MultiLineMacro = 26, 
    Directive = 27, AtValue = 28, Conditions = 29, Controlled = 30, Div_ = 31, 
    False_ = 32, Feed_forward = 33, GetText = 34, Goal = 35, Lin_extrapolator = 36, 
    Mgua = 37, Mod_ = 38, Nullptr = 39, Regexp_analyze = 40, Regexp_begin = 41, 
    Regexp_end = 42, Regexp_parallel = 43, Regexp_sequential = 44, Rem = 45, 
    True_ = 46, Plc_regexp_var = 47, Plc_regexp_equal = 48, Plc_regexp_not_equal = 49, 
    Plc_regexp_query = 50, LeftParen = 51, RightParen = 52, LeftBracket = 53, 
    RightBracket = 54, LeftBrace = 55, RightBrace = 56, AssignGreater = 57, 
    DivDiv = 58, Pound = 59, And_ = 60, Or_ = 61, At = 62, Is = 63, Is_ = 64, 
    Prolog_not = 65, Prolog_not_equal = 66, Slash = 67, ConstructAtom = 68, 
    Regexp_ref = 69, Underscore = 70, Plus = 71, Minus = 72, Star = 73, 
    Div = 74, Mod = 75, Caret = 76, And = 77, Or = 78, Tilde = 79, Not = 80, 
    Assign = 81, Less = 82, Greater = 83, Equal = 84, NotEqual = 85, LessEqual = 86, 
    GreaterEqual = 87, AndAnd = 88, OrOr = 89, Comma = 90, Arrow = 91, Question = 92, 
    Colon = 93, Doublecolon = 94, Semi = 95, Dot = 96, DotStar = 97, Ellipsis = 98, 
    Identifier = 99, DecimalLiteral = 100, OctalLiteral = 101, HexadecimalLiteral = 102, 
    BinaryLiteral = 103, Integersuffix = 104, UserDefinedIntegerLiteral = 105, 
    UserDefinedFloatingLiteral = 106, UserDefinedStringLiteral = 107, UserDefinedCharacterLiteral = 108, 
    Whitespace = 109, Newline = 110, BlockComment = 111, LineComment = 112, 
    PrologComment = 113
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
  bool IntroduceSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool MetaSentenceSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool StopSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PreprocPassesSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool AddScanSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ScanSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool AddParseSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ParseSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefPatternSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DefXPathSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool LineSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool MultiLineMacroSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool DirectiveSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PrologCommentSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

