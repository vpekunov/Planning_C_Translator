#include "mpi.h"
#include <stdio.h>
#include <math.h>

double F(int N, double t, double y1, double y2, double y3) {
  double K = sqrt(y1*y1+y2*y2);
  switch (N) {
    case 0: return -y2+y1*y3/K;
    case 1: return y1-y2*y3/K;
    case 2: return y1/K;
  }
}

int main(int argc, char ** argv) {
  if (MPI_Init(&argc,&argv)==MPI_SUCCESS) {
     double t;
     double tmax = 0.1;
     double tau = 0.01;
  
     int nProcs;
     int MyProcID;
     
     MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
     MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);
     
     if (nProcs==3) {
        double y[3] = {3.0, 0.0, 0.0};
        double R1[3], R2[3], R3[3], R4[3];
        int i;
        for (t = 0.0; t < tmax-tau; t += tau) {
          R1[MyProcID] = tau*F(MyProcID,t,y[0],y[1],y[2]);
          MPI_Allgather(&R1[MyProcID],1,MPI_DOUBLE,R1,1,MPI_DOUBLE,MPI_COMM_WORLD);
          R2[MyProcID] = tau*F(MyProcID,t+tau/2,y[0]+0.5*R1[0],y[1]+0.5*R1[1],y[2]+0.5*R1[2]);
          MPI_Allgather(&R2[MyProcID],1,MPI_DOUBLE,R2,1,MPI_DOUBLE,MPI_COMM_WORLD);
          R3[MyProcID] = tau*F(MyProcID,t+tau/2,y[0]+0.5*R2[0],y[1]+0.5*R2[1],y[2]+0.5*R2[2]);
          MPI_Allgather(&R3[MyProcID],1,MPI_DOUBLE,R3,1,MPI_DOUBLE,MPI_COMM_WORLD);
          R4[MyProcID] = tau*F(MyProcID,t+tau,y[0]+R3[0],y[1]+R3[1],y[2]+R3[2]);
          MPI_Allgather(&R4[MyProcID],1,MPI_DOUBLE,R4,1,MPI_DOUBLE,MPI_COMM_WORLD);
          y[MyProcID] += 1.0/6.0*(R1[MyProcID]+2*R2[MyProcID]+2*R3[MyProcID]+R4[MyProcID]);
          MPI_Allgather(&y[MyProcID],1,MPI_DOUBLE,y,1,MPI_DOUBLE,MPI_COMM_WORLD);
          if (MyProcID==0) {
             for (i=0; i<3; i++)
               printf("y[%i] = %lf ",i+1,y[i]);
             printf("\n");
          }
        }
     }

     MPI_Finalize();
  }

  return 0;
}
