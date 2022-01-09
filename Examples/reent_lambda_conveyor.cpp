#include <functional>
#include <iostream>

using namespace std;

typedef std::function<void(int A)> _sender;

typedef std::function<void(_sender send, int n, int stage, int A)> _function;

chain conveyor(_function worker, int A) {
    _sender send = [&] (int A) {
         throw_last(worker, A);
    };

    worker(send, throw_num_stages(), throw_stage(), A);
}

int main() {
    _function worker = [&] (_sender send, int n, int stage, int A) {
         A += stage;
         if (stage == n - 1) cout << A << endl;
         else send(A);
    };

    plan_parallel_chain(0, 5, conveyor(worker, -1));
}