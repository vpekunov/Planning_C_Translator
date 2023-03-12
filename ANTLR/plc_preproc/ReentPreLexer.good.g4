/* Modified by V.V.Pekunov -- extended to Planning C language */
/* Based on CPP14Lexer.g4 (https://github.com/antlr/grammars-v4) */

lexer grammar ReentPreLexer;
options {
	language = Cpp;
}

@members {
	int def_pattern_state = 0;
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

EmptyAtom:
	'\'\'';

BooleanLiteral: False_ | True_;

PointerLiteral: Nullptr;

UserDefinedLiteral:
	UserDefinedIntegerLiteral
	| UserDefinedFloatingLiteral
	| UserDefinedStringLiteral
	| UserDefinedCharacterLiteral;

DefModule:
	{ getCharPositionInLine() == 0 }? [ \t]* '#def_module' [ \t]*;

DefMemoization:
	{ getCharPositionInLine() == 0 }? [ \t]* '#pragma' [ \t]+ 'memoization' [ \t]*;

DefOtherPragma:
	{ getCharPositionInLine() == 0 }? [ \t]* '#pragma' [ \t]+ ~[m] ~[\n]* Newline -> channel (HIDDEN);

PreprocPasses:
	{ getCharPositionInLine() == 0 }? [ \t]* '#preproc_passes' [ \t]*;

AddScan:
	{ getCharPositionInLine() == 0 }? [ \t]* '#add_scan' [ \t]*;

Scan:
	{ getCharPositionInLine() == 0 }? [ \t]* '#scan' [ \t]*;

AddParse:
	{ getCharPositionInLine() == 0 }? [ \t]* '#add_parse' [ \t]*;

Parse:
	{ getCharPositionInLine() == 0 }? [ \t]* '#parse' [ \t]*;

DefPattern:
	{ getCharPositionInLine() == 0 }? [ \t]* '#def_pattern' [ \t]* { def_pattern_state = 1; };

MultiLineMacro:
	{ getCharPositionInLine() == 0 }? [ \t]* Pound (~[\n]*? '\\' '\r'? '\n')+ ~[\n]+ Newline -> channel (HIDDEN);

Directive: { getCharPositionInLine() == 0 }? [ \t]* Pound ('define' | 'undef' | 'ifdef' | 'ifndef' | 'if' | 'endif'
		| 'else' | 'elif' | 'line' | 'error' | 'include') ~[\n]* Newline -> channel (HIDDEN);

/*Keywords*/

AtValue: '@Value';

Conditions: 'conditions';

Controlled: 'controlled';

Div_: 'div';

//DO NOT RENAME - PYTHON NEEDS True and False
False_: 'false';

Feed_forward: 'feed_forward';

GetText: 'text()';

Goal: 'goal';

Lin_extrapolator: 'lin_extrapolator';

Mgua: 'mgua';

Mod_: 'mod';

Nullptr: 'nullptr';

Regexp_analyze: 'analyze';

Regexp_begin: '@begin';

Regexp_end: '@end';

Regexp_parallel: 'parallel';

Regexp_sequential: 'sequential';

Rem: 'rem';

//DO NOT RENAME - PYTHON NEEDS True and False
True_: 'true';

/*Operators*/
Plc_regexp_var: ')->{' { def_pattern_state = 3; };

Plc_regexp_equal: ')==>{' { def_pattern_state = 3; };

Plc_regexp_not_equal: ')!=>{' { def_pattern_state = 3; };

Plc_regexp_query: ')?=>{' { def_pattern_state = 3; };

LeftParen: '(';

RightParen: ')';

LeftBracket: '[';

RightBracket: ']';

LeftBrace: '{' { if (def_pattern_state == 1) def_pattern_state = 2; };

RightBrace: '}' {
	if (def_pattern_state == 2) def_pattern_state = 0;
	else if (def_pattern_state == 3) def_pattern_state = 2;
};

Regexp_fragment: { def_pattern_state == 2}? (Slash . | ~[@}()\][\r\n]) (Slash . | ~[()\][\\\r\n])*;

Regexp_set: { def_pattern_state == 2}? LeftBracket Caret? (Slash . | ~[\\\]])+ RightBracket;

AssignGreater: '=>';

DivDiv: '//';

Pound: '#';

And_: 'and';

Or_: 'or';

At: '@';

Is: ':-';

Is_: 'is';

Prolog_not: '\\+';

Prolog_not_equal: '\\=';

Slash: '\\';

ConstructAtom: '=..';

Regexp_ref: '$';

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

Equal: '==';

NotEqual: '!=';

LessEqual: '<=';

GreaterEqual: '>=';

AndAnd: '&&' | And_;

OrOr: '||' | Or_;

Comma: ',';

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
	| EmptyAtom
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

Newline: ('\r' '\n'? | '\n');

BlockComment: '/*' .*? '*/' -> skip;

LineComment: DivDiv (Newline | ~[_A-Za-z] ~[\r\n]*) -> skip;

PrologComment: { getCharPositionInLine() == 0 }? [ \t]* '%' ~[\r\n]* Newline -> skip;

