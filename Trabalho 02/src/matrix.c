#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct _matrix{
	double matrix[10][10];
	int lin, col, j;
};

typedef struct _stack stack_t;
struct _stack{
	double value;
	stack_t *prev;
};

matrix_t* matrix_current = NULL;
matrix_t* matrix_new = NULL;
static stack_t* stack = NULL;

static void print_top_line(int col);

matrix_t* matrix_create(){
	matrix_t* matrix = (matrix_t*) malloc(sizeof(matrix_t));
	matrix->lin = 0;
	matrix->col = 0;
	matrix->j = 0;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			matrix->matrix[i][j] = 0;
		}
	}
	return matrix;
}

void matrix_destroy(matrix_t* matrix){
	if(matrix){
		free(matrix);
	}
}

void matrix_print(matrix_t* matrix){
	printf("\n");

	if(matrix){
		print_top_line(matrix->col);
		for(int i = 0; i < matrix->lin; i++){
			printf("|  ");
			for(int j = 0; j < matrix->col; j++){
				printf("% e ", matrix->matrix[i][j]);
			}
			printf(" |\n");
		}
		print_top_line(matrix->col);
	}
	else{
		printf("No Matrix defined!\n");
	}

	printf("\n");
}

static void print_top_line(int col){
	printf("+-");
	int n = col * 14 + 1;
	for(int i = 0; i < n; i++){
		printf(" ");
	}
	printf("-+\n");
}

void matrix_init_new(){
	if(!matrix_new){
		matrix_new = matrix_create();
	}
}

void matrix_line_from_stack(){
	int i = matrix_new->lin;
	int j = 0;
	while(stack){
		matrix_new->matrix[i][j] = matrix_stack_pop();
		j++;
	}
	if(j > matrix_new->col){
		matrix_new->col = j;
	}
	matrix_new->lin++;
}


void matrix_stack_push(double value){
	stack_t *node = (stack_t*) malloc(sizeof(stack_t));
	node->value = value;
	node->prev = stack;
	stack = node;
}

double matrix_stack_pop(){
	double value = stack->value;
	stack_t* node = stack;
	stack = stack->prev;
	free(node);
	return value;
}
