// Debugged

#pragma plan clustered
#include <iostream>
#include <stdlib.h>

using namespace std;

chain B() {
  if (plan_cluster_id() < 0.4*plan_cluster_size())
     plan_register(grlow);
  else if (plan_cluster_id() > 0.6*plan_cluster_size())
     plan_register(grhigh);
  plan_registered_barrier(topology); // To ensure that all registers are passed
  if (plan_cluster_id() < 0.4*plan_cluster_size())
     plan_registered_barrier(grlow);
  else if (plan_cluster_id() > 0.6*plan_cluster_size())
     plan_registered_barrier(grhigh);
  cout<<plan_cluster_id();
}

int main() {
  const int N = 8;
  int IDs[N] = {0,2,3,5,4,7,6,1};
  clustered(IDs) plan_parallel_chain(1,N,B());

  return 0;
}