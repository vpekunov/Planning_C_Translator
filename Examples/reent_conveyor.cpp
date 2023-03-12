// Debugged

#include <iostream>

using namespace std;

chain A(funnel(out, int) * V) {
  int DATA = 1;
  Sleep(1000);
  if (V->empty()) /* Это только, чтобы продемонстрировать работу empty() -- можно убрать. */
     *V = DATA; /* V->put(&DATA, sizeof(DATA)); */
}

chain B(funnel(in, int) * V) {
  int DATA = 0;
  while (V->empty()) /* Это только, чтобы продемонстрировать работу empty() -- цикл можно убрать. */
    _Yield();
  /* V->get(&DATA, sizeof(DATA)); cout<<DATA<<endl; */
  cout<<**V<<endl;
}

chain A1() throw(int DATA) {
  Sleep(1000);
  throw_last(1);
}

chain B1(int DATA) {
  cout<<DATA<<endl;
}

int main() {
  funnel(in, int) * _IN   = new funnel(in, int)("AB");
  funnel(out, int) * _OUT = new funnel(out, int)("AB");

  plan_parallel_chain(1, A(_OUT), B(_IN));

  plan_parallel_chain(0, A1(), B1(0));

  return 0;
}