#include <stdio.h>
#include <mpi.h>

// funcion fibo
void fibonacci(int start, int end, unsigned long long* result) {
    unsigned long long a = 0, b = 1;
    for (int i = 0; i < end; i++) {
        if (i >= start) {
            result[i-start] = a;
        }
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv); // se inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rango
    MPI_Comm_size(MPI_COMM_WORLD, &size); //tama;o

    int elements_per_process = 1000 / size;
    // matriz de enteros
    unsigned long long result[elements_per_process];

    // indice inicial y final del proceso actual 
    int start = rank * elements_per_process;
    int end = start + elements_per_process;

    fibonacci(start, end, result);

    unsigned long long final_result[1000];
    // recopila los resultados parciales
    MPI_Gather(result, elements_per_process, MPI_UNSIGNED_LONG_LONG, final_result, elements_per_process, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < 1000; i++) {
            printf("%llu ", final_result[i]); //mostramos los valores largos sin signo
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
