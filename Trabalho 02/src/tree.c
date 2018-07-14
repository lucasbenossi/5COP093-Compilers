#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "parser.tab.h"

static void to_dot_recursion(node_t *root, FILE* dot);
static const char* get_label(node_t *node);

node_t* node_create(int type, double value, node_t *left, node_t *right){
	node_t* node = malloc(sizeof(node_t));
	node->type = type;
	node->value = value;
	node->left = left;
	node->right = right;
	return node;
}

void node_destroy(node_t *node){
	if(node){
		free(node);
	}
}

void tree_destroy(node_t *root){
	if(root->left){
		tree_destroy(root->left);
	}
	if(root->right){
		tree_destroy(root->right);
	}
	node_destroy(root);
}

double eval(node_t* root, double x){
	//TODO
	if(root){
		switch (root->type) {
			case PLUS:
			case MINUS:
			case MULTIPLY:
			case DIV:
			case REMAINDER:
			case POWER:
			break;
		}
	}
	return 0;
}

void to_dot(node_t* root){
	FILE* dot = fopen("abstract_syntax_tree.dot", "w");

	fprintf(dot, "digraph \"abstract_syntax_tree\" {\n");



	fprintf(dot, "}\n");

	fclose(dot);
}

static void to_dot_recursion(node_t *root, FILE* dot){

}

static const char* get_label(node_t *node){
	static char number[100];
	switch (node->type) {
		case PLUS: return "+";
		case MINUS: return "-";
		case MULTIPLY: return "*";
		case DIV: return "/";
		case POWER: return "^";
		case REMAINDER: return "%";
		case NUMBER: sprintf(number, "%f", node->value); return number;
		default: return "";
	}
}
