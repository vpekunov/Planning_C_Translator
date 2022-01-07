#ifndef __STDTOPO_H__
#define __STDTOPO_H__

#include "reentera.h"
#include <math.h>

#add_scan(scan_stdtopo)

#include <functional>
#include <iostream>

using namespace std;

#def_pattern scan_stdtopo => make_std_topo (gid(), /root/Name/@Value, /root/TParams/@Value, //ParamType/@Value, //ParamName/@Value, /root/FUN/@Value, /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    auto
    (\s|\\n|\\t)+
    (\w+)->{FUN}
    (\s|\\n|\\t)*
    \=
    (\s|\\n|\\t)*
    topology
    (\s|\\n|\\t)*
    (\w+)->{Name}
    (\s|\\n|\\t)*
    \[
      ((.{1,1024})->{TParams}\])?=>{Predicates.BAL($,']')}
    (\s|\\n|\\t)*
    \<
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\,))?=>{Predicates.TBAL($,',')})*
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\>))?=>{Predicates.TBAL($,'>')})
    (\s|\\n|\\t)*
    \{
     ((.{1,8192})->{Body}\})?=>{Predicates.BAL($,'}')}
    (\s|\\t)*
    \;
    (\s|\\t)*
  @end
};

#def_module() make_std_topo(ID, NAME, TParams, ParamTypes, ParamNames, FUN, BODY) {
@goal:-brackets_off.
@goal:-
    (
     g_read('$cdefined$', CDEFS),
     (
      member(def(ID, _, _, _, _, _, _), CDEFS)->
       true;
       (
        (
         (
          g_read('$fdefined$', [fun(GID, _, _)|_])->
            true;
            =(GID,10000)
         ),
         (
          ( predicate_property(cfuns(_,_),'dynamic'), cfuns(GID, LAMBDAS) )->
            (
              retractall(cfuns(GID, _)),
              asserta(cfuns(GID, [ID|LAMBDAS]))
            );
            asserta(cfuns(GID, [ID]))
         )
        ),
        g_assign('$cdefined$', [def(ID, ID, ParamTypes, ParamNames, FUN, ParamTypes, ParamNames)|CDEFS])
       )
     )
    ).
@make_params4([Type], [Name], Params, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Params),
    !.
@make_params4([Type|T1], [Name|T2], Params, Names):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params4(T1, T2, P4, NM),
    !,
    atom_concat(P3, P4, Params),
    atom_concat(Name, ', ', NM1),
    atom_concat(NM1, NM, Names),
    !.
