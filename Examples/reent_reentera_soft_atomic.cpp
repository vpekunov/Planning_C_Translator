#include <stdlib.h>

#include <iostream>

#include "reentera.h"

using namespace std;

const int N = 10000;

const int M = 600;

const int NF = 20;

int main() {
        int * A = new int[N];
	soft_transact_array(int) F(NF);

	srand(184415);

	for (int i = 0; i < N; i++)
	    A[i] = rand() % M;

	double grain = 1.0 * M / NF;

	F = 0;
        auto fun = reenterable(bool init, int np, int * A, soft_transact_array(int) * FF, double grain, int k)->int {
        	if (init) {
        		for (int i = 0; i < N; i += np) {
        			for (int j = 0; j < np; j++)
        				reent_last(false, np, A, FF, grain, i + j);
        			reent_group_soft_atomize;
        		}
			int SF = 0;
			for (int i = 0; i < NF; i++) {
				int VAL = (*FF)[i];
				SF += VAL;
			}
			return SF;
        	} else {
        		if (k < N) {
        			int _k = A[k] / grain;
        			if (_k >= NF) _k = NF - 1;
        			++(*FF)[_k];
        		}
        	}
		return 0;
        };

        cout << fun(true, 4, A, &F, grain, 0);

	delete[] A;

	return 0;
}