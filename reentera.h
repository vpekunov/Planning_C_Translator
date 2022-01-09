// Из-за малопонятной ошибки в GNU PROLOG пришлось переименовать:
// plan_* => reent_*
// plan_* => reent_*
// throw_first => reent_next_first
// throw_last => reent_next_last
// throw_* => reent_*

#ifndef __REENTERA_H__
#define __REENTERA_H__

#preproc_passes(2)

#add_scan(scan_fdefs, scan_reentera, scan_freentera, scan_simple_chain, scan_complex_chain, scan_general_topo)

#include <functional>
#include <iostream>

using namespace std;

#define reent_group_soft_atomize _reent_group_soft_atomize()
#define reent_group_first _reent_group_first()
#define reent_group_last _reent_group_last()
#define reent_group_parallelize _reent_group_parallelize()
#define clear_reent _clear_reent()
#define reent_processor_id _reent_processor_id
#define reent_processors _reent_processors

#def_pattern scan_fdefs => make_fdef (gid(), //ID/@Value, //HEAD/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (
     (\s|\\t)*
     ((([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{RETTYPE}(\w+(\\n|\s|\\t)*)->{ID}\(
          (
           (((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+
             (
              ((\\n|\s|\\t)*(\&|(\*)+)->{FIRST_REF}
              )|
              (\\n|\s|\\t)+()->{FIRST_REF}
             )
             (\\n|\s|\\t)*(\w+)->{FIRST}(((\\n|\s|\\t)*\[(\\n|\s|\\t)*\w+(\\n|\s|\\t)*\])*)->{FIRST_IDXS}
             ((\\n|\s|\\t)*\,((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+
              (
               ((\\n|\s|\\t)*(\&|(\*)+)->{OTHER_REF}
               )|
               (\\n|\s|\\t)+()->{OTHER_REF}
              )
              (\\n|\s|\\t)*(\w+)->{OTHER}(((\\n|\s|\\t)*\[(\\n|\s|\\t)*\w+(\\n|\s|\\t)*\])*)->{OTHER_IDXS}(\\n|\s|\\t)*
             )->{TAIL}*
             (
              (\\n|\s|\\t)*\,(\\n|\s|\\t)*(\.\.\.)->{THREEP}(\\n|\s|\\t)*
             )?
           )|
           ((\\n|\s|\\t)*(\.\.\.)->{THREEP}(\\n|\s|\\t)*)|
           (((\\n|\s|\\t)*void(\\n|\s|\\t)*)|((\\n|\s|\\t)*)->{EMPTY})
          )->{ARGS}\)(\s|\\t|\\n)*)
     (\s|\\t)*
    )->{HEAD}
  @end
  (\{|\;)
};

#def_module() make_fdef(GID, NAME, HEAD) {
@goal:-brackets_off.
@make_params([Type], [Name], Params, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Params),
    !.
@make_params([Type|T1], [Name|T2], Params, Names):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params(T1, T2, P4, NM),
    !,
    atom_concat(P3, P4, Params),
    atom_concat(Name, ', ', NM1),
    atom_concat(NM1, NM, Names),
    !.
@make_params(Type, Name, Param, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@make_reentera_def(ID, ParamTypes, ParamNames, spec(_, RetType)):-
  once(make_params(ParamTypes, ParamNames, Params, Names)),
  write('typedef std::function<int(void)> reentera_sa_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gf_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gl_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gp_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_cp_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_pi_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_pp_'), write(ID), write(';'), nl,
  write('typedef std::function<int('), write(Params), write(')> reentera_pf_'), write(ID), write(';'), nl,
  write('typedef std::function<int('), write(Params), write(')> reentera_pl_'), write(ID), write(';'), nl,
  write('typedef std::function<'),
  (
   =(RetType, '')-> write('void') ; write(RetType)
  ),
  write('(reentera_pf_'), write(ID), write(' reent_pf, reentera_pl_'), write(ID),
  write(' reent_pl, reentera_sa_'), write(ID), write(' reent_sa, reentera_gf_'), write(ID),
  write(' reent_gf, reentera_gl_'), write(ID), write(' reent_gl, reentera_gp_'), write(ID), write(' reent_gp, '),
  write(' reentera_cp_'), write(ID), write(' reent_cp, reentera_pi_'), write(ID), write(' reent_pi, '),
  write(' reentera_pp_'), write(ID), write(' reent_pp, '),
  write(Params), write(')> reentera_function_'), write(ID), write(';'), nl,
  write('reenterable '),
  write(RetType),
  write(' reentera_'), write(ID), write('(reentera_function_'), write(ID), write(' worker, '), write(Params), write(') {'), nl,
  write('    auto reent_sa = [&] ()->int {'), nl,
  write('      return plan_group_soft_atomize;'), nl,
  write('    };'), nl,
  write('    auto reent_pf = [&] ('), write(Params), write(')->int {'), nl,
  write('      return plan_first'), write('(worker, '), write(Names), write(');'), nl,
  write('    };'), nl,
  write('    auto reent_pl = [&] ('), write(Params), write(')->int {'), nl,
  write('      return plan_last'), write('(worker, '), write(Names), write(');'), nl,
  write('    };'), nl,
  write('    auto reent_gf = [&] ()->int {'), nl,
  write('      return plan_group_first;'), nl,
  write('    };'), nl,
  write('    auto reent_gl = [&] ()->int {'), nl,
  write('      return plan_group_last;'), nl,
  write('    };'), nl,
  write('    auto reent_gp = [&] ()->int {'), nl,
  write('      return plan_group_parallelize;'), nl,
  write('    };'), nl,
  write('    auto reent_cp = [&] ()->int {'), nl,
  write('      return clear_plan;'), nl,
  write('    };'), nl,
  write('    auto reent_pi = [&] ()->int {'), nl,
  write('      return plan_processor_id();'), nl,
  write('    };'), nl,
  write('    auto reent_pp = [&] ()->int {'), nl,
  write('      return plan_processors();'), nl,
  write('    };'), nl,
  (
   =(RetType, '') -> true ; write('return')
  ),
  write('    worker(reent_pf, reent_pl, reent_sa, reent_gf, reent_gl, reent_gp, reent_cp, reent_pi, reent_pp, '), write(Names), write(');'), nl,
  write('}'), nl.
@make_chain_def(ID, ID2, ParamTypes, ParamNames, ThrowTypes, ThrowNames):-
  once(make_params(ParamTypes, ParamNames, Params, Names)),
  once(make_params(ThrowTypes, ThrowNames, Throws, TNames)),
  write('typedef std::function<int(void)> reentera_sa_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gf_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gl_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_gp_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_cp_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_pi_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_pp_'), write(ID), write(';'), nl,
  write('typedef std::function<void('), write(Throws), write(')> reentera_tf_'), write(ID), write(';'), nl,
  write('typedef std::function<void('), write(Throws), write(')> reentera_tl_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_ts_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_tn_'), write(ID), write(';'), nl,
  write('typedef std::function<int('), write(Params), write(')> reentera_pf_'), write(ID), write(';'), nl,
  write('typedef std::function<int('), write(Params), write(')> reentera_pl_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_pln_'), write(ID), write(';'), nl,
  write('typedef std::function<int(void)> reentera_ptn_'), write(ID), write(';'), nl,
  write('typedef std::function<void(void)> reentera_ptq_'), write(ID), write(';'), nl,
  write('typedef std::function<void(bool, input_proc, int *, input_proc *)> reentera_pnb_'), write(ID), write(';'), nl,
  write('typedef std::function<void(reentera_pf_'), write(ID), write(' reent_pf, reentera_pl_'), write(ID),
  write(' reent_pl, reentera_sa_'), write(ID), write(' reent_sa, reentera_gf_'), write(ID),
  write(' reent_gf, reentera_gl_'), write(ID), write(' reent_gl, reentera_gp_'), write(ID), write(' reent_gp, '),
  write(' reentera_cp_'), write(ID), write(' reent_cp, reentera_pi_'), write(ID), write(' reent_pi, '),
  write(' reentera_pp_'), write(ID), write(' reent_pp, reentera_tf_'), write(ID), write(' reent_tf, '),
  write(' reentera_tl_'), write(ID), write(' reent_tl, reentera_ts_'), write(ID), write(' reent_ts, '),
  write(' reentera_tn_'), write(ID), write(' reent_tn, '),
  write(' reentera_pln_'), write(ID), write(' reent_pln, '),
  write(' reentera_ptn_'), write(ID), write(' reent_ptn, '),
  write(' reentera_ptq_'), write(ID), write(' reent_ptq, '),
  write(' reentera_pnb_'), write(ID), write(' reent_pnb, '),
  write(Params), write(')> reentera_function_'), write(ID), write(';'), nl,
  write('reentera_function_'), write(ID), write(' worker_'), write(ID), write(';'), nl,
  write('typedef std::function<void(reentera_pf_'), write(ID), write(' reent_pf, reentera_pl_'), write(ID),
  write(' reent_pl, reentera_sa_'), write(ID), write(' reent_sa, reentera_gf_'), write(ID),
  write(' reent_gf, reentera_gl_'), write(ID), write(' reent_gl, reentera_gp_'), write(ID), write(' reent_gp, '),
  write(' reentera_cp_'), write(ID), write(' reent_cp, reentera_pi_'), write(ID), write(' reent_pi, '),
  write(' reentera_pp_'), write(ID), write(' reent_pp, reentera_tf_'), write(ID), write(' reent_tf, '),
  write(' reentera_tl_'), write(ID), write(' reent_tl, reentera_ts_'), write(ID), write(' reent_ts, '),
  write(' reentera_tn_'), write(ID), write(' reent_tn, '),
  write(' reentera_pln_'), write(ID), write(' reent_pln, '),
  write(' reentera_ptn_'), write(ID), write(' reent_ptn, '),
  write(' reentera_ptq_'), write(ID), write(' reent_ptq, '),
  write(' reentera_pnb_'), write(ID), write(' reent_pnb, '),
  write(Throws), write(')> reentera_function_n'), write(ID), write(';'), nl,
  write('chain chain_'), write(ID), write('(reentera_function_'), write(ID), write(' worker, '), write(Params), write(')'),
  (
   =(Throws, Params)->
    true;
    (write(' throw(reentera_function_'), write(ID2), write(' worker, '), write(Throws), write(')'))
  ),
  write(' {'), nl,
  write('    auto reent_sa = [&] ()->int {'), nl,
  write('      return plan_group_soft_atomize;'), nl,
  write('    };'), nl,
  write('    auto reent_pf = [&] ('), write(Params), write(')->int {'), nl,
  write('      return plan_first'), write('(worker, '), write(Names), write(');'), nl,
  write('    };'), nl,
  write('    auto reent_pl = [&] ('), write(Params), write(')->int {'), nl,
  write('      return plan_last'), write('(worker, '), write(Names), write(');'), nl,
  write('    };'), nl,
  write('    auto reent_gf = [&] ()->int {'), nl,
  write('      return plan_group_first;'), nl,
  write('    };'), nl,
  write('    auto reent_gl = [&] ()->int {'), nl,
  write('      return plan_group_last;'), nl,
  write('    };'), nl,
  write('    auto reent_gp = [&] ()->int {'), nl,
  write('      return plan_group_parallelize;'), nl,
  write('    };'), nl,
  write('    auto reent_cp = [&] ()->int {'), nl,
  write('      return clear_plan;'), nl,
  write('    };'), nl,
  write('    auto reent_pi = [&] ()->int {'), nl,
  write('      return plan_processor_id();'), nl,
  write('    };'), nl,
  write('    auto reent_pp = [&] ()->int {'), nl,
  write('      return plan_processors();'), nl,
  write('    };'), nl,
  write('    auto reent_tf = [&] ('), write(Throws), write(') {'), nl,
  (
   =(ID2, '')->
    true;
    ( write('      throw_first'), write('(worker_'), write(ID2), write(', '), write(TNames), write(');'), nl )
  ),
  write('    };'), nl,
  write('    auto reent_tl = [&] ('), write(Throws), write(') {'), nl,
  (
   =(ID2, '')->
    true;
    ( write('      throw_last'), write('(worker_'), write(ID2), write(', '), write(TNames), write(');'), nl )
  ),
  write('    };'), nl,
  write('    auto reent_ts = [&] ()->int {'), nl,
  write('      return throw_stage();'), nl,
  write('    };'), nl,
  write('    auto reent_tn = [&] ()->int {'), nl,
  write('      return throw_num_stages();'), nl,
  write('    };'), nl,
  write('    auto reent_pln = [&] ()->int {'), nl,
  write('      return plan_linear_num();'), nl,
  write('    };'), nl,
  write('    auto reent_ptn = [&] ()->int {'), nl,
  write('      return plan_topology_num();'), nl,
  write('    };'), nl,
  write('    auto reent_ptq = [&] () {'), nl,
  write('      plan_topology_quit();'), nl,
  write('    };'), nl,
  write('    auto reent_pnb = [&] (bool incoming, input_proc Ref, int * n, input_proc * refs) {'), nl,
  write('      plan_neighbours(incoming, Ref, n, refs);'), nl,
  write('    };'), nl,
  write('    worker(reent_pf, reent_pl, reent_sa, reent_gf, reent_gl, reent_gp, reent_cp, reent_pi, reent_pp, reent_tf, reent_tl, reent_ts, reent_tn, reent_pln, reent_ptn, reent_ptq, reent_pnb, '), write(Names), write(');'), nl,
  write('}'), nl.
@write_defs(GID):-
  funs(GID, LAMBDAS),
  cfuns(GID, CLAMBDAS),
  (g_read('$defined$', [HDEFS|TDEFS])->
     (
      reverse([HDEFS|TDEFS], DEFS1),
      (
       (
        member(def(ID, ParamTypes, ParamNames, spec(NM, TP)), DEFS1),
        member(ID, LAMBDAS),
        make_reentera_def(ID, ParamTypes, ParamNames, spec(NM, TP)),
        fail
       );
       true
      )
     );
     g_assign('$defined$', [])
  ),
  !,
  (g_read('$cdefined$', [HCDEFS|TCDEFS])->
     (
      (
       reverse([HCDEFS|TCDEFS], CDEFS1),
       member(IDD, CLAMBDAS),
       member(def(IDD, ID2, ParamTypes, ParamNames, _, ThrowTypes, ThrowNames), CDEFS1),
       make_chain_def(IDD, ID2, ParamTypes, ParamNames, ThrowTypes, ThrowNames),
       fail
      );
      true
     );
     g_assign('$cdefined$', [])
  ),
  !.
@goal:-
    (g_read('$defined$', [_|_])->
       true;
       g_assign('$defined$', [])
    ),
    !,
    (g_read('$cdefined$', [_|_])->
       true;
       g_assign('$cdefined$', [])
    ),
    !,
    (
     g_read('$fdefined$', [HDEFS|TDEFS])->
     (
      member(fun(GID, _, _), [HDEFS|TDEFS])->
       write_defs(GID);
       ( g_assign('$fdefined$', [fun(GID, NAME, HEAD),HDEFS|TDEFS]), asserta(funs(GID, [])), asserta(cfuns(GID, [])) )
     );
     ( g_assign('$fdefined$', [fun(GID, NAME, HEAD)]), asserta(funs(GID, [])), asserta(cfuns(GID, [])) )
    ).
@goal:-
    nl,
    write(HEAD),
    !.
};

#def_pattern scan_reentera => make_reent (gid(), //ParamType/@Value, //ParamName/@Value, /root/Name/@Value, '', /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    auto
    (\s|\\n|\\t)+
    (\w+)->{Name}
    (\s|\\n|\\t)*
    \=
    (\s|\\n|\\t)*
    reenterable
    (\s|\\n|\\t)*
    \(
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\,))?=>{Predicates.TBAL($,',')})*
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\)))?=>{Predicates.TBAL($,')')})
    (\s|\\n|\\t)*
    \{
     ((.{1,8192})->{Body}\})?=>{Predicates.BAL($,'}')}
    (\s|\\t)*
    \;
    (\s|\\t)*
  @end
};

