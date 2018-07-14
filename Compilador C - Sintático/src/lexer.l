%option noyywrap
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{
	#include "parser.tab.h"
	#include <string.h>
	#include "string.h"
	extern char* line;
}

%{
	char* line = NULL;

	#define YY_USER_INIT init_lexer();

	static void init_lexer(){
		line = create_string("");
	}

	static void update_loc(){
		static int line = 1;
		static int column = 1;

		yylloc.first_line = line;
		yylloc.first_column = column;

		char *c;
		for(c = yytext; *(c+1) != '\0'; c++){
			if(*c == '\n'){
				column = 1;
				line++;
			}
			else{
				column++;
			}
		}

		yylloc.last_line = line;
		yylloc.last_column = column;

		if(*c == '\n'){
			line++;
			column = 1;
		}
		else{
			column++;
		}
	}

	static void concat_line(int token){
		if(token != NEW_LINE){
			cat_string(&line, yytext);
		}
		else{
			/*puts(line);*/
			rep_string(&line, "");
		}
	}

	static int token_action(int token){
		update_loc();
		concat_line(token);
		return token;
	}
%}


%%

"void" {return token_action(VOID);}
"int" {return token_action(INT);}
"char" {return token_action(CHAR);}
"return" {return token_action(RETURN);}
"break" {return token_action(BREAK);}
"switch" {return token_action(SWITCH);}
"case" {return token_action(CASE);}
"default" {return token_action(DEFAULT);}
"do" {return token_action(DO);}
"while" {return token_action(WHILE);}
"for" {return token_action(FOR);}
"if" {return token_action(IF);}
"else" {return token_action(ELSE);}
"typedef" {return token_action(TYPEDEF);}
"struct" {return token_action(STRUCT);}
"+" {return token_action(PLUS);}
"-" {return token_action(MINUS);}
"*" {return token_action(MULTIPLY);}
"/" {return token_action(DIV);}
"%" {return token_action(REMAINDER);}
"++" {return token_action(INC);}
"--" {return token_action(DEC);}
"&" {return token_action(BITWISE_AND);}
"|" {return token_action(BITWISE_OR);}
"~" {return token_action(BITWISE_NOT);}
"^" {return token_action(BITWISE_XOR);}
"!" {return token_action(NOT);}
"&&" {return token_action(LOGICAL_AND);}
"||" {return token_action(LOGICAL_OR);}
"==" {return token_action(EQUAL);}
"!=" {return token_action(NOT_EQUAL);}
"<" {return token_action(LESS_THAN);}
">" {return token_action(GREATER_THAN);}
"<=" {return token_action(LESS_EQUAL);}
">=" {return token_action(GREATER_EQUAL);}
">>" {return token_action(R_SHIFT);}
"<<" {return token_action(L_SHIFT);}
"=" {return token_action(ASSIGN);}
"+=" {return token_action(ADD_ASSIGN);}
"-=" {return token_action(MINUS_ASSIGN);}
";" {return token_action(SEMICOLON);}
"," {return token_action(COMMA);}
":" {return token_action(COLON);}
"(" {return token_action(L_PAREN);}
")" {return token_action(R_PAREN);}
"{" {return token_action(L_CURLY_BRACKET);}
"}" {return token_action(R_CURLY_BRACKET);}
"[" {return token_action(L_SQUARE_BRACKET);}
"]" {return token_action(R_SQUARE_BRACKET);}
"?" {return token_action(TERNARY_CONDITIONAL);}
"#" {return token_action(NUMBER_SIGN);}
"->" {return token_action(POINT);}
"printf" {return token_action(PRINTF);}
"scanf" {return token_action(SCANF);}
"define" {return token_action(DEFINE);}
"exit" {return token_action(EXIT);}

[_A-Za-x][_A-Za-x0-9]* {return token_action(IDENTIFIER);}

"0"[0-7]+ {return token_action(NUM_OCTAL);}
"0x"[0-9a-f]+ {return token_action(NUM_HEXA);}
[0-9]* {return token_action(NUM_INTEGER);}

\".*\" {return token_action(STRING);}
\'[.]\' {return token_action(CHARACTER);}

[\n] {token_action(NEW_LINE);}
[ \t] {token_action(WHITE_SPACE);}
. {token_action(ERROR);}

%%
