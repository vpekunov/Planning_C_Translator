
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>


// Generated from ReentParser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ReentParserListener.h"


/**
 * This class provides an empty implementation of ReentParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ReentParserBaseListener : public ReentParserListener {
public:

  virtual void enterTranslationUnit(ReentParser::TranslationUnitContext * /*ctx*/) override { }
  virtual void exitTranslationUnit(ReentParser::TranslationUnitContext * /*ctx*/) override { }

  virtual void enterAnyIdentifier(ReentParser::AnyIdentifierContext * /*ctx*/) override { }
  virtual void exitAnyIdentifier(ReentParser::AnyIdentifierContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(ReentParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(ReentParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterIdExpression(ReentParser::IdExpressionContext * /*ctx*/) override { }
  virtual void exitIdExpression(ReentParser::IdExpressionContext * /*ctx*/) override { }

  virtual void enterReent_funs_id(ReentParser::Reent_funs_idContext * /*ctx*/) override { }
  virtual void exitReent_funs_id(ReentParser::Reent_funs_idContext * /*ctx*/) override { }

  virtual void enterChain_funs_id(ReentParser::Chain_funs_idContext * /*ctx*/) override { }
  virtual void exitChain_funs_id(ReentParser::Chain_funs_idContext * /*ctx*/) override { }

  virtual void enterUnqualifiedId(ReentParser::UnqualifiedIdContext * /*ctx*/) override { }
  virtual void exitUnqualifiedId(ReentParser::UnqualifiedIdContext * /*ctx*/) override { }

  virtual void enterQualifiedId(ReentParser::QualifiedIdContext * /*ctx*/) override { }
  virtual void exitQualifiedId(ReentParser::QualifiedIdContext * /*ctx*/) override { }

  virtual void enterNestedNameSpecifier(ReentParser::NestedNameSpecifierContext * /*ctx*/) override { }
  virtual void exitNestedNameSpecifier(ReentParser::NestedNameSpecifierContext * /*ctx*/) override { }

  virtual void enterLambdaExpression(ReentParser::LambdaExpressionContext * /*ctx*/) override { }
  virtual void exitLambdaExpression(ReentParser::LambdaExpressionContext * /*ctx*/) override { }

  virtual void enterLambdaIntroducer(ReentParser::LambdaIntroducerContext * /*ctx*/) override { }
  virtual void exitLambdaIntroducer(ReentParser::LambdaIntroducerContext * /*ctx*/) override { }

  virtual void enterLambdaCapture(ReentParser::LambdaCaptureContext * /*ctx*/) override { }
  virtual void exitLambdaCapture(ReentParser::LambdaCaptureContext * /*ctx*/) override { }

  virtual void enterCaptureDefault(ReentParser::CaptureDefaultContext * /*ctx*/) override { }
  virtual void exitCaptureDefault(ReentParser::CaptureDefaultContext * /*ctx*/) override { }

  virtual void enterCaptureList(ReentParser::CaptureListContext * /*ctx*/) override { }
  virtual void exitCaptureList(ReentParser::CaptureListContext * /*ctx*/) override { }

  virtual void enterCapture(ReentParser::CaptureContext * /*ctx*/) override { }
  virtual void exitCapture(ReentParser::CaptureContext * /*ctx*/) override { }

  virtual void enterSimpleCapture(ReentParser::SimpleCaptureContext * /*ctx*/) override { }
  virtual void exitSimpleCapture(ReentParser::SimpleCaptureContext * /*ctx*/) override { }

  virtual void enterInitcapture(ReentParser::InitcaptureContext * /*ctx*/) override { }
  virtual void exitInitcapture(ReentParser::InitcaptureContext * /*ctx*/) override { }

  virtual void enterLambdaDeclarator(ReentParser::LambdaDeclaratorContext * /*ctx*/) override { }
  virtual void exitLambdaDeclarator(ReentParser::LambdaDeclaratorContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(ReentParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(ReentParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterTypeIdOfTheTypeId(ReentParser::TypeIdOfTheTypeIdContext * /*ctx*/) override { }
  virtual void exitTypeIdOfTheTypeId(ReentParser::TypeIdOfTheTypeIdContext * /*ctx*/) override { }

  virtual void enterExpressionList(ReentParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(ReentParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterPseudoDestructorName(ReentParser::PseudoDestructorNameContext * /*ctx*/) override { }
  virtual void exitPseudoDestructorName(ReentParser::PseudoDestructorNameContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(ReentParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(ReentParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(ReentParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(ReentParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterNewExpression(ReentParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(ReentParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterNewPlacement(ReentParser::NewPlacementContext * /*ctx*/) override { }
  virtual void exitNewPlacement(ReentParser::NewPlacementContext * /*ctx*/) override { }

  virtual void enterNewTypeId(ReentParser::NewTypeIdContext * /*ctx*/) override { }
  virtual void exitNewTypeId(ReentParser::NewTypeIdContext * /*ctx*/) override { }

  virtual void enterNewDeclarator(ReentParser::NewDeclaratorContext * /*ctx*/) override { }
  virtual void exitNewDeclarator(ReentParser::NewDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerNewDeclarator(ReentParser::NoPointerNewDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerNewDeclarator(ReentParser::NoPointerNewDeclaratorContext * /*ctx*/) override { }

  virtual void enterNewInitializer(ReentParser::NewInitializerContext * /*ctx*/) override { }
  virtual void exitNewInitializer(ReentParser::NewInitializerContext * /*ctx*/) override { }

  virtual void enterDeleteExpression(ReentParser::DeleteExpressionContext * /*ctx*/) override { }
  virtual void exitDeleteExpression(ReentParser::DeleteExpressionContext * /*ctx*/) override { }

  virtual void enterNoExceptExpression(ReentParser::NoExceptExpressionContext * /*ctx*/) override { }
  virtual void exitNoExceptExpression(ReentParser::NoExceptExpressionContext * /*ctx*/) override { }

  virtual void enterCastExpression(ReentParser::CastExpressionContext * /*ctx*/) override { }
  virtual void exitCastExpression(ReentParser::CastExpressionContext * /*ctx*/) override { }

  virtual void enterPointerMemberExpression(ReentParser::PointerMemberExpressionContext * /*ctx*/) override { }
  virtual void exitPointerMemberExpression(ReentParser::PointerMemberExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(ReentParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(ReentParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(ReentParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(ReentParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(ReentParser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(ReentParser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterShiftOperator(ReentParser::ShiftOperatorContext * /*ctx*/) override { }
  virtual void exitShiftOperator(ReentParser::ShiftOperatorContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(ReentParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(ReentParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(ReentParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(ReentParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(ReentParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(ReentParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterExclusiveOrExpression(ReentParser::ExclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitExclusiveOrExpression(ReentParser::ExclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterInclusiveOrExpression(ReentParser::InclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitInclusiveOrExpression(ReentParser::InclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(ReentParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(ReentParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(ReentParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(ReentParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(ReentParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(ReentParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(ReentParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(ReentParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(ReentParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(ReentParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterExpression(ReentParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(ReentParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterConstantExpression(ReentParser::ConstantExpressionContext * /*ctx*/) override { }
  virtual void exitConstantExpression(ReentParser::ConstantExpressionContext * /*ctx*/) override { }

  virtual void enterStatement(ReentParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(ReentParser::StatementContext * /*ctx*/) override { }

  virtual void enterLabeledStatement(ReentParser::LabeledStatementContext * /*ctx*/) override { }
  virtual void exitLabeledStatement(ReentParser::LabeledStatementContext * /*ctx*/) override { }

  virtual void enterCilk_sync(ReentParser::Cilk_syncContext * /*ctx*/) override { }
  virtual void exitCilk_sync(ReentParser::Cilk_syncContext * /*ctx*/) override { }

  virtual void enterFill_into_plan(ReentParser::Fill_into_planContext * /*ctx*/) override { }
  virtual void exitFill_into_plan(ReentParser::Fill_into_planContext * /*ctx*/) override { }

  virtual void enterFill_from_plan(ReentParser::Fill_from_planContext * /*ctx*/) override { }
  virtual void exitFill_from_plan(ReentParser::Fill_from_planContext * /*ctx*/) override { }

  virtual void enterReent_filler(ReentParser::Reent_fillerContext * /*ctx*/) override { }
  virtual void exitReent_filler(ReentParser::Reent_fillerContext * /*ctx*/) override { }

  virtual void enterReent_reader(ReentParser::Reent_readerContext * /*ctx*/) override { }
  virtual void exitReent_reader(ReentParser::Reent_readerContext * /*ctx*/) override { }

  virtual void enterReent_filler_array(ReentParser::Reent_filler_arrayContext * /*ctx*/) override { }
  virtual void exitReent_filler_array(ReentParser::Reent_filler_arrayContext * /*ctx*/) override { }

  virtual void enterReent_statement(ReentParser::Reent_statementContext * /*ctx*/) override { }
  virtual void exitReent_statement(ReentParser::Reent_statementContext * /*ctx*/) override { }

  virtual void enterChain_statement(ReentParser::Chain_statementContext * /*ctx*/) override { }
  virtual void exitChain_statement(ReentParser::Chain_statementContext * /*ctx*/) override { }

  virtual void enterAtomic_block(ReentParser::Atomic_blockContext * /*ctx*/) override { }
  virtual void exitAtomic_block(ReentParser::Atomic_blockContext * /*ctx*/) override { }

  virtual void enterSoft_atomic_block(ReentParser::Soft_atomic_blockContext * /*ctx*/) override { }
  virtual void exitSoft_atomic_block(ReentParser::Soft_atomic_blockContext * /*ctx*/) override { }

  virtual void enterPlan_first(ReentParser::Plan_firstContext * /*ctx*/) override { }
  virtual void exitPlan_first(ReentParser::Plan_firstContext * /*ctx*/) override { }

  virtual void enterPlan_get_first(ReentParser::Plan_get_firstContext * /*ctx*/) override { }
  virtual void exitPlan_get_first(ReentParser::Plan_get_firstContext * /*ctx*/) override { }

  virtual void enterPlan_last(ReentParser::Plan_lastContext * /*ctx*/) override { }
  virtual void exitPlan_last(ReentParser::Plan_lastContext * /*ctx*/) override { }

  virtual void enterPlan_get_last(ReentParser::Plan_get_lastContext * /*ctx*/) override { }
  virtual void exitPlan_get_last(ReentParser::Plan_get_lastContext * /*ctx*/) override { }

  virtual void enterPlan_register(ReentParser::Plan_registerContext * /*ctx*/) override { }
  virtual void exitPlan_register(ReentParser::Plan_registerContext * /*ctx*/) override { }

  virtual void enterPlan_registered_barrier(ReentParser::Plan_registered_barrierContext * /*ctx*/) override { }
  virtual void exitPlan_registered_barrier(ReentParser::Plan_registered_barrierContext * /*ctx*/) override { }

  virtual void enterPlan_critical(ReentParser::Plan_criticalContext * /*ctx*/) override { }
  virtual void exitPlan_critical(ReentParser::Plan_criticalContext * /*ctx*/) override { }

  virtual void enterPlan_stop(ReentParser::Plan_stopContext * /*ctx*/) override { }
  virtual void exitPlan_stop(ReentParser::Plan_stopContext * /*ctx*/) override { }

  virtual void enterClear_plan(ReentParser::Clear_planContext * /*ctx*/) override { }
  virtual void exitClear_plan(ReentParser::Clear_planContext * /*ctx*/) override { }

  virtual void enterPlan_group_first(ReentParser::Plan_group_firstContext * /*ctx*/) override { }
  virtual void exitPlan_group_first(ReentParser::Plan_group_firstContext * /*ctx*/) override { }

  virtual void enterPlan_group_last(ReentParser::Plan_group_lastContext * /*ctx*/) override { }
  virtual void exitPlan_group_last(ReentParser::Plan_group_lastContext * /*ctx*/) override { }

  virtual void enterPlan_group_parallelize(ReentParser::Plan_group_parallelizeContext * /*ctx*/) override { }
  virtual void exitPlan_group_parallelize(ReentParser::Plan_group_parallelizeContext * /*ctx*/) override { }

  virtual void enterPlan_group_atomize(ReentParser::Plan_group_atomizeContext * /*ctx*/) override { }
  virtual void exitPlan_group_atomize(ReentParser::Plan_group_atomizeContext * /*ctx*/) override { }

  virtual void enterPlan_group_soft_atomize(ReentParser::Plan_group_soft_atomizeContext * /*ctx*/) override { }
  virtual void exitPlan_group_soft_atomize(ReentParser::Plan_group_soft_atomizeContext * /*ctx*/) override { }

  virtual void enterPlan_group_vectorize(ReentParser::Plan_group_vectorizeContext * /*ctx*/) override { }
  virtual void exitPlan_group_vectorize(ReentParser::Plan_group_vectorizeContext * /*ctx*/) override { }

  virtual void enterThrow_first(ReentParser::Throw_firstContext * /*ctx*/) override { }
  virtual void exitThrow_first(ReentParser::Throw_firstContext * /*ctx*/) override { }

  virtual void enterThrow_last(ReentParser::Throw_lastContext * /*ctx*/) override { }
  virtual void exitThrow_last(ReentParser::Throw_lastContext * /*ctx*/) override { }

  virtual void enterPlanning_params(ReentParser::Planning_paramsContext * /*ctx*/) override { }
  virtual void exitPlanning_params(ReentParser::Planning_paramsContext * /*ctx*/) override { }

  virtual void enterReent_parameter_cut(ReentParser::Reent_parameter_cutContext * /*ctx*/) override { }
  virtual void exitReent_parameter_cut(ReentParser::Reent_parameter_cutContext * /*ctx*/) override { }

  virtual void enterReent_special_call(ReentParser::Reent_special_callContext * /*ctx*/) override { }
  virtual void exitReent_special_call(ReentParser::Reent_special_callContext * /*ctx*/) override { }

  virtual void enterReent_continue_any_call(ReentParser::Reent_continue_any_callContext * /*ctx*/) override { }
  virtual void exitReent_continue_any_call(ReentParser::Reent_continue_any_callContext * /*ctx*/) override { }

  virtual void enterReent_compact_continue(ReentParser::Reent_compact_continueContext * /*ctx*/) override { }
  virtual void exitReent_compact_continue(ReentParser::Reent_compact_continueContext * /*ctx*/) override { }

  virtual void enterReent_np_call(ReentParser::Reent_np_callContext * /*ctx*/) override { }
  virtual void exitReent_np_call(ReentParser::Reent_np_callContext * /*ctx*/) override { }

  virtual void enterStart_chain(ReentParser::Start_chainContext * /*ctx*/) override { }
  virtual void exitStart_chain(ReentParser::Start_chainContext * /*ctx*/) override { }

  virtual void enterStart_single_proc_chain(ReentParser::Start_single_proc_chainContext * /*ctx*/) override { }
  virtual void exitStart_single_proc_chain(ReentParser::Start_single_proc_chainContext * /*ctx*/) override { }

  virtual void enterStart_multi_proc_chain(ReentParser::Start_multi_proc_chainContext * /*ctx*/) override { }
  virtual void exitStart_multi_proc_chain(ReentParser::Start_multi_proc_chainContext * /*ctx*/) override { }

  virtual void enterChain_descriptor(ReentParser::Chain_descriptorContext * /*ctx*/) override { }
  virtual void exitChain_descriptor(ReentParser::Chain_descriptorContext * /*ctx*/) override { }

  virtual void enterVector_chain_descriptor(ReentParser::Vector_chain_descriptorContext * /*ctx*/) override { }
  virtual void exitVector_chain_descriptor(ReentParser::Vector_chain_descriptorContext * /*ctx*/) override { }

  virtual void enterList_chain_descriptor(ReentParser::List_chain_descriptorContext * /*ctx*/) override { }
  virtual void exitList_chain_descriptor(ReentParser::List_chain_descriptorContext * /*ctx*/) override { }

  virtual void enterStart_topology(ReentParser::Start_topologyContext * /*ctx*/) override { }
  virtual void exitStart_topology(ReentParser::Start_topologyContext * /*ctx*/) override { }

  virtual void enterTopology_item(ReentParser::Topology_itemContext * /*ctx*/) override { }
  virtual void exitTopology_item(ReentParser::Topology_itemContext * /*ctx*/) override { }

  virtual void enterTopology_line(ReentParser::Topology_lineContext * /*ctx*/) override { }
  virtual void exitTopology_line(ReentParser::Topology_lineContext * /*ctx*/) override { }

  virtual void enterTopology_reverse(ReentParser::Topology_reverseContext * /*ctx*/) override { }
  virtual void exitTopology_reverse(ReentParser::Topology_reverseContext * /*ctx*/) override { }

  virtual void enterTopology_node(ReentParser::Topology_nodeContext * /*ctx*/) override { }
  virtual void exitTopology_node(ReentParser::Topology_nodeContext * /*ctx*/) override { }

  virtual void enterChain_call(ReentParser::Chain_callContext * /*ctx*/) override { }
  virtual void exitChain_call(ReentParser::Chain_callContext * /*ctx*/) override { }

  virtual void enterQualified_call_statement(ReentParser::Qualified_call_statementContext * /*ctx*/) override { }
  virtual void exitQualified_call_statement(ReentParser::Qualified_call_statementContext * /*ctx*/) override { }

  virtual void enterSpawned_call_statement(ReentParser::Spawned_call_statementContext * /*ctx*/) override { }
  virtual void exitSpawned_call_statement(ReentParser::Spawned_call_statementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(ReentParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(ReentParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterCompoundStatement(ReentParser::CompoundStatementContext * /*ctx*/) override { }
  virtual void exitCompoundStatement(ReentParser::CompoundStatementContext * /*ctx*/) override { }

  virtual void enterStatementSeq(ReentParser::StatementSeqContext * /*ctx*/) override { }
  virtual void exitStatementSeq(ReentParser::StatementSeqContext * /*ctx*/) override { }

  virtual void enterSelectionStatement(ReentParser::SelectionStatementContext * /*ctx*/) override { }
  virtual void exitSelectionStatement(ReentParser::SelectionStatementContext * /*ctx*/) override { }

  virtual void enterCondition(ReentParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(ReentParser::ConditionContext * /*ctx*/) override { }

  virtual void enterIterationStatement(ReentParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(ReentParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterForInitStatement(ReentParser::ForInitStatementContext * /*ctx*/) override { }
  virtual void exitForInitStatement(ReentParser::ForInitStatementContext * /*ctx*/) override { }

  virtual void enterForRangeDeclaration(ReentParser::ForRangeDeclarationContext * /*ctx*/) override { }
  virtual void exitForRangeDeclaration(ReentParser::ForRangeDeclarationContext * /*ctx*/) override { }

  virtual void enterForRangeInitializer(ReentParser::ForRangeInitializerContext * /*ctx*/) override { }
  virtual void exitForRangeInitializer(ReentParser::ForRangeInitializerContext * /*ctx*/) override { }

  virtual void enterJumpStatement(ReentParser::JumpStatementContext * /*ctx*/) override { }
  virtual void exitJumpStatement(ReentParser::JumpStatementContext * /*ctx*/) override { }

  virtual void enterDeclarationStatement(ReentParser::DeclarationStatementContext * /*ctx*/) override { }
  virtual void exitDeclarationStatement(ReentParser::DeclarationStatementContext * /*ctx*/) override { }

  virtual void enterDeclarationseq(ReentParser::DeclarationseqContext * /*ctx*/) override { }
  virtual void exitDeclarationseq(ReentParser::DeclarationseqContext * /*ctx*/) override { }

  virtual void enterDeclaration(ReentParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(ReentParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterBlockDeclaration(ReentParser::BlockDeclarationContext * /*ctx*/) override { }
  virtual void exitBlockDeclaration(ReentParser::BlockDeclarationContext * /*ctx*/) override { }

  virtual void enterAliasDeclaration(ReentParser::AliasDeclarationContext * /*ctx*/) override { }
  virtual void exitAliasDeclaration(ReentParser::AliasDeclarationContext * /*ctx*/) override { }

  virtual void enterSimpleDeclaration(ReentParser::SimpleDeclarationContext * /*ctx*/) override { }
  virtual void exitSimpleDeclaration(ReentParser::SimpleDeclarationContext * /*ctx*/) override { }

  virtual void enterStaticAssertDeclaration(ReentParser::StaticAssertDeclarationContext * /*ctx*/) override { }
  virtual void exitStaticAssertDeclaration(ReentParser::StaticAssertDeclarationContext * /*ctx*/) override { }

  virtual void enterEmptyDeclaration(ReentParser::EmptyDeclarationContext * /*ctx*/) override { }
  virtual void exitEmptyDeclaration(ReentParser::EmptyDeclarationContext * /*ctx*/) override { }

  virtual void enterAttributeDeclaration(ReentParser::AttributeDeclarationContext * /*ctx*/) override { }
  virtual void exitAttributeDeclaration(ReentParser::AttributeDeclarationContext * /*ctx*/) override { }

  virtual void enterDeclSpecifier(ReentParser::DeclSpecifierContext * /*ctx*/) override { }
  virtual void exitDeclSpecifier(ReentParser::DeclSpecifierContext * /*ctx*/) override { }

  virtual void enterDeclSpecifierSeq(ReentParser::DeclSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitDeclSpecifierSeq(ReentParser::DeclSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterReent_special_type(ReentParser::Reent_special_typeContext * /*ctx*/) override { }
  virtual void exitReent_special_type(ReentParser::Reent_special_typeContext * /*ctx*/) override { }

  virtual void enterReent_funnel_type(ReentParser::Reent_funnel_typeContext * /*ctx*/) override { }
  virtual void exitReent_funnel_type(ReentParser::Reent_funnel_typeContext * /*ctx*/) override { }

  virtual void enterReent_cfunnel_type(ReentParser::Reent_cfunnel_typeContext * /*ctx*/) override { }
  virtual void exitReent_cfunnel_type(ReentParser::Reent_cfunnel_typeContext * /*ctx*/) override { }

  virtual void enterReent_cvar_type(ReentParser::Reent_cvar_typeContext * /*ctx*/) override { }
  virtual void exitReent_cvar_type(ReentParser::Reent_cvar_typeContext * /*ctx*/) override { }

  virtual void enterReent_csem_type(ReentParser::Reent_csem_typeContext * /*ctx*/) override { }
  virtual void exitReent_csem_type(ReentParser::Reent_csem_typeContext * /*ctx*/) override { }

  virtual void enterReent_soft_transact_array(ReentParser::Reent_soft_transact_arrayContext * /*ctx*/) override { }
  virtual void exitReent_soft_transact_array(ReentParser::Reent_soft_transact_arrayContext * /*ctx*/) override { }

  virtual void enterReent_soft_transact_var(ReentParser::Reent_soft_transact_varContext * /*ctx*/) override { }
  virtual void exitReent_soft_transact_var(ReentParser::Reent_soft_transact_varContext * /*ctx*/) override { }

  virtual void enterReent_soft_transact_in(ReentParser::Reent_soft_transact_inContext * /*ctx*/) override { }
  virtual void exitReent_soft_transact_in(ReentParser::Reent_soft_transact_inContext * /*ctx*/) override { }

  virtual void enterReent_soft_transact_out(ReentParser::Reent_soft_transact_outContext * /*ctx*/) override { }
  virtual void exitReent_soft_transact_out(ReentParser::Reent_soft_transact_outContext * /*ctx*/) override { }

  virtual void enterReent_plan_type(ReentParser::Reent_plan_typeContext * /*ctx*/) override { }
  virtual void exitReent_plan_type(ReentParser::Reent_plan_typeContext * /*ctx*/) override { }

  virtual void enterReent_plan_item_type(ReentParser::Reent_plan_item_typeContext * /*ctx*/) override { }
  virtual void exitReent_plan_item_type(ReentParser::Reent_plan_item_typeContext * /*ctx*/) override { }

  virtual void enterStorageClassSpecifier(ReentParser::StorageClassSpecifierContext * /*ctx*/) override { }
  virtual void exitStorageClassSpecifier(ReentParser::StorageClassSpecifierContext * /*ctx*/) override { }

  virtual void enterFunctionSpecifier(ReentParser::FunctionSpecifierContext * /*ctx*/) override { }
  virtual void exitFunctionSpecifier(ReentParser::FunctionSpecifierContext * /*ctx*/) override { }

  virtual void enterTypedefName(ReentParser::TypedefNameContext * /*ctx*/) override { }
  virtual void exitTypedefName(ReentParser::TypedefNameContext * /*ctx*/) override { }

  virtual void enterTypeSpecifier(ReentParser::TypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeSpecifier(ReentParser::TypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTrailingTypeSpecifier(ReentParser::TrailingTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTrailingTypeSpecifier(ReentParser::TrailingTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTypeSpecifierSeq(ReentParser::TypeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitTypeSpecifierSeq(ReentParser::TypeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterTrailingTypeSpecifierSeq(ReentParser::TrailingTypeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitTrailingTypeSpecifierSeq(ReentParser::TrailingTypeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterSimpleTypeLengthModifier(ReentParser::SimpleTypeLengthModifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeLengthModifier(ReentParser::SimpleTypeLengthModifierContext * /*ctx*/) override { }

  virtual void enterSimpleTypeSignednessModifier(ReentParser::SimpleTypeSignednessModifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeSignednessModifier(ReentParser::SimpleTypeSignednessModifierContext * /*ctx*/) override { }

  virtual void enterSimpleTypeSpecifier(ReentParser::SimpleTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeSpecifier(ReentParser::SimpleTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTheTypeName(ReentParser::TheTypeNameContext * /*ctx*/) override { }
  virtual void exitTheTypeName(ReentParser::TheTypeNameContext * /*ctx*/) override { }

  virtual void enterDecltypeSpecifier(ReentParser::DecltypeSpecifierContext * /*ctx*/) override { }
  virtual void exitDecltypeSpecifier(ReentParser::DecltypeSpecifierContext * /*ctx*/) override { }

  virtual void enterElaboratedTypeSpecifier(ReentParser::ElaboratedTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitElaboratedTypeSpecifier(ReentParser::ElaboratedTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterEnumName(ReentParser::EnumNameContext * /*ctx*/) override { }
  virtual void exitEnumName(ReentParser::EnumNameContext * /*ctx*/) override { }

  virtual void enterEnumSpecifier(ReentParser::EnumSpecifierContext * /*ctx*/) override { }
  virtual void exitEnumSpecifier(ReentParser::EnumSpecifierContext * /*ctx*/) override { }

  virtual void enterEnumHead(ReentParser::EnumHeadContext * /*ctx*/) override { }
  virtual void exitEnumHead(ReentParser::EnumHeadContext * /*ctx*/) override { }

  virtual void enterOpaqueEnumDeclaration(ReentParser::OpaqueEnumDeclarationContext * /*ctx*/) override { }
  virtual void exitOpaqueEnumDeclaration(ReentParser::OpaqueEnumDeclarationContext * /*ctx*/) override { }

  virtual void enterEnumkey(ReentParser::EnumkeyContext * /*ctx*/) override { }
  virtual void exitEnumkey(ReentParser::EnumkeyContext * /*ctx*/) override { }

  virtual void enterEnumbase(ReentParser::EnumbaseContext * /*ctx*/) override { }
  virtual void exitEnumbase(ReentParser::EnumbaseContext * /*ctx*/) override { }

  virtual void enterEnumeratorList(ReentParser::EnumeratorListContext * /*ctx*/) override { }
  virtual void exitEnumeratorList(ReentParser::EnumeratorListContext * /*ctx*/) override { }

  virtual void enterEnumeratorDefinition(ReentParser::EnumeratorDefinitionContext * /*ctx*/) override { }
  virtual void exitEnumeratorDefinition(ReentParser::EnumeratorDefinitionContext * /*ctx*/) override { }

  virtual void enterEnumerator(ReentParser::EnumeratorContext * /*ctx*/) override { }
  virtual void exitEnumerator(ReentParser::EnumeratorContext * /*ctx*/) override { }

  virtual void enterNamespaceName(ReentParser::NamespaceNameContext * /*ctx*/) override { }
  virtual void exitNamespaceName(ReentParser::NamespaceNameContext * /*ctx*/) override { }

  virtual void enterOriginalNamespaceName(ReentParser::OriginalNamespaceNameContext * /*ctx*/) override { }
  virtual void exitOriginalNamespaceName(ReentParser::OriginalNamespaceNameContext * /*ctx*/) override { }

  virtual void enterNamespaceDefinition(ReentParser::NamespaceDefinitionContext * /*ctx*/) override { }
  virtual void exitNamespaceDefinition(ReentParser::NamespaceDefinitionContext * /*ctx*/) override { }

  virtual void enterNamespaceAlias(ReentParser::NamespaceAliasContext * /*ctx*/) override { }
  virtual void exitNamespaceAlias(ReentParser::NamespaceAliasContext * /*ctx*/) override { }

  virtual void enterNamespaceAliasDefinition(ReentParser::NamespaceAliasDefinitionContext * /*ctx*/) override { }
  virtual void exitNamespaceAliasDefinition(ReentParser::NamespaceAliasDefinitionContext * /*ctx*/) override { }

  virtual void enterQualifiednamespacespecifier(ReentParser::QualifiednamespacespecifierContext * /*ctx*/) override { }
  virtual void exitQualifiednamespacespecifier(ReentParser::QualifiednamespacespecifierContext * /*ctx*/) override { }

  virtual void enterUsingDeclaration(ReentParser::UsingDeclarationContext * /*ctx*/) override { }
  virtual void exitUsingDeclaration(ReentParser::UsingDeclarationContext * /*ctx*/) override { }

  virtual void enterUsingDirective(ReentParser::UsingDirectiveContext * /*ctx*/) override { }
  virtual void exitUsingDirective(ReentParser::UsingDirectiveContext * /*ctx*/) override { }

  virtual void enterAsmDefinition(ReentParser::AsmDefinitionContext * /*ctx*/) override { }
  virtual void exitAsmDefinition(ReentParser::AsmDefinitionContext * /*ctx*/) override { }

  virtual void enterLinkageSpecification(ReentParser::LinkageSpecificationContext * /*ctx*/) override { }
  virtual void exitLinkageSpecification(ReentParser::LinkageSpecificationContext * /*ctx*/) override { }

  virtual void enterAttributeSpecifierSeq(ReentParser::AttributeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitAttributeSpecifierSeq(ReentParser::AttributeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterAttributeSpecifier(ReentParser::AttributeSpecifierContext * /*ctx*/) override { }
  virtual void exitAttributeSpecifier(ReentParser::AttributeSpecifierContext * /*ctx*/) override { }

  virtual void enterAlignmentspecifier(ReentParser::AlignmentspecifierContext * /*ctx*/) override { }
  virtual void exitAlignmentspecifier(ReentParser::AlignmentspecifierContext * /*ctx*/) override { }

  virtual void enterAttributeList(ReentParser::AttributeListContext * /*ctx*/) override { }
  virtual void exitAttributeList(ReentParser::AttributeListContext * /*ctx*/) override { }

  virtual void enterAttribute(ReentParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(ReentParser::AttributeContext * /*ctx*/) override { }

  virtual void enterAttributeNamespace(ReentParser::AttributeNamespaceContext * /*ctx*/) override { }
  virtual void exitAttributeNamespace(ReentParser::AttributeNamespaceContext * /*ctx*/) override { }

  virtual void enterAttributeArgumentClause(ReentParser::AttributeArgumentClauseContext * /*ctx*/) override { }
  virtual void exitAttributeArgumentClause(ReentParser::AttributeArgumentClauseContext * /*ctx*/) override { }

  virtual void enterBalancedTokenSeq(ReentParser::BalancedTokenSeqContext * /*ctx*/) override { }
  virtual void exitBalancedTokenSeq(ReentParser::BalancedTokenSeqContext * /*ctx*/) override { }

  virtual void enterBalancedtoken(ReentParser::BalancedtokenContext * /*ctx*/) override { }
  virtual void exitBalancedtoken(ReentParser::BalancedtokenContext * /*ctx*/) override { }

  virtual void enterInitDeclaratorList(ReentParser::InitDeclaratorListContext * /*ctx*/) override { }
  virtual void exitInitDeclaratorList(ReentParser::InitDeclaratorListContext * /*ctx*/) override { }

  virtual void enterInitDeclarator(ReentParser::InitDeclaratorContext * /*ctx*/) override { }
  virtual void exitInitDeclarator(ReentParser::InitDeclaratorContext * /*ctx*/) override { }

  virtual void enterDeclarator(ReentParser::DeclaratorContext * /*ctx*/) override { }
  virtual void exitDeclarator(ReentParser::DeclaratorContext * /*ctx*/) override { }

  virtual void enterPointerDeclarator(ReentParser::PointerDeclaratorContext * /*ctx*/) override { }
  virtual void exitPointerDeclarator(ReentParser::PointerDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerDeclarator(ReentParser::NoPointerDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerDeclarator(ReentParser::NoPointerDeclaratorContext * /*ctx*/) override { }

  virtual void enterParametersAndQualifiers(ReentParser::ParametersAndQualifiersContext * /*ctx*/) override { }
  virtual void exitParametersAndQualifiers(ReentParser::ParametersAndQualifiersContext * /*ctx*/) override { }

  virtual void enterTrailingReturnType(ReentParser::TrailingReturnTypeContext * /*ctx*/) override { }
  virtual void exitTrailingReturnType(ReentParser::TrailingReturnTypeContext * /*ctx*/) override { }

  virtual void enterPointerOperator(ReentParser::PointerOperatorContext * /*ctx*/) override { }
  virtual void exitPointerOperator(ReentParser::PointerOperatorContext * /*ctx*/) override { }

  virtual void enterCvqualifierseq(ReentParser::CvqualifierseqContext * /*ctx*/) override { }
  virtual void exitCvqualifierseq(ReentParser::CvqualifierseqContext * /*ctx*/) override { }

  virtual void enterCvQualifier(ReentParser::CvQualifierContext * /*ctx*/) override { }
  virtual void exitCvQualifier(ReentParser::CvQualifierContext * /*ctx*/) override { }

  virtual void enterRefqualifier(ReentParser::RefqualifierContext * /*ctx*/) override { }
  virtual void exitRefqualifier(ReentParser::RefqualifierContext * /*ctx*/) override { }

  virtual void enterDeclaratorid(ReentParser::DeclaratoridContext * /*ctx*/) override { }
  virtual void exitDeclaratorid(ReentParser::DeclaratoridContext * /*ctx*/) override { }

  virtual void enterTheTypeId(ReentParser::TheTypeIdContext * /*ctx*/) override { }
  virtual void exitTheTypeId(ReentParser::TheTypeIdContext * /*ctx*/) override { }

  virtual void enterAbstractDeclarator(ReentParser::AbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitAbstractDeclarator(ReentParser::AbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterPointerAbstractDeclarator(ReentParser::PointerAbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitPointerAbstractDeclarator(ReentParser::PointerAbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerAbstractDeclarator(ReentParser::NoPointerAbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerAbstractDeclarator(ReentParser::NoPointerAbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterAbstractPackDeclarator(ReentParser::AbstractPackDeclaratorContext * /*ctx*/) override { }
  virtual void exitAbstractPackDeclarator(ReentParser::AbstractPackDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerAbstractPackDeclarator(ReentParser::NoPointerAbstractPackDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerAbstractPackDeclarator(ReentParser::NoPointerAbstractPackDeclaratorContext * /*ctx*/) override { }

  virtual void enterParameterDeclarationClause(ReentParser::ParameterDeclarationClauseContext * /*ctx*/) override { }
  virtual void exitParameterDeclarationClause(ReentParser::ParameterDeclarationClauseContext * /*ctx*/) override { }

  virtual void enterParameterDeclarationList(ReentParser::ParameterDeclarationListContext * /*ctx*/) override { }
  virtual void exitParameterDeclarationList(ReentParser::ParameterDeclarationListContext * /*ctx*/) override { }

  virtual void enterParameterDeclaration(ReentParser::ParameterDeclarationContext * /*ctx*/) override { }
  virtual void exitParameterDeclaration(ReentParser::ParameterDeclarationContext * /*ctx*/) override { }

  virtual void enterReenterableDefinition(ReentParser::ReenterableDefinitionContext * /*ctx*/) override { }
  virtual void exitReenterableDefinition(ReentParser::ReenterableDefinitionContext * /*ctx*/) override { }

  virtual void enterReenterableDeclaration(ReentParser::ReenterableDeclarationContext * /*ctx*/) override { }
  virtual void exitReenterableDeclaration(ReentParser::ReenterableDeclarationContext * /*ctx*/) override { }

  virtual void enterReenterableHead(ReentParser::ReenterableHeadContext * /*ctx*/) override { }
  virtual void exitReenterableHead(ReentParser::ReenterableHeadContext * /*ctx*/) override { }

  virtual void enterReent_chain_header(ReentParser::Reent_chain_headerContext * /*ctx*/) override { }
  virtual void exitReent_chain_header(ReentParser::Reent_chain_headerContext * /*ctx*/) override { }

  virtual void enterReent_chain_params(ReentParser::Reent_chain_paramsContext * /*ctx*/) override { }
  virtual void exitReent_chain_params(ReentParser::Reent_chain_paramsContext * /*ctx*/) override { }

  virtual void enterReent_chain_param(ReentParser::Reent_chain_paramContext * /*ctx*/) override { }
  virtual void exitReent_chain_param(ReentParser::Reent_chain_paramContext * /*ctx*/) override { }

  virtual void enterReent_recursive_type(ReentParser::Reent_recursive_typeContext * /*ctx*/) override { }
  virtual void exitReent_recursive_type(ReentParser::Reent_recursive_typeContext * /*ctx*/) override { }

  virtual void enterReent_reduction(ReentParser::Reent_reductionContext * /*ctx*/) override { }
  virtual void exitReent_reduction(ReentParser::Reent_reductionContext * /*ctx*/) override { }

  virtual void enterReent_gpu_global(ReentParser::Reent_gpu_globalContext * /*ctx*/) override { }
  virtual void exitReent_gpu_global(ReentParser::Reent_gpu_globalContext * /*ctx*/) override { }

  virtual void enterReent_gpu_local(ReentParser::Reent_gpu_localContext * /*ctx*/) override { }
  virtual void exitReent_gpu_local(ReentParser::Reent_gpu_localContext * /*ctx*/) override { }

  virtual void enterReduction_symbol(ReentParser::Reduction_symbolContext * /*ctx*/) override { }
  virtual void exitReduction_symbol(ReentParser::Reduction_symbolContext * /*ctx*/) override { }

  virtual void enterReent_chain_predicate(ReentParser::Reent_chain_predicateContext * /*ctx*/) override { }
  virtual void exitReent_chain_predicate(ReentParser::Reent_chain_predicateContext * /*ctx*/) override { }

  virtual void enterReent_predicate_set(ReentParser::Reent_predicate_setContext * /*ctx*/) override { }
  virtual void exitReent_predicate_set(ReentParser::Reent_predicate_setContext * /*ctx*/) override { }

  virtual void enterReent_predicate_reset(ReentParser::Reent_predicate_resetContext * /*ctx*/) override { }
  virtual void exitReent_predicate_reset(ReentParser::Reent_predicate_resetContext * /*ctx*/) override { }

  virtual void enterReent_predicate_depends(ReentParser::Reent_predicate_dependsContext * /*ctx*/) override { }
  virtual void exitReent_predicate_depends(ReentParser::Reent_predicate_dependsContext * /*ctx*/) override { }

  virtual void enterReent_predicate_if(ReentParser::Reent_predicate_ifContext * /*ctx*/) override { }
  virtual void exitReent_predicate_if(ReentParser::Reent_predicate_ifContext * /*ctx*/) override { }

  virtual void enterReent_dependents(ReentParser::Reent_dependentsContext * /*ctx*/) override { }
  virtual void exitReent_dependents(ReentParser::Reent_dependentsContext * /*ctx*/) override { }

  virtual void enterReent_enumerator(ReentParser::Reent_enumeratorContext * /*ctx*/) override { }
  virtual void exitReent_enumerator(ReentParser::Reent_enumeratorContext * /*ctx*/) override { }

  virtual void enterLoop_statement_header(ReentParser::Loop_statement_headerContext * /*ctx*/) override { }
  virtual void exitLoop_statement_header(ReentParser::Loop_statement_headerContext * /*ctx*/) override { }

  virtual void enterReent_single_dependent(ReentParser::Reent_single_dependentContext * /*ctx*/) override { }
  virtual void exitReent_single_dependent(ReentParser::Reent_single_dependentContext * /*ctx*/) override { }

  virtual void enterChain_interface(ReentParser::Chain_interfaceContext * /*ctx*/) override { }
  virtual void exitChain_interface(ReentParser::Chain_interfaceContext * /*ctx*/) override { }

  virtual void enterChainDefinition(ReentParser::ChainDefinitionContext * /*ctx*/) override { }
  virtual void exitChainDefinition(ReentParser::ChainDefinitionContext * /*ctx*/) override { }

  virtual void enterChainDeclaration(ReentParser::ChainDeclarationContext * /*ctx*/) override { }
  virtual void exitChainDeclaration(ReentParser::ChainDeclarationContext * /*ctx*/) override { }

  virtual void enterChainHead(ReentParser::ChainHeadContext * /*ctx*/) override { }
  virtual void exitChainHead(ReentParser::ChainHeadContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(ReentParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(ReentParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterSpecial_method_name(ReentParser::Special_method_nameContext * /*ctx*/) override { }
  virtual void exitSpecial_method_name(ReentParser::Special_method_nameContext * /*ctx*/) override { }

  virtual void enterFunctionBody(ReentParser::FunctionBodyContext * /*ctx*/) override { }
  virtual void exitFunctionBody(ReentParser::FunctionBodyContext * /*ctx*/) override { }

  virtual void enterInitializer(ReentParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(ReentParser::InitializerContext * /*ctx*/) override { }

  virtual void enterBraceOrEqualInitializer(ReentParser::BraceOrEqualInitializerContext * /*ctx*/) override { }
  virtual void exitBraceOrEqualInitializer(ReentParser::BraceOrEqualInitializerContext * /*ctx*/) override { }

  virtual void enterInitializerClause(ReentParser::InitializerClauseContext * /*ctx*/) override { }
  virtual void exitInitializerClause(ReentParser::InitializerClauseContext * /*ctx*/) override { }

  virtual void enterInitializerList(ReentParser::InitializerListContext * /*ctx*/) override { }
  virtual void exitInitializerList(ReentParser::InitializerListContext * /*ctx*/) override { }

  virtual void enterBracedInitList(ReentParser::BracedInitListContext * /*ctx*/) override { }
  virtual void exitBracedInitList(ReentParser::BracedInitListContext * /*ctx*/) override { }

  virtual void enterClassName(ReentParser::ClassNameContext * /*ctx*/) override { }
  virtual void exitClassName(ReentParser::ClassNameContext * /*ctx*/) override { }

  virtual void enterClassSpecifier(ReentParser::ClassSpecifierContext * /*ctx*/) override { }
  virtual void exitClassSpecifier(ReentParser::ClassSpecifierContext * /*ctx*/) override { }

  virtual void enterClassHead(ReentParser::ClassHeadContext * /*ctx*/) override { }
  virtual void exitClassHead(ReentParser::ClassHeadContext * /*ctx*/) override { }

  virtual void enterClassHeadName(ReentParser::ClassHeadNameContext * /*ctx*/) override { }
  virtual void exitClassHeadName(ReentParser::ClassHeadNameContext * /*ctx*/) override { }

  virtual void enterClassVirtSpecifier(ReentParser::ClassVirtSpecifierContext * /*ctx*/) override { }
  virtual void exitClassVirtSpecifier(ReentParser::ClassVirtSpecifierContext * /*ctx*/) override { }

  virtual void enterClassKey(ReentParser::ClassKeyContext * /*ctx*/) override { }
  virtual void exitClassKey(ReentParser::ClassKeyContext * /*ctx*/) override { }

  virtual void enterMemberSpecification(ReentParser::MemberSpecificationContext * /*ctx*/) override { }
  virtual void exitMemberSpecification(ReentParser::MemberSpecificationContext * /*ctx*/) override { }

  virtual void enterMarkedmemberdeclaration(ReentParser::MarkedmemberdeclarationContext * /*ctx*/) override { }
  virtual void exitMarkedmemberdeclaration(ReentParser::MarkedmemberdeclarationContext * /*ctx*/) override { }

  virtual void enterMemberdeclaration(ReentParser::MemberdeclarationContext * /*ctx*/) override { }
  virtual void exitMemberdeclaration(ReentParser::MemberdeclarationContext * /*ctx*/) override { }

  virtual void enterMemberDeclaratorList(ReentParser::MemberDeclaratorListContext * /*ctx*/) override { }
  virtual void exitMemberDeclaratorList(ReentParser::MemberDeclaratorListContext * /*ctx*/) override { }

  virtual void enterMemberDeclarator(ReentParser::MemberDeclaratorContext * /*ctx*/) override { }
  virtual void exitMemberDeclarator(ReentParser::MemberDeclaratorContext * /*ctx*/) override { }

  virtual void enterVirtualSpecifierSeq(ReentParser::VirtualSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitVirtualSpecifierSeq(ReentParser::VirtualSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterVirtualSpecifier(ReentParser::VirtualSpecifierContext * /*ctx*/) override { }
  virtual void exitVirtualSpecifier(ReentParser::VirtualSpecifierContext * /*ctx*/) override { }

  virtual void enterPureSpecifier(ReentParser::PureSpecifierContext * /*ctx*/) override { }
  virtual void exitPureSpecifier(ReentParser::PureSpecifierContext * /*ctx*/) override { }

  virtual void enterBaseClause(ReentParser::BaseClauseContext * /*ctx*/) override { }
  virtual void exitBaseClause(ReentParser::BaseClauseContext * /*ctx*/) override { }

  virtual void enterBaseSpecifierList(ReentParser::BaseSpecifierListContext * /*ctx*/) override { }
  virtual void exitBaseSpecifierList(ReentParser::BaseSpecifierListContext * /*ctx*/) override { }

  virtual void enterBaseSpecifier(ReentParser::BaseSpecifierContext * /*ctx*/) override { }
  virtual void exitBaseSpecifier(ReentParser::BaseSpecifierContext * /*ctx*/) override { }

  virtual void enterClassOrDeclType(ReentParser::ClassOrDeclTypeContext * /*ctx*/) override { }
  virtual void exitClassOrDeclType(ReentParser::ClassOrDeclTypeContext * /*ctx*/) override { }

  virtual void enterBaseTypeSpecifier(ReentParser::BaseTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitBaseTypeSpecifier(ReentParser::BaseTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterAccessSpecifier(ReentParser::AccessSpecifierContext * /*ctx*/) override { }
  virtual void exitAccessSpecifier(ReentParser::AccessSpecifierContext * /*ctx*/) override { }

  virtual void enterConversionFunctionId(ReentParser::ConversionFunctionIdContext * /*ctx*/) override { }
  virtual void exitConversionFunctionId(ReentParser::ConversionFunctionIdContext * /*ctx*/) override { }

  virtual void enterConversionTypeId(ReentParser::ConversionTypeIdContext * /*ctx*/) override { }
  virtual void exitConversionTypeId(ReentParser::ConversionTypeIdContext * /*ctx*/) override { }

  virtual void enterConversionDeclarator(ReentParser::ConversionDeclaratorContext * /*ctx*/) override { }
  virtual void exitConversionDeclarator(ReentParser::ConversionDeclaratorContext * /*ctx*/) override { }

  virtual void enterConstructorInitializer(ReentParser::ConstructorInitializerContext * /*ctx*/) override { }
  virtual void exitConstructorInitializer(ReentParser::ConstructorInitializerContext * /*ctx*/) override { }

  virtual void enterMemInitializerList(ReentParser::MemInitializerListContext * /*ctx*/) override { }
  virtual void exitMemInitializerList(ReentParser::MemInitializerListContext * /*ctx*/) override { }

  virtual void enterMemInitializer(ReentParser::MemInitializerContext * /*ctx*/) override { }
  virtual void exitMemInitializer(ReentParser::MemInitializerContext * /*ctx*/) override { }

  virtual void enterMeminitializerid(ReentParser::MeminitializeridContext * /*ctx*/) override { }
  virtual void exitMeminitializerid(ReentParser::MeminitializeridContext * /*ctx*/) override { }

  virtual void enterOperatorFunctionId(ReentParser::OperatorFunctionIdContext * /*ctx*/) override { }
  virtual void exitOperatorFunctionId(ReentParser::OperatorFunctionIdContext * /*ctx*/) override { }

  virtual void enterLiteralOperatorId(ReentParser::LiteralOperatorIdContext * /*ctx*/) override { }
  virtual void exitLiteralOperatorId(ReentParser::LiteralOperatorIdContext * /*ctx*/) override { }

  virtual void enterTemplateDeclaration(ReentParser::TemplateDeclarationContext * /*ctx*/) override { }
  virtual void exitTemplateDeclaration(ReentParser::TemplateDeclarationContext * /*ctx*/) override { }

  virtual void enterTemplateparameterList(ReentParser::TemplateparameterListContext * /*ctx*/) override { }
  virtual void exitTemplateparameterList(ReentParser::TemplateparameterListContext * /*ctx*/) override { }

  virtual void enterTemplateParameter(ReentParser::TemplateParameterContext * /*ctx*/) override { }
  virtual void exitTemplateParameter(ReentParser::TemplateParameterContext * /*ctx*/) override { }

  virtual void enterTypeParameter(ReentParser::TypeParameterContext * /*ctx*/) override { }
  virtual void exitTypeParameter(ReentParser::TypeParameterContext * /*ctx*/) override { }

  virtual void enterSimpleTemplateId(ReentParser::SimpleTemplateIdContext * /*ctx*/) override { }
  virtual void exitSimpleTemplateId(ReentParser::SimpleTemplateIdContext * /*ctx*/) override { }

  virtual void enterTemplateId(ReentParser::TemplateIdContext * /*ctx*/) override { }
  virtual void exitTemplateId(ReentParser::TemplateIdContext * /*ctx*/) override { }

  virtual void enterTemplateName(ReentParser::TemplateNameContext * /*ctx*/) override { }
  virtual void exitTemplateName(ReentParser::TemplateNameContext * /*ctx*/) override { }

  virtual void enterTemplateArgumentList(ReentParser::TemplateArgumentListContext * /*ctx*/) override { }
  virtual void exitTemplateArgumentList(ReentParser::TemplateArgumentListContext * /*ctx*/) override { }

  virtual void enterTemplateArgument(ReentParser::TemplateArgumentContext * /*ctx*/) override { }
  virtual void exitTemplateArgument(ReentParser::TemplateArgumentContext * /*ctx*/) override { }

  virtual void enterTypeNameSpecifier(ReentParser::TypeNameSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeNameSpecifier(ReentParser::TypeNameSpecifierContext * /*ctx*/) override { }

  virtual void enterExplicitInstantiation(ReentParser::ExplicitInstantiationContext * /*ctx*/) override { }
  virtual void exitExplicitInstantiation(ReentParser::ExplicitInstantiationContext * /*ctx*/) override { }

  virtual void enterExplicitSpecialization(ReentParser::ExplicitSpecializationContext * /*ctx*/) override { }
  virtual void exitExplicitSpecialization(ReentParser::ExplicitSpecializationContext * /*ctx*/) override { }

  virtual void enterTryBlock(ReentParser::TryBlockContext * /*ctx*/) override { }
  virtual void exitTryBlock(ReentParser::TryBlockContext * /*ctx*/) override { }

  virtual void enterFunctionTryBlock(ReentParser::FunctionTryBlockContext * /*ctx*/) override { }
  virtual void exitFunctionTryBlock(ReentParser::FunctionTryBlockContext * /*ctx*/) override { }

  virtual void enterHandlerSeq(ReentParser::HandlerSeqContext * /*ctx*/) override { }
  virtual void exitHandlerSeq(ReentParser::HandlerSeqContext * /*ctx*/) override { }

  virtual void enterHandler(ReentParser::HandlerContext * /*ctx*/) override { }
  virtual void exitHandler(ReentParser::HandlerContext * /*ctx*/) override { }

  virtual void enterExceptionDeclaration(ReentParser::ExceptionDeclarationContext * /*ctx*/) override { }
  virtual void exitExceptionDeclaration(ReentParser::ExceptionDeclarationContext * /*ctx*/) override { }

  virtual void enterThrowExpression(ReentParser::ThrowExpressionContext * /*ctx*/) override { }
  virtual void exitThrowExpression(ReentParser::ThrowExpressionContext * /*ctx*/) override { }

  virtual void enterExceptionSpecification(ReentParser::ExceptionSpecificationContext * /*ctx*/) override { }
  virtual void exitExceptionSpecification(ReentParser::ExceptionSpecificationContext * /*ctx*/) override { }

  virtual void enterDynamicExceptionSpecification(ReentParser::DynamicExceptionSpecificationContext * /*ctx*/) override { }
  virtual void exitDynamicExceptionSpecification(ReentParser::DynamicExceptionSpecificationContext * /*ctx*/) override { }

  virtual void enterTypeIdList(ReentParser::TypeIdListContext * /*ctx*/) override { }
  virtual void exitTypeIdList(ReentParser::TypeIdListContext * /*ctx*/) override { }

  virtual void enterNoeExceptSpecification(ReentParser::NoeExceptSpecificationContext * /*ctx*/) override { }
  virtual void exitNoeExceptSpecification(ReentParser::NoeExceptSpecificationContext * /*ctx*/) override { }

  virtual void enterPlan_pragma(ReentParser::Plan_pragmaContext * /*ctx*/) override { }
  virtual void exitPlan_pragma(ReentParser::Plan_pragmaContext * /*ctx*/) override { }

  virtual void enterPlan_directive(ReentParser::Plan_directiveContext * /*ctx*/) override { }
  virtual void exitPlan_directive(ReentParser::Plan_directiveContext * /*ctx*/) override { }

  virtual void enterPlan_dir_vectorized(ReentParser::Plan_dir_vectorizedContext * /*ctx*/) override { }
  virtual void exitPlan_dir_vectorized(ReentParser::Plan_dir_vectorizedContext * /*ctx*/) override { }

  virtual void enterPlan_dir_clustered(ReentParser::Plan_dir_clusteredContext * /*ctx*/) override { }
  virtual void exitPlan_dir_clustered(ReentParser::Plan_dir_clusteredContext * /*ctx*/) override { }

  virtual void enterPlan_common(ReentParser::Plan_commonContext * /*ctx*/) override { }
  virtual void exitPlan_common(ReentParser::Plan_commonContext * /*ctx*/) override { }

  virtual void enterPlan_gpu(ReentParser::Plan_gpuContext * /*ctx*/) override { }
  virtual void exitPlan_gpu(ReentParser::Plan_gpuContext * /*ctx*/) override { }

  virtual void enterTheOperator(ReentParser::TheOperatorContext * /*ctx*/) override { }
  virtual void exitTheOperator(ReentParser::TheOperatorContext * /*ctx*/) override { }

  virtual void enterLiteral(ReentParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(ReentParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

