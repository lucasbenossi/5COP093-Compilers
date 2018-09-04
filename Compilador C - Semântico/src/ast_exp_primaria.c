#include "ast_exp_primaria.h"
#include <stdlib.h>
#include "parser.tab.h"

static ast_exp_primaria_t *ast_exp_primaria_create(){
	ast_exp_primaria_t *ast = malloc(sizeof(ast_exp_primaria_t));
	ast->obj.type = OBJECT_AST_EXP_PRIMARIA;
	return ast;
}

ast_exp_primaria_t *ast_exp_primaria_create_id(char* id){
	ast_exp_primaria_t *ast = ast_exp_primaria_create();
	ast->tipo = IDENTIFIER;
	ast->value.id = id;
	return ast;
}

ast_exp_primaria_t *ast_exp_primaria_create_number(int numero){
	ast_exp_primaria_t *ast = ast_exp_primaria_create();
	ast->tipo = NUMERO;
	ast->value.numero = numero;
	return ast;
}

ast_exp_primaria_t *ast_exp_primaria_create_character(char character){
	ast_exp_primaria_t *ast = ast_exp_primaria_create();
	ast->tipo = CHARACTER;
	ast->value.character = character;
	return ast;
}

ast_exp_primaria_t *ast_exp_primaria_create_string(char* string){
	ast_exp_primaria_t *ast = ast_exp_primaria_create();
	ast->tipo = STRING;
	ast->value.string = string;
	return ast;
}

ast_exp_primaria_t *ast_exp_primaria_create_exp(void* exp){
	ast_exp_primaria_t *ast = ast_exp_primaria_create();
	ast->tipo = EXP;
	ast->value.exp = exp;
	return ast;
}
