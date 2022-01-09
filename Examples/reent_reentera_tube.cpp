#include "stdtopo.h"

#include <iostream>

using namespace std;

const int NP = 5;

int main() {
    auto t = topology tube[NP] <input_proc Src, bool forward, int val> {
      int id = reent_linear_num();

      if (id == 1) {
         if (input_index(Src) == 0) {
            reent_next_first(this[forw()], true, val+1);
         } else {
            cout << val << endl;
            reent_topology_quit();
         }
      } else if (input_index(Src) != 0)
         if (forward) {
            if (id < NP)
               reent_next_first(this[forw()], forward, val);
            else
               reent_next_first(this[back()], false, val+1);
         } else
            reent_next_first(this[back()], forward, val);
    };

    t(empty_proc, true, 23);

    return 0;
}