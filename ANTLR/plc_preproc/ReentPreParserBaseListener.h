
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
#include "ReentPreParserListener.h"


/**
 * This class provides an empty implementation of ReentPreParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ReentPreParserBaseListener : public ReentPreParserListener {
public:

  virtual void enterTranslationUnit(ReentPreParser::TranslationUnitContext * /*ctx*/) override { }
  virtual void exitTranslationUnit(ReentPreParser::TranslationUnitContext * /*ctx*/) override { }

  virtual void enterStatementseq(ReentPreParser::StatementseqContext * /*ctx*/) override { }
  virtual void exitStatementseq(ReentPreParser::StatementseqContext * /*ctx*/) override { }

  virtual void enterStatement(ReentPreParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(ReentPreParser::StatementContext * /*ctx*/) override { }

  virtual void enterDef_pattern(ReentPreParser::Def_patternContext * /*ctx*/) override { }
  virtual void exitDef_pattern(ReentPreParser::Def_patternContext * /*ctx*/) override { }

  virtual void enterPut_fact(ReentPreParser::Put_factContext * /*ctx*/) override { }
  virtual void exitPut_fact(ReentPreParser::Put_factContext * /*ctx*/) override { }

  virtual void enterDef_pattern_param(ReentPreParser::Def_pattern_paramContext * /*ctx*/) override { }
  virtual void exitDef_pattern_param(ReentPreParser::Def_pattern_paramContext * /*ctx*/) override { }

  virtual void enterSimple_xpath_expression(ReentPreParser::Simple_xpath_expressionContext * /*ctx*/) override { }
  virtual void exitSimple_xpath_expression(ReentPreParser::Simple_xpath_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_and_expression(ReentPreParser::Xpath_and_expressionContext * /*ctx*/) override { }
  virtual void exitXpath_and_expression(ReentPreParser::Xpath_and_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_rel_expression(ReentPreParser::Xpath_rel_expressionContext * /*ctx*/) override { }
  virtual void exitXpath_rel_expression(ReentPreParser::Xpath_rel_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_mul_expression(ReentPreParser::Xpath_mul_expressionContext * /*ctx*/) override { }
  virtual void exitXpath_mul_expression(ReentPreParser::Xpath_mul_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_plus_expression(ReentPreParser::Xpath_plus_expressionContext * /*ctx*/) override { }
  virtual void exitXpath_plus_expression(ReentPreParser::Xpath_plus_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_unary_expression(ReentPreParser::Xpath_unary_expressionContext * /*ctx*/) override { }
  virtual void exitXpath_unary_expression(ReentPreParser::Xpath_unary_expressionContext * /*ctx*/) override { }

  virtual void enterXpath_query(ReentPreParser::Xpath_queryContext * /*ctx*/) override { }
  virtual void exitXpath_query(ReentPreParser::Xpath_queryContext * /*ctx*/) override { }

  virtual void enterXpath_predicate(ReentPreParser::Xpath_predicateContext * /*ctx*/) override { }
  virtual void exitXpath_predicate(ReentPreParser::Xpath_predicateContext * /*ctx*/) override { }

  virtual void enterXpath_fun_params(ReentPreParser::Xpath_fun_paramsContext * /*ctx*/) override { }
  virtual void exitXpath_fun_params(ReentPreParser::Xpath_fun_paramsContext * /*ctx*/) override { }

  virtual void enterDef_xpath(ReentPreParser::Def_xpathContext * /*ctx*/) override { }
  virtual void exitDef_xpath(ReentPreParser::Def_xpathContext * /*ctx*/) override { }

  virtual void enterDef_xpath_param(ReentPreParser::Def_xpath_paramContext * /*ctx*/) override { }
  virtual void exitDef_xpath_param(ReentPreParser::Def_xpath_paramContext * /*ctx*/) override { }

  virtual void enterDef_xpath_expression(ReentPreParser::Def_xpath_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_expression(ReentPreParser::Def_xpath_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_and_expression(ReentPreParser::Def_xpath_and_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_and_expression(ReentPreParser::Def_xpath_and_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_rel_expression(ReentPreParser::Def_xpath_rel_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_rel_expression(ReentPreParser::Def_xpath_rel_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_mul_expression(ReentPreParser::Def_xpath_mul_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_mul_expression(ReentPreParser::Def_xpath_mul_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_plus_expression(ReentPreParser::Def_xpath_plus_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_plus_expression(ReentPreParser::Def_xpath_plus_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_unary_expression(ReentPreParser::Def_xpath_unary_expressionContext * /*ctx*/) override { }
  virtual void exitDef_xpath_unary_expression(ReentPreParser::Def_xpath_unary_expressionContext * /*ctx*/) override { }

  virtual void enterDef_xpath_query(ReentPreParser::Def_xpath_queryContext * /*ctx*/) override { }
  virtual void exitDef_xpath_query(ReentPreParser::Def_xpath_queryContext * /*ctx*/) override { }

  virtual void enterDef_xpath_predicate(ReentPreParser::Def_xpath_predicateContext * /*ctx*/) override { }
  virtual void exitDef_xpath_predicate(ReentPreParser::Def_xpath_predicateContext * /*ctx*/) override { }

  virtual void enterDef_xpath_fun_params(ReentPreParser::Def_xpath_fun_paramsContext * /*ctx*/) override { }
  virtual void exitDef_xpath_fun_params(ReentPreParser::Def_xpath_fun_paramsContext * /*ctx*/) override { }

  virtual void enterRegexps(ReentPreParser::RegexpsContext * /*ctx*/) override { }
  virtual void exitRegexps(ReentPreParser::RegexpsContext * /*ctx*/) override { }

  virtual void enterRegexp_lines(ReentPreParser::Regexp_linesContext * /*ctx*/) override { }
  virtual void exitRegexp_lines(ReentPreParser::Regexp_linesContext * /*ctx*/) override { }

  virtual void enterRegexp_body(ReentPreParser::Regexp_bodyContext * /*ctx*/) override { }
  virtual void exitRegexp_body(ReentPreParser::Regexp_bodyContext * /*ctx*/) override { }

  virtual void enterPlc_regexp_logical(ReentPreParser::Plc_regexp_logicalContext * /*ctx*/) override { }
  virtual void exitPlc_regexp_logical(ReentPreParser::Plc_regexp_logicalContext * /*ctx*/) override { }

  virtual void enterPlc_regexp_var(ReentPreParser::Plc_regexp_varContext * /*ctx*/) override { }
  virtual void exitPlc_regexp_var(ReentPreParser::Plc_regexp_varContext * /*ctx*/) override { }

  virtual void enterPlc_regexp_equal(ReentPreParser::Plc_regexp_equalContext * /*ctx*/) override { }
  virtual void exitPlc_regexp_equal(ReentPreParser::Plc_regexp_equalContext * /*ctx*/) override { }

  virtual void enterPlc_regexp_not_equal(ReentPreParser::Plc_regexp_not_equalContext * /*ctx*/) override { }
  virtual void exitPlc_regexp_not_equal(ReentPreParser::Plc_regexp_not_equalContext * /*ctx*/) override { }

  virtual void enterPlc_regexp_query(ReentPreParser::Plc_regexp_queryContext * /*ctx*/) override { }
  virtual void exitPlc_regexp_query(ReentPreParser::Plc_regexp_queryContext * /*ctx*/) override { }

  virtual void enterRegexp_or_sequence(ReentPreParser::Regexp_or_sequenceContext * /*ctx*/) override { }
  virtual void exitRegexp_or_sequence(ReentPreParser::Regexp_or_sequenceContext * /*ctx*/) override { }

  virtual void enterRegexp_and_sequence(ReentPreParser::Regexp_and_sequenceContext * /*ctx*/) override { }
  virtual void exitRegexp_and_sequence(ReentPreParser::Regexp_and_sequenceContext * /*ctx*/) override { }

  virtual void enterRegexp_unary(ReentPreParser::Regexp_unaryContext * /*ctx*/) override { }
  virtual void exitRegexp_unary(ReentPreParser::Regexp_unaryContext * /*ctx*/) override { }

  virtual void enterRegexp_pred(ReentPreParser::Regexp_predContext * /*ctx*/) override { }
  virtual void exitRegexp_pred(ReentPreParser::Regexp_predContext * /*ctx*/) override { }

  virtual void enterRegexp_pred_arg(ReentPreParser::Regexp_pred_argContext * /*ctx*/) override { }
  virtual void exitRegexp_pred_arg(ReentPreParser::Regexp_pred_argContext * /*ctx*/) override { }

  virtual void enterRegexp_pred_parallel(ReentPreParser::Regexp_pred_parallelContext * /*ctx*/) override { }
  virtual void exitRegexp_pred_parallel(ReentPreParser::Regexp_pred_parallelContext * /*ctx*/) override { }

  virtual void enterDefModule(ReentPreParser::DefModuleContext * /*ctx*/) override { }
  virtual void exitDefModule(ReentPreParser::DefModuleContext * /*ctx*/) override { }

  virtual void enterDefModuleDescriptors(ReentPreParser::DefModuleDescriptorsContext * /*ctx*/) override { }
  virtual void exitDefModuleDescriptors(ReentPreParser::DefModuleDescriptorsContext * /*ctx*/) override { }

  virtual void enterDefModuleDescriptor(ReentPreParser::DefModuleDescriptorContext * /*ctx*/) override { }
  virtual void exitDefModuleDescriptor(ReentPreParser::DefModuleDescriptorContext * /*ctx*/) override { }

  virtual void enterDefMemoization(ReentPreParser::DefMemoizationContext * /*ctx*/) override { }
  virtual void exitDefMemoization(ReentPreParser::DefMemoizationContext * /*ctx*/) override { }

  virtual void enterPreprocPasses(ReentPreParser::PreprocPassesContext * /*ctx*/) override { }
  virtual void exitPreprocPasses(ReentPreParser::PreprocPassesContext * /*ctx*/) override { }

  virtual void enterAddScan(ReentPreParser::AddScanContext * /*ctx*/) override { }
  virtual void exitAddScan(ReentPreParser::AddScanContext * /*ctx*/) override { }

  virtual void enterScan(ReentPreParser::ScanContext * /*ctx*/) override { }
  virtual void exitScan(ReentPreParser::ScanContext * /*ctx*/) override { }

  virtual void enterAddParse(ReentPreParser::AddParseContext * /*ctx*/) override { }
  virtual void exitAddParse(ReentPreParser::AddParseContext * /*ctx*/) override { }

  virtual void enterParse(ReentPreParser::ParseContext * /*ctx*/) override { }
  virtual void exitParse(ReentPreParser::ParseContext * /*ctx*/) override { }

  virtual void enterScanners_list(ReentPreParser::Scanners_listContext * /*ctx*/) override { }
  virtual void exitScanners_list(ReentPreParser::Scanners_listContext * /*ctx*/) override { }

  virtual void enterMemoMapItem(ReentPreParser::MemoMapItemContext * /*ctx*/) override { }
  virtual void exitMemoMapItem(ReentPreParser::MemoMapItemContext * /*ctx*/) override { }

  virtual void enterMemoMapType(ReentPreParser::MemoMapTypeContext * /*ctx*/) override { }
  virtual void exitMemoMapType(ReentPreParser::MemoMapTypeContext * /*ctx*/) override { }

  virtual void enterCpp_balanced_expression(ReentPreParser::Cpp_balanced_expressionContext * /*ctx*/) override { }
  virtual void exitCpp_balanced_expression(ReentPreParser::Cpp_balanced_expressionContext * /*ctx*/) override { }

  virtual void enterMemoizationStyle(ReentPreParser::MemoizationStyleContext * /*ctx*/) override { }
  virtual void exitMemoizationStyle(ReentPreParser::MemoizationStyleContext * /*ctx*/) override { }

  virtual void enterMgua(ReentPreParser::MguaContext * /*ctx*/) override { }
  virtual void exitMgua(ReentPreParser::MguaContext * /*ctx*/) override { }

  virtual void enterNnet(ReentPreParser::NnetContext * /*ctx*/) override { }
  virtual void exitNnet(ReentPreParser::NnetContext * /*ctx*/) override { }

  virtual void enterExtrapolator(ReentPreParser::ExtrapolatorContext * /*ctx*/) override { }
  virtual void exitExtrapolator(ReentPreParser::ExtrapolatorContext * /*ctx*/) override { }

  virtual void enterNnet_layer_specifier(ReentPreParser::Nnet_layer_specifierContext * /*ctx*/) override { }
  virtual void exitNnet_layer_specifier(ReentPreParser::Nnet_layer_specifierContext * /*ctx*/) override { }

  virtual void enterNnet_layer_type(ReentPreParser::Nnet_layer_typeContext * /*ctx*/) override { }
  virtual void exitNnet_layer_type(ReentPreParser::Nnet_layer_typeContext * /*ctx*/) override { }

  virtual void enterControlPredicate(ReentPreParser::ControlPredicateContext * /*ctx*/) override { }
  virtual void exitControlPredicate(ReentPreParser::ControlPredicateContext * /*ctx*/) override { }

  virtual void enterAutomated_control(ReentPreParser::Automated_controlContext * /*ctx*/) override { }
  virtual void exitAutomated_control(ReentPreParser::Automated_controlContext * /*ctx*/) override { }

  virtual void enterBy_conditions_control(ReentPreParser::By_conditions_controlContext * /*ctx*/) override { }
  virtual void exitBy_conditions_control(ReentPreParser::By_conditions_controlContext * /*ctx*/) override { }

  virtual void enterBlockHeader(ReentPreParser::BlockHeaderContext * /*ctx*/) override { }
  virtual void exitBlockHeader(ReentPreParser::BlockHeaderContext * /*ctx*/) override { }

  virtual void enterTypeItem(ReentPreParser::TypeItemContext * /*ctx*/) override { }
  virtual void exitTypeItem(ReentPreParser::TypeItemContext * /*ctx*/) override { }

  virtual void enterTypeSpecifier(ReentPreParser::TypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeSpecifier(ReentPreParser::TypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTemplateParameters(ReentPreParser::TemplateParametersContext * /*ctx*/) override { }
  virtual void exitTemplateParameters(ReentPreParser::TemplateParametersContext * /*ctx*/) override { }

  virtual void enterTemplateParameter(ReentPreParser::TemplateParameterContext * /*ctx*/) override { }
  virtual void exitTemplateParameter(ReentPreParser::TemplateParameterContext * /*ctx*/) override { }

  virtual void enterParameter(ReentPreParser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(ReentPreParser::ParameterContext * /*ctx*/) override { }

  virtual void enterDimension(ReentPreParser::DimensionContext * /*ctx*/) override { }
  virtual void exitDimension(ReentPreParser::DimensionContext * /*ctx*/) override { }

  virtual void enterProlog_goal(ReentPreParser::Prolog_goalContext * /*ctx*/) override { }
  virtual void exitProlog_goal(ReentPreParser::Prolog_goalContext * /*ctx*/) override { }

  virtual void enterProlog_statement(ReentPreParser::Prolog_statementContext * /*ctx*/) override { }
  virtual void exitProlog_statement(ReentPreParser::Prolog_statementContext * /*ctx*/) override { }

  virtual void enterProlog_parameters(ReentPreParser::Prolog_parametersContext * /*ctx*/) override { }
  virtual void exitProlog_parameters(ReentPreParser::Prolog_parametersContext * /*ctx*/) override { }

  virtual void enterProlog_predicates(ReentPreParser::Prolog_predicatesContext * /*ctx*/) override { }
  virtual void exitProlog_predicates(ReentPreParser::Prolog_predicatesContext * /*ctx*/) override { }

  virtual void enterProlog_parameter(ReentPreParser::Prolog_parameterContext * /*ctx*/) override { }
  virtual void exitProlog_parameter(ReentPreParser::Prolog_parameterContext * /*ctx*/) override { }

  virtual void enterProlog_parameter_list(ReentPreParser::Prolog_parameter_listContext * /*ctx*/) override { }
  virtual void exitProlog_parameter_list(ReentPreParser::Prolog_parameter_listContext * /*ctx*/) override { }

  virtual void enterProlog_inside_list(ReentPreParser::Prolog_inside_listContext * /*ctx*/) override { }
  virtual void exitProlog_inside_list(ReentPreParser::Prolog_inside_listContext * /*ctx*/) override { }

  virtual void enterProlog_predicate(ReentPreParser::Prolog_predicateContext * /*ctx*/) override { }
  virtual void exitProlog_predicate(ReentPreParser::Prolog_predicateContext * /*ctx*/) override { }

  virtual void enterProlog_if_then(ReentPreParser::Prolog_if_thenContext * /*ctx*/) override { }
  virtual void exitProlog_if_then(ReentPreParser::Prolog_if_thenContext * /*ctx*/) override { }

  virtual void enterIs_expression(ReentPreParser::Is_expressionContext * /*ctx*/) override { }
  virtual void exitIs_expression(ReentPreParser::Is_expressionContext * /*ctx*/) override { }

  virtual void enterRelational_expression(ReentPreParser::Relational_expressionContext * /*ctx*/) override { }
  virtual void exitRelational_expression(ReentPreParser::Relational_expressionContext * /*ctx*/) override { }

  virtual void enterProlog_relation(ReentPreParser::Prolog_relationContext * /*ctx*/) override { }
  virtual void exitProlog_relation(ReentPreParser::Prolog_relationContext * /*ctx*/) override { }

  virtual void enterPow_expression(ReentPreParser::Pow_expressionContext * /*ctx*/) override { }
  virtual void exitPow_expression(ReentPreParser::Pow_expressionContext * /*ctx*/) override { }

  virtual void enterProlog_pow(ReentPreParser::Prolog_powContext * /*ctx*/) override { }
  virtual void exitProlog_pow(ReentPreParser::Prolog_powContext * /*ctx*/) override { }

  virtual void enterMul_div_expression(ReentPreParser::Mul_div_expressionContext * /*ctx*/) override { }
  virtual void exitMul_div_expression(ReentPreParser::Mul_div_expressionContext * /*ctx*/) override { }

  virtual void enterProlog_mul_div(ReentPreParser::Prolog_mul_divContext * /*ctx*/) override { }
  virtual void exitProlog_mul_div(ReentPreParser::Prolog_mul_divContext * /*ctx*/) override { }

  virtual void enterPlus_min_expression(ReentPreParser::Plus_min_expressionContext * /*ctx*/) override { }
  virtual void exitPlus_min_expression(ReentPreParser::Plus_min_expressionContext * /*ctx*/) override { }

  virtual void enterProlog_plus_minus(ReentPreParser::Prolog_plus_minusContext * /*ctx*/) override { }
  virtual void exitProlog_plus_minus(ReentPreParser::Prolog_plus_minusContext * /*ctx*/) override { }

  virtual void enterUnary_expression(ReentPreParser::Unary_expressionContext * /*ctx*/) override { }
  virtual void exitUnary_expression(ReentPreParser::Unary_expressionContext * /*ctx*/) override { }

  virtual void enterOperand(ReentPreParser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(ReentPreParser::OperandContext * /*ctx*/) override { }

  virtual void enterOperandList(ReentPreParser::OperandListContext * /*ctx*/) override { }
  virtual void exitOperandList(ReentPreParser::OperandListContext * /*ctx*/) override { }

  virtual void enterProlog_term(ReentPreParser::Prolog_termContext * /*ctx*/) override { }
  virtual void exitProlog_term(ReentPreParser::Prolog_termContext * /*ctx*/) override { }

  virtual void enterProlog_call(ReentPreParser::Prolog_callContext * /*ctx*/) override { }
  virtual void exitProlog_call(ReentPreParser::Prolog_callContext * /*ctx*/) override { }

  virtual void enterProlog_call_params(ReentPreParser::Prolog_call_paramsContext * /*ctx*/) override { }
  virtual void exitProlog_call_params(ReentPreParser::Prolog_call_paramsContext * /*ctx*/) override { }

  virtual void enterProlog_predicate_id(ReentPreParser::Prolog_predicate_idContext * /*ctx*/) override { }
  virtual void exitProlog_predicate_id(ReentPreParser::Prolog_predicate_idContext * /*ctx*/) override { }

  virtual void enterCpp_code_without_at(ReentPreParser::Cpp_code_without_atContext * /*ctx*/) override { }
  virtual void exitCpp_code_without_at(ReentPreParser::Cpp_code_without_atContext * /*ctx*/) override { }

  virtual void enterOtherLine(ReentPreParser::OtherLineContext * /*ctx*/) override { }
  virtual void exitOtherLine(ReentPreParser::OtherLineContext * /*ctx*/) override { }

  virtual void enterLiteral(ReentPreParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(ReentPreParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

