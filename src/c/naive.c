#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../lib/matrix_utils.h"
#include "../../lib/matrix_stats.h"

#define REPETITIONS 50

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
        }
    }
}

int main(int argc, char** argv){
    bool debug_mode = is_debug_mode(argc, argv);
    int size = get_matrix_size(argc, argv);
    int* mat = allocate_int_matrix(size);

    for(int t=0; t<REPETITIONS; t++){
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
            printf("%f,%f,cpu_naive\n", time, bandwidth);    
        }
    }
    
    free(mat);
    return EXIT_SUCCESS;
}