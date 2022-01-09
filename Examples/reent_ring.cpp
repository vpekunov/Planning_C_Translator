#include <functional>
#include <iostream>

using namespace std;

typedef struct {
  int sender;
  int val;
} data_MY;

typedef std::function<void(const data_MY data)> ring_sender_MY;

typedef std::function<void(int id, ring_sender_MY send, const data_MY data)> ring_function_MY;

chain ring_MY(bool init, int N, input_proc in, ring_function_MY worker, const data_MY data) {
    ring_sender_MY send = [&] (const data_MY data) {
         if (plan_linear_num() < N)
            throw_last(false, N, ring_MY[plan_linear_num()+1], worker, data);
         else
            throw_last(false, N, ring_MY[1], worker, data);
    };

    if (plan_linear_num() == 1) {
       worker(0, send, data);
       if (!init) plan_topology_quit();
    } else if (!init)
       worker(input_index(in), send, data);
}

#define NP 5

int main() {
    data_MY INIT = { 0 };

    int SUM = 0;

    ring_function_MY worker_MY = [&] (int id, ring_sender_MY send, const data_MY data) {
      if (id != 0 || data.sender == 0) {
         const data_MY DATA = { id, id };

         send(DATA);
      }
      SUM += data.val;
      if (id == 0 && data.sender != 0)
         cout << SUM << endl;
    };

    plan_topology {
      plan_parallel_chain(ring_MY[1](true, NP, empty_proc, worker_MY, INIT)->ring_MY[2](true, NP, empty_proc, worker_MY, INIT));
      plan_parallel_chain(ring_MY[2](true, NP, empty_proc, worker_MY, INIT)->ring_MY[3](true, NP, empty_proc, worker_MY, INIT));
      plan_parallel_chain(ring_MY[3](true, NP, empty_proc, worker_MY, INIT)->ring_MY[4](true, NP, empty_proc, worker_MY, INIT));
      plan_parallel_chain(ring_MY[4](true, NP, empty_proc, worker_MY, INIT)->ring_MY[5](true, NP, empty_proc, worker_MY, INIT));
      plan_parallel_reverse(ring_MY[5](true, NP, empty_proc, worker_MY, INIT)->ring_MY[1](true, NP, empty_proc, worker_MY, INIT));
    }/NP;
}