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
static void print_error_no_matrix_defined();
static void elimination(matrix_t *matrix);

matrix_t* matrix_create(){
	matrix_t* matrix = malloc(sizeof(matrix_t));
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
	if(matrix){
		printf("\n");
		print_top_line(matrix->col);
		for(int i = 0; i < matrix->lin; i++){
			printf("|  ");
			for(int j = 0; j < matrix->col; j++){
				printf("% e ", matrix->matrix[i][j]);
			}
			printf(" |\n");
		}
		print_top_line(matrix->col);
		printf("\n");
	}
	else{
		print_error_no_matrix_defined();
	}
}

static void print_top_line(int col){
	printf("+-");
	int n = col * 14 + 1;
	for(int i = 0; i < n; i++){
		printf(" ");
	}
	printf("-+\n");
}

static void print_error_no_matrix_defined(){
	printf("\n");
	printf("No Matrix defined!\n");
	printf("\n");
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

void gauss(){
	if(!matrix_current){
		print_error_no_matrix_defined();
		return;
	}

	int m = matrix_current->lin;
	int n = matrix_current->col;

	if(m != n - 1){
		printf("\n");
		printf("Matrix format incorrect!\n");
		printf("\n");
		return;
	}

	matrix_t matrix;
	matrix.lin = m;
	matrix.col = n;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			matrix.matrix[i][j] = matrix_current->matrix[i][j];
		}
	}

	for(int i = 0; i < m; i++){
		for(int k = i+1; k < m; k++){
			double term = matrix.matrix[k][i] / matrix.matrix[i][i];
			for(int j = 0; j < n; j++){
				matrix.matrix[k][j] = matrix.matrix[k][j] - term * matrix.matrix[i][j];
			}
		}
	}

	matrix_print(&matrix);

	if(matrix.matrix[m-1][n-2] == 0){
		printf("\n");
		if(matrix.matrix[m-1][n-1] == 0){
			printf("SPI - The Linear System has infinitely many solutions\n");
		}
		else{
			printf("SI - The Linear System has no solution\n");
		}
		printf("\n");
		return;
	}

	double x[n-1];
	for(int i = m-1; i >= 0; i--){
		x[i] = matrix.matrix[i][n-1];
		for(int j = i+1; j < n-1; j++){
			x[i] = x[i] - matrix.matrix[i][j] * x[j];
		}
		x[i] = x[i] / matrix.matrix[i][i];
	}

	printf("\n");
	printf("Matrix x:\n");
	printf("\n");
	for(int i = 0; i < n-1; i++){
		printf("%f\n", x[i]);
	}
	printf("\n");
}

static void elimination(matrix_t *matrix){

}
