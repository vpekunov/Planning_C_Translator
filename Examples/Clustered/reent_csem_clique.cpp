// Debugged

#pragma plan clustered

#include <iostream>>

using namespace std;

cvar(int) * DATA = NULL;

plan_csem_t SEM = NULL;

int Counter;

chain A(input_proc Src, int N) {
  int id = plan_linear_num()-1;

  if (Src == empty_proc) {
     plan_csem_wait(&SEM);
     *DATA = **DATA + 1;
     plan_csem_release(&SEM);
     Counter = 1;

     for (int i = 0; i < N; i++)
         if (i != id)
            throw_first(A[i+1], N);
  } else {
     plan_csem_wait(&SEM);
     *DATA = **DATA + 1;
     plan_csem_release(&SEM);
     Counter++;
     if (Counter == N) {
        plan_registered_barrier(topology);
        if (id == N-1) {
           cout<<**DATA<<endl;
           plan_topology_quit();
        }
     }
  }
}

#def_module(plan_topology) clique(N) {
  /*
  <i = 1,N>
     <j = 1,i-1>
        plan_parallel_chain(A[i](NULL,N)->A[j](NULL,N));
  <i = 1,N>
     <j = i+1,N>
        plan_parallel_chain(A[i](NULL,N)->A[j](NULL,N));
  */
  @inner_loop(_,0):-!.
  @inner_loop(I,J) :-
    (I==J ->
      true;
      (
       number_atom(I,IND1),
       atom_concat('A[',IND1,B1), atom_concat(B1,'](empty_proc,N)',B2),
       number_atom(J,IND2),
       atom_concat('A[',IND2,B3), atom_concat(B3,'](empty_proc,N)',B4),
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

  DATA = new cvar(int)(1);
  if (plan_cluster_id() == 0)
     *DATA = 0;

  plan_csem_init(&SEM, 1);

  int IDS[N];
  for (int i = 0; i < N; i++)
      IDS[i] = i;
  clustered(IDS) clique(N)/N;

  plan_csem_destroy(&SEM);
  delete DATA;

  return 0;
}