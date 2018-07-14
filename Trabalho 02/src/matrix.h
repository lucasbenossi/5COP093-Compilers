#ifndef MATRIX_H
#define MATRIX_H

extern double** matrix;
extern int lin, col;

double** matrix_create();

void matrix_destroy(double** matrix);

void print(double** matrix);

#endif
