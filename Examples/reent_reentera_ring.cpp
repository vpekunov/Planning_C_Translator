#include "stdtopo.h"

#include <iostream>

using namespace std;

const int NP = 5;

int main() {
    int SUM = 0;

    auto t = topology ring[NP] <input_proc Src, int from, int val> {
      int id = reent_linear_num();

      if ((id == 1) ^ (from >= 1)) {
         reent_next_first(this[forw()], id, val+1);
      }
      if (from >= 1) {
         plan_critical(topology) {
            SUM += val;
         }
         if (id == 1) {
            cout << SUM << endl;
            reent_topology_quit();
         }
      }
    };

    t(empty_proc, 0, 39);

    return 0;
}