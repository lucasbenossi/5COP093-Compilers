#include "matrix.h"
#include <stdlib.h>

double** matrix;
int lin, col;

double** matrix_create(){
	double** matrix = (double**) malloc(10*sizeof(double*));
	for(int i = 0; i < 10; i++){
		matrix[i] = (double*) malloc(10*sizeof(double));
		for(int j = 0; j < 10; j++){
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void matrix_destroy(double** matrix){
	for(int i = 0; i < 10; i++){
		free(matrix[i]);
	}
	free(matrix);
}

void print(double** matrix){
	
}
