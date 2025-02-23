#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;

        // Each thread prints its square
        printf("Thread %d: Square = %d\n", thread_id, square);

        // Use atomic to safely update the sum
        #pragma omp atomic
        sum += square;
    }

    // Print final sum outside the parallel region
    printf("Sum of squares of thread IDs: %d\n", sum);

    return 0;
}
