%output "parser.tab.c"
%defines "parser.tab.h"
%locations

%code provides {
	extern int quit;
}

%{
	#include "lexer.yy.h"
	#include "settings.h"
	void yyerror(char *s);
%}

%define api.value.type {double}

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
%token SEMICOLON
%token ABS

%token SHOW
%token RESET
%token SETTINGS
%token SET
%token H_VIEW
%token V_VIEW
%token AXIS
%token ON
%token OFF
%token PLOT
%token INTEGRAL_STEPS
%token INTEGRATE
%token MATRIX
%token SOLVE
%token DETERMINANT
%token LINEAR_SYSTEM
%token ABOUT
%token QUIT
%token COLON

%token NEW_LINE
%token ERROR

%start start

%%

start:
	command NEW_LINE {YYACCEPT;} |
	NEW_LINE {YYACCEPT;}
;

command:
	SHOW SETTINGS SEMICOLON {show_settings();} |
	RESET SETTINGS SEMICOLON {reset_settings();} |
	QUIT {quit = 1;} |
	SET H_VIEW REAL COLON REAL SEMICOLON {printf("%f %f\n", $3, $5);}
;

%%

int quit = 0;

void yyerror(char *s){
	if(!quit){
		puts("ta errado");
	}
}
