parser grammar ReentPreParser;
options {
	tokenVocab = ReentPreLexer;
	language = Cpp;
}
/*Basic concepts*/

@parser::header {
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
}

@members {
	std::map<std::string, int> modules;
	std::map<std::string, int> module_refs;
	std::set<std::string> scanners;
	std::set<std::string> scanner_refs;
	std::vector<std::string> memo_map;
	std::set<std::string> xpaths;
	std::set<std::string> regexp_vars;
	std::set<std::string> regexp_refs;
}

translationUnit: statementseq? EOF {
		for (const std::string & s : scanner_refs)
			if (scanners.find(s) == scanners.end())
				std::cerr << "warning:" << std::string("unknown scanner '") << s <<
						std::string("' in #add_scan/#add_parse/#scan/#parse directives") << std::endl;
		std::map<std::string,int>::iterator it;
		for (it = module_refs.begin(); it != module_refs.end(); it++)
			if (modules.find(it->first) == modules.end())
				throw FailedPredicateException(this, std::string("Unknown module '")+it->first+
						std::string("' in some #def_pattern directives"));
			else if (modules[it->first] != it->second)
				throw FailedPredicateException(this, std::string("Module '")+it->first+
						std::string("' was called with an incorrect parameters number in some #def_pattern directives"));
	};
/*Expressions*/

statementseq:
	statement+;

statement:
	defModule
	| DefModule {
		throw FailedPredicateException(this, "Something wrong with module definition");
	}
	| defMemoization
	| DefMemoization {
		throw FailedPredicateException(this, "Something wrong with memoization");
	}
	| preprocPasses
	| PreprocPasses {
		throw FailedPredicateException(this, "Something wrong with '#preproc_passes(n)'");
	}
	| addScan
	| AddScan {
		throw FailedPredicateException(this, "Something wrong with '#add_scan'");
	}
	| scan
	| Scan {
		throw FailedPredicateException(this, "Something wrong with '#scan'");
	}
	| addParse
	| AddParse {
		throw FailedPredicateException(this, "Something wrong with '#add_parse'");
	}
	| parse
	| Parse {
		throw FailedPredicateException(this, "Something wrong with '#parse'");
	}
	| def_pattern
	| DefPattern {
		throw FailedPredicateException(this, "Something wrong with '#def_pattern'");
	}
	| def_xpath
	| DefXPath {
		throw FailedPredicateException(this, "Something wrong with '#def_xpath'");
	}
	| objCilkSpawn
	| objCilkAssign? objCilkDesignator*? Cilk_spawn { throw FailedPredicateException(this, "Obj-cilk_spawn expression is incorrect!"); }
	| objCilkSync
	| objCilkDesignator*? Cilk_sync { throw FailedPredicateException(this, "Obj-cilk_sync expression is incorrect!"); }
	| otherLine;

def_pattern:
	DefPattern {
		regexp_vars.clear(); regexp_vars.insert("root");
		regexp_refs.clear();
		std::string call_macro;
	}
	id=Identifier {
		if (scanners.find($id.text) != scanners.end())
			throw FailedPredicateException(this, "Pattern is already defined");
		scanners.insert($id.text);
	}
	AssignGreater
	(put_fact | module=Identifier {
				call_macro = $module.text;
			})
	LeftParen
		{ int param_count = 0; }
		(def_pattern_param { param_count++; } (Comma def_pattern_param { param_count++; })*)?
	RightParen {
		if (call_macro.length() > 0) {
			if (module_refs.find(call_macro) != module_refs.end() && module_refs[call_macro] != param_count)
				throw FailedPredicateException(this,
					std::string("Pattern calls module '") + call_macro +
					std::string("' with an incorrect number of params than in another patterns"));
			else module_refs[call_macro] = param_count;
		}
	}
	regexps
	{
		for (const std::string & s : regexp_refs)
			if (regexp_vars.find(s) == regexp_vars.end())
				throw FailedPredicateException(this,
					std::string("Reference to undefined var '")+
					s +
					std::string("' in '#def_pattern' regexps/header"));
	};

put_fact:
	LeftBracket Identifier RightBracket;

