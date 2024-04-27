#include <time.h>

/*
    Compute the time a transpose function. 

    params:
        func: Function pointer to transpose function
        size: Size of the matrix to transpose
        mat: Matrix to transpose
    return:
        The time needed for the transpose operation
*/
double time_transpose(void (*func)(int s, int* m), int size, int* mat){
    clock_t begin = clock();
    (*func)(size, mat);
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

/*
    Compute the effective bandwidth of a matrix transposition. 

    params:
        size: Size of the matrix
        time: Time needed to transpose the matrix
    return:
        The effective bandwidth in bytes
*/
double compute_effective_bandwidth(int size, double time){
    int num_matrix_elements = size * size;
    int matrix_size_in_bytes = num_matrix_elements * sizeof(int);
    // Size we read and write every element, the amount of moved bytes is twice the total bytes of the matrix
    double moved_bytes = 2.0*matrix_size_in_bytes; 
    return moved_bytes / time;
}