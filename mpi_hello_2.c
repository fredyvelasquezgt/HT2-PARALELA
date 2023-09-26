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
            printf("Uso: mpiexec -n <número_de_procesos> ./mpi_hello_2 <número_de_procesos>\n");
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

    // Mensaje a enviar desde cada proceso al proceso 0
    char message[100];
    snprintf(message, sizeof(message), "Hello from process %d!", rank);

    // Proceso 0 recibe mensajes de todos los demás procesos
    if (rank == 0) {
        for (int source = 1; source < size; source++) {
            MPI_Recv(message, sizeof(message), MPI_CHAR, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proceso 0 recibió mensaje de proceso %d: %s\n", source, message);
        }
    } else {
        // Los demás procesos envían su mensaje al proceso 0
        MPI_Send(message, sizeof(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió mensaje a proceso 0: %s\n", rank, message);
    }

    // Finalizar el entorno de MPI
    MPI_Finalize();

    return 0;
}

