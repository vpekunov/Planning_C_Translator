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

#define delta 0.00001
#define LEPS 0.0001f
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
int atomic_add(volatile __global int * addr, int val) {
	int old = *addr;
	*addr += val;
	return old;
}
#endif

void BARRIER(int work_size, volatile __global int * barriers) {
	#ifdef ON_GPU
	mem_fence(CLK_GLOBAL_MEM_FENCE);
	if (get_local_id(0) == 0) {
		if (atomic_inc(barriers) == get_num_groups(0)-1) atomic_xchg(barriers, 0);
		else
			do {
				mem_fence(CLK_GLOBAL_MEM_FENCE);
			} while (atomic_add(barriers, 0) != 0);
	}
	mem_fence(CLK_GLOBAL_MEM_FENCE);
	barrier(CLK_GLOBAL_MEM_FENCE);
	#endif
}

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
         barrier(CLK_GLOBAL_MEM_FENCE);
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
#def_module() marquardt_pekunov(NAME, n, FUN, MaxIters) {
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
			_global(2) int * buf,
			_global(MaxIters*22) int * barriers,
			_global(1) float * FF) {
		int work_size = n*n > nProbes ? n*n : nProbes;
		int rest = work_size % (n*n);
		if (rest) work_size += n*n - rest;

		if (init) {
			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, nProbes, mu0, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, FF);
			plan_group_typize(NULL, n*n);
		} else {
			int id = plan_vector_id();
			float mu = mu0;
			float r = 0.1f;
			float x[n];
			for (int i = 0; i < n; i++)
				x[i] = x0[i];
			float Fk1 = @goal:-write(FUN).;
			double d = 1E30;
			int iters = 0;
			int Lk1 = 5*nProbes;
			if (id == 0) {
				#ifdef ON_GPU
				atomic_xchg(buf, 0);
				#else
				buf[0] = 0;
				#endif
			}
			BARRIER(work_size, (volatile __global int *) barriers); barriers++;
			do {
				if (id < nProbes)
					for (int i = 0; i < n; i++)
						x[i] = x0[i] + (r - 2*r*genrandom(&SEEDS[id]));
				else
					for (int i = 0; i < n; i++)
						x[i] = x0[i];
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				float Fp = @goal:-write(FUN).;
				if (id < n)
					#ifdef ON_GPU
					atomic_xchg(B+id, Fk1);
					#else
					B[id] = Fk1;
					#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id < n) {
					#ifdef ON_GPU
					atomic_xchg(iRow+id, 0);
					#else
					iRow[id] = 0;
					#endif
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				#ifdef ON_GPU
				atomic_min_float(B + id % n, Fp);
				#else
				if (B[id % n] > Fp) B[id % n] = Fp;
				#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (Fp < Fk1)
					#ifdef ON_GPU
					atomic_inc(iRow + id % n);
					#else
					iRow[id % n]++;
					#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id == 0) {
					for (int i = 1; i < n; i++) {
						atomic_add(iRow, iRow[i]);
						mem_fence(CLK_GLOBAL_MEM_FENCE);
					}
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id == 0)
					for (int i = 1; i < n; i++) {
						if (B[i] < B[0])
							#ifdef ON_GPU
							atomic_xchg(B, B[i]);
							#else
							B[0] = B[i];
							#endif
							mem_fence(CLK_GLOBAL_MEM_FENCE);
						}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				int Lk = atomic_add(iRow, 0);
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id == 0)
					#ifdef ON_GPU
					atomic_xchg(iRow, n*n*nProbes);
					#else
					iRow[0] = n*n*nProbes;
					#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				Fk1 = B[0];
				if (Fk1 == Fp)
					#ifdef ON_GPU
					atomic_min(iRow, id);
					#else
					if (id < iRow[0]) iRow[0] = id;
					#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id == 0)
					for (int i = 0; i < n; i++)
						#ifdef ON_GPU
						atomic_xchg(x1+i, x0[i]);
						#else
						x1[i] = x0[i];
						#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (iRow[0] == id)
					for (int i = 0; i < n; i++)
						#ifdef ON_GPU
						atomic_xchg(x1+i, x[i]);
						#else
						x1[i] = x[i];
						#endif
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (Lk > 0) {
					if (Lk < Lk1) {
						if (r < 0.1f) {
							r *= 3.0f;
						}
						mu /= (2.0f*Lk/Lk1 + mu);
					} else if (Lk > Lk1) {
						if (r > 0.001f) {
							r /= 1.2f;
						}
						mu += 15.0f*(Lk-Lk1)/(Lk1+1);
					}
					if (mu < mu_min) mu = mu_min;
				} else mu = mu_min;
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
						#ifdef ON_GPU
						atomic_xchg(GRAD+i, 0.5f*(fp - fm)/delta);
						atomic_xchg(A+id, mu + (fp-2.0f*Fk1+fm)/(delta*delta));
						#else
						GRAD[j] = 0.5f*(fp - fm)/delta;
						A[id] = mu + (fp-2.0f*Fk1+fm)/(delta*delta);
						#endif
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
						#ifdef ON_GPU
						atomic_xchg(A+id, (gp - gm)/(2.0f*delta));
						#else
						A[id] = (gp - gm)/(2.0f*delta);
						#endif
					}
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++)
					x[i] = x1[i];
				barrier(CLK_GLOBAL_MEM_FENCE);
				d = 0.0;
				for (int i = 0; i < n; i++) {
					float g = GRAD[i];
					d += g*g;
				}
				d = sqrt(d);
				if (d <= EPS || (iters + 1) >= MaxIters) {
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					if (id == 0) {
						#ifdef ON_GPU
						atomic_xchg(buf, iters+1);
						atomic_xchg(FF, Fk1);
						#else
						buf[0] = iters+1;
						*FF = Fk1;
						#endif
					}
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					break;
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (_GetLU(n, iRow, A, LU, buf+1, D)) {
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					_SolveLU(n, iRow, LU, GRAD, D);
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					float omega = 1.0f;
					float step = 1.0f;
					float x2[n];
					while (omega > LEPS && step > LEPS) {
						step = 0.0f;
						for (int i = 0; i < n; i++) {
							float ds = omega*D[i];
							x2[i] = x[i];
							x[i] -= ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						float Fi = @goal:-write(FUN).;
						if (Fi < Fk1) {
							Fk1 = Fi;
						} else {
							for (int i = 0; i < n; i++)
								x[i] = x2[i];
							omega *= 0.5f;
						}
					}
				} else {
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					if (id == 0) {
						#ifdef ON_GPU
						atomic_xchg(buf, iters);
						#else
						buf[0] = iters;
						#endif
					}
					BARRIER(work_size, (volatile __global int *) barriers); barriers++;
					break;
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				if (id == 0) {
					#ifdef ON_GPU
					for (int i = 0; i < n; i++) {
						atomic_xchg(x0+i, x[i]);
						atomic_xchg(x1+i, x[i]);
					}
					#else
					for (int i = 0; i < n; i++)
						x0[i] = x1[i] = x[i];
					#endif
				}
				BARRIER(work_size, (volatile __global int *) barriers); barriers++;
				iters++;
				Lk1 = Lk;
			} while (true);
		}
	}
};

