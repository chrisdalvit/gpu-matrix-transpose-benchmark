#include <stdlib.h>
#include <stdio.h>
#include "lib/matrix_utils.h"

/*
    Transpose matrix.

    params:
        size: Size of matrix
        mat: Matrix to transpose
    return:
        void
*/
void transpose_matrix(int size, int** mat){
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
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
    //print_matrix(size, mat);
    transpose_matrix(size, mat);
    //print_matrix(size, mat);
    free(mat);
    return EXIT_SUCCESS;
}