#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i;
    double pi, pi_local = 0.0;
    int start, end;
    int n = 1000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_process = n / size;

    start = rank * elements_per_process + 1;
    end = (rank + 1) * elements_per_process;
    if (rank == size - 1) {
        end = n;
    }

    for (i = start; i <= end; i++) {
        if (i % 2 == 0) {
            pi_local -= 1.0 / (2 * i - 1);
        } else {
            pi_local += 1.0 / (2 * i - 1);
        }
    }

    MPI_Reduce(&pi_local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi *= 4.0;
        printf("Valor de pi: %f\n", pi);
    }

    MPI_Finalize();

    return 0;
}
