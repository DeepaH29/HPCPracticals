#include <stdio.h>
#include <omp.h>

long long fibonacci(int n) {
    if (n <= 1) return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y)
    y = fibonacci(n - 2);

    #pragma omp taskwait  // Ensures both tasks complete before adding

    return x + y;
}

int main() {
    int n = 10;
    long long result;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single  // Ensures only one thread initiates tasks
        result = fibonacci(n);
    }

    double end_time = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}

