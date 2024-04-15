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
        __builtin_prefetch(&mat[(i+1)*size+i]);
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
    init_matrix(size, mat);
    if(debug_mode){
        print_matrix(size, mat);
    }
    double time = time_transpose(naive_transpose_int_matrix, size, mat);
    if(debug_mode){
        for(int i = 0; i < 3*size; i++){
            printf("-");    
        }
        printf("\n");
        print_matrix(size, mat);
        printf("\n");
        printf("Time for transposition: %f\n", time);    

    }
    else {
        printf("%f\n", time);    
    }
    free(mat);
    return EXIT_SUCCESS;
}