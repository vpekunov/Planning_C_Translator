#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int NX = 30;
const int NY = 30;

const double h = 0.1 * 3 / 4;

const int NP = 15000;

// Собирающая электростатическая линза
const double U1 = 200;
const double U2 = 5000;

const double e = -1.5E-13;
const double m = 1E-11;

const double e0 = 8.85E-12;

const double V = h*h;

const double tau = 0.000005;

const double T = 0.03;

const double POISSON_EPS = 0.01;

const double TOL_EPS = 0.25;

double * U; 
double * UU;
double * EX;
double * EY;
double * PX;
double * PY;
int * X;
int * Y;

reenterable CALC(bool init, TIn<double> * _in, TOut<double> * _out, double timeout_ms) {
	if (init) {
		plan_last(false, NULL, _out, timeout_ms);
		plan_last(false, _in, NULL, timeout_ms);
		plan_group_soft_atomize; 
	} else {
		double ro[NY][NX];

		double id = plan_processor_id();

		if (id == 0) {
			for (int i = 1; i < NY - 1; i++)
				for (int j = 1; j < NX - 1; j++) {
					EX[i*NX+j] = -(U[i*NX+j+1]-U[i*NX+j-1])/2.0/h;
					EY[i*NX+j] = -(U[(i+1)*NX+j]-U[(i-1)*NX+j])/2.0/h;
				}
							
			for (int i = 0; i < NP; i++) {
				PX[i] += tau*e*EX[Y[i]*NX+X[i]]/m;
				PY[i] += tau*e*EY[Y[i]*NX+X[i]]/m;
			}

			unsigned int n[NY][NX] = { 0 };
			for (int i = 0; i < NP; i++) {
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

			for (int i = 0; i < NY; i++)
				for (int j = 0; j < NX; j++)
					ro[i][j] = n[i][j]*e/V;
			_out->put((double *)ro);
		} else if (id == 1) {
			_in->get((double *)ro, timeout_ms);

			const double theta = 1.83;

			double err;
			do {
				err = 0.0;
		
				for (int i = 1; i < NY - 1; i++)
					for (int j = 1; j < NX - 1; j++) {
					  int ptr = i*NX + j;
					  if (!(j == NX/2 && (i < NY/4 || i > 3*NY/4))) {
						double _new = (1-theta)*UU[ptr] + theta/4.0*(UU[ptr-1]+UU[ptr+1]+UU[ptr+NX]+UU[ptr-NX]-h*h*ro[i][j]/e0);
						double loc_err = fabs(UU[ptr] - _new);
						if (loc_err > err) err = loc_err;
						UU[ptr] = _new;
					  }
					}
				for (int j = 0; j < NX; j++) {
					UU[j] = UU[NX + j];
					UU[(NY-1)*NX + j] = UU[(NY-2)*NX + j];
				}
			} while (err > POISSON_EPS);
		}
	}
}

int main() {
        U = new double[NY*NX];
        UU = new double[NY*NX];
        EX = new double[NY*NX];
        EY = new double[NY*NX];
	PX = new double[NP];
	PY = new double[NP];
	X = new int[NP];
	Y = new int[NP];

	for (int i = 0; i < NY; i++)
		for (int j = 0; j < NX; j++) {
			UU[i*NX+j] = j == NX-1 ? U2 : j == NX/2 && (i < NY/4 || i > 3*NY/4) ? U1 : 0.0;
			EX[i*NX+j] = 0.0;
			EY[i*NX+j] = 0.0;
		}
	for (int i = 0; i < NP; i++) {
		PX[i] = 0.5*NX*h*rand()/RAND_MAX;
		PY[i] = NY*h*rand()/RAND_MAX;

		int x = PX[i]/h;
		int y = PY[i]/h;
		if (x < 0) x = 0;
		else if (x > NX-1) x = NX-1;
		if (y < 0) y = 0;
		else if (y > NY-1) y = NY-1;

		X[i] = x;
		Y[i] = y;
	}

	double timeout_ms = 0.0;
	cout << "timeout [ms] = ";
	cin >> timeout_ms;

	TOut<double> * _out = new TOut<double>("RO", NX*NY, 2, TOL_EPS, 0);
	TIn<double> * _in = new TIn<double>("RO", NX*NY, 2, TOL_EPS, 1);

	double tm = omp_get_wtime();
	for (double t = 0.0; t < T; t += tau) {
		memmove(U, UU, NX*NY*sizeof(double));
		CALC(true, _in, _out, timeout_ms);
	}

	cout << "time = " << (omp_get_wtime() - tm) << endl;

	ofstream outU("lens_u.txt");
	for (int i = 0; i < NY; i++) {
		for (int j = 0; j < NX; j++)
			outU << U[i*NX+j] << "\t";
		outU << endl;
	}
	outU.close();

	ofstream outP("lens.txt");
	for (int i = 0; i < NP; i++) {
		outP << PX[i] << "\t" << PY[i] << endl;
	}
	outP.close();

	delete[] U;
	delete[] EX;
	delete[] EY;
	delete[] PX;
	delete[] PY;
	delete[] X;
	delete[] Y;

	return 0;
}