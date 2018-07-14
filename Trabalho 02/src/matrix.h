#ifndef MATRIX_H
#define MATRIX_H

typedef struct _matrix matrix_t;

extern matrix_t* matrix_current;
extern matrix_t* matrix_new;

matrix_t* matrix_create();

void matrix_destroy(matrix_t* matrix);

void matrix_print(matrix_t* matrix);

void matrix_init_new();

void matrix_line_from_stack();

void matrix_stack_push(double value);
double matrix_stack_pop();

#endif
