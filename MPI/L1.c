#include <stdio.h>
#include "mpi.h"


int main(int argc, char** argv)
{
    // Khoi tao moi truong MPI
    MPI_Init(&argc, &argv);
    // Lay so processs
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Lay rank cua processor
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // Lay ten cua processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);
    // Ket thuc moi truong MPI
    MPI_Finalize();
}