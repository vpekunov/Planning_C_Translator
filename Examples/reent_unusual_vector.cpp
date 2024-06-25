// Debugged

#include <iostream>

using namespace std;

chain[100] A(int a) {
  if (a != 0) cout << a << " ";
}

chain[100] B(int b) {
  cout << b << " ";
}

int main() {
  int a[5] = { 1, 2, 3, 4, 5 };
  int b[3] = { 6, 7, 8 };

  *A << [a[]];
  *B << [b[]];

  plan_parallel_chain(0, A(0), B(0));

  return 0;
}