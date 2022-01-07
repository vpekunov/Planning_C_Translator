// Debugged
#include "altopo.h"

#include <iostream>

using namespace std;

chain A(bool init, input_proc Ref, float Result) {
  static int leafs = 0;

  input_proc incoming[128];
  int n_in;
  input_proc outcoming[128];
  int n_out;

  plan_neighbours(true, A[plan_linear_num()], &n_in, incoming);
  plan_neighbours(false, A[plan_linear_num()], &n_out, outcoming);

  if (init) {
     if (n_in == 0)
        plan_first(false, empty_proc, Result);
     if (n_out == 0) {
        plan_critical(outCount) {
          leafs++;
        }
     }
  } else if (n_out == 0) {
     plan_critical(outResult) {
       cout<<Result<<" ";
       leafs--;
     }
     if (leafs == 0) plan_topology_quit();
  } else {
     for (int i = 0; i < n_out; i++) {
         throw_first(false, outcoming[i], Result);
     }
  }
}

int main() {
  const int N = 22;

  altopo([['A', '(true, empty_proc, N)']], 'A[1]*(A[2]*(A[]+A[])+A[3]*(A[]+A[]))');
  cout<<endl;
}