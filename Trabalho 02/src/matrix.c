#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct _matrix{
	double matrix[10][10];
	int lin, col;
};

matrix_t* matrix_current = NULL;
matrix_t* matrix_new = NULL;
static int matrix_i = 0;
static int matrix_j = 0;
static int matrix_err = 0;

static void print_top_line(int col);

matrix_t* matrix_create(){
	matrix_t* matrix = (matrix_t*) malloc(sizeof(matrix_t));
	matrix->lin = 0;
	matrix->col = 0;
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
	matrix_new = matrix_create();
	matrix_i = 0;
	matrix_j = 0;
	matrix_err = 0;
}

void matrix_insert_value(double value){
	if(matrix_i < 10 && matrix_j < 10){
		matrix_new->matrix[matrix_i][matrix_j] = value;
		if(matrix_i + 1 > matrix_new->lin){
			matrix_new->lin = matrix_i + 1;
		}
		if(matrix_j + 1 > matrix_new->col){
			matrix_new->col = matrix_j + 1;
		}
	}
	else{
		matrix_err = 1;
	}
	matrix_j++;
}

void matrix_insert_line(){
	matrix_j = 0;
	matrix_i++;
}

void matrix_finalize(){
	if(!matrix_err){
		matrix_destroy(matrix_current);
		matrix_current = matrix_new;
		matrix_new = NULL;
	}
	else{
		matrix_destroy(matrix_new);
		matrix_new = NULL;
		printf("\n");
		printf("ERROR: Matrix limits out of boundaries.\n");
		printf("\n");
	}
}
