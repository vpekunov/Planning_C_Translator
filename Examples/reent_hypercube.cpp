// Debugged

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> * get_idxs(int idx, int Dims, int N) {
  vector<int> * result = new vector<int>(Dims,0);
  for (int i = 0; i < Dims; i++) {
      int k = idx % N;
      (*result)[Dims-1-i] = k;
      idx = (idx - k)/N;
  }

  return result;
}

inline int get_idx(vector<int> * idxs, int Dims, int N) {
  int result = 0;

  for (int i = 0; i < Dims; i++)
      result = result*N + (*idxs)[i];

  return result;
}

vector<bool> Visited;
vector<bool> bVisited;

chain A(input_proc Src, int Dims, int N, int K) {
  int Total = pow(N,Dims);
  int id = plan_linear_num();
  vector<int> * idxs = get_idxs(id-1, Dims, N);

  auto ForwardSend = [&](int K) {
    for (int i = 0; i < Dims; i++) {
        (*idxs)[i]++;
        if ((*idxs)[i] < N) {
           int send_id = get_idx(idxs, Dims, N)+1;
           bool flag = false;
           plan_critical(hypercube)
           {
              if (!Visited[send_id-1]) {
                 Visited[send_id-1] = true;
                 flag = true;
              }
           }
           if (flag) throw_first(A[send_id],Dims,N, K);
        }
        (*idxs)[i]--;
    }
  };

  auto BackwardSend = [&](int K) {
    for (int i = 0; i < Dims; i++) {
        (*idxs)[i]--;
        if ((*idxs)[i] >= 0) {
           int send_id = get_idx(idxs, Dims, N)+1;
           bool flag = false;
           plan_critical(hypercube)
           {
              if (!bVisited[send_id-1]) {
                 bVisited[send_id-1] = true;
                 flag = true;
              }
           }
           if (flag) throw_first(A[send_id],Dims,N, K);
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
        plan_topology_quit();
     } else
        BackwardSend(K);
  }

  delete idxs;
}

#def_module(plan_topology) hypercube(NDims,NN,Args) {
   /* Можно все положительные направления сделать прямыми линками, а отрицательные -- реверсивными */
   @getidx(_,[],_,1):-!.
   @getidx(N,[H|T],Mul,IND):-Mul1 is Mul*N, getidx(N,T,Mul1,IBase), IND is IBase+(H-1)*Mul.

   @try_link(L,HB,H,R,I,N):-
     H>0, N1 is N+1, H<N1, !,
     append(L,[H|R],I1),
     getidx(N,I,1,IND),
     number_atom(IND,AIND), atom_concat('A[',AIND,A1), atom_concat(A1,']',A2), atom_concat(A2,Args,A3),
     getidx(N,I1,1,IND1),
     number_atom(IND1,AIND1), atom_concat('A[',AIND1,A4), atom_concat(A4,']',A5), atom_concat(A5,Args,A6),
     (
      HB<H -> plan_parallel_chain(A3,A6); plan_parallel_reverse(A3,A6)
     ),
     write(' ').
   @try_link(_,_,_,_,_,_):-!.

   @make_links(I,N):-
     append(L,[H|R],I),
     HM is H-1,
     HP is H+1,
     try_link(L,H,HM,R,I,N), try_link(L,H,HP,R,I,N),
     fail.
   @make_links(_,_):-!.

   @hyper(0,I,_,N):-!, make_links(I,N), !.
   @hyper(_,_,0,_):-!.
   @hyper(DIM,INDS,I,N):-
     append(INDS,[I],NEXTINDS),
     DIM1 is DIM-1,
     hyper(DIM1,NEXTINDS,N,N),
     I1 is I-1,
     hyper(DIM,INDS,I1,N).

   @goal:-hyper(NDims,[],NN,NN).
};

int main() {
  const int Dims = 3;
  const int N = 3;

  hypercube(Dims, N, '(empty_proc,Dims,N,0)');

  return 0;
}