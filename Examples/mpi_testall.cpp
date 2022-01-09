#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank, size, flag, i;
    int buffer[100];
    MPI_Request r[4];
    MPI_Status status[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size != 4)
    {
        printf("Please run with 4 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }
    if (rank == 0)
    {
        for (i=1; i<size; i++)
        {
            MPI_Irecv(&buffer[i], 1, MPI_INT, i, 123, MPI_COMM_WORLD, &r[i-1]);
        }
        flag = 0;
        MPI_Testall(size-1, r, &flag, status);
        while (!flag)
        {
            printf("wait... ");
            Sleep(1);
            MPI_Testall(size-1, r, &flag, status);
        }
        printf("\n");
    }
    else
    {
        MPI_Send(buffer, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}