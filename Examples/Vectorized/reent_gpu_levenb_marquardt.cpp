#pragma plan vectorized

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#pragma plan gpu begin

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable

#define ON_GPU

#pragma plan gpu end

#pragma plan common begin

#define delta 0.0001

#ifdef ON_GPU
void atomic_sub_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    do {
        old = as_uint(*addr);
        next = as_uint(as_float(old) - val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
}
void atomic_min_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    do {
        old = as_uint(*addr);
        if (as_float(old) <= val) break;
        next = as_uint(val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
}
void atomic_max_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    do {
        old = as_uint(*addr);
        if (as_float(old) >= val) break;
        next = as_uint(val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
}
#else
void atomic_sub_float(volatile __global float* addr, float val) {
	*addr -= val;
}
void atomic_min_float(volatile __global float* addr, float val) {
	if (*addr > val) *addr = val;
}
void atomic_max_float(volatile __global float* addr, float val) {
	if (*addr < val) *addr = val;
}
#endif

int _GetLU(int NN, __global int * iRow, __global float * A, __global float * LU, __global int * iBig, __global float * Big)
{
 int i, j;

 int id = plan_vector_id();

 int stop = 0;

 int k = id*NN;

 if (id < NN) {
    iRow[id] = id;
    for (i = 0; i < NN; i++)
        LU[k + i] = A[k + i];
 }
 barrier(CLK_GLOBAL_MEM_FENCE);

 for (i=0; !stop && i<NN-1; i++)
   {
    if (id == 0) {
       *iBig = i;
       *Big = 0.0f;
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
    float size = 0.0f;

    if (id >= i && id < NN) {
       size = fabs(LU[iRow[id]*NN+i]);
       #ifdef ON_GPU
       atomic_max_float(Big, size);
       #else
       if (size > *Big) *Big = size;
       #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
    if (id >= i && id < NN) {
       if (*Big == size)
          #ifdef ON_GPU
          atomic_max(iBig, id);
          #else
          if (id > *iBig) *iBig = id;
          #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE);

    if (*iBig!=i && id == 0)
       {
        int V = iRow[i];
        iRow[i] = iRow[*iBig];
        iRow[*iBig] = V;
       }
    barrier(CLK_GLOBAL_MEM_FENCE);
    float Divider = LU[iRow[i]*NN+i];
    if (fabs(Divider) < 1E-12)
       stop = 1;
    float Kf = !stop ? 1.0/Divider : 1.0;
    barrier(CLK_GLOBAL_MEM_FENCE);
    if (id == i) LU[iRow[i]*NN+i] = Kf;
    barrier(CLK_GLOBAL_MEM_FENCE);
    for (j=i+1;j<NN;j++)
        {
         float Fact = Kf*LU[iRow[j]*NN+i];

         if (id == j) LU[iRow[j]*NN+i] = Fact;
         barrier(CLK_GLOBAL_MEM_FENCE);
         if (id > i && id < NN)
            atomic_sub_float(&LU[iRow[j]*NN+id], Fact*LU[iRow[i]*NN+id]);
         barrier(CLK_GLOBAL_MEM_FENCE);
        }
   }
 if (!stop && id == NN-1) LU[(iRow[NN-1]+1)*NN-1] = 1.0/LU[(iRow[NN-1]+1)*NN-1];
 barrier(CLK_GLOBAL_MEM_FENCE);
 return !stop;
}

void _SolveLU(int NN, __global int * iRow, __global float * LU, __global float * Y, __global float * X)
{
 int id = plan_vector_id();

 int i,j,k;
 if (id == 0) X[0] = Y[iRow[0]];
 barrier(CLK_GLOBAL_MEM_FENCE);
 for (i=1;i<NN;i++)
     {
      if (id == i) X[i] = Y[iRow[i]];
      barrier(CLK_GLOBAL_MEM_FENCE);

      if (id < i)
         atomic_sub_float(&X[i], LU[iRow[i]*NN+id]*X[id]);
      barrier(CLK_GLOBAL_MEM_FENCE);
     }

 if (id == NN-1) X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];
 barrier(CLK_GLOBAL_MEM_FENCE);

 for (i=1,j=NN-2;i<NN;i++,j--)
     {
      if (id > j && id < NN)
         atomic_sub_float(&X[j], LU[iRow[j]*NN+id]*X[id]);
      barrier(CLK_GLOBAL_MEM_FENCE);
      if (id == j) X[j] *= LU[iRow[j]*NN+j];
      barrier(CLK_GLOBAL_MEM_FENCE);
     }
}

#pragma plan common end

// n -- размерность пространства
#def_module() levenberg_marquardt(NAME, n, FUN) {
@goal:-brackets_off.
	reenterable @goal:-write(NAME).(bool init, float EPS, float mu0,
			_global(n) float * x0, _global(n) float * x1, _global(n) float * f,
			_global(n) int * iRow,
			_global(n*n) float * A,
			_global(n*n) float * LU,
			_global(n) float * B,
			_global(n) float * GRAD,
			_global(n) float * D,
			_global(1) int * iters) {
		if (init) {
			int work_size = n*n;

			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, mu0, x0, x1, f, iRow, A, LU, B, GRAD, D, iters);
			plan_group_vectorize(NULL);
		} else {
			int id = plan_vector_id();
			float mu = mu0;
			float x[n], f[n];
			for (int i = 0; i < n; i++)
				x[i] = x0[i];
			float Fk1[n], fk1;
			@goal:-write(FUN).;
			barrier(CLK_GLOBAL_MEM_FENCE);
			for (int i = 0; i < n; i++)
				Fk1[i] = f[i];
			barrier(CLK_GLOBAL_MEM_FENCE);
			fk1 = f[0]*f[0];
			for (int i = 1; i < n; i++)
				fk1 += f[i]*f[i];
			barrier(CLK_GLOBAL_MEM_FENCE);
			float d = 1E30f;
			if (id == 0) {
				for (int i = 0; i < n; i++)
					GRAD[i] = 0.0f;
				*iters = 0;
			}
			barrier(CLK_GLOBAL_MEM_FENCE);
			do {
				for (int i = 0; i < n; i++)
					x[i] = x0[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < n) x1[id] = x0[id];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < n*n) {
					int i = id / n;
					int j = id % n;
					x[j] += delta;
					@goal:-write(FUN).;
					float FP = f[i];
					x[j] -= 2*delta;
					@goal:-write(FUN).;
					float FM = f[i];
					LU[id] = (FP-FM)/(2.0f*delta);
					x[j] += delta;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < n*n) {
					int i = id / n;
					int j = id % n;
					float a = 0.0f;
					for (int k = 0; k < n; k++) {
						a += LU[k*n+i]*LU[k*n+j];
					}
					if (i == j) {
						float g = 0.0f;
						for (int k = 0; k < n; k++) {
							g += LU[k*n+i]*Fk1[k];
						}
						GRAD[i] = g;
						B[i] = -g;
						a += mu;
					}
					A[id] = a;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				d = 0.0f;
				for (int i = 0; i < n; i++) {
					float g = GRAD[(i+id) % n];
					d += g*g;
				}
				d = sqrt(d);
				int _iters = *iters;
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (_GetLU(n, iRow, A, LU, iters, D)) {
					_SolveLU(n, iRow, LU, B, D);
					float omega = 1.0f;
					float step = 1.0f;
					while (omega > EPS && step > EPS) {
						step = 0.0f;
						for (int i = 0; i < n; i++) {
							float ds = omega*D[i];
							x[i] = x1[i] + ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						@goal:-write(FUN).;
						barrier(CLK_GLOBAL_MEM_FENCE);
						float fi = 0.0f;
						for (int i = 0; i < n; i++) {
							fi += f[i]*f[i];
						}
						barrier(CLK_GLOBAL_MEM_FENCE);
						if (fi < fk1) {
							fk1 = fi;
							for (int i = 0; i < n; i++)
								Fk1[i] = f[i];
							barrier(CLK_GLOBAL_MEM_FENCE);
							if (id < n) x1[id] = x[id];
							barrier(CLK_GLOBAL_MEM_FENCE);
						} else
							omega *= 0.5f;
					}
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0) {
					for (int i = 0; i < n; i++)
						x0[i] = x1[i];
					*iters = _iters + 1;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
			} while (d > EPS);
		}
	}
};

levenberg_marquardt('min_l_m', 3, 'f[0] = (2.0f-x[0])*(2.0f-x[0]); f[1] = (x[2]-3.0f)*(x[2]-3.0f); f[2] = (4.0f-x[1])*(4.0f-x[1])')

int main() {
	float x0[3] = { 1.0f, 1.0f, 1.0f }, x1[3], f[3];
	int iRow[3];
	float A[9];
	float LU[9];
	float B[3];
	float GRAD[3];
	float D[3];
	int iters = 0;
	min_l_m(true, 1E-4f, 20.0f, x0, x1, f, iRow, A, LU, B, GRAD, D, &iters);
	cout << iters << endl;
	for (int i = 0; i < 3; i++)
		cout << x1[i] << " ";
}
