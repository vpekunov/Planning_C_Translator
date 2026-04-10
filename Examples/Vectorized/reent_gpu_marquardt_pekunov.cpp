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
#define mu_min 0.000001

#define QRAN_SHIFT ((unsigned int) 15)
#define QRAN_MASK ((unsigned int)((1 << QRAN_SHIFT) - 1))
#define QRAN_MAX ((unsigned int) QRAN_MASK)
#define QRAN_A ((unsigned int) 1664525)
#define QRAN_C ((unsigned int)1013904223)

float genrandom(__global unsigned int * RandSeed) {
	#ifdef ON_GPU
	*RandSeed = ((long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	#else
	*RandSeed = ((long long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	#endif
	return 1.0f*(((*RandSeed) >> 16) & QRAN_MAX)/QRAN_MAX;
}

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
#def_module() marquardt_pekunov(NAME, n, FUN) {
@goal:-brackets_off.
	reenterable @goal:-write(NAME).(bool init, float EPS, int nProbes, float mu0,
			_global(n) float * x0, _global(n) float * x1,
			_global(__planned__.nProbes) unsigned int * SEEDS,
			_global(n) int * iRow,
			_global(n*n) float * A,
			_global(n*n) float * LU,
			_global(n) float * B,
			_global(n) float * GRAD,
			_global(n) float * D,
			_global(1) int * iters) {
		if (init) {
			int work_size = n > nProbes ? n : nProbes;

			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, nProbes, mu0, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, iters);
			plan_group_vectorize(NULL);
		} else {
			int id = plan_vector_id();
			float mu = mu0;
			float r = 0.1f;
			float x[n];
			for (int i = 0; i < n; i++)
				x[i] = x0[i];
			float Fk1 = @goal:-write(FUN).;
			float d = 1E30f;
			int Lk1 = 5*nProbes;
			if (id == 0) {
				for (int i = 0; i < n; i++)
					GRAD[i] = 0.0f;
				*iters = 0;
			}
			barrier(CLK_GLOBAL_MEM_FENCE);
			do {
				for (int i = 0; i < n; i++)
					x[i] = x0[i] + (r - 2*r*genrandom(&SEEDS[id]));
				float Fp = @goal:-write(FUN).;
				if (id < n) B[id] = Fk1;
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < n) iRow[id] = 0;
				barrier(CLK_GLOBAL_MEM_FENCE);
				#ifdef ON_GPU
				atomic_min_float(&B[id % n], Fp);
				#else
				if (B[id % n] > Fp) B[id % n] = Fp;
				#endif
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (Fp < Fk1)
					#ifdef ON_GPU
					atomic_inc(&iRow[id % n]);
					#else
					iRow[id % n]++;
					#endif
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0)
					for (int i = 1; i < n; i++)
						iRow[0] += iRow[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0)
					for (int i = 1; i < n; i++)
						if (B[i] < B[0]) B[0] = B[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				int Lk = iRow[0];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0) iRow[0] = nProbes - 1;
				barrier(CLK_GLOBAL_MEM_FENCE);
				Fk1 = B[0];
				if (Fk1 == Fp)
					#ifdef ON_GPU
					atomic_min(&iRow[0], id);
					#else
					if (id < iRow[0]) iRow[0] = id;
					#endif
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0)
					for (int i = 0; i < n; i++)
						x1[i] = x0[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (iRow[0] == id)
					for (int i = 0; i < n; i++)
						x1[i] = x[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (Lk > 0) {
					if (Lk < Lk1) {
						if (r < 0.001) {
							r *= 2;
						}
					} else if (Lk > Lk1) {
						if (r > 0.1) {
							r /= 2;
						}
					}
					mu = (mu0*Lk*Lk)/nProbes/nProbes;
					if (mu < mu_min) mu = mu_min;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				for (int i = 0; i < n; i++)
					x[i] = x1[i];
				if (id < n*n) {
					int i = id / n;
					int j = id % n;
					if (i == j) {
						x[i] += delta;
						float fp = @goal:-write(FUN).;
						x[i] -= 2*delta;
						float fm = @goal:-write(FUN).;
						A[id] = mu + (fp-2.0f*Fk1+fm)/(delta*delta);
						GRAD[i] = (fp - fm)/(2.0f*delta);
					} else {
						x[i] += delta;
						x[j] += delta;
						float fpp = @goal:-write(FUN).;
						x[j] -= 2*delta;
						float fpm = @goal:-write(FUN).;
						float gp = (fpp-fpm)/(2.0f*delta);
						x[i] -= 2*delta;
						float fmm = @goal:-write(FUN).;
						x[j] += 2*delta;
						float fmp = @goal:-write(FUN).;
						float gm = (fmp-fmm)/(2.0f*delta);
						A[id] = (gp - gm)/(2.0f*delta);
					}
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
					_SolveLU(n, iRow, LU, GRAD, D);
					float omega = 1.0f;
					float step = 1.0f;
					while (omega > EPS && step > EPS) {
						step = 0.0f;
						for (int i = 0; i < n; i++) {
							float ds = omega*D[i];
							x[i] = x1[i] - ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						float Fi = @goal:-write(FUN).;
						if (Fi < Fk1) {
							Fk1 = Fi;
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
				Lk1 = Lk;
			} while (d > EPS);
		}
	}
};

marquardt_pekunov('min_m_p', 2, '4.0f*(x[0]-5.0f)*(x[0]-5.0f) + (x[1]-6.0f)*(x[1]-6.0f)')

int main() {
	const int nProbes = 500;
	float x0[2] = { 1.0f, 1.0f }, x1[2];
	unsigned int SEEDS[nProbes] = { 0 };
	int iRow[2];
	float A[4];
	float LU[4];
	float B[2];
	float GRAD[2];
	float D[2];
	int iters = 0;
	unsigned int seed = (unsigned int)time(NULL);
	for (int i = 0; i < nProbes; i++)
		SEEDS[i] = (unsigned int)(100000*genrandom(&seed));
	min_m_p(true, 1E-4f, nProbes, 20.0f, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, &iters);
	cout << iters << endl;
	for (int i = 0; i < 2; i++)
		cout << x1[i] << " ";
}
