#include "mpi.h" 
#include <stdio.h>
#include <stdlib.h>

/* tests passive target RMA on 2 processes */

#define SIZE1 100
#define SIZE2 200

int main(int argc, char *argv[]) 
{ 
    int rank, nprocs, A[SIZE2], i, j;
    MPI_Win win;
    int errs = 0;
 
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 

    if (nprocs != 4) {
        printf("Run this program with 4 processes\n");fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    if (rank == 0) {
        for (i=0; i<SIZE2; i++) A[i] = 0;
        MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win); 

        for (j=1; j<4; j++)
            for (i=0; i<SIZE1; i++) {
                MPI_Win_lock(MPI_LOCK_EXCLUSIVE, j, 0, win);
                MPI_Get(A+i, 1, MPI_INT, j, i, 1, MPI_INT, win);
                A[i]++;
                MPI_Put(A+i, 1, MPI_INT, j, i, 1, MPI_INT, win);
                MPI_Win_unlock(j, win);
            }

        MPI_Win_free(&win);
    }
    else {  /* rank=1,2,3 */
        for (i=0; i<SIZE2; i++) A[i] = 0;
        MPI_Win_create(A, SIZE2*sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

        for (i=0; i<SIZE1; i++) {
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win);
            MPI_Get(A+i, 1, MPI_INT, rank, i, 1, MPI_INT, win);
            A[i]++;
            MPI_Put(A+i, 1, MPI_INT, rank, i, 1, MPI_INT, win);
            MPI_Win_unlock(rank, win);
        }

        MPI_Win_free(&win); 
        
        for (i=0; i<SIZE1; i++) {
            if (A[i] != 2) {
                printf("Slave Error: A[%d] is %d, should be %d\n", i, A[i], 2);
                errs++;
            }
        }
    }

    MPI_Finalize(); 
    return errs; 
}