
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>


// Generated from ReentParser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ReentParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ReentParser.
 */
class  ReentParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterTranslationUnit(ReentParser::TranslationUnitContext *ctx) = 0;
  virtual void exitTranslationUnit(ReentParser::TranslationUnitContext *ctx) = 0;

  virtual void enterAnyIdentifier(ReentParser::AnyIdentifierContext *ctx) = 0;
  virtual void exitAnyIdentifier(ReentParser::AnyIdentifierContext *ctx) = 0;

  virtual void enterPrimaryExpression(ReentParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(ReentParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterIdExpression(ReentParser::IdExpressionContext *ctx) = 0;
  virtual void exitIdExpression(ReentParser::IdExpressionContext *ctx) = 0;

  virtual void enterReent_funs_id(ReentParser::Reent_funs_idContext *ctx) = 0;
  virtual void exitReent_funs_id(ReentParser::Reent_funs_idContext *ctx) = 0;

  virtual void enterChain_funs_id(ReentParser::Chain_funs_idContext *ctx) = 0;
  virtual void exitChain_funs_id(ReentParser::Chain_funs_idContext *ctx) = 0;

  virtual void enterUnqualifiedId(ReentParser::UnqualifiedIdContext *ctx) = 0;
  virtual void exitUnqualifiedId(ReentParser::UnqualifiedIdContext *ctx) = 0;

  virtual void enterQualifiedId(ReentParser::QualifiedIdContext *ctx) = 0;
  virtual void exitQualifiedId(ReentParser::QualifiedIdContext *ctx) = 0;

  virtual void enterNestedNameSpecifier(ReentParser::NestedNameSpecifierContext *ctx) = 0;
  virtual void exitNestedNameSpecifier(ReentParser::NestedNameSpecifierContext *ctx) = 0;

  virtual void enterLambdaExpression(ReentParser::LambdaExpressionContext *ctx) = 0;
  virtual void exitLambdaExpression(ReentParser::LambdaExpressionContext *ctx) = 0;

  virtual void enterLambdaIntroducer(ReentParser::LambdaIntroducerContext *ctx) = 0;
  virtual void exitLambdaIntroducer(ReentParser::LambdaIntroducerContext *ctx) = 0;

  virtual void enterLambdaCapture(ReentParser::LambdaCaptureContext *ctx) = 0;
  virtual void exitLambdaCapture(ReentParser::LambdaCaptureContext *ctx) = 0;

  virtual void enterCaptureDefault(ReentParser::CaptureDefaultContext *ctx) = 0;
  virtual void exitCaptureDefault(ReentParser::CaptureDefaultContext *ctx) = 0;

  virtual void enterCaptureList(ReentParser::CaptureListContext *ctx) = 0;
  virtual void exitCaptureList(ReentParser::CaptureListContext *ctx) = 0;

  virtual void enterCapture(ReentParser::CaptureContext *ctx) = 0;
  virtual void exitCapture(ReentParser::CaptureContext *ctx) = 0;

  virtual void enterSimpleCapture(ReentParser::SimpleCaptureContext *ctx) = 0;
  virtual void exitSimpleCapture(ReentParser::SimpleCaptureContext *ctx) = 0;

  virtual void enterInitcapture(ReentParser::InitcaptureContext *ctx) = 0;
  virtual void exitInitcapture(ReentParser::InitcaptureContext *ctx) = 0;

  virtual void enterLambdaDeclarator(ReentParser::LambdaDeclaratorContext *ctx) = 0;
  virtual void exitLambdaDeclarator(ReentParser::LambdaDeclaratorContext *ctx) = 0;

  virtual void enterObjCilkSpawnArg(ReentParser::ObjCilkSpawnArgContext *ctx) = 0;
  virtual void exitObjCilkSpawnArg(ReentParser::ObjCilkSpawnArgContext *ctx) = 0;

  virtual void enterObjCilkSpawnParams(ReentParser::ObjCilkSpawnParamsContext *ctx) = 0;
  virtual void exitObjCilkSpawnParams(ReentParser::ObjCilkSpawnParamsContext *ctx) = 0;

  virtual void enterObjCilkDesignator(ReentParser::ObjCilkDesignatorContext *ctx) = 0;
  virtual void exitObjCilkDesignator(ReentParser::ObjCilkDesignatorContext *ctx) = 0;

  virtual void enterObjCilk(ReentParser::ObjCilkContext *ctx) = 0;
  virtual void exitObjCilk(ReentParser::ObjCilkContext *ctx) = 0;

  virtual void enterPostfixExpression(ReentParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(ReentParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterTypeIdOfTheTypeId(ReentParser::TypeIdOfTheTypeIdContext *ctx) = 0;
  virtual void exitTypeIdOfTheTypeId(ReentParser::TypeIdOfTheTypeIdContext *ctx) = 0;

  virtual void enterExpressionList(ReentParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(ReentParser::ExpressionListContext *ctx) = 0;

  virtual void enterPseudoDestructorName(ReentParser::PseudoDestructorNameContext *ctx) = 0;
  virtual void exitPseudoDestructorName(ReentParser::PseudoDestructorNameContext *ctx) = 0;

  virtual void enterUnaryExpression(ReentParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(ReentParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUnaryOperator(ReentParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(ReentParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterNewExpression(ReentParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(ReentParser::NewExpressionContext *ctx) = 0;

  virtual void enterNewPlacement(ReentParser::NewPlacementContext *ctx) = 0;
  virtual void exitNewPlacement(ReentParser::NewPlacementContext *ctx) = 0;

  virtual void enterNewTypeId(ReentParser::NewTypeIdContext *ctx) = 0;
  virtual void exitNewTypeId(ReentParser::NewTypeIdContext *ctx) = 0;

  virtual void enterNewDeclarator(ReentParser::NewDeclaratorContext *ctx) = 0;
  virtual void exitNewDeclarator(ReentParser::NewDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerNewDeclarator(ReentParser::NoPointerNewDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerNewDeclarator(ReentParser::NoPointerNewDeclaratorContext *ctx) = 0;

  virtual void enterNewInitializer(ReentParser::NewInitializerContext *ctx) = 0;
  virtual void exitNewInitializer(ReentParser::NewInitializerContext *ctx) = 0;

  virtual void enterDeleteExpression(ReentParser::DeleteExpressionContext *ctx) = 0;
  virtual void exitDeleteExpression(ReentParser::DeleteExpressionContext *ctx) = 0;

  virtual void enterNoExceptExpression(ReentParser::NoExceptExpressionContext *ctx) = 0;
  virtual void exitNoExceptExpression(ReentParser::NoExceptExpressionContext *ctx) = 0;

  virtual void enterCastExpression(ReentParser::CastExpressionContext *ctx) = 0;
  virtual void exitCastExpression(ReentParser::CastExpressionContext *ctx) = 0;

  virtual void enterPointerMemberExpression(ReentParser::PointerMemberExpressionContext *ctx) = 0;
  virtual void exitPointerMemberExpression(ReentParser::PointerMemberExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(ReentParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(ReentParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(ReentParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(ReentParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(ReentParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(ReentParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterShiftOperator(ReentParser::ShiftOperatorContext *ctx) = 0;
  virtual void exitShiftOperator(ReentParser::ShiftOperatorContext *ctx) = 0;

  virtual void enterRelationalExpression(ReentParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(ReentParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(ReentParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(ReentParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterAndExpression(ReentParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(ReentParser::AndExpressionContext *ctx) = 0;

  virtual void enterExclusiveOrExpression(ReentParser::ExclusiveOrExpressionContext *ctx) = 0;
  virtual void exitExclusiveOrExpression(ReentParser::ExclusiveOrExpressionContext *ctx) = 0;

  virtual void enterInclusiveOrExpression(ReentParser::InclusiveOrExpressionContext *ctx) = 0;
  virtual void exitInclusiveOrExpression(ReentParser::InclusiveOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(ReentParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(ReentParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(ReentParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(ReentParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterConditionalExpression(ReentParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(ReentParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(ReentParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(ReentParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(ReentParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(ReentParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterExpression(ReentParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(ReentParser::ExpressionContext *ctx) = 0;

  virtual void enterConstantExpression(ReentParser::ConstantExpressionContext *ctx) = 0;
  virtual void exitConstantExpression(ReentParser::ConstantExpressionContext *ctx) = 0;

  virtual void enterStatement(ReentParser::StatementContext *ctx) = 0;
  virtual void exitStatement(ReentParser::StatementContext *ctx) = 0;

  virtual void enterLabeledStatement(ReentParser::LabeledStatementContext *ctx) = 0;
  virtual void exitLabeledStatement(ReentParser::LabeledStatementContext *ctx) = 0;

  virtual void enterCilk_sync(ReentParser::Cilk_syncContext *ctx) = 0;
  virtual void exitCilk_sync(ReentParser::Cilk_syncContext *ctx) = 0;

  virtual void enterFill_into_plan(ReentParser::Fill_into_planContext *ctx) = 0;
  virtual void exitFill_into_plan(ReentParser::Fill_into_planContext *ctx) = 0;

  virtual void enterFill_from_plan(ReentParser::Fill_from_planContext *ctx) = 0;
  virtual void exitFill_from_plan(ReentParser::Fill_from_planContext *ctx) = 0;

  virtual void enterReent_filler(ReentParser::Reent_fillerContext *ctx) = 0;
  virtual void exitReent_filler(ReentParser::Reent_fillerContext *ctx) = 0;

  virtual void enterReent_reader(ReentParser::Reent_readerContext *ctx) = 0;
  virtual void exitReent_reader(ReentParser::Reent_readerContext *ctx) = 0;

  virtual void enterReent_filler_array(ReentParser::Reent_filler_arrayContext *ctx) = 0;
  virtual void exitReent_filler_array(ReentParser::Reent_filler_arrayContext *ctx) = 0;

  virtual void enterReent_statement(ReentParser::Reent_statementContext *ctx) = 0;
  virtual void exitReent_statement(ReentParser::Reent_statementContext *ctx) = 0;

  virtual void enterChain_statement(ReentParser::Chain_statementContext *ctx) = 0;
  virtual void exitChain_statement(ReentParser::Chain_statementContext *ctx) = 0;

  virtual void enterAtomic_block(ReentParser::Atomic_blockContext *ctx) = 0;
  virtual void exitAtomic_block(ReentParser::Atomic_blockContext *ctx) = 0;

  virtual void enterSoft_atomic_block(ReentParser::Soft_atomic_blockContext *ctx) = 0;
  virtual void exitSoft_atomic_block(ReentParser::Soft_atomic_blockContext *ctx) = 0;

  virtual void enterPlan_first(ReentParser::Plan_firstContext *ctx) = 0;
  virtual void exitPlan_first(ReentParser::Plan_firstContext *ctx) = 0;

  virtual void enterPlan_get_first(ReentParser::Plan_get_firstContext *ctx) = 0;
  virtual void exitPlan_get_first(ReentParser::Plan_get_firstContext *ctx) = 0;

  virtual void enterPlan_last(ReentParser::Plan_lastContext *ctx) = 0;
  virtual void exitPlan_last(ReentParser::Plan_lastContext *ctx) = 0;

  virtual void enterPlan_get_last(ReentParser::Plan_get_lastContext *ctx) = 0;
  virtual void exitPlan_get_last(ReentParser::Plan_get_lastContext *ctx) = 0;

  virtual void enterPlan_register(ReentParser::Plan_registerContext *ctx) = 0;
  virtual void exitPlan_register(ReentParser::Plan_registerContext *ctx) = 0;

  virtual void enterPlan_registered_barrier(ReentParser::Plan_registered_barrierContext *ctx) = 0;
  virtual void exitPlan_registered_barrier(ReentParser::Plan_registered_barrierContext *ctx) = 0;

  virtual void enterPlan_critical(ReentParser::Plan_criticalContext *ctx) = 0;
  virtual void exitPlan_critical(ReentParser::Plan_criticalContext *ctx) = 0;

  virtual void enterPlan_stop(ReentParser::Plan_stopContext *ctx) = 0;
  virtual void exitPlan_stop(ReentParser::Plan_stopContext *ctx) = 0;

  virtual void enterClear_plan(ReentParser::Clear_planContext *ctx) = 0;
  virtual void exitClear_plan(ReentParser::Clear_planContext *ctx) = 0;

  virtual void enterPlan_group_first(ReentParser::Plan_group_firstContext *ctx) = 0;
  virtual void exitPlan_group_first(ReentParser::Plan_group_firstContext *ctx) = 0;

  virtual void enterPlan_group_last(ReentParser::Plan_group_lastContext *ctx) = 0;
  virtual void exitPlan_group_last(ReentParser::Plan_group_lastContext *ctx) = 0;

  virtual void enterPlan_group_parallelize(ReentParser::Plan_group_parallelizeContext *ctx) = 0;
  virtual void exitPlan_group_parallelize(ReentParser::Plan_group_parallelizeContext *ctx) = 0;

  virtual void enterPlan_group_atomize(ReentParser::Plan_group_atomizeContext *ctx) = 0;
  virtual void exitPlan_group_atomize(ReentParser::Plan_group_atomizeContext *ctx) = 0;

  virtual void enterPlan_group_soft_atomize(ReentParser::Plan_group_soft_atomizeContext *ctx) = 0;
  virtual void exitPlan_group_soft_atomize(ReentParser::Plan_group_soft_atomizeContext *ctx) = 0;

  virtual void enterPlan_group_vectorize(ReentParser::Plan_group_vectorizeContext *ctx) = 0;
  virtual void exitPlan_group_vectorize(ReentParser::Plan_group_vectorizeContext *ctx) = 0;

  virtual void enterThrow_first(ReentParser::Throw_firstContext *ctx) = 0;
  virtual void exitThrow_first(ReentParser::Throw_firstContext *ctx) = 0;

  virtual void enterThrow_last(ReentParser::Throw_lastContext *ctx) = 0;
  virtual void exitThrow_last(ReentParser::Throw_lastContext *ctx) = 0;

  virtual void enterPlanning_params(ReentParser::Planning_paramsContext *ctx) = 0;
  virtual void exitPlanning_params(ReentParser::Planning_paramsContext *ctx) = 0;

  virtual void enterReent_parameter_cut(ReentParser::Reent_parameter_cutContext *ctx) = 0;
  virtual void exitReent_parameter_cut(ReentParser::Reent_parameter_cutContext *ctx) = 0;

  virtual void enterReent_special_call(ReentParser::Reent_special_callContext *ctx) = 0;
  virtual void exitReent_special_call(ReentParser::Reent_special_callContext *ctx) = 0;

  virtual void enterReent_continue_any_call(ReentParser::Reent_continue_any_callContext *ctx) = 0;
  virtual void exitReent_continue_any_call(ReentParser::Reent_continue_any_callContext *ctx) = 0;

  virtual void enterReent_compact_continue(ReentParser::Reent_compact_continueContext *ctx) = 0;
  virtual void exitReent_compact_continue(ReentParser::Reent_compact_continueContext *ctx) = 0;

  virtual void enterReent_np_call(ReentParser::Reent_np_callContext *ctx) = 0;
  virtual void exitReent_np_call(ReentParser::Reent_np_callContext *ctx) = 0;

  virtual void enterStart_chain(ReentParser::Start_chainContext *ctx) = 0;
  virtual void exitStart_chain(ReentParser::Start_chainContext *ctx) = 0;

  virtual void enterStart_single_proc_chain(ReentParser::Start_single_proc_chainContext *ctx) = 0;
  virtual void exitStart_single_proc_chain(ReentParser::Start_single_proc_chainContext *ctx) = 0;

  virtual void enterStart_multi_proc_chain(ReentParser::Start_multi_proc_chainContext *ctx) = 0;
  virtual void exitStart_multi_proc_chain(ReentParser::Start_multi_proc_chainContext *ctx) = 0;

  virtual void enterChain_descriptor(ReentParser::Chain_descriptorContext *ctx) = 0;
  virtual void exitChain_descriptor(ReentParser::Chain_descriptorContext *ctx) = 0;

  virtual void enterVector_chain_descriptor(ReentParser::Vector_chain_descriptorContext *ctx) = 0;
  virtual void exitVector_chain_descriptor(ReentParser::Vector_chain_descriptorContext *ctx) = 0;

  virtual void enterList_chain_descriptor(ReentParser::List_chain_descriptorContext *ctx) = 0;
  virtual void exitList_chain_descriptor(ReentParser::List_chain_descriptorContext *ctx) = 0;

  virtual void enterStart_topology(ReentParser::Start_topologyContext *ctx) = 0;
  virtual void exitStart_topology(ReentParser::Start_topologyContext *ctx) = 0;

  virtual void enterTopology_item(ReentParser::Topology_itemContext *ctx) = 0;
  virtual void exitTopology_item(ReentParser::Topology_itemContext *ctx) = 0;

  virtual void enterTopology_line(ReentParser::Topology_lineContext *ctx) = 0;
  virtual void exitTopology_line(ReentParser::Topology_lineContext *ctx) = 0;

  virtual void enterTopology_reverse(ReentParser::Topology_reverseContext *ctx) = 0;
  virtual void exitTopology_reverse(ReentParser::Topology_reverseContext *ctx) = 0;

  virtual void enterTopology_node(ReentParser::Topology_nodeContext *ctx) = 0;
  virtual void exitTopology_node(ReentParser::Topology_nodeContext *ctx) = 0;

  virtual void enterChain_call(ReentParser::Chain_callContext *ctx) = 0;
  virtual void exitChain_call(ReentParser::Chain_callContext *ctx) = 0;

  virtual void enterQualified_call_statement(ReentParser::Qualified_call_statementContext *ctx) = 0;
  virtual void exitQualified_call_statement(ReentParser::Qualified_call_statementContext *ctx) = 0;

  virtual void enterSpawned_call_statement(ReentParser::Spawned_call_statementContext *ctx) = 0;
  virtual void exitSpawned_call_statement(ReentParser::Spawned_call_statementContext *ctx) = 0;

  virtual void enterExpressionStatement(ReentParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(ReentParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterCompoundStatement(ReentParser::CompoundStatementContext *ctx) = 0;
  virtual void exitCompoundStatement(ReentParser::CompoundStatementContext *ctx) = 0;

  virtual void enterStatementSeq(ReentParser::StatementSeqContext *ctx) = 0;
  virtual void exitStatementSeq(ReentParser::StatementSeqContext *ctx) = 0;

  virtual void enterSelectionStatement(ReentParser::SelectionStatementContext *ctx) = 0;
  virtual void exitSelectionStatement(ReentParser::SelectionStatementContext *ctx) = 0;

  virtual void enterCondition(ReentParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(ReentParser::ConditionContext *ctx) = 0;

  virtual void enterIterationStatement(ReentParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(ReentParser::IterationStatementContext *ctx) = 0;

  virtual void enterForInitStatement(ReentParser::ForInitStatementContext *ctx) = 0;
  virtual void exitForInitStatement(ReentParser::ForInitStatementContext *ctx) = 0;

  virtual void enterForRangeDeclaration(ReentParser::ForRangeDeclarationContext *ctx) = 0;
  virtual void exitForRangeDeclaration(ReentParser::ForRangeDeclarationContext *ctx) = 0;

  virtual void enterForRangeInitializer(ReentParser::ForRangeInitializerContext *ctx) = 0;
  virtual void exitForRangeInitializer(ReentParser::ForRangeInitializerContext *ctx) = 0;

  virtual void enterJumpStatement(ReentParser::JumpStatementContext *ctx) = 0;
  virtual void exitJumpStatement(ReentParser::JumpStatementContext *ctx) = 0;

  virtual void enterDeclarationStatement(ReentParser::DeclarationStatementContext *ctx) = 0;
  virtual void exitDeclarationStatement(ReentParser::DeclarationStatementContext *ctx) = 0;

  virtual void enterDeclarationseq(ReentParser::DeclarationseqContext *ctx) = 0;
  virtual void exitDeclarationseq(ReentParser::DeclarationseqContext *ctx) = 0;

  virtual void enterDeclaration(ReentParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(ReentParser::DeclarationContext *ctx) = 0;

  virtual void enterBlockDeclaration(ReentParser::BlockDeclarationContext *ctx) = 0;
  virtual void exitBlockDeclaration(ReentParser::BlockDeclarationContext *ctx) = 0;

  virtual void enterAliasDeclaration(ReentParser::AliasDeclarationContext *ctx) = 0;
  virtual void exitAliasDeclaration(ReentParser::AliasDeclarationContext *ctx) = 0;

  virtual void enterSimpleDeclaration(ReentParser::SimpleDeclarationContext *ctx) = 0;
  virtual void exitSimpleDeclaration(ReentParser::SimpleDeclarationContext *ctx) = 0;

  virtual void enterStaticAssertDeclaration(ReentParser::StaticAssertDeclarationContext *ctx) = 0;
  virtual void exitStaticAssertDeclaration(ReentParser::StaticAssertDeclarationContext *ctx) = 0;

  virtual void enterEmptyDeclaration(ReentParser::EmptyDeclarationContext *ctx) = 0;
  virtual void exitEmptyDeclaration(ReentParser::EmptyDeclarationContext *ctx) = 0;

  virtual void enterAttributeDeclaration(ReentParser::AttributeDeclarationContext *ctx) = 0;
  virtual void exitAttributeDeclaration(ReentParser::AttributeDeclarationContext *ctx) = 0;

  virtual void enterDeclSpecifier(ReentParser::DeclSpecifierContext *ctx) = 0;
  virtual void exitDeclSpecifier(ReentParser::DeclSpecifierContext *ctx) = 0;

  virtual void enterDeclSpecifierSeq(ReentParser::DeclSpecifierSeqContext *ctx) = 0;
  virtual void exitDeclSpecifierSeq(ReentParser::DeclSpecifierSeqContext *ctx) = 0;

  virtual void enterReent_special_type(ReentParser::Reent_special_typeContext *ctx) = 0;
  virtual void exitReent_special_type(ReentParser::Reent_special_typeContext *ctx) = 0;

  virtual void enterReent_funnel_type(ReentParser::Reent_funnel_typeContext *ctx) = 0;
  virtual void exitReent_funnel_type(ReentParser::Reent_funnel_typeContext *ctx) = 0;

  virtual void enterReent_cfunnel_type(ReentParser::Reent_cfunnel_typeContext *ctx) = 0;
  virtual void exitReent_cfunnel_type(ReentParser::Reent_cfunnel_typeContext *ctx) = 0;

  virtual void enterReent_cvar_type(ReentParser::Reent_cvar_typeContext *ctx) = 0;
  virtual void exitReent_cvar_type(ReentParser::Reent_cvar_typeContext *ctx) = 0;

  virtual void enterReent_csem_type(ReentParser::Reent_csem_typeContext *ctx) = 0;
  virtual void exitReent_csem_type(ReentParser::Reent_csem_typeContext *ctx) = 0;

  virtual void enterReent_soft_transact_array(ReentParser::Reent_soft_transact_arrayContext *ctx) = 0;
  virtual void exitReent_soft_transact_array(ReentParser::Reent_soft_transact_arrayContext *ctx) = 0;

  virtual void enterReent_soft_transact_var(ReentParser::Reent_soft_transact_varContext *ctx) = 0;
  virtual void exitReent_soft_transact_var(ReentParser::Reent_soft_transact_varContext *ctx) = 0;

  virtual void enterReent_soft_transact_in(ReentParser::Reent_soft_transact_inContext *ctx) = 0;
  virtual void exitReent_soft_transact_in(ReentParser::Reent_soft_transact_inContext *ctx) = 0;

  virtual void enterReent_soft_transact_out(ReentParser::Reent_soft_transact_outContext *ctx) = 0;
  virtual void exitReent_soft_transact_out(ReentParser::Reent_soft_transact_outContext *ctx) = 0;

  virtual void enterReent_plan_type(ReentParser::Reent_plan_typeContext *ctx) = 0;
  virtual void exitReent_plan_type(ReentParser::Reent_plan_typeContext *ctx) = 0;

  virtual void enterReent_plan_item_type(ReentParser::Reent_plan_item_typeContext *ctx) = 0;
  virtual void exitReent_plan_item_type(ReentParser::Reent_plan_item_typeContext *ctx) = 0;

  virtual void enterStorageClassSpecifier(ReentParser::StorageClassSpecifierContext *ctx) = 0;
  virtual void exitStorageClassSpecifier(ReentParser::StorageClassSpecifierContext *ctx) = 0;

  virtual void enterFunctionSpecifier(ReentParser::FunctionSpecifierContext *ctx) = 0;
  virtual void exitFunctionSpecifier(ReentParser::FunctionSpecifierContext *ctx) = 0;

  virtual void enterTypedefName(ReentParser::TypedefNameContext *ctx) = 0;
  virtual void exitTypedefName(ReentParser::TypedefNameContext *ctx) = 0;

  virtual void enterTypeSpecifier(ReentParser::TypeSpecifierContext *ctx) = 0;
  virtual void exitTypeSpecifier(ReentParser::TypeSpecifierContext *ctx) = 0;

  virtual void enterTrailingTypeSpecifier(ReentParser::TrailingTypeSpecifierContext *ctx) = 0;
  virtual void exitTrailingTypeSpecifier(ReentParser::TrailingTypeSpecifierContext *ctx) = 0;

  virtual void enterTypeSpecifierSeq(ReentParser::TypeSpecifierSeqContext *ctx) = 0;
  virtual void exitTypeSpecifierSeq(ReentParser::TypeSpecifierSeqContext *ctx) = 0;

  virtual void enterTrailingTypeSpecifierSeq(ReentParser::TrailingTypeSpecifierSeqContext *ctx) = 0;
  virtual void exitTrailingTypeSpecifierSeq(ReentParser::TrailingTypeSpecifierSeqContext *ctx) = 0;

  virtual void enterSimpleTypeLengthModifier(ReentParser::SimpleTypeLengthModifierContext *ctx) = 0;
  virtual void exitSimpleTypeLengthModifier(ReentParser::SimpleTypeLengthModifierContext *ctx) = 0;

  virtual void enterSimpleTypeSignednessModifier(ReentParser::SimpleTypeSignednessModifierContext *ctx) = 0;
  virtual void exitSimpleTypeSignednessModifier(ReentParser::SimpleTypeSignednessModifierContext *ctx) = 0;

  virtual void enterSimpleTypeSpecifier(ReentParser::SimpleTypeSpecifierContext *ctx) = 0;
  virtual void exitSimpleTypeSpecifier(ReentParser::SimpleTypeSpecifierContext *ctx) = 0;

  virtual void enterTheTypeName(ReentParser::TheTypeNameContext *ctx) = 0;
  virtual void exitTheTypeName(ReentParser::TheTypeNameContext *ctx) = 0;

  virtual void enterDecltypeSpecifier(ReentParser::DecltypeSpecifierContext *ctx) = 0;
  virtual void exitDecltypeSpecifier(ReentParser::DecltypeSpecifierContext *ctx) = 0;

  virtual void enterElaboratedTypeSpecifier(ReentParser::ElaboratedTypeSpecifierContext *ctx) = 0;
  virtual void exitElaboratedTypeSpecifier(ReentParser::ElaboratedTypeSpecifierContext *ctx) = 0;

  virtual void enterEnumName(ReentParser::EnumNameContext *ctx) = 0;
  virtual void exitEnumName(ReentParser::EnumNameContext *ctx) = 0;

  virtual void enterEnumSpecifier(ReentParser::EnumSpecifierContext *ctx) = 0;
  virtual void exitEnumSpecifier(ReentParser::EnumSpecifierContext *ctx) = 0;

  virtual void enterEnumHead(ReentParser::EnumHeadContext *ctx) = 0;
  virtual void exitEnumHead(ReentParser::EnumHeadContext *ctx) = 0;

  virtual void enterOpaqueEnumDeclaration(ReentParser::OpaqueEnumDeclarationContext *ctx) = 0;
  virtual void exitOpaqueEnumDeclaration(ReentParser::OpaqueEnumDeclarationContext *ctx) = 0;

  virtual void enterEnumkey(ReentParser::EnumkeyContext *ctx) = 0;
  virtual void exitEnumkey(ReentParser::EnumkeyContext *ctx) = 0;

  virtual void enterEnumbase(ReentParser::EnumbaseContext *ctx) = 0;
  virtual void exitEnumbase(ReentParser::EnumbaseContext *ctx) = 0;

  virtual void enterEnumeratorList(ReentParser::EnumeratorListContext *ctx) = 0;
  virtual void exitEnumeratorList(ReentParser::EnumeratorListContext *ctx) = 0;

  virtual void enterEnumeratorDefinition(ReentParser::EnumeratorDefinitionContext *ctx) = 0;
  virtual void exitEnumeratorDefinition(ReentParser::EnumeratorDefinitionContext *ctx) = 0;

  virtual void enterEnumerator(ReentParser::EnumeratorContext *ctx) = 0;
  virtual void exitEnumerator(ReentParser::EnumeratorContext *ctx) = 0;

  virtual void enterNamespaceName(ReentParser::NamespaceNameContext *ctx) = 0;
  virtual void exitNamespaceName(ReentParser::NamespaceNameContext *ctx) = 0;

  virtual void enterOriginalNamespaceName(ReentParser::OriginalNamespaceNameContext *ctx) = 0;
  virtual void exitOriginalNamespaceName(ReentParser::OriginalNamespaceNameContext *ctx) = 0;

  virtual void enterNamespaceDefinition(ReentParser::NamespaceDefinitionContext *ctx) = 0;
  virtual void exitNamespaceDefinition(ReentParser::NamespaceDefinitionContext *ctx) = 0;

  virtual void enterNamespaceAlias(ReentParser::NamespaceAliasContext *ctx) = 0;
  virtual void exitNamespaceAlias(ReentParser::NamespaceAliasContext *ctx) = 0;

  virtual void enterNamespaceAliasDefinition(ReentParser::NamespaceAliasDefinitionContext *ctx) = 0;
  virtual void exitNamespaceAliasDefinition(ReentParser::NamespaceAliasDefinitionContext *ctx) = 0;

  virtual void enterQualifiednamespacespecifier(ReentParser::QualifiednamespacespecifierContext *ctx) = 0;
  virtual void exitQualifiednamespacespecifier(ReentParser::QualifiednamespacespecifierContext *ctx) = 0;

  virtual void enterUsingDeclaration(ReentParser::UsingDeclarationContext *ctx) = 0;
  virtual void exitUsingDeclaration(ReentParser::UsingDeclarationContext *ctx) = 0;

  virtual void enterUsingDirective(ReentParser::UsingDirectiveContext *ctx) = 0;
  virtual void exitUsingDirective(ReentParser::UsingDirectiveContext *ctx) = 0;

  virtual void enterAsmDefinition(ReentParser::AsmDefinitionContext *ctx) = 0;
  virtual void exitAsmDefinition(ReentParser::AsmDefinitionContext *ctx) = 0;

  virtual void enterLinkageSpecification(ReentParser::LinkageSpecificationContext *ctx) = 0;
  virtual void exitLinkageSpecification(ReentParser::LinkageSpecificationContext *ctx) = 0;

  virtual void enterAttributeSpecifierSeq(ReentParser::AttributeSpecifierSeqContext *ctx) = 0;
  virtual void exitAttributeSpecifierSeq(ReentParser::AttributeSpecifierSeqContext *ctx) = 0;

  virtual void enterAttributeSpecifier(ReentParser::AttributeSpecifierContext *ctx) = 0;
  virtual void exitAttributeSpecifier(ReentParser::AttributeSpecifierContext *ctx) = 0;

  virtual void enterAlignmentspecifier(ReentParser::AlignmentspecifierContext *ctx) = 0;
  virtual void exitAlignmentspecifier(ReentParser::AlignmentspecifierContext *ctx) = 0;

  virtual void enterAttributeList(ReentParser::AttributeListContext *ctx) = 0;
  virtual void exitAttributeList(ReentParser::AttributeListContext *ctx) = 0;

  virtual void enterAttribute(ReentParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(ReentParser::AttributeContext *ctx) = 0;

  virtual void enterAttributeNamespace(ReentParser::AttributeNamespaceContext *ctx) = 0;
  virtual void exitAttributeNamespace(ReentParser::AttributeNamespaceContext *ctx) = 0;

  virtual void enterAttributeArgumentClause(ReentParser::AttributeArgumentClauseContext *ctx) = 0;
  virtual void exitAttributeArgumentClause(ReentParser::AttributeArgumentClauseContext *ctx) = 0;

  virtual void enterBalancedTokenSeq(ReentParser::BalancedTokenSeqContext *ctx) = 0;
  virtual void exitBalancedTokenSeq(ReentParser::BalancedTokenSeqContext *ctx) = 0;

  virtual void enterBalancedtoken(ReentParser::BalancedtokenContext *ctx) = 0;
  virtual void exitBalancedtoken(ReentParser::BalancedtokenContext *ctx) = 0;

  virtual void enterInitDeclaratorList(ReentParser::InitDeclaratorListContext *ctx) = 0;
  virtual void exitInitDeclaratorList(ReentParser::InitDeclaratorListContext *ctx) = 0;

  virtual void enterInitDeclarator(ReentParser::InitDeclaratorContext *ctx) = 0;
  virtual void exitInitDeclarator(ReentParser::InitDeclaratorContext *ctx) = 0;

  virtual void enterDeclarator(ReentParser::DeclaratorContext *ctx) = 0;
  virtual void exitDeclarator(ReentParser::DeclaratorContext *ctx) = 0;

  virtual void enterPointerDeclarator(ReentParser::PointerDeclaratorContext *ctx) = 0;
  virtual void exitPointerDeclarator(ReentParser::PointerDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerDeclarator(ReentParser::NoPointerDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerDeclarator(ReentParser::NoPointerDeclaratorContext *ctx) = 0;

  virtual void enterParametersAndQualifiers(ReentParser::ParametersAndQualifiersContext *ctx) = 0;
  virtual void exitParametersAndQualifiers(ReentParser::ParametersAndQualifiersContext *ctx) = 0;

  virtual void enterTrailingReturnType(ReentParser::TrailingReturnTypeContext *ctx) = 0;
  virtual void exitTrailingReturnType(ReentParser::TrailingReturnTypeContext *ctx) = 0;

  virtual void enterPointerOperator(ReentParser::PointerOperatorContext *ctx) = 0;
  virtual void exitPointerOperator(ReentParser::PointerOperatorContext *ctx) = 0;

  virtual void enterCvqualifierseq(ReentParser::CvqualifierseqContext *ctx) = 0;
  virtual void exitCvqualifierseq(ReentParser::CvqualifierseqContext *ctx) = 0;

  virtual void enterCvQualifier(ReentParser::CvQualifierContext *ctx) = 0;
  virtual void exitCvQualifier(ReentParser::CvQualifierContext *ctx) = 0;

  virtual void enterRefqualifier(ReentParser::RefqualifierContext *ctx) = 0;
  virtual void exitRefqualifier(ReentParser::RefqualifierContext *ctx) = 0;

  virtual void enterDeclaratorid(ReentParser::DeclaratoridContext *ctx) = 0;
  virtual void exitDeclaratorid(ReentParser::DeclaratoridContext *ctx) = 0;

  virtual void enterTheTypeId(ReentParser::TheTypeIdContext *ctx) = 0;
  virtual void exitTheTypeId(ReentParser::TheTypeIdContext *ctx) = 0;

  virtual void enterAbstractDeclarator(ReentParser::AbstractDeclaratorContext *ctx) = 0;
  virtual void exitAbstractDeclarator(ReentParser::AbstractDeclaratorContext *ctx) = 0;

  virtual void enterPointerAbstractDeclarator(ReentParser::PointerAbstractDeclaratorContext *ctx) = 0;
  virtual void exitPointerAbstractDeclarator(ReentParser::PointerAbstractDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerAbstractDeclarator(ReentParser::NoPointerAbstractDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerAbstractDeclarator(ReentParser::NoPointerAbstractDeclaratorContext *ctx) = 0;

  virtual void enterAbstractPackDeclarator(ReentParser::AbstractPackDeclaratorContext *ctx) = 0;
  virtual void exitAbstractPackDeclarator(ReentParser::AbstractPackDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerAbstractPackDeclarator(ReentParser::NoPointerAbstractPackDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerAbstractPackDeclarator(ReentParser::NoPointerAbstractPackDeclaratorContext *ctx) = 0;

  virtual void enterParameterDeclarationClause(ReentParser::ParameterDeclarationClauseContext *ctx) = 0;
  virtual void exitParameterDeclarationClause(ReentParser::ParameterDeclarationClauseContext *ctx) = 0;

  virtual void enterParameterDeclarationList(ReentParser::ParameterDeclarationListContext *ctx) = 0;
  virtual void exitParameterDeclarationList(ReentParser::ParameterDeclarationListContext *ctx) = 0;

  virtual void enterParameterDeclaration(ReentParser::ParameterDeclarationContext *ctx) = 0;
  virtual void exitParameterDeclaration(ReentParser::ParameterDeclarationContext *ctx) = 0;

  virtual void enterReenterableDefinition(ReentParser::ReenterableDefinitionContext *ctx) = 0;
  virtual void exitReenterableDefinition(ReentParser::ReenterableDefinitionContext *ctx) = 0;

  virtual void enterReenterableDeclaration(ReentParser::ReenterableDeclarationContext *ctx) = 0;
  virtual void exitReenterableDeclaration(ReentParser::ReenterableDeclarationContext *ctx) = 0;

  virtual void enterReenterableHead(ReentParser::ReenterableHeadContext *ctx) = 0;
  virtual void exitReenterableHead(ReentParser::ReenterableHeadContext *ctx) = 0;

  virtual void enterReent_chain_header(ReentParser::Reent_chain_headerContext *ctx) = 0;
  virtual void exitReent_chain_header(ReentParser::Reent_chain_headerContext *ctx) = 0;

  virtual void enterReent_chain_params(ReentParser::Reent_chain_paramsContext *ctx) = 0;
  virtual void exitReent_chain_params(ReentParser::Reent_chain_paramsContext *ctx) = 0;

  virtual void enterReent_chain_param(ReentParser::Reent_chain_paramContext *ctx) = 0;
  virtual void exitReent_chain_param(ReentParser::Reent_chain_paramContext *ctx) = 0;

  virtual void enterReent_recursive_type(ReentParser::Reent_recursive_typeContext *ctx) = 0;
  virtual void exitReent_recursive_type(ReentParser::Reent_recursive_typeContext *ctx) = 0;

  virtual void enterReent_reduction(ReentParser::Reent_reductionContext *ctx) = 0;
  virtual void exitReent_reduction(ReentParser::Reent_reductionContext *ctx) = 0;

  virtual void enterReent_gpu_global(ReentParser::Reent_gpu_globalContext *ctx) = 0;
  virtual void exitReent_gpu_global(ReentParser::Reent_gpu_globalContext *ctx) = 0;

  virtual void enterReent_gpu_local(ReentParser::Reent_gpu_localContext *ctx) = 0;
  virtual void exitReent_gpu_local(ReentParser::Reent_gpu_localContext *ctx) = 0;

  virtual void enterReduction_symbol(ReentParser::Reduction_symbolContext *ctx) = 0;
  virtual void exitReduction_symbol(ReentParser::Reduction_symbolContext *ctx) = 0;

  virtual void enterReent_chain_predicate(ReentParser::Reent_chain_predicateContext *ctx) = 0;
  virtual void exitReent_chain_predicate(ReentParser::Reent_chain_predicateContext *ctx) = 0;

  virtual void enterReent_predicate_set(ReentParser::Reent_predicate_setContext *ctx) = 0;
  virtual void exitReent_predicate_set(ReentParser::Reent_predicate_setContext *ctx) = 0;

  virtual void enterReent_predicate_reset(ReentParser::Reent_predicate_resetContext *ctx) = 0;
  virtual void exitReent_predicate_reset(ReentParser::Reent_predicate_resetContext *ctx) = 0;

  virtual void enterReent_predicate_depends(ReentParser::Reent_predicate_dependsContext *ctx) = 0;
  virtual void exitReent_predicate_depends(ReentParser::Reent_predicate_dependsContext *ctx) = 0;

  virtual void enterReent_predicate_if(ReentParser::Reent_predicate_ifContext *ctx) = 0;
  virtual void exitReent_predicate_if(ReentParser::Reent_predicate_ifContext *ctx) = 0;

  virtual void enterReent_dependents(ReentParser::Reent_dependentsContext *ctx) = 0;
  virtual void exitReent_dependents(ReentParser::Reent_dependentsContext *ctx) = 0;

  virtual void enterReent_enumerator(ReentParser::Reent_enumeratorContext *ctx) = 0;
  virtual void exitReent_enumerator(ReentParser::Reent_enumeratorContext *ctx) = 0;

  virtual void enterLoop_statement_header(ReentParser::Loop_statement_headerContext *ctx) = 0;
  virtual void exitLoop_statement_header(ReentParser::Loop_statement_headerContext *ctx) = 0;

  virtual void enterReent_single_dependent(ReentParser::Reent_single_dependentContext *ctx) = 0;
  virtual void exitReent_single_dependent(ReentParser::Reent_single_dependentContext *ctx) = 0;

  virtual void enterChain_interface(ReentParser::Chain_interfaceContext *ctx) = 0;
  virtual void exitChain_interface(ReentParser::Chain_interfaceContext *ctx) = 0;

  virtual void enterChainDefinition(ReentParser::ChainDefinitionContext *ctx) = 0;
  virtual void exitChainDefinition(ReentParser::ChainDefinitionContext *ctx) = 0;

  virtual void enterChainDeclaration(ReentParser::ChainDeclarationContext *ctx) = 0;
  virtual void exitChainDeclaration(ReentParser::ChainDeclarationContext *ctx) = 0;

  virtual void enterChainHead(ReentParser::ChainHeadContext *ctx) = 0;
  virtual void exitChainHead(ReentParser::ChainHeadContext *ctx) = 0;

  virtual void enterFunctionDefinition(ReentParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(ReentParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterSpecial_method_name(ReentParser::Special_method_nameContext *ctx) = 0;
  virtual void exitSpecial_method_name(ReentParser::Special_method_nameContext *ctx) = 0;

  virtual void enterFunctionBody(ReentParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(ReentParser::FunctionBodyContext *ctx) = 0;

  virtual void enterInitializer(ReentParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(ReentParser::InitializerContext *ctx) = 0;

  virtual void enterBraceOrEqualInitializer(ReentParser::BraceOrEqualInitializerContext *ctx) = 0;
  virtual void exitBraceOrEqualInitializer(ReentParser::BraceOrEqualInitializerContext *ctx) = 0;

  virtual void enterInitializerClause(ReentParser::InitializerClauseContext *ctx) = 0;
  virtual void exitInitializerClause(ReentParser::InitializerClauseContext *ctx) = 0;

  virtual void enterInitializerList(ReentParser::InitializerListContext *ctx) = 0;
  virtual void exitInitializerList(ReentParser::InitializerListContext *ctx) = 0;

  virtual void enterBracedInitList(ReentParser::BracedInitListContext *ctx) = 0;
  virtual void exitBracedInitList(ReentParser::BracedInitListContext *ctx) = 0;

  virtual void enterClassName(ReentParser::ClassNameContext *ctx) = 0;
  virtual void exitClassName(ReentParser::ClassNameContext *ctx) = 0;

  virtual void enterClassSpecifier(ReentParser::ClassSpecifierContext *ctx) = 0;
  virtual void exitClassSpecifier(ReentParser::ClassSpecifierContext *ctx) = 0;

  virtual void enterClassHead(ReentParser::ClassHeadContext *ctx) = 0;
  virtual void exitClassHead(ReentParser::ClassHeadContext *ctx) = 0;

  virtual void enterClassHeadName(ReentParser::ClassHeadNameContext *ctx) = 0;
  virtual void exitClassHeadName(ReentParser::ClassHeadNameContext *ctx) = 0;

  virtual void enterClassVirtSpecifier(ReentParser::ClassVirtSpecifierContext *ctx) = 0;
  virtual void exitClassVirtSpecifier(ReentParser::ClassVirtSpecifierContext *ctx) = 0;

  virtual void enterClassKey(ReentParser::ClassKeyContext *ctx) = 0;
  virtual void exitClassKey(ReentParser::ClassKeyContext *ctx) = 0;

  virtual void enterMemberSpecification(ReentParser::MemberSpecificationContext *ctx) = 0;
  virtual void exitMemberSpecification(ReentParser::MemberSpecificationContext *ctx) = 0;

  virtual void enterMarkedmemberdeclaration(ReentParser::MarkedmemberdeclarationContext *ctx) = 0;
  virtual void exitMarkedmemberdeclaration(ReentParser::MarkedmemberdeclarationContext *ctx) = 0;

  virtual void enterMemberdeclaration(ReentParser::MemberdeclarationContext *ctx) = 0;
  virtual void exitMemberdeclaration(ReentParser::MemberdeclarationContext *ctx) = 0;

  virtual void enterMemberDeclaratorList(ReentParser::MemberDeclaratorListContext *ctx) = 0;
  virtual void exitMemberDeclaratorList(ReentParser::MemberDeclaratorListContext *ctx) = 0;

  virtual void enterMemberDeclarator(ReentParser::MemberDeclaratorContext *ctx) = 0;
  virtual void exitMemberDeclarator(ReentParser::MemberDeclaratorContext *ctx) = 0;

  virtual void enterVirtualSpecifierSeq(ReentParser::VirtualSpecifierSeqContext *ctx) = 0;
  virtual void exitVirtualSpecifierSeq(ReentParser::VirtualSpecifierSeqContext *ctx) = 0;

  virtual void enterVirtualSpecifier(ReentParser::VirtualSpecifierContext *ctx) = 0;
  virtual void exitVirtualSpecifier(ReentParser::VirtualSpecifierContext *ctx) = 0;

  virtual void enterPureSpecifier(ReentParser::PureSpecifierContext *ctx) = 0;
  virtual void exitPureSpecifier(ReentParser::PureSpecifierContext *ctx) = 0;

  virtual void enterBaseClause(ReentParser::BaseClauseContext *ctx) = 0;
  virtual void exitBaseClause(ReentParser::BaseClauseContext *ctx) = 0;

  virtual void enterBaseSpecifierList(ReentParser::BaseSpecifierListContext *ctx) = 0;
  virtual void exitBaseSpecifierList(ReentParser::BaseSpecifierListContext *ctx) = 0;

  virtual void enterBaseSpecifier(ReentParser::BaseSpecifierContext *ctx) = 0;
  virtual void exitBaseSpecifier(ReentParser::BaseSpecifierContext *ctx) = 0;

  virtual void enterClassOrDeclType(ReentParser::ClassOrDeclTypeContext *ctx) = 0;
  virtual void exitClassOrDeclType(ReentParser::ClassOrDeclTypeContext *ctx) = 0;

  virtual void enterBaseTypeSpecifier(ReentParser::BaseTypeSpecifierContext *ctx) = 0;
  virtual void exitBaseTypeSpecifier(ReentParser::BaseTypeSpecifierContext *ctx) = 0;

  virtual void enterAccessSpecifier(ReentParser::AccessSpecifierContext *ctx) = 0;
  virtual void exitAccessSpecifier(ReentParser::AccessSpecifierContext *ctx) = 0;

  virtual void enterConversionFunctionId(ReentParser::ConversionFunctionIdContext *ctx) = 0;
  virtual void exitConversionFunctionId(ReentParser::ConversionFunctionIdContext *ctx) = 0;

  virtual void enterConversionTypeId(ReentParser::ConversionTypeIdContext *ctx) = 0;
  virtual void exitConversionTypeId(ReentParser::ConversionTypeIdContext *ctx) = 0;

  virtual void enterConversionDeclarator(ReentParser::ConversionDeclaratorContext *ctx) = 0;
  virtual void exitConversionDeclarator(ReentParser::ConversionDeclaratorContext *ctx) = 0;

  virtual void enterConstructorInitializer(ReentParser::ConstructorInitializerContext *ctx) = 0;
  virtual void exitConstructorInitializer(ReentParser::ConstructorInitializerContext *ctx) = 0;

  virtual void enterMemInitializerList(ReentParser::MemInitializerListContext *ctx) = 0;
  virtual void exitMemInitializerList(ReentParser::MemInitializerListContext *ctx) = 0;

  virtual void enterMemInitializer(ReentParser::MemInitializerContext *ctx) = 0;
  virtual void exitMemInitializer(ReentParser::MemInitializerContext *ctx) = 0;

  virtual void enterMeminitializerid(ReentParser::MeminitializeridContext *ctx) = 0;
  virtual void exitMeminitializerid(ReentParser::MeminitializeridContext *ctx) = 0;

  virtual void enterOperatorFunctionId(ReentParser::OperatorFunctionIdContext *ctx) = 0;
  virtual void exitOperatorFunctionId(ReentParser::OperatorFunctionIdContext *ctx) = 0;

  virtual void enterLiteralOperatorId(ReentParser::LiteralOperatorIdContext *ctx) = 0;
  virtual void exitLiteralOperatorId(ReentParser::LiteralOperatorIdContext *ctx) = 0;

  virtual void enterTemplateDeclaration(ReentParser::TemplateDeclarationContext *ctx) = 0;
  virtual void exitTemplateDeclaration(ReentParser::TemplateDeclarationContext *ctx) = 0;

  virtual void enterTemplateparameterList(ReentParser::TemplateparameterListContext *ctx) = 0;
  virtual void exitTemplateparameterList(ReentParser::TemplateparameterListContext *ctx) = 0;

  virtual void enterTemplateParameter(ReentParser::TemplateParameterContext *ctx) = 0;
  virtual void exitTemplateParameter(ReentParser::TemplateParameterContext *ctx) = 0;

  virtual void enterTypeParameter(ReentParser::TypeParameterContext *ctx) = 0;
  virtual void exitTypeParameter(ReentParser::TypeParameterContext *ctx) = 0;

  virtual void enterSimpleTemplateId(ReentParser::SimpleTemplateIdContext *ctx) = 0;
  virtual void exitSimpleTemplateId(ReentParser::SimpleTemplateIdContext *ctx) = 0;

  virtual void enterTemplateId(ReentParser::TemplateIdContext *ctx) = 0;
  virtual void exitTemplateId(ReentParser::TemplateIdContext *ctx) = 0;

  virtual void enterTemplateName(ReentParser::TemplateNameContext *ctx) = 0;
  virtual void exitTemplateName(ReentParser::TemplateNameContext *ctx) = 0;

  virtual void enterTemplateArgumentList(ReentParser::TemplateArgumentListContext *ctx) = 0;
  virtual void exitTemplateArgumentList(ReentParser::TemplateArgumentListContext *ctx) = 0;

  virtual void enterTemplateArgument(ReentParser::TemplateArgumentContext *ctx) = 0;
  virtual void exitTemplateArgument(ReentParser::TemplateArgumentContext *ctx) = 0;

  virtual void enterTypeNameSpecifier(ReentParser::TypeNameSpecifierContext *ctx) = 0;
  virtual void exitTypeNameSpecifier(ReentParser::TypeNameSpecifierContext *ctx) = 0;

  virtual void enterExplicitInstantiation(ReentParser::ExplicitInstantiationContext *ctx) = 0;
  virtual void exitExplicitInstantiation(ReentParser::ExplicitInstantiationContext *ctx) = 0;

  virtual void enterExplicitSpecialization(ReentParser::ExplicitSpecializationContext *ctx) = 0;
  virtual void exitExplicitSpecialization(ReentParser::ExplicitSpecializationContext *ctx) = 0;

  virtual void enterTryBlock(ReentParser::TryBlockContext *ctx) = 0;
  virtual void exitTryBlock(ReentParser::TryBlockContext *ctx) = 0;

  virtual void enterFunctionTryBlock(ReentParser::FunctionTryBlockContext *ctx) = 0;
  virtual void exitFunctionTryBlock(ReentParser::FunctionTryBlockContext *ctx) = 0;

  virtual void enterHandlerSeq(ReentParser::HandlerSeqContext *ctx) = 0;
  virtual void exitHandlerSeq(ReentParser::HandlerSeqContext *ctx) = 0;

  virtual void enterHandler(ReentParser::HandlerContext *ctx) = 0;
  virtual void exitHandler(ReentParser::HandlerContext *ctx) = 0;

  virtual void enterExceptionDeclaration(ReentParser::ExceptionDeclarationContext *ctx) = 0;
  virtual void exitExceptionDeclaration(ReentParser::ExceptionDeclarationContext *ctx) = 0;

  virtual void enterThrowExpression(ReentParser::ThrowExpressionContext *ctx) = 0;
  virtual void exitThrowExpression(ReentParser::ThrowExpressionContext *ctx) = 0;

  virtual void enterExceptionSpecification(ReentParser::ExceptionSpecificationContext *ctx) = 0;
  virtual void exitExceptionSpecification(ReentParser::ExceptionSpecificationContext *ctx) = 0;

  virtual void enterDynamicExceptionSpecification(ReentParser::DynamicExceptionSpecificationContext *ctx) = 0;
  virtual void exitDynamicExceptionSpecification(ReentParser::DynamicExceptionSpecificationContext *ctx) = 0;

  virtual void enterTypeIdList(ReentParser::TypeIdListContext *ctx) = 0;
  virtual void exitTypeIdList(ReentParser::TypeIdListContext *ctx) = 0;

  virtual void enterNoeExceptSpecification(ReentParser::NoeExceptSpecificationContext *ctx) = 0;
  virtual void exitNoeExceptSpecification(ReentParser::NoeExceptSpecificationContext *ctx) = 0;

  virtual void enterPlan_pragma(ReentParser::Plan_pragmaContext *ctx) = 0;
  virtual void exitPlan_pragma(ReentParser::Plan_pragmaContext *ctx) = 0;

  virtual void enterPlan_directive(ReentParser::Plan_directiveContext *ctx) = 0;
  virtual void exitPlan_directive(ReentParser::Plan_directiveContext *ctx) = 0;

  virtual void enterPlan_dir_vectorized(ReentParser::Plan_dir_vectorizedContext *ctx) = 0;
  virtual void exitPlan_dir_vectorized(ReentParser::Plan_dir_vectorizedContext *ctx) = 0;

  virtual void enterPlan_dir_clustered(ReentParser::Plan_dir_clusteredContext *ctx) = 0;
  virtual void exitPlan_dir_clustered(ReentParser::Plan_dir_clusteredContext *ctx) = 0;

  virtual void enterPlan_common(ReentParser::Plan_commonContext *ctx) = 0;
  virtual void exitPlan_common(ReentParser::Plan_commonContext *ctx) = 0;

  virtual void enterPlan_gpu(ReentParser::Plan_gpuContext *ctx) = 0;
  virtual void exitPlan_gpu(ReentParser::Plan_gpuContext *ctx) = 0;

  virtual void enterTheOperator(ReentParser::TheOperatorContext *ctx) = 0;
  virtual void exitTheOperator(ReentParser::TheOperatorContext *ctx) = 0;

  virtual void enterLiteral(ReentParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(ReentParser::LiteralContext *ctx) = 0;


};

