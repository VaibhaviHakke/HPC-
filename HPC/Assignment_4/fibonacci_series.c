#include <stdio.h>
#include <omp.h>

// Recursive Fibonacci function
int fib(int n) {
    int x, y;

    if (n <= 1) {
        return n;
    } else {
        #pragma omp task shared(x) firstprivate(n)
        x = fib(n - 1);

        #pragma omp task shared(y) firstprivate(n)
        y = fib(n - 2);

        // Synchronize tasks
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n = 10;  // Fibonacci number to compute
    int result;

    // Begin parallel region with a single thread initiating the Fibonacci computation
    #pragma omp parallel num_threads(4)  // Specify the number of threads
    {
        #pragma omp single  // Ensure only one thread initiates the recursive tasks
        {
            result = fib(n);
        }
    }

    printf("Fibonacci of %d is %d\n", n, result);
    return 0;
}

