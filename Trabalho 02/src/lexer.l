%option noyywrap
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{

}

%{
	#include "parser.tab.h"
%}

%%

[0-9]+				{yylval.int_t = strtod(yytext, NULL); return INTEGER;}
[0-9]+"."[0-9]+		{yylval.double_t = strtod(yytext, NULL); return DOUBLE;}
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
";"					{return SEMICOLON;}
\n					{return NEW_LINE;}
"show"				{return SHOW;}
"reset"				{return RESET;}
"settings"			{return SETTINGS;}
"set"				{return SET;}
"h_view"			{return H_VIEW;}
"v_view"			{return V_VIEW;}
"axis"				{return AXIS;}
"on"				{yylval.int_t = 1; return ON;}
"off"				{yylval.int_t = 0; return OFF;}
"plot"				{return PLOT;}
"integral_steps"	{return INTEGRAL_STEPS;}
"integrate"			{return INTEGRATE;}
"matrix"			{return MATRIX;}
"solve"				{return SOLVE;}
"determinant"		{return DETERMINANT;}
"linear_system"		{return LINEAR_SYSTEM;}
"about"				{return ABOUT;}
"quit"				{return QUIT;}
"eval"				{return EVAL;}
"dot"				{return DOT;}
":"					{return COLON;}
"="					{return EQUALS;}
[ \t]				{/* ignore */}
.					{return ERROR;}

%%