def_pattern_param:
	CharacterLiteral
	| EmptyAtom
	| LeftBracket (def_pattern_param (Comma def_pattern_param)*
	  (Or def_pattern_param)?)? RightBracket
	| simple_xpath_expression
	| {
		throw FailedPredicateException(this, "Unrecognized (prolog_fact/module)'s parameter");
	} .; /* "." -- only to prevent warning */

simple_xpath_expression:
	xpath_and_expression (Or_ xpath_and_expression)*;

xpath_and_expression:
	xpath_rel_expression (And_ xpath_rel_expression)*;

xpath_rel_expression:
	xpath_mul_expression ((Less | Greater | Assign | NotEqual | LessEqual | GreaterEqual) xpath_mul_expression)*;

xpath_mul_expression:
	xpath_plus_expression ((Star | Div) xpath_plus_expression)*;

xpath_plus_expression:
	xpath_unary_expression ((Plus | Minus) xpath_unary_expression)*;

xpath_unary_expression:
	StringLiteral
	| CharacterLiteral
	| EmptyAtom
	| IntegerLiteral
	| FloatingLiteral
	| AtValue
	| GetText
	| LeftParen simple_xpath_expression RightParen
	| xpath_query
	| Identifier (LeftParen xpath_fun_params? RightParen)?;

xpath_query:
	(Div | DivDiv)? (var=Identifier { regexp_refs.insert($var.text); } | Star) xpath_predicate?
	((Div | DivDiv) (next=Identifier { regexp_refs.insert($next.text); } | Star) xpath_predicate?)*
	(Div | DivDiv) ((last=Identifier { regexp_refs.insert($last.text); } | Star) | AtValue | GetText);

xpath_predicate:
	LeftBracket simple_xpath_expression RightBracket;

xpath_fun_params:
	simple_xpath_expression (Comma simple_xpath_expression)*;

def_xpath:
	DefXPath
	id=Identifier {
		if (xpaths.find($id.text) != xpaths.end())
			throw FailedPredicateException(this, "XPath is already defined");
		xpaths.insert($id.text);
	}
	(
	 LeftParen
		(def_xpath_param (Comma def_xpath_param)*)?
	 RightParen
	)?
	LeftBrace Newline
		def_xpath_expression
	RightBrace Newline;

def_xpath_param:
	And? Regexp_ref Identifier;

def_xpath_expression:
	def_xpath_and_expression (Newline? Or_ Newline? def_xpath_and_expression)* Newline?;

def_xpath_and_expression:
	def_xpath_rel_expression (Newline? And_ Newline? def_xpath_rel_expression)* Newline?;

def_xpath_rel_expression:
	def_xpath_mul_expression (Newline? (Less | Greater | Assign | NotEqual | LessEqual | GreaterEqual) Newline? def_xpath_mul_expression)* Newline?;

def_xpath_mul_expression:
	def_xpath_plus_expression (Newline? (Star | Div) Newline? def_xpath_plus_expression)* Newline?;

def_xpath_plus_expression:
	def_xpath_unary_expression (Newline? (Plus | Minus) Newline? def_xpath_unary_expression)* Newline?;

def_xpath_unary_expression:
	StringLiteral
	| CharacterLiteral
	| EmptyAtom
	| IntegerLiteral
	| FloatingLiteral
	| AtValue
	| At Identifier
	| GetText
	| LeftParen Newline? def_xpath_expression Newline? RightParen Newline?
	| Identifier Newline? LeftParen Newline? def_xpath_fun_params? Newline? RightParen Newline?
	| def_xpath_query Newline?
	| Regexp_ref Identifier;

def_xpath_query:
	(Div | DivDiv)? Newline? (Identifier | Star) Newline? def_xpath_predicate?
	((Div | DivDiv) Newline? (Identifier | Star) Newline? def_xpath_predicate?)*
	((Div | DivDiv) Newline? ((Identifier | Star) | AtValue | At Identifier | GetText))?;

def_xpath_predicate:
	LeftBracket Newline? def_xpath_expression Newline? RightBracket;

def_xpath_fun_params:
	def_xpath_expression (Newline? Comma Newline? def_xpath_expression)* Newline?;

regexps:
	LeftBrace Newline
	regexp_lines*
	(Regexp_begin Newline regexp_lines* Regexp_end Newline)?
	regexp_lines*
	RightBrace Semi Newline;

regexp_lines:
	regexp_body? Newline;

