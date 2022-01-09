// Debugged

#pragma plan clustered
#include <iostream>

using namespace std;

chain B() {
  cout<<"1";
  plan_registered_barrier(topology);
  Sleep(100);
  cout<<"2";
  plan_registered_barrier(topology);
  Sleep(100);
  cout<<"3";
  plan_registered_barrier(topology);
  Sleep(100);
  cout<<"4";
  plan_registered_barrier(topology);
  Sleep(100);
  cout<<"5";
  for (int i = 0; i < 10; i++)
  {
    if (i == 0) Sleep(i*10);
    else if (i == 2) Sleep((10-i)*10);
    plan_registered_barrier(topology);
  }
  Sleep(100);
  cout<<"7";
}

int main() {
  const int N = 8;
  int IDs[N] = {0,2,3,5,4,7,6,1};
  clustered(IDs) plan_parallel_chain(1,N,B());
  cout<<endl;

  return 0;
}