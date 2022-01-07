// Debugged

#include <iostream>

using namespace std;

chain A(bool init, input_proc Src, int N, int K) throw(bool init, input_proc Src, int N, int K) {
  if (init) {
     if (plan_linear_num() == 1)
        throw_first(false, A[plan_linear_num()+1], N, 9);
  } else {
     if (input_index(Src) < plan_linear_num()) {
        if (plan_linear_num() < N) {
           throw_first(false, A[plan_linear_num()+1], N, K);
        } else
           throw_first(false, A[plan_linear_num()-1], N, K);
     } else {
        if (plan_linear_num() == 1) {
           cout<<K<<endl;
           plan_topology_quit();
        } else
           throw_first(false, A[plan_linear_num()-1], N, K);
     }
  }
}


/* На векторе + ленивые переменные. */
funnel(out, int) ** ToRight;
funnel(in, int) ** FromRight;
funnel(out, int) ** ToLeft;
funnel(in, int) ** FromLeft;

chain A1(int N) {
  int K;

  if (throw_stage() == 0)
     K = 9;
  else
     K = **FromLeft[throw_stage()];
  if (throw_stage() < N-1) {
     *ToRight[throw_stage()] = K;
     K = **FromRight[throw_stage()];
  }
  if (throw_stage() > 0)
     *ToLeft[throw_stage()] = K;
  else
     cout<<K<<endl;  
}

#def_module(plan_topology) tube(N) { /* Топология "труба". Например, A[N]+A'[N] */
  /*
  plan_parallel_chain(A[1:N](true,NULL,N,0)->);
  plan_parallel_chain(A[1:N](true,NULL,N,0)<-);
  */
  @body(NN) :-
    N1 is NN-1,
    for(I, 1, N1),
      number_atom(I, IND1),
      atom_concat('A[',IND1,A1), atom_concat(A1,'](true,empty_proc,N,0)',A2),
      I1 is I+1,
      number_atom(I1, IND2),
      atom_concat('A[',IND2,A3), atom_concat(A3,'](true,empty_proc,N,0)',A4),
      plan_parallel_chain(A2,A4),
      plan_parallel_reverse(A4,A2),
    fail.
  @body(_):-!.
  @goal :- body(N).
};

int main() {
  const int N = 5;

  tube(N)/N;

  ToRight = new funnel(out, int) * [N];
  FromRight = new funnel(in, int) * [N];
  ToLeft = new funnel(out, int) * [N];
  FromLeft = new funnel(in, int) * [N];

  for (int i = 0; i < N; i++) {
      if (i < N-1) {
         FromRight[i] = new funnel(in, int)();
         ToRight[i] = new funnel(out, int)();
      }
      if (i > 0) {
         FromLeft[i] = new funnel(in, int)(ToRight[i-1]);
         ToLeft[i] = new funnel(out, int)(FromRight[i-1]);
      }
  }

  plan_parallel_chain(1, N, A1(N));

  return 0;
}