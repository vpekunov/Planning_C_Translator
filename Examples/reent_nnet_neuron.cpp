#include <iostream>

using namespace std;

reenterable static neuro1(double x, int k, double * a, double &g) {
  g = x*g + *a;
  if (k > 0) plan_last(x, k - 1, a + 1, g);
}

reenterable static neuro2(double x, double a, double &g) {
  g = x*g + a;
}

int main() {
  double a[3] = {3.0, 2.0, 1.0};
  double x = 2.0;

  double f1 = 0.0;
  neuro1(x, 2, a, f1);

  cout<<f1<<endl;

  double f2 = 0.0;
  *neuro2<<[x, a[], 0.0];
  neuro2([x, 0.0, f2]);

  cout<<f2<<endl;

  return 0;
}