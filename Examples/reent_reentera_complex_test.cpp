#include <iostream>

#include "reentera.h"

#include "stdtopo.h"

using namespace std;

const int NP = 5;

void proc() {
  int SUM = 0;

  auto t = topology ring[NP] <input_proc Src, int from, int val> {
    int id = reent_linear_num();

    if ((id == 1) ^ (from >= 1)) {
       reent_next_first(this[1 + id % NP], id, val+1);
    }
    if (from >= 1) {
       SUM += val;
       if (id == 1) {
          cout << SUM << endl;
          reent_topology_quit();
       }
    }
  };

  t(empty_proc, 0, 39);

  auto f = reenterable (int cur, int last)  {
     cout << cur << " ";
     if (cur < last)
        reent_first(cur+1, last);
     else
        cout << endl;
  };

  f(0, 5);
}

int main() {
  chain<bool init> (true) {
    reent_next_first(false, 1);
  }
  chain<bool init, int N> (true, 0) {
    if (!init) {
       reent_next_first(false, N+1, "Calculated: ");
    }
  }
  chain<bool init, int N, char * msg> (true, 0, NULL) {
    if (!init) {
       cout<<msg<<N;
    }
  };

  auto c = chain[4]<bool init, int val, int from> {
    if (reent_stage() == 0 && init)
       cout << reent_stage() << " is first. Send " << (reent_stage()+1) << endl;
    else if (!init)
       cout << reent_stage() << ": [" << val << "] received from " << from << endl;
    if (init && reent_stage() < reent_num_stages()-1)
       reent_next_last(false, reent_stage()+1, reent_stage());
  };

  c(true, 0, -1);

  proc();

  return 0;
}