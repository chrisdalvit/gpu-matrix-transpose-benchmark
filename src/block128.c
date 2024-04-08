#include <stdlib.h>
#include <stdio.h>
#include "../lib/matrix_utils.h"
#include "../lib/matrix_stats.h"

#define BLOCK_SIZE 128

void block_transpose_int_matrix(int size, int **mat) {
    int k, l, i, j, tmp;

    for (i = 0; i < size; i += BLOCK_SIZE) {
        for (j = 0; j < size; j += BLOCK_SIZE) {
            for (k = i; k < i + BLOCK_SIZE && k < size; ++k) {
                for (l = k; l < j + BLOCK_SIZE && l < size; ++l) {
                    tmp = mat[l][k];
                    mat[l][k] = mat[k][l];
                    mat[k][l] = tmp;
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    int size = get_matrix_size(argc, argv);
    int** mat = allocate_nested_int_matrix(size);
    init_nested_matrix(size, mat);
    double time = time_transpose(block_transpose_int_matrix, size, mat);
    printf("%f\n", time);
    free_matrix(size, mat);
    return EXIT_SUCCESS;

    return 0;
}