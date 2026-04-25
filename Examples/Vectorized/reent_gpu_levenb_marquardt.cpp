#pragma plan vectorized

#add_scan(clsSolve)

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#pragma plan gpu begin

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#pragma plan gpu end

#define QRAN_SHIFT ((unsigned int) 15)
#define QRAN_MASK ((unsigned int)((1 << QRAN_SHIFT) - 1))
#define QRAN_MAX ((unsigned int) QRAN_MASK)
#define QRAN_A ((unsigned int) 1664525)
#define QRAN_C ((unsigned int)1013904223)

double genrandom(__global unsigned int * RandSeed) {
	#ifdef __GPU__
	*RandSeed = ((long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	#else
	*RandSeed = ((long long) QRAN_A * (*RandSeed) + QRAN_C) & 0xFFFFFFFF;
	#endif
	return 1.0*(((*RandSeed) >> 16) & QRAN_MAX)/QRAN_MAX;
}

#pragma plan common begin

#define delta 0.0000001
#define max_iters 2500
#define LEPS 0.000000001
#define GOOD_EPS 0.00001

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

int _GetLU(int NN, __global int * iRow, __global double * A, __global double * LU, __global int * iBig, __global int * stop, __global double * Big)
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
 barrier(CLK_GLOBAL_MEM_FENCE);

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

 barrier(CLK_GLOBAL_MEM_FENCE);

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
    barrier(CLK_GLOBAL_MEM_FENCE);
    double size = 0.0;

    if (id >= i && id < NN) {
       size = fabs(atomic_add_double(LU+atomic_add(iRow+id, 0)*NN+i, 0.0));
       #ifdef __GPU__
       atomic_max_double(Big, size);
       #else
       if (size > *Big) *Big = size;
       #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
    if (id >= i && id < NN) {
       if (atomic_add_double(Big, 0.0) == size)
          #ifdef __GPU__
          atomic_max(iBig, id);
          #else
          if (id > *iBig) *iBig = id;
          #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE);

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
    barrier(CLK_GLOBAL_MEM_FENCE);
    double Divider = atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+i, 0.0);
    if (fabs(Divider) < 1E-12)
       #ifdef __GPU__
       atomic_inc(stop);
       #else
       iBig[1]++;
       #endif
    double Kf = !atomic_add(stop, 0) ? 1.0/Divider : 1.0;
    barrier(CLK_GLOBAL_MEM_FENCE);
    if (id == i)
       #ifdef __GPU__
       atomic_xchg_double(LU+atomic_add(iRow+i, 0)*NN+i, Kf);
       #else
       LU[atomic_add(iRow+i, 0)*NN+i] = Kf;
       #endif
    barrier(CLK_GLOBAL_MEM_FENCE);
    for (j=i+1;j<NN;j++)
        {
         double Fact = Kf*atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+i, 0.0);
         barrier(CLK_GLOBAL_MEM_FENCE);
         if (id == j)
            #ifdef __GPU__
            atomic_xchg_double(LU+atomic_add(iRow+j, 0)*NN+i, Fact);
            #else
            LU[atomic_add(iRow+j, 0)*NN+i] = Fact;
            #endif
         barrier(CLK_GLOBAL_MEM_FENCE);
         if (id > i && id < NN)
            atomic_sub_double(LU+atomic_add(iRow+j, 0)*NN+id, Fact*atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+id, 0.0));
         barrier(CLK_GLOBAL_MEM_FENCE);
        }
   }
 if (!atomic_add(stop, 0) && id == NN-1)
    #ifdef __GPU__
    atomic_xchg_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 1.0/atomic_add_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0));
    #else
    LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1] = 1.0/LU[(atomic_add(iRow+NN-1, 0)+1)*NN-1];
    #endif
 barrier(CLK_GLOBAL_MEM_FENCE);
 return !atomic_add(stop, 0);
}

