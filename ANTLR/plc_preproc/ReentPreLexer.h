
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
    Scan = 17, AddParse = 18, Parse = 19, DefPattern = 20, DefXPath = 21, 
    Line = 22, MultiLineMacro = 23, Directive = 24, AtValue = 25, Conditions = 26, 
    Controlled = 27, Div_ = 28, False_ = 29, Feed_forward = 30, GetText = 31, 
    Goal = 32, Lin_extrapolator = 33, Mgua = 34, Mod_ = 35, Nullptr = 36, 
    Regexp_analyze = 37, Regexp_begin = 38, Regexp_end = 39, Regexp_parallel = 40, 
    Regexp_sequential = 41, Rem = 42, True_ = 43, Plc_regexp_var = 44, Plc_regexp_equal = 45, 
    Plc_regexp_not_equal = 46, Plc_regexp_query = 47, LeftParen = 48, RightParen = 49, 
    LeftBracket = 50, RightBracket = 51, LeftBrace = 52, RightBrace = 53, 
    AssignGreater = 54, DivDiv = 55, Pound = 56, And_ = 57, Or_ = 58, At = 59, 
    Is = 60, Is_ = 61, Prolog_not = 62, Prolog_not_equal = 63, Slash = 64, 
    ConstructAtom = 65, Regexp_ref = 66, Underscore = 67, Plus = 68, Minus = 69, 
    Star = 70, Div = 71, Mod = 72, Caret = 73, And = 74, Or = 75, Tilde = 76, 
    Not = 77, Assign = 78, Less = 79, Greater = 80, Equal = 81, NotEqual = 82, 
    LessEqual = 83, GreaterEqual = 84, AndAnd = 85, OrOr = 86, Comma = 87, 
    Arrow = 88, Question = 89, Colon = 90, Doublecolon = 91, Semi = 92, 
    Dot = 93, DotStar = 94, Ellipsis = 95, Identifier = 96, DecimalLiteral = 97, 
    OctalLiteral = 98, HexadecimalLiteral = 99, BinaryLiteral = 100, Integersuffix = 101, 
    UserDefinedIntegerLiteral = 102, UserDefinedFloatingLiteral = 103, UserDefinedStringLiteral = 104, 
    UserDefinedCharacterLiteral = 105, Whitespace = 106, Newline = 107, 
    BlockComment = 108, LineComment = 109, PrologComment = 110
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

