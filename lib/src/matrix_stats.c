#include <time.h>

double time_transpose(void (*func)(int s, int* m), int size, int* mat){
    clock_t begin = clock();
    (*func)(size, mat);
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}