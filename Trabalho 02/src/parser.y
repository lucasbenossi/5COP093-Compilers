%output "parser.tab.c"
%defines "parser.tab.h"
%locations

%code requires {
	#include "tree.h"
}

%code provides {
	extern int quit;
}

%{
	#include "lexer.yy.h"
	#include "settings.h"
	void yyerror(char *s);
	static void print_about();
%}

%union {
	double double_t;
	int int_t;
	node_t* node;
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
%token NEGATE
%token EQUALS

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
%token EVAL
%token DOT

%token NEW_LINE
%token ERROR

%start start

%type <double_t> number
%type <int_t> on_off
%type <node> exp factor power term x

%%

start:
	a NEW_LINE
;
a:
	command a |
	%empty
;

command:
	SHOW SETTINGS SEMICOLON {show_settings();} |
	RESET SETTINGS SEMICOLON {reset_settings();} |
	QUIT {quit = 1;} |
	SET H_VIEW number COLON number SEMICOLON {set_h_view($3, $5);} |
	SET V_VIEW number COLON number SEMICOLON {set_v_view($3, $5);} |
	SET AXIS on_off SEMICOLON {set_draw_axis($3);} |
	/* plot */
	/* plot( [função] ); */
	/* rpn  */
	SET INTEGRAL_STEPS INTEGER SEMICOLON {set_integral_steps($3);} |
	/* integrate ( [limite inferior] : [limite superior] , [função] );*/
	/* matrix = [ [ valor {, valor} ∗ ] {,[ valor {, valor} ∗ ] } ∗ ]; */
	/* show matrix; */
	/* solve determinant; */
	/* solve linear system; */
	ABOUT SEMICOLON {print_about();} |
	X EQUALS number SEMICOLON {x = $3;} |
	EVAL exp SEMICOLON {print_eval($2, x);} |
	DOT exp SEMICOLON {to_dot($2);}
;

on_off:
	ON {$$ = $1;} |
	OFF {$$ = $1;}
;

exp:
	factor {$$ = $1;} |
	exp PLUS factor {$$ = node_create_binary(PLUS, $1, $3);} |
	exp MINUS factor {$$ = node_create_binary(MINUS, $1, $3);}
;
factor:
	power {$$ = $1;} |
	factor MULTIPLY power {$$ = node_create_binary(MULTIPLY, $1, $3);} |
	factor DIV power {$$ = node_create_binary(DIV, $1, $3);}
;
power:
	term {$$ = $1;} |
	term POWER power {$$ = node_create_binary(POWER, $1, $3);}
;
term:
	number {$$ = node_create_value($1);} |
	SEN L_PAREN exp R_PAREN {$$ = node_create_unary(SEN, $3);} |
	COS L_PAREN exp R_PAREN {$$ = node_create_unary(COS, $3);} |
	TAN L_PAREN exp R_PAREN {$$ = node_create_unary(TAN, $3);} |
	ABS L_PAREN exp R_PAREN {$$ = node_create_unary(ABS, $3);} |
	L_PAREN exp R_PAREN {$$ = $2;} |
	x {$$ = $1;}
;
number:
	INTEGER {$$ = $1;} |
	DOUBLE {$$ = $1;} |
	MINUS INTEGER {$$ = -1 * $2;} |
	MINUS DOUBLE {$$ = -1 * $2;}
;
x:
	X {$$ = node_create_x();} |
	MINUS X {$$ = node_create_unary(NEGATE, node_create_x());}
;

%%

int quit = 0;

void yyerror(char *s){
	if(!lexer_error && !quit){
		printf("\n");
		if(*yytext == '\n'){
			printf("Erro de Sintaxe: [\\n]\n");
		}
		else{
			printf("Erro de Sintaxe: [%s]\n", yytext);
		}
		printf("\n");
	}
}

void print_about(){
	printf("\n");
	printf("+----------------------------------------------+\n");
	printf("|                                              |\n");
	printf("|                Lucas M. Benossi              |\n");
	printf("|                 201600560228                 |\n");
	printf("|                                              |\n");
	printf("+----------------------------------------------+\n");
	printf("\n");
}
