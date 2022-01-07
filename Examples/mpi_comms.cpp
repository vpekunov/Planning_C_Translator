#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[])
{
 char message[24];
 MPI_Group MPI_GROUP_WORLD;
 MPI_Group group;
 MPI_Comm fcomm;
 int size, q, proc;
 int* process_ranks;
 int rank, rank_in_group;
 MPI_Status status;

 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 printf("New group contains processes:");
 q = size - 1;
 process_ranks = (int*) malloc(q*sizeof(int));
 for (proc = 0; proc < q; proc++) {
   process_ranks[proc] = proc;
   printf("%i ", process_ranks[proc]);
 }
 printf("\n");
 MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
 MPI_Group_incl(MPI_GROUP_WORLD, q, process_ranks, &group);
 MPI_Comm_create(MPI_COMM_WORLD, group, &fcomm);
 if (fcomm != MPI_COMM_NULL) {
   MPI_Comm_group(fcomm, &group);
   MPI_Comm_rank(fcomm, &rank_in_group);
   if (rank_in_group == 0) {
      strcpy(message, "Hi, Parallel Programmer!");
      MPI_Bcast(&message, 25, MPI_BYTE, 0, fcomm);
      printf("0 send: %s\n", message);
   }
   else
   {
      MPI_Bcast(&message, 25, MPI_BYTE, 0, fcomm);
      printf("%i received: %s\n", rank_in_group, message);
   }
   MPI_Comm_free(&fcomm);
   MPI_Group_free(&group);
 }
 MPI_Finalize();
 return 0;
}