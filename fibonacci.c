#include <stdio.h>
#include <omp.h>

// Function to compute Fibonacci numbers using parallelization
long long fibonacci(int n) {
    if (n <= 1) return n;
    long long x, y;

    #pragma omp parallel sections
    {
        #pragma omp section
        x = fibonacci(n - 1);
        
        #pragma omp section
        y = fibonacci(n - 2);
    }
    return x + y;
}

int main() {
    int n = 10; // Compute Fibonacci for n = 10
    long long result;
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    printf("Fibonacci(%d) = %lld\n", n, result);
    return 0;
}
