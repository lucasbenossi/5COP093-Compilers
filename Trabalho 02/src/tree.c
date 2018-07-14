#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parser.tab.h"

struct _node{
	int type;
	double value;
	struct _node *left;
	struct _node *right;
};

static void to_dot_nodes(node_t* node, FILE* dot);
static void to_dot_edges(node_t* node, FILE* dot);
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
	if(root){
		switch (root->type) {
			case NUMBER: return root->value;
			case PLUS: return eval(root->left,x) + eval(root->right,x);
			case MINUS: return eval(root->left,x) - eval(root->right,x);
			case MULTIPLY: return eval(root->left,x) * eval(root->right,x);
			case DIV: return eval(root->left,x) / eval(root->right,x);
			case REMAINDER: return (int)eval(root->left,x) % (int)eval(root->right,x);
			case POWER: return pow(eval(root->left,x), eval(root->right,x));
			default: return 0;
		}
	}
	return 0;
}

void to_dot(node_t* root){
	FILE* dot = fopen("abstract_syntax_tree.dot", "w");

	fprintf(dot, "digraph \"abstract_syntax_tree\" {\n");
	fprintf(dot, "\tnode [shape=circle]\n");

	to_dot_nodes(root, dot);
	to_dot_edges(root, dot);

	fprintf(dot, "}\n");

	fclose(dot);
}

static void to_dot_nodes(node_t* node, FILE* dot){
	if(node){
		fprintf(dot, "\t\"%p\" [label=\"%s\"]\n", node, get_label(node));
		to_dot_nodes(node->left, dot);
		to_dot_nodes(node->right, dot);
	}
}

static void to_dot_edges(node_t* node, FILE* dot){
	if(node->left){
		fprintf(dot, "\t\"%p\" -> \"%p\"\n", node, node->left);
		to_dot_edges(node->left, dot);
	}
	if(node->right){
		fprintf(dot, "\t\"%p\" -> \"%p\"\n", node, node->right);
		to_dot_edges(node->right, dot);
	}
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
		case NUMBER: sprintf(number, "%.2f", node->value); return number;
		default: return "";
	}
}
