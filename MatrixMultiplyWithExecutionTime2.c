#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 1000  // Maximum matrix size

// Function to multiply matrices using OpenMP with either static or dynamic scheduling
void multiply_matrices(int N, int** A, int** B, int** C, int is_static) {
    double start_time, end_time;

    printf("\nRunning with %s scheduling...\n", is_static ? "STATIC" : "DYNAMIC");
    start_time = omp_get_wtime();  // Start time

    if (is_static) {
        // Static scheduling
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    } else {
        // Dynamic scheduling
        #pragma omp parallel for schedule(dynamic, 4)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    end_time = omp_get_wtime();  // End time
    printf("Execution Time for %dx%d matrix: %f seconds\n", N, N, end_time - start_time);
}

// Function to dynamically allocate a 2D matrix
int** allocate_matrix(int N) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

// Function to initialize matrices with random values
void initialize_matrices(int N, int** A, int** B) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;  // Random numbers 0-9
            B[i][j] = rand() % 10;
        }
    }
}

// Function to free dynamically allocated memory
void free_matrix(int N, int** M) {
    for (int i = 0; i < N; i++) {
        free(M[i]);
    }
    free(M);
}

int main() {
    // Different matrix sizes to test
    int sizes[] = {100, 500, 1000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_tests; i++) {
        int N = sizes[i];

        printf("\nTesting matrix size: %dx%d\n", N, N);

        // Allocate matrices on the heap
        int** A = allocate_matrix(N);
        int** B = allocate_matrix(N);
        int** C = allocate_matrix(N);

        initialize_matrices(N, A, B);

        // Test Static Scheduling
        multiply_matrices(N, A, B, C, 1);

        // Test Dynamic Scheduling
        multiply_matrices(N, A, B, C, 0);

        // Free memory
        free_matrix(N, A);
        free_matrix(N, B);
        free_matrix(N, C);
    }

    return 0;
}
