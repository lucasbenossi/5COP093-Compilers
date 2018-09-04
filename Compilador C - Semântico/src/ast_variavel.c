#include "ast_variavel.h"
#include <stdlib.h>
#include "string.h"

ast_variavel_t *ast_variavel_create_int(char* id, tipo_t tipo){
	ast_variavel_t *ast = malloc(sizeof(ast_variavel_t));
	ast->obj.type = OBJECT_AST_VARIAVEL;

	ast->id = string_create(id);
	ast->tipo = tipo;

	return ast;
}

void ast_variavel_destroy(ast_variavel_t *ast){
	free(ast);
}
