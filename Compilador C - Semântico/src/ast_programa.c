#include "ast_programa.h"
#include <stdlib.h>
#include "object.h"
#include "hash_table.h"

ast_programa_t *ast_programa_create(){
    ast_programa_t *ast = malloc(sizeof(ast_programa_t));
	ast->obj.type = OBJECT_AST_PROGRAMA;
	ast->ids = hash_table_create(100);
    return ast;
}

void ast_programa_destroy(ast_programa_t *ast){
	hash_table_destroy(ast->ids);
	free(ast);
}
