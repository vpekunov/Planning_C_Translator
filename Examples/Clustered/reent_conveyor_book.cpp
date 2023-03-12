#pragma plan clustered
#include <iostream>
using namespace std;

chain A() {
  for (int i = 0; i < 100; i++) {
      cfunnel(out, int) * V = new cfunnel(out, int)("CNL");
      *V = i;
      delete V;
  }
}

chain B() {
  for (int i = 0; i < 100; i++) {
      cfunnel(in, int) * V   = new cfunnel(in, int)("CNL");
      cout<<**V<<" ";
      delete V;
  }
}

int main() {
  int IDs[2] = {0,1};

  clustered(IDs) plan_parallel_chain(1, A(), B());

  return 0;
}