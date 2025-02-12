// ВНИМАНИЕ: нестационарный ветер!

#pragma scan parallel

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#define __MAY_BE_MICROSOFTC__

#include "memoization.h"

#include "kinetic_flow.h"

Kinetic * KIN[1024];

const bool kin_balancing = true;
double kin_time = 0.0;

#ifndef max
#define max(a,b) ((a)>(b) ? (a) : (b))
#endif

const int NX = 20;
const int NY = 15;

const int NC = 20;

const double C0[NC] = {5.0, 1.0, 3.0, 18.0, 2.9, 0.1, 0.6, 1.5, 11.0, 20.0,
                       1.1, 2.1, 3.8, 6.5,  1.2, 2.7, 11.0, 17.3, 4.4, 5.2};

const double T0 = 300.0;
const double T1 = 500.0;

char MAP[NY][NX] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

enum {Divisor, Douglas, Euler};

typedef struct {
	int i, j;
	int id;
	int Iters;
} KinItem;

KinItem WORK[NY*NX];

int comparer(const void * E1, const void * E2) {
	KinItem * _E1 = (KinItem *)E1;
	KinItem * _E2 = (KinItem *)E2;

	return _E2->Iters - _E1->Iters;
}

int seanses = 0;
long long disbal = 0;

const double k1 = 50.0;
const double k2 = 5.0;
const double k4 = 0.001;

const int M = 5;

double L2[NY][NX] = {0.0};

const double h = 1.0;
const double h2 = h*h;

const double init_tau = 0.001;

double tau = init_tau;

const double nu = 0.000013;

const double U0 = 5.0;
/* const */ double U = 5.0;

const double POISSON_EPS = 0.00001;
const double TOL = 1E-3;
const int period = 200;

double Kt[NY][NX] = {0.0};
double Et[NY][NX] = {0.0};

void Poisson(bool Swirl, unsigned char * MAP, double * I, double * omega) {
	const double theta = 1.83;

	double err;
	do {
		err = 0.0;
		
		int ptr = 0;
		for (int i = 0; i < NY; i++, ptr+=NX) {
			I[ptr] = Swirl ? I[ptr+1] : 0.0;
			I[ptr+NX-1] = Swirl ? I[ptr+NX-2] : 0.0;
		}

		ptr = 0;
		for (int j = 0; j < NX; j++, ptr++) {
			I[ptr] = Swirl ? I[ptr+NX] - h : 0.0;
			I[ptr+(NY-1)*NX] = Swirl ? I[ptr+(NY-2)*NX] : 0.0;
		}

		ptr = 0;
		for (int i = 0; i < NY; i++)
			for (int j = 0; j < NX; j++, ptr++)
			  if (MAP[ptr] == 0) {
				 double _new = (1-theta)*I[ptr] + theta/4.0*(I[ptr-1]+I[ptr+1]+I[ptr+NX]+I[ptr-NX]+h2*omega[ptr]);
				 double loc_err = fabs(I[ptr] - _new);
				 if (loc_err > err) err = loc_err;
				 I[ptr] = _new;
			  }
  } while (err > POISSON_EPS);
}

void DynaX(int KE, int integ, bool up2, unsigned char * MAP, double * W0, double * UX, double * UY, double * W1, double * K, double Knu, double * NU) {
	double L[NX+1];
	double M[NX+1];

	double R = integ == Douglas ? 0.5 : 1.0;

	memmove(W1, W0, NY*NX*sizeof(double));

	int ptr = 0;
	for (int i = 0; i < NY; i++) {
		int cur = 0;
		int j1, j2;
		ptr = i*NX;
		do {
			for (j1 = cur; j1 < NX && MAP[ptr+j1] != 0; j1++);
			if (j1 < NX && MAP[ptr+j1]==0) {
				if (KE == 0) {
					L[j1] = 0.0;
					M[j1] = W0[ptr+j1-1];
				} else if (KE == 1) { // Kt
					L[j1] = 1.0;
					M[j1] = 0.0;
				} else { // Et
					L[j1] = 0.0;
					M[j1] = pow(0.0845,0.75)*pow(Kt[i][j1-1],1.5)/0.41/h;
				}
				for (j2 = j1; j2 < NX && MAP[ptr+j2]==0; j2++) {
					int _ptr = ptr+j2;
					double A = -0.5*(fabs(UX[_ptr]) - UX[_ptr]);
					double B = 0.5*(fabs(UX[_ptr]) + UX[_ptr]);
					double A1 = -0.5*(fabs(UY[_ptr]) - UY[_ptr]);
					double B1 = 0.5*(fabs(UY[_ptr]) + UY[_ptr]);
					double Z1 = +R*tau*A/h - R*tau*(nu + Knu*0.5*(NU[_ptr+1]+NU[_ptr]))/h2;
					double Z2 = -R*tau*B/h - R*tau*(nu + Knu*0.5*(NU[_ptr-1]+NU[_ptr]))/h2;
					double Z3 = 1.0 - Z1 - Z2;
					double s = Z3 + Z2*L[j2];
					L[j2+1] = -Z1/s;
					double P = integ == Douglas ? - 0.5*tau*A1*(W0[_ptr+NX]-W0[_ptr]) - 0.5*tau*B1*(W0[_ptr]-W0[_ptr-NX]) + 0.5*tau*(-(nu+0.5*Knu*(NU[_ptr-NX]+NU[_ptr]))*(W0[_ptr]-W0[_ptr-NX])+(nu+0.5*Knu*(NU[_ptr]+NU[_ptr+NX]))*(W0[_ptr+NX]-W0[_ptr]))/h2 : 0.0;
                    double _K = K == NULL ? 0.0 : (integ == Douglas ? 0.0 : 0.5*tau*K[_ptr]);
					M[j2+1] = (W0[_ptr] + _K - Z2*M[j2] + P)/s;
				}
				if (KE == 0) { 
					W1[ptr+j2] = W0[ptr+j2];
				} else if (KE == 1) { // Kt
					W1[ptr+j2] = M[j2]/(1.0 - L[j2]);
				} else { // Et
					W1[ptr+j2] = pow(0.0845,0.75)*pow(Kt[i][j2],1.5)/0.41/h;
				}
				for (int j = j2-1; j >= j1-1; j--)
					W1[ptr+j] = L[j+1]*W1[ptr+j+1] + M[j+1];
				cur = j2;
			} else
				cur = NX;
		} while (cur < NX);
	}
}

