#include <stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;
#include "transacted.h"

const int N = 10000;
const int M = 600;
const int NF = 20;

class Histogrammer {
public:
	TArray<int> * F;
	Histogrammer(int nthreads) {
		F = new TArray<int>(NF);
		*F = 0;
	}
	void process(int * A, double grain, int i) {
		int k = A[i] / grain;
		if (k >= NF) k = NF - 1;
		++((*F)[k]);
	}
	~Histogrammer() {
		delete F;
	}
};

int main() {
        int * A = new int[N];

	srand(184415);
	for (int i = 0; i < N; i++)
	    A[i] = rand() % M;

	double grain = 1.0 * M / NF;
	TQueuedObj<Histogrammer> obj(omp_get_num_procs());

	for (int i = 0; i < N; i++)
		obj.cilk_spawn obj.process(A, grain, =i);
	obj.cilk_sync;

	int SF = 0;
	for (int i = 0; i < NF; i++)
		SF += (*obj.F)[i];
	cout << SF;

	delete[] A;

	return 0;
}