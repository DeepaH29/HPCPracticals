#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, left_neighbor, right_neighbor;
    int send_data, recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    left_neighbor = (rank - 1 + size) % size;
    right_neighbor = (rank + 1) % size;
    send_data = rank;


    MPI_Recv(&recv_data, 1, MPI_INT, left_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&send_data, 1, MPI_INT, right_neighbor, 0, MPI_COMM_WORLD);

    printf("Process %d received data %d from Process %d\n", rank, recv_data, left_neighbor);

    MPI_Finalize();
    return 0;
}
