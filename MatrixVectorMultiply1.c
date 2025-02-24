#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function for parallel matrix-vector multiplication
void matrix_vector_multiply(int **matrix, int *vector, int *result, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int rows = 4, cols = 4;

    // Allocate memory for matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));

    // Allocate memory for vector and result
    int *vector = (int *)malloc(cols * sizeof(int));
    int *result = (int *)malloc(rows * sizeof(int));

    // Initialize matrix and vector
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i + j + 1; // Example values
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Vector:\n");
    for (int i = 0; i < cols; i++) {
        vector[i] = i + 1; // Example values
        printf("%d ", vector[i]);
    }
    printf("\n");

    // Perform matrix-vector multiplication
    matrix_vector_multiply(matrix, vector, result, rows, cols);

    // Print result
    printf("Result:\n");
    for (int i = 0; i < rows; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