void DynaY(int KE, int integ, bool up2, unsigned char * MAP, double * W0, double * UX, double * UY, double * W1, double * K, double Knu, double * NU) {
	double L[NY+1];
	double M[NY+1];
	int ptr;

	double R = integ == Douglas ? 0.5 : 1.0;

	memmove(W1, W0, NY*NX*sizeof(double));

	for (int j = 0; j < NX; j++) {
		ptr = j;
		int cur = 0;
		int i1, i2;
		do {
			for (i1 = cur; i1 < NY && MAP[ptr+i1*NX] != 0; i1++);
			if (i1 < NY && MAP[ptr+i1*NX]==0) {
				if (KE == 0) {
					if (cur == 0 && up2) {
						L[i1] = 1.0;
						M[i1] = 0.0;
					} else {
						L[i1] = 0.0;
						M[i1] = W0[ptr+i1*NX-NX];
					}
				} else if (KE == 1) { // Kt
					L[i1] = 1.0;
					M[i1] = 0.0;
				} else { // Et
					L[i1] = 0.0;
					M[i1] = pow(0.0845,0.75)*pow(Kt[i1-1][j],1.5)/0.41/h;
				}
				for (i2 = i1; i2 < NY && MAP[ptr+i2*NX]==0; i2++) {
					int _ptr = ptr + i2*NX;
					double A = -0.5*(fabs(UY[_ptr]) - UY[_ptr]);
					double B = 0.5*(fabs(UY[_ptr]) + UY[_ptr]);
					double A1 = -0.5*(fabs(UX[_ptr]) - UX[_ptr]);
					double B1 = 0.5*(fabs(UX[_ptr]) + UX[_ptr]);
					double Z1 = +R*tau*A/h - R*tau*(nu + Knu*0.5*(NU[_ptr+NX]+NU[_ptr]))/h2;
					double Z2 = -R*tau*B/h - R*tau*(nu + Knu*0.5*(NU[_ptr-NX]+NU[_ptr]))/h2;
					double Z3 = 1.0 - Z1 - Z2;
					double s = Z3 + Z2*L[i2];
					L[i2+1] = -Z1/s;
					double P = integ == Douglas ? - 0.5*tau*A1*(W0[_ptr+1]-W0[_ptr]) - 0.5*tau*B1*(W0[_ptr]-W0[_ptr-1]) + 0.5*tau*(-(nu+0.5*Knu*(NU[_ptr-1]+NU[_ptr]))*(W0[_ptr]-W0[_ptr-1])+(nu+0.5*Knu*(NU[_ptr]+NU[_ptr+1]))*(W0[_ptr+1]-W0[_ptr]))/h2 : 0.0;
                    double _K = K == NULL ? 0.0 : (integ == Douglas ? tau*K[_ptr] : 0.5*tau*K[_ptr]);
					M[i2+1] = (W0[_ptr] + _K - Z2*M[i2] + P)/s;
				}
				if (KE == 0) {
					W1[ptr+i2*NX] = W0[ptr+i2*NX];
				} else if (KE == 1) { // Kt
					W1[ptr+i2*NX] = M[i2]/(1.0 - L[i2]);
				} else { // Et
					W1[ptr+i2*NX] = pow(0.0845,0.75)*pow(Kt[i2][j],1.5)/0.41/h;
				}
				for (int i = i2-1; i >= i1-1; i--)
					W1[ptr+i*NX] = L[i+1]*W1[ptr+i*NX+NX] + M[i+1];
				cur = i2;
			} else
				cur = NY;
		} while (cur < NY);
	}
}

