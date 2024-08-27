#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int array[ARRAY_SIZE];
    long long total_sum = 0;

    // Initialize the array with values
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1; // Array values from 1 to ARRAY_SIZE
    }

    // Calculate the sum of the array elements in parallel
    #pragma omp parallel reduction(+:total_sum)
    {
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            total_sum += array[i];
        }
    }

    printf("Total Sum: %lld\n", total_sum);
    return 0;
}




