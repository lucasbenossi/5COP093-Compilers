#include <stdio.h>
#include "lexer.yy.h"
#include "parser.tab.h"
#include "string.h"
#include "tree.h"

int main() {
	do{
		printf(">");

		char line[1000];
		fgets(line, 1000, stdin);

		YY_BUFFER_STATE buffer = yy_scan_string(line);

		yyparse();

		yy_delete_buffer(buffer);
	} while(!quit);

	// node_t *node = node_create_binary(PLUS, node_create_binary(MULTIPLY, node_create_value(3), node_create_value(5)), node_create_value(10));
	// node = node_create_binary(PLUS, node, node_create_value(40));
	// node = node_create_binary(MULTIPLY, node_create_x(), node);
	//
	// to_dot(node);
	// printf("%f\n", eval(node, 2));
	//
	// tree_destroy(node);
}
