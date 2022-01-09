#include <iostream>
#include <iomanip>

using namespace std;

#include "memoization.h"

#pragma memoization(i)
double fibb(int a) {
  if (a < 3) return 1;
  else return fibb(a-1)+fibb(a-2);
}

#pragma memoization(i,o)
void fibb(int a, double &result) {
  if (a < 3) result = 1;
  else {
    double b, c;
    fibb(a-1, b);
    fibb(a-2, c);
    result = b+c;
  }
}

#pragma memoization(i,*o)
void fibb(int a, double * result) {
  if (a < 3) *result = 1;
  else {
    double b, c;
    fibb(a-1, &b);
    fibb(a-2, &c);
    *result = b+c;
  }
}

int main() {
        cout << setprecision(16) << fibb(77) << endl;

	double r;

	fibb(77, r);

        cout << setprecision(16) << r << endl;

	fibb(77, &r);

        cout << setprecision(16) << r << endl;

	return 0;
}