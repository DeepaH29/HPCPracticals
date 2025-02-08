#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;

    // Ask the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Set the number of OpenMP threads
    omp_set_num_threads(num_threads);

    // Sequential Execution: Print "Hello, World" num_threads times
    printf("\nSequential Execution:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Sequential: Hello, World\n");
    }

    // Parallel Execution using OpenMP
    printf("\nParallel Execution:\n");
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Parallel (Thread %d): Hello, World\n", thread_id);
    }

    return 0;
}
