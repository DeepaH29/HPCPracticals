#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int large_data[1000000];  // Large array

if (world_rank == 0) {
    MPI_Send(&large_data, 1000000, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(&large_data, 1000000, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
} 
else if (world_rank == 1) {
    MPI_Send(&large_data, 1000000, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Recv(&large_data, 1000000, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}


    MPI_Finalize();
    return 0;
}
