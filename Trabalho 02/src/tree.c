#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parser.tab.h"
#include "settings.h"

struct _node{
	int type;
	double value;
	struct _node *left;
	struct _node *right;
};

double x = 0;
node_t* function = NULL;

static node_t* node_create(int type, double value, node_t *left, node_t *right);
static void to_dot_nodes(node_t* node, FILE* dot);
static void to_dot_edges(node_t* node, FILE* dot);
static const char* get_label(node_t *node);
static void print_rpn_line(node_t *node);

static node_t* node_create(int type, double value, node_t *left, node_t *right){
	node_t* node = malloc(sizeof(node_t));
	node->type = type;
	node->value = value;
	node->left = left;
	node->right = right;
	return node;
}

node_t* node_create_value(double value){
	return node_create(DOUBLE, value, NULL, NULL);
}

node_t* node_create_binary(int type, node_t* left, node_t* right){
	return node_create(type, 0, left, right);
}

node_t* node_create_unary(int type, node_t* node){
	return node_create(type, 0, node, NULL);
}

node_t* node_create_x(){
	return node_create(X, 0, NULL, NULL);
}

void node_destroy(node_t *node){
	if(node){
		free(node);
	}
}

void tree_destroy(node_t *root){
	if(root){
		if(root->left){
			tree_destroy(root->left);
		}
		if(root->right){
			tree_destroy(root->right);
		}
		node_destroy(root);
	}
}

double eval(node_t* node, double x){
	if(node){
		switch (node->type) {
			case DOUBLE: return node->value;
			case PLUS: return eval(node->left,x) + eval(node->right,x);
			case MINUS: return eval(node->left,x) - eval(node->right,x);
			case MULTIPLY: return eval(node->left,x) * eval(node->right,x);
			case DIV: return eval(node->left,x) / eval(node->right,x);
			case POWER: return pow(eval(node->left,x), eval(node->right,x));
			case REMAINDER: return (int)eval(node->left,x) % (int)eval(node->right,x);
			case SEN: return sin(eval(node->left,x));
			case COS: return cos(eval(node->left,x));
			case TAN: return tan(eval(node->left,x));
			case ABS: return fabs(eval(node->left,x));
			case X: return x;
		}
	}
	return 0;
}

void to_dot(node_t* node){
	FILE* dot = fopen("ast.dot", "w");

	fprintf(dot, "digraph \"abstract_syntax_tree\" {\n");
	fprintf(dot, "\tnode [shape=circle]\n");

	to_dot_nodes(node, dot);
	to_dot_edges(node, dot);

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
		case DOUBLE: sprintf(number, "%f", node->value); return number;
		case PLUS: return "+";
		case MINUS: return "-";
		case MULTIPLY: return "*";
		case DIV: return "/";
		case POWER: return "^";
		case REMAINDER: return "%";
		case SEN: return "sen";
		case COS: return "cos";
		case TAN: return "tan";
		case ABS: return "abs";
		case X: return "x";
	}
	return "";
}

void print_eval(node_t* node, double x){
	printf("\n");
	printf("%f\n", eval(node, x));
	printf("\n");
}

void print_rpn(node_t* root){
	printf("\n");
	print_rpn_line(root);
	printf("\n\n");
}

static void print_rpn_line(node_t *node){
	if(node){
		print_rpn_line(node->left);
		print_rpn_line(node->right);
		printf("%s ", get_label(node));
	}
}

void integrate(double lower, double upper, node_t *node){
	double width = (upper - lower) / settings.integral_steps;
	printf("\n");
	if(lower > upper){
		printf("ERROR: lower limit must be smaller than upper limit\n");
	}
	else{
		double sum = 0;
		for(int i = 0; i < settings.integral_steps; i++){
			double x = lower + i * width;
			double area = eval(node, x) * width;
			sum += area;
		}
		printf("%f\n", sum);
	}
	printf("\n");
}