#def_pattern scan_freentera => make_reent (gid(), //ParamType/@Value, //ParamName/@Value, /root/Name/@Value, /root/RetType/@Value, /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    auto
    (\s|\\n|\\t)+
    (\w+)->{Name}
    (\s|\\n|\\t)*
    \=
    (\s|\\n|\\t)*
    reenterable
    (\s|\\n|\\t)*
    \(
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\,))?=>{Predicates.TBAL($,',')})*
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\)))?=>{Predicates.TBAL($,')')})
    (\s|\\n|\\t)*
    \-\>
    (\s|\\n|\\t)*
    (([^{}]{1,256})->{RetType}\{)?=>{Predicates.BAL($,'{')}
    ((.{1,8192})->{Body}\})?=>{Predicates.BAL($,'}')}
    (\s|\\n|\\t)*
    \;
    (\s|\\t)*
  @end
};

#def_module() make_reent(ID, ParamTypes, ParamNames, NAME, RetType, BODY) {
@goal:-brackets_off.
@goal:-
    (
     g_read('$defined$', DEFS),
     (
      member(def(ID, _, _, _), DEFS)->
       true;
       (
        (
         (
          g_read('$fdefined$', [fun(GID, _, _)|_])->
            true;
            =(GID,10000)
         ),
         (
          ( predicate_property(funs(_,_),'dynamic'), funs(GID, LAMBDAS) )->
            (
              retractall(funs(GID, _)),
              asserta(funs(GID, [ID|LAMBDAS]))
            );
            asserta(funs(GID, [ID]))
         )
        ),
        g_assign('$defined$', [def(ID, ParamTypes, ParamNames, spec(NAME, RetType))|DEFS])
       )
     )
    ).
