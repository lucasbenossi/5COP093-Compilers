#ifndef TREE_H
#define TREE_H

typedef struct _node node_t;

node_t* node_create(int type, double value, node_t *left, node_t *right);
void node_destroy(node_t *node);

void tree_destroy(node_t *root);

double eval(node_t* root, double x);

void to_dot(node_t* root);

#endif