void _SolveLU(int NN, __global int * iRow, __global double * LU, __global double * Y, __global double * X)
{
 int id = plan_vector_id();

 int i,j,k;
 if (id == 0)
    #ifdef __GPU__
    atomic_xchg_double(X, atomic_add_double(Y+atomic_add(iRow, 0), 0.0));
    #else
    X[0] = Y[iRow[0]];
    #endif
 barrier(CLK_GLOBAL_MEM_FENCE);
 for (i=1;i<NN;i++)
     {
      if (id == i)
         #ifdef __GPU__
         atomic_xchg_double(X+i, atomic_add_double(Y+atomic_add(iRow+i, 0), 0.0));
         #else
         X[i] = Y[iRow[i]];
         #endif
      barrier(CLK_GLOBAL_MEM_FENCE);

      if (id < i)
         atomic_sub_double(X+i, atomic_add_double(LU+atomic_add(iRow+i, 0)*NN+id, 0.0)*atomic_add_double(X+id, 0.0));
      barrier(CLK_GLOBAL_MEM_FENCE);
     }

 if (id == NN-1) atomic_mul_double(X+NN-1, atomic_add_double(LU+(atomic_add(iRow+NN-1, 0)+1)*NN-1, 0.0));
 barrier(CLK_GLOBAL_MEM_FENCE);

 for (i=1,j=NN-2;i<NN;i++,j--)
     {
      if (id > j && id < NN)
         atomic_sub_double(X+j, atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+id, 0.0)*atomic_add_double(X+id, 0.0));
      barrier(CLK_GLOBAL_MEM_FENCE);
      if (id == j) atomic_mul_double(X+j, atomic_add_double(LU+atomic_add(iRow+j, 0)*NN+j, 0.0));
      barrier(CLK_GLOBAL_MEM_FENCE);
     }
}

#pragma plan common end

// n -- размерность пространства
#def_module() levenberg_marquardt(NAME, FIRSTS, LAST) {
@goal:-brackets_off.
@countl([], 0):-!.
@countl('', 0):-!.
@countl([H|T], N):-
   countl(T, N1),
   N is N1+1,
   !.
@countl(_, 1):-!.
@putf(N, A):-
   write('if (sel & (1<<'),write(N),write(')) f['), write(N), write('] = '), write(A), write(';').
@unroll(_, []):-!.
@unroll(N, [H|T]):-
   putf(N, H),
   N1 is N+1,
   unroll(N1, T),
   !.
@unroll(_, ''):-
   !.
@unroll(N, A):-
   putf(N, A),
   !.
@fn:-
   unroll(0, FIRSTS), countl(FIRSTS, N), unroll(N, LAST).
