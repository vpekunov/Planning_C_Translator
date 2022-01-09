#include <iostream>

#include "reentera.h"

using namespace std;

int main() {
  auto c = chain[4]<bool init> {
    cout << reent_stage() << " from " << reent_num_stages() << endl;
  };

  c(true);

  return 0;
}