void Eulerize(unsigned char * MAP, double * st, double * UX, double * UY, double * W1, double * K, double Knu, double * NU, double * alpha) {
	int ptr = 0;

	double _st[NY*NX];
	memmove(_st, st, NY*NX*sizeof(double));

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++, ptr++)
		  if (MAP[ptr] == 0 && fabs(alpha[ptr] - 1.0) > 1E-5) {
			 double A = -0.5*(fabs(UY[ptr]) - UY[ptr]);
			 double B = 0.5*(fabs(UY[ptr]) + UY[ptr]);
			 double A1 = -0.5*(fabs(UX[ptr]) - UX[ptr]);
			 double B1 = 0.5*(fabs(UX[ptr]) + UX[ptr]);
             double _K = K == NULL ? 0.0 : tau*K[ptr];
			 _st[ptr] = st[ptr] - tau*A1*(st[ptr+1]-st[ptr]) - tau*B1*(st[ptr]-st[ptr-1])
				                - tau*A*(st[ptr+NX]-st[ptr]) - tau*B*(st[ptr]-st[ptr-NX])
				                + tau*(-(nu+0.5*Knu*(NU[ptr-1]+NU[ptr]))*(st[ptr]-st[ptr-1])+(nu+0.5*Knu*(NU[ptr]+NU[ptr+1]))*(st[ptr+1]-st[ptr])
								       -(nu+0.5*Knu*(NU[ptr-NX]+NU[ptr]))*(st[ptr]-st[ptr-NX])+(nu+0.5*Knu*(NU[ptr]+NU[ptr+NX]))*(st[ptr+NX]-st[ptr])
								      )/h2
							    + _K;
		  }
	ptr = 0;
	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++, ptr++)
		  if (MAP[ptr] == 0 && fabs(alpha[ptr] - 1.0) > 1E-5) {
			 W1[ptr] = alpha[ptr]*W1[ptr] + (1.0-alpha[ptr])*_st[ptr];
		  }
}

double omega[NY][NX] = {0.0};
double psi[NY][NX] = {0.0};
double tk[NY][NX] = { 0.0 };
double NU[NY][NX] = {0.0};
double UX[NY][NX] = {0.0};
double UY[NY][NX] = {0.0};
double * C[NC];

double st_omega[NY][NX] = {0.0};
double st_psi[NY][NX] = {0.0};
double st_tk[NY][NX] = { 0.0 };
double st_NU[NY][NX] = { 0.0 };
double st_UX[NY][NX] = {0.0};
double st_UY[NY][NX] = {0.0};
double st_Kt[NY][NX] = {0.0};
double st_Et[NY][NX] = {0.0};
double * st_C[NC];

const int NP = NY*NX/4;

double ERRS[NY][NX] = {0.0};
double GRAV[NY][NX] = {0.0};
double PARTX[NP];
double PARTY[NP];
double PARTVX[NP] = {0.0};
double PARTVY[NP] = {0.0};
double PARTV[NP] = {0.0};

double ALPHA[NY][NX] = {0.0};

double iters[NY][NX];

#pragma memoization(t,o) lin_extrapolator(150, 2) controlled(50, 1)
void prognose(int i, double stat[NY][NX]) {
	memmove(stat, iters, sizeof(iters));
}