@make_params4(Type, Name, Param, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@lsubstitute([], _, _, []):-
    !.
@lsubstitute(A, F, T, A1):-
    append(F, REST, A),
    !,
    lsubstitute(REST, F, T, REST1),
    !,
    append(T, REST1, A1),
    !.
@lsubstitute([H|TAG], F, T, [H|TAG1]):-
    lsubstitute(TAG, F, T, TAG1),
    !.
@substitute(BODY, FROM, TO, BODY1):-
    atom_chars(BODY, LB),
    atom_chars(FROM, F),
    atom_chars(TO, T),
    lsubstitute(LB, F, T, LB1),
    atom_chars(BODY1, LB1),
    !.
@make_std_body(Name):-
    make_params4(ParamTypes, ParamNames, Params, Names),
    !,
    write('worker_'), write(ID),
    write(' = [&] (reentera_pf_'), write(ID), write(' reent_first, reentera_pf_'), write(ID),
    write(' reent_last, reentera_sa_'), write(ID),
    write(' _reent_group_soft_atomize, reentera_gf_'), write(ID),
    write(' _reent_group_first, reentera_gl_'), write(ID),
    write(' _reent_group_last, reentera_gp_'), write(ID),
    write(' _reent_group_parallelize, reentera_cp_'), write(ID),
    write(' _clear_reent, reentera_pi_'), write(ID),
    write(' _reent_processor_id, reentera_pp_'), write(ID),
    write(' _reent_processors, reentera_tf_'), write(ID),
    write(' reent_next_first, reentera_tl_'), write(ID),
    write(' reent_next_last, reentera_ts_'), write(ID),
    write(' reent_stage, reentera_tn_'), write(ID),
    write(' reent_num_stages, '),
    write(' reentera_pln_'), write(ID), write(' reent_linear_num, '),
    write(' reentera_ptn_'), write(ID), write(' reent_topology_num, '),
    write(' reentera_ptq_'), write(ID), write(' reent_topology_quit, '),
    write(' reentera_pnb_'), write(ID), write(' reent_neighbours, '),
    write(Params), write(') {'), nl,
    write_defs(Name),
    atom_concat('chain_', ID, REF0),
    atom_concat(REF0, '[', REF),
    substitute(BODY, 'this[', REF, BODY1),
    write(BODY1), nl,
    write('};'), nl,
    write('auto '), write(FUN), write(' = [&] ('), write(Params), write(')'),
    write('{'), nl,
    write('   '), write(Name), write('('), write(TParams), write(', ''chain_'), write(ID), write(''', ''(worker_'), write(ID), write(','), write(Names), write(')'');'), nl,
    write('};'),
    nl.
@write_defs('hypercube'):-
    write('int __nn__, __dims__;'), nl,
    write('input_proc __outcoming__[128];'), nl,
    write('reent_neighbours(false, chain_'), write(ID), write('[1], &__dims__, __outcoming__);'), nl,
    write('__nn__ = (int)(0.5 + pow(1.0*reent_num_stages(), 1.0/__dims__));'), nl,
    write('auto get_idxs = [&] (int idx)->vector<int> * {'), nl,
    write('  vector<int> * result = new vector<int>(__dims__,0);'), nl,
    write('  for (int i = 0; i < __dims__; i++) {'), nl,
    write('      int k = idx % __nn__;'), nl,
    write('      (*result)[__dims__-1-i] = k;'), nl,
    write('      idx = (idx - k)/__nn__;'), nl,
    write('  }'), nl,
    write('  return result;'), nl,
    write('};'), nl,
    write('auto get_idx = [&] (vector<int> * idxs)->int {'), nl,
    write('  int result = 0;'), nl,
    write('  for (int i = 0; i < __dims__; i++)'), nl,
    write('      result = result*__nn__ + (*idxs)[i];'), nl,
    write('  return result;'), nl,
    write('};'), nl,
    !.
@write_defs('clique'):-
    write('auto num_others = [&] () {'), nl,
    write(' return reent_num_stages() - 1;'), nl,
    write('};'), nl,
    write('auto other = [&] (int i) {'), nl,
    write(' int id = reent_linear_num();'), nl,
    write(' return i < id-1 ? i+1 : i + 2;'), nl,
    write('};'), nl,
    !.
@write_defs('ring'):-
    write('auto forw = [&] () {'), nl,
    write(' return 1 + reent_linear_num() % reent_num_stages();'), nl,
    write('};'), nl,
    write('auto back = [&] () {'), nl,
    write(' int n = reent_num_stages();'), nl,
    write(' return 1 + (reent_linear_num() + n - 2) % n;'), nl,
    write('};'), nl,
    !.
@write_defs('tube'):-
    write('auto forw = [&] () {'), nl,
    write(' int n = reent_num_stages();'), nl,
    write(' int id = reent_linear_num();'), nl,
    write(' return id == n ? -1 : (1 + id % n);'), nl,
    write('};'), nl,
    write('auto back = [&] () {'), nl,
    write(' int n = reent_num_stages();'), nl,
    write(' int id = reent_linear_num();'), nl,
    write(' return id == 1 ? -1 : (1 + (id + n - 2) % n);'), nl,
    write('};'), nl,
    !.
@write_defs('pyramide'):-
    write('auto forw = [&] () {'), nl,
    write(' return 2 + (reent_linear_num() - 1) % (reent_num_stages() - 1);'), nl,
    write('};'), nl,
    write('auto back = [&] () {'), nl,
    write(' int n = reent_num_stages();'), nl,
    write(' return 2 + (reent_linear_num() + n - 2) % (n - 1);'), nl,
    write('};'), nl,
    write('auto num_slaves = [&] () {'), nl,
    write(' return reent_num_stages() - 1;'), nl,
    write('};'), nl,
    write('auto slave = [&] (int i) {'), nl,
    write(' return i + 2;'), nl,
    write('};'), nl,
    write('auto master = [&] () {'), nl,
    write(' return 1;'), nl,
    write('};'), nl,
    !.
@write_defs('star'):-
    write('auto num_slaves = [&] () {'), nl,
    write(' return reent_num_stages() - 1;'), nl,
    write('};'), nl,
    write('auto slave = [&] (int i) {'), nl,
    write(' return i + 2;'), nl,
    write('};'), nl,
    write('auto master = [&] () {'), nl,
    write(' return 1;'), nl,
    write('};'), nl,
    !.
@goal:-make_std_body(NAME), !.
};

#def_module(plan_topology) hypercube(NDims,NN,Proc,Args) {
   /* Можно все положительные направления сделать прямыми линками, а отрицательные -- реверсивными */
   @getidx(_,[],_,1):-!.
   @getidx(N,[H|T],Mul,IND):-Mul1 is Mul*N, getidx(N,T,Mul1,IBase), IND is IBase+(H-1)*Mul.

   @try_link(L,HB,H,R,I,N):-
     H>0, N1 is N+1, H<N1, !,
     append(L,[H|R],I1),
     getidx(N,I,1,IND),
     number_atom(IND,AIND), atom_concat(Proc,'[',AA1), atom_concat(AA1,AIND,A1), atom_concat(A1,']',A2), atom_concat(A2,Args,A3),
     getidx(N,I1,1,IND1),
     number_atom(IND1,AIND1), atom_concat(AA1,AIND1,A4), atom_concat(A4,']',A5), atom_concat(A5,Args,A6),
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

#def_module(plan_topology) clique(NN, Proc, Args) {
  /*
  <i = 1,N>
     <j = 1,i-1>
        plan_parallel_chain(A[i]()->A[j]());
  <i = 1,N>
     <j = i+1,N>
        plan_parallel_chain(A[i]()->A[j]());
  */
  @inner_loop(_,0,_):-!.
  @inner_loop(I,J,N) :-
    (I==J ->
      true;
      (
       number_atom(I,IND1),
       atom_concat(Proc,'[',A),
       atom_concat(A,IND1,B1), atom_concat(B1,']',BB2), atom_concat(BB2, Args, B2),
       number_atom(J,IND2),
       atom_concat(A,IND2,B3), atom_concat(B3,']',BB4), atom_concat(BB4, Args, B4),
       (I<J ->
        plan_parallel_chain(B2,B4);
        plan_parallel_reverse(B2,B4)
       ),
       plan_parallel_reverse(B4,B2)
      )
    ),
    J1 is J-1,
    inner_loop(I,J1,N).
  @outer_loop(0,_):-!.
  @outer_loop(I,N) :-
    inner_loop(I, N, N),
    I1 is I-1,
    outer_loop(I1,N).
  @goal :- outer_loop(NN, NN).
};

#def_module(plan_topology) ring(N, Proc, Args) {
@write_chain(1):-
    !.
@write_chain(NN):-
    NN1 is NN-1,
    write_chain(NN1),
    write('  plan_parallel_chain('), write(Proc), write('['), write(NN1), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN), write(']'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(NN), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN1), write(']'), write(Args), write(');'),
    nl.
@goal:-
    write_chain(N),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(N), write(']'), write(Args), write('->'),
    write(Proc), write('[1]'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('[1]'), write(Args), write('->'),
    write(Proc), write('['), write(N), write(']'), write(Args), write(');'),
    nl.
};

#def_module(plan_topology) tube(N, Proc, Args) {
@write_chaint(1):-
    !.
@write_chaint(NN):-
    NN1 is NN-1,
    write_chaint(NN1),
    write('  plan_parallel_chain('), write(Proc), write('['), write(NN1), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN), write(']'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(NN), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN1), write(']'), write(Args), write(');'),
    nl.
@goal:-
    write_chaint(N),
    nl.
};

#def_module(plan_topology) pyramide(N, Proc, Args) {
@write_chainp(2):-
    !.
@write_chainp(NN):-
    NN1 is NN-1,
    write_chainp(NN1),
    write('  plan_parallel_chain('), write(Proc), write('['), write(NN1), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN), write(']'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(NN), write(']'), write(Args), write('->'),
    write(Proc), write('['), write(NN1), write(']'), write(Args), write(');'),
    write('  plan_parallel_chain('), write(Proc), write('[1]'), write(Args), write('->'),
    write(Proc), write('['), write(NN), write(']'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(NN), write(']'), write(Args), write('->'),
    write(Proc), write('[1]'), write(Args), write(');'),
    nl.
@goal:-
    write_chainp(N),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(N), write(']'), write(Args), write('->'),
    write(Proc), write('[2]'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('[2]'), write(Args), write('->'),
    write(Proc), write('['), write(N), write(']'), write(Args), write(');'),
    write('  plan_parallel_chain('), write(Proc), write('[1]'), write(Args), write('->'),
    write(Proc), write('[2]'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('[2]'), write(Args), write('->'),
    write(Proc), write('[1]'), write(Args), write(');'),
    nl.
};

#def_module(plan_topology) star(N, Proc, Args) {
@write_chains(1):-
    !.
@write_chains(NN):-
    NN1 is NN-1,
    write_chains(NN1),
    write('  plan_parallel_chain('), write(Proc), write('[1]'), write(Args), write('->'),
    write(Proc), write('['), write(NN), write(']'), write(Args), write(');'),
    write('  plan_parallel_reverse('), write(Proc), write('['), write(NN), write(']'), write(Args), write('->'),
    write(Proc), write('[1]'), write(Args), write(');'),
    nl.
@goal:-
    write_chains(N),
    !.
};

#endif
