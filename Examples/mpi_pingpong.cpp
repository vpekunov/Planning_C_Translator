#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define NUMBER_OF_TESTS 10

int main(int argc, char ** argv )
{
    double       *buf;
    int          rank,size;
    int          n;
    double       t1, t2, tmin;
    int          i, j, k, nloop;
    MPI_Status   status;
    FILE * Log = NULL;

    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    if (rank == size-2) 
	{
	 Log = fopen("pingpong.dat","w+t");
	 fprintf(Log, "Kind\t\tn\ttime (sec)\tRate (MB/sec)\n" );
	}

    if (rank>=size-2)
        for (n=1; n<550000; n*=2) {
	    if (n == 0) nloop = 1000;
	    else   	    nloop  = 1000/n;
	    if (nloop < 1) nloop = 1;

	    buf = (double *) malloc( n * sizeof(double) );
	    if (!buf) {
	        fprintf( stderr, 
		         "Could not allocate send/recv buffer of size %d\n", n );
	        MPI_Abort( MPI_COMM_WORLD, 1 );
	    }
	    tmin = 1000;
	    for (k=0; k<NUMBER_OF_TESTS; k++) {
	        if (rank == size-2) {
		    /* Make sure both processes are ready */
                    MPI_Sendrecv( MPI_BOTTOM, 0, MPI_INT, 2*size-3-rank, 14,
			          MPI_BOTTOM, 0, MPI_INT, 2*size-3-rank, 14, MPI_COMM_WORLD, 
			          &status );
		    t1 = MPI_Wtime();
		    for (j=0; j<nloop; j++) {
		        MPI_Send( buf, n, MPI_DOUBLE, 2*size-3-rank, k, MPI_COMM_WORLD );
		        MPI_Recv( buf, n, MPI_DOUBLE, 2*size-3-rank, k, MPI_COMM_WORLD, 
			          &status );
		    }
		    t2 = (MPI_Wtime() - t1) / nloop;
		    if (t2 < tmin) tmin = t2;
	        }
	        else if (rank == size-1) {
		    /* Make sure both processes are ready */
		    MPI_Sendrecv( MPI_BOTTOM, 0, MPI_INT, 2*size-3-rank, 14,
			          MPI_BOTTOM, 0, MPI_INT, 2*size-3-rank, 14, MPI_COMM_WORLD, 
			          &status );
		    for (j=0; j<nloop; j++) {
		        MPI_Recv( buf, n, MPI_DOUBLE, 2*size-3-rank, k, MPI_COMM_WORLD, 
			          &status );
		        MPI_Send( buf, n, MPI_DOUBLE, 2*size-3-rank, k, MPI_COMM_WORLD );
		    }
	        }
	    }
	    /* Convert to half the round-trip time */
	    tmin = tmin / 2.0;
	    if (rank == size-2) {
	        double rate;
	        if (tmin > 0) rate = n * sizeof(double) * 1.0e-6 /tmin;
	        else          rate = 0.0;
	        fprintf(Log, "Send/Recv\t%d\t%f\t%f\n", n, tmin, rate );
	    }
	    free( buf );
        }

    if (rank == size-2) fclose(Log);
  
    MPI_Barrier( MPI_COMM_WORLD );
    MPI_Finalize( );
    return 0;
}
