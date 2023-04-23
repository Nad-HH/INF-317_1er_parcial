#include <stdio.h>
#include <string.h>
#include <mpi.h>
// funcion para verificar si la aplabra es palindromo

int es_palindromo(char* palabra) {
    int len = strlen(palabra);
    for (int i = 0; i < len / 2; i++) {
        if (palabra[i] != palabra[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv) {
    char palabra[100];
    int size, rank, resultado_parcial, resultado_total;

    MPI_Init(&argc, &argv); //iniciamos la ejecucion de MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // numero de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rango del proceso acual
	
    // verificamos que este en el proceso maestro
    if (rank == 0) {   
        printf("Ingresa una palabra: ");
        fflush(stdout);
        scanf("%s", palabra);  //leemos la cadena de caracteres
    }
    
    // se envia a los demas procesos y se indica que se envia una cadena, con tm; max 100
    MPI_Bcast(palabra, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    
    resultado_parcial = es_palindromo(palabra);
    
    //printf("%d",resultado_parcial);
    
    // combina lso resultados parciales de todos los procesos
    MPI_Reduce(&resultado_parcial, &resultado_total, 1, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (resultado_total) {
            printf("VERDAD\n");
        } else {
            printf("FALSO\n");
        }
    }

    MPI_Finalize();

    return 0;
}