@make_params2([Type], [Name], Params, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Params),
    !.
@make_params2([Type|T1], [Name|T2], Params, Names):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params2(T1, T2, P4, NM),
    !,
    atom_concat(P3, P4, Params),
    atom_concat(Name, ', ', NM1),
    atom_concat(NM1, NM, Names),
    !.
@make_params2(Type, Name, Param, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@make_reentera_body:-
    make_params2(ParamTypes, ParamNames, Params, Names),
    !,
    write('reentera_function_'), write(ID), write(' worker_'), write(ID),
    write(' = [&] (reentera_pf_'), write(ID), write(' reent_first, reentera_pf_'), write(ID),
    write(' reent_last, reentera_sa_'), write(ID),
    write(' _reent_group_soft_atomize, reentera_gf_'), write(ID),
    write(' _reent_group_first, reentera_gl_'), write(ID),
    write(' _reent_group_last, reentera_gp_'), write(ID),
    write(' _reent_group_parallelize, reentera_cp_'), write(ID),
    write(' _clear_reent, reentera_pi_'), write(ID),
    write(' _reent_processor_id, reentera_pp_'), write(ID),
    write(' _reent_processors, '),
    write(Params), write(')'),
    (
     =(RetType, '')->
       true;
       (write('->'), write(RetType))
    ),
    write(' {'), nl,
    write(BODY), nl,
    write('};'), nl,
    write('auto '), write(NAME), write(' = [&] ('), write(Params), write(')'),
    (
     =(RetType, '')->
       true;
       (write('->'), write(RetType))
    ),
    write(' {'), nl,
    (
     =(RetType, '')->
       true;
       write('return')
    ),
    write(' reentera_'), write(ID), write('(worker_'), write(ID), write(','), write(Names), write(');'), nl,
    write('};'),
    nl.
@goal:-make_reentera_body, !.
};

