#include <iostream>

#include "reentera.h"

using namespace std;

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

  return 0;
}