%output "parser.tab.c"
%defines "parser.tab.h"
%locations

%code provides {
	extern int quit;
}

%{
	#include "lexer.yy.h"
	void yyerror(char *s);
%}

%token INTEGER
%token REAL
%token X
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token POWER
%token L_PAREN
%token R_PAREN
%token SEN
%token COS
%token TAN
%token ABS

%token QUIT

%token END_OF_LINE

%start start

%%

start:
	token END_OF_LINE {printf("lido token\n"); YYACCEPT;} |
	END_OF_LINE {YYACCEPT;}|
	QUIT {quit = 1; YYACCEPT;}
;

token:
	PLUS |
	MINUS
;
%%

int quit = 0;

void yyerror(char *s){
	puts("ta errado");
}
