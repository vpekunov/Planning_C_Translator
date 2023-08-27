/* Modified by V.V.Pekunov -- extended to Planning C language */
/* Based on CPP14Parser.g4 (https://github.com/antlr/grammars-v4) */

/*******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Camilo Sanchez (Camiloasc1) 2020 Martin Mirchev (Marti2203)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ****************************************************************************
 */
parser grammar ReentParser;
options {
	tokenVocab = ReentLexer;
	language = Cpp;
}
/*Basic concepts*/

@parser::header {
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
}

@members {
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
}

translationUnit: declarationseq? EOF {
		if (gpu_block_opened)
			throw FailedPredicateException(this, "'#pragma plan gpu end' expected");
		if (common_block_opened)
			throw FailedPredicateException(this, "'#pragma plan common end' expected");
	};
/*Expressions*/

anyIdentifier:
	Id | In | Out | Set | Reset | Depends | Plan | Common | Gpu | Begin | End
	| Local | Global | MarkState | MarkPreCondition | Vectorized | Clustered | Identifier;

primaryExpression:
	literal+
	| This
	| LeftParen expression RightParen
	| reent_funs_id
	| chain_funs_id
	| idExpression
	| lambdaExpression;

idExpression: qualifiedId | unqualifiedId;

reent_funs_id:
	{(in_reenterable || in_chain)}?
	(Plan_first | Plan_last | Plan_stop
	 | Clear_plan | Plan_get_first | Plan_get_last
	 | Plan_group_first | Plan_group_last | Plan_group_parallelize | Plan_group_vectorize
	 | Plan_group_atomize | Plan_group_soft_atomize);

chain_funs_id:
	{in_chain}? (Throw_first | Throw_last);

unqualifiedId:
	templateId
	| anyIdentifier
	| operatorFunctionId
	| conversionFunctionId
	| literalOperatorId
	| Tilde (className | decltypeSpecifier);

qualifiedId: nestedNameSpecifier Template? unqualifiedId;

nestedNameSpecifier:
	(theTypeName | namespaceName | decltypeSpecifier)? Doublecolon
	| nestedNameSpecifier (
		anyIdentifier
		| Template? simpleTemplateId
	) Doublecolon;
lambdaExpression:
	lambdaIntroducer lambdaDeclarator? compoundStatement;

lambdaIntroducer: LeftBracket lambdaCapture? RightBracket;

lambdaCapture:
	captureList
	| captureDefault (Comma captureList)?;

captureDefault: And | Assign;

captureList: capture (Comma capture)* Ellipsis?;

capture: simpleCapture | initcapture;

simpleCapture: And? anyIdentifier | This;

initcapture: And? anyIdentifier initializer;

lambdaDeclarator:
	LeftParen parameterDeclarationClause? RightParen Mutable? exceptionSpecification?
		attributeSpecifierSeq? trailingReturnType?;

objCilkSpawnArg:
	Assign idExpression
	| assignmentExpression;

objCilkSpawnParams:
	LeftParen assignmentExpression Comma assignmentExpression RightParen;

objCilkDesignator:
	primaryExpression
	| objCilkDesignator LeftBracket (expression | bracedInitList) RightBracket;

objCilk:
	objCilkDesignator
	(Dot | Arrow);

postfixExpression:
	primaryExpression
	| postfixExpression LeftBracket (expression | bracedInitList) RightBracket
	| postfixExpression LeftParen expressionList? RightParen
	| (simpleTypeSpecifier | typeNameSpecifier) (
		bracedInitList
	)
	| theTypeId
	| planned=postfixExpression (Dot | Arrow) (
		Template? ident=idExpression {
			if ($planned.text == "__planned__")
				if (!in_chain && !in_reenterable)
					throw FailedPredicateException(this, "__planned__[.|->]Id not in Chain/Reenterable Procedure");
				else if (!_in_gpu_local)
					throw FailedPredicateException(this, "__planned__[.|->]Id not inside _local(...) clause in current Chain/Reenterable header");
				else
					_reent_planned_refs.insert($ident.text);
		}
		| pseudoDestructorName
	)
	| postfixExpression (PlusPlus | MinusMinus)
	| (
		Dynamic_cast
		| Static_cast
		| Reinterpret_cast
		| Const_cast
	) Less theTypeId Greater LeftParen expression RightParen
	| typeIdOfTheTypeId LeftParen (expression | theTypeId) RightParen;
/*
 add a middle layer to eliminate duplicated function declarations
 */

typeIdOfTheTypeId: Typeid_;

expressionList: initializerList;

pseudoDestructorName:
	nestedNameSpecifier? (theTypeName Doublecolon)? Tilde theTypeName
	| nestedNameSpecifier Template simpleTemplateId Doublecolon Tilde theTypeName
	| Tilde decltypeSpecifier;

unaryExpression:
	postfixExpression
	| Sizeof (
		LeftParen theTypeId RightParen
		| Ellipsis LeftParen anyIdentifier RightParen
	)
	| (PlusPlus | MinusMinus | Sizeof) unaryExpression
	| unaryOperator castExpression
	| Alignof LeftParen theTypeId RightParen
	| noExceptExpression
	| newExpression
	| deleteExpression;

