#pragma plan vectorized

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#pragma plan gpu begin

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#pragma plan gpu end

#pragma plan common begin

#define delta 0.0000001
#define LEPS 0.000000001
#define GOOD_EPS 0.00001
#define mu_min 0.000001

#define QRAN_SHIFT ((unsigned int) 15)
#define QRAN_MASK ((unsigned int)((1 << QRAN_SHIFT) - 1))
#define QRAN_MAX ((unsigned int) QRAN_MASK)
#define QRAN_A ((unsigned int) 1664525)
#define QRAN_C ((unsigned int)1013904223)

double genrandom(__global unsigned int * RandSeed) {
	#ifdef __GPU__
	atomic_xchg(RandSeed, ((long) QRAN_A * atomic_add(RandSeed, 0) + QRAN_C) & 0xFFFFFFFF);
	return 1.0*((atomic_add(RandSeed, 0) >> 16) & QRAN_MAX)/QRAN_MAX;
	#else
	*RandSeed = ((long long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	return 1.0*(((*RandSeed) >> 16) & QRAN_MAX)/QRAN_MAX;
	#endif
}

#ifdef __GPU__
double atomic_xchg_double(volatile global double* addr, double val) {
    unsigned long old = atom_xchg((volatile global unsigned long*)addr, as_long(val));
    return as_double(old);
}
double atomic_sub_double(volatile __global double* addr, double val) {
    unsigned long old, next;
    double ret = *addr;
    do {
        old = as_ulong(*addr);
        next = as_ulong(as_double(old) - val);
    } while (atom_cmpxchg((volatile __global unsigned long*)addr, old, next) != old);
    return ret;
}
double atomic_add_double(volatile __global double* addr, double val) {
    unsigned long old, next;
    double ret = *addr;
    do {
        old = as_ulong(*addr);
        next = as_ulong(as_double(old) + val);
    } while (atom_cmpxchg((volatile __global unsigned long*)addr, old, next) != old);
    return ret;
}
double atomic_mul_double(volatile __global double* addr, double val) {
    unsigned long old, next;
    double ret = *addr;
    do {
        old = as_ulong(*addr);
        next = as_ulong(as_double(old) * val);
    } while (atom_cmpxchg((volatile __global unsigned long*)addr, old, next) != old);
    return ret;
}
void atomic_min_double(volatile __global double* addr, double val) {
    unsigned long old, next;
    do {
        old = as_ulong(*addr);
        if (as_double(old) <= val) break;
        next = as_ulong(val);
    } while (atom_cmpxchg((volatile __global unsigned long*)addr, old, next) != old);
}
void atomic_max_double(volatile __global double* addr, double val) {
    unsigned long old, next;
    do {
        old = as_ulong(*addr);
        if (as_double(old) >= val) break;
        next = as_ulong(val);
    } while (atom_cmpxchg((volatile __global unsigned long*)addr, old, next) != old);
}
#else
double atomic_sub_double(volatile __global double* addr, double val) {
        double ret = *addr;
	*addr -= val;
	return ret;
}
double atomic_add_double(volatile __global double* addr, double val) {
        double ret = *addr;
	*addr += val;
	return ret;
}
double atomic_mul_double(volatile __global double* addr, double val) {
        double ret = *addr;
	*addr *= val;
	return ret;
}
void atomic_min_double(volatile __global double* addr, double val) {
	if (*addr > val) *addr = val;
}
void atomic_max_double(volatile __global double* addr, double val) {
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

int _GetLU(int NN, __global int * iRow, __global double * A, __global double * LU, __global int * iBig, __global int * stop, __global double * Big, __global int * barriers)
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
        atomic_xchg_double(LU + k + i, atomic_add_double(A + k + i, 0.0));
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
       atomic_xchg_double(Big, 0.0);
       #else
       *iBig = i;
       *Big = 0.0;
       #endif
    }
    BARRIER(barriers); barriers++;
    double size = 0.0;

    if (id >= i && id < NN) {
       size = fabs(atomic_add_double(LU+atomic_add(iRow+id, 0)*NN+i, 0.0));
       #ifdef __GPU__
       atomic_max_double(Big, size);
       #else
       if (size > *Big) *Big = size;
       #endif
    }
    BARRIER(barriers); barriers++;
    if (id >= i && id < NN) {
       if (atomic_add_double(Big, 0.0) == size)
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
    double Divider = atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+i, 0.0);
    if (fabs(Divider) < 1E-12)
       #ifdef __GPU__
       atomic_inc(stop);
       #else
       iBig[1]++;
       #endif
    double Kf = !atomic_add(stop, 0) ? 1.0/Divider : 1.0;
    BARRIER(barriers); barriers++;
    if (id == i)
       #ifdef __GPU__
       atomic_xchg_double(LU+atomic_add(iRow+i, 0)*NN+i, Kf);
       #else
       LU[atomic_add(iRow+i, 0)*NN+i] = Kf;
       #endif
    BARRIER(barriers); barriers++;
    for (j=i+1;j<NN;j++)
        {
         double Fact = Kf*atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+i, 0.0);
         BARRIER(barriers); barriers++;
         if (id == j)
            #ifdef __GPU__
            atomic_xchg_double(LU+atomic_add(iRow+j, 0)*NN+i, Fact);
            #else
            LU[atomic_add(iRow+j, 0)*NN+i] = Fact;
            #endif
         BARRIER(barriers); barriers++;
         if (id > i && id < NN)
            atomic_sub_double(LU+atomic_add(iRow+j, 0)*NN+id, Fact*atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+id, 0.0));
         BARRIER(barriers); barriers++;
        }
   }
 if (!atomic_add(stop, 0) && id == NN-1)
    #ifdef __GPU__
    atomic_xchg_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 1.0/atomic_add_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0));
    #else
    LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1] = 1.0/LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1];
    #endif
 BARRIER(barriers);
 return !atomic_add(stop, 0);
}

