#ifndef MATRIX_H
#define MATRIX_H

typedef struct _matrix matrix_t;

extern matrix_t* matrix_current;
extern matrix_t* matrix_new;

matrix_t* matrix_create();
void matrix_destroy(matrix_t* matrix);
void matrix_print(matrix_t* matrix);
void matrix_clone(matrix_t* from, matrix_t* to);

void matrix_init_new();
void matrix_insert_value(double value);
void matrix_insert_line();
void matrix_finalize();

void gauss();
void determinant();

#endif