unaryOperator: Or | Star | And | Plus | Tilde | Minus | Not;

newExpression:
	Doublecolon? New newPlacement? (
		newTypeId
		| (LeftParen theTypeId RightParen)
	) newInitializer?;

newPlacement: LeftParen expressionList RightParen;

newTypeId: typeSpecifierSeq newDeclarator?;

newDeclarator:
	pointerOperator newDeclarator?
	| noPointerNewDeclarator;

noPointerNewDeclarator:
	LeftBracket expression RightBracket attributeSpecifierSeq?
	| noPointerNewDeclarator LeftBracket constantExpression RightBracket attributeSpecifierSeq?;

newInitializer:
	LeftParen expressionList? RightParen
	| bracedInitList;

deleteExpression:
	Doublecolon? Delete (LeftBracket RightBracket)? castExpression;

noExceptExpression: Noexcept LeftParen expression RightParen;

castExpression:
	unaryExpression
	| LeftParen theTypeId RightParen castExpression;

pointerMemberExpression:
	castExpression ((DotStar | ArrowStar) castExpression)*;

multiplicativeExpression:
	pointerMemberExpression (
		(Star | Div | Mod) pointerMemberExpression
	)*;

additiveExpression:
	multiplicativeExpression (
		(Plus | Minus) multiplicativeExpression
	)*;

shiftExpression:
	additiveExpression (shiftOperator additiveExpression)*;

shiftOperator: Greater Greater | Less Less;

relationalExpression:
	shiftExpression (
		(Less | Greater | LessEqual | GreaterEqual) shiftExpression
	)*;

equalityExpression:
	relationalExpression (
		(Equal | NotEqual) relationalExpression
	)*;

andExpression: equalityExpression (And equalityExpression)*;

exclusiveOrExpression: andExpression (Caret andExpression)*;

inclusiveOrExpression:
	exclusiveOrExpression (Or exclusiveOrExpression)*;

logicalAndExpression:
	inclusiveOrExpression (AndAnd inclusiveOrExpression)*;

logicalOrExpression:
	logicalAndExpression (OrOr logicalAndExpression)*;

conditionalExpression:
	logicalOrExpression (
		Question expression Colon assignmentExpression
	)?;

assignmentExpression:
	objCilk*? Cilk_spawn objCilkSpawnParams?
		objCilk*? idExpression
		LeftParen (objCilkSpawnArg (Comma objCilkSpawnArg)*)? RightParen
	| conditionalExpression
	| logicalOrExpression assignmentOperator initializerClause
	| throwExpression;

assignmentOperator:
	Assign
	| StarAssign
	| DivAssign
	| ModAssign
	| PlusAssign
	| MinusAssign
	| RightShiftAssign
	| LeftShiftAssign
	| AndAssign
	| XorAssign
	| OrAssign;

expression: assignmentExpression (Comma assignmentExpression)*;

constantExpression: conditionalExpression;
/*Statements*/

statement:
	labeledStatement
	| cilk_sync
	| start_chain
	| start_topology
	| fill_into_plan
	| fill_from_plan
	| plan_critical
	| reent_statement
	| chain_statement
	| reent_special_call
	| atomic_block
	| soft_atomic_block
	| (Cilk_spawn | Cilk_spawn_) spawned_call_statement
	| qualified_call_statement
	| declarationStatement
	| attributeSpecifierSeq? (
		expressionStatement
		| compoundStatement
		| selectionStatement
		| iterationStatement
		| jumpStatement
		| tryBlock
	);

labeledStatement:
	attributeSpecifierSeq? (
		anyIdentifier
		| Case constantExpression
		| Default
	) Colon statement;

cilk_sync:
	objCilk*? Cilk_sync (LeftParen assignmentExpression? RightParen)? Semi
	| Cilk_sync_ Semi;

fill_into_plan:
	Star ident=Identifier
	Less Less LeftBracket
	{ if (reenterables.find($ident.text) == reenterables.end() || (reenterables[$ident.text] & static_flag) == 0)
		throw FailedPredicateException(this, "This action can be applied to Static Reenterable Procedure only");
	}
	reent_filler (Comma reent_filler)*
	RightBracket
	Semi;

fill_from_plan:
	Star ident=Identifier
	Greater Greater LeftBracket
	{ if (reenterables.find($ident.text) == reenterables.end() || (reenterables[$ident.text] & static_flag) == 0)
		throw FailedPredicateException(this, "This action can be applied to Static Reenterable Procedure only");
	}
	reent_reader (Comma reent_reader)*
	RightBracket
	Semi;

reent_filler:
	Underscore
	| reent_filler_array
	| expression;

reent_reader:
	Underscore
	| reent_filler_array
	| Identifier;

reent_filler_array:
	Identifier (LeftBracket RightBracket)+;