const int max_iters = 30;

marquardt_pekunov('min_m_p', 3, '(100.0f*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(2.0f-x[0])*(2.0f-x[0])) + ((x[2]-3.0f)*(x[2]-3.0f)) + ((4.0f-x[1])*(4.0f-x[1]))', max_iters)

int main() {
	const int nProbes = 3*3*150;
	float ITERS = 0.0f;
	float Total = 0.0f;
	for (unsigned int seed0 = 0; seed0 < 40; seed0++) {
		float x0[3] = { 2.0f, 6.0f, -5.0f }, x1[3];
		unsigned int SEEDS[nProbes] = { 0 };
		int iRow[3];
		float A[9];
		float LU[9];
		float B[3];
		float GRAD[3];
		float D[3];
		int buf[2] = { 0 };
		int barriers[(max_iters+1)*22] = { 0 };
		float FF;
		unsigned int seed = seed0*1500;
		for (int i = 0; i < nProbes; i++)
			SEEDS[i] = (unsigned int)(100000*genrandom(&seed));
		min_m_p(true, 1E-4f, nProbes, 10.0f, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, &FF);
		cout << buf[0] << endl;
		for (int i = 0; i < 3; i++)
			cout << x1[i] << " ";
		cout << endl << "F = " << FF << endl;
		Total += FF;
		ITERS += buf[0];
	}
	cout << "Average F = " << (Total/40) << endl;
	cout << "Average ITERS = " << (ITERS/40) << endl;
}
