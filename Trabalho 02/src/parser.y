%output "parser.tab.c"
%defines "parser.tab.h"
%locations

%code provides {
	extern int parser_error;
}

%{
	#include "lexer.yy.h"
	#include <stdio.h>
	void yyerror(char *s);
%}

%token TODO

%start programa

%%

TODO

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
