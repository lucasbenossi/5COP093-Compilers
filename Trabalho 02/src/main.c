#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"
#include "tree.h"
#include "matrix.h"

int main() {
	do{
		printf(">");
		init_lexer();

		char line[1000];
		fgets(line, 1000, stdin);

		YY_BUFFER_STATE buffer = yy_scan_string(line);

		yyparse();

		yy_delete_buffer(buffer);
	} while(!quit);

	tree_destroy(function);
	matrix_destroy(matrix_current);
}
