#pragma plan vectorized

#include <iostream>
#include <chrono>

using namespace std;

reenterable void mma_m8n8k4(bool init, bool tensored, int nMatrices, _global(nMatrices*8*4) float * A, _global(nMatrices*4*8) float * B, _global(nMatrices*8*8) float * C) {
  int i, j;
  if (init) {
     if (tensored) {
        for (j = 0; j < 32/4*nMatrices; j++) {
            plan_last(false, tensored, nMatrices, A, B, C);
        }
        plan_group_typize(NULL);
     }
     else {
        for (j = 0; j < 8*nMatrices; j++) {
            plan_last(false, tensored, nMatrices, A, B, C);
        }
        plan_group_vectorize(NULL);
     }
  } else {
     int id = plan_vector_id();
     #ifdef NVIDIA_TENSOR_CAPABLE
     if (tensored) {
        int matr = (id / 32)*4 + (((id % 32) / 4) & 0x3);
        int itemA = 4*(id % 4) + 16*((id >> 4) & 0x1);
        int itemB = (id % 4) + 4*((id >> 4) & 0x1);
        int base = matr*32;
        int base2 = 2*base;
        unsigned short _A0[4];
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_A0[0]) : "f"(A[base + itemA]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_A0[1]) : "f"(A[base + itemA + 1]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_A0[2]) : "f"(A[base + itemA + 2]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_A0[3]) : "f"(A[base + itemA + 3]));
        unsigned int A0[2] = { _A0[0]+(((unsigned int)_A0[1])<<16), _A0[2]+(((unsigned int)_A0[3])<<16) };
        unsigned short _B0[4];
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_B0[0]) : "f"(B[base + itemB]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_B0[1]) : "f"(B[base + itemB + 8]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_B0[2]) : "f"(B[base + itemB + 16]));
        asm("cvt.rn.f16.f32 %0, %1;" : "=r"(_B0[3]) : "f"(B[base + itemB + 24]));
        unsigned int B0[2] = { _B0[0]+(((unsigned int)_B0[1])<<16), _B0[2]+(((unsigned int)_B0[3])<<16) };
        int row = (id & 0x1) + ((id & 0x10) >> 2);
        int rows[8] = { row, row, row+2, row+2, row, row, row+2, row+2 };
        int col = (id & 0x2);
        int cols[8] = { col, col+1, col, col+1, col+4, col+5, col+4, col+5 };
        float C0[8] = {
          C[base2 + rows[0]*8 + cols[0]],
          C[base2 + rows[1]*8 + cols[1]],
          C[base2 + rows[2]*8 + cols[2]],
          C[base2 + rows[3]*8 + cols[3]],
          C[base2 + rows[4]*8 + cols[4]],
          C[base2 + rows[5]*8 + cols[5]],
          C[base2 + rows[6]*8 + cols[6]],
          C[base2 + rows[7]*8 + cols[7]]
        };
        asm volatile(
         "mma.sync.aligned.row.col.m8n8k4.f32.f16.f16.f32"
         "{%0,%1,%2,%3,%4,%5,%6,%7}, {%8,%9}, {%10,%11}, {%12,%13,%14,%15,%16,%17,%18,%19};\n"
         : "=f"(C0[0]), "=f"(C0[1]), "=f"(C0[2]), "=f"(C0[3]), "=f"(C0[4]), "=f"(C0[5]), "=f"(C0[6]), "=f"(C0[7])
         :
           "r"(A0[0]), "r"(A0[1]),
           "r"(B0[0]), "r"(B0[1]),
           "f"(C0[0]), "f"(C0[1]), "f"(C0[2]), "f"(C0[3]), "f"(C0[4]), "f"(C0[5]), "f"(C0[6]), "f"(C0[7])
        );
        barrier(0);
        C[base2 + rows[0]*8 + cols[0]] = C0[0];
        C[base2 + rows[1]*8 + cols[1]] = C0[1];
        C[base2 + rows[2]*8 + cols[2]] = C0[2];
        C[base2 + rows[3]*8 + cols[3]] = C0[3];
        C[base2 + rows[4]*8 + cols[4]] = C0[4];
        C[base2 + rows[5]*8 + cols[5]] = C0[5];
        C[base2 + rows[6]*8 + cols[6]] = C0[6];
        C[base2 + rows[7]*8 + cols[7]] = C0[7];
     } else {
     #endif
        int matr = id / 8;
        int base = matr*32;
        int item = id % 8;
        int ptr = base*2 + item*8;
        for (i = 0; i < 8; i++) {
            float S = C[ptr];
            int ptr2 = base + item*4;
            int ptr3 = base + i;
            for (j = 0; j < 4; j++, ptr3 += 8)
                S += A[ptr2++]*B[ptr3];
            C[ptr++] = S;
        }
     #ifdef NVIDIA_TENSOR_CAPABLE
     }
     #endif
  }
}

int main() {
  const int M = 20;
  float A[M][32], B[M][32], C[M][64];

  auto start1 = std::chrono::steady_clock::now();

  for (int k = 0; k < 1000; k++) {
      for (int m = 0; m < M; m++)
          for (int i = 0; i < 32; i++) {
              A[m][i] = i;
              B[m][i] = i;
              C[m][2*i] = 1;
              C[m][2*i+1] = 1;
          }

      mma_m8n8k4(true, true, M, (float *)A, (float *)B, (float *)C);
  }

  auto end1 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
  std::cout << "TENSORED: Time elapsed (seconds): " << (elapsed_seconds1.count() - last_compile_time(NULL)) << std::endl;

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

      mma_m8n8k4(true, false, M, (float *)A, (float *)B, (float *)C);
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