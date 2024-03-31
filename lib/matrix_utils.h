#ifndef MATRIX_UTILS_H_
#define MATRIX_UTILS_H_

int** allocate_int_matrix(int size);
int** allocate_float_matrix(int size); //TODO: does not work correctly
void init_matrix(int size, int** mat);
void print_matrix(int size, int** mat);
int get_matrix_size(int argc, char *argv[]);
void free_matrix(int size, int** matrix);

#endif