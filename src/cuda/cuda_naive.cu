#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cuda_runtime.h>

#include "../../lib/helper_cuda.h"

#define REPETITIONS 50

__global__
void device_transpose(int size, int* mat){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            int tmp = mat[i*size+j];
            mat[i*size+j] = mat[j*size+i];
            mat[j*size+i] = tmp;
        }
    }
}

void host_transpose(int size, int* mat){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            int tmp = mat[i*size+j];
            mat[i*size+j] = mat[j*size+i];
            mat[j*size+i] = tmp;
        }
    }
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

int main(int argc, char **argv){
    
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
    
    // Allocate matrix memory on host and device
    int* host_mat = (int *) malloc(size * size * sizeof(int));
    int* dev_mat;
    checkCudaErrors( cudaMalloc(&dev_mat, size * size * sizeof(int)) );

    // Init matrix
    init_matrix(size, host_mat);

    // Time host
    for(int t=0; t < REPETITIONS; t++){
        init_matrix(size, host_mat);
        if(debug_mode){
            print_matrix(size, host_mat);
        }
        clock_t begin = clock();
        host_transpose(size, host_mat);
        clock_t end = clock();
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        double bandwidth = compute_effective_bandwidth(size, time);
        if(debug_mode){
            print_debug_info(size, host_mat, time, bandwidth);
        }
        else {
            printf("%f,%f,host,0,0\n", time, bandwidth);    
        }
    }

    // Time device
    for(int t=0; t < REPETITIONS; t++){
        init_matrix(size, host_mat);
        if(debug_mode){
            print_matrix(size, host_mat);
        }

        clock_t begin = clock();
        cudaMemcpy(dev_mat, host_mat, size * size * sizeof(int), cudaMemcpyHostToDevice);
        device_transpose<<<1,1>>>(size, dev_mat);
        checkCudaErrors( cudaDeviceSynchronize() );
        cudaMemcpy(host_mat, dev_mat, size * size * sizeof(int), cudaMemcpyDeviceToHost);
        clock_t end = clock();

        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        double bandwidth = compute_effective_bandwidth(size, time);
        if(debug_mode){
            print_debug_info(size, host_mat, time, bandwidth);
        }
        else {
            printf("%f,%f,device,0,0\n", time, bandwidth);    
        }
    }

    cudaFree(dev_mat);
    free(host_mat);

    return 0;
}