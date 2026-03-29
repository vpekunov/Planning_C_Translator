#pragma plan vectorized

#include <iostream>

using namespace std;

reenterable void mma_m8n8k4(bool init, int nMatrices, _global(nMatrices*8*4) double * A, _global(nMatrices*4*8) double * B, _global(nMatrices*8*8) double * C) {
  int i, j;
  if (init) {
     for (i = 0; i < nMatrices; i++) {
         for (j = 0; j < 32; j++) {
             plan_last(false, nMatrices, A, B, C);
         }
         A += 32;
         B += 32;
         C += 64;
     }
     plan_group_typize(NULL);
  } else {
     #ifdef NVIDIA_TENSOR_CAPABLE
     int id = plan_vector_id();
     int item = id % 32;
     double C0[2] = { C[item*2], C[item*2+1] };
     double A0 = A[item];
     double B0 = B[item/4 + (item%4)*8];
     asm volatile(
      "mma.sync.aligned.m8n8k4.row.col.f64.f64.f64.f64"
      "{%0,%1}, {%2}, {%3}, {%4,%5};\n"
      : "=d"(C0[0]), "=d"(C0[1])
      :
        "d"(A0),
        "d"(B0),
        "d"(C0[0]), "d"(C0[1])
     );
     barrier(0);
     C[item*2]   = C0[0];
     C[item*2+1] = C0[1];
     #endif
  }
}

int main() {
  double A[32], B[32], C[64];

  for (int i = 0; i < 32; i++) {
      A[i] = i;
      B[i] = i;
      C[2*i] = 1;
      C[2*i+1] = 1;
  }

  mma_m8n8k4(true, 1, A, B, C);

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++)
          cout<<C[i*8+j]<<" ";
      cout<<endl;
  }

  return 0;
}