double Step(int integ, long & mode) {
	double omega1[NY][NX] = {0.0};
	double nu1[NY][NX] = {0.0};
	double tk1[NY][NX] = { 0.0 };
	double c1[NY][NX] = { 0.0 };
	double _nu[NY][NX];
	double K[NY][NX] = {0.0};
	double K1[NY][NX] = {0.0};
	double KT[NY][NX] = { 0.0 };
	double err = 0.0;

	memmove(_nu, NU, NX*NY*sizeof(double));

	if (integ == Euler) {
		memmove(st_omega, omega, NY*NX*sizeof(double));
		memmove(st_psi, psi, NY*NX*sizeof(double));
		memmove(st_tk, tk, NY*NX*sizeof(double));
		memmove(st_NU, NU, NY*NX*sizeof(double));
		memmove(st_UX, UX, NY*NX*sizeof(double));
		memmove(st_UY, UY, NY*NX*sizeof(double));
		memmove(st_Kt, Kt, NY*NX*sizeof(double));
		memmove(st_Et, Et, NY*NX*sizeof(double));
		for (int c = 0; c < NC; c++)
			memmove(st_C[c], C[c], NY*NX*sizeof(double));
	}

	Poisson(true, (unsigned char *) MAP, (double *) psi, (double *) omega);

	for (int j = 0; j < NX; j++)
		UX[0][j] = U;

	for (int j = 0; j < NX; j++) {
		omega[NY-1][j] = -2.0*(psi[NY-2][j] - psi[NY-1][j])/h2;
		omega[0][j] = -2.0*(psi[1][j] - psi[0][j])/h2 - 2.0*U/h;
	}

	for (int i = 0; i < NY; i++) {
		omega[i][NX-1] = -2.0*(psi[i][NX-2] - psi[i][NX-1])/h2;
		omega[i][0] = -2.0*(psi[i][1] - psi[i][0])/h2 - 2.0*U/h;
	}

    for (int i = 7; i < NY-1; i++) {
		omega[i][6] = -2.0*(psi[i][5] - psi[i][6])/h2;
		omega[i][10] = -2.0*(psi[i][11] - psi[i][10])/h2;
	}
	for (int j = 6; j <= 10; j++) {
		tk[7][j] = T1;
		for (int k = 0; k < NC; k++)
			C[k][7 * NX + j] = C0[k] * 0.41E-4;
		omega[7][j] = -2.0*(psi[6][j] - psi[7][j])/h2;
	}
	for (int i = 1; i < NY-1; i++)
		for (int j = 1; j < NX-1; j++) {
			double dUxdx = (UX[i][j+1]-UX[i][j-1])/2.0/h;
			double dUydx = (UY[i][j+1]-UY[i][j-1])/2.0/h;
			double dUxdy = (UX[i+1][j]-UX[i-1][j])/2.0/h;
			double dUydy = (UY[i+1][j]-UY[i-1][j])/2.0/h;

			double dTdx = (tk[i][j + 1] - tk[i][j - 1]) / 2.0 / h;

            double SSS2 =  2*(dUxdx*dUxdx+dUydy*dUydy) + (dUxdy+dUydx)*(dUxdy+dUydx);
            double DDD =  _nu[i][j]*SSS2;
            double RNG  = sqrt(SSS2)*Kt[i][j]/Et[i][j];
            double RNG3 = RNG*RNG*RNG;

			K[i][j] = DDD-Et[i][j]; // Kt
			K1[i][j] = (1.42*DDD-(1.68+0.0845*RNG3*(1-RNG/4.38)/(1+0.012*RNG3))*Et[i][j])*Et[i][j]/Kt[i][j]; // Et
			KT[i][j] = 0.00367*9.81*dTdx;
			NU[i][j] = 0.0845 * Kt[i][j] * Kt[i][j]/Et[i][j];
		}

	if (mode++%2) {
		DynaX(0, integ, false, (unsigned char *) MAP, (double *) omega, (double *) UX, (double *) UY, (double *) omega1, NULL, 1.0, (double *) _nu);
		DynaY(0, integ, false, (unsigned char *) MAP, (double *) omega1, (double *) UX, (double *) UY, (double *) omega, NULL, 1.0, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_omega, (double *) UX, (double *) UY, (double *) omega, NULL, 1.0, (double *) _nu, (double *) ALPHA);
		DynaX(0, integ, true, (unsigned char *)MAP, (double *)tk, (double *)UX, (double *)UY, (double *)tk1, (double *)KT, 1.0, (double *)_nu);
		DynaY(0, integ, true, (unsigned char *)MAP, (double *)tk1, (double *)UX, (double *)UY, (double *)tk, (double *)KT, 1.0, (double *)_nu);
		if (integ == Euler) Eulerize((unsigned char *)MAP, (double *)st_tk, (double *)UX, (double *)UY, (double *)tk, (double *)KT, 1.0, (double *)_nu, (double *)ALPHA);
		DynaX(1, integ, true, (unsigned char *)MAP, (double *)Kt, (double *)UX, (double *)UY, (double *)nu1, (double *)K, 1.0 / 0.7194, (double *)_nu);
		DynaY(1, integ, true, (unsigned char *) MAP, (double *) nu1, (double *) UX, (double *) UY, (double *) Kt, (double *) K, 1.0/0.7194, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_Kt, (double *) UX, (double *) UY, (double *) Kt, (double *) K, 1.0/0.7194, (double *) _nu, (double *) ALPHA);
		DynaX(2, integ, true, (unsigned char *) MAP, (double *) Et, (double *) UX, (double *) UY, (double *) nu1, (double *) K1, 1.0/0.7194, (double *) _nu);
		DynaY(2, integ, true, (unsigned char *) MAP, (double *) nu1, (double *) UX, (double *) UY, (double *) Et, (double *) K1, 1.0/0.7194, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_Et, (double *) UX, (double *) UY, (double *) Et, (double *) K1, 1.0/0.7194, (double *) _nu, (double *) ALPHA);
		for (int c = 0; c < NC; c++) {
			DynaX(0, integ, false, (unsigned char *) MAP, (double *) C[c], (double *) UX, (double *) UY, (double *) c1, NULL, 1.0, (double *) _nu);
			DynaY(0, integ, false, (unsigned char *) MAP, (double *) c1, (double *) UX, (double *) UY, (double *) C[c], NULL, 1.0, (double *) _nu);
			if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_C[c], (double *) UX, (double *) UY, (double *) C[c], NULL, 1.0, (double *) _nu, (double *) ALPHA);
		}
	} else {
		DynaY(0, integ, false, (unsigned char *) MAP, (double *) omega, (double *) UX, (double *) UY, (double *) omega1, NULL, 1.0, (double *) _nu);
		DynaX(0, integ, false, (unsigned char *) MAP, (double *) omega1, (double *) UX, (double *) UY, (double *) omega, NULL, 1.0, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_omega, (double *) UX, (double *) UY, (double *) omega, NULL, 1.0, (double *) _nu, (double *) ALPHA);
		DynaY(0, integ, true, (unsigned char *)MAP, (double *)tk, (double *)UX, (double *)UY, (double *)tk1, (double *)KT, 1.0, (double *)_nu);
		DynaX(0, integ, true, (unsigned char *)MAP, (double *)tk1, (double *)UX, (double *)UY, (double *)tk, (double *)KT, 1.0, (double *)_nu);
		if (integ == Euler) Eulerize((unsigned char *)MAP, (double *)st_tk, (double *)UX, (double *)UY, (double *)tk, (double *)KT, 1.0, (double *)_nu, (double *)ALPHA);
		DynaY(1, integ, true, (unsigned char *)MAP, (double *)Kt, (double *)UX, (double *)UY, (double *)nu1, (double *)K, 1.0 / 0.7194, (double *)_nu);
		DynaX(1, integ, true, (unsigned char *) MAP, (double *) nu1, (double *) UX, (double *) UY, (double *) Kt, (double *) K, 1.0/0.7194, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_Kt, (double *) UX, (double *) UY, (double *) Kt, (double *) K, 1.0/0.7194, (double *) _nu, (double *) ALPHA);
		DynaY(2, integ, true, (unsigned char *) MAP, (double *) Et, (double *) UX, (double *) UY, (double *) nu1, (double *) K1, 1.0/0.7194, (double *) _nu);
		DynaX(2, integ, true, (unsigned char *) MAP, (double *) nu1, (double *) UX, (double *) UY, (double *) Et, (double *) K1, 1.0/0.7194, (double *) _nu);
		if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_Et, (double *) UX, (double *) UY, (double *) Et, (double *) K1, 1.0/0.7194, (double *) _nu, (double *) ALPHA);
		for (int c = 0; c < NC; c++) {
			DynaY(0, integ, false, (unsigned char *) MAP, (double *) C[c], (double *) UX, (double *) UY, (double *) c1, NULL, 1.0, (double *) _nu);
			DynaX(0, integ, false, (unsigned char *) MAP, (double *) c1, (double *) UX, (double *) UY, (double *) C[c], NULL, 1.0, (double *) _nu);
			if (integ == Euler) Eulerize((unsigned char *) MAP, (double *) st_C[c], (double *) UX, (double *) UY, (double *) C[c], NULL, 1.0, (double *) _nu, (double *) ALPHA);
		}
	}

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++)
			if (MAP[i][j] == 0) {
				double ux = (psi[i+1][j] - psi[i-1][j])/h/2.0;
				UX[i][j] = ux;
				double uy = -(psi[i][j+1] - psi[i][j-1])/h/2.0; 
				UY[i][j] = uy;
		    }

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++)
			if (MAP[i][j] == 0) {
				double _err = fabs(NU[i][j] - _nu[i][j]);
				if (_err > err)
					err = _err;
		    }

	int np = omp_get_num_procs();
	double tt = omp_get_wtime();
	if (kin_balancing) {
		static int counter = 0;

		static bool initialized = false;
		double _iters[NY][NX] = { 0.0 };

		if (!initialized) {
			for (int i = 0; i < NY; i++)
				for (int j = 0; j < NX; j++)
					iters[i][j] = 1.0;
			initialized = true;
		}

		if (counter >= 50)
			predict_prognose(counter, _iters);
		else
			memmove(_iters, iters, sizeof(iters));

		long long L = 0;
		for (int i = 0, ptr = 0; i < NY; i++)
			for (int j = 0; j < NX; j++, ptr++) {
				WORK[ptr].i = i;
				WORK[ptr].j = j;
				if (_iters[i][j] == _iters[i][j])
					WORK[ptr].Iters = (int)_iters[i][j];
				else
					WORK[ptr].Iters = 1000;
				WORK[ptr].id = -1;
				L += WORK[ptr].Iters;
			}
		qsort((void *)WORK, NY*NX, sizeof(KinItem), comparer);
		int ptr = 0;
		for (int id = 0; id < np; id++) {
			long long M = 1 + L / np;
			while (M > 0 && ptr < NY*NX) {
				if (WORK[ptr].id < 0) {
					WORK[ptr].id = id;
					M -= WORK[ptr].Iters;
				}
				ptr++;
			}
		}

		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			long long disb = 0;
			for (int m = 0; m < NY*NX; m++)
				if (WORK[m].id == id) {
					int i = WORK[m].i;
					int j = WORK[m].j;

					if (MAP[i][j] == 0) {
						KIN[id]->EndTime = tau; /* vremya interirovaniya */
						KIN[id]->Tk = tk[i][j];      /* Temperatura provediya reaksii v K*/
						for (int k = 0; k < KIN[id]->NSubst; k++)
							KIN[id]->Conc0[k] = C[k][i*NX + j];
						KIN[id]->LossPrecision = 0;
						KIN[id]->OneTaktKinetic(1, 0);
						if (KIN[id]->LossPrecision) {
							printf(" Oshibka vichislenii : %s.",
								(KIN[id]->KinErrorInfo.LossH == 0 ? " slishkom mnogo iterasii" :
								" poterya tochnosti - shag po vremeni stremitcya k nulu "));
							printf(" Vichisleniya prervani v moment t=%lf. Vipolneno %i iterasii\n",
								KIN[id]->KinErrorInfo.ReachTau, KIN[id]->Iters);
						}
						else
							for (int k = 0; k < KIN[id]->NSubst; k++)
								C[k][i*NX + j] = KIN[id]->Conc1[k];
						disb += abs(WORK[m].Iters - KIN[id]->Iters);
						iters[i][j] = 1.0*(WORK[m].Iters = KIN[id]->Iters);
					}
				}
			#pragma omp atomic
			disbal += disb;
		}
		prognose(counter++, iters);
		seanses++;
	}
	else {
		#pragma omp parallel for schedule(static, max(1,NY/np)) num_threads(np)
		for (int i = 0; i < NY; i++)
			for (int j = 0; j < NX; j++)
				if (MAP[i][j] == 0) {
					int id = omp_get_thread_num();

					KIN[id]->EndTime = tau; /* vremya interirovaniya */
					KIN[id]->Tk = tk[i][j];      /* Temperatura provediya reaksii v K*/
					for (int k = 0; k < KIN[id]->NSubst; k++)
						KIN[id]->Conc0[k] = C[k][i*NX + j];
					KIN[id]->LossPrecision = 0;
					KIN[id]->OneTaktKinetic(1, 0);
					if (KIN[id]->LossPrecision) {
						printf(" Oshibka vichislenii : %s.",
							(KIN[id]->KinErrorInfo.LossH == 0 ? " slishkom mnogo iterasii" :
							" poterya tochnosti - shag po vremeni stremitcya k nulu "));
						printf(" Vichisleniya prervani v moment t=%lf. Vipolneno %i iterasii\n",
							KIN[id]->KinErrorInfo.ReachTau, KIN[id]->Iters);
					}
					else
						for (int k = 0; k < KIN[id]->NSubst; k++)
							C[k][i*NX + j] = KIN[id]->Conc1[k];
				}
	}
	kin_time += omp_get_wtime() - tt;

	return err;
}

