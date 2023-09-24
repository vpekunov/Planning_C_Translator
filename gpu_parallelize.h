#ifndef __GPU_PARALLELIZE__
#define __GPU_PARALLELIZE__

#pragma plan vectorized

#pragma syntax nocheck

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

#preproc_passes(2)

#add_scan(optFun,nonOptHeader,gpuFor)

#def_module() enumerations_point() {
@goal:-brackets_off.
@intersect([],_,[]):-!.
@intersect([H|T],L,[H|L1]):-
  member(H,L),
  intersect(T,L,L1),
  !.
@intersect([_|T],L,L1):-
  intersect(T,L,L1),
  !.
@union([],L,L):-!.
@union([H|T],L,L1):-
  member(H,L),
  union(T,L,L1),
  !.
@union([H|T],L,[H|L1]):-
  union(T,L,L1),
  !.
@explode(_,0,[]):-!.
@explode(GID,N,[A3|T1]):-
  N1 is N-1,
  atom_concat('ID',GID,AA),
  atom_concat(AA,'_',A1),
  number_atom(N1,A2),
  atom_concat(A1,A2,A3),
  explode(GID,N1,T1),
  !.
@get_marks(Visited,Visited,C,[]):-
  member(C,Visited),
  !.
@get_marks(Visited,Visited1,C,LMARKS):-
  ( (predicate_property(lmarks(_,_,_),'dynamic'), lmarks(C,LM1,_))->true;=(LM1,[]) ),
  !,
  (
    ( predicate_property(calls(_,_),'dynamic'), calls(C, CALLS) )->
     (
       make_trace([C|Visited], Visited1, CALLS, LM2),
       union(LM1,LM2,LMARKS)
     );
     ( =(LMARKS,LM1), =(Visited1,[C|Visited]) )
  ),
  !.
@make_trace(Visited,Visited,[],[]):-!.
@make_trace(Visited,Visited2,[C|CALLS],LMARKS):-
  get_marks(Visited,Visited1,C,LM1),
  make_trace(Visited1,Visited2,CALLS,LM2),
  union(LM1,LM2,LMARKS),
  !.
@write_enums('', [], Last):-
  write(', '), write(Last), write(' };'), nl,
  !.
@write_enums(_, [[]], Last):-
  write('enum { '), write(Last), write(' = 1'), write(' };'), nl,
  !.
@write_enums('0', [], Last):-
  write('enum { '), write(Last), write(' = 1'), write(' };'), nl,
  !.
@write_enums('', [E|T], Last):-
  write(', '), write(E),
  write_enums('', T, Last),
  !.
@write_enums(FirstValue, [E|T], Last):-
  write('enum { '), write(E), write(' = '), write(FirstValue),
  write_enums('', T, Last),
  !.
@goal:-
  (
   (predicate_property(enumerated,'dynamic'), enumerated)->
     (
      (
        (
          predicate_property(marks(_,_,_),'dynamic'),
          marks(GID,ID,N),
          once(explode(GID,N,LMARKS)),
          assertz(lmarks(ID,LMARKS,GID)),
          fail
        );
        true
      ),
      !,
      assertz(common([[]])),
      (
        (
          predicate_property(gpu_loop(_,_),'dynamic'),
          gpu_loop(GIDL,LOOPCALLS),
          once(;(->(lmarks(_,LLMARKS,GIDL),true),=(LLMARKS,[]))),
          once(make_trace([],_,LOOPCALLS,TLMARKS)),
          once(union(LLMARKS,TLMARKS,LMARKS)),
          once(common(GENMARKS)),
          once(retractall(common(_))),
          once(;( ->(=(GENMARKS,[[]]),=(NEWMARKS,LMARKS)) , once(union(GENMARKS,LMARKS,NEWMARKS)) )),
          assertz(common(NEWMARKS)),
          fail
        );
        true
      ),
      !,
      common(GenEnums),
      write_enums('0', GenEnums, '__markCommons'),
      !
     );
     (
      assertz(enumerated)
     )
  ).
};

#pragma plan common begin
enumerations_point();
#pragma plan common end

