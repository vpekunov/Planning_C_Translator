#include <stdlib.h>

#include <iostream>

using namespace std;

const int N = 10000;

const int M = 600;

const int NF = 20;

reenterable calc_histo(bool init, int np, int * A, soft_transact_array(int) * F, double grain, int k) {
	if (init) {
		for (int i = 0; i < N; i += np) {
			for (int j = 0; j < np; j++)
				plan_last(false, np, A, F, grain, i + j);
			plan_group_soft_atomize;
		}
	} else {
		if (k < N) {
			int _k = A[k] / grain;
			if (_k >= NF) _k = NF - 1;
			++(*F)[_k];
		}
	}
}

int main() {
        int * A = new int[N];
	soft_transact_array(int) F(NF);

	srand(184415);

	for (int i = 0; i < N; i++)
	    A[i] = rand() % M;

	double grain = 1.0 * M / NF;

	F = 0;
	calc_histo(true, 4, A, &F, grain, 0);

	int SF = 0;
	for (int i = 0; i < NF; i++)
		SF += F[i];
	cout << SF;

	delete[] A;

	return 0;
}