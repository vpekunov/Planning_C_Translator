// 05 processors

#include <iostream>

using namespace std;

#include "mpi.h"

int nProcs;
int MyProcID;

int main() {
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyProcID);
  cout<<"ID = "<<MyProcID<<" on "<<nProcs<<" processors"<<endl;

  MPI_Finalize();

  return 0;
}
