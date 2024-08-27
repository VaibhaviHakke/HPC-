#include <stdio.h>
#include <omp.h>

void vector_scalar_addition(double* vector, double scalar, int n) {
    // Parallelize this loop with OpenMP
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int n = 1000; // Size of the vector
    double vector[n];
    double scalar = 5.0;

    // Initialize the vector with some values
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    // Perform vector scalar addition
    vector_scalar_addition(vector, scalar, n);

    // Print the first 10 elements of the result for verification
    for (int i = 0; i < 10; i++) {
        printf("%f ", vector[i]);
    }
    printf("\n");

    return 0;
}

