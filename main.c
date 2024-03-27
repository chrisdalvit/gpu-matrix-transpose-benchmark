#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lib/matrix_utils.h"

/*
    Extract the matrix size for command line arguments. 
    Exit with failure if wrong number of arguments was passed to program.

    params:
        argc: Number of command line arguments
        argv: Command line arguments
    return:
        Matrix size computed from the command line argument
*/
int get_matrix_size(int argc, char *argv[]){
    if(argc != 2){
        printf("One argument expected. But got %d arguments.\n", argc-1);
        exit(EXIT_FAILURE);
    }
    return (int) pow(2.0, atoi(argv[1]));
}

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
    int** mat = allocate_matrix(size);
    init_matrix(size, mat);
    print_matrix(size, mat);
    transpose_matrix(size, mat);
    print_matrix(size, mat);
    return EXIT_SUCCESS;
}