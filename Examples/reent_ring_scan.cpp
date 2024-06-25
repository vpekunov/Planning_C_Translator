typedef struct {
  int sender;
  int val;
} data_MY;

#include "ring.h"

using namespace std;

#define NP 5

int main() {
    data_MY INIT = { 0 };

    int SUM = 0;

    ring<data_MY>(NP, INIT) {
      if (id != 0 || data.sender == 0) {
         const data_MY DATA = { id, id };

         send(DATA);
      }
      plan_critical(topology) {
        SUM += data.val;
      }
      if (id == 0 && data.sender != 0)
         cout << SUM << endl;
    };
}