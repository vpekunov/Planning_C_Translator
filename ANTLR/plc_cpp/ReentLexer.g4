/* Modified by V.V.Pekunov -- extended to Planning C language */
/* Based on CPP14Lexer.g4 (https://github.com/antlr/grammars-v4) */

lexer grammar ReentLexer;
options {
	language = Cpp;
}

@lexer::header {
#include <map>
}

@members {
	std::map<int, std::string> __lines;
}
IntegerLiteral:
	DecimalLiteral Integersuffix?
	| OctalLiteral Integersuffix?
	| HexadecimalLiteral Integersuffix?
	| BinaryLiteral Integersuffix?;

CharacterLiteral:
	('u' | 'U' | 'L')? '\'' Cchar+ '\'';

FloatingLiteral:
	Fractionalconstant Exponentpart? Floatingsuffix?
	| Digitsequence Exponentpart Floatingsuffix?;

StringLiteral:
	Encodingprefix?
    (Rawstring
	|'"' Schar* '"');

BooleanLiteral: False_ | True_;

PointerLiteral: Nullptr;

UserDefinedLiteral:
	UserDefinedIntegerLiteral
	| UserDefinedFloatingLiteral
	| UserDefinedStringLiteral
	| UserDefinedCharacterLiteral;

PlanPragma:
	'#pragma' [ \t]+ Plan;

DoNotCheck:
	{ getCharPositionInLine() == 0 }? [ \t]* '#pragma' [ \t]+ 'syntax' [ \t]+
	'nocheck' (~[\r\n]* Newline Line?)+?
	{ getCharPositionInLine() == 0 }? [ \t]* '#pragma' [ \t]+ 'syntax' [ \t]+
	'check' ~[\r\n]* Newline -> skip;

BlockComment: '/*' .*? '*/' -> skip;

OtherPragma:
	'#pragma' [ \t]+ ('package' | 'pop' | 'push' | 'pack' | ~[p]+) (~[\n/]+ ('/' ('*' .*? '*/')?)?)* -> channel (HIDDEN);

Line:
	{ getCharPositionInLine() == 0 }? [ \t]* '#line' [ \t]+ IntegerLiteral [ \t]+ StringLiteral Newline { __lines[getLine()] = getText(); } -> skip;

MultiLineMacro:
	'#' (~[\n]*? '\\' '\r'? '\n' Line?)+ ~ [\n]+ -> channel (HIDDEN);

Directive: '#' ('define' | 'undef' | 'ifdef' | 'ifndef' | 'if' | 'endif'
		| 'else' | 'elif' | 'error' | 'include')
		(~[\n/]+ ('/' ('*' .*? '*/')?)?)* -> channel (HIDDEN);

/*Keywords*/

Alignas: 'alignas';

Alignof: 'alignof';

Asm: 'asm';

Auto: 'auto';

Begin: 'begin';

Bool: 'bool';

Break: 'break';

Case: 'case';

Catch: 'catch';

Cfunnel: 'cfunnel';

Chain: 'chain';

Char: 'char';

Char16: 'char16_t';

Char32: 'char32_t';

Cilk_for: 'cilk_for';

Cilk_for_: '_Cilk_for';

Cilk_spawn: 'cilk_spawn';

Cilk_spawn_: '_Cilk_spawn';

Cilk_sync: 'cilk_sync';

Cilk_sync_: '_Cilk_sync';

Class: 'class';

Clear_plan: 'clear_plan';

Clustered: 'clustered';

Common: 'common';

Const: 'const';

Constexpr: 'constexpr';

Const_cast: 'const_cast';

Continue: 'continue';

Csem: 'plan_csem_t';

Cvar: 'cvar';

Decltype: 'decltype';

Default: 'default';

Delete: 'delete';

Depends: 'depends';

Do: 'do';

Double: 'double';

Dynamic_cast: 'dynamic_cast';

Else: 'else';

End: 'end';

Enum: 'enum';

Explicit: 'explicit';

Export: 'export';

Extern: 'extern';

//DO NOT RENAME - PYTHON NEEDS True and False
False_: 'false';

