// 04 processors

#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank, size, flag, i, count;
    int buffer[100];
    MPI_Request r[4];
    MPI_Status status[4];
    int index[4];
 
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
        int remaining = 3;
        for (i=1; i<size; i++)
        {
            MPI_Irecv(&buffer[i], 1, MPI_INT, i, 123, MPI_COMM_WORLD, &r[i-1]);
        }
        while (remaining > 0)
        {
            MPI_Testsome(size-1, r, &count, index, status);
            if (count > 0)
            {
                printf("%d finished\n", count);
                remaining -= count;
            }
            else
            {
                Sleep(1);
            }
        }
    }
    else
    {
        MPI_Send(buffer, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}