%option noyywrap
%option yylineno
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{
	#include "parser.tab.h"
}

%%

"a"	{return A;}
"b"	{return B;}
.	{return -2;}

%%