Final: 'final';

Float: 'float';

For: 'for';

Friend: 'friend';

Funnel: 'funnel';

Global: 'global';

Gpu: 'gpu';

Goto: 'goto';

GpuGlobal: '_global';

GpuLocal: '_local';

Id: 'id';

If: 'if';

In: 'in';

Inline: 'inline';

Int: 'int';

Local: 'local';

Long: 'long';

MarkPreCondition: 'pre_id';

MarkState: 'state';

Markupdef: 'markupdef';

Mutable: 'mutable';

Namespace: 'namespace';

New: 'new';

Noexcept: 'noexcept';

Nullptr: 'nullptr';

Operator: 'operator';

Out: 'out';

Override: 'override';

Plan: 'plan';

Plan_atomize: 'plan_atomize';

Plan_chain: 'plan_chain';

Plan_critical: 'plan_critical';

Plan_first: 'plan_first';

Plan_get_first: 'plan_get_first';

Plan_get_last: 'plan_get_last';

Plan_group_atomize: 'plan_group_atomize';

Plan_group_first: 'plan_group_first';

Plan_group_last: 'plan_group_last';

Plan_group_parallelize: 'plan_group_parallelize';

Plan_group_soft_atomize: 'plan_group_soft_atomize';

Plan_group_vectorize: 'plan_group_vectorize';

Plan_item_type: 'plan_item_type';

Plan_last: 'plan_last';

Plan_parallel_chain: 'plan_parallel_chain';

Plan_parallel_reverse: 'plan_parallel_reverse';

Plan_register: 'plan_register';

Plan_registered_barrier: 'plan_registered_barrier';

Plan_stop: 'plan_stop';

Plan_topology: 'plan_topology';

Plan_type: 'plan_type';

Private: 'private';

Protected: 'protected';

Public: 'public';

Reduction: 'reduction';

Reenterable: 'reenterable';

Register: 'register';

Reinterpret_cast: 'reinterpret_cast';

Reset: 'reset';

Return: 'return';

Set: 'set';

Short: 'short';

Signed: 'signed';

Sizeof: 'sizeof';

Soft_transact_array: 'soft_transact_array';

Soft_transact_in: 'soft_transact_in';

Soft_transact_out: 'soft_transact_out';

Soft_transact_var: 'soft_transact_var';

Static: 'static';

Static_assert: 'static_assert';

Static_cast: 'static_cast';

Struct: 'struct';

Switch: 'switch';

Template: 'template';

This: 'this';

Thread_local: 'thread_local';

Throw: 'throw';

Throw_first: 'throw_first';

Throw_last: 'throw_last';

Transaction_atomic: 'transaction_atomic';

//DO NOT RENAME - PYTHON NEEDS True and False
True_: 'true';

Try: 'try';

Typedef: 'typedef';

Typeid_: 'typeid';

Typename_: 'typename';

Union: 'union';

Unsigned: 'unsigned';

Using: 'using';

Vectorized: 'vectorized';

Virtual: 'virtual';

Void: 'void';

Volatile: 'volatile';

Wchar: 'wchar_t';

While: 'while';
/*Operators*/

At: '@';

Dollar: '$';

Is: ':-';

LeftParen: '(';

RightParen: ')';

LeftBracket: '[';

RightBracket: ']';

LeftBrace: '{';

RightBrace: '}';

Underscore: '_';

Plus: '+';

Minus: '-';

Star: '*';

Div: '/';

Mod: '%';

Caret: '^';

And: '&';

Or: '|';

Tilde: '~';

Not: '!' | 'not';

Assign: '=';

Less: '<';

Greater: '>';

PlusAssign: '+=';

MinusAssign: '-=';

StarAssign: '*=';

DivAssign: '/=';

ModAssign: '%=';

XorAssign: '^=';

AndAssign: '&=';

OrAssign: '|=';

LeftShiftAssign: '<<=';

RightShiftAssign: '>>=';

Equal: '==';

NotEqual: '!=';

LessEqual: '<=';

GreaterEqual: '>=';

AndAnd: '&&' | 'and';

