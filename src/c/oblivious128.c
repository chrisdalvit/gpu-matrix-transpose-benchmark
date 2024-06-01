#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../../lib/matrix_utils.h"
#include "../../lib/matrix_stats.h"

void transpose_block(int size, int *mat, int row_offset, int col_offset) {
    if (size <= 128) { // Base case, use a simple loop for small matrices
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int tmp = mat[(row_offset + i) * size + (col_offset + j)];
                mat[(row_offset + i) * size + (col_offset + j)] = mat[(row_offset + j) * size + (col_offset + i)];
                mat[(row_offset + j) * size + (col_offset + i)] = tmp;
            }
        }
    } else {
        int m = size / 2; // Divide the matrix into four quadrants

        // Transpose each quadrant recursively
        transpose_block(m, mat, row_offset, col_offset);
        transpose_block(m, mat, row_offset, col_offset + m);
        transpose_block(m, mat, row_offset + m, col_offset);
        transpose_block(m, mat, row_offset + m, col_offset + m);

        // Swap the quadrants to achieve in-place transposition
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                int tmp = mat[(row_offset + i) * size + (col_offset + m + j)];
                mat[(row_offset + i) * size + (col_offset + m + j)] = mat[(row_offset + m + i) * size + (col_offset + j)];
                mat[(row_offset + m + i) * size + (col_offset + j)] = tmp;
            }
        }
    }
}

void transpose(int size, int *mat){
    transpose_block(size, mat, 0, 0);
}

int main(int argc, char **argv) {
    bool debug_mode = is_debug_mode(argc, argv);
    int size = get_matrix_size(argc, argv);
    int* mat = allocate_int_matrix(size);
    init_matrix(size, mat);
    init_matrix(size, mat);
    if(debug_mode){
        print_matrix(size, mat);
    }
    double time = time_transpose(transpose, size, mat);
    double bandwidth = compute_effective_bandwidth(size, time);

    if(debug_mode){
        print_debug_info(size, mat, time, bandwidth);
    }
    else {
        printf("%f,%f\n", time,bandwidth);    
    }
    free(mat);

    return 0;
}
