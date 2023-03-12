
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>


// Generated from ReentParser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  ReentParser : public antlr4::Parser {
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

  enum {
    RuleTranslationUnit = 0, RuleAnyIdentifier = 1, RulePrimaryExpression = 2, 
    RuleIdExpression = 3, RuleReent_funs_id = 4, RuleChain_funs_id = 5, 
    RuleUnqualifiedId = 6, RuleQualifiedId = 7, RuleNestedNameSpecifier = 8, 
    RuleLambdaExpression = 9, RuleLambdaIntroducer = 10, RuleLambdaCapture = 11, 
    RuleCaptureDefault = 12, RuleCaptureList = 13, RuleCapture = 14, RuleSimpleCapture = 15, 
    RuleInitcapture = 16, RuleLambdaDeclarator = 17, RulePostfixExpression = 18, 
    RuleTypeIdOfTheTypeId = 19, RuleExpressionList = 20, RulePseudoDestructorName = 21, 
    RuleUnaryExpression = 22, RuleUnaryOperator = 23, RuleNewExpression = 24, 
    RuleNewPlacement = 25, RuleNewTypeId = 26, RuleNewDeclarator = 27, RuleNoPointerNewDeclarator = 28, 
    RuleNewInitializer = 29, RuleDeleteExpression = 30, RuleNoExceptExpression = 31, 
    RuleCastExpression = 32, RulePointerMemberExpression = 33, RuleMultiplicativeExpression = 34, 
    RuleAdditiveExpression = 35, RuleShiftExpression = 36, RuleShiftOperator = 37, 
    RuleRelationalExpression = 38, RuleEqualityExpression = 39, RuleAndExpression = 40, 
    RuleExclusiveOrExpression = 41, RuleInclusiveOrExpression = 42, RuleLogicalAndExpression = 43, 
    RuleLogicalOrExpression = 44, RuleConditionalExpression = 45, RuleAssignmentExpression = 46, 
    RuleAssignmentOperator = 47, RuleExpression = 48, RuleConstantExpression = 49, 
    RuleStatement = 50, RuleLabeledStatement = 51, RuleFill_into_plan = 52, 
    RuleFill_from_plan = 53, RuleReent_filler = 54, RuleReent_reader = 55, 
    RuleReent_filler_array = 56, RuleReent_statement = 57, RuleChain_statement = 58, 
    RuleAtomic_block = 59, RuleSoft_atomic_block = 60, RulePlan_first = 61, 
    RulePlan_get_first = 62, RulePlan_last = 63, RulePlan_get_last = 64, 
    RulePlan_register = 65, RulePlan_registered_barrier = 66, RulePlan_critical = 67, 
    RulePlan_stop = 68, RuleClear_plan = 69, RulePlan_group_first = 70, 
    RulePlan_group_last = 71, RulePlan_group_parallelize = 72, RulePlan_group_atomize = 73, 
    RulePlan_group_soft_atomize = 74, RulePlan_group_vectorize = 75, RuleThrow_first = 76, 
    RuleThrow_last = 77, RulePlanning_params = 78, RuleReent_parameter_cut = 79, 
    RuleReent_special_call = 80, RuleReent_continue_any_call = 81, RuleReent_compact_continue = 82, 
    RuleReent_np_call = 83, RuleStart_chain = 84, RuleStart_single_proc_chain = 85, 
    RuleStart_multi_proc_chain = 86, RuleChain_descriptor = 87, RuleVector_chain_descriptor = 88, 
    RuleList_chain_descriptor = 89, RuleStart_topology = 90, RuleTopology_item = 91, 
    RuleTopology_line = 92, RuleTopology_reverse = 93, RuleTopology_node = 94, 
    RuleChain_call = 95, RuleQualified_call_statement = 96, RuleExpressionStatement = 97, 
    RuleCompoundStatement = 98, RuleStatementSeq = 99, RuleSelectionStatement = 100, 
    RuleCondition = 101, RuleIterationStatement = 102, RuleForInitStatement = 103, 
    RuleForRangeDeclaration = 104, RuleForRangeInitializer = 105, RuleJumpStatement = 106, 
    RuleDeclarationStatement = 107, RuleDeclarationseq = 108, RuleDeclaration = 109, 
    RuleBlockDeclaration = 110, RuleAliasDeclaration = 111, RuleSimpleDeclaration = 112, 
    RuleStaticAssertDeclaration = 113, RuleEmptyDeclaration = 114, RuleAttributeDeclaration = 115, 
    RuleDeclSpecifier = 116, RuleDeclSpecifierSeq = 117, RuleReent_special_type = 118, 
    RuleReent_funnel_type = 119, RuleReent_cfunnel_type = 120, RuleReent_cvar_type = 121, 
    RuleReent_csem_type = 122, RuleReent_soft_transact_array = 123, RuleReent_soft_transact_var = 124, 
    RuleReent_soft_transact_in = 125, RuleReent_soft_transact_out = 126, 
    RuleReent_plan_type = 127, RuleReent_plan_item_type = 128, RuleStorageClassSpecifier = 129, 
    RuleFunctionSpecifier = 130, RuleTypedefName = 131, RuleTypeSpecifier = 132, 
    RuleTrailingTypeSpecifier = 133, RuleTypeSpecifierSeq = 134, RuleTrailingTypeSpecifierSeq = 135, 
    RuleSimpleTypeLengthModifier = 136, RuleSimpleTypeSignednessModifier = 137, 
    RuleSimpleTypeSpecifier = 138, RuleTheTypeName = 139, RuleDecltypeSpecifier = 140, 
    RuleElaboratedTypeSpecifier = 141, RuleEnumName = 142, RuleEnumSpecifier = 143, 
    RuleEnumHead = 144, RuleOpaqueEnumDeclaration = 145, RuleEnumkey = 146, 
    RuleEnumbase = 147, RuleEnumeratorList = 148, RuleEnumeratorDefinition = 149, 
    RuleEnumerator = 150, RuleNamespaceName = 151, RuleOriginalNamespaceName = 152, 
    RuleNamespaceDefinition = 153, RuleNamespaceAlias = 154, RuleNamespaceAliasDefinition = 155, 
    RuleQualifiednamespacespecifier = 156, RuleUsingDeclaration = 157, RuleUsingDirective = 158, 
    RuleAsmDefinition = 159, RuleLinkageSpecification = 160, RuleAttributeSpecifierSeq = 161, 
    RuleAttributeSpecifier = 162, RuleAlignmentspecifier = 163, RuleAttributeList = 164, 
    RuleAttribute = 165, RuleAttributeNamespace = 166, RuleAttributeArgumentClause = 167, 
    RuleBalancedTokenSeq = 168, RuleBalancedtoken = 169, RuleInitDeclaratorList = 170, 
    RuleInitDeclarator = 171, RuleDeclarator = 172, RulePointerDeclarator = 173, 
    RuleNoPointerDeclarator = 174, RuleParametersAndQualifiers = 175, RuleTrailingReturnType = 176, 
    RulePointerOperator = 177, RuleCvqualifierseq = 178, RuleCvQualifier = 179, 
    RuleRefqualifier = 180, RuleDeclaratorid = 181, RuleTheTypeId = 182, 
    RuleAbstractDeclarator = 183, RulePointerAbstractDeclarator = 184, RuleNoPointerAbstractDeclarator = 185, 
    RuleAbstractPackDeclarator = 186, RuleNoPointerAbstractPackDeclarator = 187, 
    RuleParameterDeclarationClause = 188, RuleParameterDeclarationList = 189, 
    RuleParameterDeclaration = 190, RuleReenterableDefinition = 191, RuleReenterableDeclaration = 192, 
    RuleReenterableHead = 193, RuleReent_chain_header = 194, RuleReent_chain_params = 195, 
    RuleReent_chain_param = 196, RuleReent_recursive_type = 197, RuleReent_reduction = 198, 
    RuleReent_gpu_global = 199, RuleReent_gpu_local = 200, RuleReduction_symbol = 201, 
    RuleReent_chain_predicate = 202, RuleReent_predicate_set = 203, RuleReent_predicate_reset = 204, 
    RuleReent_predicate_depends = 205, RuleReent_predicate_if = 206, RuleReent_dependents = 207, 
    RuleReent_enumerator = 208, RuleLoop_statement_header = 209, RuleReent_single_dependent = 210, 
    RuleChain_interface = 211, RuleChainDefinition = 212, RuleChainDeclaration = 213, 
    RuleChainHead = 214, RuleFunctionDefinition = 215, RuleSpecial_method_name = 216, 
    RuleFunctionBody = 217, RuleInitializer = 218, RuleBraceOrEqualInitializer = 219, 
    RuleInitializerClause = 220, RuleInitializerList = 221, RuleBracedInitList = 222, 
    RuleClassName = 223, RuleClassSpecifier = 224, RuleClassHead = 225, 
    RuleClassHeadName = 226, RuleClassVirtSpecifier = 227, RuleClassKey = 228, 
    RuleMemberSpecification = 229, RuleMarkedmemberdeclaration = 230, RuleMemberdeclaration = 231, 
    RuleMemberDeclaratorList = 232, RuleMemberDeclarator = 233, RuleVirtualSpecifierSeq = 234, 
    RuleVirtualSpecifier = 235, RulePureSpecifier = 236, RuleBaseClause = 237, 
    RuleBaseSpecifierList = 238, RuleBaseSpecifier = 239, RuleClassOrDeclType = 240, 
    RuleBaseTypeSpecifier = 241, RuleAccessSpecifier = 242, RuleConversionFunctionId = 243, 
    RuleConversionTypeId = 244, RuleConversionDeclarator = 245, RuleConstructorInitializer = 246, 
    RuleMemInitializerList = 247, RuleMemInitializer = 248, RuleMeminitializerid = 249, 
    RuleOperatorFunctionId = 250, RuleLiteralOperatorId = 251, RuleTemplateDeclaration = 252, 
    RuleTemplateparameterList = 253, RuleTemplateParameter = 254, RuleTypeParameter = 255, 
    RuleSimpleTemplateId = 256, RuleTemplateId = 257, RuleTemplateName = 258, 
    RuleTemplateArgumentList = 259, RuleTemplateArgument = 260, RuleTypeNameSpecifier = 261, 
    RuleExplicitInstantiation = 262, RuleExplicitSpecialization = 263, RuleTryBlock = 264, 
    RuleFunctionTryBlock = 265, RuleHandlerSeq = 266, RuleHandler = 267, 
    RuleExceptionDeclaration = 268, RuleThrowExpression = 269, RuleExceptionSpecification = 270, 
    RuleDynamicExceptionSpecification = 271, RuleTypeIdList = 272, RuleNoeExceptSpecification = 273, 
    RulePlan_pragma = 274, RulePlan_directive = 275, RulePlan_dir_vectorized = 276, 
    RulePlan_dir_clustered = 277, RulePlan_common = 278, RulePlan_gpu = 279, 
    RuleTheOperator = 280, RuleLiteral = 281
  };

  explicit ReentParser(antlr4::TokenStream *input);
  ~ReentParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  	const int static_flag = 0x1;
  	bool in_reenterable = false;
  	bool in_chain = false;
  	bool _in_gpu_local = false;
  	bool reent_static = false;
  	bool allow_vectorized = false;
  	bool allow_clustered = false;
  	bool common_block_opened = false;
  	bool gpu_block_opened = false;
  	std::map<std::string,int> reenterables;
  	std::map<std::string,int> chains;
  	std::set<std::string> _reent_chain_params;
  	std::set<std::string> _reent_planned_refs;
  	std::string last_declarator_id;
  	std::string last_reent_chain_declarator;


  class TranslationUnitContext;
  class AnyIdentifierContext;
  class PrimaryExpressionContext;
  class IdExpressionContext;
  class Reent_funs_idContext;
  class Chain_funs_idContext;
  class UnqualifiedIdContext;
  class QualifiedIdContext;
  class NestedNameSpecifierContext;
  class LambdaExpressionContext;
  class LambdaIntroducerContext;
  class LambdaCaptureContext;
  class CaptureDefaultContext;
  class CaptureListContext;
  class CaptureContext;
  class SimpleCaptureContext;
  class InitcaptureContext;
  class LambdaDeclaratorContext;
  class PostfixExpressionContext;
  class TypeIdOfTheTypeIdContext;
  class ExpressionListContext;
  class PseudoDestructorNameContext;
  class UnaryExpressionContext;
  class UnaryOperatorContext;
  class NewExpressionContext;
  class NewPlacementContext;
  class NewTypeIdContext;
  class NewDeclaratorContext;
  class NoPointerNewDeclaratorContext;
  class NewInitializerContext;
  class DeleteExpressionContext;
  class NoExceptExpressionContext;
  class CastExpressionContext;
  class PointerMemberExpressionContext;
  class MultiplicativeExpressionContext;
  class AdditiveExpressionContext;
  class ShiftExpressionContext;
  class ShiftOperatorContext;
  class RelationalExpressionContext;
  class EqualityExpressionContext;
  class AndExpressionContext;
  class ExclusiveOrExpressionContext;
  class InclusiveOrExpressionContext;
  class LogicalAndExpressionContext;
  class LogicalOrExpressionContext;
  class ConditionalExpressionContext;
  class AssignmentExpressionContext;
  class AssignmentOperatorContext;
  class ExpressionContext;
  class ConstantExpressionContext;
  class StatementContext;
  class LabeledStatementContext;
  class Fill_into_planContext;
  class Fill_from_planContext;
  class Reent_fillerContext;
  class Reent_readerContext;
  class Reent_filler_arrayContext;
  class Reent_statementContext;
  class Chain_statementContext;
  class Atomic_blockContext;
  class Soft_atomic_blockContext;
  class Plan_firstContext;
  class Plan_get_firstContext;
  class Plan_lastContext;
  class Plan_get_lastContext;
  class Plan_registerContext;
  class Plan_registered_barrierContext;
  class Plan_criticalContext;
  class Plan_stopContext;
  class Clear_planContext;
  class Plan_group_firstContext;
  class Plan_group_lastContext;
  class Plan_group_parallelizeContext;
  class Plan_group_atomizeContext;
  class Plan_group_soft_atomizeContext;
  class Plan_group_vectorizeContext;
  class Throw_firstContext;
  class Throw_lastContext;
  class Planning_paramsContext;
  class Reent_parameter_cutContext;
  class Reent_special_callContext;
  class Reent_continue_any_callContext;
  class Reent_compact_continueContext;
  class Reent_np_callContext;
  class Start_chainContext;
  class Start_single_proc_chainContext;
  class Start_multi_proc_chainContext;
  class Chain_descriptorContext;
  class Vector_chain_descriptorContext;
  class List_chain_descriptorContext;
  class Start_topologyContext;
  class Topology_itemContext;
  class Topology_lineContext;
  class Topology_reverseContext;
  class Topology_nodeContext;
  class Chain_callContext;
  class Qualified_call_statementContext;
  class ExpressionStatementContext;
  class CompoundStatementContext;
  class StatementSeqContext;
  class SelectionStatementContext;
  class ConditionContext;
  class IterationStatementContext;
  class ForInitStatementContext;
  class ForRangeDeclarationContext;
  class ForRangeInitializerContext;
  class JumpStatementContext;
  class DeclarationStatementContext;
  class DeclarationseqContext;
  class DeclarationContext;
  class BlockDeclarationContext;
  class AliasDeclarationContext;
  class SimpleDeclarationContext;
  class StaticAssertDeclarationContext;
  class EmptyDeclarationContext;
  class AttributeDeclarationContext;
  class DeclSpecifierContext;
  class DeclSpecifierSeqContext;
  class Reent_special_typeContext;
  class Reent_funnel_typeContext;
  class Reent_cfunnel_typeContext;
  class Reent_cvar_typeContext;
  class Reent_csem_typeContext;
  class Reent_soft_transact_arrayContext;
  class Reent_soft_transact_varContext;
  class Reent_soft_transact_inContext;
  class Reent_soft_transact_outContext;
  class Reent_plan_typeContext;
  class Reent_plan_item_typeContext;
  class StorageClassSpecifierContext;
  class FunctionSpecifierContext;
  class TypedefNameContext;
  class TypeSpecifierContext;
  class TrailingTypeSpecifierContext;
  class TypeSpecifierSeqContext;
  class TrailingTypeSpecifierSeqContext;
  class SimpleTypeLengthModifierContext;
  class SimpleTypeSignednessModifierContext;
  class SimpleTypeSpecifierContext;
  class TheTypeNameContext;
  class DecltypeSpecifierContext;
  class ElaboratedTypeSpecifierContext;
  class EnumNameContext;
  class EnumSpecifierContext;
  class EnumHeadContext;
  class OpaqueEnumDeclarationContext;
  class EnumkeyContext;
  class EnumbaseContext;
  class EnumeratorListContext;
  class EnumeratorDefinitionContext;
  class EnumeratorContext;
  class NamespaceNameContext;
  class OriginalNamespaceNameContext;
  class NamespaceDefinitionContext;
  class NamespaceAliasContext;
  class NamespaceAliasDefinitionContext;
  class QualifiednamespacespecifierContext;
  class UsingDeclarationContext;
  class UsingDirectiveContext;
  class AsmDefinitionContext;
  class LinkageSpecificationContext;
  class AttributeSpecifierSeqContext;
  class AttributeSpecifierContext;
  class AlignmentspecifierContext;
  class AttributeListContext;
  class AttributeContext;
  class AttributeNamespaceContext;
  class AttributeArgumentClauseContext;
  class BalancedTokenSeqContext;
  class BalancedtokenContext;
  class InitDeclaratorListContext;
  class InitDeclaratorContext;
  class DeclaratorContext;
  class PointerDeclaratorContext;
  class NoPointerDeclaratorContext;
  class ParametersAndQualifiersContext;
  class TrailingReturnTypeContext;
  class PointerOperatorContext;
  class CvqualifierseqContext;
  class CvQualifierContext;
  class RefqualifierContext;
  class DeclaratoridContext;
  class TheTypeIdContext;
  class AbstractDeclaratorContext;
  class PointerAbstractDeclaratorContext;
  class NoPointerAbstractDeclaratorContext;
  class AbstractPackDeclaratorContext;
  class NoPointerAbstractPackDeclaratorContext;
  class ParameterDeclarationClauseContext;
  class ParameterDeclarationListContext;
  class ParameterDeclarationContext;
  class ReenterableDefinitionContext;
  class ReenterableDeclarationContext;
  class ReenterableHeadContext;
  class Reent_chain_headerContext;
  class Reent_chain_paramsContext;
  class Reent_chain_paramContext;
  class Reent_recursive_typeContext;
  class Reent_reductionContext;
  class Reent_gpu_globalContext;
  class Reent_gpu_localContext;
  class Reduction_symbolContext;
  class Reent_chain_predicateContext;
  class Reent_predicate_setContext;
  class Reent_predicate_resetContext;
  class Reent_predicate_dependsContext;
  class Reent_predicate_ifContext;
  class Reent_dependentsContext;
  class Reent_enumeratorContext;
  class Loop_statement_headerContext;
  class Reent_single_dependentContext;
  class Chain_interfaceContext;
  class ChainDefinitionContext;
  class ChainDeclarationContext;
  class ChainHeadContext;
  class FunctionDefinitionContext;
  class Special_method_nameContext;
  class FunctionBodyContext;
  class InitializerContext;
  class BraceOrEqualInitializerContext;
  class InitializerClauseContext;
  class InitializerListContext;
  class BracedInitListContext;
  class ClassNameContext;
  class ClassSpecifierContext;
  class ClassHeadContext;
  class ClassHeadNameContext;
  class ClassVirtSpecifierContext;
  class ClassKeyContext;
  class MemberSpecificationContext;
  class MarkedmemberdeclarationContext;
  class MemberdeclarationContext;
  class MemberDeclaratorListContext;
  class MemberDeclaratorContext;
  class VirtualSpecifierSeqContext;
  class VirtualSpecifierContext;
  class PureSpecifierContext;
  class BaseClauseContext;
  class BaseSpecifierListContext;
  class BaseSpecifierContext;
  class ClassOrDeclTypeContext;
  class BaseTypeSpecifierContext;
  class AccessSpecifierContext;
  class ConversionFunctionIdContext;
  class ConversionTypeIdContext;
  class ConversionDeclaratorContext;
  class ConstructorInitializerContext;
  class MemInitializerListContext;
  class MemInitializerContext;
  class MeminitializeridContext;
  class OperatorFunctionIdContext;
  class LiteralOperatorIdContext;
  class TemplateDeclarationContext;
  class TemplateparameterListContext;
  class TemplateParameterContext;
  class TypeParameterContext;
  class SimpleTemplateIdContext;
  class TemplateIdContext;
  class TemplateNameContext;
  class TemplateArgumentListContext;
  class TemplateArgumentContext;
  class TypeNameSpecifierContext;
  class ExplicitInstantiationContext;
  class ExplicitSpecializationContext;
  class TryBlockContext;
  class FunctionTryBlockContext;
  class HandlerSeqContext;
  class HandlerContext;
  class ExceptionDeclarationContext;
  class ThrowExpressionContext;
  class ExceptionSpecificationContext;
  class DynamicExceptionSpecificationContext;
  class TypeIdListContext;
  class NoeExceptSpecificationContext;
  class Plan_pragmaContext;
  class Plan_directiveContext;
  class Plan_dir_vectorizedContext;
  class Plan_dir_clusteredContext;
  class Plan_commonContext;
  class Plan_gpuContext;
  class TheOperatorContext;
  class LiteralContext; 

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    DeclarationseqContext *declarationseq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  AnyIdentifierContext : public antlr4::ParserRuleContext {
  public:
    AnyIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *In();
    antlr4::tree::TerminalNode *Out();
    antlr4::tree::TerminalNode *Set();
    antlr4::tree::TerminalNode *Reset();
    antlr4::tree::TerminalNode *Depends();
    antlr4::tree::TerminalNode *Plan();
    antlr4::tree::TerminalNode *Common();
    antlr4::tree::TerminalNode *Gpu();
    antlr4::tree::TerminalNode *Begin();
    antlr4::tree::TerminalNode *End();
    antlr4::tree::TerminalNode *Local();
    antlr4::tree::TerminalNode *Global();
    antlr4::tree::TerminalNode *MarkState();
    antlr4::tree::TerminalNode *MarkPreCondition();
    antlr4::tree::TerminalNode *Vectorized();
    antlr4::tree::TerminalNode *Clustered();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnyIdentifierContext* anyIdentifier();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LiteralContext *> literal();
    LiteralContext* literal(size_t i);
    antlr4::tree::TerminalNode *This();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();
    Reent_funs_idContext *reent_funs_id();
    Chain_funs_idContext *chain_funs_id();
    IdExpressionContext *idExpression();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  IdExpressionContext : public antlr4::ParserRuleContext {
  public:
    IdExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdContext *qualifiedId();
    UnqualifiedIdContext *unqualifiedId();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdExpressionContext* idExpression();

  class  Reent_funs_idContext : public antlr4::ParserRuleContext {
  public:
    Reent_funs_idContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_first();
    antlr4::tree::TerminalNode *Plan_last();
    antlr4::tree::TerminalNode *Plan_stop();
    antlr4::tree::TerminalNode *Clear_plan();
    antlr4::tree::TerminalNode *Plan_get_first();
    antlr4::tree::TerminalNode *Plan_get_last();
    antlr4::tree::TerminalNode *Plan_group_first();
    antlr4::tree::TerminalNode *Plan_group_last();
    antlr4::tree::TerminalNode *Plan_group_parallelize();
    antlr4::tree::TerminalNode *Plan_group_vectorize();
    antlr4::tree::TerminalNode *Plan_group_atomize();
    antlr4::tree::TerminalNode *Plan_group_soft_atomize();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_funs_idContext* reent_funs_id();

  class  Chain_funs_idContext : public antlr4::ParserRuleContext {
  public:
    Chain_funs_idContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw_first();
    antlr4::tree::TerminalNode *Throw_last();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chain_funs_idContext* chain_funs_id();

  class  UnqualifiedIdContext : public antlr4::ParserRuleContext {
  public:
    UnqualifiedIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TemplateIdContext *templateId();
    AnyIdentifierContext *anyIdentifier();
    OperatorFunctionIdContext *operatorFunctionId();
    ConversionFunctionIdContext *conversionFunctionId();
    LiteralOperatorIdContext *literalOperatorId();
    antlr4::tree::TerminalNode *Tilde();
    ClassNameContext *className();
    DecltypeSpecifierContext *decltypeSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnqualifiedIdContext* unqualifiedId();

  class  QualifiedIdContext : public antlr4::ParserRuleContext {
  public:
    QualifiedIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NestedNameSpecifierContext *nestedNameSpecifier();
    UnqualifiedIdContext *unqualifiedId();
    antlr4::tree::TerminalNode *Template();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QualifiedIdContext* qualifiedId();

  class  NestedNameSpecifierContext : public antlr4::ParserRuleContext {
  public:
    NestedNameSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Doublecolon();
    TheTypeNameContext *theTypeName();
    NamespaceNameContext *namespaceName();
    DecltypeSpecifierContext *decltypeSpecifier();
    NestedNameSpecifierContext *nestedNameSpecifier();
    AnyIdentifierContext *anyIdentifier();
    SimpleTemplateIdContext *simpleTemplateId();
    antlr4::tree::TerminalNode *Template();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NestedNameSpecifierContext* nestedNameSpecifier();
  NestedNameSpecifierContext* nestedNameSpecifier(int precedence);
  class  LambdaExpressionContext : public antlr4::ParserRuleContext {
  public:
    LambdaExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LambdaIntroducerContext *lambdaIntroducer();
    CompoundStatementContext *compoundStatement();
    LambdaDeclaratorContext *lambdaDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LambdaExpressionContext* lambdaExpression();

  class  LambdaIntroducerContext : public antlr4::ParserRuleContext {
  public:
    LambdaIntroducerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    LambdaCaptureContext *lambdaCapture();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LambdaIntroducerContext* lambdaIntroducer();

  class  LambdaCaptureContext : public antlr4::ParserRuleContext {
  public:
    LambdaCaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CaptureListContext *captureList();
    CaptureDefaultContext *captureDefault();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LambdaCaptureContext* lambdaCapture();

  class  CaptureDefaultContext : public antlr4::ParserRuleContext {
  public:
    CaptureDefaultContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *Assign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CaptureDefaultContext* captureDefault();

  class  CaptureListContext : public antlr4::ParserRuleContext {
  public:
    CaptureListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CaptureContext *> capture();
    CaptureContext* capture(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CaptureListContext* captureList();

  class  CaptureContext : public antlr4::ParserRuleContext {
  public:
    CaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleCaptureContext *simpleCapture();
    InitcaptureContext *initcapture();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CaptureContext* capture();

  class  SimpleCaptureContext : public antlr4::ParserRuleContext {
  public:
    SimpleCaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *This();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleCaptureContext* simpleCapture();

  class  InitcaptureContext : public antlr4::ParserRuleContext {
  public:
    InitcaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();
    InitializerContext *initializer();
    antlr4::tree::TerminalNode *And();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitcaptureContext* initcapture();

  class  LambdaDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    LambdaDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ParameterDeclarationClauseContext *parameterDeclarationClause();
    antlr4::tree::TerminalNode *Mutable();
    ExceptionSpecificationContext *exceptionSpecification();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    TrailingReturnTypeContext *trailingReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LambdaDeclaratorContext* lambdaDeclarator();

  class  PostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::PostfixExpressionContext *planned = nullptr;
    ReentParser::IdExpressionContext *ident = nullptr;
    PostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    TypeNameSpecifierContext *typeNameSpecifier();
    BracedInitListContext *bracedInitList();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Dynamic_cast();
    antlr4::tree::TerminalNode *Static_cast();
    antlr4::tree::TerminalNode *Reinterpret_cast();
    antlr4::tree::TerminalNode *Const_cast();
    TypeIdOfTheTypeIdContext *typeIdOfTheTypeId();
    PostfixExpressionContext *postfixExpression();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Arrow();
    PseudoDestructorNameContext *pseudoDestructorName();
    IdExpressionContext *idExpression();
    antlr4::tree::TerminalNode *Template();
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PostfixExpressionContext* postfixExpression();
  PostfixExpressionContext* postfixExpression(int precedence);
  class  TypeIdOfTheTypeIdContext : public antlr4::ParserRuleContext {
  public:
    TypeIdOfTheTypeIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Typeid_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeIdOfTheTypeIdContext* typeIdOfTheTypeId();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InitializerListContext *initializerList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionListContext* expressionList();

  class  PseudoDestructorNameContext : public antlr4::ParserRuleContext {
  public:
    PseudoDestructorNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Tilde();
    std::vector<TheTypeNameContext *> theTypeName();
    TheTypeNameContext* theTypeName(size_t i);
    NestedNameSpecifierContext *nestedNameSpecifier();
    antlr4::tree::TerminalNode *Doublecolon();
    antlr4::tree::TerminalNode *Template();
    SimpleTemplateIdContext *simpleTemplateId();
    DecltypeSpecifierContext *decltypeSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoDestructorNameContext* pseudoDestructorName();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PostfixExpressionContext *postfixExpression();
    antlr4::tree::TerminalNode *Sizeof();
    antlr4::tree::TerminalNode *LeftParen();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Ellipsis();
    AnyIdentifierContext *anyIdentifier();
    UnaryExpressionContext *unaryExpression();
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();
    UnaryOperatorContext *unaryOperator();
    CastExpressionContext *castExpression();
    antlr4::tree::TerminalNode *Alignof();
    NoExceptExpressionContext *noExceptExpression();
    NewExpressionContext *newExpression();
    DeleteExpressionContext *deleteExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Or();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Tilde();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Not();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryOperatorContext* unaryOperator();

  class  NewExpressionContext : public antlr4::ParserRuleContext {
  public:
    NewExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *New();
    NewTypeIdContext *newTypeId();
    antlr4::tree::TerminalNode *Doublecolon();
    NewPlacementContext *newPlacement();
    NewInitializerContext *newInitializer();
    antlr4::tree::TerminalNode *LeftParen();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewExpressionContext* newExpression();

  class  NewPlacementContext : public antlr4::ParserRuleContext {
  public:
    NewPlacementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewPlacementContext* newPlacement();

  class  NewTypeIdContext : public antlr4::ParserRuleContext {
  public:
    NewTypeIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierSeqContext *typeSpecifierSeq();
    NewDeclaratorContext *newDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewTypeIdContext* newTypeId();

  class  NewDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    NewDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointerOperatorContext *pointerOperator();
    NewDeclaratorContext *newDeclarator();
    NoPointerNewDeclaratorContext *noPointerNewDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewDeclaratorContext* newDeclarator();

  class  NoPointerNewDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    NoPointerNewDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightBracket();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    NoPointerNewDeclaratorContext *noPointerNewDeclarator();
    ConstantExpressionContext *constantExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoPointerNewDeclaratorContext* noPointerNewDeclarator();
  NoPointerNewDeclaratorContext* noPointerNewDeclarator(int precedence);
  class  NewInitializerContext : public antlr4::ParserRuleContext {
  public:
    NewInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ExpressionListContext *expressionList();
    BracedInitListContext *bracedInitList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewInitializerContext* newInitializer();

  class  DeleteExpressionContext : public antlr4::ParserRuleContext {
  public:
    DeleteExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Delete();
    CastExpressionContext *castExpression();
    antlr4::tree::TerminalNode *Doublecolon();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteExpressionContext* deleteExpression();

  class  NoExceptExpressionContext : public antlr4::ParserRuleContext {
  public:
    NoExceptExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Noexcept();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoExceptExpressionContext* noExceptExpression();

  class  CastExpressionContext : public antlr4::ParserRuleContext {
  public:
    CastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    antlr4::tree::TerminalNode *LeftParen();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *RightParen();
    CastExpressionContext *castExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CastExpressionContext* castExpression();

  class  PointerMemberExpressionContext : public antlr4::ParserRuleContext {
  public:
    PointerMemberExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CastExpressionContext *> castExpression();
    CastExpressionContext* castExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DotStar();
    antlr4::tree::TerminalNode* DotStar(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ArrowStar();
    antlr4::tree::TerminalNode* ArrowStar(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PointerMemberExpressionContext* pointerMemberExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PointerMemberExpressionContext *> pointerMemberExpression();
    PointerMemberExpressionContext* pointerMemberExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Star();
    antlr4::tree::TerminalNode* Star(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Div();
    antlr4::tree::TerminalNode* Div(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Mod();
    antlr4::tree::TerminalNode* Mod(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Plus();
    antlr4::tree::TerminalNode* Plus(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Minus();
    antlr4::tree::TerminalNode* Minus(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  ShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    std::vector<ShiftOperatorContext *> shiftOperator();
    ShiftOperatorContext* shiftOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ShiftExpressionContext* shiftExpression();

  class  ShiftOperatorContext : public antlr4::ParserRuleContext {
  public:
    ShiftOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ShiftOperatorContext* shiftOperator();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LessEqual();
    antlr4::tree::TerminalNode* LessEqual(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GreaterEqual();
    antlr4::tree::TerminalNode* GreaterEqual(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpressionContext *> relationalExpression();
    RelationalExpressionContext* relationalExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Equal();
    antlr4::tree::TerminalNode* Equal(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NotEqual();
    antlr4::tree::TerminalNode* NotEqual(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EqualityExpressionContext* equalityExpression();

  class  AndExpressionContext : public antlr4::ParserRuleContext {
  public:
    AndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpressionContext *> equalityExpression();
    EqualityExpressionContext* equalityExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> And();
    antlr4::tree::TerminalNode* And(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AndExpressionContext* andExpression();

  class  ExclusiveOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExclusiveOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AndExpressionContext *> andExpression();
    AndExpressionContext* andExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Caret();
    antlr4::tree::TerminalNode* Caret(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExclusiveOrExpressionContext* exclusiveOrExpression();

  class  InclusiveOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    InclusiveOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExclusiveOrExpressionContext *> exclusiveOrExpression();
    ExclusiveOrExpressionContext* exclusiveOrExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Or();
    antlr4::tree::TerminalNode* Or(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InclusiveOrExpressionContext* inclusiveOrExpression();

  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InclusiveOrExpressionContext *> inclusiveOrExpression();
    InclusiveOrExpressionContext* inclusiveOrExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AndAnd();
    antlr4::tree::TerminalNode* AndAnd(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicalAndExpressionContext* logicalAndExpression();

  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OrOr();
    antlr4::tree::TerminalNode* OrOr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicalOrExpressionContext* logicalOrExpression();

  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExpressionContext *logicalOrExpression();
    antlr4::tree::TerminalNode *Question();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Colon();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConditionalExpressionContext* conditionalExpression();

  class  AssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();
    LogicalOrExpressionContext *logicalOrExpression();
    AssignmentOperatorContext *assignmentOperator();
    InitializerClauseContext *initializerClause();
    ThrowExpressionContext *throwExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentExpressionContext* assignmentExpression();

  class  AssignmentOperatorContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *StarAssign();
    antlr4::tree::TerminalNode *DivAssign();
    antlr4::tree::TerminalNode *ModAssign();
    antlr4::tree::TerminalNode *PlusAssign();
    antlr4::tree::TerminalNode *MinusAssign();
    antlr4::tree::TerminalNode *RightShiftAssign();
    antlr4::tree::TerminalNode *LeftShiftAssign();
    antlr4::tree::TerminalNode *AndAssign();
    antlr4::tree::TerminalNode *XorAssign();
    antlr4::tree::TerminalNode *OrAssign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  ConstantExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConstantExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstantExpressionContext* constantExpression();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabeledStatementContext *labeledStatement();
    Start_chainContext *start_chain();
    Start_topologyContext *start_topology();
    Fill_into_planContext *fill_into_plan();
    Fill_from_planContext *fill_from_plan();
    Plan_criticalContext *plan_critical();
    Reent_statementContext *reent_statement();
    Chain_statementContext *chain_statement();
    Reent_special_callContext *reent_special_call();
    Atomic_blockContext *atomic_block();
    Soft_atomic_blockContext *soft_atomic_block();
    Qualified_call_statementContext *qualified_call_statement();
    DeclarationStatementContext *declarationStatement();
    ExpressionStatementContext *expressionStatement();
    CompoundStatementContext *compoundStatement();
    SelectionStatementContext *selectionStatement();
    IterationStatementContext *iterationStatement();
    JumpStatementContext *jumpStatement();
    TryBlockContext *tryBlock();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  LabeledStatementContext : public antlr4::ParserRuleContext {
  public:
    LabeledStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Colon();
    StatementContext *statement();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *Case();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *Default();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LabeledStatementContext* labeledStatement();

  class  Fill_into_planContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Fill_into_planContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);
    antlr4::tree::TerminalNode *LeftBracket();
    std::vector<Reent_fillerContext *> reent_filler();
    Reent_fillerContext* reent_filler(size_t i);
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Fill_into_planContext* fill_into_plan();

  class  Fill_from_planContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Fill_from_planContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    antlr4::tree::TerminalNode *LeftBracket();
    std::vector<Reent_readerContext *> reent_reader();
    Reent_readerContext* reent_reader(size_t i);
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Fill_from_planContext* fill_from_plan();

  class  Reent_fillerContext : public antlr4::ParserRuleContext {
  public:
    Reent_fillerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Underscore();
    Reent_filler_arrayContext *reent_filler_array();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_fillerContext* reent_filler();

  class  Reent_readerContext : public antlr4::ParserRuleContext {
  public:
    Reent_readerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Underscore();
    Reent_filler_arrayContext *reent_filler_array();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_readerContext* reent_reader();

  class  Reent_filler_arrayContext : public antlr4::ParserRuleContext {
  public:
    Reent_filler_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_filler_arrayContext* reent_filler_array();

  class  Reent_statementContext : public antlr4::ParserRuleContext {
  public:
    Reent_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Plan_firstContext *plan_first();
    Plan_lastContext *plan_last();
    Plan_stopContext *plan_stop();
    Clear_planContext *clear_plan();
    Plan_get_firstContext *plan_get_first();
    Plan_get_lastContext *plan_get_last();
    Plan_registerContext *plan_register();
    Plan_registered_barrierContext *plan_registered_barrier();
    Plan_group_firstContext *plan_group_first();
    Plan_group_lastContext *plan_group_last();
    Plan_group_parallelizeContext *plan_group_parallelize();
    Plan_group_vectorizeContext *plan_group_vectorize();
    Plan_group_atomizeContext *plan_group_atomize();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_statementContext* reent_statement();

  class  Chain_statementContext : public antlr4::ParserRuleContext {
  public:
    Chain_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Throw_firstContext *throw_first();
    Throw_lastContext *throw_last();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chain_statementContext* chain_statement();

  class  Atomic_blockContext : public antlr4::ParserRuleContext {
  public:
    Atomic_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_atomize();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Atomic_blockContext* atomic_block();

  class  Soft_atomic_blockContext : public antlr4::ParserRuleContext {
  public:
    Soft_atomic_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Transaction_atomic();
    antlr4::tree::TerminalNode *LeftParen();
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *RightParen();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Soft_atomic_blockContext* soft_atomic_block();

  class  Plan_firstContext : public antlr4::ParserRuleContext {
  public:
    Plan_firstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_first();
    antlr4::tree::TerminalNode *LeftParen();
    Planning_paramsContext *planning_params();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_firstContext* plan_first();

  class  Plan_get_firstContext : public antlr4::ParserRuleContext {
  public:
    Plan_get_firstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_get_first();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_get_firstContext* plan_get_first();

  class  Plan_lastContext : public antlr4::ParserRuleContext {
  public:
    Plan_lastContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_last();
    antlr4::tree::TerminalNode *LeftParen();
    Planning_paramsContext *planning_params();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_lastContext* plan_last();

  class  Plan_get_lastContext : public antlr4::ParserRuleContext {
  public:
    Plan_get_lastContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_get_last();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_get_lastContext* plan_get_last();

  class  Plan_registerContext : public antlr4::ParserRuleContext {
  public:
    Plan_registerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_register();
    antlr4::tree::TerminalNode *LeftParen();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_registerContext* plan_register();

  class  Plan_registered_barrierContext : public antlr4::ParserRuleContext {
  public:
    Plan_registered_barrierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_registered_barrier();
    antlr4::tree::TerminalNode *LeftParen();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_registered_barrierContext* plan_registered_barrier();

  class  Plan_criticalContext : public antlr4::ParserRuleContext {
  public:
    Plan_criticalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_critical();
    antlr4::tree::TerminalNode *LeftParen();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *RightParen();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_criticalContext* plan_critical();

  class  Plan_stopContext : public antlr4::ParserRuleContext {
  public:
    Plan_stopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_stop();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_stopContext* plan_stop();

  class  Clear_planContext : public antlr4::ParserRuleContext {
  public:
    Clear_planContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Clear_plan();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Clear_planContext* clear_plan();

  class  Plan_group_firstContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_firstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_first();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_firstContext* plan_group_first();

  class  Plan_group_lastContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_lastContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_last();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_lastContext* plan_group_last();

  class  Plan_group_parallelizeContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_parallelizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_parallelize();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_parallelizeContext* plan_group_parallelize();

  class  Plan_group_atomizeContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_atomizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_atomize();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_atomizeContext* plan_group_atomize();

  class  Plan_group_soft_atomizeContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_soft_atomizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_soft_atomize();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_soft_atomizeContext* plan_group_soft_atomize();

  class  Plan_group_vectorizeContext : public antlr4::ParserRuleContext {
  public:
    Plan_group_vectorizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_group_vectorize();
    antlr4::tree::TerminalNode *LeftParen();
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_group_vectorizeContext* plan_group_vectorize();

  class  Throw_firstContext : public antlr4::ParserRuleContext {
  public:
    Throw_firstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw_first();
    antlr4::tree::TerminalNode *LeftParen();
    Planning_paramsContext *planning_params();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Throw_firstContext* throw_first();

  class  Throw_lastContext : public antlr4::ParserRuleContext {
  public:
    Throw_lastContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw_last();
    antlr4::tree::TerminalNode *LeftParen();
    Planning_paramsContext *planning_params();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Throw_lastContext* throw_last();

  class  Planning_paramsContext : public antlr4::ParserRuleContext {
  public:
    Planning_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);
    std::vector<Reent_parameter_cutContext *> reent_parameter_cut();
    Reent_parameter_cutContext* reent_parameter_cut(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Planning_paramsContext* planning_params();

  class  Reent_parameter_cutContext : public antlr4::ParserRuleContext {
  public:
    Reent_parameter_cutContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Not();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_parameter_cutContext* reent_parameter_cut();

  class  Reent_special_callContext : public antlr4::ParserRuleContext {
  public:
    Reent_special_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reent_continue_any_callContext *reent_continue_any_call();
    Reent_compact_continueContext *reent_compact_continue();
    Reent_np_callContext *reent_np_call();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_special_callContext* reent_special_call();

  class  Reent_continue_any_callContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::AnyIdentifierContext *ident = nullptr;
    Reent_continue_any_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Continue();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();
    AnyIdentifierContext *anyIdentifier();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_continue_any_callContext* reent_continue_any_call();

  class  Reent_compact_continueContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::AnyIdentifierContext *ident = nullptr;
    Reent_compact_continueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();
    AnyIdentifierContext *anyIdentifier();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_compact_continueContext* reent_compact_continue();

  class  Reent_np_callContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::AnyIdentifierContext *ident = nullptr;
    Reent_np_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *Semi();
    AnyIdentifierContext *anyIdentifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_np_callContext* reent_np_call();

  class  Start_chainContext : public antlr4::ParserRuleContext {
  public:
    Start_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Start_single_proc_chainContext *start_single_proc_chain();
    Start_multi_proc_chainContext *start_multi_proc_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Start_chainContext* start_chain();

  class  Start_single_proc_chainContext : public antlr4::ParserRuleContext {
  public:
    Start_single_proc_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_chain();
    antlr4::tree::TerminalNode *LeftParen();
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *Comma();
    Chain_descriptorContext *chain_descriptor();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Start_single_proc_chainContext* start_single_proc_chain();

  class  Start_multi_proc_chainContext : public antlr4::ParserRuleContext {
  public:
    Start_multi_proc_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_parallel_chain();
    std::vector<antlr4::tree::TerminalNode *> LeftParen();
    antlr4::tree::TerminalNode* LeftParen(size_t i);
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *Comma();
    Chain_descriptorContext *chain_descriptor();
    std::vector<antlr4::tree::TerminalNode *> RightParen();
    antlr4::tree::TerminalNode* RightParen(size_t i);
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Clustered();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Start_multi_proc_chainContext* start_multi_proc_chain();

  class  Chain_descriptorContext : public antlr4::ParserRuleContext {
  public:
    Chain_descriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Vector_chain_descriptorContext *vector_chain_descriptor();
    List_chain_descriptorContext *list_chain_descriptor();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chain_descriptorContext* chain_descriptor();

  class  Vector_chain_descriptorContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::PrimaryExpressionContext *ident = nullptr;
    Vector_chain_descriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Comma();
    Chain_callContext *chain_call();
    PrimaryExpressionContext *primaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Vector_chain_descriptorContext* vector_chain_descriptor();

  class  List_chain_descriptorContext : public antlr4::ParserRuleContext {
  public:
    List_chain_descriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Chain_callContext *> chain_call();
    Chain_callContext* chain_call(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Arrow();
    antlr4::tree::TerminalNode* Arrow(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  List_chain_descriptorContext* list_chain_descriptor();

  class  Start_topologyContext : public antlr4::ParserRuleContext {
  public:
    Start_topologyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_topology();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Clustered();
    antlr4::tree::TerminalNode *LeftParen();
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<Topology_itemContext *> topology_item();
    Topology_itemContext* topology_item(size_t i);
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Start_topologyContext* start_topology();

  class  Topology_itemContext : public antlr4::ParserRuleContext {
  public:
    Topology_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    Topology_lineContext *topology_line();
    Topology_reverseContext *topology_reverse();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Topology_itemContext* topology_item();

  class  Topology_lineContext : public antlr4::ParserRuleContext {
  public:
    Topology_lineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_parallel_chain();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Topology_nodeContext *> topology_node();
    Topology_nodeContext* topology_node(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    std::vector<antlr4::tree::TerminalNode *> Arrow();
    antlr4::tree::TerminalNode* Arrow(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Topology_lineContext* topology_line();

  class  Topology_reverseContext : public antlr4::ParserRuleContext {
  public:
    Topology_reverseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_parallel_reverse();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<Topology_nodeContext *> topology_node();
    Topology_nodeContext* topology_node(size_t i);
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Arrow();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Topology_reverseContext* topology_reverse();

  class  Topology_nodeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Topology_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();
    std::vector<antlr4::tree::TerminalNode *> IntegerLiteral();
    antlr4::tree::TerminalNode* IntegerLiteral(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Topology_nodeContext* topology_node();

  class  Chain_callContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Chain_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Div();
    PrimaryExpressionContext *primaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chain_callContext* chain_call();

  class  Qualified_call_statementContext : public antlr4::ParserRuleContext {
  public:
    Qualified_call_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdContext *qualifiedId();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_call_statementContext* qualified_call_statement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    StatementSeqContext *statementSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  StatementSeqContext : public antlr4::ParserRuleContext {
  public:
    StatementSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementSeqContext* statementSeq();

  class  SelectionStatementContext : public antlr4::ParserRuleContext {
  public:
    SelectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContext *condition();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *Else();
    antlr4::tree::TerminalNode *Switch();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectionStatementContext* selectionStatement();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    DeclSpecifierSeqContext *declSpecifierSeq();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Assign();
    InitializerClauseContext *initializerClause();
    BracedInitListContext *bracedInitList();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConditionContext* condition();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *While();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContext *condition();
    antlr4::tree::TerminalNode *RightParen();
    StatementContext *statement();
    antlr4::tree::TerminalNode *Do();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *For();
    ForInitStatementContext *forInitStatement();
    ForRangeDeclarationContext *forRangeDeclaration();
    antlr4::tree::TerminalNode *Colon();
    ForRangeInitializerContext *forRangeInitializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  ForInitStatementContext : public antlr4::ParserRuleContext {
  public:
    ForInitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionStatementContext *expressionStatement();
    SimpleDeclarationContext *simpleDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForInitStatementContext* forInitStatement();

  class  ForRangeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ForRangeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclSpecifierSeqContext *declSpecifierSeq();
    DeclaratorContext *declarator();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForRangeDeclarationContext* forRangeDeclaration();

  class  ForRangeInitializerContext : public antlr4::ParserRuleContext {
  public:
    ForRangeInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    BracedInitListContext *bracedInitList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForRangeInitializerContext* forRangeInitializer();

  class  JumpStatementContext : public antlr4::ParserRuleContext {
  public:
    JumpStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Break();
    antlr4::tree::TerminalNode *Continue();
    antlr4::tree::TerminalNode *Return();
    antlr4::tree::TerminalNode *Goto();
    AnyIdentifierContext *anyIdentifier();
    ExpressionContext *expression();
    BracedInitListContext *bracedInitList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JumpStatementContext* jumpStatement();

  class  DeclarationStatementContext : public antlr4::ParserRuleContext {
  public:
    DeclarationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockDeclarationContext *blockDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationStatementContext* declarationStatement();

  class  DeclarationseqContext : public antlr4::ParserRuleContext {
  public:
    DeclarationseqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationseqContext* declarationseq();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Plan_pragmaContext *plan_pragma();
    ReenterableDeclarationContext *reenterableDeclaration();
    ReenterableDefinitionContext *reenterableDefinition();
    ChainDeclarationContext *chainDeclaration();
    ChainDefinitionContext *chainDefinition();
    FunctionDefinitionContext *functionDefinition();
    BlockDeclarationContext *blockDeclaration();
    TemplateDeclarationContext *templateDeclaration();
    ExplicitInstantiationContext *explicitInstantiation();
    ExplicitSpecializationContext *explicitSpecialization();
    LinkageSpecificationContext *linkageSpecification();
    NamespaceDefinitionContext *namespaceDefinition();
    EmptyDeclarationContext *emptyDeclaration();
    AttributeDeclarationContext *attributeDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationContext* declaration();

  class  BlockDeclarationContext : public antlr4::ParserRuleContext {
  public:
    BlockDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleDeclarationContext *simpleDeclaration();
    AsmDefinitionContext *asmDefinition();
    NamespaceAliasDefinitionContext *namespaceAliasDefinition();
    UsingDeclarationContext *usingDeclaration();
    UsingDirectiveContext *usingDirective();
    StaticAssertDeclarationContext *staticAssertDeclaration();
    AliasDeclarationContext *aliasDeclaration();
    OpaqueEnumDeclarationContext *opaqueEnumDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlockDeclarationContext* blockDeclaration();

  class  AliasDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AliasDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Using();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *Assign();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *Semi();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AliasDeclarationContext* aliasDeclaration();

  class  SimpleDeclarationContext : public antlr4::ParserRuleContext {
  public:
    SimpleDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    DeclSpecifierSeqContext *declSpecifierSeq();
    InitDeclaratorListContext *initDeclaratorList();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleDeclarationContext* simpleDeclaration();

  class  StaticAssertDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StaticAssertDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Static_assert();
    antlr4::tree::TerminalNode *LeftParen();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StaticAssertDeclarationContext* staticAssertDeclaration();

  class  EmptyDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EmptyDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EmptyDeclarationContext* emptyDeclaration();

  class  AttributeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AttributeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeDeclarationContext* attributeDeclaration();

  class  DeclSpecifierContext : public antlr4::ParserRuleContext {
  public:
    DeclSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Friend();
    antlr4::tree::TerminalNode *Typedef();
    antlr4::tree::TerminalNode *Markupdef();
    antlr4::tree::TerminalNode *Constexpr();
    StorageClassSpecifierContext *storageClassSpecifier();
    TypeSpecifierContext *typeSpecifier();
    FunctionSpecifierContext *functionSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclSpecifierContext* declSpecifier();

  class  DeclSpecifierSeqContext : public antlr4::ParserRuleContext {
  public:
    DeclSpecifierSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclSpecifierContext *> declSpecifier();
    DeclSpecifierContext* declSpecifier(size_t i);
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclSpecifierSeqContext* declSpecifierSeq();

  class  Reent_special_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_special_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reent_funnel_typeContext *reent_funnel_type();
    Reent_cfunnel_typeContext *reent_cfunnel_type();
    Reent_cvar_typeContext *reent_cvar_type();
    Reent_csem_typeContext *reent_csem_type();
    Reent_soft_transact_arrayContext *reent_soft_transact_array();
    Reent_soft_transact_varContext *reent_soft_transact_var();
    Reent_soft_transact_inContext *reent_soft_transact_in();
    Reent_soft_transact_outContext *reent_soft_transact_out();
    Reent_plan_typeContext *reent_plan_type();
    Reent_plan_item_typeContext *reent_plan_item_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_special_typeContext* reent_special_type();

  class  Reent_funnel_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_funnel_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Funnel();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *Comma();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *In();
    antlr4::tree::TerminalNode *Out();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_funnel_typeContext* reent_funnel_type();

  class  Reent_cfunnel_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_cfunnel_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Cfunnel();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *Comma();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *In();
    antlr4::tree::TerminalNode *Out();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_cfunnel_typeContext* reent_cfunnel_type();

  class  Reent_cvar_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_cvar_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Cvar();
    antlr4::tree::TerminalNode *LeftParen();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_cvar_typeContext* reent_cvar_type();

  class  Reent_csem_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_csem_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Csem();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_csem_typeContext* reent_csem_type();

  class  Reent_soft_transact_arrayContext : public antlr4::ParserRuleContext {
  public:
    Reent_soft_transact_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Soft_transact_array();
    antlr4::tree::TerminalNode *LeftParen();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_soft_transact_arrayContext* reent_soft_transact_array();

  class  Reent_soft_transact_varContext : public antlr4::ParserRuleContext {
  public:
    Reent_soft_transact_varContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Soft_transact_var();
    antlr4::tree::TerminalNode *LeftParen();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_soft_transact_varContext* reent_soft_transact_var();

  class  Reent_soft_transact_inContext : public antlr4::ParserRuleContext {
  public:
    Reent_soft_transact_inContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Soft_transact_in();
    antlr4::tree::TerminalNode *LeftParen();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_soft_transact_inContext* reent_soft_transact_in();

  class  Reent_soft_transact_outContext : public antlr4::ParserRuleContext {
  public:
    Reent_soft_transact_outContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Soft_transact_out();
    antlr4::tree::TerminalNode *LeftParen();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_soft_transact_outContext* reent_soft_transact_out();

  class  Reent_plan_typeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Reent_plan_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_type();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_plan_typeContext* reent_plan_type();

  class  Reent_plan_item_typeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *ident = nullptr;
    Reent_plan_item_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plan_item_type();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_plan_item_typeContext* reent_plan_item_type();

  class  StorageClassSpecifierContext : public antlr4::ParserRuleContext {
  public:
    StorageClassSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Register();
    antlr4::tree::TerminalNode *Static();
    antlr4::tree::TerminalNode *Thread_local();
    antlr4::tree::TerminalNode *Extern();
    antlr4::tree::TerminalNode *Mutable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StorageClassSpecifierContext* storageClassSpecifier();

  class  FunctionSpecifierContext : public antlr4::ParserRuleContext {
  public:
    FunctionSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Inline();
    antlr4::tree::TerminalNode *Virtual();
    antlr4::tree::TerminalNode *Explicit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionSpecifierContext* functionSpecifier();

  class  TypedefNameContext : public antlr4::ParserRuleContext {
  public:
    TypedefNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypedefNameContext* typedefName();

  class  TypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reent_special_typeContext *reent_special_type();
    ClassSpecifierContext *classSpecifier();
    TrailingTypeSpecifierContext *trailingTypeSpecifier();
    EnumSpecifierContext *enumSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeSpecifierContext* typeSpecifier();

  class  TrailingTypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TrailingTypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElaboratedTypeSpecifierContext *elaboratedTypeSpecifier();
    TypeNameSpecifierContext *typeNameSpecifier();
    CvQualifierContext *cvQualifier();
    SimpleTypeSpecifierContext *simpleTypeSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TrailingTypeSpecifierContext* trailingTypeSpecifier();

  class  TypeSpecifierSeqContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecifierSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeSpecifierContext *> typeSpecifier();
    TypeSpecifierContext* typeSpecifier(size_t i);
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeSpecifierSeqContext* typeSpecifierSeq();

  class  TrailingTypeSpecifierSeqContext : public antlr4::ParserRuleContext {
  public:
    TrailingTypeSpecifierSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TrailingTypeSpecifierContext *> trailingTypeSpecifier();
    TrailingTypeSpecifierContext* trailingTypeSpecifier(size_t i);
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TrailingTypeSpecifierSeqContext* trailingTypeSpecifierSeq();

  class  SimpleTypeLengthModifierContext : public antlr4::ParserRuleContext {
  public:
    SimpleTypeLengthModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Short();
    antlr4::tree::TerminalNode *Long();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleTypeLengthModifierContext* simpleTypeLengthModifier();

  class  SimpleTypeSignednessModifierContext : public antlr4::ParserRuleContext {
  public:
    SimpleTypeSignednessModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Unsigned();
    antlr4::tree::TerminalNode *Signed();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleTypeSignednessModifierContext* simpleTypeSignednessModifier();

  class  SimpleTypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    SimpleTypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TheTypeNameContext *theTypeName();
    NestedNameSpecifierContext *nestedNameSpecifier();
    antlr4::tree::TerminalNode *Template();
    SimpleTemplateIdContext *simpleTemplateId();
    SimpleTypeSignednessModifierContext *simpleTypeSignednessModifier();
    std::vector<SimpleTypeLengthModifierContext *> simpleTypeLengthModifier();
    SimpleTypeLengthModifierContext* simpleTypeLengthModifier(size_t i);
    antlr4::tree::TerminalNode *Char();
    antlr4::tree::TerminalNode *Char16();
    antlr4::tree::TerminalNode *Char32();
    antlr4::tree::TerminalNode *Wchar();
    antlr4::tree::TerminalNode *Bool();
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *Double();
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *Auto();
    DecltypeSpecifierContext *decltypeSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleTypeSpecifierContext* simpleTypeSpecifier();

  class  TheTypeNameContext : public antlr4::ParserRuleContext {
  public:
    TheTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassNameContext *className();
    EnumNameContext *enumName();
    TypedefNameContext *typedefName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TheTypeNameContext* theTypeName();

  class  DecltypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    DecltypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Decltype();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Auto();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DecltypeSpecifierContext* decltypeSpecifier();

  class  ElaboratedTypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ElaboratedTypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassKeyContext *classKey();
    AnyIdentifierContext *anyIdentifier();
    SimpleTemplateIdContext *simpleTemplateId();
    NestedNameSpecifierContext *nestedNameSpecifier();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    antlr4::tree::TerminalNode *Template();
    antlr4::tree::TerminalNode *Enum();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElaboratedTypeSpecifierContext* elaboratedTypeSpecifier();

  class  EnumNameContext : public antlr4::ParserRuleContext {
  public:
    EnumNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumNameContext* enumName();

  class  EnumSpecifierContext : public antlr4::ParserRuleContext {
  public:
    EnumSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EnumHeadContext *enumHead();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    EnumeratorListContext *enumeratorList();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumSpecifierContext* enumSpecifier();

  class  EnumHeadContext : public antlr4::ParserRuleContext {
  public:
    EnumHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EnumkeyContext *enumkey();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    AnyIdentifierContext *anyIdentifier();
    EnumbaseContext *enumbase();
    NestedNameSpecifierContext *nestedNameSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumHeadContext* enumHead();

  class  OpaqueEnumDeclarationContext : public antlr4::ParserRuleContext {
  public:
    OpaqueEnumDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EnumkeyContext *enumkey();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *Semi();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    EnumbaseContext *enumbase();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OpaqueEnumDeclarationContext* opaqueEnumDeclaration();

  class  EnumkeyContext : public antlr4::ParserRuleContext {
  public:
    EnumkeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Enum();
    antlr4::tree::TerminalNode *Class();
    antlr4::tree::TerminalNode *Struct();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumkeyContext* enumkey();

  class  EnumbaseContext : public antlr4::ParserRuleContext {
  public:
    EnumbaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Colon();
    TypeSpecifierSeqContext *typeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumbaseContext* enumbase();

  class  EnumeratorListContext : public antlr4::ParserRuleContext {
  public:
    EnumeratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EnumeratorDefinitionContext *> enumeratorDefinition();
    EnumeratorDefinitionContext* enumeratorDefinition(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumeratorListContext* enumeratorList();

  class  EnumeratorDefinitionContext : public antlr4::ParserRuleContext {
  public:
    EnumeratorDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EnumeratorContext *enumerator();
    antlr4::tree::TerminalNode *Assign();
    ConstantExpressionContext *constantExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumeratorDefinitionContext* enumeratorDefinition();

  class  EnumeratorContext : public antlr4::ParserRuleContext {
  public:
    EnumeratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumeratorContext* enumerator();

  class  NamespaceNameContext : public antlr4::ParserRuleContext {
  public:
    NamespaceNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OriginalNamespaceNameContext *originalNamespaceName();
    NamespaceAliasContext *namespaceAlias();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceNameContext* namespaceName();

  class  OriginalNamespaceNameContext : public antlr4::ParserRuleContext {
  public:
    OriginalNamespaceNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginalNamespaceNameContext* originalNamespaceName();

  class  NamespaceDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::DeclarationseqContext *namespaceBody = nullptr;
    NamespaceDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Namespace();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Inline();
    AnyIdentifierContext *anyIdentifier();
    OriginalNamespaceNameContext *originalNamespaceName();
    DeclarationseqContext *declarationseq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceDefinitionContext* namespaceDefinition();

  class  NamespaceAliasContext : public antlr4::ParserRuleContext {
  public:
    NamespaceAliasContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceAliasContext* namespaceAlias();

  class  NamespaceAliasDefinitionContext : public antlr4::ParserRuleContext {
  public:
    NamespaceAliasDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Namespace();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *Assign();
    QualifiednamespacespecifierContext *qualifiednamespacespecifier();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceAliasDefinitionContext* namespaceAliasDefinition();

  class  QualifiednamespacespecifierContext : public antlr4::ParserRuleContext {
  public:
    QualifiednamespacespecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamespaceNameContext *namespaceName();
    NestedNameSpecifierContext *nestedNameSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QualifiednamespacespecifierContext* qualifiednamespacespecifier();

  class  UsingDeclarationContext : public antlr4::ParserRuleContext {
  public:
    UsingDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Using();
    UnqualifiedIdContext *unqualifiedId();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Doublecolon();
    NestedNameSpecifierContext *nestedNameSpecifier();
    antlr4::tree::TerminalNode *Typename_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UsingDeclarationContext* usingDeclaration();

  class  UsingDirectiveContext : public antlr4::ParserRuleContext {
  public:
    UsingDirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Using();
    antlr4::tree::TerminalNode *Namespace();
    NamespaceNameContext *namespaceName();
    antlr4::tree::TerminalNode *Semi();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    NestedNameSpecifierContext *nestedNameSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UsingDirectiveContext* usingDirective();

  class  AsmDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AsmDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Asm();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsmDefinitionContext* asmDefinition();

  class  LinkageSpecificationContext : public antlr4::ParserRuleContext {
  public:
    LinkageSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Extern();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    DeclarationContext *declaration();
    DeclarationseqContext *declarationseq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LinkageSpecificationContext* linkageSpecification();

  class  AttributeSpecifierSeqContext : public antlr4::ParserRuleContext {
  public:
    AttributeSpecifierSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AttributeSpecifierContext *> attributeSpecifier();
    AttributeSpecifierContext* attributeSpecifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeSpecifierSeqContext* attributeSpecifierSeq();

  class  AttributeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AttributeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    AttributeListContext *attributeList();
    AlignmentspecifierContext *alignmentspecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeSpecifierContext* attributeSpecifier();

  class  AlignmentspecifierContext : public antlr4::ParserRuleContext {
  public:
    AlignmentspecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Alignas();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    TheTypeIdContext *theTypeId();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AlignmentspecifierContext* alignmentspecifier();

  class  AttributeListContext : public antlr4::ParserRuleContext {
  public:
    AttributeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeListContext* attributeList();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();
    AttributeNamespaceContext *attributeNamespace();
    antlr4::tree::TerminalNode *Doublecolon();
    AttributeArgumentClauseContext *attributeArgumentClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeContext* attribute();

  class  AttributeNamespaceContext : public antlr4::ParserRuleContext {
  public:
    AttributeNamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeNamespaceContext* attributeNamespace();

  class  AttributeArgumentClauseContext : public antlr4::ParserRuleContext {
  public:
    AttributeArgumentClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    BalancedTokenSeqContext *balancedTokenSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeArgumentClauseContext* attributeArgumentClause();

  class  BalancedTokenSeqContext : public antlr4::ParserRuleContext {
  public:
    BalancedTokenSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BalancedtokenContext *> balancedtoken();
    BalancedtokenContext* balancedtoken(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BalancedTokenSeqContext* balancedTokenSeq();

  class  BalancedtokenContext : public antlr4::ParserRuleContext {
  public:
    BalancedtokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LeftParen();
    antlr4::tree::TerminalNode* LeftParen(size_t i);
    BalancedTokenSeqContext *balancedTokenSeq();
    std::vector<antlr4::tree::TerminalNode *> RightParen();
    antlr4::tree::TerminalNode* RightParen(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LeftBrace();
    antlr4::tree::TerminalNode* LeftBrace(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBrace();
    antlr4::tree::TerminalNode* RightBrace(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BalancedtokenContext* balancedtoken();

  class  InitDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitDeclaratorContext *> initDeclarator();
    InitDeclaratorContext* initDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitDeclaratorListContext* initDeclaratorList();

  class  InitDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    InitializerContext *initializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitDeclaratorContext* initDeclarator();

  class  DeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointerDeclaratorContext *pointerDeclarator();
    NoPointerDeclaratorContext *noPointerDeclarator();
    ParametersAndQualifiersContext *parametersAndQualifiers();
    TrailingReturnTypeContext *trailingReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclaratorContext* declarator();

  class  PointerDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    PointerDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NoPointerDeclaratorContext *noPointerDeclarator();
    std::vector<PointerOperatorContext *> pointerOperator();
    PointerOperatorContext* pointerOperator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Const();
    antlr4::tree::TerminalNode* Const(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PointerDeclaratorContext* pointerDeclarator();

  class  NoPointerDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    NoPointerDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratoridContext *declaratorid();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    antlr4::tree::TerminalNode *LeftParen();
    PointerDeclaratorContext *pointerDeclarator();
    antlr4::tree::TerminalNode *RightParen();
    NoPointerDeclaratorContext *noPointerDeclarator();
    ParametersAndQualifiersContext *parametersAndQualifiers();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    ConstantExpressionContext *constantExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoPointerDeclaratorContext* noPointerDeclarator();
  NoPointerDeclaratorContext* noPointerDeclarator(int precedence);
  class  ParametersAndQualifiersContext : public antlr4::ParserRuleContext {
  public:
    ParametersAndQualifiersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ParameterDeclarationClauseContext *parameterDeclarationClause();
    CvqualifierseqContext *cvqualifierseq();
    RefqualifierContext *refqualifier();
    ExceptionSpecificationContext *exceptionSpecification();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParametersAndQualifiersContext* parametersAndQualifiers();

  class  TrailingReturnTypeContext : public antlr4::ParserRuleContext {
  public:
    TrailingReturnTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Arrow();
    TrailingTypeSpecifierSeqContext *trailingTypeSpecifierSeq();
    AbstractDeclaratorContext *abstractDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TrailingReturnTypeContext* trailingReturnType();

  class  PointerOperatorContext : public antlr4::ParserRuleContext {
  public:
    PointerOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *AndAnd();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    antlr4::tree::TerminalNode *Star();
    NestedNameSpecifierContext *nestedNameSpecifier();
    CvqualifierseqContext *cvqualifierseq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PointerOperatorContext* pointerOperator();

  class  CvqualifierseqContext : public antlr4::ParserRuleContext {
  public:
    CvqualifierseqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CvQualifierContext *> cvQualifier();
    CvQualifierContext* cvQualifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CvqualifierseqContext* cvqualifierseq();

  class  CvQualifierContext : public antlr4::ParserRuleContext {
  public:
    CvQualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *Volatile();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CvQualifierContext* cvQualifier();

  class  RefqualifierContext : public antlr4::ParserRuleContext {
  public:
    RefqualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *AndAnd();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RefqualifierContext* refqualifier();

  class  DeclaratoridContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::IdExpressionContext *ident = nullptr;
    DeclaratoridContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdExpressionContext *idExpression();
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclaratoridContext* declaratorid();

  class  TheTypeIdContext : public antlr4::ParserRuleContext {
  public:
    TheTypeIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierSeqContext *typeSpecifierSeq();
    AbstractDeclaratorContext *abstractDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TheTypeIdContext* theTypeId();

  class  AbstractDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    AbstractDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointerAbstractDeclaratorContext *pointerAbstractDeclarator();
    ParametersAndQualifiersContext *parametersAndQualifiers();
    TrailingReturnTypeContext *trailingReturnType();
    NoPointerAbstractDeclaratorContext *noPointerAbstractDeclarator();
    AbstractPackDeclaratorContext *abstractPackDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AbstractDeclaratorContext* abstractDeclarator();

  class  PointerAbstractDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    PointerAbstractDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NoPointerAbstractDeclaratorContext *noPointerAbstractDeclarator();
    std::vector<PointerOperatorContext *> pointerOperator();
    PointerOperatorContext* pointerOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PointerAbstractDeclaratorContext* pointerAbstractDeclarator();

  class  NoPointerAbstractDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    NoPointerAbstractDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParametersAndQualifiersContext *parametersAndQualifiers();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    std::vector<ConstantExpressionContext *> constantExpression();
    ConstantExpressionContext* constantExpression(size_t i);
    antlr4::tree::TerminalNode *LeftParen();
    PointerAbstractDeclaratorContext *pointerAbstractDeclarator();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<NoPointerAbstractDeclaratorContext *> noPointerAbstractDeclarator();
    NoPointerAbstractDeclaratorContext* noPointerAbstractDeclarator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoPointerAbstractDeclaratorContext* noPointerAbstractDeclarator();
  NoPointerAbstractDeclaratorContext* noPointerAbstractDeclarator(int precedence);
  class  AbstractPackDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    AbstractPackDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NoPointerAbstractPackDeclaratorContext *noPointerAbstractPackDeclarator();
    std::vector<PointerOperatorContext *> pointerOperator();
    PointerOperatorContext* pointerOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AbstractPackDeclaratorContext* abstractPackDeclarator();

  class  NoPointerAbstractPackDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    NoPointerAbstractPackDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ellipsis();
    NoPointerAbstractPackDeclaratorContext *noPointerAbstractPackDeclarator();
    ParametersAndQualifiersContext *parametersAndQualifiers();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    ConstantExpressionContext *constantExpression();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoPointerAbstractPackDeclaratorContext* noPointerAbstractPackDeclarator();
  NoPointerAbstractPackDeclaratorContext* noPointerAbstractPackDeclarator(int precedence);
  class  ParameterDeclarationClauseContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParameterDeclarationListContext *parameterDeclarationList();
    antlr4::tree::TerminalNode *Ellipsis();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterDeclarationClauseContext* parameterDeclarationClause();

  class  ParameterDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterDeclarationContext *> parameterDeclaration();
    ParameterDeclarationContext* parameterDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterDeclarationListContext* parameterDeclarationList();

  class  ParameterDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclSpecifierSeqContext *declSpecifierSeq();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Assign();
    InitializerClauseContext *initializerClause();
    AbstractDeclaratorContext *abstractDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterDeclarationContext* parameterDeclaration();

  class  ReenterableDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ReenterableDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ReenterableHeadContext *reenterableHead();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReenterableDefinitionContext* reenterableDefinition();

  class  ReenterableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ReenterableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ReenterableHeadContext *reenterableHead();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReenterableDeclarationContext* reenterableDeclaration();

  class  ReenterableHeadContext : public antlr4::ParserRuleContext {
  public:
    ReenterableHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Reenterable();
    Reent_chain_headerContext *reent_chain_header();
    antlr4::tree::TerminalNode *LeftBracket();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Static();
    std::vector<Reent_chain_predicateContext *> reent_chain_predicate();
    Reent_chain_predicateContext* reent_chain_predicate(size_t i);
    antlr4::tree::TerminalNode *Local();
    antlr4::tree::TerminalNode *Global();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReenterableHeadContext* reenterableHead();

  class  Reent_chain_headerContext : public antlr4::ParserRuleContext {
  public:
    Reent_chain_headerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratoridContext *declaratorid();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    DeclSpecifierSeqContext *declSpecifierSeq();
    Reent_chain_paramsContext *reent_chain_params();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_chain_headerContext* reent_chain_header();

  class  Reent_chain_paramsContext : public antlr4::ParserRuleContext {
  public:
    Reent_chain_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Reent_chain_paramContext *> reent_chain_param();
    Reent_chain_paramContext* reent_chain_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_chain_paramsContext* reent_chain_params();

  class  Reent_chain_paramContext : public antlr4::ParserRuleContext {
  public:
    Reent_chain_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    Reent_recursive_typeContext *reent_recursive_type();
    Reent_reductionContext *reent_reduction();
    Reent_gpu_globalContext *reent_gpu_global();
    Reent_gpu_localContext *reent_gpu_local();
    DeclSpecifierSeqContext *declSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_chain_paramContext* reent_chain_param();

  class  Reent_recursive_typeContext : public antlr4::ParserRuleContext {
  public:
    Reent_recursive_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *LeftParen();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_recursive_typeContext* reent_recursive_type();

  class  Reent_reductionContext : public antlr4::ParserRuleContext {
  public:
    Reent_reductionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Reduction();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    Reduction_symbolContext *reduction_symbol();
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_reductionContext* reent_reduction();

  class  Reent_gpu_globalContext : public antlr4::ParserRuleContext {
  public:
    Reent_gpu_globalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GpuGlobal();
    antlr4::tree::TerminalNode *LeftParen();
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_gpu_globalContext* reent_gpu_global();

  class  Reent_gpu_localContext : public antlr4::ParserRuleContext {
  public:
    Reent_gpu_localContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GpuLocal();
    antlr4::tree::TerminalNode *LeftParen();
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_gpu_localContext* reent_gpu_local();

  class  Reduction_symbolContext : public antlr4::ParserRuleContext {
  public:
    Reduction_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Caret();
    antlr4::tree::TerminalNode *AndAnd();
    antlr4::tree::TerminalNode *OrOr();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *Or();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reduction_symbolContext* reduction_symbol();

  class  Reent_chain_predicateContext : public antlr4::ParserRuleContext {
  public:
    Reent_chain_predicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reent_predicate_setContext *reent_predicate_set();
    Reent_predicate_resetContext *reent_predicate_reset();
    Reent_predicate_dependsContext *reent_predicate_depends();
    Reent_predicate_ifContext *reent_predicate_if();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_chain_predicateContext* reent_chain_predicate();

  class  Reent_predicate_setContext : public antlr4::ParserRuleContext {
  public:
    Reent_predicate_setContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Set();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_predicate_setContext* reent_predicate_set();

  class  Reent_predicate_resetContext : public antlr4::ParserRuleContext {
  public:
    Reent_predicate_resetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Reset();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_predicate_resetContext* reent_predicate_reset();

  class  Reent_predicate_dependsContext : public antlr4::ParserRuleContext {
  public:
    Reent_predicate_dependsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Depends();
    antlr4::tree::TerminalNode *LeftParen();
    Reent_dependentsContext *reent_dependents();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_predicate_dependsContext* reent_predicate_depends();

  class  Reent_predicate_ifContext : public antlr4::ParserRuleContext {
  public:
    Reent_predicate_ifContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();
    Reent_enumeratorContext *reent_enumerator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_predicate_ifContext* reent_predicate_if();

  class  Reent_dependentsContext : public antlr4::ParserRuleContext {
  public:
    Reent_dependentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reent_enumeratorContext *reent_enumerator();
    std::vector<Reent_single_dependentContext *> reent_single_dependent();
    Reent_single_dependentContext* reent_single_dependent(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_dependentsContext* reent_dependents();

  class  Reent_enumeratorContext : public antlr4::ParserRuleContext {
  public:
    Reent_enumeratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    Loop_statement_headerContext *loop_statement_header();
    antlr4::tree::TerminalNode *RightBracket();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_enumeratorContext* reent_enumerator();

  class  Loop_statement_headerContext : public antlr4::ParserRuleContext {
  public:
    Loop_statement_headerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *While();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContext *condition();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *For();
    ForInitStatementContext *forInitStatement();
    antlr4::tree::TerminalNode *Semi();
    ForRangeDeclarationContext *forRangeDeclaration();
    antlr4::tree::TerminalNode *Colon();
    ForRangeInitializerContext *forRangeInitializer();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Loop_statement_headerContext* loop_statement_header();

  class  Reent_single_dependentContext : public antlr4::ParserRuleContext {
  public:
    Reent_single_dependentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    CastExpressionContext *castExpression();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Arrow();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reent_single_dependentContext* reent_single_dependent();

  class  Chain_interfaceContext : public antlr4::ParserRuleContext {
  public:
    Chain_interfaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    Reent_chain_paramsContext *reent_chain_params();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chain_interfaceContext* chain_interface();

  class  ChainDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ChainDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChainHeadContext *chainHead();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChainDefinitionContext* chainDefinition();

  class  ChainDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ChainDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChainHeadContext *chainHead();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChainDeclarationContext* chainDeclaration();

  class  ChainHeadContext : public antlr4::ParserRuleContext {
  public:
    ChainHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Chain();
    Reent_chain_headerContext *reent_chain_header();
    antlr4::tree::TerminalNode *LeftBracket();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightBracket();
    Chain_interfaceContext *chain_interface();
    std::vector<Reent_chain_predicateContext *> reent_chain_predicate();
    Reent_chain_predicateContext* reent_chain_predicate(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChainHeadContext* chainHead();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionBodyContext *functionBody();
    Special_method_nameContext *special_method_name();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    DeclaratorContext *declarator();
    ParameterDeclarationClauseContext *parameterDeclarationClause();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    DeclSpecifierSeqContext *declSpecifierSeq();
    VirtualSpecifierSeqContext *virtualSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  Special_method_nameContext : public antlr4::ParserRuleContext {
  public:
    Special_method_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnyIdentifierContext *> anyIdentifier();
    AnyIdentifierContext* anyIdentifier(size_t i);
    antlr4::tree::TerminalNode *Doublecolon();
    antlr4::tree::TerminalNode *Tilde();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Special_method_nameContext* special_method_name();

  class  FunctionBodyContext : public antlr4::ParserRuleContext {
  public:
    FunctionBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CompoundStatementContext *compoundStatement();
    ConstructorInitializerContext *constructorInitializer();
    FunctionTryBlockContext *functionTryBlock();
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Default();
    antlr4::tree::TerminalNode *Delete();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionBodyContext* functionBody();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BraceOrEqualInitializerContext *braceOrEqualInitializer();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitializerContext* initializer();

  class  BraceOrEqualInitializerContext : public antlr4::ParserRuleContext {
  public:
    BraceOrEqualInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Assign();
    InitializerClauseContext *initializerClause();
    BracedInitListContext *bracedInitList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BraceOrEqualInitializerContext* braceOrEqualInitializer();

  class  InitializerClauseContext : public antlr4::ParserRuleContext {
  public:
    InitializerClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();
    BracedInitListContext *bracedInitList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitializerClauseContext* initializerClause();

  class  InitializerListContext : public antlr4::ParserRuleContext {
  public:
    InitializerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitializerClauseContext *> initializerClause();
    InitializerClauseContext* initializerClause(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Ellipsis();
    antlr4::tree::TerminalNode* Ellipsis(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitializerListContext* initializerList();

  class  BracedInitListContext : public antlr4::ParserRuleContext {
  public:
    BracedInitListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    InitializerListContext *initializerList();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BracedInitListContext* bracedInitList();

  class  ClassNameContext : public antlr4::ParserRuleContext {
  public:
    ClassNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleTemplateIdContext *simpleTemplateId();
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassNameContext* className();

  class  ClassSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ClassSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassHeadContext *classHead();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    MemberSpecificationContext *memberSpecification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassSpecifierContext* classSpecifier();

  class  ClassHeadContext : public antlr4::ParserRuleContext {
  public:
    ClassHeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassKeyContext *classKey();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    ClassHeadNameContext *classHeadName();
    BaseClauseContext *baseClause();
    ClassVirtSpecifierContext *classVirtSpecifier();
    antlr4::tree::TerminalNode *Union();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassHeadContext* classHead();

  class  ClassHeadNameContext : public antlr4::ParserRuleContext {
  public:
    ClassHeadNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassNameContext *className();
    NestedNameSpecifierContext *nestedNameSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassHeadNameContext* classHeadName();

  class  ClassVirtSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ClassVirtSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Final();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassVirtSpecifierContext* classVirtSpecifier();

  class  ClassKeyContext : public antlr4::ParserRuleContext {
  public:
    ClassKeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Class();
    antlr4::tree::TerminalNode *Struct();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassKeyContext* classKey();

  class  MemberSpecificationContext : public antlr4::ParserRuleContext {
  public:
    MemberSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MarkedmemberdeclarationContext *> markedmemberdeclaration();
    MarkedmemberdeclarationContext* markedmemberdeclaration(size_t i);
    std::vector<MemberdeclarationContext *> memberdeclaration();
    MemberdeclarationContext* memberdeclaration(size_t i);
    std::vector<AccessSpecifierContext *> accessSpecifier();
    AccessSpecifierContext* accessSpecifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Colon();
    antlr4::tree::TerminalNode* Colon(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemberSpecificationContext* memberSpecification();

  class  MarkedmemberdeclarationContext : public antlr4::ParserRuleContext {
  public:
    MarkedmemberdeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *MarkPreCondition();
    antlr4::tree::TerminalNode *MarkState();
    antlr4::tree::TerminalNode *LeftParen();
    std::vector<PrimaryExpressionContext *> primaryExpression();
    PrimaryExpressionContext* primaryExpression(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *RightParen();
    DeclSpecifierSeqContext *declSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MarkedmemberdeclarationContext* markedmemberdeclaration();

  class  MemberdeclarationContext : public antlr4::ParserRuleContext {
  public:
    MemberdeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    DeclSpecifierSeqContext *declSpecifierSeq();
    MemberDeclaratorListContext *memberDeclaratorList();
    FunctionDefinitionContext *functionDefinition();
    UsingDeclarationContext *usingDeclaration();
    StaticAssertDeclarationContext *staticAssertDeclaration();
    TemplateDeclarationContext *templateDeclaration();
    AliasDeclarationContext *aliasDeclaration();
    EmptyDeclarationContext *emptyDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemberdeclarationContext* memberdeclaration();

  class  MemberDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    MemberDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MemberDeclaratorContext *> memberDeclarator();
    MemberDeclaratorContext* memberDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemberDeclaratorListContext* memberDeclaratorList();

  class  MemberDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    MemberDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    VirtualSpecifierSeqContext *virtualSpecifierSeq();
    PureSpecifierContext *pureSpecifier();
    BraceOrEqualInitializerContext *braceOrEqualInitializer();
    antlr4::tree::TerminalNode *Colon();
    ConstantExpressionContext *constantExpression();
    AnyIdentifierContext *anyIdentifier();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemberDeclaratorContext* memberDeclarator();

  class  VirtualSpecifierSeqContext : public antlr4::ParserRuleContext {
  public:
    VirtualSpecifierSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VirtualSpecifierContext *> virtualSpecifier();
    VirtualSpecifierContext* virtualSpecifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VirtualSpecifierSeqContext* virtualSpecifierSeq();

  class  VirtualSpecifierContext : public antlr4::ParserRuleContext {
  public:
    VirtualSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Override();
    antlr4::tree::TerminalNode *Final();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VirtualSpecifierContext* virtualSpecifier();

  class  PureSpecifierContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *val = nullptr;
    PureSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *OctalLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PureSpecifierContext* pureSpecifier();

  class  BaseClauseContext : public antlr4::ParserRuleContext {
  public:
    BaseClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Colon();
    BaseSpecifierListContext *baseSpecifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BaseClauseContext* baseClause();

  class  BaseSpecifierListContext : public antlr4::ParserRuleContext {
  public:
    BaseSpecifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BaseSpecifierContext *> baseSpecifier();
    BaseSpecifierContext* baseSpecifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Ellipsis();
    antlr4::tree::TerminalNode* Ellipsis(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BaseSpecifierListContext* baseSpecifierList();

  class  BaseSpecifierContext : public antlr4::ParserRuleContext {
  public:
    BaseSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BaseTypeSpecifierContext *baseTypeSpecifier();
    antlr4::tree::TerminalNode *Virtual();
    AccessSpecifierContext *accessSpecifier();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BaseSpecifierContext* baseSpecifier();

  class  ClassOrDeclTypeContext : public antlr4::ParserRuleContext {
  public:
    ClassOrDeclTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassNameContext *className();
    NestedNameSpecifierContext *nestedNameSpecifier();
    DecltypeSpecifierContext *decltypeSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassOrDeclTypeContext* classOrDeclType();

  class  BaseTypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    BaseTypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassOrDeclTypeContext *classOrDeclType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BaseTypeSpecifierContext* baseTypeSpecifier();

  class  AccessSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AccessSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Private();
    antlr4::tree::TerminalNode *Protected();
    antlr4::tree::TerminalNode *Public();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AccessSpecifierContext* accessSpecifier();

  class  ConversionFunctionIdContext : public antlr4::ParserRuleContext {
  public:
    ConversionFunctionIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Operator();
    ConversionTypeIdContext *conversionTypeId();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConversionFunctionIdContext* conversionFunctionId();

  class  ConversionTypeIdContext : public antlr4::ParserRuleContext {
  public:
    ConversionTypeIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierSeqContext *typeSpecifierSeq();
    ConversionDeclaratorContext *conversionDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConversionTypeIdContext* conversionTypeId();

  class  ConversionDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    ConversionDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointerOperatorContext *pointerOperator();
    ConversionDeclaratorContext *conversionDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConversionDeclaratorContext* conversionDeclarator();

  class  ConstructorInitializerContext : public antlr4::ParserRuleContext {
  public:
    ConstructorInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Colon();
    MemInitializerListContext *memInitializerList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstructorInitializerContext* constructorInitializer();

  class  MemInitializerListContext : public antlr4::ParserRuleContext {
  public:
    MemInitializerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MemInitializerContext *> memInitializer();
    MemInitializerContext* memInitializer(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Ellipsis();
    antlr4::tree::TerminalNode* Ellipsis(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemInitializerListContext* memInitializerList();

  class  MemInitializerContext : public antlr4::ParserRuleContext {
  public:
    MemInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MeminitializeridContext *meminitializerid();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    BracedInitListContext *bracedInitList();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemInitializerContext* memInitializer();

  class  MeminitializeridContext : public antlr4::ParserRuleContext {
  public:
    MeminitializeridContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassOrDeclTypeContext *classOrDeclType();
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MeminitializeridContext* meminitializerid();

  class  OperatorFunctionIdContext : public antlr4::ParserRuleContext {
  public:
    OperatorFunctionIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Operator();
    TheOperatorContext *theOperator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OperatorFunctionIdContext* operatorFunctionId();

  class  LiteralOperatorIdContext : public antlr4::ParserRuleContext {
  public:
    LiteralOperatorIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Operator();
    antlr4::tree::TerminalNode *StringLiteral();
    AnyIdentifierContext *anyIdentifier();
    antlr4::tree::TerminalNode *UserDefinedStringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LiteralOperatorIdContext* literalOperatorId();

  class  TemplateDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TemplateDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Template();
    antlr4::tree::TerminalNode *Less();
    TemplateparameterListContext *templateparameterList();
    antlr4::tree::TerminalNode *Greater();
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateDeclarationContext* templateDeclaration();

  class  TemplateparameterListContext : public antlr4::ParserRuleContext {
  public:
    TemplateparameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateParameterContext *> templateParameter();
    TemplateParameterContext* templateParameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateparameterListContext* templateparameterList();

  class  TemplateParameterContext : public antlr4::ParserRuleContext {
  public:
    TemplateParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeParameterContext *typeParameter();
    ParameterDeclarationContext *parameterDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateParameterContext* templateParameter();

  class  TypeParameterContext : public antlr4::ParserRuleContext {
  public:
    TypeParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Class();
    antlr4::tree::TerminalNode *Typename_();
    antlr4::tree::TerminalNode *Assign();
    TheTypeIdContext *theTypeId();
    antlr4::tree::TerminalNode *Template();
    antlr4::tree::TerminalNode *Less();
    TemplateparameterListContext *templateparameterList();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *Ellipsis();
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeParameterContext* typeParameter();

  class  SimpleTemplateIdContext : public antlr4::ParserRuleContext {
  public:
    ReentParser::TemplateNameContext *id = nullptr;
    SimpleTemplateIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    TemplateNameContext *templateName();
    TemplateArgumentListContext *templateArgumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleTemplateIdContext* simpleTemplateId();

  class  TemplateIdContext : public antlr4::ParserRuleContext {
  public:
    TemplateIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleTemplateIdContext *simpleTemplateId();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    OperatorFunctionIdContext *operatorFunctionId();
    LiteralOperatorIdContext *literalOperatorId();
    TemplateArgumentListContext *templateArgumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateIdContext* templateId();

  class  TemplateNameContext : public antlr4::ParserRuleContext {
  public:
    TemplateNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnyIdentifierContext *anyIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateNameContext* templateName();

  class  TemplateArgumentListContext : public antlr4::ParserRuleContext {
  public:
    TemplateArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateArgumentContext *> templateArgument();
    TemplateArgumentContext* templateArgument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Ellipsis();
    antlr4::tree::TerminalNode* Ellipsis(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateArgumentListContext* templateArgumentList();

  class  TemplateArgumentContext : public antlr4::ParserRuleContext {
  public:
    TemplateArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TheTypeIdContext *theTypeId();
    ConstantExpressionContext *constantExpression();
    IdExpressionContext *idExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateArgumentContext* templateArgument();

  class  TypeNameSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TypeNameSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Typename_();
    NestedNameSpecifierContext *nestedNameSpecifier();
    AnyIdentifierContext *anyIdentifier();
    SimpleTemplateIdContext *simpleTemplateId();
    antlr4::tree::TerminalNode *Template();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeNameSpecifierContext* typeNameSpecifier();

  class  ExplicitInstantiationContext : public antlr4::ParserRuleContext {
  public:
    ExplicitInstantiationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Template();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Extern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExplicitInstantiationContext* explicitInstantiation();

  class  ExplicitSpecializationContext : public antlr4::ParserRuleContext {
  public:
    ExplicitSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Template();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExplicitSpecializationContext* explicitSpecialization();

  class  TryBlockContext : public antlr4::ParserRuleContext {
  public:
    TryBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Try();
    CompoundStatementContext *compoundStatement();
    HandlerSeqContext *handlerSeq();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TryBlockContext* tryBlock();

  class  FunctionTryBlockContext : public antlr4::ParserRuleContext {
  public:
    FunctionTryBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Try();
    CompoundStatementContext *compoundStatement();
    HandlerSeqContext *handlerSeq();
    ConstructorInitializerContext *constructorInitializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionTryBlockContext* functionTryBlock();

  class  HandlerSeqContext : public antlr4::ParserRuleContext {
  public:
    HandlerSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<HandlerContext *> handler();
    HandlerContext* handler(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HandlerSeqContext* handlerSeq();

  class  HandlerContext : public antlr4::ParserRuleContext {
  public:
    HandlerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Catch();
    antlr4::tree::TerminalNode *LeftParen();
    ExceptionDeclarationContext *exceptionDeclaration();
    antlr4::tree::TerminalNode *RightParen();
    CompoundStatementContext *compoundStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HandlerContext* handler();

  class  ExceptionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ExceptionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierSeqContext *typeSpecifierSeq();
    AttributeSpecifierSeqContext *attributeSpecifierSeq();
    DeclaratorContext *declarator();
    AbstractDeclaratorContext *abstractDeclarator();
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExceptionDeclarationContext* exceptionDeclaration();

  class  ThrowExpressionContext : public antlr4::ParserRuleContext {
  public:
    ThrowExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ThrowExpressionContext* throwExpression();

  class  ExceptionSpecificationContext : public antlr4::ParserRuleContext {
  public:
    ExceptionSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DynamicExceptionSpecificationContext *dynamicExceptionSpecification();
    NoeExceptSpecificationContext *noeExceptSpecification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExceptionSpecificationContext* exceptionSpecification();

  class  DynamicExceptionSpecificationContext : public antlr4::ParserRuleContext {
  public:
    DynamicExceptionSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    TypeIdListContext *typeIdList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DynamicExceptionSpecificationContext* dynamicExceptionSpecification();

  class  TypeIdListContext : public antlr4::ParserRuleContext {
  public:
    TypeIdListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TheTypeIdContext *> theTypeId();
    TheTypeIdContext* theTypeId(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Ellipsis();
    antlr4::tree::TerminalNode* Ellipsis(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeIdListContext* typeIdList();

  class  NoeExceptSpecificationContext : public antlr4::ParserRuleContext {
  public:
    NoeExceptSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Noexcept();
    antlr4::tree::TerminalNode *LeftParen();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NoeExceptSpecificationContext* noeExceptSpecification();

  class  Plan_pragmaContext : public antlr4::ParserRuleContext {
  public:
    Plan_pragmaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PlanPragma();
    Plan_directiveContext *plan_directive();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_pragmaContext* plan_pragma();

  class  Plan_directiveContext : public antlr4::ParserRuleContext {
  public:
    Plan_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Plan_dir_vectorizedContext *plan_dir_vectorized();
    Plan_dir_clusteredContext *plan_dir_clustered();
    Plan_commonContext *plan_common();
    Plan_gpuContext *plan_gpu();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_directiveContext* plan_directive();

  class  Plan_dir_vectorizedContext : public antlr4::ParserRuleContext {
  public:
    Plan_dir_vectorizedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Vectorized();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_dir_vectorizedContext* plan_dir_vectorized();

  class  Plan_dir_clusteredContext : public antlr4::ParserRuleContext {
  public:
    Plan_dir_clusteredContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Clustered();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_dir_clusteredContext* plan_dir_clustered();

  class  Plan_commonContext : public antlr4::ParserRuleContext {
  public:
    Plan_commonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Common();
    antlr4::tree::TerminalNode *Begin();
    antlr4::tree::TerminalNode *End();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_commonContext* plan_common();

  class  Plan_gpuContext : public antlr4::ParserRuleContext {
  public:
    Plan_gpuContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Gpu();
    antlr4::tree::TerminalNode *Begin();
    antlr4::tree::TerminalNode *End();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Plan_gpuContext* plan_gpu();

  class  TheOperatorContext : public antlr4::ParserRuleContext {
  public:
    TheOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *New();
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Delete();
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Div();
    antlr4::tree::TerminalNode *Mod();
    antlr4::tree::TerminalNode *Caret();
    antlr4::tree::TerminalNode *And();
    antlr4::tree::TerminalNode *Or();
    antlr4::tree::TerminalNode *Tilde();
    antlr4::tree::TerminalNode *Not();
    antlr4::tree::TerminalNode *Assign();
    std::vector<antlr4::tree::TerminalNode *> Greater();
    antlr4::tree::TerminalNode* Greater(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Less();
    antlr4::tree::TerminalNode* Less(size_t i);
    antlr4::tree::TerminalNode *GreaterEqual();
    antlr4::tree::TerminalNode *PlusAssign();
    antlr4::tree::TerminalNode *MinusAssign();
    antlr4::tree::TerminalNode *StarAssign();
    antlr4::tree::TerminalNode *ModAssign();
    antlr4::tree::TerminalNode *XorAssign();
    antlr4::tree::TerminalNode *AndAssign();
    antlr4::tree::TerminalNode *OrAssign();
    antlr4::tree::TerminalNode *RightShiftAssign();
    antlr4::tree::TerminalNode *LeftShiftAssign();
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *AndAnd();
    antlr4::tree::TerminalNode *OrOr();
    antlr4::tree::TerminalNode *PlusPlus();
    antlr4::tree::TerminalNode *MinusMinus();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *ArrowStar();
    antlr4::tree::TerminalNode *Arrow();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TheOperatorContext* theOperator();

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
  bool reent_funs_idSempred(Reent_funs_idContext *_localctx, size_t predicateIndex);
  bool chain_funs_idSempred(Chain_funs_idContext *_localctx, size_t predicateIndex);
  bool nestedNameSpecifierSempred(NestedNameSpecifierContext *_localctx, size_t predicateIndex);
  bool postfixExpressionSempred(PostfixExpressionContext *_localctx, size_t predicateIndex);
  bool noPointerNewDeclaratorSempred(NoPointerNewDeclaratorContext *_localctx, size_t predicateIndex);
  bool reent_statementSempred(Reent_statementContext *_localctx, size_t predicateIndex);
  bool chain_statementSempred(Chain_statementContext *_localctx, size_t predicateIndex);
  bool atomic_blockSempred(Atomic_blockContext *_localctx, size_t predicateIndex);
  bool vector_chain_descriptorSempred(Vector_chain_descriptorContext *_localctx, size_t predicateIndex);
  bool noPointerDeclaratorSempred(NoPointerDeclaratorContext *_localctx, size_t predicateIndex);
  bool noPointerAbstractDeclaratorSempred(NoPointerAbstractDeclaratorContext *_localctx, size_t predicateIndex);
  bool noPointerAbstractPackDeclaratorSempred(NoPointerAbstractPackDeclaratorContext *_localctx, size_t predicateIndex);

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

