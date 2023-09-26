#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Inicializar el entorno de MPI
    MPI_Init(&argc, &argv);

    // Obtener el rango (identificador) del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el número total de procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verificar si se proporcionó la cantidad correcta de argumentos en línea de comandos
    if (argc != 2) {
        if (rank == 0) {
            printf("Uso: mpiexec -n <número_de_procesos> ./mpi_hello <número_de_procesos>\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Obtener la cantidad de procesos desde la línea de comandos
    int num_processes = atoi(argv[1]);

    // Verificar si el número de procesos especificado coincide con el número real de procesos
    if (num_processes != size) {
        if (rank == 0) {
            printf("El número de procesos especificado no coincide con el número real de procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Imprimir el mensaje desde cada proceso
    printf("Hello World, I'm process %d of %d!\n", rank, size);

    // Finalizar el entorno de MPI
    MPI_Finalize();

    return 0;
}