const double T = 1.8;

int main() {
	char Buf[512];

	double _omega[NY][NX] = {0.0};
	double _psi[NY][NX] = {0.0};
	double _tk[NY][NX] = { 0.0 };
	double _NU[NY][NX] = { 0.0 };
	double _UX[NY][NX] = {0.0};
	double _UY[NY][NX] = {0.0};
	double _Kt[NY][NX] = {0.0};
	double _Et[NY][NX] = {0.0};
	double * _C[NC];
	double __omega[NY][NX] = {0.0};
	double __tk[NY][NX] = { 0.0 };
	double __psi[NY][NX] = { 0.0 };
	double __NU[NY][NX] = {0.0};
	double __UX[NY][NX] = {0.0};
	double __UY[NY][NX] = {0.0};
	double __Kt[NY][NX] = {0.0};
	double __Et[NY][NX] = {0.0};
	double * __C[NC];

	int np = omp_get_num_procs();

	for (int i = 0; i < np; i++) {
		KIN[i] = new Kinetic;

		KIN[i]->NSubst = 15; /*chislo vezhestv */
		KIN[i]->NReact = 17; /*chislo reaksii*/
		KIN[i]->MaxIterations = 50000;
		/* Zadaem simvolnie oboznachenie veshestv */
		strcpy(KIN[i]->Names[0], "CH4");   strcpy(KIN[i]->Names[1], "O2");
		strcpy(KIN[i]->Names[2], "CH3");   strcpy(KIN[i]->Names[3], "HO2");
		strcpy(KIN[i]->Names[4], "CH3OO"); strcpy(KIN[i]->Names[5], "CH2O");
		strcpy(KIN[i]->Names[6], "OH");    strcpy(KIN[i]->Names[7], "H2O");
		strcpy(KIN[i]->Names[8], "HCO");   strcpy(KIN[i]->Names[9], "CO");
		strcpy(KIN[i]->Names[10], "H2O2"); strcpy(KIN[i]->Names[11], "CO2");
		strcpy(KIN[i]->Names[12], "H");    strcpy(KIN[i]->Names[13], "H2");
		strcpy(KIN[i]->Names[14], "C2H6");
		KIN[i]->AllocateKineticByReactions();
		/* opredelyaem parametri reakzii */
		KIN[i]->EA[0] = 55.0;      KIN[i]->A[0] = 11.0;    KIN[i]->Tn[0] = 1.0;
		KIN[i]->EA[1] = 0.0;      KIN[i]->A[1] = 8.0;    KIN[i]->Tn[1] = 1.0;
		KIN[i]->EA[2] = 20.0;       KIN[i]->A[2] = 13.0 - 3.0;    KIN[i]->Tn[2] = 0.0;
		KIN[i]->EA[3] = 8.5;      KIN[i]->A[3] = 11.0;    KIN[i]->Tn[3] = 0.0;
		KIN[i]->EA[4] = 6.3;      KIN[i]->A[4] = 12.0;    KIN[i]->Tn[4] = 0.0;
		KIN[i]->EA[5] = 32.0;      KIN[i]->A[5] = 11.0;    KIN[i]->Tn[5] = 1.0;
		KIN[i]->EA[6] = 0.0;      KIN[i]->A[6] = 8.0;     KIN[i]->Tn[6] = 0.0;
		KIN[i]->EA[7] = 19.75;       KIN[i]->A[7] = 11.0;     KIN[i]->Tn[7] = 0.0;
		KIN[i]->EA[8] = 8.5;      KIN[i]->A[8] = 11.0;    KIN[i]->Tn[8] = 1.0;
		KIN[i]->EA[9] = 7.0;      KIN[i]->A[9] = 11.0;    KIN[i]->Tn[9] = 0.0;
		KIN[i]->EA[10] = 11.2;      KIN[i]->A[10] = 10.1;    KIN[i]->Tn[10] = 1.0;
		KIN[i]->EA[11] = 2.0;     KIN[i]->A[11] = 8.5;    KIN[i]->Tn[11] = 1.0;
		KIN[i]->EA[12] = 0.0;     KIN[i]->A[12] = 10.0;    KIN[i]->Tn[12] = 0.0;
		KIN[i]->EA[13] = 0.0;     KIN[i]->A[13] = 10.0;        KIN[i]->Tn[13] = 0.0;
		KIN[i]->EA[14] = 0.0;     KIN[i]->A[14] = 10.0;     KIN[i]->Tn[14] = 1.0;
		KIN[i]->EA[15] = 0.0;      KIN[i]->A[15] = 10.0;     KIN[i]->Tn[15] = 0.0;
		KIN[i]->EA[16] = 0.0;      KIN[i]->A[16] = 10.0;     KIN[i]->Tn[16] = 1.0;
		for (int j = 0; j < 17; j++)
			KIN[i]->A[j] += 3.0;
		/* transliruem reaksii */
		KIN[i]->Translate(0, "CH4+O2->CH3+HO2");    KIN[i]->Translate(1, "CH3+O2->CH3OO");
		KIN[i]->Translate(2, "CH3OO->CH2O+OH");     KIN[i]->Translate(3, "CH4+OH->CH3+H2O");
		KIN[i]->Translate(4, "CH2O+OH->H2O+HCO");   KIN[i]->Translate(5, "CH2O+O2->HCO+HO2");
		KIN[i]->Translate(6, "HCO+O2->CO+HO2");     KIN[i]->Translate(7, "CH4+HO2->H2O2+CH3");
		KIN[i]->Translate(8, "CH2O+HO2->H2O2+HCO"); KIN[i]->Translate(9, "CO+OH->CO2+H");
		KIN[i]->Translate(10, "CH4+H->CH3+H2");     KIN[i]->Translate(11, "CH2O+H->HCO+H2");
		KIN[i]->Translate(12, "2CH3->C2H6");        KIN[i]->Translate(13, "2HO2->H2O2+O2");
		KIN[i]->Translate(14, "OH+HO2->H2O+O2");    KIN[i]->Translate(15, "H+HO2->H2+O2");
		KIN[i]->Translate(16, "CH3+HO2->CH4+O2");
		KIN[i]->ReTranslate();
		KIN[i]->AllocateKineticBySubsts();
	}

	for (int i = 1; i < NY - 1; i++)
		for (int j = 1; j < NX-1; j++)
			if (MAP[i][j] == 0) {
				L2[i][j] = max(NX,NY)*h;
				for (int _i = 1; _i < NY-1; _i++)
					for (int _j = 1; _j < NX-1; _j++)
						if (MAP[_i][_j] == 1) {
							double L = hypot(abs(i-_i)*h, abs(j-_j)*h);
							double LL = L*L;
							if (LL < L2[i][j]) L2[i][j] = LL;
						}
			}

	for (int c = 0; c < NC; c++) {
		C[c] = (double *) new double[NY][NX];
		_C[c] = (double *) new double[NY][NX];
		__C[c] = (double *) new double[NY][NX];
		st_C[c] = (double *) new double[NY][NX];
	}

	double t0 = omp_get_wtime();
	double time = 0.0;
	double err = 1.0;
	long mode = 0;
	for (int i = 1; i < NY-1; i++)
		for (int j = 1; j < NX-1; j++)
			if (MAP[i][j] == 0)
				NU[i][j] = 0.01;
	int iters = 0;
	tau = init_tau;

	memset(omega, 0, NY*NX*sizeof(double));
	memset(psi, 0, NY*NX*sizeof(double));
	memset(UX, 0, NY*NX*sizeof(double));
	memset(UY, 0, NY*NX*sizeof(double));
	memset(NU, 0, NY*NX*sizeof(double));
	for (int i = 1; i < NY-1; i++)
		for (int j = 1; j < NX-1; j++) {
			Kt[i][j] = 0.01;
			Et[i][j] = 0.01;
			NU[i][j] = MAP[i][j] != 0 && i != 0 ? 0.0 : 0.0845*Kt[i][j]*Kt[i][j]/Et[i][j];
		}

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++)
			tk[i][j] = T0;

	for (int c = 0; c < NC; c++) {
		memset(C[c], 0, NX*NY*sizeof(double));
		for (int j = 0; j < NX; j++)
			C[c][j] = C0[c]*0.41E-4;
	}

	for (int i = 0, ptr = 0; i < NY; i++)
		for (int j = 0; j < NX; j++, ptr++) {
			WORK[ptr].i = i;
			WORK[ptr].j = j;
			WORK[ptr].id = ptr % np;
			WORK[ptr].Iters = 1;
		}

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++) {
			ALPHA[i][j] = 0.5;
		}
	for (int p = 0; p < NP; p++) {
		PARTX[p] = h*(NX-1)*rand()/RAND_MAX;
		PARTY[p] = h*(NY-1)*rand()/RAND_MAX;
	}
	t0 = omp_get_wtime();
	mode = 0;
	err = 1.0;
	iters = 0;
	tau = init_tau;
	for (time = 0.0; time < T; time += tau, iters++) {
		U = cos(time * 4);

		if (iters % period == 0) {
			memmove(_omega, omega, NX*NY*sizeof(double));
			memmove(_psi, psi, NX*NY*sizeof(double));
			memmove(_tk, tk, NX*NY*sizeof(double));
			memmove(_UX, UX, NX*NY*sizeof(double));
			memmove(_UY, UY, NX*NY*sizeof(double));
			memmove(_NU, NU, NX*NY*sizeof(double));
			memmove(_Kt, Kt, NX*NY*sizeof(double));
			memmove(_Et, Et, NX*NY*sizeof(double));
			for (int c = 0; c < NC; c++)
				memmove(_C[c], C[c], NX*NY*sizeof(double));

		}
		err = Step(Euler, mode);
		if (iters % period == 0) {
			printf("t = %lf : avr disb = %lf\n", time, 1.0*disbal/seanses);
			disbal = 0;
			seanses = 0;

			memmove(__omega, omega, NX*NY*sizeof(double));
			memmove(__tk, tk, NX*NY*sizeof(double));
			memmove(__psi, psi, NX*NY*sizeof(double));
			memmove(__UX, UX, NX*NY*sizeof(double));
			memmove(__UY, UY, NX*NY*sizeof(double));
			memmove(__NU, NU, NX*NY*sizeof(double));
			memmove(__Kt, Kt, NX*NY*sizeof(double));
			memmove(__Et, Et, NX*NY*sizeof(double));
			for (int c = 0; c < NC; c++)
				memmove(__C[c], C[c], NX*NY*sizeof(double));
			memmove(omega, _omega, NX*NY*sizeof(double));
			memmove(tk, _tk, NX*NY*sizeof(double));
			memmove(psi, _psi, NX*NY*sizeof(double));
			memmove(UX, _UX, NX*NY*sizeof(double));
			memmove(UY, _UY, NX*NY*sizeof(double));
			memmove(NU, _NU, NX*NY*sizeof(double));
			memmove(Kt, _Kt, NX*NY*sizeof(double));
			memmove(Et, _Et, NX*NY*sizeof(double));
			for (int c = 0; c < NC; c++)
				memmove(C[c], _C[c], NX*NY*sizeof(double));
			tau /= 2.0;
			err = Step(Euler, mode);
			err = Step(Euler, mode);
			tau *= 2.0;
			double err0 = 0.0;
			err = 0.0;
			for (int i = 1; i < NY-1; i++)
				for (int j = 1; j < NX-1; j++) {
					double _err = fabs(omega[i][j]-__omega[i][j])/(2.0*2.0-1);
					if (_err > err) err = _err;
					_err = fabs(psi[i][j]-__psi[i][j])/(2.0*2.0-1);
					if (_err > err) err = _err;
					_err = fabs(NU[i][j]-__NU[i][j])/(2.0*2.0-1);
					if (_err > err) err = _err;
					_err = fabs(tk[i][j] - __tk[i][j]) / (2.0*2.0 - 1);
					if (_err > err) err = _err;
					/*
					for (int c = 0; c < NC; c++) {
						_err = fabs(C[c][i*NX+j]-__C[c][i*NX+j])/(2.0*2.0-1);
						if (_err > err) err = _err;
					}
					*/
					ERRS[i][j] = +k1*err/TOL;
					if (err > err0) err0 = err;
				}
			double q = pow(TOL/max(1E-7,err0), 0.8);
			if (q > 5.0) q = 5.0;
			if (q < 0.001) q = 0.001;
			tau *= q;
			Poisson(false, (unsigned char *) MAP, (double *) GRAV, (double *) ERRS);
		}
		for (int p = 0; p < NP; p++) {
			int i = (int)(PARTY[p] / h);
			int j = (int)(PARTX[p] / h);
			if (i > 0 && i < NY-1 && j > 0 && j < NX-1) {
				double PX = k2*(GRAV[i][j+1]-GRAV[i][j-1])/2.0/h - k4*PARTVX[p]*PARTV[p];
				double PY = k2*(GRAV[i+1][j]-GRAV[i-1][j])/2.0/h - k4*PARTVY[p]*PARTV[p];
                PARTVX[p] = PARTVX[p] + tau*PX;
				PARTVY[p] = PARTVY[p] + tau*PY;
				PARTX[p] = PARTX[p] + tau*PARTVX[p];
				PARTY[p] = PARTY[p] + tau*PARTVY[p];
				PARTV[p] = hypot(PARTVX[p], PARTVY[p]);
			}
		}
		for (int i = 0; i < NY; i++)
			for (int j = 0; j < NX; j++)
				ALPHA[i][j] = 0.0;
		for (int p = 0; p < NP; p++) {
			int _i = (int)(PARTY[p] / h);
			int _j = (int)(PARTX[p] / h);
			ALPHA[_i][_j] += 1.0;
		}
		for (int i = 0; i < NY; i++)
			for (int j = 0; j < NX; j++) {
				int q = (int)(0.5 + ALPHA[i][j]);
				ALPHA[i][j] = 1.0 - 0.5*(q <= 1 ? 0.0 : (q < M ? 1.0*q/M : 1.0));
			}
	}
	printf("SPECIAL CHECK EULER TIME = %lf at time = %lf with kinetic time = %lf\n", omp_get_wtime() - t0, time, kin_time);
	auto WRITE = [&](char * name, double * vals) {
		FILE * F = fopen(name, "w+t");
		int ptr = 0;
		for (int i = 0; i < NY; i++) {
			for (int j = 0; j < NX; j++, ptr++) {
				fprintf(F, "%lf ", vals[ptr]);
			}
			fprintf(F, "\n");
		}
		fclose(F);
	};
	WRITE("nturb_lm2.dat", (double *) L2);
	WRITE("nturb_nu.dat", (double *) NU);
	WRITE("nturb_t.dat", (double *)tk);
	WRITE("nturb_vx.dat", (double *)UX);
	WRITE("nturb_vy.dat", (double *) UY);
	WRITE("nturb_c0.dat", (double *)C[0]);

	for (int c = 0; c < NC; c++) {
		delete[] C[c];
		delete[] _C[c];
		delete[] __C[c];
		delete[] st_C[c];
	}

	return 0;
}