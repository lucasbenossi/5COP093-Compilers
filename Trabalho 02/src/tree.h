#ifndef TREE_H
#define TREE_H

typedef struct _node node_t;

extern double x;
extern node_t* function;

node_t* node_create_value(double value);
node_t* node_create_binary(int type, node_t* left, node_t* right);
node_t* node_create_unary(int type, node_t* node);
node_t* node_create_x();

void node_destroy(node_t *node);

void tree_destroy(node_t *root);

double eval(node_t* node, double x);

void to_dot(node_t* node);

void print_eval(node_t* node, double x);

void print_rpn(node_t* root);

#endif
