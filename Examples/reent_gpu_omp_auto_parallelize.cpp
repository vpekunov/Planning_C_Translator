#include <iostream>

using namespace std;

#include "gpu_loop_compile.h"

void same(int k, int * out) {
  if (k >= 0) *out = k;
  else *out = 0;
}

int main() {
  /* __pivot */ int iters[4] = { 0 };
  int k, s, m;
  for (k = 6; k < 10; k++) {
      int p;
      for (s = 0; s < 100; s++)
          for (m = 0; m < 100; m++)
              same(k, &p);
      iters[k-6] = p;
  }
  for (int i = 0; i < 4; i++)
      cout << iters[i] << " ";
  cout << endl;
}
