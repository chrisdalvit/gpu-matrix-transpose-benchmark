#ifndef MATRIX_UTILS_H_
#define MATRIX_UTILS_H_

int* allocate_int_matrix(int size);
void init_matrix(int size, int* mat);
int get_matrix_size(int argc, char *argv[]);
bool is_debug_mode(int argc, char *argv[]);
void print_matrix(int size, int* mat);
void print_debug_info(int size, int *mat, double time);

#endif