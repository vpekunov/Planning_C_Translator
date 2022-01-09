#include <iostream>

using namespace std;

const int N = 150;

chain Sender(int A) throw(int B) {
   for (int i = 0; i < N; i++)
       throw_last(i);
   throw_last(-1);
}

chain Receiver(int B) {
   while (B >= 0) {
      cout<<B<<" ";
      plan_get_first(B);
   } 
}

int main() {
    plan_parallel_chain(0, Sender(0), Receiver(0));

    return 0;
}