reent_statement:
	{(in_reenterable || in_chain)}?
	(plan_first | plan_last | plan_stop
	 | clear_plan | plan_get_first | plan_get_last
	 | plan_register | plan_registered_barrier
	 | plan_group_first | plan_group_last | plan_group_parallelize | plan_group_vectorize
	 | plan_group_atomize);

chain_statement:
	{in_chain}? (throw_first | throw_last);

atomic_block:
	{(!in_reenterable && !in_chain)}?
	Plan_atomize compoundStatement;

soft_atomic_block:
	Transaction_atomic LeftParen primaryExpression RightParen compoundStatement;

plan_first:
	Plan_first LeftParen planning_params RightParen Semi;

plan_get_first:
	Plan_get_first LeftParen expression RightParen Semi;

plan_last:
	Plan_last LeftParen planning_params RightParen Semi;

plan_get_last:
	Plan_get_last LeftParen expression RightParen Semi;

plan_register:
	Plan_register LeftParen anyIdentifier RightParen Semi;

plan_registered_barrier:
	Plan_registered_barrier LeftParen anyIdentifier RightParen Semi;

plan_critical:
	Plan_critical LeftParen anyIdentifier RightParen compoundStatement;

plan_stop:
	Plan_stop Semi;

clear_plan:
	Clear_plan Semi;

plan_group_first:
	Plan_group_first Semi;

plan_group_last:
	Plan_group_last Semi;

plan_group_parallelize:
	Plan_group_parallelize Semi;

plan_group_atomize:
	Plan_group_atomize Semi;

plan_group_soft_atomize:
	Plan_group_soft_atomize Semi;

plan_group_vectorize:
	Plan_group_vectorize {
		if (!allow_vectorized)
			throw FailedPredicateException(this, "'plan_group_vectorize' without '#pragma plan vectorized'");
	} LeftParen assignmentExpression RightParen Semi;

throw_first:
	Throw_first LeftParen planning_params RightParen Semi;

throw_last:
	Throw_last LeftParen planning_params RightParen Semi;

planning_params:
	assignmentExpression reent_parameter_cut? (Comma assignmentExpression reent_parameter_cut?)*;

reent_parameter_cut:
	Not;

reent_special_call:
	reent_continue_any_call
	| reent_compact_continue
	| reent_np_call;

reent_continue_any_call:
	Continue ident=anyIdentifier
	{ if (reenterables.find($ident.text) == reenterables.end() || (reenterables[$ident.text] & static_flag) == 0)
		throw FailedPredicateException(this, "Continue can be applied to Static Reenterable Procedure only");
	}
	LeftParen expression? RightParen (Div primaryExpression)? Semi;

reent_compact_continue:
	ident=anyIdentifier
	LeftParen LeftBracket
	{ if (reenterables.find($ident.text) == reenterables.end() || (reenterables[$ident.text] & static_flag) == 0)
		throw FailedPredicateException(this, "Continuing ([Call]) can be applied to Static Reenterable Procedure only");
	}
	expression?
	RightBracket RightParen (Div primaryExpression)? Semi;

reent_np_call:
	ident=anyIdentifier
	LeftParen expression? RightParen
	{ if (_input->LT(1)->getText() == "/" && chains.find($ident.text) == chains.end() && reenterables.find($ident.text) == reenterables.end())
		throw FailedPredicateException(this, "Clause '/NumberOfProcessors' can be applied to Chain/Reenterable Procedure only");
	}
	Div primaryExpression Semi;

start_chain:
	start_single_proc_chain | start_multi_proc_chain;

start_single_proc_chain:
	Plan_chain LeftParen primaryExpression Comma chain_descriptor RightParen Semi;

start_multi_proc_chain:
	{ if (_input->LT(1)->getText() == "clustered")
		if (!allow_clustered)
			throw FailedPredicateException(this, "clustered chain without previous '#pragma plan clustered'");
	}
	(Clustered LeftParen assignmentExpression RightParen)?
	Plan_parallel_chain LeftParen primaryExpression Comma chain_descriptor RightParen Semi;

chain_descriptor:
	vector_chain_descriptor
	| list_chain_descriptor;

vector_chain_descriptor:
	ident=primaryExpression { chains.find($ident.text) == chains.end() }?
	Comma chain_call;

list_chain_descriptor:
	chain_call ((Comma | Arrow) chain_call)*;

start_topology:
	{ if (_input->LT(1)->getText() == "clustered")
		if (!allow_clustered)
			throw FailedPredicateException(this, "clustered topology without previous '#pragma plan clustered'");
	}
	(Clustered LeftParen assignmentExpression RightParen)?
	Plan_topology LeftBrace
	topology_item+
	RightBrace
	(Div primaryExpression)? Semi;

topology_item:
	(topology_line
	 | topology_reverse)
	Semi;

topology_line:
	Plan_parallel_chain LeftParen
	topology_node ((Arrow | Comma) topology_node)*
	RightParen;

topology_reverse:
	Plan_parallel_reverse LeftParen
	topology_node (Arrow | Comma) topology_node
	RightParen;

