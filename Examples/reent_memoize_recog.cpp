#include "memoization.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

float class1 = 1;
int cross1[5][4] = {
   { 1, 0, 0, 1 },
   { 0, 1, 1, 0 },
   { 0, 1, 1, 0 },
   { 1, 0, 0, 1 },
   { 0, 0, 0, 0 }
};

float class2 = 1;
int cross2[5][4] = {
   { 0, 0, 0, 0 },
   { 1, 0, 0, 1 },
   { 0, 1, 1, 0 },
   { 0, 1, 1, 0 },
   { 1, 0, 0, 1 }
};

float class3 = 0;
int zero[5][4] = {
   { 0, 1, 1, 0 },
   { 1, 0, 0, 1 },
   { 1, 0, 0, 1 },
   { 1, 0, 0, 1 },
   { 0, 1, 1, 0 }
};

#pragma memoization(i, o) feed_forward(0.001, 0.025, 5000, 5, e)
void recog(int c[5][4], float & code) {
}

int test[5][4] = {
   { 0, 1, 1, 0 },
   { 1, 1, 0, 1 },
   { 1, 0, 1, 1 },
   { 1, 0, 0, 1 },
   { 0, 1, 1, 0 }
};

int main() {
	srand((unsigned int) time(NULL));

	recog(cross1, class1);
	recog(cross2, class2);
	recog(zero, class3);

	float c;
	predict_recog(test, c);
	cout << c << endl;

	return 0;
}