#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"

int main() {
	if(yyparse() == 0){
		printf("SUCCESSFUL COMPILATION.");
	}
}