#def_pattern scan_simple_chain => make_simple_chain (gid(), /root/NP/@Value, //ParamType/@Value, //ParamName/@Value, /root/Name/@Value, /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    auto
    (\s|\\n|\\t)+
    (\w+)->{Name}
    (\s|\\n|\\t)*
    \=
    (\s|\\n|\\t)*
    chain
    (\s|\\n|\\t)*
    \[
      ((\s|\\n|\\t)*((.{1,96})->{NP}\])?=>{Predicates.BAL($,']')})
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

#def_module() make_simple_chain(ID, NP, ParamTypes, ParamNames, NAME, BODY) {
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
        g_assign('$cdefined$', [def(ID, ID, ParamTypes, ParamNames, NAME, ParamTypes, ParamNames)|CDEFS])
       )
     )
    ).
@make_params3([Type], [Name], Params, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Params),
    !.
@make_params3([Type|T1], [Name|T2], Params, Names):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params3(T1, T2, P4, NM),
    !,
    atom_concat(P3, P4, Params),
    atom_concat(Name, ', ', NM1),
    atom_concat(NM1, NM, Names),
    !.
@make_params3(Type, Name, Param, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@make_simple_body:-
    make_params3(ParamTypes, ParamNames, Params, Names),
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
    write(BODY), nl,
    write('};'), nl,
    write('auto '), write(NAME), write(' = [&] ('), write(Params), write(')'),
    write(' {'), nl,
    write(' plan_parallel_chain(1, '), write(NP), write(', chain_'), write(ID), write('(worker_'), write(ID), write(','), write(Names), write('));'),
    write('};'),
    nl.
@goal:-make_simple_body, !.
};

