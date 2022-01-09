#include <iostream>

#include <stdlib.h>
#include <time.h>

#include "memoization.h"

using namespace std;

const int N = 26;

double seq[N] = { 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, 0.0, 1.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0 };

#pragma memoization(t) lin_extrapolator(1, 3) controlled(5, 2)
double series(int t) {
	return seq[t];
}

int main() {
	srand((unsigned int) time(NULL));

	for (int i = 0; i < N; i++)
            cout << seq[i] << " ";
	cout << endl;
	for (int i = 0; i < N; i++)
            cout << series(i) << " ";
	cout << endl;

	return 0;
}