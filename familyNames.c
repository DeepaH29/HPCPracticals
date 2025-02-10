#include <stdio.h>
#include <omp.h>

int main() {
    // Define an array of family member names
    const char *family_members[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    int num_members = sizeof(family_members) / sizeof(family_members[0]);
    
    // Set the number of threads equal to the number of family members
    #pragma omp parallel num_threads(num_members)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d says: %s\n", thread_id, family_members[thread_id]);
    }
    
    return 0;
}