@n:-countl(FIRSTS, N), N1 is N+1, write('('), write(N1), write(')').
	reenterable @goal:-write(NAME).(bool init, double EPS, double mu0,
			_global(@goal:-n.) double * x0,
			_global(@goal:-n.) int * iRow,
			_global(@goal:-n.*@goal:-n.) double * A,
			_global(@goal:-n.*@goal:-n.) double * LU,
			_global(@goal:-n.*@goal:-n.) double * J0,
			_global(@goal:-n.) double * B,
			_global(@goal:-n.) double * GRAD,
			_global(@goal:-n.) double * D,
			_global(3) int * buf,
			_global(1) double * FF) {
		if (init) {
			int work_size = @goal:-n.*@goal:-n.;

			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, mu0, x0, iRow, A, LU, J0, B, GRAD, D, buf, FF);
			plan_group_typize(NULL, work_size);
		} else {
			int id = plan_vector_id();
			double mu = mu0;
			double dk = 1E30;
			double pk = 0.0;
			double pk1;
			double fk0 = 0.0, dfk0 = 0.0;
			double d = 1E30;
			long sel = (1<<(@goal:-n.))-1;
			if (id == 0) {
				#ifdef __GPU__
				for (int i = 0; i < @goal:-n.; i++)
					atomic_xchg_double(GRAD+i, 0.0);
				atomic_xchg(buf, 0);
				#else
				for (int i = 0; i < @goal:-n.; i++)
					GRAD[i] = 0.0;
				buf[0] = 0;
				#endif
			}
			barrier(CLK_GLOBAL_MEM_FENCE);

			double x[@goal:-n.], f[@goal:-n.];
			double Fk1[@goal:-n.], fk1;
			for (int i = 0; i < @goal:-n.; i++)
				x[i] = atomic_add_double(x0+i, 0.0);
			barrier(CLK_GLOBAL_MEM_FENCE);
			@goal:-fn.;
			barrier(CLK_GLOBAL_MEM_FENCE);
			for (int i = 0; i < @goal:-n.; i++)
				Fk1[i] = f[i];
			barrier(CLK_GLOBAL_MEM_FENCE);
			fk1 = f[0]*f[0];
			for (int i = 1; i < @goal:-n.; i++)
				fk1 += f[i]*f[i];
			do {
				barrier(CLK_GLOBAL_MEM_FENCE);
				for (int i = 0; i < @goal:-n.; i++)
					x[i] = atomic_add_double(x0+i, 0.0);
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < @goal:-n.*@goal:-n.) {
					int i = id / @goal:-n.;
					int j = id % @goal:-n.;
					x[j] += delta;
					sel = 1<<i;
					@goal:-fn.;
					double FP = f[i];
					x[j] -= 2*delta;
					@goal:-fn.;
					double FM = f[i];
					#ifdef __GPU__
					double val = (FP-FM)/(2.0*delta);
					atomic_xchg_double(J0+id, val);
					atomic_xchg_double(LU+id, val);
					#else
					J0[id] = LU[id] = (FP-FM)/(2.0*delta);
					#endif
					x[j] += delta;
					sel = (1<<(@goal:-n.))-1;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id < @goal:-n.*@goal:-n.) {
					int i = id / @goal:-n.;
					int j = id % @goal:-n.;
					double a = 0.0;
					for (int k = 0; k < @goal:-n.; k++) {
						a += atomic_add_double(LU+k*@goal:-n.+i, 0.0)*atomic_add_double(LU+k*@goal:-n.+j, 0.0);
					}
					if (i == j) {
						double g = 0.0;
						for (int k = 0; k < @goal:-n.; k++) {
							g += atomic_add_double(LU+k*@goal:-n.+i, 0.0)*Fk1[k];
						}
						#ifdef __GPU__
						atomic_xchg_double(GRAD+i, g);
						atomic_xchg_double(B+i, -g);
						#else
						GRAD[i] = g;
						B[i] = -g;
						#endif
						a += mu;
					}
					#ifdef __GPU__
					atomic_xchg_double(A+id, a);
					#else
					A[id] = a;
					#endif
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				for (int i = 0; i < @goal:-n.; i++)
					x[i] = atomic_add_double(x0+i, 0.0);
				barrier(CLK_GLOBAL_MEM_FENCE);
				d = 0.0;
				for (int i = 0; i < @goal:-n.; i++) {
					double g = atomic_add_double(GRAD+i, 0.0);
					d += g*g;
				}
				d = sqrt(d);
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (dk <= EPS && d <= EPS || (atomic_add(buf, 0)+1) >= max_iters) {
					if (id == 0) {
						fk1 = 0.0;
						for (int i = 0; i < @goal:-n.; i++)
							fk1 += fabs(Fk1[i]);
						#ifdef __GPU__
						atomic_xchg_double(FF, fk1);
						#else
						*FF = fk1;
						#endif
					}
					barrier(CLK_GLOBAL_MEM_FENCE);
					break;
				}
				if (_GetLU(@goal:-n., iRow, A, LU, buf+1, buf+2, D)) {
					_SolveLU(@goal:-n., iRow, LU, B, D);
					double dfk1 = -atomic_add_double(B, 0.0)*atomic_add_double(D, 0.0);
					double fk1 = Fk1[0]*Fk1[0];
					int first = dk == 1E30;
					barrier(CLK_GLOBAL_MEM_FENCE);
					for (int i = 1; i < @goal:-n.; i++) {
						dfk1 += -atomic_add_double(B+i, 0.0)*atomic_add_double(D+i, 0.0);
						fk1 += Fk1[i]*Fk1[i];
					}
					barrier(CLK_GLOBAL_MEM_FENCE);
					if (id < @goal:-n.) {
						double h = Fk1[id];
						for (int k = 0; k < @goal:-n.; k++)
							h += atomic_add_double(J0+id*@goal:-n.+k, 0.0)*atomic_add_double(D+k, 0.0);
						#ifdef __GPU__
						atomic_xchg_double(B+id, h);
						#else
						B[id] = h;
						#endif
					}
					barrier(CLK_GLOBAL_MEM_FENCE);
					pk1 = atomic_add_double(B, 0.0)*atomic_add_double(B, 0.0);
					for (int i = 1; i < @goal:-n.; i++)
						pk1 += atomic_add_double(B+i, 0.0)*atomic_add_double(B+i, 0.0);
					barrier(CLK_GLOBAL_MEM_FENCE);

					double omega = max(1.0,d);
					double step = 1.0;
					dk = 0.0;
					double x2[@goal:-n.];
					while (omega > LEPS && step > LEPS) {
						step = 0.0;
						for (int i = 0; i < @goal:-n.; i++) {
							double ds = omega*atomic_add_double(D+i, 0.0);
							x2[i] = x[i];
							x[i] += ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						@goal:-fn.;
						barrier(CLK_GLOBAL_MEM_FENCE);
						double fi = 0.0;
						for (int i = 0; i < @goal:-n.; i++) {
							fi += f[i]*f[i];
						}
						barrier(CLK_GLOBAL_MEM_FENCE);
						if (fi < fk1) {
							fk1 = fi;
							dk += omega;
							for (int i = 0; i < @goal:-n.; i++)
								Fk1[i] = f[i];
						} else {
							for (int i = 0; i < @goal:-n.; i++)
								x[i] = x2[i];
							omega *= 0.5;
						}
						barrier(CLK_GLOBAL_MEM_FENCE);
					}
					if (!first) {
						double alphak;
						double a = fk0;
						double b = dfk0;
						double m = fk1 - a - b*dk;
						double q = dfk1 - b;
						double c = (3.0*m - dk*q)/dk/dk;
						double d = (dk*q - 2.0*m)/dk/dk/dk;
						double DISCR = 4.0*c*c - 12.0*d*b;
						if (DISCR < 0.0)
							if (fk0 < fk1) alphak = 0.0;
							else alphak = dk;
						else if (DISCR == 0.0) {
							double t0 = -c/(3.0*d);
							if (2.0*c+6.0*d*t0 > 0.0) alphak = t0;
							else
								if (fk0 < fk1) alphak = 0.0;
								else alphak = dk;
						} else {
							double DD = sqrt(DISCR);
							double t1 = (-2.0*c - DD)/(6.0*d);
							double t2 = (-2.0*c + DD)/(6.0*d);
							if (2.0*c + 6.0*d*t1 > 0.0) alphak = t1;
							else alphak = t2;
						}
						double zk = a + alphak*(b + alphak*(c + alphak*d));
						if (zk >= pk) mu += (zk - pk)/(alphak + EPS);
						else mu /= (3.0 + mu);
					}
					barrier(CLK_GLOBAL_MEM_FENCE);
					fk0 = fk1;
					dfk0 = dfk1;
					pk = pk1;
				} else {
					if (id == 0) {
						fk1 = 0.0;
						for (int i = 0; i < @goal:-n.; i++)
							fk1 += fabs(Fk1[i]);
						#ifdef __GPU__
						atomic_xchg_double(FF, fk1);
						#else
						*FF = fk1;
						#endif
					}
					barrier(CLK_GLOBAL_MEM_FENCE);
					break;
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				if (id == 0) {
					#ifdef __GPU__
					for (int i = 0; i < @goal:-n.; i++) {
						atomic_xchg_double(x0+i, x[i]);
					}
					#else
					for (int i = 0; i < @goal:-n.; i++)
						x0[i] = x[i];
					#endif
				}
				barrier(CLK_GLOBAL_MEM_FENCE);
				#ifdef __GPU__
				if (id == 0) atomic_add(buf, 1);
				#else
				if (id == 0) (*buf)++;
				#endif
			} while (true);
		}
	}
};