topology_node:
	ident=Identifier
	(LeftBracket IntegerLiteral+ RightBracket)?
	{ if (chains.find($ident.text) == chains.end()) throw FailedPredicateException(this, "Chain procedure Identifier expected in topology"); }
	LeftParen expression? RightParen (Div primaryExpression)?;

chain_call:
	ident=Identifier
	{ if (chains.find($ident.text) == chains.end()) throw FailedPredicateException(this, "Chain procedure Identifier expected"); }
	LeftParen expression? RightParen (Div primaryExpression)?;

qualified_call_statement:
	qualifiedId LeftParen expression? RightParen Semi;

spawned_call_statement:
	idExpression LeftParen expression? RightParen Semi;

expressionStatement: expression? Semi;

compoundStatement: LeftBrace statementSeq? RightBrace;

statementSeq: statement+;

selectionStatement:
	If LeftParen condition RightParen statement (Else statement)?
	| Switch LeftParen condition RightParen statement;

condition:
	expression
	| attributeSpecifierSeq? declSpecifierSeq declarator (
		Assign initializerClause
		| bracedInitList
	);

iterationStatement:
	While LeftParen condition RightParen statement
	| Do statement While LeftParen expression RightParen Semi
	| (For | Cilk_for | Cilk_for_) LeftParen (
		forInitStatement condition? Semi expression?
		| forRangeDeclaration Colon forRangeInitializer
	) RightParen statement;

forInitStatement: expressionStatement | simpleDeclaration;

forRangeDeclaration:
	attributeSpecifierSeq? declSpecifierSeq declarator;

forRangeInitializer: expression | bracedInitList;

jumpStatement:
	(
		Break
		| Continue
		| Return (expression | bracedInitList)?
		| Goto anyIdentifier
	) Semi;

declarationStatement: blockDeclaration;
/*Declarations*/

declarationseq: declaration+;

declaration:
	plan_pragma
	| reenterableDeclaration
	| reenterableDefinition
	| chainDeclaration
	| chainDefinition
	| functionDefinition
	| blockDeclaration
	| templateDeclaration
	| explicitInstantiation
	| explicitSpecialization
	| linkageSpecification
	| namespaceDefinition
	| emptyDeclaration
	| attributeDeclaration;

blockDeclaration:
	simpleDeclaration
	| asmDefinition
	| namespaceAliasDefinition
	| usingDeclaration
	| usingDirective
	| staticAssertDeclaration
	| aliasDeclaration
	| opaqueEnumDeclaration;

aliasDeclaration:
	Using anyIdentifier attributeSpecifierSeq? Assign theTypeId Semi;

simpleDeclaration:
	(declSpecifierSeq initDeclaratorList?)? Semi
	| attributeSpecifierSeq declSpecifierSeq initDeclaratorList Semi;

staticAssertDeclaration:
	Static_assert LeftParen constantExpression Comma StringLiteral RightParen Semi;

emptyDeclaration: Semi;

attributeDeclaration: attributeSpecifierSeq Semi;

declSpecifier:
	Friend
	| Typedef
	| Markupdef
	| Constexpr
	| storageClassSpecifier
	| typeSpecifier
	| functionSpecifier;
	
declSpecifierSeq: declSpecifier+? attributeSpecifierSeq?;

reent_special_type:
	reent_funnel_type
	| reent_cfunnel_type
	| reent_cvar_type
	| reent_csem_type
	| reent_soft_transact_array
	| reent_soft_transact_var
	| reent_soft_transact_in
	| reent_soft_transact_out
	| reent_plan_type
	| reent_plan_item_type;

reent_funnel_type:
	Funnel LeftParen (In | Out) Comma simpleTypeSpecifier RightParen;

reent_cfunnel_type:
	Cfunnel {
		if (!allow_clustered)
			throw FailedPredicateException(this, "using cfunnel without previous '#pragma plan clustered'");
	}
	LeftParen (In | Out) Comma simpleTypeSpecifier RightParen;

reent_cvar_type:
	Cvar {
		if (!allow_clustered)
			throw FailedPredicateException(this, "using cvar without previous '#pragma plan clustered'");
	}
	LeftParen simpleTypeSpecifier RightParen;

reent_csem_type:
	Csem {
		if (!allow_clustered)
			throw FailedPredicateException(this, "using plan_csem_t without previous '#pragma plan clustered'");
	};

reent_soft_transact_array:
	Soft_transact_array
	LeftParen simpleTypeSpecifier RightParen;

reent_soft_transact_var:
	Soft_transact_var
	LeftParen simpleTypeSpecifier RightParen;

reent_soft_transact_in:
	Soft_transact_in
	LeftParen simpleTypeSpecifier RightParen;

reent_soft_transact_out:
	Soft_transact_out
	LeftParen simpleTypeSpecifier RightParen;

reent_plan_type:
	Plan_type LeftParen ident=Identifier
	{ std::map<std::string,int>::iterator it = reenterables.find($ident.text);
	  if (it == reenterables.end() || (it->second & static_flag) == 0)
		throw FailedPredicateException(this, "Static reenterable procedure's name expected");
	}
	RightParen;