#def_pattern scan_complex_chain => make_complex_chain (gid(), //ParamType/@Value, //ParamName/@Value, /root/InitVals/@Value, /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (
     (\s|\\n|\\t)*
     chain
     (\s|\\n|\\t)*
     \<
       ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+(\s|\\n|\\t)*(\,|\>))->{ParamName}))?=>{Predicates.TBAL($,',>')})+
     (\s|\\n|\\t)*
     \(
       ((.{1,1024})->{InitVals}\))?=>{Predicates.BAL($,')')}
     (\s|\\n|\\t)*
     \{
      ((.{1,8192})->{Body}\})?=>{Predicates.BAL($,'}')}
     (\s|\\t)*
    )+
    \;
  @end
};

#def_module() make_complex_chain(CID, CParamTypes, CParamNames, CInit, CBODY) {
@goal:-brackets_off.
@get_chain_items([], [], []):-
    !.
@get_chain_items(R, L, [L1|T]):-
    append(R1, R2, R),
    last(R1, LAST),
    atom_chars(LAST, LLAST),
    last(LLAST, '>'),
    length(R1, NN),
    append(L1, L2, L),
    length(L1, NN),
    !,
    get_chain_items(R2, L2, T).
@purge_names([], []):-
    !.
@purge_names([H|T], [H1|T1]):-
    atom_chars(H, HH),
    append(HL, [_], HH),
    atom_chars(H1, HL),
    purge_names(T, T1).
