#pragma plan vectorized

#include <iostream>
#include <chrono>

using namespace std;

reenterable void mma_m8n8k4(bool init, bool tensored, int nMatrices, _global(nMatrices*8*4) double * A, _global(nMatrices*4*8) double * B, _global(nMatrices*8*8) double * C) {
  int i, j;
  if (init) {
     if (tensored) {
        for (j = 0; j < 32*nMatrices; j++) {
            plan_last(false, tensored, nMatrices, A, B, C);
        }
        plan_group_typize(NULL, 32);
     }
     else {
        for (j = 0; j < 8*nMatrices; j++) {
            plan_last(false, tensored, nMatrices, A, B, C);
        }
        plan_group_vectorize(NULL);
     }
  } else {
     if (tensored) {
        int id = plan_vector_id();
        int item = id % 32;
        int matr = id / 32;
        int base = matr*32;
        #ifdef NVIDIA_TENSOR_CAPABLE
        double C0[2] = { C[base*2 + item*2], C[base*2 + item*2 + 1] };
        double A0 = A[base + item];
        double B0 = B[base + item/4 + (item%4)*8];
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
        C[base*2 + item*2]   = C0[0];
        C[base*2 + item*2 + 1] = C0[1];
        #else
        if (item < 8) {
           int ptr = base*2 + item*8;
           for (i = 0; i < 8; i++) {
               double S = C[ptr];
               int ptr2 = base + item*4;
               int ptr3 = base + i;
               for (j = 0; j < 4; j++, ptr3 += 8)
                   S += A[ptr2++]*B[ptr3];
               C[ptr++] = S;
           }
        }
        barrier(0);
        #endif
     } else {
        int id = plan_vector_id();
        int matr = id / 8;
        int base = matr*32;
        int item = id % 8;
        int ptr = base*2 + item*8;
        for (i = 0; i < 8; i++) {
            double S = C[ptr];
            int ptr2 = base + item*4;
            int ptr3 = base + i;
            for (j = 0; j < 4; j++, ptr3 += 8)
                S += A[ptr2++]*B[ptr3];
            C[ptr++] = S;
        }
     }
  }
}

int main() {
  const int M = 20;
  double A[M][32], B[M][32], C[M][64];

  auto start1 = std::chrono::steady_clock::now();

  for (int k = 0; k < 1000; k++) {
      for (int m = 0; m < M; m++)
          for (int i = 0; i < 32; i++) {
              A[m][i] = i;
              B[m][i] = i;
              C[m][2*i] = 1;
              C[m][2*i+1] = 1;
          }

      mma_m8n8k4(true, true, M, (double *)A, (double *)B, (double *)C);
  }

  auto end1 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
  std::cout << "TENSORED: Time elapsed (seconds): " << elapsed_seconds1.count() << std::endl;

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++)
          cout<<C[M/2][i*8+j]<<" ";
      cout<<endl;
  }

  auto start2 = std::chrono::steady_clock::now();

  for (int k = 0; k < 1000; k++) {
      for (int m = 0; m < M; m++)
          for (int i = 0; i < 32; i++) {
              A[m][i] = i;
              B[m][i] = i;
              C[m][2*i] = 1;
              C[m][2*i+1] = 1;
          }

      mma_m8n8k4(true, false, M, (double *)A, (double *)B, (double *)C);
  }

  auto end2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
  std::cout << "NON_TENSORED: Time elapsed (seconds): " << elapsed_seconds2.count() << std::endl;

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++)
          cout<<C[M/2][i*8+j]<<" ";
      cout<<endl;
  }

  return 0;
}