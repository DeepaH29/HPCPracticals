#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 1000  // Define a maximum size for static allocation

// Function to compare two integers (for ascending order)
int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to compare two integers (for descending order)
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// Function to compute the minimum scalar product using OpenMP
long long min_scalar_product(int vec1[], int vec2[], int n) {
    // Sort vec1 in ascending order
    qsort(vec1, n, sizeof(int), compare_asc);
    // Sort vec2 in descending order
    qsort(vec2, n, sizeof(int), compare_desc);
    
    long long min_product = 0;
    
    // Compute dot product in parallel
    #pragma omp parallel for reduction(+:min_product)
    for (int i = 0; i < n; i++) {
        min_product += (long long)vec1[i] * vec2[i];
    }
    
    return min_product;
}

int main() {
    int n;
    printf("Enter the size of vectors (max %d): ", MAX_SIZE);
    scanf("%d", &n);
    
    if (n > MAX_SIZE) {
        printf("Size exceeds maximum limit of %d.\n", MAX_SIZE);
        return 1;
    }
    
    int vec1[MAX_SIZE], vec2[MAX_SIZE];
    
    printf("Enter elements of first vector: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vec1[i]);
    }
    
    printf("Enter elements of second vector: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vec2[i]);
    }
    
    long long result = min_scalar_product(vec1, vec2, n);
    printf("Minimum Scalar Product: %lld\n", result);
    
    return 0;
}
