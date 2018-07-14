#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"
#include "string.h"

int main() {
	do{
		printf(">");
		yyparse();
	} while(!quit);
}
