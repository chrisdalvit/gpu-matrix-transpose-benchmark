#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
    Allocate memory for a matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int** allocate_matrix(int size){
    int** mat = (int **) malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++){
        mat[i] =(int *) malloc(size * sizeof(int));
    }
    return mat;
}

/*
    Initialize matrix with random values.

    params:
        size: Size of the matrix
        mat: Matrix of initialize
    return:
        void
*/
void init_matrix(int size, int** mat) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            mat[j][i] = rand() % 100;
        }
    }
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

/*
    Print a matrix. 
    Matrix entries on the diagonal are printed in color for better orientation.

    params:
        size: Size of the matrix
        mat: Matrix to print
    return:
        void
*/
void print_matrix(int size, int** mat){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                printf(ANSI_COLOR_GREEN "%2d " ANSI_COLOR_RESET, mat[i][j]);
            }
            else {
                printf("%2d ", mat[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
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