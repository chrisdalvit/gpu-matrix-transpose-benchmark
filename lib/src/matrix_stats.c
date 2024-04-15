#include <time.h>

double time_transpose(void (*func)(int s, int* m), int size, int* mat){
    clock_t begin = clock();
    (*func)(size, mat);
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

double compute_effective_bandwidth(int size, double time){
    int num_matrix_elements = size * size;
    int matrix_size_in_bytes = num_matrix_elements * sizeof(int);
    // Size we read and write every element, the amount of moved bytes is twice the total bytes of the matrix
    int moved_bytes = 2*matrix_size_in_bytes; 
    return (moved_bytes / 1000000000.0) / time;
}