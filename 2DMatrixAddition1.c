#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_SIZE 2000  // Maximum matrix size

// Function to perform matrix addition
void matrix_addition(int size, int num_threads) {
    // Dynamically allocate matrices
    int **A = (int **)malloc(size * sizeof(int *));
    int **B = (int **)malloc(size * sizeof(int *));
    int **C = (int **)malloc(size * sizeof(int *));
    
    for (int i = 0; i < size; i++) {
        A[i] = (int *)malloc(size * sizeof(int));
        B[i] = (int *)malloc(size * sizeof(int));
        C[i] = (int *)malloc(size * sizeof(int));
    }
    
    // Initialize matrices with random values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }
    
    double start_time = omp_get_wtime(); // Start timing
    
    // Perform matrix addition using OpenMP with varying threads
    #pragma omp parallel for num_threads(num_threads) collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    double end_time = omp_get_wtime(); // End timing
    printf("Matrix size: %d, Threads: %d, Time taken: %f seconds\n", size, num_threads, end_time - start_time);

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main() {
    srand(time(NULL));
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {2, 4, 8};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            matrix_addition(sizes[i], threads[j]);
        }
    }
    
    return 0;
}
