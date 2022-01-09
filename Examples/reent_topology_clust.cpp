// Debugged

#pragma plan clustered

#include <iostream>

using namespace std;

chain A(bool init) throw(bool init, bool stop, int N) {
  throw_first(false, false, 1);
  Sleep(2000);
  throw_first(false, true, 1);
}

chain B(bool init, bool stop, int N) throw(bool init, bool stop, int N) {
  if (!init) {
     if (stop) throw_first(false, true, N);
     else throw_first(false, false, N+1);
  }
}

chain C(bool init, bool stop, int N) throw(bool init, bool stop, int N) {
  static int lastN = 1;
  if (!init) {
     if (stop) {
        cout<<lastN;
        plan_topology_quit();
     } else {
        lastN = N+1;
        throw_first(false, false, lastN);
     }
  }
}

int main() {
  int IDS[3] = {0,1,2};

  clustered(IDS)
  plan_topology { /* A*B*C+C*B или (A+C)*B+B*C */ /* Видимо, всем эл-там всех конвейеров будут разрешены инициализационные этапы */
    plan_parallel_chain(A(true)->B(true,false,0)->C(true,false,0));
    plan_parallel_reverse(C(true,false,0)->B(true,false,0));
  }/3;

  return 0;
}