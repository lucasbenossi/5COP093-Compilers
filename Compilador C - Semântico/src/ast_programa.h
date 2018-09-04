#ifndef AST_PROGRAMA_H
#define AST_PROGRAMA_H
#include "object.h"
#include "hash_table.h"

typedef struct _ast_programa{
	object_t obj;
	hash_table_t *ids;
} ast_programa_t;

ast_programa_t *ast_programa_create();

void ast_programa_destroy(ast_programa_t *ast);

#endif
