// Uncomment the following line if you hava a Cilk-capable compiler
// #define CILK

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "atomic_cilk_gpu_omp_compile.h"

#pragma auto for
#pragma auto omp for
#pragma auto gpu for
#pragma auto parallelize

#pragma auto pure(malloc,fabs,free,sizeof,omp_get_wtime)

#define BASE_PARALLEL 1

#define theta 1.83

#define NX 40
#define NY 40

#define h 0.1

#define NP 15000

// Собирающая электростатическая линза
#define U1 200
#define U2 5000

#define e -1.5E-13
#define m 1E-11

#define e0 8.85E-12

#define V (h*h)

#define tau 0.000015

#define T 0.09

#define POISSON_EPS 0.01

#define TOL_EPS 0.25

#ifndef CILK
#define _Cilk_spawn /* _Cilk_spawn */
#define _Cilk_sync /* _Cilk_sync */
#define _Cilk_for for
#endif

#define cilk_spawn _Cilk_spawn
#define cilk_sync _Cilk_sync
#define cilk_for(A) _Cilk_for(int A)

int main() {
        double * U  = (double *)malloc(NY*NX*sizeof(double));
        double * UU = (double *)malloc(NY*NX*sizeof(double));
        double * EX = (double *)malloc(NY*NX*sizeof(double));
        double * EY = (double *)malloc(NY*NX*sizeof(double));
	double * PX = (double *)malloc(NP*sizeof(double));
	double * PY = (double *)malloc(NP*sizeof(double));
	int * X = (int *)malloc(NP*sizeof(int));
	int * Y = (int *)malloc(NP*sizeof(int));

	double ro[NY][NX];

	split_private double t;
	split_private double tm;
	split_private int i, j;

	for (i = 0; i < NY; i++)
		for (j = 0; j < NX; j++) {
			UU[i*NX+j] = j == NX-1 ? U2 : j == NX/2 && (i < NY/4 || i > 3*NY/4) ? U1 : 0.0;
			EX[i*NX+j] = 0.0;
			EY[i*NX+j] = 0.0;
		}
	for (i = 0; i < NP; i++) {
		int x, y;

		PX[i] = 0.5*NX*h*rand()/RAND_MAX;
		PY[i] = NY*h*rand()/RAND_MAX;

		x = PX[i]/h;
		y = PY[i]/h;
		if (x < 0) x = 0;
		else if (x > NX-1) x = NX-1;
		if (y < 0) y = 0;
		else if (y > NY-1) y = NY-1;

		X[i] = x;
		Y[i] = y;
	}

	tm = omp_get_wtime();

	for (t = 0.0; t < T; t += tau) {
		unsigned int n[NY][NX] = { 0 };
		double err;
		int ptr = 0;
		for (i = 0; i < NY; i++)
    			for (j = 0; j < NX; j++, ptr++)
				U[ptr] = UU[ptr];
		for (i = 1; i < NY - 1; i++)
			for (j = 1; j < NX - 1; j++) {
				EX[i*NX+j] = -(U[i*NX+j+1]-U[i*NX+j-1])/2.0/h;
				EY[i*NX+j] = -(U[(i+1)*NX+j]-U[(i-1)*NX+j])/2.0/h;
			}
						
		#pragma omp parallel for if(BASE_PARALLEL) private(i) num_threads(split_tune)
		for (i = 0; i < NP; i++) {
			PX[i] += tau*e*EX[Y[i]*NX+X[i]]/m;
			PY[i] += tau*e*EY[Y[i]*NX+X[i]]/m;
		}

		#pragma omp parallel for if(BASE_PARALLEL) private(i) num_threads(split_tune)
		for (i = 0; i < NP; i++) {
			int x = PX[i]/h;
			int y = PY[i]/h;
			if (x < 0) x = 0;
			else if (x > NX-1) x = NX-1;
			if (y < 0) y = 0;
			else if (y > NY-1) y = NY-1;

			Y[i] = y;
			X[i] = x;
			n[y][x]++;
		}

		for (i = 0; i < NY; i++)
			for (j = 0; j < NX; j++)
				ro[i][j] = n[i][j]*e/V;

		do {
			err = 0.0;
	
			#pragma omp parallel for if(BASE_PARALLEL) private(i,j) num_threads(split_tune)
			for (i = 1; i < NY - 1; i++)
				for (j = 1+(i-1)%2; j < NX - 1; j+=2) {
				  int ptr = i*NX + j;
				  if (!(j == NX/2 && (i < NY/4 || i > 3*NY/4))) {
					double _new = (1-theta)*UU[ptr] + theta/4.0*(UU[ptr-1]+UU[ptr+1]+UU[ptr+NX]+UU[ptr-NX]-h*h*ro[i][j]/e0);
					double loc_err = fabs(UU[ptr] - _new);
					if (loc_err > err) err = loc_err;
					UU[ptr] = _new;
				  }
				}
			#pragma omp parallel for if(BASE_PARALLEL) private(i,j) num_threads(split_tune)
			for (i = 1; i < NY - 1; i++)
				for (j = 1+i%2; j < NX - 1; j+=2) {
				  int ptr = i*NX + j;
				  if (!(j == NX/2 && (i < NY/4 || i > 3*NY/4))) {
					double _new = (1-theta)*UU[ptr] + theta/4.0*(UU[ptr-1]+UU[ptr+1]+UU[ptr+NX]+UU[ptr-NX]-h*h*ro[i][j]/e0);
					double loc_err = fabs(UU[ptr] - _new);
					if (loc_err > err) err = loc_err;
					UU[ptr] = _new;
				  }
				}
			for (j = 0; j < NX; j++) {
				UU[j] = UU[NX + j];
				UU[(NY-1)*NX + j] = UU[(NY-2)*NX + j];
			}
		} while (err > POISSON_EPS);
	}

	for (i = 0; i < NY; i++) {
		for (j = 0; j < NX; j++)
			printf("%lf\t", UU[i*NX+j]);
		printf("\n");
	}

	return 0;
}