reent_plan_item_type:
	Plan_item_type LeftParen ident=Identifier
	{ std::map<std::string,int>::iterator it = reenterables.find($ident.text);
	  if (it == reenterables.end() || (it->second & static_flag) == 0)
		throw FailedPredicateException(this, "Static reenterable procedure's name expected");
	}
	RightParen;

storageClassSpecifier:
	Register
	| Static
	| Thread_local
	| Extern
	| Mutable;

functionSpecifier: Inline | Virtual | Explicit;

typedefName: anyIdentifier;

typeSpecifier:
	reent_special_type
	| classSpecifier
	| trailingTypeSpecifier
	| enumSpecifier;

trailingTypeSpecifier:
	elaboratedTypeSpecifier
	| typeNameSpecifier
	| cvQualifier
	| simpleTypeSpecifier;

typeSpecifierSeq: typeSpecifier+ attributeSpecifierSeq?;

trailingTypeSpecifierSeq:
	trailingTypeSpecifier+ attributeSpecifierSeq?;

simpleTypeLengthModifier:
	Short
	| Long;
	
simpleTypeSignednessModifier:
	Unsigned
	| Signed;

simpleTypeSpecifier:
	nestedNameSpecifier? theTypeName
	| nestedNameSpecifier Template simpleTemplateId
	| simpleTypeSignednessModifier
	| simpleTypeSignednessModifier? simpleTypeLengthModifier+
	| simpleTypeSignednessModifier? Char
	| simpleTypeSignednessModifier? Char16
	| simpleTypeSignednessModifier? Char32
	| simpleTypeSignednessModifier? Wchar
	| Bool
	| simpleTypeSignednessModifier? simpleTypeLengthModifier* Int
	| Float
	| simpleTypeLengthModifier? Double
	| Void
	| Auto
	| decltypeSpecifier;

theTypeName:
	className
	| enumName
	| typedefName;

decltypeSpecifier:
	Decltype LeftParen (expression | Auto) RightParen;

elaboratedTypeSpecifier:
	classKey (
		attributeSpecifierSeq? nestedNameSpecifier? anyIdentifier
		| simpleTemplateId
		| nestedNameSpecifier Template? simpleTemplateId
	)
	| Enum nestedNameSpecifier? anyIdentifier;

enumName: anyIdentifier;

enumSpecifier:
	enumHead LeftBrace (enumeratorList Comma?)? RightBrace;

enumHead:
	enumkey attributeSpecifierSeq? (
		nestedNameSpecifier? anyIdentifier
	)? enumbase?;

opaqueEnumDeclaration:
	enumkey attributeSpecifierSeq? anyIdentifier enumbase? Semi;

enumkey: Enum (Class | Struct)?;

enumbase: Colon typeSpecifierSeq;

enumeratorList:
	enumeratorDefinition (Comma enumeratorDefinition)*;

enumeratorDefinition: enumerator (Assign constantExpression)?;

enumerator: anyIdentifier;

namespaceName: originalNamespaceName | namespaceAlias;

originalNamespaceName: anyIdentifier;

namespaceDefinition:
	Inline? Namespace (anyIdentifier | originalNamespaceName)? LeftBrace namespaceBody = declarationseq
		? RightBrace;

namespaceAlias: anyIdentifier;

namespaceAliasDefinition:
	Namespace anyIdentifier Assign qualifiednamespacespecifier Semi;

qualifiednamespacespecifier: nestedNameSpecifier? namespaceName;

usingDeclaration:
	Using ((Typename_? nestedNameSpecifier) | Doublecolon) unqualifiedId Semi;

usingDirective:
	attributeSpecifierSeq? Using Namespace nestedNameSpecifier? namespaceName Semi;

asmDefinition: Asm LeftParen StringLiteral RightParen Semi;

linkageSpecification:
	Extern StringLiteral (
		LeftBrace declarationseq? RightBrace
		| declaration
	);

attributeSpecifierSeq: attributeSpecifier+;

attributeSpecifier:
	LeftBracket LeftBracket attributeList? RightBracket RightBracket
	| alignmentspecifier;

alignmentspecifier:
	Alignas LeftParen (theTypeId | constantExpression) Ellipsis? RightParen;

attributeList: attribute (Comma attribute)* Ellipsis?;

attribute: (attributeNamespace Doublecolon)? anyIdentifier attributeArgumentClause?;

attributeNamespace: anyIdentifier;

attributeArgumentClause: LeftParen balancedTokenSeq? RightParen;

balancedTokenSeq: balancedtoken+;

balancedtoken:
	LeftParen balancedTokenSeq RightParen
	| LeftBracket balancedTokenSeq RightBracket
	| LeftBrace balancedTokenSeq RightBrace
	| ~(
		LeftParen
		| RightParen
		| LeftBrace
		| RightBrace
		| LeftBracket
		| RightBracket
	)+;
/*Declarators*/

initDeclaratorList: initDeclarator (Comma initDeclarator)*;

initDeclarator: declarator initializer?;

declarator:
	pointerDeclarator
	| noPointerDeclarator parametersAndQualifiers trailingReturnType;