regexp_body:
	{
		!_input->LT(-1) || _input->LT(-1)->getText()!="\n" ||
		(_input->LT(1) && _input->LT(1)->getText() != "@begin" && _input->LT(1)->getText() != "@end" &&
		 (_input->LT(1)->getText() != "}" || _input->LT(2) && _input->LT(2)->getText() != ";"))
	}?
	(
	  LeftParen (regexp_body | Newline)* (plc_regexp_logical | RightParen)
	  | Regexp_set
	  | Regexp_fragment
	) regexp_body?;

plc_regexp_logical:
	plc_regexp_var
	| plc_regexp_equal
	| plc_regexp_not_equal
	| plc_regexp_query;

plc_regexp_var:
	Plc_regexp_var
	(
	 lib_or_id=Identifier
		(Dot Identifier LeftBrace var=Identifier RightBrace RightBrace { regexp_vars.insert($var.text); }
		 | RightBrace { regexp_vars.insert($lib_or_id.text); }
		 | { throw FailedPredicateException(this, "->{Id} expected"); }
		)
	);

plc_regexp_equal:
	Plc_regexp_equal (req=Identifier | { throw FailedPredicateException(this, "==>{Id} expected"); }) RightBrace {
		regexp_refs.insert($req.text);
	};

plc_regexp_not_equal:
	Plc_regexp_not_equal (req=Identifier | { throw FailedPredicateException(this, "!=>{Id} expected"); }) RightBrace {
		regexp_refs.insert($req.text);
	};
	
plc_regexp_query:
	Plc_regexp_query
		(
		  regexp_or_sequence
		  | { throw FailedPredicateException(this, "=>{op[,op]} unrecognized"); }
		)
	RightBrace;

regexp_or_sequence:
	Newline? regexp_and_sequence (Newline? Semi Newline? regexp_and_sequence)* Newline?;

regexp_and_sequence:
	Newline? regexp_unary (Newline? Comma Newline? regexp_unary)* Newline?;

regexp_unary:
	Newline? LeftParen Newline? regexp_or_sequence Newline? RightParen Newline?
	| Newline? regexp_pred Newline?;

regexp_pred:
	regexp_pred_parallel
	| Regexp_sequential
	| Not? Identifier (Dot Identifier)? (LeftParen (Newline? regexp_pred_arg (Newline? Comma Newline? regexp_pred_arg)*)? Newline? RightParen)?;

regexp_pred_arg:
	Underscore
	| Regexp_ref (ref=Identifier { regexp_refs.insert($ref.text); })?
	| StringLiteral
	| CharacterLiteral
	| EmptyAtom
	| IntegerLiteral
	| FloatingLiteral
	| var=Identifier { regexp_refs.insert($var.text); };

regexp_pred_parallel:
	Regexp_parallel Newline? (LeftParen Newline? Regexp_analyze Newline? RightParen)? Newline?;

defModule:
	DefModule LeftParen Identifier? RightParen ident=Identifier LeftParen
	{ int param_counter = 0; }
	( Identifier { param_counter++; } (Comma Identifier { param_counter++; })* )?
	RightParen {
		modules[$ident.text] = param_counter;
	} Newline* LeftBrace Newline*
		defModuleDescriptors 
	Newline*;

defModuleDescriptors:
	defModuleDescriptor (RightBrace Semi | RightBrace? defModuleDescriptors);

defModuleDescriptor:
	At (prolog_goal | prolog_statement | { throw FailedPredicateException(this, "Corrupted Prolog statement in module definition"); } )
	| cpp_code_without_at;

defMemoization:
	DefMemoization LeftParen
	{ memo_map.clear(); int param_counter = 0; }
	first=memoMapItem { param_counter++; memo_map.push_back($first.text); }
	(Comma next=memoMapItem { param_counter++;
		if ($next.text == "*g" || $next.text == "g")
			if (std::find(memo_map.begin(), memo_map.end(), "g") != memo_map.end() ||
				std::find(memo_map.begin(), memo_map.end(), "*g") != memo_map.end())
				throw FailedPredicateException(this, "only one parameter can be of type 'g'");
		if ($next.text == "*o" || $next.text == "o")
			if (std::find(memo_map.begin(), memo_map.end(), "o") != memo_map.end() ||
				std::find(memo_map.begin(), memo_map.end(), "*o") != memo_map.end())
				throw FailedPredicateException(this, "only one parameter can be of type 'o'");
		if ($next.text == "*t" || $next.text == "t")
			throw FailedPredicateException(this, "only first parameter can be of type 't'");
		memo_map.push_back($next.text);
	})*
	RightParen
	memoizationStyle?
	Newline+
	blockHeader;

