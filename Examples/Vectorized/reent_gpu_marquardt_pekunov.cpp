#pragma plan vectorized

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#pragma plan gpu begin

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable

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
	#ifdef __GPU__
	atomic_xchg(RandSeed, ((long) QRAN_A * atomic_add(RandSeed, 0) + QRAN_C) & 0xFFFFFFFF);
	return 1.0f*((atomic_add(RandSeed, 0) >> 16) & QRAN_MAX)/QRAN_MAX;
	#else
	*RandSeed = ((long long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	return 1.0f*(((*RandSeed) >> 16) & QRAN_MAX)/QRAN_MAX;
	#endif
}

#ifdef __GPU__
float atomic_sub_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    float ret = *addr;
    do {
        old = as_uint(*addr);
        next = as_uint(as_float(old) - val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
    return ret;
}
float atomic_add_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    float ret = *addr;
    do {
        old = as_uint(*addr);
        next = as_uint(as_float(old) + val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
    return ret;
}
float atomic_mul_float(volatile __global float* addr, float val) {
    unsigned int old, next;
    float ret = *addr;
    do {
        old = as_uint(*addr);
        next = as_uint(as_float(old) * val);
    } while (atomic_cmpxchg((volatile __global unsigned int*)addr, old, next) != old);
    return ret;
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
float atomic_sub_float(volatile __global float* addr, float val) {
        float ret = *addr;
	*addr -= val;
	return ret;
}
float atomic_add_float(volatile __global float* addr, float val) {
        float ret = *addr;
	*addr += val;
	return ret;
}
float atomic_mul_float(volatile __global float* addr, float val) {
        float ret = *addr;
	*addr *= val;
	return ret;
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

void BARRIER(volatile __global int * barriers) {
	#ifdef __GPU__
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

int _GetLU(int NN, __global int * iRow, __global float * A, __global float * LU, __global int * iBig, __global int * stop, __global float * Big, __global int * barriers)
{
 int i, j;

 int id = plan_vector_id();

 int k = id*NN;

 if (id == 0)
    #ifdef __GPU__
    atomic_xchg(stop, 0);
    #else
    *stop = 0;
    #endif
 BARRIER(barriers); barriers++;

 if (id < NN) {
    #ifdef __GPU__
    atomic_xchg(iRow+id, id);
    for (i = 0; i < NN; i++)
        atomic_xchg(LU + k + i, atomic_add_float(A + k + i, 0.0f));
    #else
    iRow[id] = id;
    for (i = 0; i < NN; i++)
        LU[k + i] = A[k + i];
    #endif
 }

 BARRIER(barriers); barriers++;

 for (i=0; !atomic_add(stop, 0) && i<NN-1; i++)
   {
    if (id == 0) {
       #ifdef __GPU__
       atomic_xchg(iBig, i);
       atomic_xchg(Big, 0.0f);
       #else
       *iBig = i;
       *Big = 0.0f;
       #endif
    }
    BARRIER(barriers); barriers++;
    float size = 0.0f;

    if (id >= i && id < NN) {
       size = fabs(atomic_add_float(LU+atomic_add(iRow+id, 0)*NN+i, 0.0f));
       #ifdef __GPU__
       atomic_max_float(Big, size);
       #else
       if (size > *Big) *Big = size;
       #endif
    }
    BARRIER(barriers); barriers++;
    if (id >= i && id < NN) {
       if (atomic_add_float(Big, 0.0f) == size)
          #ifdef __GPU__
          atomic_max(iBig, id);
          #else
          if (id > *iBig) *iBig = id;
          #endif
    }
    BARRIER(barriers); barriers++;

    int ii = atomic_add(iBig, 0);
    if (ii != i && id == 0)
       {
        #ifdef __GPU__
        int V = atomic_add(iRow+i, 0);
        atomic_xchg(iRow+i, atomic_add(iRow+ii, 0));
        atomic_xchg(iRow+ii, V);
        #else
        int V = iRow[i];
        iRow[i] = iRow[ii];
        iRow[ii] = V;
        #endif
       }
    BARRIER(barriers); barriers++;
    float Divider = atomic_add_float(LU+atomic_add(iRow+i, 0)*NN+i, 0.0f);
    if (fabs(Divider) < 1E-12)
       #ifdef __GPU__
       atomic_inc(stop);
       #else
       iBig[1]++;
       #endif
    float Kf = !atomic_add(stop, 0) ? 1.0/Divider : 1.0;
    BARRIER(barriers); barriers++;
    if (id == i)
       #ifdef __GPU__
       atomic_xchg(LU+atomic_add(iRow+i, 0)*NN+i, Kf);
       #else
       LU[atomic_add(iRow+i, 0)*NN+i] = Kf;
       #endif
    BARRIER(barriers); barriers++;
    for (j=i+1;j<NN;j++)
        {
         float Fact = Kf*atomic_add_float(LU+atomic_add(iRow+j, 0)*NN+i, 0.0f);
         BARRIER(barriers); barriers++;
         if (id == j)
            #ifdef __GPU__
            atomic_xchg(LU+atomic_add(iRow+j, 0)*NN+i, Fact);
            #else
            LU[atomic_add(iRow+j, 0)*NN+i] = Fact;
            #endif
         BARRIER(barriers); barriers++;
         if (id > i && id < NN)
            atomic_sub_float(LU+atomic_add(iRow+j, 0)*NN+id, Fact*atomic_add_float(LU+atomic_add(iRow+i, 0)*NN+id, 0.0f));
         BARRIER(barriers); barriers++;
        }
   }
 if (!atomic_add(stop, 0) && id == NN-1)
    #ifdef __GPU__
    atomic_xchg(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 1.0/atomic_add_float(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0f));
    #else
    LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1] = 1.0/LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1];
    #endif
 BARRIER(barriers);
 return !atomic_add(stop, 0);
}

void _SolveLU(int NN, __global int * iRow, __global float * LU, __global float * Y, __global float * X, __global int * barriers)
{
 int id = plan_vector_id();

 int i,j,k;
 if (id == 0)
    #ifdef __GPU__
    atomic_xchg(X, atomic_add_float(Y+atomic_add(iRow, 0), 0.0f));
    #else
    X[0] = Y[iRow[0]];
    #endif
 BARRIER(barriers); barriers++;
 for (i=1;i<NN;i++)
     {
      if (id == i)
         #ifdef __GPU__
         atomic_xchg(X+i, atomic_add_float(Y+atomic_add(iRow+i, 0), 0.0f));
         #else
         X[i] = Y[iRow[i]];
         #endif
      BARRIER(barriers); barriers++;

      if (id < i)
         atomic_sub_float(X+i, atomic_add_float(LU+atomic_add(iRow+i, 0)*NN+id, 0.0f)*atomic_add_float(X+id, 0.0f));
      BARRIER(barriers); barriers++;
     }

 if (id == NN-1) atomic_mul_float(X+NN-1, atomic_add_float(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0f));
 BARRIER(barriers); barriers++;

 for (i=1,j=NN-2;i<NN;i++,j--)
     {
      if (id > j && id < NN)
         atomic_sub_float(X+j, atomic_add_float(LU+atomic_add(iRow+j, 0)*NN+id, 0.0f)*atomic_add_float(X+id, 0.0f));
      BARRIER(barriers); barriers++;
      if (id == j) atomic_mul_float(X+j, atomic_add_float(LU+atomic_add(iRow+j, 0)*NN+j, 0.0f));
      BARRIER(barriers); barriers++;
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
			_global(3) int * buf,
			_global((MaxIters+1)*(23+(2+4*n)+(3+6*n+3*n*n))) int * barriers,
			_global(1) float * FF) {
		int work_size = n*n > nProbes ? n*n : nProbes;

		if (init) {
			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, nProbes, mu0, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, FF);
			plan_group_vectorize(NULL);
		} else {
			int id = plan_vector_id();
			float mu = mu0;
			float r = 0.1f;
			float x[n];
			for (int i = 0; i < n; i++)
				x[i] = atomic_add_float(x0+i, 0.0f);
			float Fk1 = @goal:-write(FUN).;
			double d = 1E30;
			int iters = 0;
			int Lk1 = 5*nProbes;
			if (id == 0) {
				#ifdef __GPU__
				atomic_xchg(buf, 0);
				#else
				buf[0] = 0;
				#endif
			}
			BARRIER((volatile __global int *) barriers); barriers++;
			do {
				if (id < nProbes)
					for (int i = 0; i < n; i++)
						x[i] = atomic_add_float(x0+i, 0.0f) + (r - 2*r*genrandom(SEEDS+id));
				else
					for (int i = 0; i < n; i++)
						x[i] = atomic_add_float(x0+i, 0.0f);
				BARRIER((volatile __global int *) barriers); barriers++;
				float Fp = @goal:-write(FUN).;
				if (id < n)
					#ifdef __GPU__
					atomic_xchg(B+id, Fk1);
					#else
					B[id] = Fk1;
					#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id < n) {
					#ifdef __GPU__
					atomic_xchg(iRow+id, 0);
					#else
					iRow[id] = 0;
					#endif
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				#ifdef __GPU__
				atomic_min_float(B + id % n, Fp);
				#else
				if (B[id % n] > Fp) B[id % n] = Fp;
				#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (Fp < Fk1)
					#ifdef __GPU__
					atomic_inc(iRow + id % n);
					#else
					iRow[id % n]++;
					#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id == 0) {
					for (int i = 1; i < n; i++) {
						atomic_add(iRow, atomic_add(iRow+i, 0));
						mem_fence(CLK_GLOBAL_MEM_FENCE);
					}
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id == 0)
					for (int i = 1; i < n; i++) {
						if (atomic_add_float(B+i, 0.0f) < atomic_add_float(B, 0.0f))
							#ifdef __GPU__
							atomic_xchg(B, atomic_add_float(B+i, 0.0f));
							#else
							B[0] = B[i];
							#endif
							mem_fence(CLK_GLOBAL_MEM_FENCE);
						}
				BARRIER((volatile __global int *) barriers); barriers++;
				int Lk = atomic_add(iRow, 0);
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id == 0)
					#ifdef __GPU__
					atomic_xchg(iRow, n*n*nProbes);
					#else
					iRow[0] = n*n*nProbes;
					#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				Fk1 = atomic_add_float(B, 0.0f);
				if (Fk1 == Fp)
					#ifdef __GPU__
					atomic_min(iRow, id);
					#else
					if (id < iRow[0]) iRow[0] = id;
					#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id == 0)
					for (int i = 0; i < n; i++)
						#ifdef __GPU__
						atomic_xchg(x1+i, atomic_add_float(x0+i, 0.0f));
						#else
						x1[i] = x0[i];
						#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (atomic_add(iRow, 0) == id)
					for (int i = 0; i < n; i++)
						#ifdef __GPU__
						atomic_xchg(x1+i, x[i]);
						#else
						x1[i] = x[i];
						#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (Lk > 0) {
					if (Lk < Lk1) {
						if (r < 1.0f) {
							r *= 3.0f;
						}
						mu /= (2.0f*Lk/Lk1 + mu);
					} else if (Lk > Lk1) {
						if (r > 0.0001f) {
							r /= 3.0f;
						}
						mu += 10.0f*(Lk-Lk1)/(Lk1+1);
					}
					if (mu < mu_min) mu = mu_min;
				} else mu = mu_min;
				BARRIER((volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++)
					x[i] = atomic_add_float(x1+i, 0.0f);
				if (id < n*n) {
					int i = id / n;
					int j = id % n;
					if (i == j) {
						x[i] += delta;
						float fp = @goal:-write(FUN).;
						x[i] -= 2*delta;
						float fm = @goal:-write(FUN).;
						#ifdef __GPU__
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
						#ifdef __GPU__
						atomic_xchg(A+id, (gp - gm)/(2.0f*delta));
						#else
						A[id] = (gp - gm)/(2.0f*delta);
						#endif
					}
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++)
					x[i] = atomic_add_float(x1+i, 0.0f);
				BARRIER((volatile __global int *) barriers); barriers++;
				d = 0.0;
				for (int i = 0; i < n; i++) {
					float g = atomic_add_float(GRAD+i, 0.0f);
					d += g*g;
				}
				d = sqrt(d);
				if (d <= EPS || (iters + 1) >= MaxIters) {
					BARRIER((volatile __global int *) barriers); barriers++;
					if (id == 0) {
						#ifdef __GPU__
						atomic_xchg(buf, iters+1);
						atomic_xchg(FF, Fk1);
						#else
						buf[0] = iters+1;
						*FF = Fk1;
						#endif
					}
					BARRIER((volatile __global int *) barriers); barriers++;
					break;
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				if (_GetLU(n, iRow, A, LU, buf+1, buf+2, D, barriers)) {
					barriers += 3 + 6*n + n*n*3;
					_SolveLU(n, iRow, LU, GRAD, D, barriers);
					barriers += 2 + 4*n;
					float omega = 1.0f;
					float step = 1.0f;
					float x2[n];
					while (omega > LEPS && step > LEPS) {
						step = 0.0f;
						for (int i = 0; i < n; i++) {
							float ds = omega*atomic_add_float(D+i, 0.0f);
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
					barriers += 3 + 6*n + n*n*3;
					if (id == 0) {
						#ifdef __GPU__
						atomic_xchg(buf, iters+1);
						atomic_xchg(FF, Fk1);
						#else
						buf[0] = iters+1;
						*FF = Fk1;
						#endif
					}
					BARRIER((volatile __global int *) barriers); barriers++;
					break;
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				if (id == 0) {
					#ifdef __GPU__
					for (int i = 0; i < n; i++) {
						atomic_xchg(x0+i, x[i]);
						atomic_xchg(x1+i, x[i]);
					}
					#else
					for (int i = 0; i < n; i++)
						x0[i] = x1[i] = x[i];
					#endif
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				iters++;
				Lk1 = Lk;
			} while (true);
		}
	}
};

const int max_iters = 500;
const int n = 3;

marquardt_pekunov('min_m_p', n, '(100.0f*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(2.0f-x[0])*(2.0f-x[0])) + ((x[2]-3.0f)*(x[2]-3.0f)) + ((4.0f-x[1])*(4.0f-x[1]))', max_iters)

int main() {
	const int nProbes = n*n*150;
	const int nPoints = 100;
	float ITERS = 0.0f;
	float Total = 0.0f;
	int nGOOD = 0;
	unsigned int seed_points = 184415;
	float rs[n] = { 3.0f, 6.0f, 5.0f };
	for (unsigned int k = 0; k < nPoints; k++) {
		float x0[n], x1[n];

		for (int i = 0; i < n; i++)
			x0[i] = rs[i] - 2*rs[i]*genrandom(&seed_points);

		unsigned int SEEDS[nProbes] = { 0 };
		int iRow[n];
		float A[n*n];
		float LU[n*n];
		float B[n];
		float GRAD[n];
		float D[n];
		int buf[3] = { 0 };
		int barriers[(max_iters+1)*(23+(2+4*n)+(3+6*n+3*n*n))] = { 0 };
		float FF;

		unsigned int seed = 184415;
		for (int i = 0; i < nProbes; i++)
			SEEDS[i] = (unsigned int)(100000*genrandom(&seed));

		min_m_p(true, 1E-3f, nProbes, 10.0f, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, &FF);
		cout << buf[0] << endl;
		for (int i = 0; i < n; i++)
			cout << x1[i] << " ";
		cout << endl << "F = " << FF << endl;
		Total += FF;
		ITERS += buf[0];
		if (fabs(FF) < LEPS) nGOOD++;
	}
	cout << "Average F = " << (Total/nPoints) << endl;
	cout << "Average ITERS = " << (ITERS/nPoints) << endl;
	cout << "nGOODS = " << nGOOD << endl;
}
