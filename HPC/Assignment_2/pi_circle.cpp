#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

double computePi(int num_points, int num_threads) {
    int inside_circle = 0;
    #pragma omp parallel num_threads(num_threads)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        int local_inside_circle = 0;
        #pragma omp for
        for (int i = 0; i < num_points; ++i) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                ++local_inside_circle;
            }
        }
        #pragma omp atomic
        inside_circle += local_inside_circle;
    }
    return 4.0 * inside_circle / num_points;
}

int main() {
    int num_points = 1000000; // Adjust data size
    int num_threads_list[] = {1, 2, 4, 8, 16}; // Different thread counts

    for (int num_threads : num_threads_list) {
        double start_time = omp_get_wtime();
        double pi = computePi(num_points, num_threads);
        double end_time = omp_get_wtime();

        std::cout << "Threads: " << num_threads << "\n";
        std::cout << "Estimated Pi: " << pi << "\n";
        std::cout << "Time Taken: " << end_time - start_time << " seconds\n\n";
    }
    
    return 0;
}

