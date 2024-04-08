#ifndef MATRIX_UTILS_H_
#define MATRIX_UTILS_H_

int** allocate_nested_int_matrix(int size);
int* allocate_flat_int_matrix(int size);
void init_nested_matrix(int size, int** mat);
void print_nested_matrix(int size, int** mat);
int get_matrix_size(int argc, char *argv[]);
void free_matrix(int size, int** matrix);

#endif