#include <stdlib.h>
#include <stdio.h>
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
void naive_transpose_int_matrix(int size, int** mat){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            int tmp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = tmp;
        }
    }
}

int main(int argc, char** argv){
    int size = get_matrix_size(argc, argv);
    int** mat = allocate_int_matrix(size);
    init_matrix(size, mat);
    double time = time_transpose(naive_transpose_int_matrix, size, mat);
    printf("%f\n", time);
    free_matrix(size, mat);
    return EXIT_SUCCESS;
}