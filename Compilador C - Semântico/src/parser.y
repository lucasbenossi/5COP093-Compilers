%output "parser.tab.c"
%defines "parser.tab.h"
%locations

%code provides {
	extern int parser_error;
}

%code requires {
}

%{
	#include "lexer.yy.h"
	#include <stdio.h>
	#include "ast_exp_primaria.h"
	void yyerror(char *s);
%}

%union{
	char* string;
	int integer;
	char character;
	void* pointer;
}

%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINT
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token IDENTIFIER
%token NUM_OCTAL
%token NUM_HEXA
%token NUM_INTEGER
%token STRING
%token CHARACTER
%token NEW_LINE
%token WHITE_SPACE
%token ML_COMMENT_START
%token ML_COMMENT_END
%token SL_COMMENT
%token ERROR
%token END_OF_INPUT

%token EXP
%token NUMERO

%start programa

%%

//Programa
programa:
	declaracoes a |
	funcao a ;
a:
	declaracoes a |
	funcao a |
	%empty ;

//Declaracoes
declaracoes:
	NUMBER_SIGN DEFINE IDENTIFIER expressao |
	decl_variaveis |
	decl_prototipos ;

//Ponteiro
star:
	MULTIPLY star |
	%empty ;

//Tamanho Vetor
size:
	L_SQUARE_BRACKET expressao R_SQUARE_BRACKET size |
	%empty ;

//Funcao
funcao:
	tipo star IDENTIFIER parametros L_CURLY_BRACKET b comandos R_CURLY_BRACKET ;
b:
	decl_variaveis b |
	%empty ;

//Declaracao de Variaveis
decl_variaveis:
	tipo star IDENTIFIER size init c SEMICOLON ;
init:
	ASSIGN exp_atrib |
	%empty ;
c:
	COMMA star IDENTIFIER size init c |
	%empty ;

//Declaracao de Prototipos
decl_prototipos:
	tipo star IDENTIFIER parametros SEMICOLON ;

//Parametros
parametros:
	L_PAREN d R_PAREN ;
d:
	tipo star IDENTIFIER size dd |
	%empty ;
dd:
	COMMA tipo star IDENTIFIER size dd |
	%empty ;

//Tipo
tipo:
	INT |
	CHAR |
	VOID
;

//Bloco
bloco:
	L_CURLY_BRACKET comandos R_CURLY_BRACKET ;

//Comandos
comandos:
	lista_comandos j ;
j:
	lista_comandos j |
	%empty ;

//Lista Comandos
lista_comandos:
	DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON |
	IF L_PAREN expressao R_PAREN bloco ab |
	WHILE L_PAREN expressao R_PAREN bloco |
	FOR L_PAREN ac SEMICOLON ac SEMICOLON ac R_PAREN bloco |
	PRINTF L_PAREN STRING ad R_PAREN SEMICOLON |
	SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON |
	EXIT L_PAREN expressao R_PAREN SEMICOLON |
	RETURN ac SEMICOLON |
	expressao SEMICOLON |
	SEMICOLON |
	bloco ;
ab:
	ELSE bloco |
	%empty ;
ac:
	expressao |
	%empty ;
ad:
	COMMA expressao |
	%empty ;

//Expressao
expressao:
	exp_atrib e ;
e:
	COMMA exp_atrib e |
	%empty ;

//Expressao de Atribuicao
exp_atrib:
	exp_condicional |
	exp_unaria f exp_atrib ;
f:
	ASSIGN |
	ADD_ASSIGN |
	MINUS_ASSIGN ;

//Expressao de Condicional
exp_condicional:
	exp_or_l g ;
g:
	TERNARY_CONDITIONAL expressao COLON exp_condicional |
	%empty ;

//Expressao OR Logico
exp_or_l:
	exp_and_l h ;
h:
	LOGICAL_OR exp_and_l h |
	%empty ;

//Expressao AND Logico
exp_and_l:
	exp_or i ;
i:
	LOGICAL_AND exp_or i |
	%empty ;

//Expressao OR
exp_or:
	exp_xor k ;
k:
	BITWISE_OR exp_xor k |
	%empty ;

//Expressao XOR
exp_xor:
	exp_and l ;
l:
	BITWISE_XOR exp_and l |
	%empty ;

//Expressao AND
exp_and:
	exp_igualdade m ;
m:
	BITWISE_AND exp_igualdade m |
	%empty ;

//Expressao de Igualdade
exp_igualdade:
	exp_relacional o ;
o:
	n exp_relacional o |
	%empty ;
n:
	EQUAL |
	NOT_EQUAL ;

//Expressao Relacional
exp_relacional:
	exp_shift p ;
p:
	q exp_shift p |
	%empty ;
q:
	LESS_THAN |
	LESS_EQUAL |
	GREATER_THAN |
	GREATER_EQUAL ;

//Expressao Shift
exp_shift:
	exp_aditiva r ;
r:
	s exp_aditiva r |
	%empty ;
s:
	L_SHIFT |
	R_SHIFT ;

//Expressao Aditiva
exp_aditiva:
	exp_multiplicativa t ;
t:
	u exp_multiplicativa t |
	%empty ;
u:
	PLUS |
	MINUS ;

//Expressao Multiplicativa
exp_multiplicativa:
	exp_cast v ;
v:
	w exp_cast v |
	%empty ;
w:
	MULTIPLY | DIV | REMAINDER ;

//Expressao Cast
exp_cast:
	exp_unaria |
	L_PAREN tipo star R_PAREN exp_cast ;

//Expressao Unaria
exp_unaria:
	exp_pos_fixa |
	INC exp_unaria |
	DEC exp_unaria |
	ae exp_cast ;
ae:
	BITWISE_AND | MULTIPLY | PLUS | MINUS | BITWISE_NOT | NOT ;

//Expressao Pos-Fixa
exp_pos_fixa:
	exp_primaria |
	exp_pos_fixa aa ;
aa:
	L_SQUARE_BRACKET expressao R_SQUARE_BRACKET |
	INC |
	DEC |
	L_PAREN x R_PAREN ;
x:
	exp_atrib y |
	%empty ;
y:
	COMMA exp_atrib y |
	%empty ;

//Expressao Primaria
exp_primaria:
	IDENTIFIER |
	numero |
	CHARACTER |
	STRING  |
	L_PAREN expressao R_PAREN
;

//Numero
numero:
	NUM_INTEGER | NUM_HEXA | NUM_OCTAL
;

%%

int parser_error = 0;

void yyerror(char *s){
	if(!lexer_error){
		parser_error = 1;

		int line = yylloc.first_line;
		int column = yylloc.first_column;
		if(sl_comment){
			column = sl_comment_column;
		}

		if(returned_token == END_OF_INPUT){
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", line, column);
		}
		else{
			printf("error:syntax:%d:%d: %s\n", line, column, yytext);
		}

		printf("%s", input_line);
		yylex();
		while(returned_token != NEW_LINE && returned_token != END_OF_INPUT){
			printf("%s", yytext);
			yylex();
		}
		printf("\n");

		for(int i = 0; i < column - 1; i++){
			printf(" ");
		}
		printf("^");
	}
}
