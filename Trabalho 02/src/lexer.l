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
