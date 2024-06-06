#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cuda_runtime.h>

#include "../../lib/helper_cuda.h"


#define REPETITIONS 50
#define TILE_DIM 32

__global__ void transpose(int size, int* matrix) {
    __shared__ int tile[TILE_DIM][TILE_DIM+1];

    int x = blockIdx.x * TILE_DIM + threadIdx.x;
    int y = blockIdx.y * TILE_DIM + threadIdx.y;

    for (int i = 0; i < TILE_DIM; i += blockDim.y) {
        if (x < size && y + i < size) {
            tile[threadIdx.y + i][threadIdx.x] = matrix[(y + i) * size + x];
        }
    }

    __syncthreads();

    for (int i = 0; i < TILE_DIM; i += blockDim.y) {
        if (x < size && y + i < size) {
            matrix[(y + i) * size + x] = tile[threadIdx.x][threadIdx.y + i];
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
float compute_effective_bandwidth(int size, float time){
    int num_matrix_elements = size * size;
    int matrix_size_in_bytes = num_matrix_elements * sizeof(int);
    // Size we read and write every element, the amount of moved bytes is twice the total bytes of the matrix
    float moved_bytes = 2.0*matrix_size_in_bytes; 
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

int main(int argc, char** argv) {
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
    
    dim3 dimBlock(TILE_DIM, TILE_DIM);
    dim3 dimGrid((size + TILE_DIM - 1) / TILE_DIM, (size + TILE_DIM - 1) / TILE_DIM);
    // Init matrix
    init_matrix(size, host_mat);

    // warm up
    checkCudaErrors( cudaMemcpy(dev_mat, host_mat, size * size * sizeof(int), cudaMemcpyHostToDevice) );
    transpose<<<dimGrid, dimBlock>>>(size, dev_mat);
    checkCudaErrors( cudaDeviceSynchronize() );
    checkCudaErrors( cudaMemcpy(host_mat, dev_mat, size * size * sizeof(int), cudaMemcpyDeviceToHost) );

    // Time device
    for(int t=0; t < REPETITIONS; t++){
        init_matrix(size, host_mat);
        if(debug_mode){
            print_matrix(size, host_mat);
        }

        checkCudaErrors( cudaMemcpy(dev_mat, host_mat, size * size * sizeof(int), cudaMemcpyHostToDevice) );
        clock_t begin = clock();
        transpose<<<dimGrid,dimBlock>>>(size, dev_mat);
        checkCudaErrors( cudaDeviceSynchronize() );
        clock_t end = clock();
        checkCudaErrors( cudaMemcpy(host_mat, dev_mat, size * size * sizeof(int), cudaMemcpyDeviceToHost) );
        float time = (float)(end - begin) / CLOCKS_PER_SEC;
    
        float bandwidth = compute_effective_bandwidth(size, time);
        if(debug_mode){
            print_debug_info(size, host_mat, time, bandwidth);
        }
        else {
            printf("%f,%f,gpu_tiled\n", time, bandwidth);    
        }
    }

    checkCudaErrors( cudaFree(dev_mat) );
    free(host_mat);

    return 0;
}