#def_pattern optFun => insert_marks(gid(), '', '', '', //RETTYPE/@Value, //ID/@Value, //PARAMS/@Value, //KINDS/@Value, //TYPES/@Value, //NAMES/@Value, '', //OP/@Value, //TYPE/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    \$(\s|\\t|\\n)+
    ((([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{RETTYPE}(\w+(\\n|\s|\\t)*)->{ID}
         (
          (
           (\(
            (
             (
              (\s|\\t|\\n)*
              (
               ()->{KINDS}
               (([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{TYPES}
               (\w+)->{NAMES}
               (\s|\\t|\\n)*\,
              )?=>{Predicates.TBAL($,',')}
             )*
             (
              (\s|\\t|\\n)*
              (
               (
                ()->{KINDS}
                void|
                (
                 (([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{TYPES}
                 (\w+)->{NAMES}
                )
                (\s|\\t|\\n)*
               )?
               \)
              )?=>{Predicates.TBAL($,')')}
             )
            )
           )->{PARAMS}
           (\s|\\t|\\n)*
          )
         )(\s|\\t|\\n)*)
    \{
    (*PRUNE)
    (
     (
      (\s|\\t|\\n)*
      (
       ((if)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((do)->{TYPE}\b(\s|\\t|\\n)*)|
       ((else)->{TYPE}\b(\s|\\t|\\n)*)|
       ((while)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((for)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((switch)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((case)->{TYPE}\b(\s|\\t|\\n)*(([^:]{1,368})\:)?=>{Predicates.BAL($,':')}(\s|\\t|\\n)*)|
       ((break)->{TYPE}(\s|\\t|\\n)*\;)|
       ((\{)->{TYPE}(\s|\\t|\\n)*)|
       ((\})->{TYPE}(\s|\\t|\\n)*)|
       ((\w+)->{TYPE}(\s|\\t|\\n)*\(((.{0,512})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*\;)|
       (()->{TYPE}(((.{0,368})\;)?=>{Predicates.BAL($,';')}))
      )
     )->{OP}*
     (\s|\\t|\\n)*
     \}
    )?=>{Predicates.BAL($,'}')}
  @end
  (\s|\\t|\\n)*
};

#def_pattern nonOptHeader => register_fun(gid(), //RETTYPE/@Value, //ID/@Value, //PARAMS/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ((([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{RETTYPE}(\w+(\\n|\s|\\t)*)->{ID}
         (
          (
           (\(
            (
             (
              (\s|\\t|\\n)*
              (
               (([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{TYPES}
               (\w+)->{NAMES}
               (\s|\\t|\\n)*\,
              )?=>{Predicates.TBAL($,',')}
             )*
             (
              (\s|\\t|\\n)*
              (
               (
                void|
                (
                 (([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{TYPES}
                 (\w+)->{NAMES}
                )
                (\s|\\t|\\n)*
               )?
               \)
              )?=>{Predicates.TBAL($,')')}
             )
            )
           )->{PARAMS}
           (\s|\\t|\\n)*
          )
         )(\s|\\t|\\n)*)
  @end
  \{
  (\s|\\t|\\n)*
};

#def_pattern gpuFor => insert_marks(gid(), //DEVICE/@Value, //CHUNK/@Value, //LOOP/@Value, '', randomid(), //PARAMS/@Value, //KINDS/@Value, //TYPES/@Value, //NAMES/@Value, //SIZES/@Value, //OP/@Value, //TYPE/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    vectorized(\s|\\t|\\n)*\(
          ((.{0,128})->{DEVICE}\,)?=>{Predicates.BAL($,',')}
          (\s|\\t|\\n)*
          ((.{0,128})->{CHUNK}\))?=>{Predicates.BAL($,')')}
          (\s|\\t|\\n)*
    gpu(\s|\\t|\\n)*
         (
          (
           (\<
            (
             (\s|\\t|\\n)*
             (_local(\s|\\t|\\n)+|_global(\s|\\t|\\n)+|_pivot(\s|\\t|\\n)+|)->{KINDS}
             (
              (.{1,128})->{TYPES}
              (\s|\\t|\\n)(\w+)->{NAMES}
              (\s|\\t|\\n)*
              ((\[(.{1,64}\])?=>{Predicates.BAL($,']')}(\s|\\t|\\n)*)*)->{SIZES}
              \,
             )?=>{Predicates.TBAL($,',')}
            )*
            (
             (\s|\\t|\\n)*
             (_local(\s|\\t|\\n)+|_global(\s|\\t|\\n)+|_pivot(\s|\\t|\\n)+|)->{KINDS}
             (
              (.{1,128})->{TYPES}
              (\s|\\t|\\n)(\w+)->{NAMES}
              (\s|\\t|\\n)*
              ((\[(.{1,64}\])?=>{Predicates.BAL($,']')}(\s|\\t|\\n)*)*)->{SIZES}
              \>
             )?=>{Predicates.TBAL($,'>')}
            )
           )->{PARAMS}
           (\s|\\t|\\n)*
          )
         )(\s|\\t|\\n)*
    (
     (for|while)(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*
    )->{LOOP}
    (()->{MARGIN}\{((.*)$)?=>{Predicates.getBAL($,'}',$MARGIN), stop_fail(MARGIN)}|\{)
    (
     (
      (\s|\\t|\\n)*
      (
       ((if)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((do)->{TYPE}\b(\s|\\t|\\n)*)|
       ((else)->{TYPE}\b(\s|\\t|\\n)*)|
       ((while)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((for)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((switch)->{TYPE}(\s|\\t|\\n)*\(((.{1,368})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*)|
       ((case)->{TYPE}\b(\s|\\t|\\n)*(([^:]{1,368})\:)?=>{Predicates.BAL($,':')}(\s|\\t|\\n)*)|
       ((break)->{TYPE}(\s|\\t|\\n)*\;)|
       ((\{)->{TYPE}(\s|\\t|\\n)*)|
       ((\})->{TYPE}(\s|\\t|\\n)*)|
       ((\w+)->{TYPE}(\s|\\t|\\n)*\(((.{0,512})\))?=>{Predicates.BAL($,')')}(\s|\\t|\\n)*\;)|
       (()->{TYPE}(((.{0,368})\;)?=>{Predicates.BAL($,';')}))
      )
     )->{OP}*
     (\s|\\t|\\n)*
     \}
    )?=>{Predicates.BAL($,'}')}
  @end
  (\s|\\t|\\n)*
};

#def_module() insert_marks(GID, DEVICE, CHUNK, LOOP, RETTYPE, ID, PARAMS, KINDS, TYPES, NAMES, SIZES, OP, TYPE) {
@goal:-brackets_off.
@put_register(N,N1):-
  N1 is N+1,
  write('RegisterMark(TR,ID'), write(GID), write('_'), write(N), write(');'), nl,
  !.
@make_op(C1,C2,N,N2,[H1|T1],R1,['{'|T2],R2):-
  write(H1), put_register(N,N1),
  make_seq(C1, C2, N1, N2, T1, R1, T2, R2),
  !.
@make_op(C1,C2,N,N1,[H1|T1],R1,['if','{'|T2],R2):-
  write(H1),
  make_op(C1, C22, N, N12, T1, R12, ['{'|T2], R22),
  (=(R22,['else'|_])->
     (make_op(C22,C2,N12,N1,R12,R1,R22,R2),!);
     (=(C2,C22),=(R2,R22),=(N1,N12),=(R1,R12))
  ),
  !.
@make_op(C1,C2,N,N2,[H1|T1],R1,['if'|T2],R2):-
  write(H1), write('{'), put_register(N,N1),
  make_op(C1, C22, N1, N12, T1, R12, T2, R22),
  write('}'),
  (=(R22,['else'|_])->
     (make_op(C22,C2,N12,N2,R12,R1,R22,R2),!);
     (=(C2,C22),=(R2,R22),=(N2,N12),=(R1,R12))
  ),
  !.
@make_op(C1,C2,N,N1,[H1|T1],R1,['else','{'|T2],R2):-
  write(H1),
  make_op(C1, C2, N, N1, T1, R1, ['{'|T2], R2),
  !.
@make_op(C1,C2,N,N2,[H1|T1],R1,['else'|T2],R2):-
  write(H1), write('{'), put_register(N,N1),
  make_op(C1, C2, N1, N2, T1, R1, T2, R2),
  write('}'),
  !.
@make_op(C1,C1,N,N,[H1|T1],T1,['break'|T2],T2):-
  write(H1),
  !.
@make_op(C1,C1,N,N,[H1|T1],T1,['case'|T2],T2):-
  write(H1),
  !.
@make_op(C1,C2,N,N1,[H1|T1],R1,['do','{'|T2],R2):-
  write(H1),
  make_op(C1, C2, N, N1, T1, [H2,_|R1], ['{'|T2], ['while',''|R2]),
  write(H2), write(';'),
  !.
@make_op(C1,C2,N,N1,[H1|T1],R1,['while','{'|T2],R2):-
  write(H1),
  make_op(C1, C2, N, N1, T1, R1, ['{'|T2], R2),
  !.
@make_op(C1,C2,N,N2,[H1|T1],R1,['while'|T2],R2):-
  write(H1), write('{'), put_register(N,N1),
  make_op(C1, C2, N1, N2, T1, R1, T2, R2),
  write('}'),
  !.
@make_op(C1,C2,N,N1,[H1,H2|T1],R1,['switch','{'|T2],R2):-
  write(H1), write(H2),
  make_seq(C1, C2, N, N1, T1, R1, T2, R2),
  !.
@make_op(C1,C2,N,N1,[H1|T1],R1,['for','{'|T2],R2):-
  write(H1),
  make_op(C1, C2, N, N1, T1, R1, ['{'|T2], R2),
  !.
@make_op(C1,C2,N,N2,[H1|T1],R1,['for'|T2],R2):-
  write(H1), write('{'), put_register(N,N1),
  make_op(C1, C2, N1, N2, T1, R1, T2, R2),
  write('}'),
  !.
@make_op(C1,C1,N,N,[H1|T1],T1,[''|T2],T2):-
  write(H1),
  !.
@make_op(CALLS,[CALL|CALLS],N,N,[H1|T1],T1,[CALL|T2],T2):-
  write(H1),
  !.
@make_seq(C1,C1,N,N,[],[],[],[]):-!.
@make_seq(C1,C1,N,N,[H1|T1],T1,['}'|T2],T2):-
  write(H1),
  !.
@make_seq(C1,C3,N,N2,[H1|T1],R1,[H2|T2],R2):-
  make_op(C1,C2,N,N1,[H1|T1],R11,[H2|T2],R22),
  make_seq(C2,C3,N1,N2,R11,R1,R22,R2),
  !.
@make_seq(C1,C2,N,N1,A1,R1,A2,R2):-
  \+ is_list(A1),
  make_seq(C1,C2,N,N1,[A1],R1,[A2],R2),
  !.
@make_set([],[]):-!.
@make_set([H|T],T1):-
  member(H,T),
  !,
  make_set(T,T1),
  !.
@make_set([H|T],[H|T1]):-
  make_set(T, T1),
  !.
@determ_size(L,R,S):-
  append(Part,[']'|R],L),
  !,
  atom_chars(PP,['('|Part]),
  atom_concat(PP,')',S),
  !.
@determ_sizes([],''):-!.
@determ_sizes([' '|T],A):-
  determ_sizes(T,A),
  !.
@determ_sizes(['['|Rest],B):-
  determ_size(Rest, Rest1, B),
  determ_sizes(Rest1, '').
@determ_sizes(['['|Rest],A):-
  determ_size(Rest, Rest1, B),
  determ_sizes(Rest1, C),
  !,
  atom_concat(B,'*',BB),
  atom_concat(BB,C,A),
  !.
@get_size(SZ,ASZ):-
  atom_chars(SZ, LSZ),
  determ_sizes(LSZ, ASZ),
  !.
@gen_reent_each_param('','','',''):-!.
@gen_reent_each_param([],[],[],[]):-!.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[_|SZZ]):-
  atom_concat('_local',_,K),
  !,
  write(', _local(1) '), write(T), write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[SZ|SZZ]):-
  atom_concat('_pivot',_,K),
  !,
  (=(SZ,'')->
    (write(', _global(1) '), write(T));
    (write(', _global('),get_size(SZ,ASZ),write(ASZ),write(') '), write(T), write(' *'))
  ), !,
  write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[SZ|SZZ]):-
  atom_concat('_global',_,K),
  !,
  (=(SZ,'')->
    (write(', _global(1) '), write(T));
    (write(', _global('),get_size(SZ,ASZ),write(ASZ),write(') '), write(T), write(' *'))
  ), !,
  write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([''|TK],[T|TT],[N|NN],[_|SZZ]):-
  !,
  write(', '), write(T), write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param(K,T,N,S):-
  gen_reent_each_param([K],[T],[N],[S]).
@gen_reent_params(Kinds,Types,Names,Sizes):-
  write('int init, int __markCommons, _local(__planned__.__markCommons) unsigned short * TR'),
  gen_reent_each_param(Kinds,Types,Names,Sizes),
  !.
@insert_prototype([]):-!.
@insert_prototype([block(Gid,loop(B,Device,Chunk,Kinds,Types,Names,Sizes))|T]):-
  write('reenterable['), write(Chunk), write('+1] static Loop'), write(Gid), write('('),gen_reent_params(Kinds,Types,Names,Sizes),write(') {'), nl,
  write('  if (init == 1) {'), nl,
  write('     plan_group_vectorize('), write(Device), write(');'), nl,
  write('  } else if (init == 2) {'), nl,
  write('     plan_undo_locals();'),nl,
  write('  } else {'), nl,
  write(B),
  write('  }'), nl,
  write('}'),
  nl, nl,
  insert_prototype(T),
  !.
@insert_prototype(_):-!.
@build_blocks_list(B):-
  retractall(tempb(_)),
  assertz(tempb([])),
  (
   ( blocks(Gid,X), tempb(BB), retractall(tempb(_)), assertz(tempb([block(Gid,X)|BB])), fail );
   true
  ),
  !,
  tempb(B),
  !.
@insert_prototypes(GID):-
  build_blocks_list(Blocks),
  append(_,[block(GID,_)|T],Blocks),
  !,
  insert_prototype(T),
  !.
@write_param_names(''):-!.
@write_param_names([H]):-write(H),!.
@write_param_names([A,B|T]):-
  write(A), write(','),
  write_param_names([B|T]).
@write_param_names(A):-write(A),!.
@write_params(PRMS):-
  atom_chars(PRMS,[_|Rest]),
  !,
  append(R,[_],Rest),
  !,
  atom_chars(PRMS1,R),
  !,
  write(PRMS1).
@write_fun:-
  (
   (predicate_property(blocks(_,_),'dynamic'), blocks(GID,_))->
     insert_prototypes(GID);
     assertz(blocks(GID,optfun))
  ),
  !,
  nl, write('#define '), write(ID), write('('), write_param_names(NAMES), write(') __'), write(ID),
      write('(TR'), (=(NAMES,'')->true;write(',')), !, write_param_names(NAMES), write(')'), nl,
  write(RETTYPE), write(' __'), write(ID),
      write('(__global unsigned short * TR'), (=(NAMES,'')->true;write(',')), !, write_params(PARAMS), write(')'), nl,
  write('{'), nl,
  put_register(0,N1),
  (\=(OP,'')->make_seq([], CALLS, N1, N, OP, [], TYPE, []);( =(N,N1),=(CALLS,[]) )),
  !,
  (
   (predicate_property(marks(_,_,_),'dynamic'), marks(GID,ID,_))->
     true;
     assertz(marks(GID,ID,N))
  ),
  !,
  make_set(CALLS, SETCALLS),
  (
   (predicate_property(calls(_,_),'dynamic'), calls(ID,_))->
     true;
     assertz(calls(ID,SETCALLS))
  ),
  !,
  write('}'), nl, !.
@read_code(S,C,[C]):-
  at_end_of_stream(S),
  !.
@read_code(S,C,[C|T]):-
  get_code(S,C1),
  read_code(S,C1,T),
  !.
@read_codes(S,TS):-
  get_code(S,C),
  read_code(S,C,TS).
@write_starter(Offs):-
  write(Offs), write('if (__chunker > 0) {'), nl,
  write(Offs), write('   Loop'), write(GID), write('([1, __markCommons, TR'),
    (=(NAMES,'')->true;write(',')), !, write_param_names(NAMES),
    write(']);'), nl,
  write(Offs), write('   float t = last_execution_time('), write(DEVICE), write(');'), nl,
  write(Offs), write('   for (int offs = __start_block; offs < __n; offs++) {'), nl,
  write(Offs), write('       int ptr = __plan_indexes[offs];'), nl,
  write(Offs), write('       for (int s = __HistorySize-1; s > 0; s--)'), nl,
  write(Offs), write('           Timings[ptr*__HistorySize + s] = Timings[ptr*__HistorySize + s-1];'), nl,
  write(Offs), write('       Timings[ptr*__HistorySize] = t;'), nl,
  write(Offs), write('   }'), nl,
  write(Offs), write('}'), nl,
  !.
@write_fillers(_, _, [], [], []):-!.
@write_fillers(Offs, PI, [K|TK], [N|TN], [V|TV]):-
  atom_concat('_global', _, K),
  !,
  write(Offs), write(PI), write('.'), write(N), write(' = '), write(V), write(';'), nl,
  write_fillers(Offs, PI, TK, TN, TV),
  !.
@write_fillers(Offs, PI, [K|TK], [N|TN], [V|TV]):-
  atom_concat('_local', _, K),
  !,
  write(Offs), write(PI), write('.'), write(N), write(' = '), write(V), write(' + __n;'), nl,
  write_fillers(Offs, PI, TK, TN, TV),
  !.
@write_fillers(Offs, PI, [K|TK], [N|TN], [V|TV]):-
  atom_concat('_pivot', _, K),
  !,
  write(Offs), write(PI), write('.'), write(N), write(' = '), write(V), write(';'), nl,
  write_fillers(Offs, PI, TK, TN, TV),
  !.
@write_fillers(Offs, PI, [''|TK], [N|TN], [V|TV]):-
  !,
  write(Offs), write(PI), write('.'), write(N), write(' = '), write(V), write(';'), nl,
  write_fillers(Offs, PI, TK, TN, TV),
  !.
@get_pivot([], [], [], '', ''):-!.
@get_pivot([K|_], [N|_], [T|_], N, T):-
  atom_concat('_pivot', _, K),
  !.
@get_pivot([_|TK], [_|TN], [_|TT], N, T):-
  get_pivot(TK, TN, TT, N, T),
  !.
@write_loop:-
  write('{'), nl,
    write('static int __nn = 0;'), nl,
    write('static unsigned short * TR = NULL;'), nl,
    write('static unsigned short * TR1 = NULL;'), nl,
    write('static unsigned short * TR2 = NULL;'), nl,
    write('static unsigned short * TR3 = NULL;'), nl,
    write('static unsigned short * Prognosed0 = NULL;'), nl,
    write('static unsigned short * Prognosed1 = NULL;'), nl,
    write('static unsigned short * Prognosed2 = NULL;'), nl,
    write('static unsigned int np = 0;'), nl,
    write('static vector<int> WOrder(__markCommons);'), nl,
    write('static int TraceWNotFound = 7;'), nl,
    write('static float TraceW[__markCommons] = { 0.0f };'), nl,
    write('static float * Timings = NULL;'), nl,
    write('static WinnersType * Winners = NULL;'), nl,
    write('static BestersType * Besters = NULL;'), nl,
    write('static bool initialized = false;'), nl,
    write('if (!initialized) {'), nl,
    write('   np = omp_get_num_procs();'), nl,
    write('}'), nl,
    write('if (TraceWNotFound) {'), nl,
    write('   for (int i = 0; i < __markCommons; i++)'), nl,
    write('       WOrder[i] = i;'), nl,
    write('   sort(WOrder.begin(), WOrder.end(),'), nl,
    write('     [&](const int & A, const int & B)->bool {'), nl,
    write('        return TraceW[A] > TraceW[B];'), nl,
    write('     }'), nl,
    write('   );'), nl,
    write('   TraceWNotFound--;'), nl,
    write('}'), nl,
    write('int __total = 0;'), nl,
    write('int __n = 0;'), nl,
    write(LOOP), write(' __total++;'), nl,
    write('int __rest = __total % ('),write(CHUNK),write(');'),nl,
    write('int __working = __total;'),nl,
    write('if (__rest) __total += (('),write(CHUNK),write(') - __rest);'),nl,
    write('vector<int> __plan_indexes(__total);'), nl,
    write('for (int i = 0; i < __total; i++) __plan_indexes[i] = i;'), nl,
    write('if (__total > __nn) {'), nl,
    write('   TR = (unsigned short *) realloc(TR, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   TR1 = (unsigned short *) realloc(TR1, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   TR2 = (unsigned short *) realloc(TR2, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   TR3 = (unsigned short *) realloc(TR3, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   Prognosed0 = (unsigned short *) realloc(Prognosed0, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   Prognosed1 = (unsigned short *) realloc(Prognosed1, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   Prognosed2 = (unsigned short *) realloc(Prognosed2, __total*__markCommons*sizeof(unsigned short));'), nl,
    write('   Timings = (float *) realloc(Timings, __total*__HistorySize*sizeof(float));'), nl,
    write('   Winners = (WinnersType *) realloc(Winners, __total*sizeof(WinnersType));'), nl,
    write('   Besters = (BestersType *) realloc(Besters, __total*sizeof(BestersType));'), nl,
    write('   for (int i = __nn; i < __total; i++) {'), nl,
    write('       for (int j = 0; j < __HistorySize; j++) Timings[i*__HistorySize + j] = 1.0f;'), nl,
    write('       for (int j = 0; j < __markCommons; j++) Prognosed0[i*__markCommons + j] = 1;'), nl,
    write('       for (int j = 0; j < __markCommons; j++) Prognosed1[i*__markCommons + j] = 1;'), nl,
    write('       for (int j = 0; j < __markCommons; j++) Prognosed2[i*__markCommons + j] = 1;'), nl,
    write('       memset(Winners[i], 0, sizeof(WinnersType));'), nl,
    write('       memset(Besters[i], 0, sizeof(BestersType));'), nl,
    write('       memset(&TR[i*__markCommons], 0, __markCommons*sizeof(unsigned short));'), nl,
    write('       memset(&TR1[i*__markCommons], 0, __markCommons*sizeof(unsigned short));'), nl,
    write('       memset(&TR2[i*__markCommons], 0, __markCommons*sizeof(unsigned short));'), nl,
    write('       memset(&TR3[i*__markCommons], 0, __markCommons*sizeof(unsigned short));'), nl,
    write('   }'), nl,
    write('   __nn = __total;'), nl,
    write('}'), nl,
    write('vector<plan_item_type(Loop'), write(GID), write(')> __plan_sorted(__total);'), nl,
    write('plan_item_type(Loop'), write(GID), write(') __plan_item;'), nl,
% Collect plan
    write(LOOP),
    write('  {'), nl,
    write('    __plan_item.TR = TR + __n*__markCommons;'), nl,
    write_fillers('    ', '__plan_item', ['', '' | KINDS], ['init', '__markCommons' | NAMES], ['0', '__markCommons' | NAMES]),
    write('    __plan_sorted[__n] = __plan_item;'), nl,
    write('    __n++;'), nl,
    write('    if (__n == __working) { __plan_item.init = 2; for (; __n < __total; __n++) { __plan_item.TR = TR + __n*__markCommons; __plan_sorted[__n] = __plan_item; } }'),nl,
    write('  }'), nl,
% Sort indexes of plan
    get_pivot(KINDS, NAMES, TYPES, Pivot, PivotType),
    write('if (!initialized) {'), nl,
    (
     =(Pivot, '')->
      true;
      (
       write('   sort(__plan_indexes.begin(),__plan_indexes.end(),'), nl,
       write('     [&](const int & A, const int & B)->bool {'), nl,
       write('        int d = __plan_sorted[B].'), write(Pivot), write('[B] - __plan_sorted[A].'), write(Pivot), write('[A];'), nl,
       write('        int i;'), nl,
       write('        if (abs(d) > 0) return d < 0;'), nl,
       write('        for (i = 0; i < __markCommons; i++) {'), nl,
       write('            int p = WOrder[i];'), nl,
       write('            int q = (TR[B*__markCommons + p] - TR[A*__markCommons + p]);'), nl,
       write('            if (q != 0) return q < 0;'), nl,
       write('        }'), nl,
       write('        return false;'), nl,
       write('     }'), nl,
       write('   );'), nl
      )
    ),
    !,
    write('   initialized = true;'), nl,
    write('}'), nl,
% Empty traces
    write('memset(TR, 0, __nn*__markCommons*sizeof(unsigned short));'), nl,
% Run
    write('int __chunker = 0;'), nl,
    write('int __start_block = 0;'), nl,
    write('__n = 0;'), nl,
    write('while (__n < __total)'),nl,
    write('  {'), nl,
    write('    if (__chunker == 0) { __plan_item.init = 1; *Loop'), write(GID), write(' << __plan_item; }'), nl,
    write('    *Loop'), write(GID), write(' << __plan_sorted[__plan_indexes[__n]];'), nl,
    write('    __n++;'), nl,
    write('    if (++__chunker == ('), write(CHUNK), write(')) {'), nl,
    write_starter('       '),
    write('       __start_block = __n;'), nl,
    write('       __chunker = 0;'), nl,
    write('    }'), nl,
    write('  }'), nl,
    write_starter('    '),
% Handling
    (
     =(Pivot, '')->
       true;
       (
        write('std::function<'), write(PivotType), write('(int)> getPivot = [&](int raw_index)->'), write(PivotType), write('{'), nl,
        write('   return raw_index < __working ? __plan_sorted[raw_index].'), write(Pivot), write('[raw_index] : ('),write(PivotType), write(')0;'), nl,
        write('};'), nl,
        write('trace_balancing(np, TraceWNotFound, TraceW, Timings, __total, Winners, WOrder, Besters, TR, TR1, TR2, TR3, Prognosed0, Prognosed1, Prognosed2, getPivot);'), nl
       )
    ),
    !,
  write('}'), nl,
  telling(CurOut),
  told,
  tell('_loop.txt'),
  (\=(OP,'')->make_seq([], CALLS, 0, N, OP, [], TYPE, []);( =(N,0),=(CALLS,[]) )),
  told,
  append(CurOut),
  open('_loop.txt',read,S),
  read_codes(S,LS),
  !,
  atom_codes(Loop,LS),
  close(S),
  !,
  (
   (predicate_property(marks(_,_,_),'dynamic'), marks(GID,_,_))->
     true;
     assertz(marks(GID,ID,N))
  ),
  !,
  make_set(CALLS, SETCALLS),
  (
   (predicate_property(gpu_loop(_,_),'dynamic'), gpu_loop(GID,_))->
     true;
     assertz(gpu_loop(GID,SETCALLS))
  ),
  (
   (predicate_property(blocks(_,_),'dynamic'), blocks(GID,_))->
     true;
     assertz(blocks(GID,loop(Loop,DEVICE,CHUNK,KINDS,TYPES,NAMES,SIZES)))
  ),
  !.
@goal:-
 ( =(LOOP,'')->write_fun;write_loop ), !.
};

#def_module() register_fun(GID, RETTYPE, ID, PARAMS) {
@goal:-brackets_off.
@determ_size(L,R,S):-
  append(Part,[']'|R],L),
  !,
  atom_chars(PP,['('|Part]),
  atom_concat(PP,')',S),
  !.
@determ_sizes([],''):-!.
@determ_sizes([' '|T],A):-
  determ_sizes(T,A),
  !.
@determ_sizes(['['|Rest],B):-
  determ_size(Rest, Rest1, B),
  determ_sizes(Rest1, '').
@determ_sizes(['['|Rest],A):-
  determ_size(Rest, Rest1, B),
  determ_sizes(Rest1, C),
  !,
  atom_concat(B,'*',BB),
  atom_concat(BB,C,A),
  !.
@get_size(SZ,ASZ):-
  atom_chars(SZ, LSZ),
  determ_sizes(LSZ, ASZ),
  !.
@gen_reent_each_param('','','',''):-!.
@gen_reent_each_param([],[],[],[]):-!.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[_|SZZ]):-
  atom_concat('_local',_,K),
  !,
  write(', _local(1) '), write(T), write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[SZ|SZZ]):-
  atom_concat('_pivot',_,K),
  !,
  (=(SZ,'')->
    (write(', _global(1) '), write(T));
    (write(', _global('),get_size(SZ,ASZ),write(ASZ),write(') '), write(T), write(' *'))
  ), !,
  write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([K|TK],[T|TT],[N|NN],[SZ|SZZ]):-
  atom_concat('_global',_,K),
  !,
  (=(SZ,'')->
    (write(', _global(1) '), write(T));
    (write(', _global('),get_size(SZ,ASZ),write(ASZ),write(') '), write(T), write(' *'))
  ), !,
  write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param([''|TK],[T|TT],[N|NN],[_|SZZ]):-
  !,
  write(', '), write(T), write(' '), write(N),
  gen_reent_each_param(TK,TT,NN,SZZ),
  !.
@gen_reent_each_param(K,T,N,S):-
  gen_reent_each_param([K],[T],[N],[S]).
@gen_reent_params(Kinds,Types,Names,Sizes):-
  write('int init, int __markCommons, _local(__planned__.__markCommons) unsigned short * TR'),
  gen_reent_each_param(Kinds,Types,Names,Sizes),
  !.
@insert_prototype([]):-!.
@insert_prototype([block(Gid,loop(B,Device,Chunk,Kinds,Types,Names,Sizes))|T]):-
  write('reenterable['), write(Chunk), write('+1] static Loop'), write(Gid), write('('),gen_reent_params(Kinds,Types,Names,Sizes),write(') {'), nl,
  write('  if (init == 1) {'), nl,
  write('     plan_group_vectorize('), write(Device), write(');'), nl,
  write('  } else if (init == 2) {'), nl,
  write('     plan_undo_locals();'),nl,
  write('  } else {'), nl,
  write(B),
  write('  }'), nl,
  write('}'),
  nl, nl,
  insert_prototype(T),
  !.
@insert_prototype(_):-!.
@build_blocks_list(B):-
  retractall(tempb(_)),
  assertz(tempb([])),
  (
   ( blocks(Gid,X), tempb(BB), retractall(tempb(_)), once(append(BB,[block(Gid,X)],BB1)), assertz(tempb(BB1)), fail );
   true
  ),
  !,
  tempb(B),
  !.
@insert_prototypes(GID):-
  build_blocks_list(Blocks),
  append(_,[block(GID,_)|T],Blocks),
  !,
  insert_prototype(T),
  !.
@write_params(PRMS):-
  atom_chars(PRMS,[_|Rest]),
  !,
  append(R,[_],Rest),
  !,
  atom_chars(PRMS1,R),
  !,
  write(PRMS1).
@goal:-
  (
   (predicate_property(blocks(_,_),'dynamic'), blocks(GID,_))->
     insert_prototypes(GID);
     assertz(blocks(GID,fun))
  ),
  write(RETTYPE), write(' '), write(ID), write('('), write_params(PARAMS), write(')'), nl,
  !.
};

#pragma plan common begin
void RegisterMark(__global unsigned short * C, int idx) {
 C[idx]++;
}
#pragma plan common end

float determ(float a1, float b1, float a2, float b2) {
	return a1*b2 - a2*b1;
}

void GetPredictor(int p, int Iters3, int Iters2, int Iters1, int Iters, float * W1, float * Q) {
	float a1, b1, a2, b2, s1, s2;
	if (p == 3) {
		a1 = Iters3*Iters3 + Iters2*Iters2 + Iters1*Iters1;
		b1 = Iters3 + Iters2 + Iters1;
		a2 = b1;
		b2 = 3;
		s1 = Iters2*Iters3 + Iters1*Iters2 + Iters*Iters1;
		s2 = Iters2 + Iters1 + Iters;
	} else if (p == 2) {
		a1 = Iters2*Iters2 + Iters1*Iters1;
		b1 = Iters2 + Iters1;
		a2 = b1;
		b2 = 2;
		s1 = Iters1*Iters2 + Iters*Iters1;
		s2 = Iters1 + Iters;
	} else if (p == 1) {
		*W1 = 1.0;
		*Q = 0.0;
		return;
	}

	float d = determ(a1, b1, a2, b2);
	if (fabsf(d) < 1E-5) {
		*W1 = 1.0;
		*Q = 0.0;
	} else {
		*W1 = determ(s1, b1, s2, b2) / d;
		*Q = determ(a1, s1, a2, s2) / d;
	}
}

const int __HistorySize = 6;

typedef signed char _WinnersType[__markCommons];
typedef signed char _BestersType[__markCommons];
typedef _WinnersType WinnersType[__HistorySize];
typedef _BestersType BestersType[__HistorySize];

typedef float mnk_vector[__markCommons];
typedef mnk_vector mnk_matrix[__markCommons];

template<class PivotType>
void trace_balancing(
  int np,
  int TraceWNotFound,
  float TraceW[__markCommons],
  float * Timings, /* NN*__HistorySize */
  int NN,
  WinnersType * Winners, /* NN */
  const vector<int> & WOrder,
  BestersType * Besters, /* NN */
  unsigned short * TR, /* NN*__markCommons */
  unsigned short * TR1,/* NN*__markCommons */
  unsigned short * TR2,/* NN*__markCommons */
  unsigned short * TR3,/* NN*__markCommons */
  unsigned short * Prognosed0, /* NN*__markCommons */
  unsigned short * Prognosed1,/* NN*__markCommons */
  unsigned short * Prognosed2,/* NN*__markCommons */
  std::function<PivotType(int raw_index)> getPivot
) {
	float aMNK[__markCommons][__markCommons] = { 0.0f };
	float bMNK[__markCommons] = { 0.0f };
	float gradMNK[__markCommons] = { 0.0f };

	if (TraceWNotFound) {
		#pragma omp parallel for schedule(guided) num_threads(np)
		for (int s = 0; s < __markCommons; s++) {
			for (int j = 0; j < NN; j++) {
				bMNK[s] += getPivot(j)*TR[j*__markCommons + s];
				for (int p = s; p < __markCommons; p++)
					aMNK[s][p] += TR[j*__markCommons + p]*TR[j*__markCommons + s];
			}
		}
		for (int s = 0; s < __markCommons; s++) {
			for (int p = s; p < __markCommons; p++)
				aMNK[p][s] = aMNK[s][p];
		}

		for (int s = 0; s < __markCommons; s++) {
			float pp = fabsf(bMNK[s]);
			for (int p = 0; p < __markCommons; p++) {
				float p1 = fabsf(aMNK[s][p]);
				if (p1 > pp) pp = p1;
			}
			if (pp > 1.0f) {
				for (int p = 0; p < __markCommons; p++)
					aMNK[s][p] /= pp;
				bMNK[s] /= pp;
			}
		}

		for (int k = 0; k < 5; k++) {
			float alpha = 0.0025f;
			float f = 0.0f;
			for (int s = 0; s < __markCommons; s++) {
				float it = -bMNK[s];
				for (int p = 0; p < __markCommons; p++)
					it += aMNK[s][p]*TraceW[p];
				f += it*it;
			}
			for (int j = 0; j < __markCommons; j++) {
				float delta = 0.001f;
				float f1 = 0.0f;

				TraceW[j] += delta;
				for (int s = 0; s < __markCommons; s++) {
					float it = -bMNK[s];
					for (int p = 0; p < __markCommons; p++)
						it += aMNK[s][p]*TraceW[p];
					f1 += it*it;
				}
				TraceW[j] -= delta;
				gradMNK[j] = (f1 - f)/delta;
			}
			for (int s = 0; s < __markCommons; s++)
				TraceW[s] -= alpha*gradMNK[s];
		}
	}

	#pragma omp parallel for schedule(guided) num_threads(np)
	for (int j = 0; j < NN; j++) {
		float f, maxt = 0.000000001f;
		int errs[3];
		short int ks;
		signed char nump;

		for (int k = 0; k < __HistorySize; k++)
                    if (Timings[j*__HistorySize + k] > maxt)
			maxt = Timings[j*__HistorySize + k];

		for (int ks = 0; ks < __markCommons; ks++) {
			unsigned short int buf;

			int k = WOrder[ks];

			errs[0] = abs(Prognosed0[j*__markCommons+k] - TR[j*__markCommons+k]);
			errs[1] = abs(Prognosed1[j*__markCommons+k] - TR[j*__markCommons+k]);
			errs[2] = abs(Prognosed2[j*__markCommons+k] - TR[j*__markCommons+k]);

			if (errs[0] < errs[1])
				if (errs[0] < errs[2])
					nump = 0;
				else
					nump = 2;
			else
				if (errs[2] < errs[1])
					nump = 2;
				else
					nump = 1;

			for (int s = __HistorySize-1; s > 0; s--)
				Besters[j][s][k] = Besters[j][s-1][k];
			Besters[j][0][k] = nump;

			if (ks >= (__markCommons / 4) || fabsf(TraceW[k]) <= 1E-6f) {
				for (int s = __HistorySize-1; s > 0; s--)
					Winners[j][s][k] = Winners[j][s-1][k];
				Winners[j][0][k] = 0;

				Prognosed0[j*__markCommons+k] = Prognosed1[j*__markCommons+k] = Prognosed2[j*__markCommons+k] = TR[j*__markCommons + k];

				buf = TR[j*__markCommons + k];
			} else {
				float Quality[3] = { 0.0f, 0.0f, 0.0f };
				float W1[3];
				float Q[3];

				for (int s = __HistorySize-1; s > 0; s--) {
					char w = Winners[j][s][k];
					float t = Timings[j*__HistorySize + s];
					float d = t > 1E-9f ? maxt/t : maxt/1E-9f;
					if (w == Besters[j][s][k])
						Quality[w] += d;
					else
						Quality[w] -= d;
				}

				if (Quality[0] > Quality[1])
					if (Quality[0] > Quality[2])
						nump = 0;
					else
						nump = 2;
				else
					if (Quality[2] > Quality[1])
						nump = 2;
					else
						nump = 1;

				GetPredictor(
					1, TR3[j*__markCommons+k], TR2[j*__markCommons+k], TR1[j*__markCommons+k], TR[j*__markCommons+k],
					&W1[0], &Q[0]
				);
				f = TR[j*__markCommons+k]*W1[0] + Q[0];
				if (f < 0.0f) Prognosed0[j*__markCommons+k] = 0;
				else Prognosed0[j*__markCommons+k] = (unsigned short int) f;

				GetPredictor(
					2, TR3[j*__markCommons+k], TR2[j*__markCommons+k], TR1[j*__markCommons+k], TR[j*__markCommons+k],
					&W1[1], &Q[1]
				);
				f = TR[j*__markCommons + k]*W1[1] + Q[1];
				if (f < 0.0f) Prognosed1[j*__markCommons + k] = 0;
				else Prognosed1[j*__markCommons + k] = (unsigned short int) f;

				GetPredictor(
					3, TR3[j*__markCommons+k], TR2[j*__markCommons+k], TR1[j*__markCommons+k], TR[j*__markCommons+k],
					&W1[2], &Q[2]
				);
				f = TR[j*__markCommons + k]*W1[2] + Q[2];
				if (f < 0.0f) Prognosed2[j*__markCommons + k] = 0;
				else Prognosed2[j*__markCommons + k] = (unsigned short int) f;

				for (int s = __HistorySize-1; s > 0; s--)
					Winners[j][s][k] = Winners[j][s-1][k];
				Winners[j][0][k] = nump;

				buf = nump == 0 ? Prognosed0[j*__markCommons + k] : (nump == 1 ? Prognosed1[j*__markCommons + k] : Prognosed2[j*__markCommons + k]);
			}
			TR3[j*__markCommons + k] = TR2[j*__markCommons + k];
			TR2[j*__markCommons + k] = TR1[j*__markCommons + k];
			TR1[j*__markCommons + k] = TR[j*__markCommons + k];
			TR[j*__markCommons + k] = buf;
		}
	}
};

#pragma syntax check

#endif
