#include <stdio.h>
#include <mpi.h>
int main()
{
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    while (1)
    {
        int data;
        if (world_rank == 0)
        {
            data = 100;
            printf("Process 0 broadcasting data %d\n", data);
            MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
            printf("Process %d received data %d from root process\n", world_rank, data);
        }
        MPI_Request request;
        MPI_Status status;
        MPI_Wait(&request, &status);
    }

    MPI_Finalize();
}