#include <iostream>

using namespace std;

#include "gpu_parallelize.h"

#pragma plan common begin
$ void same(int k, int * out) {
  if (k >= 0) *out = k;
  else *out = 0;
}
#pragma plan common end

int main() {
  int iters[4] = { 0 };
  int k;
  vectorized(NULL,2) gpu<int k, _pivot int iters[4]>
  for (k = 6; k < 10; k++) {
      int p;
      same(k, &p);
      iters[k-6] = p;
  }
  for (int i = 0; i < 4; i++)
      cout << iters[i] << " ";
  cout << endl;
}
