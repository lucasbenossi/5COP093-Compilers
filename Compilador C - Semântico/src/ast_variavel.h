#ifndef AST_VARIAVEL_H
#define AST_VARIAVEL_H

#include "object.h"
#include "tipo.h"

typedef union ast_variavel_init_u {
	int int_v;
	char char_v;
} ast_variavel_init_t;

typedef struct ast_variavel_s {
	object_t obj;
	tipo_t tipo;
	char *id;
	ast_variavel_init_t init;
	int ptr_level;
	int array_size;
} ast_variavel_t;

ast_variavel_t *ast_variavel_create_int(char* id, tipo_t tipo);

void ast_variavel_destroy(ast_variavel_t *ast);

#endif
