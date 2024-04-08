#include <stdlib.h>
#include <stdio.h>
#include "../lib/matrix_utils.h"
#include "../lib/matrix_stats.h"

#define BLOCK_SIZE 128

void block_transpose_int_matrix(int size, int **mat) {
    int i, j, ii, jj, tmp;

    for (ii = 0; ii < size; ii += BLOCK_SIZE) {
        for (jj = 0; jj < size; jj += BLOCK_SIZE) {
            for (i = ii; i < ii + BLOCK_SIZE && i < size; ++i) {
                for (j = i; j < jj + BLOCK_SIZE && j < size; ++j) {
                    tmp = mat[j][i];
                    mat[j][i] = mat[i][j];
                    mat[i][j] = tmp;
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    int size = get_matrix_size(argc, argv);
    int** mat = allocate_int_matrix(size);
    init_matrix(size, mat);
    double time = time_transpose(block_transpose_int_matrix, size, mat);
    printf("%f\n", time);
    free_matrix(size, mat);
    return EXIT_SUCCESS;

    return 0;
}