@make_params4([Type], [Name], Param):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@make_params4([Type|T1], [Name|T2], Param):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params4(T1, T2, P4),
    !,
    atom_concat(P3, P4, Param),
    !.
@make_params4(Type, Name, Param):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Param),
    !.
@make_complex_body(N, [ParamTypes|PT], [ParamNames|PN], [Init|IN], [BODY|CB]):-
    atom_concat(CID, '_', ID1),
    number_atom(N, NN),
    atom_concat(ID1, NN, ID),
    (
     =(PT,[])->
       =(NXT, N);
       NXT is N+1
    ),
    number_atom(NXT, NNXT),
    atom_concat(ID1, NNXT, ID2),
    g_read('$cdefined$', CDEFS),
    (
     member(def(ID, ID2, _, _, _, _, _), CDEFS)->
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
       (
        =(PT,[])->
         g_assign('$cdefined$', [def(ID, ID2, ParamTypes, ParamNames, Init, ParamTypes, ParamNames)|CDEFS]);
         (=([TT|_],PT), =([TN|_], PN), g_assign('$cdefined$', [def(ID, ID2, ParamTypes, ParamNames, Init, TT, TN)|CDEFS]))
       )
      )
    ),
    make_params4(ParamTypes, ParamNames, Params),
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
    write(BODY), nl,
    write('};'), nl,
    (
     =(PT,[])->
      true;
      ( N1 is N+1, make_complex_body(N1, PT, PN, IN, CB) )
    ).