pointerDeclarator: (pointerOperator Const?)* noPointerDeclarator;

noPointerDeclarator:
	declaratorid attributeSpecifierSeq?
	| noPointerDeclarator (
		parametersAndQualifiers
		| LeftBracket constantExpression? RightBracket attributeSpecifierSeq?
	)
	| LeftParen pointerDeclarator RightParen;

parametersAndQualifiers:
	LeftParen parameterDeclarationClause? RightParen cvqualifierseq? refqualifier?
		exceptionSpecification? attributeSpecifierSeq?;

trailingReturnType:
	Arrow trailingTypeSpecifierSeq abstractDeclarator?;

pointerOperator:
	(And | AndAnd) attributeSpecifierSeq?
	| nestedNameSpecifier? Star attributeSpecifierSeq? cvqualifierseq?;

cvqualifierseq: cvQualifier+;

cvQualifier: Const | Volatile;

refqualifier: And | AndAnd;

declaratorid: Ellipsis? ident=idExpression { last_declarator_id = $ident.text; };

theTypeId: typeSpecifierSeq abstractDeclarator?;

abstractDeclarator:
	pointerAbstractDeclarator
	| noPointerAbstractDeclarator? parametersAndQualifiers trailingReturnType
	| abstractPackDeclarator;

pointerAbstractDeclarator:
	noPointerAbstractDeclarator
	| pointerOperator+ noPointerAbstractDeclarator?;

noPointerAbstractDeclarator:
	noPointerAbstractDeclarator (
		parametersAndQualifiers
		| noPointerAbstractDeclarator (LeftBracket constantExpression? RightBracket)+
			attributeSpecifierSeq?
	)
	| parametersAndQualifiers
	| (LeftBracket constantExpression? RightBracket)+ attributeSpecifierSeq?
	| LeftParen pointerAbstractDeclarator RightParen;

abstractPackDeclarator:
	pointerOperator* noPointerAbstractPackDeclarator;

noPointerAbstractPackDeclarator:
	noPointerAbstractPackDeclarator (
		parametersAndQualifiers
		| LeftBracket constantExpression? RightBracket attributeSpecifierSeq?
	)
	| Ellipsis;

parameterDeclarationClause:
	parameterDeclarationList (Comma? Ellipsis)?;

parameterDeclarationList:
	parameterDeclaration (Comma parameterDeclaration)*;

parameterDeclaration:
	attributeSpecifierSeq? declSpecifierSeq (
		(declarator | abstractDeclarator?) (
			Assign initializerClause
		)?
	);

reenterableDefinition:
	reenterableHead
	{ reenterables[last_reent_chain_declarator] =
		(reent_static ? static_flag : 0); }
	compoundStatement { in_reenterable = false; };

reenterableDeclaration:
	reenterableHead { in_reenterable = false; reenterables[last_reent_chain_declarator] =
		(reent_static ? static_flag : 0); } Semi;

reenterableHead:
	Reenterable (LeftBracket constantExpression RightBracket)?
	{ in_reenterable = true; reent_static = _input->LT(1)->getText() == "static"; }
	(Static (Local | Global)?)? reent_chain_header reent_chain_predicate*;

reent_chain_header:
	declSpecifierSeq? declaratorid {
		last_reent_chain_declarator = last_declarator_id;
		_reent_chain_params.clear();
		_reent_planned_refs.clear();
	} LeftParen reent_chain_params? RightParen {
		for (const std::string & id : _reent_planned_refs)
			if (_reent_chain_params.find(id) == _reent_chain_params.end())
				throw FailedPredicateException(this,
					std::string("__planned__[.|->]")+id+
					std::string(" : there is no parameter ")+id+
					std::string(" in current Chain/Reenterable header"));
	};

reent_chain_params:
	reent_chain_param (Comma reent_chain_param)*;

reent_chain_param:
	(reent_recursive_type | reent_reduction | reent_gpu_global | reent_gpu_local)? declSpecifierSeq? declarator {
		_reent_chain_params.insert(last_declarator_id);
	};

reent_recursive_type:
	Id LeftParen constantExpression RightParen;

reent_reduction:
	Reduction LeftParen (reduction_symbol | anyIdentifier) RightParen;

reent_gpu_global:
	GpuGlobal {
		if (!allow_vectorized)
			throw FailedPredicateException(this, "'_global(N)' without '#pragma plan vectorized'");
	}
	LeftParen assignmentExpression RightParen;

reent_gpu_local:
	GpuLocal {
		if (!allow_vectorized)
			throw FailedPredicateException(this, "'_local(N)' without '#pragma plan vectorized'");
		_in_gpu_local = true;
	}
	LeftParen assignmentExpression RightParen {
		_in_gpu_local = false;
	};

reduction_symbol:
	Plus | Minus | Star | Caret | AndAnd | OrOr | And | Or;

reent_chain_predicate:
	reent_predicate_set
	| reent_predicate_reset
	| reent_predicate_depends
	| reent_predicate_if;

reent_predicate_set:
	Set LeftParen expression RightParen;

