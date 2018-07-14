#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"

int main() {
	if(yyparse() == 0){
		printf("SUCCESSFUL COMPILATION.");
	}

	// for(int token = yylex(); token != 0; token = yylex()){
	// 	printf("%s\n", yytext);
	// }

	destroy_string(input_line);
}
