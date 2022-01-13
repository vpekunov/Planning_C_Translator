#pragma plan vectorized

#include <iostream>
using namespace std;

#pragma plan common begin
#define N 5
#pragma plan common end

reenterable Mul(bool init, int k, _global(N) int * A, int i, _local(1) int * out) {
  int ii;
  if (init) {
     for (ii = 0; ii < N; ii++) {
         plan_last(false, k, A, ii, out);
         out++;
     }
     plan_group_vectorize(NULL);
  } else {
         *out = A[i]*k;
     }
}

int main() {
    int A[N] = {1, 2, 3, 4, 5};
    int B[N];

    Mul(true, 11, A, 0, B);

    for (int i = 0; i < N; i++)
        cout << B[i] << " ";
    cout << endl;
}
