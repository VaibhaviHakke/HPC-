#include <stdio.h>
#include <omp.h>

int main() {
    double pi = 0.0;
    int num_threads;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        double local_pi = 22.0 / 7.0;

        #pragma omp critical
        {
            pi += local_pi;
        }
    }

    pi /= num_threads;

    printf("Estimated value of Pi using 22/7 with OpenMP: %f\n", pi);

    return 0;
}







