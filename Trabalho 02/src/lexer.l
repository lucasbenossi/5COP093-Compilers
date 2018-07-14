%option noyywrap
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{

}

%{
	#include "parser.tab.h"
	#include <string.h>
	#include "string.h"
%}

%%

[0-9]+				{return INTEGER;}
[0-9]+"."[0-9]+		{return REAL;}
[xX]				{return X;}
"+"					{return PLUS;}
"-"					{return MINUS;}
"*"					{return MULTIPLY;}
"/"					{return DIV;}
"%"					{return REMAINDER;}
"^"					{return POWER;}
"("					{return L_PAREN;}
")"					{return R_PAREN;}
"sen"				{return SEN;}
"cos"				{return COS;}
"tan"				{return TAN;}
"abs"				{return ABS;}
\n					{return END_OF_LINE;}
"quit"				{return QUIT;}
[ \t]				{/* ignore whitespace */}
.					{}

%%
