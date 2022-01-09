#ifndef __TRANSACTED_H__
#define __TRANSACTED_H__

#add_scan(scan_cilk_spawn,scan_cilk_sync)

#def_pattern scan_cilk_spawn => make_spawn(gid(), //OBJID/@Value, //REFERER/@Value, //NPRECONDS/@Value, //PRECONDS/@Value, //FUNID/@Value, //PRMID/@Value, //PRMTAIL/@Value) {
  (((^)|(\;)+|\}|\=|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (
     (\w+)->{OBJID}
     (\-\>|\.\*|\.)->{REFERER}
    )?
    cilk_spawn
    (\s|\\t|\\n)*
    (
      \(
      (\s|\\t|\\n)*
      ((.{1,64})->{NPRECONDS}\,)?=>{Predicates.TBAL($,',')}
      (\s|\\t|\\n)*
      ((.{1,64})->{PRECONDS}\))?=>{Predicates.TBAL($,')')}
    )?
    (\s|\\t|\\n)+
    ([^\(]+)->{FUNID}
    (
     \(
       (
        ((\s|\\t|\\n)*(void(\s|\\t|\\n)*)?\))|
        (
         (\s|\\t|\\n)*((\=)?(\w+))->{PRMID}((.{0,256}(\,|\)))->{PRMTAIL})?=>{Predicates.TBAL($,'),')}
        )+
       )
    )
    (\s|\\t|\\n)*
    \;
  @end
};

#def_pattern scan_cilk_sync => make_sync(gid(), //OBJID/@Value, //REFERER/@Value, //SYNC_CHILDREN/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (
     (\w+)->{OBJID}
     (\-\>|\.\*|\.)->{REFERER}
    )?
    cilk_sync
    (\s|\\t|\\n)*
    (
      \(
      (\s|\\t|\\n)*
      ((.{0,64})->{SYNC_CHILDREN}\))?=>{Predicates.TBAL($,')')}
    )?
    (\s|\\t|\\n)*
    \;
  @end
};

#def_module() make_spawn(GID, OBJID, REFERER, NPRECONDS, PRECONDS, FUNID, PRMID, PRMTAIL) {
@goal:-brackets_off.
@get_non_capture('', ''):-!.
@get_non_capture([], ''):-!.
@get_non_capture([''], ''):-!.
@get_non_capture([Prm|T], C):-
   atom_chars(Prm, ['='|TPrm]),
   !,
   atom_chars(CPrm, TPrm),
   get_non_capture(T, C1),
   (
     =(C1, '')->
      =(C, CPrm);
      ( atom_concat(CPrm, ',', C2), atom_concat(C2, C1, C) )
   ),
   !.
@get_non_capture([_|T], C):-
   get_non_capture(T, C),
   !.
@get_non_capture(A, C):-
   get_non_capture([A], C),
   !.
@get_params('', _, ')'):-!.
@get_params([], _, ''):-!.
@get_params([''], _, ')'):-!.
@get_params([Prm|PrmT], [TAIL|TT], C):-
   (
     atom_chars(Prm, ['='|TPrm])->
       atom_chars(CPrm, TPrm);
       =(CPrm, Prm)
   ),
   !,
   atom_concat(CPrm, TAIL, CX),
   get_params(PrmT, TT, C1),
   atom_concat(CX, C1, C),
   !.
@get_params(A, B, C):-
   get_params([A], [B], C),
   !.
@goal:-
   write('[&] ()->int {'), nl,
   write('  int __id__ = 0;'), nl,
   write('  auto __runner__ = [&'), get_non_capture(PRMID, C),
   (
     =(C, '')->
      true;
      ( write(','), write(C) )
   ),
   !,
   write('] () {'), nl,
   write('    '), write(FUNID), write('('), get_params(PRMID, PRMTAIL, CP), write(CP), write(';'), nl,
   write('  };'), nl,
   write('  '), write(OBJID), write(REFERER), write('join(__runner__, __id__'),
   (
     =(NPRECONDS, '')->
       true;
       ( write(', '), write(NPRECONDS), write(', '), write(PRECONDS) )
   ),
   !,
   write(');'), nl,
   write('  return __id__;'), nl,
   write('} ();'), nl.
};

#def_module() make_sync(GID, OBJID, REFERER, SYNC_CHILDREN) {
@goal:-brackets_off.
@goal:-
   write(OBJID), write(REFERER), write('reinit('), write(SYNC_CHILDREN), write(');'), nl.
};

#endif
