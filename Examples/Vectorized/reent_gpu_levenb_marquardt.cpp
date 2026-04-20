#pragma plan vectorized

#add_scan(clsSolve)

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#pragma plan gpu begin

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable

#define ON_GPU

#pragma plan gpu end

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

#pragma plan common begin

#define delta 0.00001
#define LEPS 0.0001

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
 barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);

 for (i=0; !stop && i<NN-1; i++)
   {
    if (id == 0) {
       *iBig = i;
       *Big = 0.0f;
    }
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
    float size = 0.0f;

    if (id >= i && id < NN) {
       size = fabs(LU[iRow[id]*NN+i]);
       #ifdef ON_GPU
       atomic_max_float(Big, size);
       #else
       if (size > *Big) *Big = size;
       #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
    if (id >= i && id < NN) {
       if (*Big == size)
          #ifdef ON_GPU
          atomic_max(iBig, id);
          #else
          if (id > *iBig) *iBig = id;
          #endif
    }
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);

    if (*iBig!=i && id == 0)
       {
        int V = iRow[i];
        iRow[i] = iRow[*iBig];
        iRow[*iBig] = V;
       }
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
    float Divider = LU[iRow[i]*NN+i];
    if (fabs(Divider) < 1E-12)
       stop = 1;
    float Kf = !stop ? 1.0/Divider : 1.0;
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
    if (id == i) LU[iRow[i]*NN+i] = Kf;
    barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
    for (j=i+1;j<NN;j++)
        {
         float Fact = Kf*LU[iRow[j]*NN+i];
         barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
         if (id == j) LU[iRow[j]*NN+i] = Fact;
         barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
         if (id > i && id < NN)
            atomic_sub_float(&LU[iRow[j]*NN+id], Fact*LU[iRow[i]*NN+id]);
         barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
        }
   }
 if (!stop && id == NN-1) LU[(iRow[NN-1]+1)*NN-1] = 1.0/LU[(iRow[NN-1]+1)*NN-1];
 barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
 return !stop;
}

