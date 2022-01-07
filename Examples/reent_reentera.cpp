#include <iostream>

#include "reentera.h"

using namespace std;

int main() {
   auto f = reenterable (int cur, int last)  {
      cout << cur << " ";
      if (cur < last)
         reent_first(cur+1, last);
      else
         cout << endl;
   };

   f(0, 5);

   return 0;
}