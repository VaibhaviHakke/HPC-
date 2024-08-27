#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int count = 0;  // Track the number of items in the buffer

// Function for the producer thread
void producer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce an item (random number in this case)
        int item = rand() % 100;

        #pragma omp critical  // Ensure only one producer/consumer accesses the buffer at a time
        {
            if (count < BUFFER_SIZE) {
                buffer[count] = item;
                count++;
                printf("Produced: %d, Buffer Count: %d\n", item, count);
            }
        }
    }
}

// Function for the consumer thread
void consumer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item;

        #pragma omp critical  // Ensure only one producer/consumer accesses the buffer at a time
        {
            if (count > 0) {
                item = buffer[count - 1];
                count--;
                printf("Consumed: %d, Buffer Count: %d\n", item, count);
            }
        }
    }
}

int main() {
    // Parallel region with two threads: one producer and one consumer
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer();  // Producer thread
        }

        #pragma omp section
        {
            consumer();  // Consumer thread
        }
    }

    return 0;
}

