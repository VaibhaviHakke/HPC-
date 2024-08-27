#include <stdio.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 1000000

int main() {
    int array[ARRAY_SIZE];
    int total_sum = 0;
    clock_t start, end;
    double duration;

    // Initialize the array with values
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1; // Array values from 1 to ARRAY_SIZE
    }

    start = clock();

    #pragma omp parallel
    {
        int local_sum = 0;

        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            local_sum += array[i];
        }

        #pragma omp atomic
        total_sum += local_sum; // Atomic update to total_sum
    }

    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Total Sum: %d\n", total_sum);
    printf("Atomic Execution Time: %f seconds\n", duration);

    return 0;
}

