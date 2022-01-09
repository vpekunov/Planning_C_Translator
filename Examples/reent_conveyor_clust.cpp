// Debugged

#pragma plan clustered

#include <iostream>

using namespace std;

chain A() {
  for (int i = 0; i < 100; i++) {
      cfunnel(out, int) * V = new cfunnel(out, int)("AB");
      int DATA = 1;
      Sleep(rand()%10);
      if (V->empty()) /* Это только, чтобы продемонстрировать работу empty() -- можно убрать. */
         *V = DATA; /* V->put(&DATA, sizeof(DATA)); */
      Sleep(rand()%10);
      delete V;
  }
}

chain B() {
  for (int i = 0; i < 100; i++) {
      cfunnel(in, int) * V   = new cfunnel(in, int)("AB");
      int DATA = 0;
      Sleep(rand()%10);
      while (V->empty()) /* Это только, чтобы продемонстрировать работу empty() -- цикл можно убрать. */
        _Yield();
      Sleep(rand()%10);
      /* V->get(&DATA, sizeof(DATA)); cout<<DATA<<endl; */
      cout<<**V;
      Sleep(rand()%10);
      delete V;
  }
}

chain A1() throw(int DATA) {
  Sleep(1000);
  throw_last(1);
}

chain B1(int DATA) {
  cout<<DATA<<endl;
}

int main() {
  int IDs[2] = {0,1};

  clustered(IDs) plan_parallel_chain(0, A1(), B1(0));

  clustered(IDs) plan_parallel_chain(1, A(), B());

  return 0;
}