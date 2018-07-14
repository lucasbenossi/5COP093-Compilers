%option noyywrap
%option outfile="lexer.yy.c"
%option header-file="lexer.yy.h"

%top{
	extern char* input_line;
	extern int lexer_error;
	extern int ml_comment, ml_comment_line, ml_comment_column;
	extern int sl_comment, sl_comment_line, sl_comment_column;
	extern int returned_token;
}

%{
	#include "parser.tab.h"
	#include <string.h>
	#include "string.h"
	#define YY_USER_INIT init_lexer();
	static void init_lexer();
	static int token_action(int token);
	static void update_loc();
	static void concat_line(int token);
%}

%%

"void" {if(token_action(VOID)) return VOID;}
"int" {if(token_action(INT)) return INT;}
"char" {if(token_action(CHAR)) return CHAR;}
"return" {if(token_action(RETURN)) return RETURN;}
"break" {if(token_action(BREAK)) return BREAK;}
"switch" {if(token_action(SWITCH)) return SWITCH;}
"case" {if(token_action(CASE)) return CASE;}
"default" {if(token_action(DEFAULT)) return DEFAULT;}
"do" {if(token_action(DO)) return DO;}
"while" {if(token_action(WHILE)) return WHILE;}
"for" {if(token_action(FOR)) return FOR;}
"if" {if(token_action(IF)) return IF;}
"else" {if(token_action(ELSE)) return ELSE;}
"typedef" {if(token_action(TYPEDEF)) return TYPEDEF;}
"struct" {if(token_action(STRUCT)) return STRUCT;}
"+" {if(token_action(PLUS)) return PLUS;}
"-" {if(token_action(MINUS)) return MINUS;}
"*" {if(token_action(MULTIPLY)) return MULTIPLY;}
"/" {if(token_action(DIV)) return DIV;}
"%" {if(token_action(REMAINDER)) return REMAINDER;}
"++" {if(token_action(INC)) return INC;}
"--" {if(token_action(DEC)) return DEC;}
"&" {if(token_action(BITWISE_AND)) return BITWISE_AND;}
"|" {if(token_action(BITWISE_OR)) return BITWISE_OR;}
"~" {if(token_action(BITWISE_NOT)) return BITWISE_NOT;}
"^" {if(token_action(BITWISE_XOR)) return BITWISE_XOR;}
"!" {if(token_action(NOT)) return NOT;}
"&&" {if(token_action(LOGICAL_AND)) return LOGICAL_AND;}
"||" {if(token_action(LOGICAL_OR)) return LOGICAL_OR;}
"==" {if(token_action(EQUAL)) return EQUAL;}
"!=" {if(token_action(NOT_EQUAL)) return NOT_EQUAL;}
"<" {if(token_action(LESS_THAN)) return LESS_THAN;}
">" {if(token_action(GREATER_THAN)) return GREATER_THAN;}
"<=" {if(token_action(LESS_EQUAL)) return LESS_EQUAL;}
">=" {if(token_action(GREATER_EQUAL)) return GREATER_EQUAL;}
">>" {if(token_action(R_SHIFT)) return R_SHIFT;}
"<<" {if(token_action(L_SHIFT)) return L_SHIFT;}
"=" {if(token_action(ASSIGN)) return ASSIGN;}
"+=" {if(token_action(ADD_ASSIGN)) return ADD_ASSIGN;}
"-=" {if(token_action(MINUS_ASSIGN)) return MINUS_ASSIGN;}
";" {if(token_action(SEMICOLON)) return SEMICOLON;}
"," {if(token_action(COMMA)) return COMMA;}
":" {if(token_action(COLON)) return COLON;}
"(" {if(token_action(L_PAREN)) return L_PAREN;}
")" {if(token_action(R_PAREN)) return R_PAREN;}
"{" {if(token_action(L_CURLY_BRACKET)) return L_CURLY_BRACKET;}
"}" {if(token_action(R_CURLY_BRACKET)) return R_CURLY_BRACKET;}
"[" {if(token_action(L_SQUARE_BRACKET)) return L_SQUARE_BRACKET;}
"]" {if(token_action(R_SQUARE_BRACKET)) return R_SQUARE_BRACKET;}
"?" {if(token_action(TERNARY_CONDITIONAL)) return TERNARY_CONDITIONAL;}
"#" {if(token_action(NUMBER_SIGN)) return NUMBER_SIGN;}
"->" {if(token_action(POINT)) return POINT;}
"printf" {if(token_action(PRINTF)) return PRINTF;}
"scanf" {if(token_action(SCANF)) return SCANF;}
"define" {if(token_action(DEFINE)) return DEFINE;}
"exit" {if(token_action(EXIT)) return EXIT;}
[_A-Za-x][_A-Za-x0-9]* {if(token_action(IDENTIFIER)) return IDENTIFIER;}
"0"[0-7]+ {if(token_action(NUM_OCTAL)) return NUM_OCTAL;}
"0x"[0-9a-f]+ {if(token_action(NUM_HEXA)) return NUM_HEXA;}
[0-9]* {if(token_action(NUM_INTEGER)) return NUM_INTEGER;}
\".*\" {if(token_action(STRING)) return STRING;}
\'[.]\' {if(token_action(CHARACTER)) return CHARACTER;}

"/*" {if(token_action(ML_COMMENT_START)) return ML_COMMENT_START;}
"*/" {if(token_action(ML_COMMENT_END)) return ML_COMMENT_END;}
"//".* {if(token_action(SL_COMMENT)) return SL_COMMENT;}
[\n] {if(token_action(NEW_LINE)) return NEW_LINE;}
[ \t]* {if(token_action(WHITE_SPACE)) return WHITE_SPACE;}
. {if(token_action(ERROR)) return ERROR;}
<<EOF>> {if(token_action(END_OF_INPUT)) return 0;}

%%

char* input_line = NULL;
int lexer_error = 0;
int ml_comment = 0, ml_comment_line, ml_comment_column;
int sl_comment = 0, sl_comment_line, sl_comment_column;
int returned_token = 0;

static void init_lexer(){
	input_line = create_string("");
}

static int token_action(int token){
	returned_token = token;
	update_loc();
	concat_line(token);

	if(!parser_error){
		if(token == ML_COMMENT_START && !ml_comment){
			ml_comment = 1;
			ml_comment_line = yylloc.first_line;
			ml_comment_column = yylloc.first_column;
			return 0;
		}
		else if(token == ML_COMMENT_END){
			ml_comment = 0;
			return 0;
		}
		else if(token == SL_COMMENT){
			sl_comment = 1;
			sl_comment_line = yylloc.first_line;
			sl_comment_column = yylloc.first_column;
			return 0;
		}
		else if(token == NEW_LINE){
			sl_comment = 0;
			return 0;
		}
		else if(token == WHITE_SPACE){
			return 0;
		}
		else if(token == ERROR){
			if(!ml_comment){
				printf("error:lexical:%d:%d: %s", yylloc.first_line, yylloc.first_column, yytext);
				lexer_error = 1;
			}
			else{
				return 0;
			}
		}
		else if(token == END_OF_INPUT && ml_comment){
			printf("error:lexical:%d:%d: unterminated comment", ml_comment_line, ml_comment_column);
			lexer_error = 1;
		}
		else if(ml_comment){
			return 0;
		}
	}

	return 1;
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
		cat_string(&input_line, yytext);
	}
	else{
		rep_string(&input_line, "");
	}
}
