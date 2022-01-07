#include <iostream>

using namespace std;

#include <stdlib.h>
#include "mpi.h"

int nProcs;
int MyProcID;

int main() {
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyProcID);

  cout<<"ID = "<<MyProcID<<" on "<<nProcs<<" processors"<<endl;

  MPI_Barrier(MPI_COMM_WORLD);

  if (MyProcID == 0) {
     double * v  = new double[nProcs];
     double * v1 = new double[nProcs];
     for (int i = 0; i < nProcs; i++)
         v[i] = 1.0*rand()/RAND_MAX;
     cout<<"Sent: ";
     for (int i = 0; i < nProcs; i++)
         cout<<v[i]<<" ";
     cout<<endl;
     MPI_Scatter(v, 1, MPI_DOUBLE, &v1[0], 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     MPI_Gather(&v1[0], 1, MPI_DOUBLE, v1, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     cout<<"Received: ";
     for (int i = 0; i < nProcs; i++)
         cout<<v1[i]<<" ";
     cout<<endl;
     delete[] v;
     delete[] v1;
  } else {
     double x;
     MPI_Scatter(NULL, 1, MPI_DOUBLE, &x, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     MPI_Gather(&x, 1, MPI_DOUBLE, NULL, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