void _SolveLU(int NN, __global int * iRow, __global double * LU, __global double * Y, __global double * X, __global int * barriers)
{
 int id = plan_vector_id();

 int i,j,k;
 if (id == 0)
    #ifdef __GPU__
    atomic_xchg_double(X, atomic_add_double(Y+atomic_add(iRow, 0), 0.0));
    #else
    X[0] = Y[iRow[0]];
    #endif
 BARRIER(barriers); barriers++;
 for (i=1;i<NN;i++)
     {
      if (id == i)
         #ifdef __GPU__
         atomic_xchg_double(X+i, atomic_add_double(Y+atomic_add(iRow+i, 0), 0.0));
         #else
         X[i] = Y[iRow[i]];
         #endif
      BARRIER(barriers); barriers++;

      if (id < i)
         atomic_sub_double(X+i, atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+id, 0.0)*atomic_add_double(X+id, 0.0));
      BARRIER(barriers); barriers++;
     }

 if (id == NN-1) atomic_mul_double(X+NN-1, atomic_add_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0));
 BARRIER(barriers); barriers++;

 for (i=1,j=NN-2;i<NN;i++,j--)
     {
      if (id > j && id < NN)
         atomic_sub_double(X+j, atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+id, 0.0)*atomic_add_double(X+id, 0.0));
      BARRIER(barriers); barriers++;
      if (id == j) atomic_mul_double(X+j, atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+j, 0.0));
      BARRIER(barriers); barriers++;
     }
}

#pragma plan common end

