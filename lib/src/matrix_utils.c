#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../matrix_utils.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
    Determine if program is executed in debug mode. 

    params:
        argc: Number of command line arguments
        argv: Command line arguments
    return:
        Boolean indicating wheter the program is executed in debug mode
*/
bool is_debug_mode(int argc, char *argv[]){
    if(argc < 3){
        return false;
    }
    return strcmp(argv[2], "--debug") == 0;
}

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
    if(argc < 2){
        printf("One argument expected. But got %d arguments.\n", argc-1);
        exit(EXIT_FAILURE);
    }
    int input = atoi(argv[1]);
    if(input == 0){
        printf("Provide a valid numeric value. Not '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    return (int) pow(2.0, input);
}

/*
    Allocate memory for a flat integer matrix of given size.

    params:
        size: Size of the matrix
    return:
        Pointer to the allocated matrix
*/
int* allocate_int_matrix(int size){
    int* mat = (int *) malloc(size * size * sizeof(int));
    return mat;
}

/*
    Initialize flat matrix with random values.

    params:
        size: Size of the matrix
        mat: Matrix of initialize
    return:
        void
*/
void init_matrix(int size, int* mat) {
    for(int i = 0; i < size * size; i++){
        mat[i] = rand() % 100;
    }
}

/*
    Print the matrix on the terminal.

    params:
        size: Size of the matrix
        mat: Matrix of initialize
    return:
        void
*/
void print_matrix(int size, int* mat){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                printf(ANSI_COLOR_GREEN "%2d " ANSI_COLOR_RESET, mat[i*size + j]);
            }
            else {
                printf("%2d ", mat[i*size + j]);
            }
        }
        printf("\n");
    }
}

/*
    Print information for debugging on the terminal.

    params:
        size: Size of the matrix
        mat: Transposed matrix
        time: Time needed for transposition
    return:
        void
*/
void print_debug_info(int size, int *mat, double time, double bandwidth){
    for(int i = 0; i < 3*size; i++){
        printf("-");    
    }
    printf("\n");
    print_matrix(size, mat);
    printf("\n");
    printf("Time for transposition: %f\n", time);
    printf("Effective bandwidth: %.15f\n", bandwidth);
}