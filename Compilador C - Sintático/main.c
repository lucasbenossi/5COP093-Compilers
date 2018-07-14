#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"

int main() {
	for(int token = yylex(); token != 0; token = yylex()){
		printf("%d %d %d %d %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, yytext);
	}
}
