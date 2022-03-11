#pragma plan vectorized

#include <iostream>

using namespace std;

#pragma plan common begin

#define N 5
#define threads 100

#pragma plan common end

#pragma plan gpu begin
#define addition 0.01
#pragma plan gpu end

float MUL = 3.14;

float * _OUT = NULL;

reenterable void proc(bool init, int k, _global(1) float * mul, _global(threads) int * sizes, int n, _local(__planned__.n) float * out) {
  int i;
  if (init) {
     for (i = 0; i < threads; i++) {
         plan_last(false, i, mul, sizes, sizes[i], out);
         out += sizes[i];
     }
     plan_group_vectorize(NULL);
  } else
     for (i = 0; i < n; i++) {
         *out = k*(*mul);
#ifdef __GPU__
         *out += addition;
#endif
         out++;
     }
}

int main() {
  int * sizes = new int[threads];

  int NN = 0;
  for (int i = 0; i < threads; i++) {
      sizes[i] = 1 + i % 2;
      NN += sizes[i];
  }

  _OUT = new float[NN];

  cout<<"MAX group size = "<<vector_max_size(NULL)<<endl;
  cout<<"LOCAL MEMORY (per multiprocessor) size = "<<local_memory_size(NULL)<<endl;

  proc(true, 0, &MUL, sizes, 0, _OUT);

  for (int i = 0; i < NN; i++)
      cout<<_OUT[i]<<" ";
  cout<<endl;

  delete[] _OUT;
  delete[] sizes;

  return 0;
}