#def_pattern clsSolve => levenberg_marquardt (//NAME/@Value, //FIRST/@Value, //LAST/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (solve(\s|\\t)*\((\w+)->{NAME}\,(\s|\\t)*
         (
          (((.+?)->{FIRST}\,)?=>{Predicates.BAL($,',')}(\s|\\t)*)*
          ((.+?)->{LAST}\))?=>{Predicates.BAL($,')')}
         )
         (\s|\\t|\\n)*)\;
  @end
};

solve(solve_l_m, 100.0*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(2.0-x[0])*(2.0-x[0]), (x[2]-3.0)*(x[2]-3.0), (4.0-x[1])*(4.0-x[1]));

const int n = 3;

int main() {
	const int nPoints = 100;
	double ITERS = 0.0;
	double Total = 0.0;
	int nGOOD = 0;
	unsigned int seed_points = 184415;
	double rs[n] = { 3.0, 6.0, 5.0 };
	
	for (unsigned int k = 0; k < nPoints; k++) {
		double x0[n];

		for (int i = 0; i < n; i++)
			x0[i] = rs[i] - 2*rs[i]*genrandom(&seed_points);

		int iRow[n];
		double A[n*n];
		double LU[n*n], J0[n*n];
		double B[n];
		double GRAD[n];
		double D[n];
		int buf[3] = { 0 };
		double FF;

		solve_l_m(true, 1E-6, 10.0, x0, iRow, A, LU, J0, B, GRAD, D, buf, &FF);
		cout << buf[0] << endl;
		for (int i = 0; i < n; i++)
			cout << x0[i] << " ";
		cout << endl << "F = " << FF << endl;
		Total += FF;
		ITERS += buf[0];
		if (fabs(FF) < GOOD_EPS) nGOOD++;
	}
	cout << "Average F = " << (Total/nPoints) << endl;
	cout << "Average ITERS = " << (ITERS/nPoints) << endl;
	cout << "nGOODS = " << nGOOD << endl;
}