@make_chain(N, [_], [_], [Init], [_]):-
    atom_concat(CID, '_', ID1),
    number_atom(N, NN),
    atom_concat(ID1, NN, ID),
    write('chain_'), write(ID), write('(worker_'), write(ID), write(','), write(Init), write(')'),
    !.
@make_chain(N, [_|PT], [_|PN], [Init|IN], [_|CB]):-
    atom_concat(CID, '_', ID1),
    number_atom(N, NN),
    atom_concat(ID1, NN, ID),
    write('chain_'), write(ID), write('(worker_'), write(ID), write(','), write(Init), write('),'),
    N1 is N+1,
    make_chain(N1, PT, PN, IN, CB),
    !.
@make_complex_call(PT, PN, IN, CB):-
    write('  plan_parallel_chain(1, '),
    make_chain(1, PT, PN, IN, CB),
    write(');'), nl.
@goal:-
    purge_names(CParamNames, CNN),
    get_chain_items(CParamNames, CParamTypes, PT), get_chain_items(CParamNames, CNN, PN),
    make_complex_body(1, PT, PN, CInit, CBODY),
    make_complex_call(PT, PN, CInit, CBODY),
    !.
};

#def_pattern scan_general_topo => make_general_topo (gid(), /root/DESC/@Value, //ParamType/@Value, //ParamName/@Value, /root/Name/@Value, /root/Body/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    auto
    (\s|\\n|\\t)+
    (\w+)->{Name}
    (\s|\\n|\\t)*
    \=
    (\s|\\n|\\t)*
    chain
    (\s|\\n|\\t)*
    \[
      (\s|\\n|\\t)*
    \]
    (\s|\\n|\\t)*
    \<
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\,))?=>{Predicates.TBAL($,',')})*
      ((\s|\\n|\\t)*(((.{1,96})->{ParamType}(\s|\\n|\\t)*\b(\w+)->{ParamName})(\s|\\n|\\t)*(\>))?=>{Predicates.TBAL($,'>')})
    (\s|\\n|\\t)*
    \{
     ((.{1,8192})->{Body}\})?=>{Predicates.BAL($,'}')}
    (\s|\\t)*
    \{
      ((\s|\\n|\\t)*(([0-9\-\>\< ]{1,96})->{DESC}(\s|\\n|\\t)*(\,))?=>{Predicates.BAL($,',')})*
      ((\s|\\n|\\t)*(([0-9\-\>\< ]{1,96})->{DESC}(\s|\\n|\\t)*(\}))?=>{Predicates.BAL($,'}')})
    \;
    (\s|\\t)*
  @end
};

