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

%union {
	double double_t;
	int int_t;
}

%token <int_t> INTEGER
%token <double_t> DOUBLE
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
%token <int_t> ON
%token <int_t> OFF
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

%type <double_t> double
%type <int_t> on_off

%%

start:
	command NEW_LINE {YYACCEPT;} |
	NEW_LINE {YYACCEPT;}
;

double:
	DOUBLE {$$ = $1;} |
	MINUS DOUBLE {$$ = -1 * $2;}
;

on_off:
	ON {$$ = $1;} |
	OFF {$$ = $1;}
;

command:
	SHOW SETTINGS SEMICOLON {show_settings();} |
	RESET SETTINGS SEMICOLON {reset_settings();} |
	QUIT {quit = 1;} |
	SET H_VIEW double COLON double SEMICOLON {set_h_view($3, $5);} |
	SET V_VIEW double COLON double SEMICOLON {set_v_view($3, $5);} |
	SET AXIS on_off SEMICOLON {set_draw_axis($3);} |
	SET INTEGRAL_STEPS INTEGER SEMICOLON {set_integral_steps($3);}
;

%%

int quit = 0;

void yyerror(char *s){
	if(!quit){
		puts("ta errado");
	}
}
