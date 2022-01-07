#include <iostream>

using namespace std;

#include "mpi.h"

int nProcs;
int MyProcID;

int main() {
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyProcID);

  MPI_Status status;
  int v;

  if (MyProcID == 0) {
     v = 15;
     cout<<"Sended: "<<v<<endl;
  }

  double t0 = MPI_Wtime();
  for (int i = 0; i < 500; i++) {
      if (MyProcID > 0) MPI_Recv(&v, 1, MPI_INT, MyProcID-1, 1234, MPI_COMM_WORLD, &status);
      if (MyProcID < nProcs-1) MPI_Send(&v, 1, MPI_INT, MyProcID+1, 1234, MPI_COMM_WORLD);
      if (MyProcID < nProcs-1) MPI_Recv(&v, 1, MPI_INT, MyProcID+1, 1234, MPI_COMM_WORLD, &status);
      if (MyProcID > 0) MPI_Send(&v, 1, MPI_INT, MyProcID-1, 1234, MPI_COMM_WORLD);
  }
  double t = MPI_Wtime() - t0;

  if (MyProcID == 0) {
     cout<<"Received: "<<v<<endl;
     cout<<"Total time = "<<t<<endl;
  }

  MPI_Finalize();

  return 0;
}