#def_module() make_general_topo(ID, DESC, ParamTypes, ParamNames, NAME, BODY) {
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
        g_assign('$cdefined$', [def(ID, ID, ParamTypes, ParamNames, NAME, ParamTypes, ParamNames)|CDEFS])
       )
     )
    ).
@make_params5([Type], [Name], Params, Name):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, Params),
    !.
@make_params5([Type|T1], [Name|T2], Params, Names):-
    atom_concat(Type, ' ', P1),
    atom_concat(P1, Name, P2),
    atom_concat(P2, ',', P3),
    make_params5(T1, T2, P4, NM),
    !,
    atom_concat(P3, P4, Params),
    atom_concat(Name, ', ', NM1),
    atom_concat(NM1, NM, Names),
    !.
@make_params5(Type, Name, Param, Name):-
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
@make_gen_body:-
    make_params5(ParamTypes, ParamNames, Params, Names),
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
    atom_concat('chain_', ID, REF0),
    atom_concat(REF0, '[', REF),
    substitute(BODY, 'this[', REF, BODY1),
    write(BODY1), nl,
    write('};'), nl,
    write('auto '), write(NAME), write(' = [&] ('), write(Params), write(')'),
    write(' {'), nl,
    write(' plan_topology {'),
    make_line(DESC, Names),
    write(' };'), nl,
    write('};'),
    nl.
@trim_blanks([' '|T], L):-
    trim_blanks(T, L).
@trim_blanks(['\t'|T], L):-
    trim_blanks(T, L).
@trim_blanks(L, L):-
    !.
@get_num(MOST, [], MOST, []):-
    !.
@get_num(MOST, [C|T], N, REST):-
    ( atom_codes(C, [CODE]), >(CODE, 47), <(CODE, 58) ),
    !,
    MOST1 is MOST*10+(CODE-48),
    get_num(MOST1, T, N, REST),
    !. 
@get_num(MOST, [C|T], MOST, [C|T]):-
    \+ ( atom_codes(C, [CODE]), >(CODE, 47), <(CODE, 58) ),
    !.
@extract_lnums([], []):-
    !.
@extract_lnums([' '|T1], L2):-
    extract_lnums(T1, L2).
@extract_lnums(['\t'|T1], L2):-
    extract_lnums(T1, L2).
@extract_lnums(['-','>'|T1], [N2|T2]):-
    trim_blanks(T1, T11),
    get_num(0, T11, N2, REST),
    !,
    extract_lnums(REST, T2).
@extract_lnums(['<','-'|T1], [N2N|T2]):-
    trim_blanks(T1, T11),
    get_num(0, T11, N2, REST),
    N2N is -N2,
    !,
    extract_lnums(REST, T2).
@extract_nums(CHARS, [N1|T]):-
    get_num(0, CHARS, N1, REST),
    !,
    extract_lnums(REST, T).
@process_line([], _):-
    !.
@process_line([_], _):-
    !.
@process_line([A,B|T], Init):-
    AA is abs(A),
    BB is abs(B),
    (
      >(B, 0)->
       ( write('plan_parallel_chain('),
         write('chain_'), write(ID), write('['), write(AA), write('](worker_'), write(ID), write(','), write(Init), write(')->'),
         write('chain_'), write(ID), write('['), write(BB), write('](worker_'), write(ID), write(','), write(Init), write(')'),
         write(');'), nl );
       ( write('plan_parallel_reverse('),
         write('chain_'), write(ID), write('['), write(BB), write('](worker_'), write(ID), write(','), write(Init), write(')->'),
         write('chain_'), write(ID), write('['), write(AA), write('](worker_'), write(ID), write(','), write(Init), write(')'),
         write(');'), nl )
    ),
    process_line([BB|T], Init),
    !.
@make_line([], Init):-
    !.
@make_line([L|T], Init):-
    atom_chars(L, CHARS),
    extract_nums(CHARS, LNUMS),
    process_line(LNUMS, Init),
    !,
    make_line(T, Init).
@goal:-make_gen_body, !.
};

#endif
