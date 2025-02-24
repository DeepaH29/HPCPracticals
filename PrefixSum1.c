#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compute prefix sum using OpenMP
void prefix_sum(int *arr, int *prefix, int n) {
    int i;
    int num_threads;

    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
    }

    int *offsets = (int *)malloc(num_threads * sizeof(int));

    // Step 1: Compute local prefix sum
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = (n + num_threads - 1) / num_threads;
        int start = id * chunk_size;
        int end = (start + chunk_size > n) ? n : start + chunk_size;

        if (start < n) {
            prefix[start] = arr[start];
            for (i = start + 1; i < end; i++) {
                prefix[i] = prefix[i - 1] + arr[i];
            }
            offsets[id] = prefix[end - 1];  // Store last value of each chunk
        }
    }

    // Step 2: Compute global offsets
    for (i = 1; i < num_threads; i++) {
        offsets[i] += offsets[i - 1];
    }

    // Step 3: Apply offsets to adjust final prefix sum
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = (n + num_threads - 1) / num_threads;
        int start = id * chunk_size;
        int end = (start + chunk_size > n) ? n : start + chunk_size;

        if (id > 0 && start < n) {
            for (i = start; i < end; i++) {
                prefix[i] += offsets[id - 1];
            }
        }
    }

    free(offsets);
}

int main() {
    int n = 10;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int prefix[n];

    printf("Input Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    prefix_sum(arr, prefix, n);

    printf("Prefix Sum:  ");
    for (int i = 0; i < n; i++)
        printf("%d ", prefix[i]);
    printf("\n");

    return 0;
}
