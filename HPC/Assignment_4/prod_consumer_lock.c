#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int count = 0;

omp_lock_t buffer_lock;

void producer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;

        while (1) {
            omp_set_lock(&buffer_lock);
            if (count < BUFFER_SIZE) {  // Check if buffer is not full
                buffer[count] = item;
                count++;
                printf("Produced: %d, Buffer Count: %d\n", item, count);
                omp_unset_lock(&buffer_lock);
                break;
            }
            omp_unset_lock(&buffer_lock);
        }
    }
}

void consumer() {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item;

        while (1) {
            omp_set_lock(&buffer_lock);
            if (count > 0) {  // Check if buffer is not empty
                item = buffer[count - 1];
                count--;
                printf("Consumed: %d, Buffer Count: %d\n", item, count);
                omp_unset_lock(&buffer_lock);
                break;
            }
            omp_unset_lock(&buffer_lock);
        }
    }
}

int main() {
    omp_init_lock(&buffer_lock);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer();
        }

        #pragma omp section
        {
            consumer();
        }
    }

    omp_destroy_lock(&buffer_lock);
    return 0;
}

