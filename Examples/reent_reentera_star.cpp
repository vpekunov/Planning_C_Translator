#include "stdtopo.h"

#include <iostream>

using namespace std;

const int NP = 5;

int main() {
    int SUM = 0;
    int PROCESSED = 0;

    auto t = topology star[NP] <input_proc Src, int val> {
      int id = reent_linear_num();

      if (id == master()) {
         if (input_index(Src) == 0) {
            SUM = 0;
            PROCESSED = 0;
            for (int i = 0; i < num_slaves(); i++)
                reent_next_first(this[slave(i)], val+1);
         } else {
            SUM += val;
            PROCESSED++;
            if (PROCESSED == NP-1) {
               cout << SUM << endl;
               reent_topology_quit();
            }
         }
      } else if (input_index(Src) != 0)
         reent_next_first(this[master()], val+1);
    };

    t(empty_proc, 78);

    return 0;
}