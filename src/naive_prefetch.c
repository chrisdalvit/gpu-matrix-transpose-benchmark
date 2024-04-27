#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../lib/matrix_utils.h"
#include "../lib/matrix_stats.h"

/*
    Transpose matrix.

    params:
        size: Size of matrix
        mat: Matrix to transpose
    return:
        void
*/
void naive_transpose_int_matrix(int size, int* mat){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            int tmp = mat[i*size+j];
            mat[i*size+j] = mat[j*size+i];
            mat[j*size+i] = tmp;
            __builtin_prefetch(&mat[j*size+(i+1)], 1, 1);
            __builtin_prefetch(&mat[(i+1)*size+j], 1, 1);
        }
    }
}

int main(int argc, char** argv){
    bool debug_mode = is_debug_mode(argc, argv);
    int size = get_matrix_size(argc, argv);
    int* mat = allocate_int_matrix(size);
    init_matrix(size, mat);
    if(debug_mode){
        print_matrix(size, mat);
    }
    double time = time_transpose(naive_transpose_int_matrix, size, mat);
    double bandwidth = compute_effective_bandwidth(size, time);

    if(debug_mode){
        print_debug_info(size, mat, time, bandwidth);
    }
    else {
        printf("%f,%f\n", time, bandwidth);    
    }
    free(mat);
    return EXIT_SUCCESS;
}