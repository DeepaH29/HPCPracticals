#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0;
    int n = 20;  // First 20 natural numbers

    #pragma omp parallel 
    {
        int partial_sum = 0;
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Each thread computes a portion of the sum
        for (int i = thread_id + 1; i <= n; i += num_threads) {
            partial_sum += i;
        }

        // Print partial sum calculated by each thread
        printf("Thread %d: Partial Sum = %d\n", thread_id, partial_sum);

        // Use lastprivate to assign the last thread's value to total_sum
        #pragma omp critical
        {
            total_sum += partial_sum;
        }
    }

    // Print the final sum
    printf("Total sum of first %d natural numbers: %d\n", n, total_sum);
    
    return 0;
}
