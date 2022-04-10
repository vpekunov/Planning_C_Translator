#include "cilk_compile.h"

#pragma auto for
#pragma auto pure(sqrt)
#pragma auto pure(exp,sin)

#include <stdio.h>
#include <math.h>
#include <omp.h>

#define PI 3.14159265358

#define NX 100

#define NY 100

#define MaxT 0.001

#define h 0.01

#define tau 0.00001

#define cilk_spawn _Cilk_spawn
#define cilk_sync _Cilk_sync
#define cilk_for _Cilk_for

double F(double x, double y, double t) {
  double r = sqrt(x*x + y*y);
  double result = 0.0;
  int i;

  for (i = 0; i < 300; i++)
      result += exp(-r*t)*sin(0.1*i*r + 0.5*PI);

  return result;
}

int main() {
  double v[NY][NX] = {0.0};
  double v1[NY][NX] = {0.0};
  double t;
  int x, y;

  double start = omp_get_wtime();

  for (t = 0.0; t < MaxT; t += tau) {
      for (y = 1; y < NY-1; y++)
          for (x = 1; x < NX-1; x++)
              v1[y][x] = v[y][x] + tau*((v[y-1][x]+v[y+1][x]+v[y][x-1]+v[y][x+1]-4.0*v[y][x])/h/h - F(x*h, y*h, t));
      for (y = 1; y < NY-1; y++)
          for (x = 1; x < NX-1; x++)
              v[y][x] = v1[y][x];
  }

  for (y = 0; y < NY; y++) {
      for (x = 0; x < NX; x++)
          printf("%lf ", v[y][x]);
      printf("\n");
  }

  printf("Total time = %lf\n", omp_get_wtime() - start);

  return 0;
}