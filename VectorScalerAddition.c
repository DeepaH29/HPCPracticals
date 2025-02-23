#include <stdio.h>
#include <omp.h>

#define N 10  // Size of the vector

int main() {
    int vector[N], scalar = 5;

    // Initialize the vector with some values
    for (int i = 0; i < N; i++) {
        vector[i] = i;
    }

    printf("Original Vector:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    // Parallel region for vector-scalar addition
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vector[i] += scalar;
    }

    printf("Vector after Scalar Addition:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    return 0;
}