preprocPasses:
	PreprocPasses LeftParen IntegerLiteral (Comma StringLiteral)? RightParen Newline;

addScan:
	AddScan scanners_list Newline;

scan:
	Scan scanners_list Newline;

addParse:
	AddParse scanners_list Newline;

parse:
	Parse scanners_list Newline;

scanners_list:
	LeftParen
		first=Identifier {
			scanner_refs.insert($first.text);
		}
		(Comma next=Identifier {
			scanner_refs.insert($next.text);
		})*
	RightParen;

memoMapItem:
	Star? memoMapType;

memoMapType:
	{ _input->LT(1)->getText() == "i" || _input->LT(1)->getText() == "o" ||
	  _input->LT(1)->getText() == "g" || _input->LT(1)->getText() == "t" }? Identifier
	| { throw FailedPredicateException(this,
		std::string("Wrong map descriptor '")+
		_input->LT(1)->getText()+
		std::string("'. Must be one of ['i','o','g','t']")); };

cpp_balanced_expression:
	(
	 Identifier (LeftParen (cpp_balanced_expression (Comma cpp_balanced_expression)*)? RightParen)?
	 | ~(Comma | LeftParen | RightParen | LeftBracket | RightBracket | Identifier)+
	 | LeftParen cpp_balanced_expression RightParen
	 | LeftBracket cpp_balanced_expression RightBracket
	) cpp_balanced_expression?;

memoizationStyle:
	(mgua | nnet | extrapolator) controlPredicate?;

mgua:
	Mgua LeftParen (Identifier | IntegerLiteral | FloatingLiteral) RightParen;

nnet:
	Feed_forward LeftParen
		(IntegerLiteral | FloatingLiteral) Comma
		(FloatingLiteral) Comma
		(IntegerLiteral)
		(Comma nnet_layer_specifier (Comma nnet_layer_specifier)?)?
	RightParen;

extrapolator:
	Lin_extrapolator LeftParen
		(IntegerLiteral | FloatingLiteral) Comma
		IntegerLiteral
	RightParen;

nnet_layer_specifier:
	IntegerLiteral Comma nnet_layer_type;

nnet_layer_type:
	{ _input->LT(1)->getText() == "e" || _input->LT(1)->getText() == "l" ||
	  _input->LT(1)->getText() == "h" || _input->LT(1)->getText() == "r" }? Identifier
	| { throw FailedPredicateException(this,
		std::string("Must be the Number of neurons with following one of ['e','l','h','r']")); };

controlPredicate:
	automated_control | by_conditions_control;

automated_control:
	Controlled LeftParen
		IntegerLiteral Comma IntegerLiteral
	RightParen;

by_conditions_control:
	Conditions LeftParen
		cpp_balanced_expression Comma cpp_balanced_expression
	RightParen;

blockHeader:
	type=typeItem+ Identifier LeftParen
	{ if ($type.text == "void" &&
		std::find(memo_map.begin(), memo_map.end(), "o") == memo_map.end() &&
		std::find(memo_map.begin(), memo_map.end(), "*o") == memo_map.end()
		)
		throw FailedPredicateException(this, "void memoized function must have 'o' parameter");
	  else if ($type.text != "void" &&
		( std::find(memo_map.begin(), memo_map.end(), "o") != memo_map.end() ||
		std::find(memo_map.begin(), memo_map.end(), "*o") != memo_map.end())
		)
		throw FailedPredicateException(this, "non-void memoized function can't have 'o' parameter");
	  int param_count = 0;
	}
	(parameter { param_count++; } (Comma parameter { param_count++; })*)?
	RightParen
	{ if (param_count != memo_map.size()) throw FailedPredicateException(this, "number of mapping parameters does not correspond to the number of parameters in function's header"); }
	Newline* LeftBrace ~Newline* Newline+;

typeItem:
	typeSpecifier (And | AndAnd | Star*);

