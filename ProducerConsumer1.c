#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10  // Total number of items to produce/consume

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in buffer
int in = 0, out = 0;  // Buffer index pointers

// Producer function
void producer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = i + 1;  // Producing an item

        // Wait if buffer is full
        while (count == BUFFER_SIZE);

        #pragma omp critical
        {
            buffer[in] = item;
            printf("Produced: %d at index %d\n", item, in);
            in = (in + 1) % BUFFER_SIZE;
            count++;
        }
    }
}

// Consumer function
void consumer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item;

        // Wait if buffer is empty
        while (count == 0);

        #pragma omp critical
        {
            item = buffer[out];
            printf("Consumed: %d from index %d\n", item, out);
            out = (out + 1) % BUFFER_SIZE;
            count--;
        }
    }
}

int main() {
    // Using two threads: one for producer, one for consumer
    #pragma omp parallel sections
    {
        #pragma omp section
        producer();

        #pragma omp section
        consumer();
    }
    
    return 0;
}
