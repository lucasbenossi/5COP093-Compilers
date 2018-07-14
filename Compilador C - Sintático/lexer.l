%option noyywrap
%option yylineno
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{
	#include "parser.tab.h"
}

%%

"void" {return VOID;}
"int" {return INT;}
"char" {return CHAR;}
"return" {return RETURN;}
"break" {return BREAK;}
"switch" {return SWITCH;}
"case" {return CASE;}
"default" {return DEFAULT;}
"do" {return DO;}
"while" {return WHILE;}
"for" {return FOR;}
"if" {return IF;}
"else" {return ELSE;}
"typedef" {return TYPEDEF;}
"struct" {return STRUCT;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULTIPLY;}
"/" {return DIV;}
"%" {return REMAINDER;}
"++" {return INC;}
"--" {return DEC;}
"&" {return BITWISE_AND;}
"|" {return BITWISE_OR;}
"~" {return BITWISE_NOT;}
"^" {return BITWISE_XOR;}
"!" {return NOT;}
"&&" {return LOGICAL_AND;}
"||" {return LOGICAL_OR;}
"==" {return EQUAL;}
"!=" {return NOT_EQUAL;}
"<" {return LESS_THAN;}
">" {return GREATER_THAN;}
"<=" {return LESS_EQUAL;}
">=" {return GREATER_EQUAL;}
">>" {return R_SHIFT;}
"<<" {return L_SHIFT;}
"=" {return ASSIGN;}
"+=" {return ADD_ASSIGN;}
"-=" {return MINUS_ASSIGN;}
";" {return SEMICOLON;}
"," {return COMMA;}
":" {return COLON;}
"(" {return L_PAREN;}
")" {return R_PAREN;}
"{" {return L_CURLY_BRACKET;}
"}" {return R_CURLY_BRACKET;}
"[" {return L_SQUARE_BRACKET;}
"]" {return R_SQUARE_BRACKET;}
"?" {return TERNARY_CONDITIONAL;}
"#" {return NUMBER_SIGN;}
"->" {return POINT;}
"printf" {return PRINTF;}
"scanf" {return SCANF;}
"define" {return DEFINE;}
"exit" {return EXIT;}

[_A-Za-x][_A-Za-x0-9]* {return IDENTIFIER;}

"0"[0-7]+ {return NUM_OCTAL;}
"0x"[0-9a-f]+ {return NUM_HEXA;}
[0-9]* {return NUM_INTEGER;}

\".*\" {return STRING;}
\'[.]\' {return CHARACTER;}

%%
