#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define VECTOR_SIZE 200  // Define vector size

// Function to perform scalar addition on a 1D vector
void vector_scalar_addition(int chunk_size) {
    int A[VECTOR_SIZE];
    int scalar = 5;
    
    // Initialize vector with random values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = rand() % 100;
    }
    
    double start_time = omp_get_wtime(); // Start timing
    
    // Perform scalar addition using OpenMP with STATIC scheduling and varying chunk sizes
    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] += scalar;
    }
    
    double end_time = omp_get_wtime(); // End timing
    printf("Chunk Size: %d, Time taken: %f seconds\n", chunk_size, end_time - start_time);
}

int main() {
    srand(time(NULL));
    int chunk_sizes[] = {1, 5, 10, 20, 50};
    
    for (int i = 0; i < 5; i++) {
        vector_scalar_addition(chunk_sizes[i]);
    }
    
    return 0;
}
