#include <stdio.h>
#include <omp.h>

#define N 1000  


double parallel_dot_product(double A[], double B[], int n) {
    double dot_product = 0.0;
    
    // Parallel region
    #pragma omp parallel
    {
        double local_sum = 0.0;

        // Parallel for loop
        #pragma omp for
        for (int i = 0; i < n; i++) {
            local_sum += A[i] * B[i];
        }

        // Critical section to update the global dot_product
        #pragma omp critical
        {
            dot_product += local_sum;
        }
    }

    return dot_product;
}

int main() {
    double A[N], B[N];

    // Initialize vectors A and B
    for (int i = 0; i < N; i++) {
        A[i] = i + 1; 
        B[i] = (i + 1) * 2; 
    }

    double result = parallel_dot_product(A, B, N);
    printf("Dot Product: %f\n", result);

    return 0;
}

