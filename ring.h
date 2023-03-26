#ifndef __RING_H__
#define __RING_H__

#preproc_passes(2)

#add_scan(topoRing)

#include <functional>
#include <iostream>

using namespace std;

#def_module() __ring_defs() {
@goal:-brackets_off.
@make_ring_def(ID, NP, DT, INIT, BODY):-
  write('typedef std::function<void(const '), write(DT), write(' data)> ring_sender_'), write(ID), write(';'), nl,
  write('typedef std::function<void(int id, ring_sender_'), write(ID), write(' send, const '), write(DT), write(' data)> ring_function_'), write(ID), write(';'), nl,
  write('chain ring_'), write(ID), write('(bool init, int NN, input_proc in, ring_function_'), write(ID), write(' worker, const '), write(DT), write(' data) {'), nl,
  write('    ring_sender_'), write(ID), write(' send = [&] (const '), write(DT), write(' data) {'), nl,
  write('         if (plan_linear_num() < NN)'), nl,
  write('            throw_last(false, NN, ring_'), write(ID), write('[plan_linear_num()+1], worker, data);'), nl,
  write('         else'), nl,
  write('            throw_last(false, NN, ring_'), write(ID), write('[1], worker, data);'), nl,
  write('    };'), nl,
  write('    if (plan_linear_num() == 1) {'), nl,
  write('       worker(0, send, data);'), nl,
  write('       if (!init) plan_topology_quit();'), nl,
  write('    } else if (!init)'), nl,
  write('       worker(input_index(in), send, data);'), nl,
  write('}'), nl.
@insert_ring_defs:-
  predicate_property(ring_def(_,_,_,_,_),'dynamic'),
  ring_def(ID, NP, DT, INIT, BODY),
  make_ring_def(ID, NP, DT, INIT, BODY),
  fail.
@insert_ring_defs:-!.
@goal:-insert_ring_defs.
};

__ring_defs()

#def_pattern topoRing => __make_ring (gid(), /root/NP/@Value, /root/DT/@Value, /root/INIT/@Value, /root/BODY/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ring
    (\s|\\t)*
    \<
    (\s|\\t)*
    (\w+)->{DT}
    (\s|\\t)*
    \>
    (\s|\\t)*
    \(
    (\s|\\t)*
    (\w+)->{NP}
    (\s|\\t)*
    \,
    (\s|\\t)*
    (\w+)->{INIT}
    (\s|\\t)*
    \)
    (\s|\\t)*
    \{
     ((.{1,8192})->{BODY}\})?=>{Predicates.BAL($,'}')}
    (\s|\\t)*
  @end
};

#def_module() __make_ring(ID, NP, DT, INIT, BODY) {
@goal:-brackets_off.
@goal:-assertz(ring_def(ID, NP, DT, INIT, BODY)).
@make_ring_body:-
    write('ring_function_'), write(ID), write(' worker_'), write(ID), write(' = [&] (int id, ring_sender_'), write(ID), write(' send, const '), write(DT), write(' data) {'), nl,
    write(BODY), nl,
    write('};'), nl.
@write_chain(1, _, _):-
    !.
@write_chain(NN, ID, INIT):-
    NN1 is NN-1,
    write_chain(NN1, ID, INIT),
    write('  plan_parallel_chain(ring_'), write(ID), write('['), write(NN1), write('](true, '), write(NP), write(', empty_proc, worker_'), write(ID), write(', '), write(INIT), write(')->'),
    write('ring_'), write(ID), write('['), write(NN), write('](true, '), write(NP), write(', empty_proc, worker_'), write(ID), write(', '), write(INIT), write('));'),
    nl.
@make_ring_call:-
    write('plan_topology {'), nl,
    number_atom(NN, NP),
    write_chain(NN, ID, INIT),
    write('  plan_parallel_reverse(ring_'), write(ID), write('['), write(NP), write('](true, '), write(NP), write(', empty_proc, worker_'), write(ID), write(', '), write(INIT), write(')->'),
    write('ring_'), write(ID), write('[1](true, '), write(NP), write(', empty_proc, worker_'), write(ID), write(', '), write(INIT), write('));'),
    nl,
    write('}/'), write(NP), write(';'), nl.
@goal:-make_ring_body, make_ring_call, !.
};

#endif
