// Debugged

#include <math.h>

#include <iostream>

using namespace std;

const double eps = 1E-8;

enum { fnSin, fnCos };

chain Main(double x) throw(int proc, double x, funnel(in, double) * VAR) {
  funnel(in, double) * sin_in = new funnel(in, double)();
  funnel(in, double) * cos_in = new funnel(in, double)();

  throw_last(fnSin, x, sin_in);
  throw_last(fnCos, x, cos_in);

  double s = **sin_in;
  double c = **cos_in;

  cout<<(s+c)<<" vs "<<(sin(x)+cos(x))<<endl;
}

chain Calc(int proc, double x, funnel(in, double) * VAR) {
  funnel(out, double) * _OUT = new funnel(out, double)(VAR);

  plan_group_parallelize;

  if (proc == fnSin) {
     double result = 0.0;
     double item = x;
     int m = 1;
     while (fabs(item) > eps) {
        result += item;
        m++;
        item *= -x*x/((2*m-1)*(2*m-2)); 
     }
     *_OUT = result;
  } else if (proc == fnCos) {
     double result = 0.0;
     double item = 1.0;
     int m = 1;
     while (fabs(item) > eps) {
        result += item;
        item *= -x*x/(2*m*(2*m-1)); 
        m++;
     }
     *_OUT = result;
  }
}

int main() {
  double x;

  cout<<"x = ";
  cin>>x;

  plan_parallel_chain(0, Main(x), Calc(0, x, NULL)/8);

  return 0;
}