// 06 processors

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

  MPI_Barrier(MPI_COMM_WORLD);

  if (MyProcID == 0) {
     double v = 7.0;
     cout<<"Sent: "<<v<<endl;
     for (int i = 1; i < nProcs; i++)
         MPI_Send(&v, 1, MPI_DOUBLE, nProcs-i, 1234, MPI_COMM_WORLD);
     for (int i = 1; i < nProcs; i++) {
         MPI_Status st, status;
         int presents = 0;
         while (!presents)
            MPI_Iprobe(MPI_ANY_SOURCE, 1234, MPI_COMM_WORLD, &presents, &st);
         MPI_Recv(&v, 1, MPI_DOUBLE, st.MPI_SOURCE, 1234, MPI_COMM_WORLD, &status);
         cout<<"Received from "<<status.MPI_SOURCE<<" value "<<v<<endl;
     }
  } else {
     double x;
     MPI_Status status;
     MPI_Recv(&x, 1, MPI_DOUBLE, 0, 1234, MPI_COMM_WORLD, &status);
     x += 1.0*MyProcID;
     MPI_Send(&x, 1, MPI_DOUBLE, 0, 1234, MPI_COMM_WORLD);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
