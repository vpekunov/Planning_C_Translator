// Debugged

#include <iostream>

using namespace std;

int Sum_i_1_N(int N) {
  return (N*N+N)>>1;
}

int M;

volatile int Counter = 0;

chain A(bool init, input_proc Src, int N, int K, int last) {
  int id = plan_linear_num();

  if (init) {
     if (id == 1)
        for (int i = 1; i <= N; i++)
            throw_first(false, A[2+Sum_i_1_N(i-1)], N, 17, i+1+Sum_i_1_N(i-1));
  } else {
     if (id == last) {
        plan_critical(A_out) {
          cout<<K<<endl;
          Counter++;
          if (Counter == N)
             plan_topology_quit();
        }
     } else
        throw_first(false, A[id+1], N, K, last);
  }
}

#def_module(plan_topology) margo(N) { /* Ромашка */
   @sum_i_1_N(NN, Result) :- Result is round((NN*NN+NN)/2).
   /* Соединения с центральным узлом */
   @make_central(0):-!.
   @make_central(I) :-
     I1 is I-1,
     sum_i_1_N(I1,N1), N2 is N1+2,
     number_atom(N2,IND),
     atom_concat('A[',IND,A1), atom_concat(A1,'](true,empty_proc,N,0,0)',A2),
     plan_parallel_chain('A[1](true,empty_proc,N,0,0)',A2),
     make_central(I1).
   /*
   <i = 1, N>
      plan_parallel_chain(A[1](true,NULL,N,0,0)->A[2+Sum_i_1_N(i-1)](true,NULL,N,0,0));
   */
   @make_petal(_, 1):-!.
   @make_petal(I, J) :-
     I1 is I-1,
     sum_i_1_N(I1,NN), N1 is NN+J, N2 is NN+J+1,
     number_atom(N1,IND1),
     atom_concat('A[',IND1,A1), atom_concat(A1,'](true,empty_proc,N,0,0)',A2),
     number_atom(N2,IND2),
     atom_concat('A[',IND2,A3), atom_concat(A3,'](true,empty_proc,N,0,0)',A4),
     plan_parallel_chain(A2,A4),
     J1 is J-1,
     make_petal(I, J1).
   @loop_petals(0):-!.
   @loop_petals(I) :-
     make_petal(I, I),
     I1 is I-1,
     loop_petals(I1).
   /*
   <i = 1, N>
      <j = 2, i>
         plan_parallel_chain(A[j+Sum_i_1_N(i-1)](true,NULL,N,0,0)->A[j+1+Sum_i_1_N(i-1)](true,NULL,N,0,0));
   */
   @goal :- make_central(N), loop_petals(N).
};

int main() {
  // 2 3--4
  // |/
  // 1--5--6--7
  // |\
  // | 8--9--10--11
  // |
  // +--12--13--14--15--16

  const int N = 5;

  M = 1 + Sum_i_1_N(N);

  margo(N)/M;

  return 0;
}