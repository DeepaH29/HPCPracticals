#include <stdio.h>
#include <omp.h>

int main() {
    int total_threads, sum_of_squares = 0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;

        // Print the square of the thread ID
        printf("Thread %d: Square = %d\n", thread_id, square);

        // Use reduction to compute sum of squares safely in parallel
        #pragma omp atomic
        sum_of_squares += square;
    }

    // Print the final sum of squares (only once)
    #pragma omp barrier
    #pragma omp master
    {
        printf("Sum of squares of thread IDs = %d\n", sum_of_squares);
    }

    return 0;
}
