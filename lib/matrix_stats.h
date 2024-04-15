#ifndef MATRIX_STATS_H_
#define MATRIX_STATS_H_

double time_transpose(void (*func)(int s, int* m), int size, int* mat);
double compute_effective_bandwidth(int size, double time);

#endif