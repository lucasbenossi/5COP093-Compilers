#include <stdio.h>
#include "lexer.yy.h"

int main() {
	printf("%d\n", yylex());
}