reent_predicate_reset:
	Reset LeftParen expression RightParen;

reent_predicate_depends:
	Depends LeftParen reent_dependents RightParen;

reent_predicate_if:
	If LeftParen reent_enumerator? expression RightParen;

reent_dependents:
	reent_enumerator reent_single_dependent |
	reent_single_dependent (Comma reent_single_dependent)*;

reent_enumerator:
	LeftBracket
	loop_statement_header
	RightBracket;

loop_statement_header:
	While LeftParen condition RightParen
	| (For | Cilk_for | Cilk_for_) LeftParen (
		forInitStatement condition? Semi expression?
		| forRangeDeclaration Colon forRangeInitializer
	) RightParen;

reent_single_dependent:
	Id (Dot | Arrow) castExpression;

chain_interface:
	Throw LeftParen reent_chain_params? RightParen;

chainDefinition:
	chainHead { chains[last_reent_chain_declarator] = 0; } compoundStatement { in_chain = false; };

chainDeclaration:
	chainHead { in_chain = false; chains[last_reent_chain_declarator] = 0; } Semi;

chainHead:
	Chain (LeftBracket constantExpression RightBracket)? {
		in_chain = true;
	} reent_chain_header
	chain_interface? reent_chain_predicate*;

functionDefinition:
	(
	 special_method_name LeftParen parameterDeclarationClause? RightParen
	 | attributeSpecifierSeq? declSpecifierSeq? declarator virtualSpecifierSeq?
	)
	functionBody;

special_method_name:
	anyIdentifier Doublecolon Tilde? anyIdentifier;

functionBody:
	constructorInitializer? compoundStatement
	| functionTryBlock
	| Assign (Default | Delete) Semi;

initializer:
	braceOrEqualInitializer
	| LeftParen expressionList RightParen;

braceOrEqualInitializer:
	Assign initializerClause
	| bracedInitList;

initializerClause: assignmentExpression | bracedInitList;

initializerList:
	initializerClause Ellipsis? (
		Comma initializerClause Ellipsis?
	)*;

bracedInitList: LeftBrace (initializerList Comma?)? RightBrace;
/*Classes*/

className: simpleTemplateId | anyIdentifier;

classSpecifier:
	classHead LeftBrace memberSpecification? RightBrace;

classHead:
	classKey attributeSpecifierSeq? (
		classHeadName classVirtSpecifier?
	)? baseClause?
	| Union attributeSpecifierSeq? (
		classHeadName classVirtSpecifier?
	)?;

classHeadName: nestedNameSpecifier? className;

classVirtSpecifier: Final;

classKey: Class | Struct;

memberSpecification:
	(markedmemberdeclaration | memberdeclaration | accessSpecifier Colon)+;

markedmemberdeclaration:
	(
	 MarkPreCondition
	 | MarkState LeftParen primaryExpression Comma primaryExpression RightParen
	)
	declSpecifierSeq? declarator Semi;

memberdeclaration:
	attributeSpecifierSeq? declSpecifierSeq? memberDeclaratorList? Semi
	| functionDefinition
	| usingDeclaration
	| staticAssertDeclaration
	| templateDeclaration
	| aliasDeclaration
	| emptyDeclaration;

memberDeclaratorList:
	memberDeclarator (Comma memberDeclarator)*;

memberDeclarator:
	declarator (
		virtualSpecifierSeq pureSpecifier?
		| (pureSpecifier | braceOrEqualInitializer)?
	)
	| anyIdentifier? attributeSpecifierSeq? Colon constantExpression;

virtualSpecifierSeq: virtualSpecifier+;

virtualSpecifier: Override | Final;
/*
 purespecifier: Assign '0'//Conflicts with the lexer ;
 */

pureSpecifier:
	Assign val = OctalLiteral {if($val.text.compare("0")!=0) throw InputMismatchException(this);
		};
/*Derived classes*/

baseClause: Colon baseSpecifierList;

baseSpecifierList:
	baseSpecifier Ellipsis? (Comma baseSpecifier Ellipsis?)*;

baseSpecifier:
	attributeSpecifierSeq? (
		baseTypeSpecifier
		| Virtual accessSpecifier? baseTypeSpecifier
		| accessSpecifier Virtual? baseTypeSpecifier
	);

classOrDeclType:
	nestedNameSpecifier? className
	| decltypeSpecifier;

baseTypeSpecifier: classOrDeclType;

accessSpecifier: Private | Protected | Public;
/*Special member functions*/

conversionFunctionId: Operator conversionTypeId;

conversionTypeId: typeSpecifierSeq conversionDeclarator?;

conversionDeclarator: pointerOperator conversionDeclarator?;

constructorInitializer: Colon memInitializerList;

memInitializerList:
	memInitializer Ellipsis? (Comma memInitializer Ellipsis?)*;

memInitializer:
	meminitializerid (
		LeftParen expressionList? RightParen
		| bracedInitList
	);

meminitializerid: classOrDeclType | anyIdentifier;
/*Overloading*/

operatorFunctionId: Operator theOperator;

