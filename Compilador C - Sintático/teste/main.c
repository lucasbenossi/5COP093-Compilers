#include <stdio.h>
#include "parser.tab.h"

int main() {
	if(yyparse() == 0){
		printf("ok\n");
	}
	else{
		printf("error\n");
	}
}
