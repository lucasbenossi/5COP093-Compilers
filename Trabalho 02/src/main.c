#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"
#include "string.h"
#include "tree.h"

int main() {
	// do{
	// 	printf(">");
	//
	// 	char line[1000];
	// 	fgets(line, 1000, stdin);
	//
	// 	YY_BUFFER_STATE buffer = yy_scan_string(line);
	//
	// 	yyparse();
	//
	// 	yy_delete_buffer(buffer);
	// } while(!quit);

	node_t *node = node_create(PLUS, 0, node_create(MULTIPLY, 0, node_create(NUMBER, 3.0, NULL, NULL), node_create(NUMBER, 5.0, NULL, NULL)), node_create(NUMBER, 10.0, NULL, NULL));

	to_dot(node);

	tree_destroy(node);
}
