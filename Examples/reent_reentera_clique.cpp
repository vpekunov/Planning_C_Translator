// Debugged

#include "stdtopo.h"

#include <iostream>

using namespace std;

const int N = 5;

int ** DATA = NULL;
int * Counters = NULL;

int main() {
  DATA = new int * [N];
  Counters = new int [N];

  auto t = topology clique[N] <input_proc Src, int NN, int K> {
    int id = reent_linear_num()-1;

    if (K == 0) {
       DATA[id] = new int [NN];
       DATA[id][id] = id + 2;
       Counters[id] = 1;

       for (int i = 0; i < num_others(); i++)
           reent_next_first(this[other(i)], NN, id + 2);
    } else {
       DATA[id][input_index(Src)-1] = K;
       bool flag = false;
       plan_critical(topology) {
         Counters[id]++; // Magic place... Do not put before critical never
         if (Counters[id] == NN) {
            for (int i = 0; i < NN; i++)
                cout<<DATA[id][i]<<" ";
            cout<<endl;
            flag = true;
         }
       }
       if (flag) {
          reent_registered_barrier(reent_topology_num(), topology);
          if (id == NN-1)
             reent_topology_quit();
       }
    }
  };

  t(empty_proc, N, 0);

  return 0;
}