#include <stdio.h>
#include <omp.h>

#define ROWS 3
#define COLS 3

void matrix_scalar_multiplication(int matrix[ROWS][COLS], int scalar) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

void print_matrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int scalar = 2;

    printf("Original Matrix:\n");
    print_matrix(matrix);

    matrix_scalar_multiplication(matrix, scalar);

    printf("\nMatrix after scalar multiplication by %d:\n", scalar);
    print_matrix(matrix);

    return 0;
}
