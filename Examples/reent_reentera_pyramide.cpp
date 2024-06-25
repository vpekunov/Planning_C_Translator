#include "stdtopo.h"

#include <iostream>

using namespace std;

const int NP = 5;

int main() {
    int SUM = 0;
    int PROCESSED = 0;

    auto t = topology pyramide[NP] <input_proc Src, int val> {
      int id = reent_linear_num();

      input_proc outcoming[128];
      int n_out;

      reent_neighbours(false, this[id], &n_out, outcoming);

      if (id == master()) {
         if (input_index(Src) == 0) {
            SUM = 0;
            PROCESSED = 0;
            for (int i = 0; i < n_out; i++)
                reent_next_first(outcoming[i], val+1);
         } else {
            plan_critical(topology) {
               SUM += val;
            }
            PROCESSED++;
            if (PROCESSED == NP-1) {
               cout << SUM << endl;
               reent_topology_quit();
            }
         }
      } else if (input_index(Src) != 0)
         if (input_index(Src) == master())
            reent_next_first(this[forw()], val+1);
         else
            reent_next_first(this[master()], val+1);
    };

    t(empty_proc, 23);

    return 0;
}