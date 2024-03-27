#include <stdio.h>
#include <stdlib.h>
#include "../matrix_utils.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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