OrOr: '||' | 'or';

PlusPlus: '++';

MinusMinus: '--';

Comma: ',';

ArrowStar: '->*';

Arrow: '->';

Question: '?';

Colon: ':';

Doublecolon: '::';

Semi: ';';

Dot: '.';

DotStar: '.*';

Ellipsis: '...';

fragment Hexquad:
	HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT;

fragment Universalcharactername:
	'\\u' Hexquad
	| '\\U' Hexquad Hexquad;

Identifier:
	/*
	 Identifiernondigit | Identifier Identifiernondigit | Identifier DIGIT
	 */
	Identifiernondigit (Identifiernondigit | DIGIT)*;

fragment Identifiernondigit: NONDIGIT | Universalcharactername;

fragment NONDIGIT: [a-zA-Z_];

fragment DIGIT: [0-9];

DecimalLiteral: NONZERODIGIT ('\''? DIGIT)*;

OctalLiteral: '0' ('\''? OCTALDIGIT)*;

HexadecimalLiteral: ('0x' | '0X') HEXADECIMALDIGIT (
		'\''? HEXADECIMALDIGIT
	)*;

BinaryLiteral: ('0b' | '0B') BINARYDIGIT ('\''? BINARYDIGIT)*;

fragment NONZERODIGIT: [1-9];

fragment OCTALDIGIT: [0-7];

fragment HEXADECIMALDIGIT: [0-9a-fA-F];

fragment BINARYDIGIT: [01];

Integersuffix:
	Unsignedsuffix Longsuffix?
	| Unsignedsuffix Longlongsuffix?
	| Longsuffix Unsignedsuffix?
	| Longlongsuffix Unsignedsuffix?;

fragment Unsignedsuffix: [uU];

fragment Longsuffix: [lL];

fragment Longlongsuffix: 'll' | 'LL';

fragment Cchar:
	~ ['\\\r\n]
	| Escapesequence
	| Universalcharactername;

fragment Escapesequence:
	Simpleescapesequence
	| Octalescapesequence
	| Hexadecimalescapesequence;

fragment Simpleescapesequence:
	'\\\''
	| '\\"'
	| '\\?'
	| '\\\\'
	| '\\a'
	| '\\b'
	| '\\f'
	| '\\n'
	| '\\r'
	| ('\\' ('\r' '\n'? | '\n'))
	| '\\t'
	| '\\v';

fragment Octalescapesequence:
	'\\' OCTALDIGIT
	| '\\' OCTALDIGIT OCTALDIGIT
	| '\\' OCTALDIGIT OCTALDIGIT OCTALDIGIT;

fragment Hexadecimalescapesequence: '\\x' HEXADECIMALDIGIT+;

fragment Fractionalconstant:
	Digitsequence? '.' Digitsequence
	| Digitsequence '.';

fragment Exponentpart:
	'e' SIGN? Digitsequence
	| 'E' SIGN? Digitsequence;

fragment SIGN: [+-];

fragment Digitsequence: DIGIT ('\''? DIGIT)*;

fragment Floatingsuffix: [flFL];

fragment Encodingprefix: 'u8' | 'u' | 'U' | 'L';

fragment Schar:
	~ ["\\\r\n]
	| Escapesequence
	| Universalcharactername;

fragment Rawstring: 'R"' (( '\\' ["()] )|~[\r\n (])*? '(' ~[)]*? ')'  (( '\\' ["()]) | ~[\r\n "])*? '"';

UserDefinedIntegerLiteral:
	DecimalLiteral Udsuffix
	| OctalLiteral Udsuffix
	| HexadecimalLiteral Udsuffix
	| BinaryLiteral Udsuffix;

UserDefinedFloatingLiteral:
	Fractionalconstant Exponentpart? Udsuffix
	| Digitsequence Exponentpart Udsuffix;

UserDefinedStringLiteral: StringLiteral Udsuffix;

UserDefinedCharacterLiteral: CharacterLiteral Udsuffix;

fragment Udsuffix: Identifier;

Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;

LineComment: '//' ~ [\r\n]* -> skip;
