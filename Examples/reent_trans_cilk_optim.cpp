#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>

#include <iostream>

#include "transacted.h"

using namespace std;

const int N = 3;

const double EPS = 0.00001;

class Variant {
public:
	TArray<double> * X;
	TArray<bool> * Locked;
	TScalar<double> * F;

	Variant(int nthreads) {
		X = new TArray<double>(N);
		F = new TScalar<double>();
		Locked = new TArray<bool>(N);
		*F = 10000;
	}

	double FUN(double * x) {
		return pow(1.5 - x[0], 2)*pow(x[1] - 0.25, 2)*pow(1.7 - x[2]*x[2], 2);
	}

	void process(double * x, bool * L) {
		// Решаем задачу оптимизации
		TQueuedObj<Variant> * variants = NULL;
		double f, f0;
		do {
			double g[N];
			f0 = FUN(x);
			f = f0;
			for (int i = 0; i < N; i++) {
				const double delta = 0.000001;

				x[i] += delta;
				double f1 = FUN(x);
				x[i] -= delta;
				g[i] = (f1 - f)/delta;
			}
			double step = 0.1;
			while (step > EPS) {
				double x1[N];
				for (int i = 0; i < N; i++)
					x1[i] = L[i] ? x[i] : (x[i] - step*g[i]);
				double ff = FUN(x1);
				if (ff < f - EPS) {
					f = ff;
					for (int i = 0; i < N; i++)
						x[i] = x1[i];
				} else
					step /= 2.0;
			}
		} while (fabs(f0 - f) > EPS);
		bool integer = true;
		for (int i = 0; i < N; i++) {
			double xv = x[i];
			if (!L[i] && fabs((int)(xv)-xv) > EPS) {
				double * x1 = new double[N];
				bool * L1 = new bool[N];
				for (int j = 0; j < N; j++) {
					x1[j] = x[j];
					L1[j] = L[j];
				}
				x1[i] = ceil(xv);
				L1[i] = true;
				if (variants == NULL) {
					variants = new TQueuedObj<Variant>(2);
				}
				int id1 = variants->cilk_spawn variants->process(x1, L1);

				double * x2 = new double[N];
				bool * L2 = new bool[N];
				for (int j = 0; j < N; j++) {
					x2[j] = x[j];
					L2[j] = L[j];
				}
				x2[i] = floor(xv);
				L2[i] = true;
				int id2 = variants->cilk_spawn variants->process(x2, L2);
				integer = false;
			}
		}
		if (integer && f < *F) {
			*F = f;
			for (int i = 0; i < N; i++) {
				(*X)[i] = x[i];
				(*Locked)[i] = L[i];
			}
		}
		if (variants) {
			variants->cilk_sync(false);
			if (*variants->F < *F) {
				*F = *variants->F;
				for (int i = 0; i < N; i++) {
					(*X)[i] = (*variants->X)[i];
					(*Locked)[i] = (*variants->Locked)[i];
				}
			}
			delete variants;
		}
	}

	~Variant() {
		delete F;
		delete Locked;
		delete X;
	}
};

int main() {
	TQueuedObj<Variant> task(1);
	double x[N] = { 0.0 };
	bool L[N] = { false };

	int id = task.cilk_spawn task.process(x, L);
	task.cilk_sync();

	cout << "F[ ";
	for (int i = 0; i < N; i++) {
		cout << (*task.X)[i] << " ";
	}
	cout << "] = " << *task.F << endl;

	return 0;
}