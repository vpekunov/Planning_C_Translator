#include <iostream>

#include "reentera.h"

using namespace std;

int main() {
  auto c = chain[4]<bool init, int val, int from> {
    if (reent_stage() == 0 && init)
       cout << reent_stage() << " is first. Send " << (reent_stage()+1) << endl;
    else if (!init)
       cout << reent_stage() << ": [" << val << "] received from " << from << endl;
    if (init && reent_stage() < reent_num_stages()-1)
       reent_next_last(false, reent_stage()+1, reent_stage());
  };

  c(true, 0, -1);

  return 0;
}