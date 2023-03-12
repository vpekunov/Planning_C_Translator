
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
#include "ReentPreParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ReentPreParser.
 */
class  ReentPreParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterTranslationUnit(ReentPreParser::TranslationUnitContext *ctx) = 0;
  virtual void exitTranslationUnit(ReentPreParser::TranslationUnitContext *ctx) = 0;

  virtual void enterStatementseq(ReentPreParser::StatementseqContext *ctx) = 0;
  virtual void exitStatementseq(ReentPreParser::StatementseqContext *ctx) = 0;

  virtual void enterStatement(ReentPreParser::StatementContext *ctx) = 0;
  virtual void exitStatement(ReentPreParser::StatementContext *ctx) = 0;

  virtual void enterDef_pattern(ReentPreParser::Def_patternContext *ctx) = 0;
  virtual void exitDef_pattern(ReentPreParser::Def_patternContext *ctx) = 0;

  virtual void enterPut_fact(ReentPreParser::Put_factContext *ctx) = 0;
  virtual void exitPut_fact(ReentPreParser::Put_factContext *ctx) = 0;

  virtual void enterDef_pattern_param(ReentPreParser::Def_pattern_paramContext *ctx) = 0;
  virtual void exitDef_pattern_param(ReentPreParser::Def_pattern_paramContext *ctx) = 0;

  virtual void enterSimple_xpath_expression(ReentPreParser::Simple_xpath_expressionContext *ctx) = 0;
  virtual void exitSimple_xpath_expression(ReentPreParser::Simple_xpath_expressionContext *ctx) = 0;

  virtual void enterXpath_and_expression(ReentPreParser::Xpath_and_expressionContext *ctx) = 0;
  virtual void exitXpath_and_expression(ReentPreParser::Xpath_and_expressionContext *ctx) = 0;

  virtual void enterXpath_rel_expression(ReentPreParser::Xpath_rel_expressionContext *ctx) = 0;
  virtual void exitXpath_rel_expression(ReentPreParser::Xpath_rel_expressionContext *ctx) = 0;

  virtual void enterXpath_mul_expression(ReentPreParser::Xpath_mul_expressionContext *ctx) = 0;
  virtual void exitXpath_mul_expression(ReentPreParser::Xpath_mul_expressionContext *ctx) = 0;

  virtual void enterXpath_plus_expression(ReentPreParser::Xpath_plus_expressionContext *ctx) = 0;
  virtual void exitXpath_plus_expression(ReentPreParser::Xpath_plus_expressionContext *ctx) = 0;

  virtual void enterXpath_unary_expression(ReentPreParser::Xpath_unary_expressionContext *ctx) = 0;
  virtual void exitXpath_unary_expression(ReentPreParser::Xpath_unary_expressionContext *ctx) = 0;

  virtual void enterXpath_query(ReentPreParser::Xpath_queryContext *ctx) = 0;
  virtual void exitXpath_query(ReentPreParser::Xpath_queryContext *ctx) = 0;

  virtual void enterXpath_predicate(ReentPreParser::Xpath_predicateContext *ctx) = 0;
  virtual void exitXpath_predicate(ReentPreParser::Xpath_predicateContext *ctx) = 0;

  virtual void enterXpath_fun_params(ReentPreParser::Xpath_fun_paramsContext *ctx) = 0;
  virtual void exitXpath_fun_params(ReentPreParser::Xpath_fun_paramsContext *ctx) = 0;

  virtual void enterRegexps(ReentPreParser::RegexpsContext *ctx) = 0;
  virtual void exitRegexps(ReentPreParser::RegexpsContext *ctx) = 0;

  virtual void enterRegexp_lines(ReentPreParser::Regexp_linesContext *ctx) = 0;
  virtual void exitRegexp_lines(ReentPreParser::Regexp_linesContext *ctx) = 0;

  virtual void enterRegexp_body(ReentPreParser::Regexp_bodyContext *ctx) = 0;
  virtual void exitRegexp_body(ReentPreParser::Regexp_bodyContext *ctx) = 0;

  virtual void enterPlc_regexp_logical(ReentPreParser::Plc_regexp_logicalContext *ctx) = 0;
  virtual void exitPlc_regexp_logical(ReentPreParser::Plc_regexp_logicalContext *ctx) = 0;

  virtual void enterPlc_regexp_var(ReentPreParser::Plc_regexp_varContext *ctx) = 0;
  virtual void exitPlc_regexp_var(ReentPreParser::Plc_regexp_varContext *ctx) = 0;

  virtual void enterPlc_regexp_equal(ReentPreParser::Plc_regexp_equalContext *ctx) = 0;
  virtual void exitPlc_regexp_equal(ReentPreParser::Plc_regexp_equalContext *ctx) = 0;

  virtual void enterPlc_regexp_not_equal(ReentPreParser::Plc_regexp_not_equalContext *ctx) = 0;
  virtual void exitPlc_regexp_not_equal(ReentPreParser::Plc_regexp_not_equalContext *ctx) = 0;

  virtual void enterPlc_regexp_query(ReentPreParser::Plc_regexp_queryContext *ctx) = 0;
  virtual void exitPlc_regexp_query(ReentPreParser::Plc_regexp_queryContext *ctx) = 0;

  virtual void enterRegexp_or_sequence(ReentPreParser::Regexp_or_sequenceContext *ctx) = 0;
  virtual void exitRegexp_or_sequence(ReentPreParser::Regexp_or_sequenceContext *ctx) = 0;

  virtual void enterRegexp_and_sequence(ReentPreParser::Regexp_and_sequenceContext *ctx) = 0;
  virtual void exitRegexp_and_sequence(ReentPreParser::Regexp_and_sequenceContext *ctx) = 0;

  virtual void enterRegexp_unary(ReentPreParser::Regexp_unaryContext *ctx) = 0;
  virtual void exitRegexp_unary(ReentPreParser::Regexp_unaryContext *ctx) = 0;

  virtual void enterRegexp_pred(ReentPreParser::Regexp_predContext *ctx) = 0;
  virtual void exitRegexp_pred(ReentPreParser::Regexp_predContext *ctx) = 0;

  virtual void enterRegexp_pred_arg(ReentPreParser::Regexp_pred_argContext *ctx) = 0;
  virtual void exitRegexp_pred_arg(ReentPreParser::Regexp_pred_argContext *ctx) = 0;

  virtual void enterRegexp_pred_parallel(ReentPreParser::Regexp_pred_parallelContext *ctx) = 0;
  virtual void exitRegexp_pred_parallel(ReentPreParser::Regexp_pred_parallelContext *ctx) = 0;

  virtual void enterDefModule(ReentPreParser::DefModuleContext *ctx) = 0;
  virtual void exitDefModule(ReentPreParser::DefModuleContext *ctx) = 0;

  virtual void enterDefModuleDescriptor(ReentPreParser::DefModuleDescriptorContext *ctx) = 0;
  virtual void exitDefModuleDescriptor(ReentPreParser::DefModuleDescriptorContext *ctx) = 0;

  virtual void enterDefMemoization(ReentPreParser::DefMemoizationContext *ctx) = 0;
  virtual void exitDefMemoization(ReentPreParser::DefMemoizationContext *ctx) = 0;

  virtual void enterPreprocPasses(ReentPreParser::PreprocPassesContext *ctx) = 0;
  virtual void exitPreprocPasses(ReentPreParser::PreprocPassesContext *ctx) = 0;

  virtual void enterAddScan(ReentPreParser::AddScanContext *ctx) = 0;
  virtual void exitAddScan(ReentPreParser::AddScanContext *ctx) = 0;

  virtual void enterScan(ReentPreParser::ScanContext *ctx) = 0;
  virtual void exitScan(ReentPreParser::ScanContext *ctx) = 0;

  virtual void enterAddParse(ReentPreParser::AddParseContext *ctx) = 0;
  virtual void exitAddParse(ReentPreParser::AddParseContext *ctx) = 0;

  virtual void enterParse(ReentPreParser::ParseContext *ctx) = 0;
  virtual void exitParse(ReentPreParser::ParseContext *ctx) = 0;

  virtual void enterScanners_list(ReentPreParser::Scanners_listContext *ctx) = 0;
  virtual void exitScanners_list(ReentPreParser::Scanners_listContext *ctx) = 0;

  virtual void enterMemoMapItem(ReentPreParser::MemoMapItemContext *ctx) = 0;
  virtual void exitMemoMapItem(ReentPreParser::MemoMapItemContext *ctx) = 0;

  virtual void enterMemoMapType(ReentPreParser::MemoMapTypeContext *ctx) = 0;
  virtual void exitMemoMapType(ReentPreParser::MemoMapTypeContext *ctx) = 0;

  virtual void enterCpp_balanced_expression(ReentPreParser::Cpp_balanced_expressionContext *ctx) = 0;
  virtual void exitCpp_balanced_expression(ReentPreParser::Cpp_balanced_expressionContext *ctx) = 0;

  virtual void enterMemoizationStyle(ReentPreParser::MemoizationStyleContext *ctx) = 0;
  virtual void exitMemoizationStyle(ReentPreParser::MemoizationStyleContext *ctx) = 0;

  virtual void enterMgua(ReentPreParser::MguaContext *ctx) = 0;
  virtual void exitMgua(ReentPreParser::MguaContext *ctx) = 0;

  virtual void enterNnet(ReentPreParser::NnetContext *ctx) = 0;
  virtual void exitNnet(ReentPreParser::NnetContext *ctx) = 0;

  virtual void enterExtrapolator(ReentPreParser::ExtrapolatorContext *ctx) = 0;
  virtual void exitExtrapolator(ReentPreParser::ExtrapolatorContext *ctx) = 0;

  virtual void enterNnet_layer_specifier(ReentPreParser::Nnet_layer_specifierContext *ctx) = 0;
  virtual void exitNnet_layer_specifier(ReentPreParser::Nnet_layer_specifierContext *ctx) = 0;

  virtual void enterNnet_layer_type(ReentPreParser::Nnet_layer_typeContext *ctx) = 0;
  virtual void exitNnet_layer_type(ReentPreParser::Nnet_layer_typeContext *ctx) = 0;

  virtual void enterControlPredicate(ReentPreParser::ControlPredicateContext *ctx) = 0;
  virtual void exitControlPredicate(ReentPreParser::ControlPredicateContext *ctx) = 0;

  virtual void enterAutomated_control(ReentPreParser::Automated_controlContext *ctx) = 0;
  virtual void exitAutomated_control(ReentPreParser::Automated_controlContext *ctx) = 0;

  virtual void enterBy_conditions_control(ReentPreParser::By_conditions_controlContext *ctx) = 0;
  virtual void exitBy_conditions_control(ReentPreParser::By_conditions_controlContext *ctx) = 0;

  virtual void enterBlockHeader(ReentPreParser::BlockHeaderContext *ctx) = 0;
  virtual void exitBlockHeader(ReentPreParser::BlockHeaderContext *ctx) = 0;

  virtual void enterTypeItem(ReentPreParser::TypeItemContext *ctx) = 0;
  virtual void exitTypeItem(ReentPreParser::TypeItemContext *ctx) = 0;

  virtual void enterTypeSpecifier(ReentPreParser::TypeSpecifierContext *ctx) = 0;
  virtual void exitTypeSpecifier(ReentPreParser::TypeSpecifierContext *ctx) = 0;

  virtual void enterTemplateParameters(ReentPreParser::TemplateParametersContext *ctx) = 0;
  virtual void exitTemplateParameters(ReentPreParser::TemplateParametersContext *ctx) = 0;

  virtual void enterTemplateParameter(ReentPreParser::TemplateParameterContext *ctx) = 0;
  virtual void exitTemplateParameter(ReentPreParser::TemplateParameterContext *ctx) = 0;

  virtual void enterParameter(ReentPreParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(ReentPreParser::ParameterContext *ctx) = 0;

  virtual void enterDimension(ReentPreParser::DimensionContext *ctx) = 0;
  virtual void exitDimension(ReentPreParser::DimensionContext *ctx) = 0;

  virtual void enterProlog_goal(ReentPreParser::Prolog_goalContext *ctx) = 0;
  virtual void exitProlog_goal(ReentPreParser::Prolog_goalContext *ctx) = 0;

  virtual void enterProlog_statement(ReentPreParser::Prolog_statementContext *ctx) = 0;
  virtual void exitProlog_statement(ReentPreParser::Prolog_statementContext *ctx) = 0;

  virtual void enterProlog_parameters(ReentPreParser::Prolog_parametersContext *ctx) = 0;
  virtual void exitProlog_parameters(ReentPreParser::Prolog_parametersContext *ctx) = 0;

  virtual void enterProlog_predicates(ReentPreParser::Prolog_predicatesContext *ctx) = 0;
  virtual void exitProlog_predicates(ReentPreParser::Prolog_predicatesContext *ctx) = 0;

  virtual void enterProlog_parameter(ReentPreParser::Prolog_parameterContext *ctx) = 0;
  virtual void exitProlog_parameter(ReentPreParser::Prolog_parameterContext *ctx) = 0;

  virtual void enterProlog_parameter_list(ReentPreParser::Prolog_parameter_listContext *ctx) = 0;
  virtual void exitProlog_parameter_list(ReentPreParser::Prolog_parameter_listContext *ctx) = 0;

  virtual void enterProlog_inside_list(ReentPreParser::Prolog_inside_listContext *ctx) = 0;
  virtual void exitProlog_inside_list(ReentPreParser::Prolog_inside_listContext *ctx) = 0;

  virtual void enterProlog_predicate(ReentPreParser::Prolog_predicateContext *ctx) = 0;
  virtual void exitProlog_predicate(ReentPreParser::Prolog_predicateContext *ctx) = 0;

  virtual void enterProlog_if_then(ReentPreParser::Prolog_if_thenContext *ctx) = 0;
  virtual void exitProlog_if_then(ReentPreParser::Prolog_if_thenContext *ctx) = 0;

  virtual void enterIs_expression(ReentPreParser::Is_expressionContext *ctx) = 0;
  virtual void exitIs_expression(ReentPreParser::Is_expressionContext *ctx) = 0;

  virtual void enterRelational_expression(ReentPreParser::Relational_expressionContext *ctx) = 0;
  virtual void exitRelational_expression(ReentPreParser::Relational_expressionContext *ctx) = 0;

  virtual void enterProlog_relation(ReentPreParser::Prolog_relationContext *ctx) = 0;
  virtual void exitProlog_relation(ReentPreParser::Prolog_relationContext *ctx) = 0;

  virtual void enterPow_expression(ReentPreParser::Pow_expressionContext *ctx) = 0;
  virtual void exitPow_expression(ReentPreParser::Pow_expressionContext *ctx) = 0;

  virtual void enterProlog_pow(ReentPreParser::Prolog_powContext *ctx) = 0;
  virtual void exitProlog_pow(ReentPreParser::Prolog_powContext *ctx) = 0;

  virtual void enterMul_div_expression(ReentPreParser::Mul_div_expressionContext *ctx) = 0;
  virtual void exitMul_div_expression(ReentPreParser::Mul_div_expressionContext *ctx) = 0;

  virtual void enterProlog_mul_div(ReentPreParser::Prolog_mul_divContext *ctx) = 0;
  virtual void exitProlog_mul_div(ReentPreParser::Prolog_mul_divContext *ctx) = 0;

  virtual void enterPlus_min_expression(ReentPreParser::Plus_min_expressionContext *ctx) = 0;
  virtual void exitPlus_min_expression(ReentPreParser::Plus_min_expressionContext *ctx) = 0;

  virtual void enterProlog_plus_minus(ReentPreParser::Prolog_plus_minusContext *ctx) = 0;
  virtual void exitProlog_plus_minus(ReentPreParser::Prolog_plus_minusContext *ctx) = 0;

  virtual void enterUnary_expression(ReentPreParser::Unary_expressionContext *ctx) = 0;
  virtual void exitUnary_expression(ReentPreParser::Unary_expressionContext *ctx) = 0;

  virtual void enterOperand(ReentPreParser::OperandContext *ctx) = 0;
  virtual void exitOperand(ReentPreParser::OperandContext *ctx) = 0;

  virtual void enterOperandList(ReentPreParser::OperandListContext *ctx) = 0;
  virtual void exitOperandList(ReentPreParser::OperandListContext *ctx) = 0;

  virtual void enterProlog_term(ReentPreParser::Prolog_termContext *ctx) = 0;
  virtual void exitProlog_term(ReentPreParser::Prolog_termContext *ctx) = 0;

  virtual void enterProlog_call(ReentPreParser::Prolog_callContext *ctx) = 0;
  virtual void exitProlog_call(ReentPreParser::Prolog_callContext *ctx) = 0;

  virtual void enterProlog_call_params(ReentPreParser::Prolog_call_paramsContext *ctx) = 0;
  virtual void exitProlog_call_params(ReentPreParser::Prolog_call_paramsContext *ctx) = 0;

  virtual void enterProlog_predicate_id(ReentPreParser::Prolog_predicate_idContext *ctx) = 0;
  virtual void exitProlog_predicate_id(ReentPreParser::Prolog_predicate_idContext *ctx) = 0;

  virtual void enterCpp_code_without_at(ReentPreParser::Cpp_code_without_atContext *ctx) = 0;
  virtual void exitCpp_code_without_at(ReentPreParser::Cpp_code_without_atContext *ctx) = 0;

  virtual void enterCpp_code_continues(ReentPreParser::Cpp_code_continuesContext *ctx) = 0;
  virtual void exitCpp_code_continues(ReentPreParser::Cpp_code_continuesContext *ctx) = 0;

  virtual void enterOtherLine(ReentPreParser::OtherLineContext *ctx) = 0;
  virtual void exitOtherLine(ReentPreParser::OtherLineContext *ctx) = 0;

  virtual void enterLiteral(ReentPreParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(ReentPreParser::LiteralContext *ctx) = 0;


};

