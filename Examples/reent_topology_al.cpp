// Debugged

#include <iostream>

using namespace std;

#include "altopo.h"

bool stop;

chain A(bool init) throw(bool init, int N) {
  stop = false;
  throw_first(false, 1);
  Sleep(2000);
  stop = true;
}

chain B(bool init, int N) throw(bool init, bool _stop, int N) {
  if (!init) {
     if (stop) throw_first(false, true, N);
     else throw_first(false, false, N+1);
  }
}

chain C(bool init, bool _stop, int N) throw(bool init, int N) {
  if (!init) {
     if (_stop) {
        cout<<N;
        plan_topology_quit();
     } else throw_first(false, N+1);
  }
}

int main() {
  altopo([['A','(true)'],['B','(true,0)'],['C','(true,false,0)']], 'A*B*C+C*B')/3;

  return 0;
}