typeSpecifier:
	Identifier (
		Less templateParameters? Greater |
		Identifier*
	);

templateParameters:
	templateParameter (Comma templateParameter)*;

templateParameter:
	typeSpecifier | literal;

parameter:
	typeItem Identifier dimension*;

dimension:
	LeftBracket (Identifier | IntegerLiteral) RightBracket;

prolog_goal:
	Goal Is prolog_predicates Dot;

prolog_statement:
	Identifier prolog_parameters?
		(Is prolog_predicates)? Dot;

prolog_parameters:
	(LeftParen prolog_parameter (Comma prolog_parameter)* RightParen);

prolog_predicates:
	Newline* Prolog_not? prolog_predicate prolog_if_then?
		((Semi | Comma) prolog_predicates)?;

prolog_parameter:
	literal
	| EmptyAtom
	| prolog_parameter_list
	| prolog_predicate
	| Underscore;

prolog_parameter_list:
	LeftBracket (prolog_inside_list
	  (Or prolog_parameter)?)? RightBracket;

prolog_inside_list:
	prolog_parameter (Comma prolog_inside_list)?;

prolog_predicate:
	LeftParen Newline* prolog_predicates Newline* RightParen Newline*
	| Not
	| prolog_call
	| is_expression;

prolog_if_then:
	(Arrow Newline* Prolog_not? prolog_predicate);

is_expression:
	relational_expression (Is_ relational_expression)?;

relational_expression:
	pow_expression (prolog_relation relational_expression)?;

prolog_relation:
	Equal | NotEqual | Less | Greater | LessEqual | GreaterEqual;

pow_expression:
	mul_div_expression (prolog_pow pow_expression)?;

prolog_pow:
	Star Star | Caret;

mul_div_expression:
	plus_min_expression (prolog_mul_div mul_div_expression)?;

prolog_mul_div:
	Star | Rem | Div_ | Mod_ | Div Div?;

plus_min_expression:
	unary_expression (prolog_plus_minus plus_min_expression)*;

prolog_plus_minus:
	Plus | Minus;

unary_expression:
	prolog_plus_minus? operand;

operand:
	LeftParen relational_expression RightParen
	| operandList
	| prolog_term
	| EmptyAtom
	| literal;

operandList:
	LeftBracket (relational_expression (Comma relational_expression)*
	  (Or relational_expression)?)? RightBracket;

prolog_term:
	Identifier (LeftParen (relational_expression (Comma relational_expression)*)?  RightParen)?;

prolog_call:
	prolog_predicate_id prolog_call_params
	| Identifier prolog_call_params?;

prolog_call_params:
	LeftParen Newline* prolog_parameter (Comma Newline* prolog_parameter)* Newline* RightParen;

prolog_predicate_id:
	Semi
	| Less
	| Assign
	| Greater
	| LessEqual
	| GreaterEqual
	| Equal
	| NotEqual
	| Arrow
	| Prolog_not_equal
	| ConstructAtom;

cpp_code_without_at:
	~(At | RightBrace)+;

objCilkSpawnArg:
	Assign Identifier
	| cpp_balanced_expression;

objCilkSpawnParams:
	LeftParen cpp_balanced_expression Comma cpp_balanced_expression RightParen;

objCilkDesignator:
	Identifier (LeftBracket cpp_balanced_expression RightBracket)* (Dot | Arrow);

objCilkAssign:
	Identifier+ (LeftBracket cpp_balanced_expression RightBracket)* Assign;

objCilkSpawn:
	objCilkAssign?
	objCilkDesignator*? Cilk_spawn
	(
	 objCilkSpawnParams?
		objCilkDesignator*? Identifier
		LeftParen (objCilkSpawnArg (Comma objCilkSpawnArg)*)? RightParen
	 Semi (~Newline)* Newline
	);

objCilkSync:
	objCilkDesignator*? Cilk_sync
	(
	 (LeftParen cpp_balanced_expression? RightParen)? Semi (~Newline)* Newline
	);

otherLine:
	{ _input->LT(-1) == NULL || _input->LT(-1)->getText() == "\n" }? (~Newline)* Newline;

literal:
	IntegerLiteral
	| CharacterLiteral
	| FloatingLiteral
	| StringLiteral
	| BooleanLiteral
	| PointerLiteral
	| UserDefinedLiteral;
	
