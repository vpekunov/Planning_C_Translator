
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>


// Generated from ReentPreParser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  ReentPreParser : public antlr4::Parser {
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

  enum {
    RuleTranslationUnit = 0, RuleStatementseq = 1, RuleStatement = 2, RuleDef_pattern = 3, 
    RulePut_fact = 4, RuleDef_pattern_param = 5, RuleSimple_xpath_expression = 6, 
    RuleXpath_and_expression = 7, RuleXpath_rel_expression = 8, RuleXpath_mul_expression = 9, 
    RuleXpath_plus_expression = 10, RuleXpath_unary_expression = 11, RuleXpath_query = 12, 
    RuleXpath_predicate = 13, RuleXpath_fun_params = 14, RuleDef_xpath = 15, 
    RuleDef_xpath_param = 16, RuleDef_xpath_expression = 17, RuleDef_xpath_and_expression = 18, 
    RuleDef_xpath_rel_expression = 19, RuleDef_xpath_mul_expression = 20, 
    RuleDef_xpath_plus_expression = 21, RuleDef_xpath_unary_expression = 22, 
    RuleDef_xpath_query = 23, RuleDef_xpath_predicate = 24, RuleDef_xpath_fun_params = 25, 
    RuleRegexps = 26, RuleRegexp_lines = 27, RuleRegexp_body = 28, RulePlc_regexp_logical = 29, 
    RulePlc_regexp_var = 30, RulePlc_regexp_equal = 31, RulePlc_regexp_not_equal = 32, 
    RulePlc_regexp_query = 33, RuleRegexp_or_sequence = 34, RuleRegexp_and_sequence = 35, 
    RuleRegexp_unary = 36, RuleRegexp_pred = 37, RuleRegexp_pred_arg = 38, 
    RuleRegexp_pred_parallel = 39, RuleDefModule = 40, RuleDefModuleDescriptors = 41, 
    RuleDefModuleDescriptor = 42, RuleDefMemoization = 43, RulePreprocPasses = 44, 
    RuleAddScan = 45, RuleScan = 46, RuleAddParse = 47, RuleParse = 48, 
    RuleScanners_list = 49, RuleMemoMapItem = 50, RuleMemoMapType = 51, 
    RuleCpp_balanced_expression = 52, RuleMemoizationStyle = 53, RuleMgua = 54, 
    RuleNnet = 55, RuleExtrapolator = 56, RuleNnet_layer_specifier = 57, 
    RuleNnet_layer_type = 58, RuleControlPredicate = 59, RuleAutomated_control = 60, 
    RuleBy_conditions_control = 61, RuleBlockHeader = 62, RuleTypeItem = 63, 
    RuleTypeSpecifier = 64, RuleTemplateParameters = 65, RuleTemplateParameter = 66, 
    RuleParameter = 67, RuleDimension = 68, RuleProlog_goal = 69, RuleProlog_statement = 70, 
    RuleProlog_parameters = 71, RuleProlog_predicates = 72, RuleProlog_parameter = 73, 
    RuleProlog_parameter_list = 74, RuleProlog_inside_list = 75, RuleProlog_predicate = 76, 
    RuleProlog_if_then = 77, RuleIs_expression = 78, RuleRelational_expression = 79, 
    RuleProlog_relation = 80, RulePow_expression = 81, RuleProlog_pow = 82, 
    RuleMul_div_expression = 83, RuleProlog_mul_div = 84, RulePlus_min_expression = 85, 
    RuleProlog_plus_minus = 86, RuleUnary_expression = 87, RuleOperand = 88, 
    RuleOperandList = 89, RuleProlog_term = 90, RuleProlog_call = 91, RuleProlog_call_params = 92, 
    RuleProlog_predicate_id = 93, RuleCpp_code_without_at = 94, RuleObjCilkSpawnArg = 95, 
    RuleObjCilkSpawnParams = 96, RuleObjCilkDesignator = 97, RuleObjCilkSpawn = 98, 
    RuleObjCilkSync = 99, RuleOtherLine = 100, RuleLiteral = 101
  };

  explicit ReentPreParser(antlr4::TokenStream *input);
  ~ReentPreParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  	std::map<std::string, int> modules;
  	std::map<std::string, int> module_refs;
  	std::set<std::string> scanners;
  	std::set<std::string> scanner_refs;
  	std::vector<std::string> memo_map;
  	std::set<std::string> xpaths;
  	std::set<std::string> regexp_vars;
  	std::set<std::string> regexp_refs;


  class TranslationUnitContext;
  class StatementseqContext;
  class StatementContext;
  class Def_patternContext;
  class Put_factContext;
  class Def_pattern_paramContext;
  class Simple_xpath_expressionContext;
  class Xpath_and_expressionContext;
  class Xpath_rel_expressionContext;
  class Xpath_mul_expressionContext;
  class Xpath_plus_expressionContext;
  class Xpath_unary_expressionContext;
  class Xpath_queryContext;
  class Xpath_predicateContext;
  class Xpath_fun_paramsContext;
  class Def_xpathContext;
  class Def_xpath_paramContext;
  class Def_xpath_expressionContext;
  class Def_xpath_and_expressionContext;
  class Def_xpath_rel_expressionContext;
  class Def_xpath_mul_expressionContext;
  class Def_xpath_plus_expressionContext;
  class Def_xpath_unary_expressionContext;
  class Def_xpath_queryContext;
  class Def_xpath_predicateContext;
  class Def_xpath_fun_paramsContext;
  class RegexpsContext;
  class Regexp_linesContext;
  class Regexp_bodyContext;
  class Plc_regexp_logicalContext;
  class Plc_regexp_varContext;
  class Plc_regexp_equalContext;
  class Plc_regexp_not_equalContext;
  class Plc_regexp_queryContext;
  class Regexp_or_sequenceContext;
  class Regexp_and_sequenceContext;
  class Regexp_unaryContext;
  class Regexp_predContext;
  class Regexp_pred_argContext;
  class Regexp_pred_parallelContext;
  class DefModuleContext;
  class DefModuleDescriptorsContext;
  class DefModuleDescriptorContext;
  class DefMemoizationContext;
  class PreprocPassesContext;
  class AddScanContext;
  class ScanContext;
  class AddParseContext;
  class ParseContext;
  class Scanners_listContext;
  class MemoMapItemContext;
  class MemoMapTypeContext;
  class Cpp_balanced_expressionContext;
  class MemoizationStyleContext;
  class MguaContext;
  class NnetContext;
  class ExtrapolatorContext;
  class Nnet_layer_specifierContext;
  class Nnet_layer_typeContext;
  class ControlPredicateContext;
  class Automated_controlContext;
  class By_conditions_controlContext;
  class BlockHeaderContext;
  class TypeItemContext;
  class TypeSpecifierContext;
  class TemplateParametersContext;
  class TemplateParameterContext;
  class ParameterContext;
  class DimensionContext;
  class Prolog_goalContext;
  class Prolog_statementContext;
  class Prolog_parametersContext;
  class Prolog_predicatesContext;
  class Prolog_parameterContext;
  class Prolog_parameter_listContext;
  class Prolog_inside_listContext;
  class Prolog_predicateContext;
  class Prolog_if_thenContext;
  class Is_expressionContext;
  class Relational_expressionContext;
  class Prolog_relationContext;
  class Pow_expressionContext;
  class Prolog_powContext;
  class Mul_div_expressionContext;
  class Prolog_mul_divContext;
  class Plus_min_expressionContext;
  class Prolog_plus_minusContext;
  class Unary_expressionContext;
  class OperandContext;
  class OperandListContext;
  class Prolog_termContext;
  class Prolog_callContext;
  class Prolog_call_paramsContext;
  class Prolog_predicate_idContext;
  class Cpp_code_without_atContext;
  class ObjCilkSpawnArgContext;
  class ObjCilkSpawnParamsContext;
  class ObjCilkDesignatorContext;
  class ObjCilkSpawnContext;
  class ObjCilkSyncContext;
  class OtherLineContext;
  class LiteralContext; 

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    StatementseqContext *statementseq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  StatementseqContext : public antlr4::ParserRuleContext {
  public:
    StatementseqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementseqContext* statementseq();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DefModuleContext *defModule();
    antlr4::tree::TerminalNode *DefModule();
    DefMemoizationContext *defMemoization();
    antlr4::tree::TerminalNode *DefMemoization();
    PreprocPassesContext *preprocPasses();
    antlr4::tree::TerminalNode *PreprocPasses();
    AddScanContext *addScan();
    antlr4::tree::TerminalNode *AddScan();
    ScanContext *scan();
    antlr4::tree::TerminalNode *Scan();
    AddParseContext *addParse();
    antlr4::tree::TerminalNode *AddParse();
    ParseContext *parse();
    antlr4::tree::TerminalNode *Parse();
    Def_patternContext *def_pattern();
    antlr4::tree::TerminalNode *DefPattern();
    Def_xpathContext *def_xpath();
    antlr4::tree::TerminalNode *DefXPath();
    ObjCilkSpawnContext *objCilkSpawn();
    antlr4::tree::TerminalNode *Cilk_spawn();
    std::vector<ObjCilkDesignatorContext *> objCilkDesignator();
    ObjCilkDesignatorContext* objCilkDesignator(size_t i);
    ObjCilkSyncContext *objCilkSync();
    antlr4::tree::TerminalNode *Cilk_sync();
    OtherLineContext *otherLine();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  Def_patternContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    antlr4::Token *module = nullptr;
    Def_patternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DefPattern();
    antlr4::tree::TerminalNode *AssignGreater();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    RegexpsContext *regexps();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    Put_factContext *put_fact();
    std::vector<Def_pattern_paramContext *> def_pattern_param();
    Def_pattern_paramContext* def_pattern_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_patternContext* def_pattern();

  class  Put_factContext : public antlr4::ParserRuleContext {
  public:
    Put_factContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *RightBracket();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Put_factContext* put_fact();

  class  Def_pattern_paramContext : public antlr4::ParserRuleContext {
  public:
    Def_pattern_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CharacterLiteral();
    antlr4::tree::TerminalNode *EmptyAtom();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    std::vector<Def_pattern_paramContext *> def_pattern_param();
    Def_pattern_paramContext* def_pattern_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *Or();
    Simple_xpath_expressionContext *simple_xpath_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_pattern_paramContext* def_pattern_param();

  class  Simple_xpath_expressionContext : public antlr4::ParserRuleContext {
  public:
    Simple_xpath_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Xpath_and_expressionContext *> xpath_and_expression();
    Xpath_and_expressionContext* xpath_and_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Or_();
    antlr4::tree::TerminalNode* Or_(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Simple_xpath_expressionContext* simple_xpath_expression();

  class  Xpath_and_expressionContext : public antlr4::ParserRuleContext {
  public:
    Xpath_and_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Xpath_rel_expressionContext *> xpath_rel_expression();
    Xpath_rel_expressionContext* xpath_rel_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> And_();
    antlr4::tree::TerminalNode* And_(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_and_expressionContext* xpath_and_expression();

  class  Xpath_rel_expressionContext : public antlr4::ParserRuleContext {
  public:
    Xpath_rel_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Xpath_mul_expressionContext *> xpath_mul_expression();
    Xpath_mul_expressionContext* xpath_mul_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Assign();
    antlr4::tree::TerminalNode* Assign(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NotEqual();
    antlr4::tree::TerminalNode* NotEqual(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LessEqual();
    antlr4::tree::TerminalNode* LessEqual(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GreaterEqual();
    antlr4::tree::TerminalNode* GreaterEqual(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_rel_expressionContext* xpath_rel_expression();

  class  Xpath_mul_expressionContext : public antlr4::ParserRuleContext {
  public:
    Xpath_mul_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Xpath_plus_expressionContext *> xpath_plus_expression();
    Xpath_plus_expressionContext* xpath_plus_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_mul_expressionContext* xpath_mul_expression();

  class  Xpath_plus_expressionContext : public antlr4::ParserRuleContext {
  public:
    Xpath_plus_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Xpath_unary_expressionContext *> xpath_unary_expression();
    Xpath_unary_expressionContext* xpath_unary_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Plus();
    antlr4::tree::TerminalNode* Plus(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Minus();
    antlr4::tree::TerminalNode* Minus(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_plus_expressionContext* xpath_plus_expression();

  class  Xpath_unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Xpath_unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *CharacterLiteral();
    antlr4::tree::TerminalNode *EmptyAtom();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *AtValue();
    antlr4::tree::TerminalNode *GetText();
    antlr4::tree::TerminalNode *LeftParen();
    Simple_xpath_expressionContext *simple_xpath_expression();
    antlr4::tree::TerminalNode *RightParen();
    Xpath_queryContext *xpath_query();
    antlr4::tree::TerminalNode *Identifier();
    Xpath_fun_paramsContext *xpath_fun_params();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_unary_expressionContext* xpath_unary_expression();

  class  Xpath_queryContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *var = nullptr;
    antlr4::Token *next = nullptr;
    antlr4::Token *last = nullptr;
    Xpath_queryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DivDiv();
    antlr4::tree::TerminalNode* DivDiv(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    antlr4::tree::TerminalNode *AtValue();
    antlr4::tree::TerminalNode *GetText();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<Xpath_predicateContext *> xpath_predicate();
    Xpath_predicateContext* xpath_predicate(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_queryContext* xpath_query();

  class  Xpath_predicateContext : public antlr4::ParserRuleContext {
  public:
    Xpath_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    Simple_xpath_expressionContext *simple_xpath_expression();
    antlr4::tree::TerminalNode *RightBracket();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_predicateContext* xpath_predicate();

  class  Xpath_fun_paramsContext : public antlr4::ParserRuleContext {
  public:
    Xpath_fun_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Simple_xpath_expressionContext *> simple_xpath_expression();
    Simple_xpath_expressionContext* simple_xpath_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Xpath_fun_paramsContext* xpath_fun_params();

  class  Def_xpathContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    Def_xpathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DefXPath();
    antlr4::tree::TerminalNode *LeftBrace();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    Def_xpath_expressionContext *def_xpath_expression();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<Def_xpath_paramContext *> def_xpath_param();
    Def_xpath_paramContext* def_xpath_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpathContext* def_xpath();

  class  Def_xpath_paramContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Regexp_ref();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *And();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_paramContext* def_xpath_param();

  class  Def_xpath_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_and_expressionContext *> def_xpath_and_expression();
    Def_xpath_and_expressionContext* def_xpath_and_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Or_();
    antlr4::tree::TerminalNode* Or_(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_expressionContext* def_xpath_expression();

  class  Def_xpath_and_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_and_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_rel_expressionContext *> def_xpath_rel_expression();
    Def_xpath_rel_expressionContext* def_xpath_rel_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> And_();
    antlr4::tree::TerminalNode* And_(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_and_expressionContext* def_xpath_and_expression();

  class  Def_xpath_rel_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_rel_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_mul_expressionContext *> def_xpath_mul_expression();
    Def_xpath_mul_expressionContext* def_xpath_mul_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Assign();
    antlr4::tree::TerminalNode* Assign(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NotEqual();
    antlr4::tree::TerminalNode* NotEqual(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LessEqual();
    antlr4::tree::TerminalNode* LessEqual(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GreaterEqual();
    antlr4::tree::TerminalNode* GreaterEqual(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_rel_expressionContext* def_xpath_rel_expression();

  class  Def_xpath_mul_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_mul_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_plus_expressionContext *> def_xpath_plus_expression();
    Def_xpath_plus_expressionContext* def_xpath_plus_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_mul_expressionContext* def_xpath_mul_expression();

  class  Def_xpath_plus_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_plus_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_unary_expressionContext *> def_xpath_unary_expression();
    Def_xpath_unary_expressionContext* def_xpath_unary_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Plus();
    antlr4::tree::TerminalNode* Plus(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Minus();
    antlr4::tree::TerminalNode* Minus(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_plus_expressionContext* def_xpath_plus_expression();

  class  Def_xpath_unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *CharacterLiteral();
    antlr4::tree::TerminalNode *EmptyAtom();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *AtValue();
    antlr4::tree::TerminalNode *At();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *GetText();
    antlr4::tree::TerminalNode *LeftParen();
    Def_xpath_expressionContext *def_xpath_expression();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    Def_xpath_fun_paramsContext *def_xpath_fun_params();
    Def_xpath_queryContext *def_xpath_query();
    antlr4::tree::TerminalNode *Regexp_ref();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_unary_expressionContext* def_xpath_unary_expression();

  class  Def_xpath_queryContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_queryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<Def_xpath_predicateContext *> def_xpath_predicate();
    Def_xpath_predicateContext* def_xpath_predicate(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DivDiv();
    antlr4::tree::TerminalNode* DivDiv(size_t i);
    antlr4::tree::TerminalNode *AtValue();
    antlr4::tree::TerminalNode *At();
    antlr4::tree::TerminalNode *GetText();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_queryContext* def_xpath_query();

  class  Def_xpath_predicateContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    Def_xpath_expressionContext *def_xpath_expression();
    antlr4::tree::TerminalNode *RightBracket();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_predicateContext* def_xpath_predicate();

  class  Def_xpath_fun_paramsContext : public antlr4::ParserRuleContext {
  public:
    Def_xpath_fun_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Def_xpath_expressionContext *> def_xpath_expression();
    Def_xpath_expressionContext* def_xpath_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Def_xpath_fun_paramsContext* def_xpath_fun_params();

  class  RegexpsContext : public antlr4::ParserRuleContext {
  public:
    RegexpsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Semi();
    std::vector<Regexp_linesContext *> regexp_lines();
    Regexp_linesContext* regexp_lines(size_t i);
    antlr4::tree::TerminalNode *Regexp_begin();
    antlr4::tree::TerminalNode *Regexp_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RegexpsContext* regexps();

  class  Regexp_linesContext : public antlr4::ParserRuleContext {
  public:
    Regexp_linesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Newline();
    Regexp_bodyContext *regexp_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_linesContext* regexp_lines();

  class  Regexp_bodyContext : public antlr4::ParserRuleContext {
  public:
    Regexp_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *Regexp_set();
    antlr4::tree::TerminalNode *Regexp_fragment();
    std::vector<Regexp_bodyContext *> regexp_body();
    Regexp_bodyContext* regexp_body(size_t i);
    Plc_regexp_logicalContext *plc_regexp_logical();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_bodyContext* regexp_body();

  class  Plc_regexp_logicalContext : public antlr4::ParserRuleContext {
  public:
    Plc_regexp_logicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Plc_regexp_varContext *plc_regexp_var();
    Plc_regexp_equalContext *plc_regexp_equal();
    Plc_regexp_not_equalContext *plc_regexp_not_equal();
    Plc_regexp_queryContext *plc_regexp_query();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plc_regexp_logicalContext* plc_regexp_logical();

  class  Plc_regexp_varContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *lib_or_id = nullptr;
    antlr4::Token *var = nullptr;
    Plc_regexp_varContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plc_regexp_var();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *LeftBrace();
    std::vector<antlr4::tree::TerminalNode *> RightBrace();
    antlr4::tree::TerminalNode* RightBrace(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plc_regexp_varContext* plc_regexp_var();

  class  Plc_regexp_equalContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *req = nullptr;
    Plc_regexp_equalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plc_regexp_equal();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plc_regexp_equalContext* plc_regexp_equal();

  class  Plc_regexp_not_equalContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *req = nullptr;
    Plc_regexp_not_equalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plc_regexp_not_equal();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plc_regexp_not_equalContext* plc_regexp_not_equal();

  class  Plc_regexp_queryContext : public antlr4::ParserRuleContext {
  public:
    Plc_regexp_queryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plc_regexp_query();
    antlr4::tree::TerminalNode *RightBrace();
    Regexp_or_sequenceContext *regexp_or_sequence();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plc_regexp_queryContext* plc_regexp_query();

  class  Regexp_or_sequenceContext : public antlr4::ParserRuleContext {
  public:
    Regexp_or_sequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Regexp_and_sequenceContext *> regexp_and_sequence();
    Regexp_and_sequenceContext* regexp_and_sequence(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Semi();
    antlr4::tree::TerminalNode* Semi(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_or_sequenceContext* regexp_or_sequence();

  class  Regexp_and_sequenceContext : public antlr4::ParserRuleContext {
  public:
    Regexp_and_sequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Regexp_unaryContext *> regexp_unary();
    Regexp_unaryContext* regexp_unary(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_and_sequenceContext* regexp_and_sequence();

  class  Regexp_unaryContext : public antlr4::ParserRuleContext {
  public:
    Regexp_unaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    Regexp_or_sequenceContext *regexp_or_sequence();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    Regexp_predContext *regexp_pred();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_unaryContext* regexp_unary();

  class  Regexp_predContext : public antlr4::ParserRuleContext {
  public:
    Regexp_predContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Regexp_pred_parallelContext *regexp_pred_parallel();
    antlr4::tree::TerminalNode *Regexp_sequential();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    antlr4::tree::TerminalNode *Not();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<Regexp_pred_argContext *> regexp_pred_arg();
    Regexp_pred_argContext* regexp_pred_arg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_predContext* regexp_pred();

  class  Regexp_pred_argContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ref = nullptr;
    antlr4::Token *var = nullptr;
    Regexp_pred_argContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Underscore();
    antlr4::tree::TerminalNode *Regexp_ref();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *CharacterLiteral();
    antlr4::tree::TerminalNode *EmptyAtom();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatingLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_pred_argContext* regexp_pred_arg();

  class  Regexp_pred_parallelContext : public antlr4::ParserRuleContext {
  public:
    Regexp_pred_parallelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Regexp_parallel();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *Regexp_analyze();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Regexp_pred_parallelContext* regexp_pred_parallel();

  class  DefModuleContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    DefModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DefModule();
    std::vector<antlr4::tree::TerminalNode *> LeftParen();
    antlr4::tree::TerminalNode* LeftParen(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightParen();
    antlr4::tree::TerminalNode* RightParen(size_t i);
    antlr4::tree::TerminalNode *LeftBrace();
    DefModuleDescriptorsContext *defModuleDescriptors();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefModuleContext* defModule();

  class  DefModuleDescriptorsContext : public antlr4::ParserRuleContext {
  public:
    DefModuleDescriptorsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DefModuleDescriptorContext *defModuleDescriptor();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Semi();
    DefModuleDescriptorsContext *defModuleDescriptors();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefModuleDescriptorsContext* defModuleDescriptors();

  class  DefModuleDescriptorContext : public antlr4::ParserRuleContext {
  public:
    DefModuleDescriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *At();
    Prolog_goalContext *prolog_goal();
    Prolog_statementContext *prolog_statement();
    Cpp_code_without_atContext *cpp_code_without_at();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefModuleDescriptorContext* defModuleDescriptor();

  class  DefMemoizationContext : public antlr4::ParserRuleContext {
  public:
    ReentPreParser::MemoMapItemContext *first = nullptr;
    ReentPreParser::MemoMapItemContext *next = nullptr;
    DefMemoizationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DefMemoization();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    BlockHeaderContext *blockHeader();
    std::vector<MemoMapItemContext *> memoMapItem();
    MemoMapItemContext* memoMapItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    MemoizationStyleContext *memoizationStyle();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefMemoizationContext* defMemoization();

  class  PreprocPassesContext : public antlr4::ParserRuleContext {
  public:
    PreprocPassesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PreprocPasses();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Newline();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PreprocPassesContext* preprocPasses();

  class  AddScanContext : public antlr4::ParserRuleContext {
  public:
    AddScanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AddScan();
    Scanners_listContext *scanners_list();
    antlr4::tree::TerminalNode *Newline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AddScanContext* addScan();

  class  ScanContext : public antlr4::ParserRuleContext {
  public:
    ScanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Scan();
    Scanners_listContext *scanners_list();
    antlr4::tree::TerminalNode *Newline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScanContext* scan();

  class  AddParseContext : public antlr4::ParserRuleContext {
  public:
    AddParseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AddParse();
    Scanners_listContext *scanners_list();
    antlr4::tree::TerminalNode *Newline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AddParseContext* addParse();

  class  ParseContext : public antlr4::ParserRuleContext {
  public:
    ParseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Parse();
    Scanners_listContext *scanners_list();
    antlr4::tree::TerminalNode *Newline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParseContext* parse();

  class  Scanners_listContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *first = nullptr;
    antlr4::Token *next = nullptr;
    Scanners_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Scanners_listContext* scanners_list();

  class  MemoMapItemContext : public antlr4::ParserRuleContext {
  public:
    MemoMapItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MemoMapTypeContext *memoMapType();
    antlr4::tree::TerminalNode *Star();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemoMapItemContext* memoMapItem();

  class  MemoMapTypeContext : public antlr4::ParserRuleContext {
  public:
    MemoMapTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemoMapTypeContext* memoMapType();

  class  Cpp_balanced_expressionContext : public antlr4::ParserRuleContext {
  public:
    Cpp_balanced_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LeftParen();
    antlr4::tree::TerminalNode* LeftParen(size_t i);
    std::vector<Cpp_balanced_expressionContext *> cpp_balanced_expression();
    Cpp_balanced_expressionContext* cpp_balanced_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightParen();
    antlr4::tree::TerminalNode* RightParen(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cpp_balanced_expressionContext* cpp_balanced_expression();

  class  MemoizationStyleContext : public antlr4::ParserRuleContext {
  public:
    MemoizationStyleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MguaContext *mgua();
    NnetContext *nnet();
    ExtrapolatorContext *extrapolator();
    ControlPredicateContext *controlPredicate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemoizationStyleContext* memoizationStyle();

  class  MguaContext : public antlr4::ParserRuleContext {
  public:
    MguaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Mgua();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatingLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MguaContext* mgua();

  class  NnetContext : public antlr4::ParserRuleContext {
  public:
    NnetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Feed_forward();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> IntegerLiteral();
    antlr4::tree::TerminalNode* IntegerLiteral(size_t i);
    std::vector<antlr4::tree::TerminalNode *> FloatingLiteral();
    antlr4::tree::TerminalNode* FloatingLiteral(size_t i);
    std::vector<Nnet_layer_specifierContext *> nnet_layer_specifier();
    Nnet_layer_specifierContext* nnet_layer_specifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NnetContext* nnet();

  class  ExtrapolatorContext : public antlr4::ParserRuleContext {
  public:
    ExtrapolatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Lin_extrapolator();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *Comma();
    std::vector<antlr4::tree::TerminalNode *> IntegerLiteral();
    antlr4::tree::TerminalNode* IntegerLiteral(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *FloatingLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExtrapolatorContext* extrapolator();

  class  Nnet_layer_specifierContext : public antlr4::ParserRuleContext {
  public:
    Nnet_layer_specifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *Comma();
    Nnet_layer_typeContext *nnet_layer_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Nnet_layer_specifierContext* nnet_layer_specifier();

  class  Nnet_layer_typeContext : public antlr4::ParserRuleContext {
  public:
    Nnet_layer_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Nnet_layer_typeContext* nnet_layer_type();

  class  ControlPredicateContext : public antlr4::ParserRuleContext {
  public:
    ControlPredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Automated_controlContext *automated_control();
    By_conditions_controlContext *by_conditions_control();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ControlPredicateContext* controlPredicate();

  class  Automated_controlContext : public antlr4::ParserRuleContext {
  public:
    Automated_controlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Controlled();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<antlr4::tree::TerminalNode *> IntegerLiteral();
    antlr4::tree::TerminalNode* IntegerLiteral(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Automated_controlContext* automated_control();

  class  By_conditions_controlContext : public antlr4::ParserRuleContext {
  public:
    By_conditions_controlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Conditions();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Cpp_balanced_expressionContext *> cpp_balanced_expression();
    Cpp_balanced_expressionContext* cpp_balanced_expression(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  By_conditions_controlContext* by_conditions_control();

  class  BlockHeaderContext : public antlr4::ParserRuleContext {
  public:
    ReentPreParser::TypeItemContext *type = nullptr;
    BlockHeaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *LeftBrace();
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<TypeItemContext *> typeItem();
    TypeItemContext* typeItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlockHeaderContext* blockHeader();

  class  TypeItemContext : public antlr4::ParserRuleContext {
  public:
    TypeItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierContext *typeSpecifier();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *AndAnd();
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeItemContext* typeItem();

  class  TypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    TemplateParametersContext *templateParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeSpecifierContext* typeSpecifier();

  class  TemplateParametersContext : public antlr4::ParserRuleContext {
  public:
    TemplateParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateParameterContext *> templateParameter();
    TemplateParameterContext* templateParameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateParametersContext* templateParameters();

  class  TemplateParameterContext : public antlr4::ParserRuleContext {
  public:
    TemplateParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierContext *typeSpecifier();
    LiteralContext *literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateParameterContext* templateParameter();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeItemContext *typeItem();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<DimensionContext *> dimension();
    DimensionContext* dimension(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterContext* parameter();

  class  DimensionContext : public antlr4::ParserRuleContext {
  public:
    DimensionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *IntegerLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DimensionContext* dimension();

  class  Prolog_goalContext : public antlr4::ParserRuleContext {
  public:
    Prolog_goalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Goal();
    antlr4::tree::TerminalNode *Is();
    Prolog_predicatesContext *prolog_predicates();
    antlr4::tree::TerminalNode *Dot();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_goalContext* prolog_goal();

  class  Prolog_statementContext : public antlr4::ParserRuleContext {
  public:
    Prolog_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Dot();
    Prolog_parametersContext *prolog_parameters();
    antlr4::tree::TerminalNode *Is();
    Prolog_predicatesContext *prolog_predicates();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_statementContext* prolog_statement();

  class  Prolog_parametersContext : public antlr4::ParserRuleContext {
  public:
    Prolog_parametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Prolog_parameterContext *> prolog_parameter();
    Prolog_parameterContext* prolog_parameter(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_parametersContext* prolog_parameters();

  class  Prolog_predicatesContext : public antlr4::ParserRuleContext {
  public:
    Prolog_predicatesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prolog_predicateContext *prolog_predicate();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    antlr4::tree::TerminalNode *Prolog_not();
    Prolog_if_thenContext *prolog_if_then();
    Prolog_predicatesContext *prolog_predicates();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_predicatesContext* prolog_predicates();

  class  Prolog_parameterContext : public antlr4::ParserRuleContext {
  public:
    Prolog_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralContext *literal();
    antlr4::tree::TerminalNode *EmptyAtom();
    Prolog_parameter_listContext *prolog_parameter_list();
    Prolog_predicateContext *prolog_predicate();
    antlr4::tree::TerminalNode *Underscore();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_parameterContext* prolog_parameter();

  class  Prolog_parameter_listContext : public antlr4::ParserRuleContext {
  public:
    Prolog_parameter_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    Prolog_inside_listContext *prolog_inside_list();
    antlr4::tree::TerminalNode *Or();
    Prolog_parameterContext *prolog_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_parameter_listContext* prolog_parameter_list();

  class  Prolog_inside_listContext : public antlr4::ParserRuleContext {
  public:
    Prolog_inside_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prolog_parameterContext *prolog_parameter();
    antlr4::tree::TerminalNode *Comma();
    Prolog_inside_listContext *prolog_inside_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_inside_listContext* prolog_inside_list();

  class  Prolog_predicateContext : public antlr4::ParserRuleContext {
  public:
    Prolog_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    Prolog_predicatesContext *prolog_predicates();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    antlr4::tree::TerminalNode *Not();
    Prolog_callContext *prolog_call();
    Is_expressionContext *is_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_predicateContext* prolog_predicate();

  class  Prolog_if_thenContext : public antlr4::ParserRuleContext {
  public:
    Prolog_if_thenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Arrow();
    Prolog_predicateContext *prolog_predicate();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    antlr4::tree::TerminalNode *Prolog_not();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_if_thenContext* prolog_if_then();

  class  Is_expressionContext : public antlr4::ParserRuleContext {
  public:
    Is_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Relational_expressionContext *> relational_expression();
    Relational_expressionContext* relational_expression(size_t i);
    antlr4::tree::TerminalNode *Is_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Is_expressionContext* is_expression();

  class  Relational_expressionContext : public antlr4::ParserRuleContext {
  public:
    Relational_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pow_expressionContext *pow_expression();
    Prolog_relationContext *prolog_relation();
    Relational_expressionContext *relational_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Relational_expressionContext* relational_expression();

  class  Prolog_relationContext : public antlr4::ParserRuleContext {
  public:
    Prolog_relationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *GreaterEqual();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_relationContext* prolog_relation();

  class  Pow_expressionContext : public antlr4::ParserRuleContext {
  public:
    Pow_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Mul_div_expressionContext *mul_div_expression();
    Prolog_powContext *prolog_pow();
    Pow_expressionContext *pow_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Pow_expressionContext* pow_expression();

  class  Prolog_powContext : public antlr4::ParserRuleContext {
  public:
    Prolog_powContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    antlr4::tree::TerminalNode *Caret();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_powContext* prolog_pow();

  class  Mul_div_expressionContext : public antlr4::ParserRuleContext {
  public:
    Mul_div_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Plus_min_expressionContext *plus_min_expression();
    Prolog_mul_divContext *prolog_mul_div();
    Mul_div_expressionContext *mul_div_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Mul_div_expressionContext* mul_div_expression();

  class  Prolog_mul_divContext : public antlr4::ParserRuleContext {
  public:
    Prolog_mul_divContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Rem();
    antlr4::tree::TerminalNode *Div_();
    antlr4::tree::TerminalNode *Mod_();
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_mul_divContext* prolog_mul_div();

  class  Plus_min_expressionContext : public antlr4::ParserRuleContext {
  public:
    Plus_min_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_expressionContext *unary_expression();
    std::vector<Prolog_plus_minusContext *> prolog_plus_minus();
    Prolog_plus_minusContext* prolog_plus_minus(size_t i);
    std::vector<Plus_min_expressionContext *> plus_min_expression();
    Plus_min_expressionContext* plus_min_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plus_min_expressionContext* plus_min_expression();

  class  Prolog_plus_minusContext : public antlr4::ParserRuleContext {
  public:
    Prolog_plus_minusContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_plus_minusContext* prolog_plus_minus();

  class  Unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OperandContext *operand();
    Prolog_plus_minusContext *prolog_plus_minus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_expressionContext* unary_expression();

  class  OperandContext : public antlr4::ParserRuleContext {
  public:
    OperandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    Relational_expressionContext *relational_expression();
    antlr4::tree::TerminalNode *RightParen();
    OperandListContext *operandList();
    Prolog_termContext *prolog_term();
    antlr4::tree::TerminalNode *EmptyAtom();
    LiteralContext *literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OperandContext* operand();

  class  OperandListContext : public antlr4::ParserRuleContext {
  public:
    OperandListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    std::vector<Relational_expressionContext *> relational_expression();
    Relational_expressionContext* relational_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *Or();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OperandListContext* operandList();

  class  Prolog_termContext : public antlr4::ParserRuleContext {
  public:
    Prolog_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<Relational_expressionContext *> relational_expression();
    Relational_expressionContext* relational_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_termContext* prolog_term();

  class  Prolog_callContext : public antlr4::ParserRuleContext {
  public:
    Prolog_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prolog_predicate_idContext *prolog_predicate_id();
    Prolog_call_paramsContext *prolog_call_params();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_callContext* prolog_call();

  class  Prolog_call_paramsContext : public antlr4::ParserRuleContext {
  public:
    Prolog_call_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Prolog_parameterContext *> prolog_parameter();
    Prolog_parameterContext* prolog_parameter(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_call_paramsContext* prolog_call_params();

  class  Prolog_predicate_idContext : public antlr4::ParserRuleContext {
  public:
    Prolog_predicate_idContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *GreaterEqual();
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();
    antlr4::tree::TerminalNode *Arrow();
    antlr4::tree::TerminalNode *Prolog_not_equal();
    antlr4::tree::TerminalNode *ConstructAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prolog_predicate_idContext* prolog_predicate_id();

  class  Cpp_code_without_atContext : public antlr4::ParserRuleContext {
  public:
    Cpp_code_without_atContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> At();
    antlr4::tree::TerminalNode* At(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBrace();
    antlr4::tree::TerminalNode* RightBrace(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cpp_code_without_atContext* cpp_code_without_at();

  class  ObjCilkSpawnArgContext : public antlr4::ParserRuleContext {
  public:
    ObjCilkSpawnArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *Identifier();
    Cpp_balanced_expressionContext *cpp_balanced_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjCilkSpawnArgContext* objCilkSpawnArg();

  class  ObjCilkSpawnParamsContext : public antlr4::ParserRuleContext {
  public:
    ObjCilkSpawnParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Cpp_balanced_expressionContext *> cpp_balanced_expression();
    Cpp_balanced_expressionContext* cpp_balanced_expression(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjCilkSpawnParamsContext* objCilkSpawnParams();

  class  ObjCilkDesignatorContext : public antlr4::ParserRuleContext {
  public:
    ObjCilkDesignatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Arrow();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<Cpp_balanced_expressionContext *> cpp_balanced_expression();
    Cpp_balanced_expressionContext* cpp_balanced_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjCilkDesignatorContext* objCilkDesignator();

  class  ObjCilkSpawnContext : public antlr4::ParserRuleContext {
  public:
    ObjCilkSpawnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Cilk_spawn();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<ObjCilkDesignatorContext *> objCilkDesignator();
    ObjCilkDesignatorContext* objCilkDesignator(size_t i);
    ObjCilkSpawnParamsContext *objCilkSpawnParams();
    std::vector<ObjCilkSpawnArgContext *> objCilkSpawnArg();
    ObjCilkSpawnArgContext* objCilkSpawnArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjCilkSpawnContext* objCilkSpawn();

  class  ObjCilkSyncContext : public antlr4::ParserRuleContext {
  public:
    ObjCilkSyncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Cilk_sync();
    antlr4::tree::TerminalNode *Semi();
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);
    std::vector<ObjCilkDesignatorContext *> objCilkDesignator();
    ObjCilkDesignatorContext* objCilkDesignator(size_t i);
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    Cpp_balanced_expressionContext *cpp_balanced_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjCilkSyncContext* objCilkSync();

  class  OtherLineContext : public antlr4::ParserRuleContext {
  public:
    OtherLineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Newline();
    antlr4::tree::TerminalNode* Newline(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OtherLineContext* otherLine();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *CharacterLiteral();
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *BooleanLiteral();
    antlr4::tree::TerminalNode *PointerLiteral();
    antlr4::tree::TerminalNode *UserDefinedLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LiteralContext* literal();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool regexp_bodySempred(Regexp_bodyContext *_localctx, size_t predicateIndex);
  bool memoMapTypeSempred(MemoMapTypeContext *_localctx, size_t predicateIndex);
  bool nnet_layer_typeSempred(Nnet_layer_typeContext *_localctx, size_t predicateIndex);
  bool otherLineSempred(OtherLineContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

