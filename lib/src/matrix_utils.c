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
    Allocate memory for a matrix of given size and datatype.

    params:
        size: Size of the matrix
        dtype_ptr_size: Size of a pointer to the matrix datatype
        dtype_size: Size of the matrix datatype
    return:
        Pointer to the allocated matrix
*/
int** allocate_matrix(int size, unsigned long dtype_ptr_size, unsigned long dtype_size){
    int** mat = (int **) malloc(size * dtype_ptr_size);
    for(int i = 0; i < size; i++){
        mat[i] =(int *) malloc(size * dtype_size);
    }
    return mat;
}

/*
    Allocate memory for a integer matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int** allocate_int_matrix(int size){
    return allocate_matrix(size, sizeof(int*), sizeof(int));
}

/*
    Allocate memory for a integer matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int** allocate_float_matrix(int size){
    return allocate_matrix(size, sizeof(float*), sizeof(float));
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