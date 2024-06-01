#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cuda_runtime.h>

#include "../../lib/helper_cuda.h"

#define REPETITIONS 50

__global__ void transpose(int *matrix, int size) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < size && y < size && x < y) {
        int idx1 = y * size + x;
        int idx2 = x * size + y;
        int temp = matrix[idx1];
        matrix[idx1] = matrix[idx2];
        matrix[idx2] = temp;
    }
}

/*
    Initialize matrix with random values between 0 and 99.

    params:
        size: Size of the matrix
        mat: Transposed matrix
    return:
        void
*/
void init_matrix(int size, int* mat){
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
            printf("%2d ", mat[i*size + j]);
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

/*
    Compute the effective bandwidth of a matrix transposition. 

    params:
        size: Size of the matrix
        time: Time needed to transpose the matrix
    return:
        The effective bandwidth in bytes
*/
double compute_effective_bandwidth(int size, double time){
    int num_matrix_elements = size * size;
    int matrix_size_in_bytes = num_matrix_elements * sizeof(int);
    // Size we read and write every element, the amount of moved bytes is twice the total bytes of the matrix
    double moved_bytes = 2.0*matrix_size_in_bytes; 
    return moved_bytes / time;
}

int main(int argc, char **argv) {

    // Check if argumnet is present
    if(argc < 2){
        printf("One argument expected. But got %d arguments.\n", argc-1);
        exit(EXIT_FAILURE);
    }

    // Check if debug mode is activated
    bool debug_mode = false;
    if(argc >= 3 && strcmp(argv[2], "--debug") == 0){
        debug_mode = true;
    }
    
    // Compute matrix size
    int input = atoi(argv[1]);
    if(input == 0){
        printf("Provide a valid numeric value. Not '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    int size = (int) pow(2.0, input);

    int* h_matrix = (int *) malloc(size * size * sizeof(int));
    init_matrix(size, h_matrix);

    int *d_matrix;
    cudaMalloc(&d_matrix, size * size * sizeof(int));

    dim3 blockSize(16, 16);
    dim3 gridSize((size + blockSize.x - 1) / blockSize.x, (size + blockSize.y - 1) / blockSize.y);

    for(int t=0; t < REPETITIONS; t++){
        init_matrix(size, h_matrix);
        if(debug_mode){
            print_matrix(size, h_matrix);
        }
        clock_t begin = clock();
        cudaMemcpy(d_matrix, h_matrix, size * size * sizeof(int), cudaMemcpyHostToDevice);
        transpose<<<gridSize, blockSize>>>(d_matrix, size);
        cudaDeviceSynchronize();
        cudaMemcpy(h_matrix, d_matrix, size * size * sizeof(int), cudaMemcpyDeviceToHost);
        clock_t end = clock();
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        double bandwidth = compute_effective_bandwidth(size, time);
        if(debug_mode){
            print_debug_info(size, h_matrix, time, bandwidth);
        }
        else {
            printf("%f,%f,device,0,0\n", time, bandwidth);    
        }
    }

    cudaFree(d_matrix);
    free(h_matrix);

    return 0;
}
