#include <stdio.h>
#include <omp.h>

static long num_steps = 1000;
double step;

int main() {
    int i, nthreads;
    double pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;

        double partial_sum = 0.0;
        for (i = id; i < num_steps; i += nthrds) {
            x = (i+0.5)*step;
            partial_sum += 4.0/(1.0+x*x);
        }

        #pragma omp critical
        sum += partial_sum;
    }

    pi = step * sum;
    printf("pi = %f\n", pi);

    return 0;
}
