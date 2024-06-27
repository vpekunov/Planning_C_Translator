// Uncomment the following line if you hava a Cilk-capable compiler
// #define CILK

#include <iostream>

using namespace std;

#include "atomic_cilk_gpu_omp_compile.h"

#pragma auto for
#pragma auto omp for
#pragma auto gpu for
#pragma auto parallelize

#ifndef CILK
#define _Cilk_spawn /* _Cilk_spawn */
#define _Cilk_sync /* _Cilk_sync */
#define _Cilk_for for
#endif

#define cilk_spawn
#define cilk_sync
#define cilk_for(A) _Cilk_for(int A)

void same(int k, int * out) {
  if (k >= 0) *out = k;
  else *out = 0;
}

int main() {
  __pivot int iters[4] = { 0 };
  split_private int k, s, m;
  for (k = 6; k < 10; k++) {
      int p,q;
      for (s = 0; s < 100; s++)
          for (m = 0; m < 100; m++)
              same(k, &p);
      for (s = 0; s < 100; s++)
          for (m = 0; m < 100; m++)
              same(k, &q);
      iters[k-6] = p + q;
  }
  for (int i = 0; i < 4; i++)
      cout << iters[i] << " ";
  cout << endl;
}
