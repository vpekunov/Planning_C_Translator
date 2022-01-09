#include <stdio.h>
#include "mpi.h"

void main(int argc, char *argv[])
{
  int num, p;
  int Neven, Nodd, members[6], even_rank, odd_rank;
  MPI_Group group_world, even_group, odd_group;

  MPI_Init(&argc, &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD, &num);  
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  if (p != 6) MPI_Abort(MPI_COMM_WORLD, -1);
  Neven = (p + 1)/2;
  Nodd = p - Neven;
  members[0] = 2;
  members[1] = 0;
  members[2] = 4;
  MPI_Comm_group(MPI_COMM_WORLD, &group_world);
  MPI_Group_incl(group_world, Neven, members, &even_group);
  MPI_Group_excl(group_world, Neven, members,  &odd_group);
  MPI_Barrier(MPI_COMM_WORLD);
  if(num == 0) {
   printf("Number of processes is %d\n", p);
   printf("Number of odd processes is %d\n", Nodd);
   printf("Number of even processes is %d\n", Neven);
   printf("members[0] is assigned rank %d\n", members[0]);
   printf("members[1] is assigned rank %d\n", members[1]);
   printf("members[2] is assigned rank %d\n", members[2]);
   printf("\n");
   printf("     num     even      odd\n");
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Group_rank(even_group, &even_rank);
  MPI_Group_rank( odd_group,  &odd_rank);
  printf("%8d %8d %8d\n",num, even_rank, odd_rank);
  MPI_Finalize();    
}