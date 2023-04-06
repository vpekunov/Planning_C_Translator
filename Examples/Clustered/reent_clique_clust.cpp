#pragma plan clustered

#include <iostream>>

using namespace std;

int * DATA;
int Counter;

chain A(input_proc Src, int N, int K) {
  int id = plan_linear_num()-1;

  if (K == 0) {
     DATA = new int [N];
     DATA[id] = id + 2;
     Counter = 1;

     for (int i = 0; i < N; i++)
         if (i != id)
            throw_first(A[i+1], N, id + 2);
  } else {
     DATA[input_index(Src)-1] = K;
     Counter++;
     if (Counter == N) {
        for (int i = 0; i < N; i++)
            cout<<DATA[i]<<" ";
        cout<<endl;
        plan_registered_barrier(topology);
        if (id == N-1) {
           // Sleep(2000);
           plan_topology_quit();
        }
     }
  }
}

#def_module(plan_topology) clique(N) {
  /*
  <i = 1,N>
     <j = 1,i-1>
        plan_parallel_chain(A[i](NULL,N,0)->A[j](NULL,N,0));
  <i = 1,N>
     <j = i+1,N>
        plan_parallel_chain(A[i](NULL,N,0)->A[j](NULL,N,0));
  */
  @inner_loop(_,0):-!.
  @inner_loop(I,J) :-
    (==(I,J) ->
      true;
      (
       number_atom(I,IND1),
       atom_concat('A[',IND1,B1), atom_concat(B1,'](empty_proc,N,0)',B2),
       number_atom(J,IND2),
       atom_concat('A[',IND2,B3), atom_concat(B3,'](empty_proc,N,0)',B4),
       (I<J ->
        plan_parallel_chain(B2,B4);
        plan_parallel_reverse(B2,B4)
       ),
       plan_parallel_reverse(B4,B2)
      )
    ),
    J1 is J-1,
    inner_loop(I,J1).
  @outer_loop(0):-!.
  @outer_loop(I) :-
    inner_loop(I, N),
    I1 is I-1,
    outer_loop(I1).
  @goal :- outer_loop(N).
};

int main() {
  const int N = 5;

  int IDS[N];
  for (int i = 0; i < N; i++)
      IDS[i] = i;
  clustered(IDS) clique(N)/N;

  return 0;
}