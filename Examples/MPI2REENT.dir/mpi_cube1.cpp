// 08 processors

#include "mpi.h"
#include <stdlib.h>
#include <math.h>

int getProcID(int N, int x, int y, int z) {
  return (z*N+y)*N+x;
}

int main(int argc, char ** argv) {
  if (MPI_Init(&argc,&argv)==MPI_SUCCESS) {
     int nProcs;
     int MyProcID;
     
     int N, X, Y, Z;
     
     int A;

     MPI_Status  Status;
     
     MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
     MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);
     
     N = floor(pow((double)nProcs,1.0/3.0)+0.5);

     X = MyProcID%N;
     Y = ((MyProcID-X)/N)%N;
     Z = (MyProcID-Y*N-X)/(N*N);
     
     if (MyProcID==0) A = 1000.0*rand()/RAND_MAX;
     if (Y==0 && Z==0) {
        if (X>0) MPI_Recv(&A,1,MPI_INT,getProcID(N,X-1,Y,Z),1234,MPI_COMM_WORLD,&Status);
        if (X<N-1) MPI_Send(&A,1,MPI_INT,getProcID(N,X+1,Y,Z),1234,MPI_COMM_WORLD);
     }
     if (Z==0) {
        if (Y>0) MPI_Recv(&A,1,MPI_INT,getProcID(N,X,Y-1,Z),1234,MPI_COMM_WORLD,&Status);
        if (Y<N-1) MPI_Send(&A,1,MPI_INT,getProcID(N,X,Y+1,Z),1234,MPI_COMM_WORLD);
     }
     if (Z>0) MPI_Recv(&A,1,MPI_INT,getProcID(N,X,Y,Z-1),1234,MPI_COMM_WORLD,&Status);
     if (Z<N-1) MPI_Send(&A,1,MPI_INT,getProcID(N,X,Y,Z+1),1234,MPI_COMM_WORLD);

     printf("(%i,%i,%i) : %i\n",X,Y,Z,A);

     MPI_Finalize();
  }

  return 0;
}