literalOperatorId:
	Operator (
		StringLiteral anyIdentifier
		| UserDefinedStringLiteral
	);
/*Templates*/

templateDeclaration:
	Template Less templateparameterList Greater declaration;

templateparameterList:
	templateParameter (Comma templateParameter)*;

templateParameter: typeParameter | parameterDeclaration;

typeParameter:
	(
		(Template Less templateparameterList Greater)? Class
		| Typename_
	) ((Ellipsis? anyIdentifier?) | (anyIdentifier? Assign theTypeId));

simpleTemplateId:
	id=templateName Less templateArgumentList? Greater
	{ if (!allow_clustered && ($id.text == "cfunneled_predictor_in" || $id.text == "cfunneled_predictor_out" ))
		throw FailedPredicateException(this, "cfunneled_predictor_{in|out} can't be used without '#pragma plan clustered'");
	};

templateId:
	simpleTemplateId
	| (operatorFunctionId | literalOperatorId) Less templateArgumentList? Greater;

templateName: anyIdentifier;

templateArgumentList:
	templateArgument Ellipsis? (Comma templateArgument Ellipsis?)*;

templateArgument: theTypeId | constantExpression | idExpression;

typeNameSpecifier:
	Typename_ nestedNameSpecifier (
		anyIdentifier
		| Template? simpleTemplateId
	);

explicitInstantiation: Extern? Template declaration;

explicitSpecialization: Template Less Greater declaration;
/*Exception handling*/

tryBlock: Try compoundStatement handlerSeq;

functionTryBlock:
	Try constructorInitializer? compoundStatement handlerSeq;

handlerSeq: handler+;

handler:
	Catch LeftParen exceptionDeclaration RightParen compoundStatement;

exceptionDeclaration:
	attributeSpecifierSeq? typeSpecifierSeq (
		declarator
		| abstractDeclarator
	)?
	| Ellipsis;

throwExpression: Throw assignmentExpression?;

exceptionSpecification:
	dynamicExceptionSpecification
	| noeExceptSpecification;

dynamicExceptionSpecification:
	Throw LeftParen typeIdList? RightParen;

typeIdList: theTypeId Ellipsis? (Comma theTypeId Ellipsis?)*;

noeExceptSpecification:
	Noexcept LeftParen constantExpression RightParen
	| Noexcept;
/*Preprocessing directives*/

plan_pragma:
	PlanPragma plan_directive;

plan_directive:
	plan_dir_vectorized
	| plan_dir_clustered
	| plan_common
	| plan_gpu;

plan_dir_vectorized:
	Vectorized { allow_vectorized = true; };

plan_dir_clustered:
	Clustered { allow_clustered = true; };

plan_common:
	Common {
		if (!allow_vectorized)
			throw FailedPredicateException(this, "'#pragma plan common' without '#pragma plan vectorized'");
		if (gpu_block_opened)
			throw FailedPredicateException(this, "'#pragma plan common' can present only in non-gpu blocks'");
	}
	(
	  Begin {
		if (common_block_opened)
			throw FailedPredicateException(this, "'#pragma plan common begin' reintroduced");
		common_block_opened = true;
	  }
	  | End {
		if (!common_block_opened)
			throw FailedPredicateException(this, "'#pragma plan common end' in non-common block");
		common_block_opened = false;
	  }
	);

plan_gpu:
	Gpu {
		if (!allow_vectorized)
			throw FailedPredicateException(this, "'#pragma plan gpu' without '#pragma plan vectorized'");
		if (common_block_opened)
			throw FailedPredicateException(this, "'#pragma plan gpu' can present only in non-common blocks'");
	}
	(
	  Begin {
		if (gpu_block_opened)
			throw FailedPredicateException(this, "'#pragma plan gpu begin' reintroduced");
		gpu_block_opened = true;
	  }
	  | End {
		if (!gpu_block_opened)
			throw FailedPredicateException(this, "'#pragma plan gpu end' in non-gpu block");
		gpu_block_opened = false;
	  }
	);

/*Lexer*/

theOperator:
	New (LeftBracket RightBracket)?
	| Delete (LeftBracket RightBracket)?
	| Plus
	| Minus
	| Star
	| Div
	| Mod
	| Caret
	| And
	| Or
	| Tilde
	| Not
	| Assign
	| Greater
	| Less
	| GreaterEqual
	| PlusAssign
	| MinusAssign
	| StarAssign
	| ModAssign
	| XorAssign
	| AndAssign
	| OrAssign
	| Less Less
	| Greater Greater
	| RightShiftAssign
	| LeftShiftAssign
	| Equal
	| NotEqual
	| LessEqual
	| AndAnd
	| OrOr
	| PlusPlus
	| MinusMinus
	| Comma
	| ArrowStar
	| Arrow
	| LeftParen RightParen
	| LeftBracket RightBracket;

literal:
	IntegerLiteral
	| CharacterLiteral
	| FloatingLiteral
	| StringLiteral
	| BooleanLiteral
	| PointerLiteral
	| UserDefinedLiteral;
	
