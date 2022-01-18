#pragma plan clustered

#include <iostream>

#include "reentera.h"

using namespace std;

int main() {
  int IDS[3] = { 0, 1, 2 };
  clustered(IDS) chain<bool init> (true) {
    reent_next_first(false, 1);
  }
  chain<bool init, int N> (true, 0) {
    if (!init) {
       reent_next_first(false, N+1);
    }
  }
  chain<bool init, int N> (true, 0, NULL) {
    if (!init) {
       cout<<"Calculated: "<<N;
    }
  };

  return 0;
}