void _SolveLU(int NN, __global int * iRow, __global float * LU, __global float * Y, __global float * X)
{
 int id = plan_vector_id();

 int i,j,k;
 if (id == 0) X[0] = Y[iRow[0]];
 barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
 for (i=1;i<NN;i++)
     {
      if (id == i) X[i] = Y[iRow[i]];
      barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);

      if (id < i)
         atomic_sub_float(&X[i], LU[iRow[i]*NN+id]*X[id]);
      barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
     }

 if (id == NN-1) X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];
 barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);

 for (i=1,j=NN-2;i<NN;i++,j--)
     {
      if (id > j && id < NN)
         atomic_sub_float(&X[j], LU[iRow[j]*NN+id]*X[id]);
      barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
      if (id == j) X[j] *= LU[iRow[j]*NN+j];
      barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
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
	reenterable @goal:-write(NAME).(bool init, float EPS, int MaxIters, float mu0,
			_global(@goal:-n.) float * x0,
			_global(@goal:-n.) int * iRow,
			_global(@goal:-n.*@goal:-n.) float * A,
			_global(@goal:-n.*@goal:-n.) float * LU,
			_global(@goal:-n.*@goal:-n.) float * J0,
			_global(@goal:-n.) float * B,
			_global(@goal:-n.) float * GRAD,
			_global(@goal:-n.) float * D,
			_global(2) int * buf,
			_global(1) float * FF) {
		if (init) {
			int work_size = @goal:-n.*@goal:-n.;
			int rest = work_size % 32;
			if (rest) work_size += 32 - rest;

			for (int i = 0; i < work_size; i++)
				plan_last(false, EPS, MaxIters, mu0, x0, iRow, A, LU, J0, B, GRAD, D, buf, FF);
			plan_group_typize(NULL);
		} else {
			int id = plan_vector_id();
			float mu = mu0;
			float dk = 1E30f;
			float pk = 0.0f;
			float pk1;
			float fk0, dfk0;
			double d = 1E30;
			long sel = (1<<(@goal:-n.))-1;
			if (id == 0) {
				for (int i = 0; i < @goal:-n.; i++)
					GRAD[i] = 0.0f;
				buf[0] = 0;
			}
			barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);

			float x[@goal:-n.], f[@goal:-n.];
			float Fk1[@goal:-n.], fk1;
			for (int i = 0; i < @goal:-n.; i++)
				x[i] = x0[i];
			barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
			@goal:-fn.;
			barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
			for (int i = 0; i < @goal:-n.; i++)
				Fk1[i] = f[i];
			barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
			fk1 = f[0]*f[0];
			for (int i = 1; i < @goal:-n.; i++)
				fk1 += f[i]*f[i];
			barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
			do {
				for (int i = 0; i < @goal:-n.; i++)
					x[i] = x0[i];
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
				if (id < @goal:-n.*@goal:-n.) {
					int i = id / @goal:-n.;
					int j = id % @goal:-n.;
					x[j] += delta;
					sel = 1<<i;
					@goal:-fn.;
					float FP = f[i];
					x[j] -= 2*delta;
					@goal:-fn.;
					float FM = f[i];
					J0[id] = LU[id] = (FP-FM)/(2.0f*delta);
					x[j] += delta;
					sel = (1<<(@goal:-n.))-1;
				}
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
				if (id < @goal:-n.*@goal:-n.) {
					int i = id / @goal:-n.;
					int j = id % @goal:-n.;
					float a = 0.0f;
					for (int k = 0; k < @goal:-n.; k++) {
						a += LU[k*@goal:-n.+i]*LU[k*@goal:-n.+j];
					}
					if (i == j) {
						float g = 0.0f;
						for (int k = 0; k < @goal:-n.; k++) {
							g += LU[k*@goal:-n.+i]*Fk1[k];
						}
						GRAD[i] = g;
						B[i] = -g;
						a += mu;
					}
					A[id] = a;
				}
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
				d = 0.0;
				for (int i = 0; i < @goal:-n.; i++) {
					float g = GRAD[i];
					d += g*g;
				}
				d = sqrt(d);
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
				if (d <= EPS*EPS || (*buf+1) >= MaxIters) {
					if (id == 0) {
						fk1 = 0.0f;
						for (int i = 0; i < @goal:-n.; i++)
							fk1 += Fk1[i]*Fk1[i];
						*FF = sqrt(fk1);
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					break;
				}
				if (_GetLU(@goal:-n., iRow, A, LU, &buf[1], D)) {
					_SolveLU(@goal:-n., iRow, LU, B, D);
					float dfk1 = -B[0]*D[0];
					float fk1 = Fk1[0]*Fk1[0];
					int first = dk == 1E30f;
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					for (int i = 1; i < @goal:-n.; i++) {
						dfk1 += -B[i]*D[i];
						fk1 += Fk1[i]*Fk1[i];
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					if (id < @goal:-n.) {
						float h = Fk1[id];
						for (int k = 0; k < @goal:-n.; k++)
							h += J0[id*@goal:-n.+k]*D[k];
						B[id] = h;
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					pk1 = B[0]*B[0];
					for (int i = 1; i < @goal:-n.; i++)
						pk1 += B[i]*B[i];
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					float omega = 1.0f;
					float step = 1.0f;
					dk = 0.0f;
					while (omega > LEPS && step > LEPS) {
						step = 0.0f;
						for (int i = 0; i < @goal:-n.; i++) {
							float ds = omega*D[i];
							x[i] = x0[i] + ds;
							ds = fabs(ds);
							if (ds > step) step = ds;
						}
						@goal:-fn.;
						barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
						float fi = 0.0f;
						for (int i = 0; i < @goal:-n.; i++) {
							fi += f[i]*f[i];
						}
						barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
						if (fi < fk1) {
							fk1 = fi;
							dk += omega;
							for (int i = 0; i < @goal:-n.; i++)
								Fk1[i] = f[i];
							barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
							if (id < @goal:-n.) x0[id] = x[id];
							barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
						} else
							omega *= 0.5f;
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					if (!first) {
						float alphak;
						float a = fk0;
						float b = dfk0;
						float m = fk1 - a - b*dk;
						float q = dfk1 - b;
						float c = (3.0f*m - dk*q)/dk/dk;
						float d = (dk*q - 2.0f*m)/dk/dk/dk;
						float DISCR = 4.0f*c*c - 12.0f*d*b;
						if (DISCR < 0.0f)
							if (fk0 < fk1) alphak = 0.0f;
							else alphak = dk;
						else if (DISCR == 0.0f) {
							float t0 = -c/(3.0f*d);
							if (2.0f*c+6.0f*d*t0 > 0.0f) alphak = t0;
							else
								if (fk0 < fk1) alphak = 0.0f;
								else alphak = dk;
						} else {
							float DD = sqrt(DISCR);
							float t1 = (-2.0f*c - DD)/(6.0f*d);
							float t2 = (-2.0f*c + DD)/(6.0f*d);
							if (2.0f*c + 6.0f*d*t1 > 0.0f) alphak = t1;
							else alphak = t2;
						}
						float zk = a + alphak*(b + alphak*(c + alphak*d));
						if (zk >= pk) mu += (zk - pk)/(alphak + EPS);
						else mu /= (3.0f + mu);
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					fk0 = fk1;
					dfk0 = dfk1;
					pk = pk1;
				} else {
					if (id == 0) {
						fk1 = 0.0f;
						for (int i = 0; i < @goal:-n.; i++)
							fk1 += Fk1[i]*Fk1[i];
						*FF = sqrt(fk1);
					}
					barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
					break;
				}
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
				#ifdef ON_GPU
				if (id == 0) atomic_add(buf, 1);
				#else
				if (id == 0) (*buf)++;
				#endif
				barrier(CLK_GLOBAL_MEM_FENCE+CLK_LOCAL_MEM_FENCE);
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

solve(solve_l_m, 100.0f*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(2.0f-x[0])*(2.0f-x[0]), (x[2]-3.0f)*(x[2]-3.0f), (4.0f-x[1])*(4.0f-x[1]));

const int max_iters = 500;

int main() {
	const int nPoints = 100;
	float ITERS = 0.0f;
	float Total = 0.0f;
	int nGOOD = 0;
	unsigned int seed_points = 184415;
	float rs[3] = { 3.0f, 6.0f, 5.0f };
	for (unsigned int k = 0; k < nPoints; k++) {
		float x0[3], x1[3];

		for (int i = 0; i < 3; i++)
			x0[i] = rs[i] - 2*rs[i]*genrandom(&seed_points);

		int iRow[3];
		float A[9];
		float LU[9], J0[9];
		float B[3];
		float GRAD[3];
		float D[3];
		int buf[2] = { 0 };
		float FF;

		solve_l_m(true, 0.5E-6f, max_iters, 10.0f, x0, iRow, A, LU, J0, B, GRAD, D, buf, &FF);
		cout << buf[0] << endl;
		for (int i = 0; i < 3; i++)
			cout << x0[i] << " ";
		cout << endl << "F = " << FF << endl;
		Total += FF;
		ITERS += buf[0];
		if (fabs(FF) < LEPS) nGOOD++;
	}
	cout << "Average F = " << (Total/nPoints) << endl;
	cout << "Average ITERS = " << (ITERS/nPoints) << endl;
	cout << "nGOODS = " << nGOOD << endl;
}
