%defines

%{
	#include "lexer.yy.h"
	#include <stdio.h>
	void yyerror(char *s);
%}

%token A
%token B

%start s

%%

s:
	A s B
|	A B
;

%%

void yyerror(char *s){
	return;
}
