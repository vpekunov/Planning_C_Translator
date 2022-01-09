// Debugged

const int Dims = 3;
const int N = 3;

#include "stdtopo.h"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<bool> Visited;
vector<bool> bVisited;

int main() {

  auto t = topology hypercube[Dims, N] <input_proc Src, int Dims, int N, int K> {
     int Total = pow(N,Dims);
     int id = reent_linear_num();
     vector<int> * idxs = get_idxs(id-1);

     auto ForwardSend = [&](int K) {
       for (int i = 0; i < Dims; i++) {
           (*idxs)[i]++;
           if ((*idxs)[i] < N) {
              int send_id = get_idx(idxs)+1;
              bool flag = false;
              plan_critical(hypercube)
              {
                 if (!Visited[send_id-1]) {
                    Visited[send_id-1] = true;
                    flag = true;
                 }
              }
              if (flag) reent_next_first(this[send_id],Dims,N, K);
           }
           (*idxs)[i]--;
       }
     };

     auto BackwardSend = [&](int K) {
       for (int i = 0; i < Dims; i++) {
           (*idxs)[i]--;
           if ((*idxs)[i] >= 0) {
              int send_id = get_idx(idxs)+1;
              bool flag = false;
              plan_critical(hypercube)
              {
                 if (!bVisited[send_id-1]) {
                    bVisited[send_id-1] = true;
                    flag = true;
                 }
              }
              if (flag) reent_next_first(this[send_id],Dims,N, K);
           }
           (*idxs)[i]++;
       }
     };

     if (Src == empty_proc) {
        if (id == 1) {
           plan_critical(hypercube)
           {
             for (int i = 0; i < Total; i++)
                 Visited.push_back(false);
             Visited[0] = true;
           }
           ForwardSend(21);
        }
     } else if (input_index(Src) < id) {
        if (id == Total) {
           plan_critical(hypercube)
           {
             for (int i = 0; i < Total-1; i++)
                 Visited[i] = true;
             Visited[Total-1] = true;
             for (int i = 0; i < Total; i++)
                 bVisited.push_back(false);
             bVisited[Total-1] = true;
           }
           BackwardSend(K);
        } else
           ForwardSend(K);
     } else {
        if (id == 1) {
           cout<<"After hypercube traverse K = "<<K;
           reent_topology_quit();
        } else
           BackwardSend(K);
     }

     delete idxs;
  };

  t(empty_proc,Dims,N,0);

  return 0;
}