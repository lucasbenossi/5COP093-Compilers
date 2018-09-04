#ifndef AST_EXP_PRIMARIA
#define AST_EXP_PRIMARIA
#include "object.h"

typedef struct ast_exp_primaria_s{
	object_t obj;
	int tipo;
	union value_u {
		char* id;
		int numero;
		char character;
		char* string;
		void* exp;
	} value;
} ast_exp_primaria_t;

ast_exp_primaria_t *ast_exp_primaria_create_id(char *id);
ast_exp_primaria_t *ast_exp_primaria_create_number(int numero);
ast_exp_primaria_t *ast_exp_primaria_create_character(char character);
ast_exp_primaria_t *ast_exp_primaria_create_string(char *string);
ast_exp_primaria_t *ast_exp_primaria_create_exp(void* exp);

#endif
