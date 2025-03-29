 #include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize MPI

    int world_rank;
    int world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get number of processes

    printf("Hello from process %d out of %d!\n", world_rank, world_size);

    MPI_Finalize(); // Finalize MPI
    return 0;
}
