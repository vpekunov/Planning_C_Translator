
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
    Directive = 27, AtValue = 28, Cilk_spawn = 29, Cilk_sync = 30, Conditions = 31, 
    Controlled = 32, Div_ = 33, False_ = 34, Feed_forward = 35, GetText = 36, 
    Goal = 37, Lin_extrapolator = 38, Mgua = 39, Mod_ = 40, Nullptr = 41, 
    Regexp_analyze = 42, Regexp_begin = 43, Regexp_end = 44, Regexp_parallel = 45, 
    Regexp_sequential = 46, Rem = 47, True_ = 48, Plc_regexp_var = 49, Plc_regexp_equal = 50, 
    Plc_regexp_not_equal = 51, Plc_regexp_query = 52, LeftParen = 53, RightParen = 54, 
    LeftBracket = 55, RightBracket = 56, LeftBrace = 57, RightBrace = 58, 
    AssignGreater = 59, DivDiv = 60, Pound = 61, And_ = 62, Or_ = 63, At = 64, 
    Is = 65, Is_ = 66, Prolog_not = 67, Prolog_not_equal = 68, Slash = 69, 
    ConstructAtom = 70, Regexp_ref = 71, Underscore = 72, Plus = 73, Minus = 74, 
    Star = 75, Div = 76, Mod = 77, Caret = 78, And = 79, Or = 80, Tilde = 81, 
    Not = 82, Assign = 83, Less = 84, Greater = 85, Equal = 86, NotEqual = 87, 
    LessEqual = 88, GreaterEqual = 89, AndAnd = 90, OrOr = 91, Comma = 92, 
    Arrow = 93, Question = 94, Colon = 95, Doublecolon = 96, Semi = 97, 
    Dot = 98, DotStar = 99, Ellipsis = 100, Identifier = 101, DecimalLiteral = 102, 
    OctalLiteral = 103, HexadecimalLiteral = 104, BinaryLiteral = 105, Integersuffix = 106, 
    UserDefinedIntegerLiteral = 107, UserDefinedFloatingLiteral = 108, UserDefinedStringLiteral = 109, 
    UserDefinedCharacterLiteral = 110, Whitespace = 111, Newline = 112, 
    BlockComment = 113, LineComment = 114, PrologComment = 115
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

