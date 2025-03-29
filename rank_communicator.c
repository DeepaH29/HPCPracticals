#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv); // Initialize MPI

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Define a group with first five ranks
    int ranks[5] = {0, 1, 2, 3, 4};

    MPI_Group world_group, new_group;
    MPI_Comm new_comm;

    // Get the global group
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    // Create a new group with selected ranks
    MPI_Group_incl(world_group, 5, ranks, &new_group);

    // Create a new communicator for the new group
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    if (new_comm != MPI_COMM_NULL) { // If part of the new communicator
        int new_rank, new_size;
        MPI_Comm_rank(new_comm, &new_rank);
        MPI_Comm_size(new_comm, &new_size);

        printf("World Rank: %d -> New Comm Rank: %d (Size: %d)\n", world_rank, new_rank, new_size);
    }

    MPI_Finalize(); // Finalize MPI
    return 0;
}