// n -- размерность пространства
#def_module() marquardt_pekunov(NAME, n, FUN, MaxIters) {
@goal:-brackets_off.
	reenterable @goal:-write(NAME).(bool init, double EPS, int nProbes, double mu0,
			_global(n) double * x0, _global(n) double * x1,
			_global(__planned__.nProbes) unsigned int * SEEDS,
			_global(n) int * iRow,
			_global(n*n) double * A,
			_global(n*n) double * LU,
			_global(n) double * B,
			_global(n) double * GRAD,
			_global(n) double * D,
			_global(3) int * buf,
			_global((MaxIters+1)*(23+(2+4*n)+(3+6*n+3*n*n))) int * barriers,
			_global(1) double * FF) {
		int work_size = n*n > nProbes ? n*n : nProbes;

		if (init) {
			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, nProbes, mu0, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, FF);
			plan_group_vectorize(NULL);
		} else {
			int id = plan_vector_id();
			double mu = mu0;
			double r = 0.1;
			double x[n];
			for (int i = 0; i < n; i++)
				x[i] = atomic_add_double(x0+i, 0.0);
			double Fk1 = @goal:-write(FUN).;
			double d = 1E30;
			double dk = 0.0;
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
						x[i] = atomic_add_double(x0+i, 0.0) + (r - 2*r*genrandom(SEEDS+id));
				else
					for (int i = 0; i < n; i++)
						x[i] = atomic_add_double(x0+i, 0.0);
				BARRIER((volatile __global int *) barriers); barriers++;
				double Fp = @goal:-write(FUN).;
				if (id < n)
					#ifdef __GPU__
					atomic_xchg_double(B+id, Fk1);
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
				atomic_min_double(B + id % n, Fp);
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
						if (atomic_add_double(B+i, 0.0) < atomic_add_double(B, 0.0))
							#ifdef __GPU__
							atomic_xchg_double(B, atomic_add_double(B+i, 0.0));
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
				Fk1 = atomic_add_double(B, 0.0);
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
						atomic_xchg_double(x1+i, atomic_add_double(x0+i, 0.0));
						#else
						x1[i] = x0[i];
						#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				if (atomic_add(iRow, 0) == id)
					for (int i = 0; i < n; i++)
						#ifdef __GPU__
						atomic_xchg_double(x1+i, x[i]);
						#else
						x1[i] = x[i];
						#endif
				BARRIER((volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++) {
					double s = atomic_add_double(x1+i, 0.0) - atomic_add_double(x0+i, 0.0);
					dk += s*s;
				}
				dk = sqrt(dk);
				if (Lk > 0) {
					if (Lk < Lk1) {
						if (r < 1.0) {
							r *= 5.0;
						}
						mu /= (2.0*Lk1/(Lk+1) + mu);
					} else if (Lk > Lk1) {
						if (r > 0.0001) {
							r /= 5.0;
						}
						mu += 10.0*(Lk-Lk1)/(Lk1+1);
					}
					if (mu < mu_min) mu = mu_min;
				} else mu = mu_min;
				BARRIER((volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++)
					x[i] = atomic_add_double(x1+i, 0.0);
				if (id < n*n) {
					int i = id / n;
					int j = id % n;
					if (i == j) {
						x[i] += delta;
						double fp = @goal:-write(FUN).;
						x[i] -= 2*delta;
						double fm = @goal:-write(FUN).;
						#ifdef __GPU__
						atomic_xchg_double(GRAD+i, 0.5*(fp - fm)/delta);
						atomic_xchg_double(A+id, mu + (fp-2.0*Fk1+fm)/(delta*delta));
						#else
						GRAD[j] = 0.5*(fp - fm)/delta;
						A[id] = mu + (fp-2.0*Fk1+fm)/(delta*delta);
						#endif
					} else {
						x[i] += delta;
						x[j] += delta;
						double fpp = @goal:-write(FUN).;
						x[j] -= 2*delta;
						double fpm = @goal:-write(FUN).;
						double gp = (fpp-fpm)/(2.0*delta);
						x[i] -= 2*delta;
						double fmm = @goal:-write(FUN).;
						x[j] += 2*delta;
						double fmp = @goal:-write(FUN).;
						double gm = (fmp-fmm)/(2.0*delta);
						#ifdef __GPU__
						atomic_xchg_double(A+id, (gp - gm)/(2.0*delta));
						#else
						A[id] = (gp - gm)/(2.0*delta);
						#endif
					}
				}
				BARRIER((volatile __global int *) barriers); barriers++;
				for (int i = 0; i < n; i++)
					x[i] = atomic_add_double(x1+i, 0.0);
				BARRIER((volatile __global int *) barriers); barriers++;
				d = 0.0;
				for (int i = 0; i < n; i++) {
					double g = atomic_add_double(GRAD+i, 0.0);
					d += g*g;
				}
				d = sqrt(d);
				if (dk <= EPS && d <= EPS || (iters + 1) >= MaxIters) {
					BARRIER((volatile __global int *) barriers); barriers++;
					if (id == 0) {
						#ifdef __GPU__
						atomic_xchg(buf, iters+1);
						atomic_xchg_double(FF, Fk1);
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
					double omega = max(1.0,d);
					double step = 1.0;
					double x2[n];
					dk = 0.0;
					while (omega > LEPS && step > LEPS) {
						step = 0.0;
						for (int i = 0; i < n; i++) {
							double ds = omega*atomic_add_double(D+i, 0.0);
							x2[i] = x[i];
							x[i] -= ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						double Fi = @goal:-write(FUN).;
						if (Fi < Fk1) {
							Fk1 = Fi;
							dk += omega;
						} else {
							for (int i = 0; i < n; i++)
								x[i] = x2[i];
							omega *= 0.5;
						}
					}
				} else {
					barriers += 3 + 6*n + n*n*3;
					if (id == 0) {
						#ifdef __GPU__
						atomic_xchg(buf, iters+1);
						atomic_xchg_double(FF, Fk1);
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
						atomic_xchg_double(x0+i, x[i]);
						atomic_xchg_double(x1+i, x[i]);
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

const int max_iters = 2500;
const int n = 3;

marquardt_pekunov('min_m_p', n, '(100.0*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(2.0-x[0])*(2.0-x[0])) + ((x[2]-3.0)*(x[2]-3.0)) + ((4.0-x[1])*(4.0-x[1]))', max_iters)

int main() {
	const int nProbes = n*n*150;
	const int nPoints = 100;
	double ITERS = 0.0;
	double Total = 0.0;
	int nGOOD = 0;
	unsigned int seed_points = 184415;
	double rs[n] = { 3.0, 6.0, 5.0 };
	for (unsigned int k = 0; k < nPoints; k++) {
		double x0[n], x1[n];

		for (int i = 0; i < n; i++)
			x0[i] = rs[i] - 2*rs[i]*genrandom(&seed_points);

		unsigned int SEEDS[nProbes] = { 0 };
		int iRow[n];
		double A[n*n];
		double LU[n*n];
		double B[n];
		double GRAD[n];
		double D[n];
		int buf[3] = { 0 };
		int barriers[(max_iters+1)*(23+(2+4*n)+(3+6*n+3*n*n))] = { 0 };
		double FF;

		unsigned int seed = 184415;
		for (int i = 0; i < nProbes; i++)
			SEEDS[i] = (unsigned int)(100000*genrandom(&seed));

		min_m_p(true, 1E-6, nProbes, 10.0, x0, x1, SEEDS, iRow, A, LU, B, GRAD, D, buf, barriers, &FF);
		cout << buf[0] << endl;
		for (int i = 0; i < n; i++)
			cout << x1[i] << " ";
		cout << endl << "F = " << FF << endl;
		Total += FF;
		ITERS += buf[0];
		if (fabs(FF) < GOOD_EPS) nGOOD++;
	}
	cout << "Average F = " << (Total/nPoints) << endl;
	cout << "Average ITERS = " << (ITERS/nPoints) << endl;
	cout << "nGOODS = " << nGOOD << endl;
}
