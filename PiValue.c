#include <stdio.h>
#include <omp.h>

#define N 1000000000  // Data size (larger N gives better accuracy)

int main() {
    double pi = 0.0;
    double step = 1.0 / N;

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:pi)
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= step;
    double end_time = omp_get_wtime();

    printf("Calculated Pi: %.15f\n", pi);
    printf("Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}
