#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../matrix_utils.h"

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
    Allocate memory for a nested integer matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int** allocate_nested_int_matrix(int size){
    int** mat = (int **) malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++){
        mat[i] =(int *) malloc(size * sizeof(int));
    }
    return mat;
}

/*
    Allocate memory for a flat integer matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int* allocate_flat_int_matrix(int size){
    int* mat = (int *) malloc(size * sizeof(int));
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
void init_nested_matrix(int size, int** mat) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            mat[j][i] = rand() % 100;
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
void print_nested_matrix(int size, int** mat){
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

/*
    Free matrix memory.

    params:
        size: Size of the matrix
        matrix: Matrix to free
    return:
        void
*/
void free_matrix(int size, int** matrix){
    for(int i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}