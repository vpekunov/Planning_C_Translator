#ifndef __ATOMIC_COMPILE_H__
#define __ATOMIC_COMPILE_H__

#parse(clsAtomicProgram,clsAtomicSpace,clsAtomicInclude,clsAtomicPreproc,clsAtomicComments,clsAtomicTypedef,clsAtomicCVar,clsAtomicFunction,clsAtomicFor,clsAtomicSwitch,clsAtomicWhile,clsAtomicIf,clsAtomicElse,clsAtomicDo,clsAtomicAlternation,clsAtomicReturn,clsAtomicOper,clsAtomicBegin,clsAtomicEnd,clsAtomicTerminator)

#preproc_passes(1,"_atomic.cpp")

#def_pattern clsAtomicAlternation => [prog] ('clsAtomicAlternation', gid(), /root/TYPE/@Value, [['arg', /root/CASE/@Value]]) {
  (((^)|(\;)+|\}|\{|\\n|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (
     (((case)->{TYPE}(\\n|\s|\\t)+((.+?)->{CASE}\:)?=>{Predicates.BAL($,':')}
          ))|
     (((default)->{TYPE}(\\n|\s|\\t)*\:)
          )
    )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicBegin => [prog] ('clsAtomicBegin', gid(), '{', '') {
  (((^)|(\;)+|\}|\{|\\n|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\{)
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicComments => [comment] ('clsAtomicComments', gid(), /root/CONTENT/@Value) {
  @begin
    ((\/\/([^\\]*)->{CONTENT}(\\n))|(\/\*(.*?)->{CONTENT}\*\/))
  @end
};

#def_pattern clsAtomicCVar => [prog] ('clsAtomicCVar', gid(), /root/TYPE/@Value, [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (struct|union)->{TYPE}(\\n|\s|\\t)+
    ((((\w+)?\s*\{.{1,2048}?)->{EXPR}\})?=>{Predicates.BAL($,'}')}\s*\w+\s*\;)
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicDo => [prog] ('clsAtomicDo', gid(), 'do', '') {
  (((^)|(\;)+|\}|\{|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (do)
  @end
  (\s|\\t)*
  ((\s|\{|\\n|\\t))
  (\s|\\t)*
};

#def_pattern clsAtomicElse => [prog] ('clsAtomicElse', gid(), 'else', '') {
  (((\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (else)
  @end
  (\s|\\t)*
  (\s|\{|\\n|\\t)
  (\s|\\t)*
};

#def_pattern clsAtomicEnd => [prog] ('clsAtomicEnd', gid(), '}', '') {
  (((\;)+|\}|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ()->{GID}
    (\s|\\t)*
    (\})
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicFor => [prog] ('clsAtomicFor', gid(), 'for', [['init', /root/INITF/@Value],['init', /root/INITN/@Value],['cond', /root/COND/@Value],['chng', /root/CHNGF/@Value],['chng', /root/CHNGN/@Value]]) {
  (((^)|(\;)+|\}|\)|\{|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (for(\s|\\t)*\(
           (\\n|\s|\\t)*((([^;]{1,300}?)->{INITF}\,)?=>{Predicates.BAL($,',')}
              )*
              ((([^;]{0,300}?)->{INITN}\;)?=>{Predicates.BAL($,';')}
              )
           (\\n|\s|\\t)*((([^;]{0,300}?)->{COND}\;)?=>{Predicates.BAL($,';')}
              )
           (\\n|\s|\\t)*((([^;]{1,300}?)->{CHNGF}\,)?=>{Predicates.BAL($,',')}
              )*
              ((([^\)]{0,300}?)->{CHNGN}\))?=>{Predicates.BAL($,')')}
              )
        )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicFunction => [prog] ('clsAtomicFunction', gid(), 'func', [['arg', //FIRST_REF/@Value], ['type', //FIRST_TYPE/@Value], ['arg', //FIRST/@Value], ['idxs', //FIRST_IDXS/@Value], ['arg', //OTHER_REF/@Value], ['type', //OTHER_TYPE/@Value], ['arg', //OTHER/@Value], ['idxs', //OTHER_IDXS/@Value], ['arg', //THREEP/@Value], ['args', /root/ARGS/@Value], ['ret', /root/RETTYPE/@Value], ['name', /root/ID/@Value]]) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    ((([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{RETTYPE}(\w+(\\n|\s|\\t)*)->{ID}\(
         (
          ((((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+)->{FIRST_TYPE}
            (
             ((\\n|\s|\\t)*(\&|(\*)+)->{FIRST_REF}
             )|
             (\\n|\s|\\t)+()->{FIRST_REF}
            )
            (\\n|\s|\\t)*(\w+)->{FIRST}(((\\n|\s|\\t)*\[(\\n|\s|\\t)*\w+(\\n|\s|\\t)*\])*)->{FIRST_IDXS}
            ((\\n|\s|\\t)*\,(((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+)->{OTHER_TYPE}
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
  @end
  (\{|\;)
};

#def_pattern clsAtomicIf => [prog] ('clsAtomicIf', gid(), 'if', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (if(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicInclude => [include] ('clsAtomicInclude', gid(), /root/FILE/@Value) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#include(\s|\\t)*\x22([^\x22]+)->{FILE}\x22(\\n|($))
    )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicOper => [prog] ('clsAtomicOper', gid(), 'op', [['op', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    ((([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicPreproc => [prog] ('clsAtomicPreproc', gid(), 'preproc', [['body', /root/BODY/@Value]]) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#
       ((include\s*\<[^\>]+\>\s*)|([^\\]*\\\\\\n)*[^\\]*)(\\n|($))
    )->{BODY}
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicReturn => [prog] ('clsAtomicReturn', gid(), 'return', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (return(\\n|\s|\\t)+(([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
    )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicSwitch => [prog] ('clsAtomicSwitch', gid(), 'switch', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (switch(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{EXPR}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicTypedef => [prog] ('clsAtomicTypedef', gid(), 'type', [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\)|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    typedef((\\n|\s|\\t)+)
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicWhile => [prog] ('clsAtomicWhile', gid(), 'while', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (while(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsAtomicTerminator => atomic_parallelize (gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() atomic_parallelize(AfterLastID) {
@goal:-brackets_off.

% #pragma auto pure(fun1,fun2,...) -- обозначает функции без сторонних эффектов
% #pragma auto split(auto|(var1[N1],var2[N1][N2],var3,...)) [omp-params] -- помечает цикл как потенциально параллелизуемый расщеплением
% split_private type var-decl -- помечает переменную как локальную при распараллеливании циклов. Такие переменные попадают в private-пометки,
%   если они не указаны явно
% #pragma auto parallelize -- распараллеливает циклы, насколько возможно

@read_string(S,V):-
  peek_char(S,'"'),
  get_char(S,'"'),
  (
    peek_char(S,'"')->(
      get_char(S,'"'),
      read_string(S,V1),
      atom_concat('"',V1,V)
    );(
      =(V,'')
    )
  ),
  !.

@read_string(S,V):-
  get_char(S,C),
  read_string(S,V1),
  atom_concat(C,V1,V),
  !.

@read_val(S,''):-
  peek_char(S,','),
  !.

@read_val(S,''):-
  (peek_char(S,'\r'),get_char(S,'\r'); true),
  peek_char(S,'\n'),
  !.

@read_val(S,V):-
  peek_char(S,'"'),
  get_char(S,'"'),
  read_string(S,V1),
  read_val(S,V2),
  atom_concat(V1,V2,V),
  !.

@read_val(S,V):-
  get_char(S,C),
  read_val(S,R),
  atom_concat(C,R,V),
  !.

@unescapel([],[]):-!.

@unescapel(['\\', '\\'|T],['\\'|T1]):-
  unescapel(T,T1).

@unescapel(['\\', 'n'|T],['\n'|T1]):-
  unescapel(T,T1).

@unescapel(['\\', 't'|T],['\t'|T1]):-
  unescapel(T,T1).

@unescapel([H|T],[H|T1]):-
  unescapel(T,T1).

@unescape(Itoc,Otoc):-
  atom_chars(Itoc,L),
  unescapel(L,L1),
  atom_chars(Otoc,L1),
  !.

@db_line(_,_,0,[[]]):-!.

@db_line(First,S,N,[[H|T]]):-
  (=(First,'+')->read_token(S,','); true),
  !,
  N1 is N-1,
  !,
  read_val(S,TOC0),
  unescape(TOC0,TOC),
  (
   =(TOC,',')->(
     =(H,''),
     db_line('-',S,N1,[T])
   );(
     =(H,TOC),
     db_line('+',S,N1,[T])
   )
  ).

@db_find(S,GID,NC,L):-
  read_token(S,CurID),
  number(CurID),
  (
   =(GID,CurID)->(
     db_line('+',S,NC,L0)
   );(
     db_line('+',S,NC,_),
     =(L0,[])
   )
  ),
  !,
  db_find(S,GID,NC,L1),
  append(L0,L1,L),
  !.

@db_find(_,_,_,[]):-!.

@get_db_by_key(FName,GID,NC,L):-
  open(FName,read,S),
  NC1 is NC-1,
  db_find(S,GID,NC1,L),
  close(S).

@db_get(S,Predicate,NC):-
  read_token(S,CurID),
  number(CurID),
  db_line('+',S,NC,L0),
  !,
  (
   predicate_property(db_content(_,_,_),'dynamic'), db_content(Predicate,CurID,LL)->(
     retract(db_content(Predicate,CurID,_)),
     append(LL,L0,L1),
     assertz(db_content(Predicate,CurID,L1))
   );(
     assertz(db_content(Predicate,CurID,L0))
   )
  ),
  db_get(S,Predicate,NC),
  !.

@db_get(_,_,_):-!.

@into_paired_list_f(_, [], []).

@into_paired_list_f(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(into_paired_list_f(TYPE, T, LL)).

@into_paired_list_f(TYPE, V, [[TYPE, V]]).

@strip_list_f([[type,''], [arg,''], [idxs,'']], []).

@strip_list_f(L, L).

@into_paired_list(_, '', []).

@into_paired_list(_, [], []).

@into_paired_list(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(into_paired_list(TYPE, T, LL)).

@into_paired_list(TYPE, V, [[TYPE, V]]).

@make_arg(TYPE, F, N, L):-
  once(into_paired_list(TYPE, F, L1)),
  once(into_paired_list(TYPE, N, L2)),
  append(L1, L2, L).

@make_fargs([], [], [], [], []).

@make_fargs([['arg','']|REFT],[TP|TPT],[NM|NMT],[IDXS|IDXST], [TP,NM,IDXS|T]):-
  once(make_fargs(REFT, TPT, NMT, IDXST, T)).

@make_fargs([REF|REFT],[TP|TPT],[NM|NMT],[IDXS|IDXST], [REF,TP,NM,IDXS|T]):-
  once(make_fargs(REFT, TPT, NMT, IDXST, T)).

@analyze_args(_, _, '').

@analyze_args(GID, _, [[Name, Val]]):-
  asserta(db_content('args', GID, [[Name, Val]])).

@analyze_args(GID, 'for', [['init',INITF], ['init',INITN], ['cond',COND], ['chng',CHNGF], ['chng',CHNGN]]):-
  once(make_arg('init', INITF, INITN, L1)),
  once(make_arg('chng', CHNGF, CHNGN, L2)),
  append(L1, [['cond',COND]], L3),
  append(L3, L2, L4),
  asserta(db_content('args', GID, L4)).

@analyze_args(GID, 'func', [['arg',REF1], ['type',TYPE1], ['arg',NM1], ['idxs',IDXS1], ['arg',REFN], ['type',TYPEN], ['arg',NMN], ['idxs',IDXSN], ['arg',THREEP], ARGSV, RETV, NAMEV]):-
  once(into_paired_list_f('arg', REF1, REF1L)),
  once(into_paired_list_f('type', TYPE1, TYPE1L)),
  once(into_paired_list_f('arg', NM1, NM1L)),
  once(into_paired_list_f('idxs', IDXS1, IDXS1L)),
  once(make_fargs(REF1L, TYPE1L, NM1L, IDXS1L, L1)),
  once(strip_list_f(L1, L11)),
  once(into_paired_list_f('arg', REFN, REFNL)),
  once(into_paired_list_f('type', TYPEN, TYPENL)),
  once(into_paired_list_f('arg', NMN, NMNL)),
  once(into_paired_list_f('idxs', IDXSN, IDXSNL)),
  once(make_fargs(REFNL, TYPENL, NMNL, IDXSNL, L2)),
  once(strip_list_f(L2, L22)),
  append(L11, L22, LM),
  once((
    =(THREEP, '...')->
     append(LM, [['arg', '...']], LK);
     =(LK, LM)
  )),
  append(LK, [ARGSV, RETV, NAMEV], LL),
  asserta(db_content('args', GID, LL)).

@read_db:-
  prog(_, GID, TYPE, ARGS),
  number_atom(NGID, GID),
  asserta(db_content('prog', NGID, [[TYPE]])),
  analyze_args(NGID, TYPE, ARGS),
  fail.

@read_db:-
  !.

@number_sym(C):-
  member(C, ['0','1','2','3','4','5','6','7','8','9']),
  !.

@ident_first_sym(C):-
  member(C, ['_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']),
  !.

@ident_other_sym(C):-
  (
   ident_first_sym(C) -> true; number_sym(C)
  ),
  !.

@find_ident2([Sym|Tag], Id, Rest):-
  ident_other_sym(Sym),
  find_ident2(Tag, TId, Rest),
  atom_concat(Sym, TId, Id),
  !.
@find_ident2(L, '', L):-!.

@find_ident([Sym|Tag], Id, Rest):-
  ident_first_sym(Sym),
  !,
  find_ident2(Tag, S, Rest),
  atom_concat(Sym, S, Id),
  !.

@find_intn([Sym|Tag], Num, Rest):-
  number_sym(Sym),
  find_intn(Tag, TNum, Rest),
  atom_concat(Sym, TNum, Num),
  !.
@find_intn(L, '', L):-!.

@find_int2([Sym|Tag], Num, Rest):-
  number_sym(Sym),
  find_intn([Sym|Tag], Num, Rest),
  !.

@find_int([Sym|Tag], Num, Rest):-
  number_sym(Sym),
  find_ident2(Tag, T, Rest),
  atom_concat(Sym, T, Num),
  !.

@find_real(L, Num, Rest):-
  find_int2(L, _, R1),
  (append(['.'], R2, R1), find_int2(R2, _, R3); =(R3, R1)),
  (append(['E'], R4, R3); append(['e'], R4, R3)),
  !,
  (append(['+'], R5, R4); append(['-'], R5, R4); =(R5, R4)),
  !,
  find_ident2(R5, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@find_real(L, Num, Rest):-
  find_int2(L, _, R1),
  append(['.'], R2, R1),
  find_ident2(R2, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@parse_string(_,[], [], []):-!,fail.

@parse_string(Delim, [Delim,Delim|T], [Delim|S1], Rest):-
  parse_string(Delim, T, S1, Rest),
  !.

@parse_string(Delim, [Delim|T], [], T):-
  !.

@parse_string(Delim, [H|T], [H|S1], R):-
  parse_string(Delim, T, S1, R),
  !.

@parse_expr2([], []):-!.

@parse_expr2([First|RR], L):-
  member(First, [' ', '\t', '\n', '\r']),
  parse_expr2(RR, L).

@parse_expr2(CL, L):-
  append(['\\', '\\', 'n'], RR, CL),
  parse_expr2(RR, L).

@parse_expr2(CL, L):-
  append(['\\', '\\', 't'], RR, CL),
  parse_expr2(RR, L).

@parse_expr2(['"'|RR], [dstring(H)|T]):-
  parse_string('"', RR, HH, Rest),
  atom_chars(H,HH),
  parse_expr2(Rest, T).

@parse_expr2(['/','*'|RR], T):-
  append(_,['*','/'|Rest],RR),
  !,
  parse_expr2(Rest, T).

@parse_expr2([''''|RR], [cstring(H)|T]):-
  parse_string('''', RR, HH, Rest),
  atom_chars(H,HH),
  parse_expr2(Rest, T).

@parse_expr2(CL, [H|T]):-
  append([First], RR, CL),
  (
   ident_other_sym(First)->(
    (
     (find_real(CL, HH, R),
      =(H, real(HH)));
     (find_int(CL, HH, R),
      =(H, integ(HH)));
     (find_ident(CL, HH, R),
      =(H, id(HH)))
    ),
    !,
    parse_expr2(R, T)
   );(
     =(H, First),
     !,
     parse_expr2(RR, T)
   )
  ),
  !.

@parse_expr(S,L):-
  atom_chars(S,CL),
  parse_expr2(CL, L).

@get_balanced(Depth,['('|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  get_balanced(Depth1,T,Delims,BAL0,[')'|R0]),
  get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['('|BAL0],[')'|BAL1],BAL),
  !.

@get_balanced(Depth,['['|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  get_balanced(Depth1,T,Delims,BAL0,[']'|R0]),
  get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['['|BAL0],[']'|BAL1],BAL),
  !.

@get_balanced(Depth,['{'|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  get_balanced(Depth1,T,Delims,BAL0,['}'|R0]),
  get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['{'|BAL0],['}'|BAL1],BAL),
  !.

@get_balanced(Depth,[H|T],_,[],[H|T]):-
  \+ =(Depth,0),
  member(H,[')',']','}']),
  !.

@get_balanced(Depth,[H|T],Delims,[],[H|T]):-
  =(Depth,0),
  member(H,Delims),
  !.

@get_balanced(Depth,[H|T],Delims,[H|T1],Rest):-
  get_balanced(Depth,T,Delims,T1,Rest),
  !.

@get_balanced(0,[],_,[],[]):-!.

@get_balanced(_,[],_,_,_):-!,fail.

@union([H|T], L, L1):-
  member(H, L),
  union(T, L, L1),
  !.
@union([H|T], L, [H|T1]):-
  union(T, L, T1),
  !.
@union([], L, L):-!.

@intersect([], _, []):-!.

@intersect(_, [], []):-!.

@intersect([H|T],V,[H|T1]):-
   member(H,V),
   !,
   subtract(V,[H],V1),
   !,
   intersect(T,V1,T1),
   !.

@intersect([_|T],V,T1):-
   intersect(T,V,T1).

@unique([],[]):-!.

@unique([H|T],L):-
   append(Left,[H|Right],T),
   append(Left,Right,T1),
   !,
   unique([H|T1],L),
   !.

@unique([H|T],[H|T1]):-
   unique(T,T1),
   !.

@bypass_idxs(['['|T],T1,INS,OUTS,FUNS,Lazies):-
   get_balanced(0,T,[']'],EXPR,[']'|T0]),
   get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   bypass_idxs(T0,T1,INS1,OUTS1,FUNS1,LZ1),
   union(INS0,INS1,INS), union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), union(LZ0,LZ1,Lazies),
   !.

@bypass_idxs(L,L,[],[],[],[]):-!.

@rbypass_idxs(L,L1,INS,OUTS,FUNS,Lazies):-
   last(L,']'),
   !,
   append(Left1,['['|Right1],L),
   get_balanced(0,Right1,[']'],EXPR,[']']),
   get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   rbypass_idxs(Left1,L1,INS1,OUTS1,FUNS1,LZ1),
   union(INS0,INS1,INS), union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), union(LZ0,LZ1,Lazies),
   !.

@rbypass_idxs(L,L,[],[],[],[]):-!.

@rbypass_var(L,V,R,[],[],[],[]):-
   append(R,['(','*',id(V),')'],L).

@rbypass_var(L,V,R,[],[],[],[]):-
   append(R,['(',id(V),')'],L).

@rbypass_var(L,V,R,INS,OUTS,FUNS,Lazies):-
   rbypass_idxs(L,R0,INS0,OUTS0,FUNS0,LZ0),
   append(Left,[id(VV)],R0),
   !,
   (
    ( append(Left1,['.'],Left); append(Left1,['-','>'],Left) )->
     (
      rbypass_var(Left1,V,R,INS1,OUTS1,FUNS1,LZ1),
      union(INS0,INS1,INS), union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), union(LZ0,LZ1,Lazies)
     );
     (=(V,VV),=(R,Left),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0))
   ),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['<','<','='|Right],L),
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['>','>','='|Right],L),
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,[A,'='|Right],L),
   member(A,['+','-','*','/','|','&','^','%']),
   !,
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],Ins,Funs,Lazs):-
   append(Left,['='|Right],L),
   last(Left,A),
   \+ member(A,['=','!','<','>']),
   \+ =(Right,['='|_]),
   !,
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+'|Right],L),
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-'|Right],L),
   rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+',id(V)|Right],L),
   bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-',id(V)|Right],L),
   bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   union(OUTST1,OUTST2,OUTST3), union(OUTST3,Outs0,OUTST),
   union(Ins1,Ins2,Ins3), union(Ins3,Ins0,Ins),
   union(Funs1,Funs2,Funs3), union(Funs3,Funs0,Funs),
   union(Laz1,Laz2,Laz3), union(Laz3,Laz0,Lazs),
   !.

@get_assgns(L,Outs,Ins,Funs,Lazs):-
   get_vars(L,Ins,Outs,Funs,Lazs),
   !.

@bypass_var([id(_)|T],R,INS,OUTS,FUNS,Lazies):-
   bypass_idxs(T,R0,INS0,OUTS0,FUNS0,LZ0),
   (
    ( =(['.'|R1],R0); =(['-','>'|R1],R0) )->
     (
      bypass_var(R1,R,INS1,OUTS1,FUNS1,LZ1),
      union(INS0,INS1,INS), union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), union(LZ0,LZ1,Lazies)
     );(
      =(R,R0),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0)
     )
   ),
   !.

@glob_prefixate([],[]):-!.

@glob_prefixate([var(H,TP)|T],[global(H,TP)|T1]):-
   glob_prefixate(T,T1).

@get_glob_lazies(Fun,NPrms,GP,LP,ILP):-
   atomic_function(Fun,GID,NPrms),
   predicate_property(atomic_fanalyzed(_,_,_,_,_),'dynamic'),
   atomic_fanalyzed(Fun,GID,Globs,LP,ILP),
   glob_prefixate(Globs, GP),
   !.

@get_glob_lazies(_,_,[],0,[]):-!.

@get_ftime(Fun,NPrms,T):-
   atomic_function(Fun,GID,NPrms),
   predicate_property(atomic_ftime(_,_,_),'dynamic'),
   atomic_ftime(Fun,GID,T),
   !.

@get_ftime(_,_,T):-  % Содержит время исполнения функции по умолчанию
  g_read('$DefFTime',T),
  !.

@put_ftime(Fun,NPrms,T):-
   atomic_function(Fun,GID,NPrms),
   (
    (predicate_property(atomic_ftime(_,_,_),'dynamic'), atomic_ftime(Fun,GID,T0))->(
         D is T-T0,
         (
          ;(<(D,-1),>(D,1))->(
             retractall(atomic_ftime(Fun,GID,_)),
             asserta(atomic_ftime(Fun,GID,T)),
             retractall(atomic_retime),
             asserta(atomic_retime)
            );
            true
         )
       );(
         retractall(atomic_retime),
         asserta(atomic_retime),
         asserta(atomic_ftime(Fun,GID,T))
       )
   ),
   !.

@put_ltime(GID,T):-
   (
    (predicate_property(atomic_splitted(_,_),'dynamic'), atomic_splitted(GID,_))->
      (
       (predicate_property(atomic_ltime(_,_),'dynamic'), atomic_ltime(GID,T0))->(
            D is T-T0,
            (
             ;(<(D,-1),>(D,1))->(
                retractall(atomic_ltime(GID,_)),
                asserta(atomic_ltime(GID,T)),
                retractall(atomic_retime),
                asserta(atomic_retime)
               );
               true
            )
          );(
            retractall(atomic_retime),
            asserta(atomic_retime),
            asserta(atomic_ltime(GID,T))
          )
      );
      true
   ),
   !.

@getTime([],T):-
   g_read('$DefOperTime', T),
   !.

@getTime([V|T],TM):-
   =..(V,[_,F,Prms]),
   length(Prms,N),
   get_ftime(F,N,T0),
   getTime(T,T1),
   TM is T0+T1,
   !.

@extract_singles([],[]):-!.

@extract_singles([[]|T],L):-
  extract_singles(T,L),
  !.

@extract_singles([[V]|T],[V|L]):-
  extract_singles(T,L),
  !.

% Анализ вызова функций на предмет наличия ленивых переменных (модифицируемых глобальных и модифицируемых &|*-параметров)
% Если уже есть результаты предварительного анализа в фактах atomic_fanalyzed, то данные о "ленивости" берутся из них, если же их
% нет, то считается, что глобальных ленивых переменных для этой функции нет, а ленивыми являются все &|*-параметры
% Во втором параметре принимает список разобранных параметров, каждый из которых = список токенов
% В третьем параметре возвращает список ленивых переменных [global(имя,тип),...,par(функция,имя_параметра,переданная переменная),...]
% В четвертом параметре возвращается список имен, переданных в неленивые &|* - параметры
% В пятом параметре принимается список-карта переданных значений. Элемент = множество из одного элемента (имя переданной переменной)
%  или пустое множество (если в параметре передано выражение).
% В шестом параметре возвращается список имен переданных в качестве параметров переменных, значения которых используются на чтение в функции
@get_lazies(Fun, [], GP, [], _, []):-
     get_glob_lazies(Fun,0,GP,_,_),
     !.

@get_lazies(Fun, Params, [], _, ParSingleMap, _):-
   predicate_property(atomic_farg(_,_,_,_,_,_),'dynamic')->(
     length(Params,N),
     once(atomic_farg(Fun,N,_,_,_,_)),
     asserta(counter(0)),
     get_glob_lazies(Fun,N,GP,LP,ReadParams),
     asserta(params(GP)),
     asserta(isingles([])),
     asserta(refs([])),
     atomic_farg(Fun,_,REF,V,_,_),
     once(counter(I)),
     I1 is I+1,
     retract(counter(I)),
     asserta(counter(I1)),
     once(isingles(ISI)),
     once(nth(I1,ParSingleMap,VAL)),
     (
      (=(VAL,[Passed]),once(member(V,ReadParams)))->(
           retract(isingles(ISI)),asserta(isingles([Passed|ISI]))
         );(
           true
         )
     ),
     once(member(REF,['&','*','**','***','[]'])),
     once(;(nth(I1,Params,[id(P)|TT]),nth(I1,Params,['&',id(P)|TT]))),
     bypass_var([id(P)|TT],[],_,_,_,_),
     (
      once(;(=(LP,0),member(V,LP)))->
        true;
        (once(refs(RF)),retract(refs(RF)),asserta(refs([P|RF])))
     ),
     once(params(LZ)),
     retract(params(_)),
     once(append(LZ,[par(Fun,V,P)],LZ1)),
     asserta(params(LZ1)),
     fail
   );(
     fail
   ).

@get_lazies(_, Params, LZ, Refs, _, ISingles):-
   predicate_property(params(_),'dynamic'),
   params(LZ),
   counter(N),
   isingles(ISingles),
   refs(Refs),
   retractall(params(_)),
   retractall(counter(_)),
   retractall(isingles(_)),
   retractall(refs(_)),
   !,
   length(Params,N),
   !.

@get_lazies(_, _, [], [], ParSingleMap, ISingles):-
   extract_singles(ParSingleMap,ISingles),
   !.

@get_fparams(Mode, Fun, NPrms, []):-
   predicate_property(atomic_farg(_,_,_,_,_,_),'dynamic')->(
     once(atomic_farg(Fun,NPrms,_,_,Type,Idxs)),
     asserta(counter(0)),
     asserta(params([])),
     atomic_farg(Fun,_,REF,V,_,_),
     once(counter(I)),
     I1 is I+1,
     retract(counter(I)),
     asserta(counter(I1)),
     (
      =(Mode,lazy)->once(member(REF,['&','*','**','***','[]']));true
     ),
     once(params(LZ)),
     retract(params(_)),
     ( =(Idxs,'[]')->once(=(ParsedIdxs,[]));once(parse_expr(Idxs,ParsedIdxs)) ),
     once(parse_expr(Type,ParsedType)),
     once(append(LZ,[var(V,type(ParsedType,ParsedIdxs))],LZ1)),
     asserta(params(LZ1)),
     fail
   );(
     true,!
   ).

@get_fparams(_, _, NPrms, LZ):-
   predicate_property(params(_),'dynamic'),
   params(LZ),
   counter(NPrms),
   retractall(params(_)),
   retractall(counter(_)),
   !.

@get_fparams(_, _, _, []):-!.

@get_funs(L,[func(F,Params)|T],INS,OUTS,Lazies):-
   append(_,[id(F),'('|Right],L),
   !,
   get_fun_params(F,Right,[')'|Rest],Params,INS0,ParSingleMap,OUTS0,FUNS0,LZZ),
   !,
   get_lazies(F,Params,LZ0,_,ParSingleMap,INSI),
   !,
   get_funs(Rest,FUNS1,INS1,OUTS1,LZ1),
   union(OUTS0,OUTS1,OUTS),
   union(INS0,INS1,INS2), union(INS2,INSI,INS),
   append(FUNS0,FUNS1,T),
   union(LZZ,LZ0,LZ2),
   union(LZ2,LZ1,Lazies),
   !.

@get_funs(_,[],[],[],[]):-!.

@extract_lzv([],[]):-!.

@extract_lzv([par(_,_,V)|T],[V|T1]):-
   extract_lzv(T,T1),
   !.

@extract_lzv([global(V,_)|T],[V|T1]):-
   extract_lzv(T,T1),
   !.

@get_vars([],[],[],[],[]):-!.

@get_vars([id(V),A|T],[V|TT],Outs,FUNS,Lazies):-
   \+ =(A,'('),
   bypass_var([id(V),A|T],T0,INS0,OUTS0,FUNS0,LZ0),
   !,
   get_vars(T0,INS1,OUTS1,FUNS1,LZ1),
   union(INS0,INS1,TT), union(OUTS0,OUTS1,Outs),
   append(FUNS0,FUNS1,FUNS), union(LZ0,LZ1,Lazies).

@get_vars([id(_),'('|T],Ins,Outs,FUNS,Lazies):-
   get_balanced(0,T,[')'],_,[')'|T0]),
   !,
   get_vars(T0,Ins,Outs,FUNS,Lazies).

@get_vars([id(V)],[V],[],[],[]):-
   !.

@get_vars([_|T],INS,OUTS,FUNS,Lazies):-
   get_vars(T,INS,OUTS,FUNS,Lazies).   

@get_expr(L,INS,OUTS,FUNS,Lazies):-
   get_assgns(L,OUTS0,INS0,FUNSV,LZV),!,
   get_funs(L,FUNS0,INS1,OUTS1,LZ0),
   union(INS0,INS1,INS2),
   unique(INS2,INS),
   union(OUTS0,OUTS1,OUTS2),
   unique(OUTS2,OUTS20), !,
   append(FUNS0,FUNSV,FUNS),
   union(LZ0,LZV,LZB),
   unique(LZB,Lazies),
   extract_lzv(Lazies,LaziesV),
   union(OUTS20,LaziesV,OUTSZ),
   unique(OUTSZ,OUTS),
   !.

@check_arg([id(V)|Rest],[V]):-
   bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@check_arg(['&',id(V)|Rest],[V]):-
   bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@check_arg(_,[]):-
   !.

@get_fun_params(_,[')'|R],[')'|R],[],[],[],[],[],[]):-!.

@get_fun_params(Fun,L,R,[P|T],INS,[V|MAP],OUTS,FUNS,Lazies):-
   get_balanced(0,L,[',',')'],P,[','|Rest]),
   get_expr(P,INS1,OUTS1,FUNS1,LZ1),
   ((atomic_function(Fun,_,_),=(OUTS3,[]));check_arg(P,OUTS3)),
   check_arg(P,V),
   !,
   get_fun_params(Fun,Rest,R,T,INS2,MAP,OUTS2,FUNS2,LZ2),
   (
    =(V,[Single])->
      subtract(INS1,[Single],INSQ);
      =(INSQ,INS1)
   ),
   union(INSQ,INS2,INS),
   union(OUTS1,OUTS2,OUTSK), union(OUTSK,OUTS3,OUTS), append(FUNS1,FUNS2,FUNS), union(LZ1,LZ2,Lazies),
   !.

@get_fun_params(Fun,L,[')'|Rest],[Item],INS,[V],OUTS,FUNS,Lazies):-
   get_balanced(0,L,[',',')'],Item,[')'|Rest]),
   get_expr(Item,INS1,OUTS0,FUNS,Lazies),
   ((atomic_function(Fun,_,_),=(OUTS3,[]));check_arg(Item,OUTS3)),
   check_arg(Item,V),
   !,
   (
    =(V,[Single])->
      subtract(INS1,[Single],INS);
      =(INS,INS1)
   ),
   union(OUTS0,OUTS3,OUTS),
   !.

@analyze_item_expr(intros(TP),[id(V)|T],INS,[V|OUTT],[var(V,type(TP,IDXS))],FUNS,[],[],[]):-
   bypass_idxs(T,['='|Rest],INS0,OUTS0,FUNS0,_),
   append(IDXS,['='|Rest],T),
   \+ =(Rest,['='|_]),
   get_expr(Rest,INS1,OUTS1,FUNS1,_),
   !,
   union(INS0,INS1,INSA), union(OUTS0,OUTS1,OUTTA), append(FUNS0,FUNS1,FUNS),
   unique(INSA,INS), unique(OUTTA,OUTT),
   !.

@analyze_item_expr(intros(TP),[id(V)|T],INS,[V|OUTS],[var(V,type(TP,T))],FUNS,[],[],LAZIES):-
   bypass_idxs(T,[],INS,OUTS,FUNS,LAZIES),
   !.

@analyze_item_expr(inits,[id(V),'('|T],INS,OUTS,[],FUNS,[proc(V,L)],REFS,Lazies):-
   get_fun_params(V,T,[')'],L,INS0,ParSingleMap,OUTS0,FUNS,LZ0),
   !,
   get_lazies(V,L,Lazies,Refs0,ParSingleMap,INSI),
   !,
   % get_lazies возвращает ленивые выходные переменные Lazies уже с учетом результатов анализа. Возвращает Refs0 -- переменные
   % в параметрах &|*, не являющиеся выходными. Возвращает INSI -- все входные переменные в параметрах, используемые в функции
   extract_lzv(LZ0,LZV),
   union(OUTS0,LZV,OUTP),
   extract_lzv(Lazies,LaziesV),
   subtract(Refs0,LaziesV,REFS),
   union(OUTP,LaziesV,OUTS2),
   unique(OUTS2,OUTS),
   union(INS0,INSI,INS2), unique(INS2,INS),
   !.

@analyze_item_expr(inits,L,INS,OUTS,[],FUNS,[expr],[],[]):-
   get_expr(L,INS,OUTS,FUNS,_),
   !.

@analyze_list_expr(_,[],[],[],[],[],[],[],[]):-!.

@analyze_list_expr(Mode,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   get_balanced(0,L,[','],Item,Rest),
   (=([','|T],Rest)->true;=(T,Rest)),
   !,
   analyze_item_expr(Mode,Item,INS0,OUTS0,NEWS0,FUNS0,PROCS0,REFS0,LZ0),
   !,
   analyze_list_expr(Mode,T,INS1,OUTS1,NEWS1,FUNS1,PROCS1,REFS1,LZ1),
   union(INS0,INS1,INS2),
   union(OUTS0,OUTS1,OUTS2),
   union(NEWS0,NEWS1,NEWS2),
   append(FUNS0,FUNS1,FUNS),
   union(PROCS0,PROCS1,PROCS2),
   union(REFS0,REFS1,REFS2),
   union(LZ0,LZ1,LZ2),
   !,
   unique(INS2,INS), unique(OUTS2,OUTS), unique(NEWS2,NEWS),
   unique(PROCS2,PROCS), unique(REFS2,REFS), unique(LZ2,Lazies),
   !.

@declaration([id(_)]):-!.

@declaration([id(_)|T]):-
  declaration(T).

% analyze_expr(parsed_list,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES)
% INS -- список переменных, значения которых = входные для выражения
% OUTS -- список переменных, которые в выражении получают значения в результате ПРИСВАИВАНИЙ (простых и совмещенных) и в &-параметрах
%           функций (не ленивых). Ленивая -- только главная функция! Новые переменные выходными НЕ ЯВЛЯЮТСЯ!
% NEWS -- переменные, декларированные в текущем выражении
% FUNS -- список элементов func(V,L) = вызываемых функций с именами V и списками аргументов L
% PROCS -- список элементов proc(V,L) = вызываемых процедур с именами V и списками аргументов L. В норме -- список из одного элемента
% REFS -- список выходных (&,*)-параметров в процедуре, не относящихся к ленивым. Они не получают в такой процедуре значения
% LAZIES -- список потенциально ленивых переменных = выходных (&,*) в процедуре. Не имеет прямого отношения к OUTS, ДОЛЖЕН с ним пересекаться
@analyze_expr([],[],[],[],[],[],[],[]):-!.

@analyze_expr(['*'|Rest],Ins,Outs,News,Funs,Procs,Refs,Lazies):-
   analyze_expr(Rest,Ins,Outs,News,Funs,Procs,Refs,Lazies),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*',id(V1)],L),
   append(D,['*'],DD),
   declaration(D),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*',id(V1)],L),
   append(D,['*','*'],DD),
   declaration(D),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*','*',id(V1)],L),
   append(D,['*','*','*'],DD),
   declaration(D),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['&',id(V1)],L),
   append(D,['&'],DD),
   declaration(D),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(D,[]))],[],[],[],[]):-
   append(D,[id(V1)],L),
   declaration(D),
   !.

@analyze_expr([id(V)],[V],[],[],[],[],[],[]):-
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*',id(V1),A|T1],L),
   declaration(D),
   append(D,['*'],DD),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*',id(V1),A|T1],L),
   declaration(D),
   append(D,['*','*'],DD),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*','*',id(V1),A|T1],L),
   declaration(D),
   append(D,['*','*','*'],DD),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['&',id(V1),A|T1],L),
   declaration(D),
   append(D,['&'],DD),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,[id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros(D),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   analyze_list_expr(inits,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies),
   !.

@get_params_length([], 0):-!.

@get_params_length([[arg,'...']],infinity):-!.

@get_params_length([[idxs,_]|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([[type,_]|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([[arg,'&']|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([[arg,'*']|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([[arg,'**']|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([[arg,'***']|T], N):-
   get_params_length(T,N),
   !.

@get_params_length([_|T], N1):-
   get_params_length(T,N),
   (
    =(N,infinity)->
     =(N1,infinity);
     N1 is N+1
   ),
   !.

@prepare_atomic_function(_,_,[]):-!.

@prepare_atomic_function(Name,N,[[name,Name]|T]):-
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[args,_]|T]):-
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[type,TP],[arg,V],[idxs,Idxs]|T]):-
   \+ atom_length(Idxs,0),
   assertz(atomic_farg(Name,N,'[]',V,TP,Idxs)),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[arg,'&'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'&',V,TP,[])),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[arg,'*'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'*',V,TP,[])),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[arg,'**'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'**',V,TP,[])),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[arg,'***'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'***',V,TP,[])),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_function(Name,N,[[type,TP],[arg,V],[idxs,'']|T]):-
   assertz(atomic_farg(Name,N,'',V,TP,[])),
   !,
   prepare_atomic_function(Name,N,T).

@prepare_atomic_functions:-
   global_trace(TR),
   db_content('prog',GID,[[func]]),
   db_content('args',GID,Params),
   once(append(_,[gid('clsAtomicFunction',GID),gid('clsAtomicBegin',_)|_],TR)),
   member([name,Name],Params),
   get_params_length(Params,N),
   \+ =(N,infinity),
   N1 is N-3, % -args, -ret, -name
   asserta(atomic_function(Name,GID,N1)),
   call(prepare_atomic_function(Name,N1,Params)),write(Params),
   fail.

@prepare_atomic_functions:-!.

@prepare_ifor([],_,[]):-!.

@prepare_ifor([[Type,V]|T],Type,[VAL|TT]):-
   parse_expr(V,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !,
   =..(VAL,[Type,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L]]),
   prepare_ifor(T,Type,TT).

@prepare_ifor([_|T],Type,TT):-
   !,
   prepare_ifor(T,Type,TT).

@prepare_ops(Type,GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   member(Type,['clsAtomicWhile','clsAtomicSwitch','clsAtomicIf','clsAtomicReturn','clsAtomicOper']),
   !,
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

@prepare_ops('clsAtomicAlternation',GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

% (default:) in switch-case
@prepare_ops('clsAtomicAlternation',_,[arg([],[],[],[],[],[],[],[])]):-
   !.

@prepare_ops('clsAtomicFor',GID,OPL):-
   db_content('args',GID,L),
   prepare_ifor(L,'init',OPL1),
   prepare_ifor(L,'cond',OPL2),
   prepare_ifor(L,'chng',OPL3),
   !,
   append(OPL1,OPL2,OPLP), append(OPLP,OPL3,OPL),
   !.

% Помещает в базу факт atomic_op(Class,GID1,GID2,IDs,Ops) только втом случае, если его еще в базе не было,
% или он был, но с другими ops. В последнем случае устанавливается флаг-факт atomic_recalculate. Это требуется
% для нормальной работы итеративной процедуры уточнения состава ленивых переменных/параметров для каждой функции
@put_atomic_op(Class,GID1,GID2,IDs,Ops):-
   (
      (predicate_property(atomic_op(_,_,_,_,_),'dynamic'), atomic_op(Class,GID1,GID2,IDs,Ops1))->(
        =(Ops,Ops1)->(
          true, !
        );(
          retractall(atomic_op(Class,GID1,GID2,_,_)),
          (
           (predicate_property(atomic_reanalyze,'dynamic'), atomic_reanalyze)->(
             true, !
           );(
             asserta(atomic_reanalyze)
           )
          ),
          asserta(atomic_op(Class,GID1,GID2,IDs,Ops))
        )
      );(
        asserta(atomic_op(Class,GID1,GID2,IDs,Ops))
      )
   ),
   !.

@get_atomic_fseq([gid('clsAtomicEnd',GID)|Rest],[gid('clsAtomicEnd',GID)|Rest],[]):-!.

@get_atomic_fseq(L,Rest,[GID|IDT]):-
   get_atomic_fop(L,Rest0,GID),
   !,
   get_atomic_fseq(Rest0,Rest,IDT),
   !.

@get_atomic_fop([gid('clsAtomicBegin',GID1)|T],Rest,GID1):-
   get_atomic_fseq(T,[gid('clsAtomicEnd',GID2)|Rest],IDs),
   !,
   put_atomic_op('clsAtomicBegin',GID1,GID2,IDs,[]),
   !.

@get_atomic_fop([gid(Type,GID)|T],Rest,GID):-
   member(Type,['clsAtomicFor','clsAtomicSwitch','clsAtomicWhile']),
   !,
   get_atomic_fop(T,Rest,OPID),
   !,
   prepare_ops(Type,GID,OPL),
   put_atomic_op(Type,GID,-1,[OPID],OPL),
   !.

@get_atomic_fop([gid('clsAtomicDo',GID)|T],Rest,GID):-
   get_atomic_fop(T,[gid('clsAtomicWhile',GID1),gid('clsAtomicOper',EmptyGID)|Rest],OPID),
   db_content('args',EmptyGID,[[op,'']]),
   !,
   prepare_ops('clsAtomicWhile',GID1,OPL),
   put_atomic_op('clsAtomicDo',GID,GID1,[OPID],OPL),
   !.

@get_atomic_fop([gid('clsAtomicIf',GID)|T],Rest,GID):-
   get_atomic_fop(T,Rest0,OPID0),
   !,
   prepare_ops('clsAtomicIf',GID,OPL),
   (
    =(Rest0,[gid('clsAtomicElse',GID1)|Rest1])->(
       get_atomic_fop(Rest1,Rest,OPID1),
       put_atomic_op('clsAtomicIf',GID,GID1,[OPID0,OPID1],OPL)
    );(
       put_atomic_op('clsAtomicIf',GID,-1,[OPID0],OPL),
       =(Rest,Rest0)
    )
   ),
   !.

@get_atomic_fop([gid('clsAtomicPreproc',GID)|T],T,GID):-
   put_atomic_op('clsAtomicPreproc',GID,-1,[],[]),
   !.

@get_atomic_fop([gid(Type,GID)|T],T,GID):-
   prepare_ops(Type,GID,OPL),
   put_atomic_op(Type,GID,-1,[],OPL),
   !.

@get_atomic_fprocs([],[]):-!.

@get_atomic_fprocs([GID|T],[GID|TT]):-
   atomic_op('clsAtomicOper',GID,_,[],[arg(_,_,_,_,[proc(Name,_)],_,_,_)]),
   atomic_function(Name,_,_),
   !,
   get_atomic_fprocs(T,TT),
   !.
   
@get_atomic_fprocs([GID|T],PGIDS):-
   atomic_op(_,GID,_,LGIDs,_),
   !,
   get_atomic_fprocs(LGIDs,PGIDS0),
   get_atomic_fprocs(T,PGIDS1),
   !,
   append(PGIDS0,PGIDS1,PGIDS),
   !.

@build_atomic_function(Fun,FGID,Body):-
   get_atomic_fop(Body,[],OPID),
   put_atomic_op('clsAtomicFunction',FGID,-1,[OPID],[]),
   get_atomic_fprocs([OPID],ProcsGIDs),
   asserta(atomic_fprocs(Fun,FGID,ProcsGIDs)),
   !.

% Анализ (структурный, в глубину) всех функций с разбором выражений, результаты которого попадают в atomic_op
@build_atomic_functions:-
   global_trace(TR),
   retractall(atomic_fprocs(_,_,_)),
   !,
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Fun,GID,_),
      once(append(_,[gid('clsAtomicFunction',GID)|T],TR)),
      bypass_complex(T,Body,_),
      call(build_atomic_function(Fun,GID,Body)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@get_globals([],[]):-!.

@get_globals([gid('clsAtomicCVar',GID)|T],[var(V,type(TP,IDXS))|T1]):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   rbypass_var(L,V,TP,_,_,_,_),
   append(TP,[id(V)|IDXS],L),
   get_globals(T,T1).

@get_globals([gid('clsAtomicOper',GID)|T],T1):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   analyze_expr(L,_,_,NEWS,_,_,_,_),
   get_globals(T,T0),
   append(NEWS,T0,T1),
   !.

@get_globals([gid('clsAtomicFunction',_)|T],T1):-
   bypass_complex(T,_,After),
   get_globals(After,T1),
   !.

@get_globals([_|T],T1):-
   get_globals(T,T1).

@find_globals:-
   global_trace(TR),
   get_globals(TR,GLOBS),
   asserta(atomic_globals(GLOBS)),
   !.

@addLocals([],News,[News]):-!.

@addLocals([L|T],News,[L1|T]):-
   append(L,News,L0),
   !,
   unique(L0,L1),
   !.

@excludeLocals(V,[],V):-!.

@excludeLocals(Vars,[Locs|T],Outs):-
   subtract(Vars,Locs,Vars0),
   excludeLocals(Vars0,T,Outs),
   !.

@getNewInOutLazies([],[],[],[],[],0.0):-!.

@getNewInOutLazies([V|T],News,Ins,Outs,Lazies,TM):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,_,_,Laz0,_]),
   getTime(Funs0,T0),
   getNewInOutLazies(T,News1,Ins1,Outs1,Laz1,T1),
   !,
   append(News0,News1,News2), append(Outs0,Outs1,Outs2), append(Laz0,Laz1,Laz2), append(Ins0,Ins1,Ins2),
   unique(News2,News), unique(Outs2,Outs), unique(Laz2,Lazies), unique(Ins2,Ins),
   TM is T0+T1,
   !.

@extract_var_names([],[]):-
   !.

@extract_var_names([var(Name,_)|T],[Name|T1]):-
   extract_var_names(T,T1),
   !.

@analyze_one_flazies([],_,_,_,[],[],[]):-!.

% ReadParams -- читаемые в самой функции ее ленивые параметры (не только выходные, но и входные)
@analyze_one_flazies([GID|GIDS],Globs,Pars,Locals,GLazies,PLazies,ReadParams):-
   atomic_op(_,GID,_,IGIDs,Ops),
   getNewInOutLazies(Ops,News,Ins,Outs,_,_),
   addLocals(Locals,News,Locals1),
   excludeLocals(Outs,Locals1,PreOuts),
   excludeLocals(Ins,Locals1,PreIns),
   intersect(PreOuts,Pars,PLA),
   intersect(PreIns,Pars,ILA),
   subtract(PreOuts,PLA,PreOuts1),
   intersect(PreOuts1,Globs,GLA),
   analyze_one_flazies(IGIDs,Globs,Pars,[News|Locals],GL0,PL0,IL0),
   analyze_one_flazies(GIDS,Globs,Pars,Locals1,GL1,PL1,IL1),
   append(GL0,GL1,GL2), append(GL2,GLA,GL3), append(PL0,PL1,PL2), append(PL2,PLA,PL3),
   append(IL0,IL1,IL2), append(IL2,ILA,IL3),
   unique(GL3,GLazies), unique(PL3,PLazies), unique(IL3,ReadParams),
   !.

@analyze_flazies(Fun,NPrms,GLazies,PLazies,ReadParams):-
   atomic_function(Fun,GID,NPrms),
   !,
   (
    (predicate_property(atomic_fanalyzed(_,_,_,_,_),'dynamic'), atomic_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams))->(
     true,!
     );(
     get_fparams(lazy,Fun,NPrms,LPars0),
     !,
     atomic_globals(GlobVars),
     extract_var_names(GlobVars,Glob0),
     !,
     asserta(atomic_fanalyzed(Fun,GID,[],LPars0,LPars0)),
     analyze_one_flazies([GID],Glob0,LPars0,[],GLazies,PLazies,ReadParams),
     retractall(atomic_fanalyzed(Fun,GID,[],_,_)),
     asserta(atomic_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams)),
     !
    )
   ).

% Определение выходных переменных (глобальных и потенциально модифицируемых параметров) для каждой функции. Для этого проводится
% структурный анализ функции в глубину (с отслеживанием локально декларированных переменных, изменение которых нас здесь не интересует),
% выявляются модифицируемые переменные. Модифицируемые глобалы и параметры попадают в atomic_fanalyzed
@analyze_atomic_functions:-
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Fun,_,N),
      call(analyze_flazies(Fun,N,_,_,_)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Итерационное сходящееся уточнение состава ленивых переменных/параметров функций (atomic_fanalyzed). На каждой итерации
% для каждой функции уточняется список модифицируемых глобальных переменных и &|*-параметров. Это делается в analyze_atomic_functions.
% Это уточнение может влиять на другие функции, вызывающие уточненные. Сначала считается, что функция модифицирует все свои &|*-параметры,
% они входят в соответствующие списки atomic_fanalyzed, потом эти списки урезаются, в то время как списки глобальных переменных расщиряются.
% Проходит "волна" уточнений, в результате которой, например, функции int p1(int &x) { p2(x); }, int p2(int & x) { cout << x; } в последнем
% приближении уже не имеют выходных ленивых значений вообще, в то время как функции int p1() { p2(); }, int p2() { X = 11; } имеют один
% ленивый результат -- глобальную переменную X.
% После оередного уточнения, выполняется перестройка atomic_op-фактов, в которых выполняется новый разбор выражений с учетом новых данных
% о ленивости. Если при этом изменится хоть один факт, то устанавливается atomic_reanalyze, что свидетельствует о необходимости как минимум
% еще одной итерации.
@iterative_build_funs:-
   retractall(atomic_reanalyze),
   build_atomic_functions,
   (
    (predicate_property(atomic_reanalyze,'dynamic'), atomic_reanalyze)->(
      retractall(atomic_fanalyzed(_,_,_,_,_)),
      analyze_atomic_functions,
      iterative_build_funs,
      !
    );(
      true, !
    )
   ),
   !.

@extract_idx(['-','>',id(_)|Rest],EXPR):-
   extract_idx(Rest,EXPR),
   !.

@extract_idx(['.',id(_)|Rest],EXPR):-
   extract_idx(Rest,EXPR),
   !.

@extract_idx(['['|Rest],[EXPR|EXPRT]):-
   get_balanced(0,Rest,[']'],EXPR,[']'|Rest0]),
   !,
   extract_idx(Rest0,EXPRT),
   !.

@extract_idx(_,[]):-
   !.

@extract_idxs(L,T):-
   append(_,[id(V)|TT],L),
   !,
   extract_idx(TT,Idxs),
   !,
   extract_idxs(TT,T0),
   union([var(V,Idxs)],T0,T),
   !.

@extract_idxs(_,[]):-
   !.

@get_expr_idxs([],[]):-
   !.

@get_expr_idxs([E|T],Idxs):-
   =..(E,[_,_,_,_,_,_,_,_,[L]]),
   !,
   extract_idxs(L,Idxs1),
   get_expr_idxs(T,Idxs2),
   union(Idxs1,Idxs2,Idxs),
   !.

@get_var_idxs([],[]):-
   !.

@get_var_idxs([GID|T],Idxs):-
   atomic_op(_,GID,_,LGIDs,Exprs),
   !,
   get_expr_idxs(Exprs,Idxs0),
   !,
   get_var_idxs(LGIDs,Idxs1),
   get_var_idxs(T,Idxs2),
   union(Idxs0,Idxs1,IdxsA), union(IdxsA,Idxs2,Idxs),
   !.

@get_list_deps(_,[]):-
   !.

@get_list_deps(NamePath,[V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   get_fdeps(Name,NamePath,NPrms),
   get_list_deps(NamePath,T),
   !.

@get_expr_deps(_,[]):-
   !.

@get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   get_list_deps(NamePath,FUNS),
   get_expr_deps(NamePath,T),
   !.

@get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   get_list_deps(NamePath,FUNS),
   get_list_deps(NamePath,PROCS),
   get_expr_deps(NamePath,T),
   !.

@get_block_deps(_,[]):-
   !.

@get_block_deps(NamePath,[GID|T]):-
   atomic_op(_,GID,_,LGIDs,Exprs),
   get_expr_deps(NamePath,Exprs),
   get_block_deps(NamePath,LGIDs),
   !,
   get_block_deps(NamePath,T),
   !.

@mark_deps([]):-
   !.

@mark_deps([path(Name,NPrms)|T]):-
   (
    (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,t))->(
      true,!
    );(
      retractall(atomic_fdependent(Name,NPrms,_)), asserta(atomic_fdependent(Name,NPrms,t))
    )
   ),
   mark_deps(T).

@get_fdeps(Name,NamePath,NPrms):-
   member(path(Name,NPrms),NamePath),
   !.

@get_fdeps(Name,NamePath,NPrms):-
   atomic_function(Name,GID,NPrms),
   atomic_op('clsAtomicFunction',GID,_,LGIDs,_),
   (
    (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,_))->(
      true,!
    );(
      get_block_deps([path(Name,NPrms)|NamePath],LGIDs),
      (
       (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,_))->(
         true,!
       );(
         asserta(atomic_fdependent(Name,NPrms,f))
       )
      )
    )
   ),
   (
     (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,t))->
        mark_deps(NamePath);
        true
   ).

@get_fdeps(Name,NamePath,NPrms):-
   \+ atomic_function(Name,_,NPrms),
   (
    (predicate_property(atomic_fpure(_),'dynamic'),atomic_fpure(Name))->
       true;
       mark_deps(NamePath)
   ),
   !.

% Определение зависимостей функций от внешних функций
@find_dependents:-
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Name,_,NPrms),
      call(get_fdeps(Name,[],NPrms)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@get_comma_list([V,')'],[F]):-
   =..(V,[_,F]),
   !.

@get_comma_list([V,','|R],[F|T]):-
   =..(V,[_,F]),
   get_comma_list(R,T).

@get_next_op(GID,Next):-
   atomic_op(_,_,_,GIDs,_),
   append(_,[GID,Next|_],GIDs),
   !.

@get_next_op(GID,Next):-
   global_trace(GIDs),
   append(_,[gid(_,GID),gid(_,Next)|_],GIDs),
   !.

@analyze_pragma_pure([]):-
   !.

@analyze_pragma_pure([F|T]):-
   (
    (predicate_property(atomic_fpure(_),'dynamic'),atomic_fpure(F))->
       true;
       asserta(atomic_fpure(F))
   ),
   !,
   analyze_pragma_pure(T).

@into_atom([],_,''):-
   !.

@into_atom([id(V)|T],Gap,A):-
   into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@into_atom([real(V)|T],Gap,A):-
   into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@into_atom([integ(V)|T],Gap,A):-
   into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@into_atom([Z|T],Gap,A):-
   into_atom(T,Gap,A1),
   atom_concat(Z,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@analyze_pragma_split([id(F),')'|T],[F],T):-
   !.

@analyze_pragma_split([id(F),','|R],[F|T],Rest):-
   analyze_pragma_split(R,T,Rest),
   !.

@analyze_privates(Params,Privates,REST):-
   append(Left,[id(private),'('|T],Params),
   append(L,[')'|Right],T),
   !,
   append(L,[')'],L1),
   get_comma_list(L1,Privates),
   append(Left,Right,REST),
   !.

@analyze_privates(L,[],L):-
   !.

@analyze_param(Params,ID,Out,_,OParams):-
   append(L0,[id(ID),'('|T],Params),
   append(L,[')'|L1],T),
   !,
   append(L0,L1,OParams),
   !,
   append(L,[')'],L2),
   get_comma_list(L2,Out),
   !.

@analyze_param(Params,_,Def,Def,Params):-
   !.

@insert_splitteds([],_,[]):-
   !.

@insert_splitteds([gid(C1,PrevGID),gid(C2,LoopGID),gid(C3,BodyGID)|RIGHT],NewGID,[gid(C1,PrevGID),gid('clsAtomicPreproc',NewGID),gid(C2,LoopGID)|RIGHT1]):-
   db_content('prog',PrevGID,[[PrevType]]),
   \+ member(PrevType,['preproc','do','while','for']),
   db_content('prog',LoopGID,[[LType]]),
   member(LType,['do','for','while']),
   db_content('prog',BodyGID,[['{']]),
   asserta(db_content('prog',NewGID,[['preproc']])),
   asserta(db_content('args',NewGID,[['body','#pragma auto split(auto) tol(0.01) degree(2)']])),
   asserta(atomic_auto(LoopGID)),
   NextGID is NewGID-1,
   insert_splitteds([gid(C3,BodyGID)|RIGHT],NextGID,RIGHT1),
   !.

@insert_splitteds([H|T],NewGID,[H|T1]):-
   insert_splitteds(T,NewGID,T1),
   !.

% Очистка + Загрузка необходимых данных перед анализом
@prepare_atomic:-
   retractall(db_content(_,_,_)),
   retractall(atomic_function(_,_,_)),
   retractall(atomic_fdependent(_,_,_)),
   retractall(atomic_fpure(_)),
   retractall(atomic_farg(_,_,_,_,_,_)),
   retractall(atomic_fprocs(_,_,_)),
   asserta(atomic_op('','','','','')), retractall(atomic_op(_,_,_,_,_)),
   retractall(atomic_globals(_)),
   retractall(atomic_fanalyzed(_,_,_,_,_)),
   retractall(atomic_ftime(_,_,_)),
   retractall(atomic_ltime(_,_)),
   asserta(atomic_retime),retractall(atomic_retime),
   retractall(atomic_auto(_)),
   retractall(atomic_split(_,_,_,_,_)),
   asserta(atomic_reanalyze),retractall(atomic_reanalyze),
   asserta(atomic_splitted('','')), retractall(atomic_splitted(_,_)),
   retractall(atomic_splitted_time(_,_)),
   retractall(atomic_break(_)),
   retractall(atomic_continue(_)),
   retractall(params(_)),
   retractall(counter(_)),
   read_db,
   !,
   (
    (db_content('prog',GID1,[['preproc']]),
     db_content('args',GID1,[[body,S1]]),
     once(parse_expr(S1,['#',id('pragma'),id('auto'),id('pure'),'('|R1])),
     once(get_comma_list(R1,L1)),
     once(analyze_pragma_pure(L1)),
     once(global_trace(GTR)),
     append(LEFTR,[gid(_,GID1)|RIGHTR],GTR),
     append(LEFTR,RIGHTR,GTR2),
     once(retractall(global_trace(_))),
     once(asserta(global_trace(GTR2))),
     fail);
     true
   ),
   !,
   (
    (db_content('prog',GID3,[['preproc']]),
     db_content('args',GID3,[[body,S3]]),
     once(parse_expr(S3,['#',id('pragma'),id('auto'),id('parallelize')])),
     once(global_trace(GT)),
     once(insert_splitteds(GT,-10,GT1)),
     append(LEFT1,[gid(_,GID3)|RIGHT1],GT1),
     append(LEFT1,RIGHT1,GT2),
     once(retractall(global_trace(_))),
     once(asserta(global_trace(GT2))),
     fail);
     true
   ),
   !,
   prepare_atomic_functions,
   !,
   find_globals,
   !,
   build_atomic_functions,
   !,
   analyze_atomic_functions,
   !,
   iterative_build_funs,
   !,
   find_dependents,
   !,
   (
    (db_content('prog',GID2,[['preproc']]),
     db_content('args',GID2,[[body,S2]]),
     once(parse_expr(S2,['#',id('pragma'),id('auto'),id('split'),'('|R2])),
     once(get_next_op(GID2,GIDK)),
     once(analyze_pragma_split(R2,L2,R3)),
     once(analyze_privates(R3,Privates,R4)),
     once(analyze_param(R4,'tol',Tol,[0.01],R5)),
     once(analyze_param(R5,'degree',Degree,[2],R6)),
     once(into_atom(R6,' ',A5)),
     asserta(atomic_splitted(GIDK,params(L2,Privates,Tol,Degree,A5))),
     fail);
     true
   ),
   !.

@find_lvar(V,[Globals],global(V,TP)):-
   member(global(V,TP),Globals),
   !.

@find_lvar(V,[TopVars|_],loc(TopGID,V,TP)):-
   member(loc(TopGID,V,TP),TopVars),
   !.

@find_lvar(V,[_|RestVars],V1):-
   find_lvar(V,RestVars,V1),
   !.

@find_lvars([],_,[]):-!.

@find_lvars([global(V,TP)|T],Vars,[global(V,TP)|T1]):-
   find_lvars(T,Vars,T1),
   !.

@find_lvars([par(_,_,V)|T],Vars,[V1|T1]):-
   find_lvar(V,Vars,V1),
   find_lvars(T,Vars,T1),
   !.

@find_lvars([V|T],Vars,[V1|T1]):-
   find_lvar(V,Vars,V1),
   find_lvars(T,Vars,T1),
   !.

@find_lvars([V|T],Vars,T1):-
   \+ find_lvar(V,Vars,_),
   find_lvars(T,Vars,T1),
   !.

@loc_prefixate(_,[],[]):-!.

@loc_prefixate(TopGID,[var(V,TP)|T],[loc(TopGID,V,TP)|T1]):-
   loc_prefixate(TopGID,T,T1),
   !.

@analyze_fpdeps_list([],t):-
   !.

@analyze_fpdeps_list([H|_],f):-
   =..(H,[_,Name,LPrms]),
   length(LPrms,L),
   (
    atomic_function(Name,_,L)->
      atomic_fdependent(Name,L,t);
      \+ (predicate_property(atomic_fpure(_),'dynamic'), atomic_fpure(Name))
   ),
   !.

@analyze_fpdeps_list([_|T],Allow):-
   analyze_fpdeps_list(T,Allow),
   !.

@analyze_fpdeps(Funs,Procs,Allow):-
   append(Funs,Procs,FP),
   analyze_fpdeps_list(FP,Allow),
   !.

@getNewInOutRefLazies(_,_,[],[],[],[],[],[],0.0,t):-!.

@getNewInOutRefLazies(TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM,Allow):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,Procs0,Ref0,Laz0,_]),
   analyze_fpdeps(Funs0,Procs0,Allow0),
   find_lvars(Ins0,Vars,InsP),
   find_lvars(Outs0,Vars,OutsP),
   find_lvars(Ref0,Vars,RefsP),
   find_lvars(Laz0,Vars,LazP),
   loc_prefixate(TopGID,News0,NewsP),
   !,
   getTime(Funs0,T0),
   getNewInOutRefLazies(TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1,Allow1),
   !,
   (
     (=(Allow0,f);=(Allow1,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
   append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
   unique(News2,News), unique(Ins2,Ins), unique(Laz2,Lazies),
   append(Outs2,News,Outs3), unique(Outs3,Outs), unique(Ref2,Refs),
   TM is T0+T1,
   !.

@getForNewInOutRefLazies(_,_,_,[],[],[],[],[],[],0.0,t):-!.

@getForNewInOutRefLazies(Types,TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM,Allow):-
   =..(V,[Type,Ins0,Outs0,News0,Funs0,Procs0,Ref0,Laz0,_]),
   analyze_fpdeps(Funs0,Procs0,Allow0),
   (
    member(Type,Types)->(
      !,
      find_lvars(Ins0,Vars,InsP),
      find_lvars(Outs0,Vars,OutsP),
      find_lvars(Ref0,Vars,RefsP),
      find_lvars(Laz0,Vars,LazP),
      loc_prefixate(TopGID,News0,NewsP),
      !,
      getTime(Funs0,T0),
      getForNewInOutRefLazies(Types,TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1,Allow1),
      !,
      append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
      append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
      unique(News2,News), unique(Ins2,Ins), unique(Laz2,Lazies),
      unique(Outs2,Outs), unique(Ref2,Refs),
      TM is T0+T1
    );(
      getForNewInOutRefLazies(Types,TopGID,Vars,T,News,Ins,Outs,Refs,Lazies,TM,Allow1)
    )
   ),
   (
     (=(Allow0,f);=(Allow1,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   !.

@register_splitted_time(GID,TTP,TTN,TT1):-
   (
    (predicate_property(atomic_splitted(_,_),'dynamic'), atomic_splitted(GID,_))->
      (
       (predicate_property(atomic_splitted_time(_,_),'dynamic'), atomic_splitted_time(GID,Timings))->
         (
            retractall(atomic_splitted_time(GID,_)),
            asserta(atomic_splitted_time(GID,[TTP|Timings])),
            =(TT1,TTP)
         );(
            asserta(atomic_splitted_time(GID,[TTP])),
            =(TT1,TTP)
         )
      );
      =(TT1,TTN)
   ),
   !.

% Альтернативы из switch {}
@traverse_alters([op(CurGID,Time,Ins2,Outs2,Allow)], [CurGID|GIDs], [TopGID|StackGIDs], [switch(TopGID,Pass)|StackConstrs], StackConstrs, Vars, Time, NAlt):-
   atomic_op('clsAtomicAlternation',CurGID,_,[],_),
   (
    (append(ALT,[NextGID|_],GIDs),atomic_op('clsAtomicOper',NextGID,_,[],_),db_content('args',NextGID,[['op','break']]),!)->
       (
        !,
        traverse_fun(t,Splitted1, ALT,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T1),
        !
       );
       (
        traverse_fun(t,Splitted1, GIDs,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T1),
        !
       )
   ),
   collecting(Splitted1, [], [], Ins1, Outs1, Allow1),
   retractall(atomic_break(_)),
   (
    (append(_,[NextGID1|Rest1],GIDs),atomic_op('clsAtomicAlternation',NextGID1,_,[],_))->(
       !,
       traverse_alters(Splitted2, [NextGID1|Rest1],[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T2,NAlt1),
       Time is T1+T2,
       NAlt is NAlt1+1,
       !,
       collecting(Splitted2, Ins1, Outs1, Ins2, Outs2, Allow2),
       !
    );(
       =(Time,T1), =(NAlt,1),
       =(Ins2,Ins1), =(Outs2,Outs1), =(Allow2,t),
       !
    )
   ),
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   !.

@traverse_alters([], [], [TopGID|_], [switch(TopGID,_)|CRest], CRest, _, 0.0, 0):-!.

@exclude_locs(_, [], []):-
   !.

@exclude_locs(GID, [loc(GID,_,_)|T], T1):-
   exclude_locs(GID, T, T1),
   !.

@exclude_locs(GID, [H|T], [H|T1]):-
   exclude_locs(GID, T, T1),
   !.

@collecting([], Ins, Outs, Ins, Outs, t):-
   !.

@collecting([op(GID,_,I,O,Allow1)|T],Ins,Outs,Ins3,Outs3,Allow):-
   collecting(T,Ins,Outs,Ins1,Outs1,Allow2),
   exclude_locs(GID,Ins1,Ins2),
   exclude_locs(GID,Outs1,Outs2),
   union(I,Ins2,Ins3),
   union(O,Outs2,Outs3),
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   !.

@purge_owns([],_,[]):-
   !.

@purge_owns([loc(CurGID,_,_)|T],CurGID,T1):-
   purge_owns(T,CurGID,T1),
   !.

@purge_owns([H|T],CurGID,[H|T1]):-
   purge_owns(T,CurGID,T1),
   !.

@check_split(CurGID,1000000.0):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopID,_,CurGID,_,_),
   predicate_property(atomic_splitted(_,_),'dynamic'),
   atomic_splitted(LoopID,_),
   !.

@check_split(_,1.0):-
   !.

@exclude_vars([],_,[]):-
   !.

@exclude_vars([loc(_,V,_)|T],Vars,T1):-
   member(V,Vars),
   !,
   exclude_vars(T,Vars,T1),
   !.

@exclude_vars([global(V,_)|T],Vars,T1):-
   member(V,Vars),
   !,
   exclude_vars(T,Vars,T1),
   !.

@exclude_vars([H|T],Vars,[H|T1]):-
   exclude_vars(T,Vars,T1),
   !.

@exclude_canals([],[auto],[],[]):-
   !.

@exclude_canals([],Canals,Canals,[]):-
   !.

@exclude_canals([loc(_,V,Type)|T],[auto],[V|T1],[]):-
   \+ member('*', Type), \+ member('&', Type),
   exclude_canals(T,[auto],T1,[]),
   !.

@exclude_canals([global(V,Type)|T],[auto],[V|T1],[]):-
   \+ member('*', Type), \+ member('&', Type),
   exclude_canals(T,[auto],T1,[]),
   !.

@exclude_canals(_,[auto|_],[],[error]):-
   !.

@exclude_canals([loc(_,V,Type)|T],Canals,Canals,T1):-
   \+ member('*', Type), \+ member('&', Type),
   member(V,Canals),
   !,
   exclude_canals(T,Canals,Canals,T1),
   !.

@exclude_canals([global(V,Type)|T],Canals,Canals,T1):-
   \+ member('*', Type), \+ member('&', Type),
   member(V,Canals),
   !,
   exclude_canals(T,Canals,Canals,T1),
   !.

@exclude_canals([H|T],Canals,Canals,[H|T1]):-
   exclude_canals(T,Canals,Canals,T1),
   !.

@purge_trace([],_,[]):-
   !.

@purge_trace([op(GID,Time,Ins,Outs,Allow)|T],Privates,[op(GID,Time,Ins1,Outs1,Allow)|T1]):-
   exclude_vars(Ins,Privates,Ins1),
   exclude_vars(Outs,Privates,Outs1),
   purge_trace(T,Privates,T1),
   !.

@get_best([],_,_,_,_,_):-
   !, fail.

@get_best([variant(St,G,Fin,Tm,CDecls)],St,G,Fin,Tm,CDecls):-
   !.

@get_best([variant(St,G,Fin,Tm,CDecls)|T],StartGID,GID,FinGID,Time,CDECLS):-
   get_best(T,St1,G1,Fin1,Tm1,CDecls1),
   !,
   g_read('$DefOperTime', T0),
   (
    (
     length(CDecls,L),length(CDecls1,L1),D is abs(Tm-Tm1),EPS is 2*T0,
     ((<(D,EPS),\+ =(L,0),<(L,L1));<(Tm,Tm1))
    )->
     (=(StartGID,St),=(GID,G),=(FinGID,Fin),=(Time,Tm),=(CDECLS,CDecls));
     (=(StartGID,St1),=(GID,G1),=(FinGID,Fin1),=(Time,Tm1),=(CDECLS,CDecls1))
   ),
   !.

@analyze_part([],[],[],0.0):-
   !.

@analyze_part([op(_,Tm,I,O,_)|T],Ins,Outs,T1):-
   analyze_part(T,Ins1,Outs1,T2),
   union(I,Ins1,Ins),
   union(O,Outs1,Outs),
   T1 is T2+Tm,
   !.

@indexes_split([], []):-
   !.

@indexes_split(L, [IDX|T]):-
   append(['['|IDXS],[']','['|Next],L),
   !,
   into_atom(IDXS,'',IDX),
   indexes_split(['['|Next],T),
   !.

@indexes_split(L, [IDX]):-
   append(['['|IDXS],[']'],L),
   !,
   into_atom(IDXS,'',IDX),
   !.

@find_decl(V,Vars,var(V,Type,Idxs)):-
   member(global(V,type(TypeSEQ,IdxSEQ)),Vars),
   indexes_split(IdxSEQ,Idxs),
   into_atom(TypeSEQ,' ',Type),
   !.

@find_decl(V,Vars,var(V,Type,Idxs)):-
   member(loc(_,V,type(TypeSEQ,IdxSEQ)),Vars),
   indexes_split(IdxSEQ,Idxs),
   into_atom(TypeSEQ,' ',Type),
   !.

@get_canal_decls([],_,[]):-
   !.

@get_canal_decls([C|T],Vars,[CDecl|T1]):-
   find_decl(C,Vars,CDecl),
   get_canal_decls(T,Vars,T1),
   !.

@belongs(op(GID,_,_,_,_),LoopGID):-
   atomic_op(_,LoopGID,_,LGIDs,_),
   member(GID,LGIDs),
   !.
   
@belongs(op(GID,_,_,_,_),LoopGID):-
   atomic_op('clsAtomicBegin',UpperGID,_,LGIDs,_),
   member(GID,LGIDs),
   !,
   atomic_op(_,LoopGID,_,LGIDs2,_),
   member(UpperGID,LGIDs2),
   !.

@delete_splitted_gids([],_,[]):-
   !.

@delete_splitted_gids([op(GID,_,_,_,_)|T],GID,T1):-
   delete_splitted_gids(T,GID,T1),
   !.
   
@delete_splitted_gids([op(GID,A,B,C,D)|T],GID1,[op(GID,A,B,C,D)|T1]):-
   delete_splitted_gids(T,GID1,T1),
   !.
   
@find_start([],[],GID,GID):-
   !.

@find_start(Splitted11,Splitted1,FirstGID0,FirstGID):-
   atomic_op('clsAtomicOper',FirstGID0,_,_,[arg(_,_,News,_,_,_,_,_)]),
   \+ =(News,[]),
   global_trace(TR),
   append(_,[gid(_,FirstGID0),gid(_,FirstGID1)|_],TR),
   delete_splitted_gids(Splitted11,FirstGID0,Splitted12),
   find_start(Splitted12,Splitted1,FirstGID1,FirstGID),
   !.

@find_start(Splitted1,Splitted1,FirstGID0,FirstGID0):-
   !.

@generate_variants(_,_,_,[],[]):-
   !.

@generate_variants(LoopGID,Canals,First,[H|Last1],V):-
   append(First,[H],First1),
   !,
   generate_variants(LoopGID,Canals,First1,Last1,V0),
   !,
   analyze_part(First,Ins1,Outs1,T1),
   analyze_part([H|Last1],Ins2,Outs2,T2),
   intersect(Outs1,Ins2,P1),
   exclude_canals(P1, Canals, FoundCanals, P11),
   intersect(Outs2,Ins1,P2),
   (
     (
      (append(_,[op(PrevGID,_,_,_,_)],First), =(P11,[]), =(P2,[]), \+ atomic_op('clsAtomicPreproc',PrevGID,_,_,_), belongs(H,LoopGID))->
        (Time is max(T1,T2), =(H,op(GID,_,_,_,_)), get_canal_decls(FoundCanals,P1,CDS), =(V,[variant(-1,GID,-1,Time,CDS)|V0]));
        =(V,V0)
     )
   ),
   !.

@contains_break_continue(GID):-
   atomic_op('clsAtomicOper',GID,_,_,_),
   db_content('args',GID,[['op',OP]]),
   once((=(OP,'break');=(OP,'continue'))),
   !.

@contains_break_continue(GID):-
   atomic_op('clsAtomicBegin',GID,_,IGIDs,_),
   member(IGID, IGIDs),
   contains_break_continue(IGID),
   !.

@contains_break_continue(GID):-
   atomic_op('clsAtomicIf',GID,-1,[OPID0],_),
   contains_break_continue(OPID0),
   !.

@contains_break_continue(GID):-
   atomic_op('clsAtomicIf',GID,_,[OPID0,OPID1],_),
   once(( contains_break_continue(OPID0); contains_break_continue(OPID1) )),
   !.

@try_split(_,_,[],_,_,_):-
   !, fail.

@try_split(_,_,[_],_,_,_):-
   !, fail.

@try_split(_,_,Body,_,_,_):-
   member(op(CurGID,_,_,_,_),Body),
   contains_break_continue(CurGID),
   !, fail.

@try_split(LoopGID,Canals,[H|T],GID,Time,CDecls):-
   generate_variants(LoopGID,Canals,[H],T,V),
   !,
   get_best(V,_,GID,_,Time,CDecls).

@try_forwards(_,_,_,_,[],V,V):-
   !.

@try_forwards(LoopGID,Canals,BaseTime,FinGID,[op(PrevGID,Time,_,_,_)|T],Vars0,Vars1):-
   ThisTime is BaseTime+Time,
   try_forwards(LoopGID,Canals,ThisTime,FinGID,T,Vars0,V0),
   !,
   (
    (\+ atomic_op('clsAtomicPreproc',PrevGID,_,_,_), try_split(LoopGID,Canals,T,GID,TS,CDS), =(T,[H|_]), belongs(H,LoopGID))->
      (Time1 is ThisTime+TS, =(T,[op(StartGID,_,_,_,_)|_]), =(Vars1,[variant(StartGID,GID,FinGID,Time1,CDS)|V0]));
      (=(Vars1,V0))
   ),
   !.

@try_backwards(_,_,_,_,[],V,V):-
   !.

@try_backwards(LoopGID,Canals,BaseTime,StartGID,L,Vars0,Vars1):-
   append(T,[op(FinGID,Time,_,_,_)], L),
   ThisTime is BaseTime+Time,
   try_backwards(LoopGID,Canals,ThisTime,StartGID,T,Vars0,V0),
   !,
   (
    (
     (append(_,[op(PrevGID,_,_,_,_)],T), \+ atomic_op('clsAtomicPreproc',PrevGID,_,_,_), try_split(LoopGID,Canals,T,GID,TS,CDS),
      =(T,[H|_]), belongs(H,LoopGID))->
       (Time1 is ThisTime+TS, =(Vars1,[variant(StartGID,GID,FinGID,Time1,CDS)|V0]));
       (=(Vars1,V0))
    )
   ),
   !.

@create_split(CurGID,VarCanals,Privates,Splitted):-
   (member(op(_,_,_,_,f),Splitted), predicate_property(atomic_auto(_),'dynamic'), atomic_auto(CurGID))->
     ( retractall(atomic_split(CurGID,_,_,_,_)),! );
     (
       purge_trace(Splitted,Privates,Splitted0),
       append(Splitted11,[op(0,-1,[],[],t)|_],Splitted0),
       !,
       global_trace(GT),
       append(_,[gid(_,CurGID),gid(_,_),gid(_,FirstGID0)|_],GT),
       find_start(Splitted11,Splitted1,FirstGID0,FirstGID),
       !,
       append(_,[gid(C,CurGID)|Right],GT),
       !,
       bypass_op([gid(C,CurGID)|Right],Loop,_),
       (
         =(C,'clsAtomicDo')->
          append(_,[gid(_,AfterLastGID),gid('clsAtomicWhile',_),gid('clsAtomicOper',_)],Loop);
          append(_,[gid(_,AfterLastGID)],Loop)
       ),
       !,
       (
          (try_split(CurGID,VarCanals,Splitted1,GID0,Time0,CDS)->
            (
             =(V0,[variant(FirstGID,GID0,AfterLastGID,Time0,CDS)])
            );
             =(V0,[])
          ),
          (
           try_forwards(CurGID,VarCanals,0.0,AfterLastGID,Splitted1,V0,V1),
           try_backwards(CurGID,VarCanals,0.0,FirstGID,Splitted1,V1,V2),
           !,
           (
            get_best(V2,StartGID,GID,FinGID,_,CDecls)->
             (
               retractall(atomic_split(CurGID,_,_,_,_)),
               asserta(atomic_split(CurGID,StartGID,GID,FinGID,CDecls))
             );
             true
            )
          )
       ),
       !
     ).

@find_split_privates_one([], []):-
   !.

@find_split_privates_one([global(V,type([id(split_private)|_],_))|T], [V|T1]):-
   find_split_privates_one(T, T1),
   !.

@find_split_privates_one([loc(_,V,type([id(split_private)|_],_))|T], [V|T1]):-
   find_split_privates_one(T, T1),
   !.

@find_split_privates_one([_|T], T1):-
   find_split_privates_one(T, T1),
   !.

@find_split_privates([], []):-
   !.

@find_split_privates([VARS|T], Privates):-
   find_split_privates_one(VARS, P0),
   find_split_privates(T, P1),
   union(P0, P1, Privates),
   !.

@concat_privates([], ''):-
   !.

@concat_privates([V], V):-
   !.

@concat_privates([V1,V2|T], S):-
   concat_privates([V2|T], S1),
   atom_concat(V1,',',S2),
   atom_concat(S2,S1,S),
   !.

@analyze_splitted(CurGID,Vars):-
   atomic_splitted(CurGID,params(Canals,OldPrivates,Tol,Degree,RestParams)),
   !,
   find_split_privates(Vars,Privates),
   length(OldPrivates,OLD),
   length(Privates,NEW),
   !,
   (
     >(NEW,OLD)->
       (retractall(atomic_splitted(CurGID,_)), asserta(atomic_splitted(CurGID,params(Canals,Privates,Tol,Degree,RestParams))));
       true
   ),
   !.

@analyze_splitted(_,_):-
   !.

% Окончание while
@traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [while(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsAtomicWhile',TopGID,_,[_],Ops),
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
   !,
   (
    (predicate_property(atomic_continue(_),'dynamic'), atomic_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(atomic_continue(_)),
   (
    (predicate_property(atomic_break(_),'dynamic'), atomic_break(_))->(
       retractall(atomic_break(_)),
       =(T1,0.0),=(OSplitted,[])
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          atomic_op('clsAtomicWhile',TopGID,_,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          traverse_fun(SMode,Splitted1, [IGID1],[TopGID|StackGIDs],[while(TopGID,2)|StackConstrs],_,[LVars|Vars],T11),
          (
           <(T11,1000000.0)->
             (put_ltime(TopGID,T11), T1 is T11);
             (
              T01 is round(T11/1000000),
              T02 is round(T11-T01*1000000.0),
              T1N is T01+T02,
              T1P is max(T01,T02),
              register_splitted_time(TopGID,T1P,T1N,T1)
             )
          ),
          !,
          =(OSplitted,[op(0,-1,[],[],t)|Splitted1])
         );
         (=(T1,0.0),=(OSplitted,[]))
      )
   ),
   (
    (=(CONT,1))->(
      Time is BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is T1+BaseTime
    )
   ),
   !.

% Прерывание break
@traverse_fun(_, [], [CurGID|_], StackGIDs, [Top|StackConstrs], StackConstrs, Vars, Time):-
   atomic_op('clsAtomicOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','break']]),
   !,
   check_split(CurGID,K),
   asserta(atomic_break(CurGID)),
   =..(Top,[_,TopGID,_]),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(vr(VAR0)), once(tm(T0)),
     traverse_fun(t, _, [],[CurTopGID|Rest],[Top|StackConstrs],_,VAR0,TT),
     T1 is T0+TT,
     retractall(vr(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(vr(VAR1)), asserta(tm(T1)),
     =(TopGID,CurTopGID), % Проверка -- условие окончания цикла
   !,
   Time is T1*K,
   retractall(vr(_)), retractall(tm(_)),
   !.

% Возобновление continue
@traverse_fun(_, [], [CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','continue']]),
   !,
   check_split(CurGID,K),
   asserta(atomic_continue(CurGID)),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)),
     traverse_fun(t, _, [],[CurTopGID|Rest],ST0,ST1,VAR0,TT),
     T1 is T0+TT,
     retractall(st(_)), retractall(vr(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(st(ST1)), asserta(vr(VAR1)), asserta(tm(T1)),
     \+ atomic_continue(CurGID), % Проверка -- условие окончания цикла
   !,
   =(OutCStack,ST1), Time is T1*K,
   retractall(st(_)), retractall(vr(_)), retractall(tm(_)),
   !.

% Возврат return
@traverse_fun(_, [], [CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicReturn',CurGID,_,[],_),
   !,
   check_split(CurGID,K),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)),
     traverse_fun(t, _, [],[CurTopGID|Rest],ST0,ST1,VAR0,TT),
     T1 is T0+TT,
     retractall(st(_)), retractall(vr(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(st(ST1)), asserta(vr(VAR1)), asserta(tm(T1)),
     =(Rest,[-1]), % Проверка -- условие окончания цикла
   !,
   =(OutCStack,ST1), Time is T1*K,
   retractall(st(_)), retractall(vr(_)), retractall(tm(_)),
   !.

% Окончание do-while
@traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [do(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsAtomicDo',TopGID,LastGID,[_],Ops),
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
   !,
   (
    (predicate_property(atomic_continue(_),'dynamic'), atomic_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(atomic_continue(_)),
   (
    (predicate_property(atomic_break(_),'dynamic'), atomic_break(_))->(
       retractall(atomic_break(_)),
       =(T2,0.0),=(OSplitted,[])
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          atomic_op('clsAtomicDo',TopGID,LastGID,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          traverse_fun(SMode, Splitted1, [IGID1],[TopGID|StackGIDs],[do(TopGID,2)|StackConstrs],_,[LVars|Vars],T22),
          (
           <(T22,1000000.0)->
             (put_ltime(TopGID,T22), T2 is T22);
             (
              T01 is round(T22/1000000),
              T02 is round(T22-T01*1000000.0),
              T2N is T01+T02,
              T2P is max(T01,T02),
              register_splitted_time(TopGID,T2P,T2N,T2)
             )
          ),
          !,
          =(OSplitted, [op(0,-1,[],[],t)|Splitted1])
         );
         (=(T2,0.0),=(OSplitted,[]))
      )
   ),
   (
    (=(CONT,1))->(
      Time is BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is T2+BaseTime
    )
   ),
   !.

% Окончание for
@traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [for(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsAtomicFor',TopGID,_,[_],Ops),
   !,
   getForNewInOutRefLazies(['cond','chng'],TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
   !,
   (
    (predicate_property(atomic_continue(_),'dynamic'), atomic_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(atomic_continue(_)),
   (
    (predicate_property(atomic_break(_),'dynamic'), atomic_break(_))->(
       retractall(atomic_break(_)),
       =(T2,0.0),=(OSplitted,[])
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          atomic_op('clsAtomicFor',TopGID,_,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          traverse_fun(SMode, Splitted1, [IGID1],[TopGID|StackGIDs],[for(TopGID,2)|StackConstrs],_,[LVars|Vars],T22),
          (
           <(T22,1000000.0)->
             (put_ltime(TopGID,T22), T2 is T22);
             (
              T01 is round(T22/1000000),
              T02 is round(T22-T01*1000000.0),
              T2N is T01+T02,
              T2P is max(T01,T02),
              register_splitted_time(TopGID,T2P,T2N,T2)
             )
          ),
          !,
          =(OSplitted, [op(0,-1,[],[],t)|Splitted1])
         );
         (=(T2,0.0),=(OSplitted,[]))
      )
   ),
   (
    (=(CONT,1))->(
      Time is BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is T2+BaseTime
    )
   ),
   !.

% Окончание произвольного {}
@traverse_fun(_, [], [], [TopGID|_], StackConstrs, StackConstrs, _, 0.0):-
   atomic_op('clsAtomicBegin',TopGID,_,_,_),
   !,
   (
     true
   ),
   !.

% Окончание функции
@traverse_fun(_, [], [], [-1], StackConstrs, StackConstrs, _, 0.0):-
   !.

% Окончание произвольного (не{}) оператора. Может вызываться в операторе окончания различных конструктов
@traverse_fun(_, [], [], [TopGID|_], StackConstrs, StackConstrs, _, 0.0):-
   \+ atomic_op('clsAtomicBegin',TopGID,_,_,_),
   !,
   (
     true
   ),
   !.

% Полный if-else, IGIDs = [IfGID,EGID]. Краткий if -- обрабатывается обычным образом, IGIDs = [IfGID]
@traverse_fun(Mode, [op(CurGID,OTime,Ins2,Outs2,Allow)|Splitted3], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicIf',CurGID,_,LGIDS,Ops),
   (
     =(LGIDS, [IfGID,EGID])->
      true;
      ( =(LGIDS, [IfGID]), =(EGID, '') )
   ),
   !,
   check_split(CurGID,K),
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   traverse_fun(t, Splitted1,[IfGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T20),
   collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
   (
    =(EGID, '')->
      (
       =(Ins2, Ins1), =(Outs2, Outs1), =(Allow3, Allow1), =(T21, T20)
      );
      ( traverse_fun(t, Splitted2,[EGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T21),
        collecting(Splitted2, Ins1, Outs1, Ins2, Outs2, Allow3)
      )
   ),
   !,
   (
     OTime is BaseTime+0.5*(T20+T21)
   ),
   traverse_fun(Mode, Splitted3, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f);=(Allow3,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(BaseTime+0.5*(T20+T21)+T3),
   !.

% Полный while
@traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicWhile',CurGID,_,[IGID],Ops),
   !,
   check_split(CurGID,K),
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   traverse_fun(SMode, Splitted1,[IGID],[CurGID,TopGID|StackGIDs],[while(CurGID,1)|StackConstrs],_,[News|Vars],T2),
   !,
   (
    <(T2,1000000.0)->
      CheckedTime is T2;
      (
       T01 is round(T2/1000000),
       T02 is round(T2-T01*1000000.0),
       CheckedTime is max(T01,T02)
      )
   ),
   !,
   (
     OTime is BaseTime+CheckedTime,
     analyze_splitted(CurGID,Vars),
     collecting(Splitted1, Ins, Outs, Ins0, Outs1, Allow2),
     purge_owns(Ins0,CurGID,Ins1)
   ),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             create_split(CurGID,Canals,Privates,Splitted1)
         )
       );
       (true)
   ),
   traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(BaseTime+T3+CheckedTime),
   !.

% Полный for
@traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicFor',CurGID,_,[IGID],Ops),
   !,
   check_split(CurGID,K),
   getForNewInOutRefLazies(['init','cond'],CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   traverse_fun(SMode, Splitted1,[IGID],[CurGID,TopGID|StackGIDs],[for(CurGID,1)|StackConstrs],_,[News|Vars],T2),
   !,
   analyze_splitted(CurGID,Vars),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             create_split(CurGID,Canals,Privates,Splitted1)
         )
       );
       (true)
   ),
   (
    <(T2,1000000.0)->
      CheckedTime is T2;
      (
       T01 is round(T2/1000000),
       T02 is round(T2-T01*1000000.0),
       CheckedTime is max(T01,T02)
      )
   ),
   !,
   (
      OTime is BaseTime+CheckedTime,
      collecting(Splitted1, Ins, Outs, Ins0, Outs1, Allow2),
      purge_owns(Ins0,CurGID,Ins1)
   ),
   !,
   traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(T3+BaseTime+CheckedTime),
   !.

% Полный do-while
@traverse_fun(Mode, [op(CurGID,CheckedTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicDo',CurGID,_,[IGID],_),
   !,
   check_split(CurGID,K),
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   traverse_fun(SMode, Splitted1, [IGID],[CurGID,TopGID|StackGIDs],[do(CurGID,1)|StackConstrs],_,[[]|Vars],T1),
   !,
   (
    <(T1,1000000.0)->
      CheckedTime is T1;
      (
       T01 is round(T1/1000000),
       T02 is round(T1-T01*1000000.0),
       CheckedTime is max(T01,T02)
      )
   ),
   !,
   analyze_splitted(CurGID,Vars),
   collecting(Splitted1, [], [], Ins0, Outs1, Allow),
   purge_owns(Ins0,CurGID,Ins1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             create_split(CurGID,Canals,Privates,Splitted1)
         )
       );
       (true)
   ),
   traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T2),
   !,
   Time is K*(CheckedTime+T2),
   !.

% switch
@traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsAtomicSwitch',CurGID,_,[IGID],Ops),
   atomic_op('clsAtomicBegin',IGID,_,IGIDs,_),
   !,
   check_split(CurGID,K),
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   traverse_alters(Splitted1, IGIDs,[CurGID,TopGID|StackGIDs],[switch(CurGID,1)|StackConstrs],_,[News|Vars],TNN,NAlt),
   !,
   collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
   !,
   (
     =(NAlt,0)->
       OTime is BaseTime;
       OTime is BaseTime+TNN/NAlt
   ),
   !,
   traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T2),
   !,
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   (
    =(NAlt,0)->
      Time is K*(BaseTime+T2);
      Time is K*(BaseTime+TNN/NAlt+T2)
   ),
   !.

@traverse_fun(Mode, OSplitted, [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   check_split(CurGID,K),
   (
    (predicate_property(atomic_break(_),'dynamic'), atomic_break(_))->(
       traverse_fun(Mode, OSplitted, [], [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Time1),
       Time is Time1*K,
       !
    );(
       atomic_op(_,CurGID,_,IGIDs,Ops),
       !,
       getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
       (
        ( % Если это запуск процедуры, то прибавляем время ее исполнения
          atomic_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)])->
            (getTime([proc(Fun,Prms)],TSP1), g_read('$DefOperTime',TOp0), TSP is TSP1-TOp0);
            =(TSP,0.0)
        )
       ),
       addLocals(Vars,News,Vars1),
       !,
       traverse_fun(t, Splitted1, IGIDs,[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T2),
       !,
       traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars1,T3),
       !,
       (=(Mode,t)->
         (
            OTime is TSP+BaseTime+T2,
            collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
            (
              (=(Allow1,f);=(Allow2,f))->
                =(Allow,f);
                =(Allow,t)
            ),
            =(OSplitted, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2])
         );
         (
            append(Splitted1,Splitted2,OSplitted)
         )
       ),
       !,
       Time is K*(TSP+BaseTime+T2+T3),
       !
    )
   ).

@create_splits(Fun,GID,NPrms):-
   retractall(atomic_break(_)),
   retractall(atomic_continue(_)),
   atomic_globals(GLOB),
   glob_prefixate(GLOB,G1),
   get_fparams(all,Fun,NPrms,PARMS),
   loc_prefixate(GID,PARMS,P1),
   traverse_fun(f, _, [GID],[-1],[],_,[P1,G1],Time),
   put_ftime(Fun,NPrms,Time),
   !.

@bypass_sequence([],[],[]):-!.

@bypass_sequence([gid('clsAtomicEnd',GID)|T],[],[gid('clsAtomicEnd',GID)|T]):-
   !.

@bypass_sequence([gid('clsAtomicBegin',GID)|T],TT,T3):-
   bypass_complex([gid('clsAtomicBegin',GID)|T],T0,T1),
   bypass_sequence(T1,T2,T3),
   append(T0,T2,TT),
   !.

@bypass_sequence([H|T],[H|T1],T2):-
   bypass_sequence(T,T1,T2),
   !.

@bypass_complex([gid('clsAtomicBegin',GID)|T],[gid('clsAtomicBegin',GID)|T1],T2):-
   bypass_sequence(T,T0,[gid('clsAtomicEnd',GID2)|T2]),
   append(T0,[gid('clsAtomicEnd',GID2)],T1).

@bypass_op([A|T],[A|BeforeWith],After):-
   member(A,[gid('clsAtomicFor',_),gid('clsAtomicSwitch',_),gid('clsAtomicWhile',_)]),
   !,
   bypass_op(T,BeforeWith,After),
   !.

@bypass_op([gid('clsAtomicDo',GID)|T],[gid('clsAtomicDo',GID)|T1],T2):-
   bypass_op(T,BeforeWhile,[gid('clsAtomicWhile',GIDW),gid('clsAtomicOper',EMPTY)|T2]),
   append(BeforeWhile,[gid('clsAtomicWhile',GIDW),gid('clsAtomicOper',EMPTY)],T1),
   !.

@bypass_op([gid('clsAtomicIf',GID)|T],[gid('clsAtomicIf',GID)|T1],T2):-
   bypass_op(T,BeforeWith,[A|AfterT]),
   (
    =(gid('clsAtomicElse',_),A)->(
      bypass_op(AfterT,BeforeWith2,T2),
      append(BeforeWith,[A|BeforeWith2],T1),
      !
    );(
      =(T1,BeforeWith),=(T2,[A|AfterT]),!
    )
   ),
   !.

@bypass_op([gid('clsAtomicBegin',GID)|T],T1,T2):-
   bypass_complex([gid('clsAtomicBegin',GID)|T],T1,T2),
   !.

@bypass_op([A|T],[A],T):-!.

@insert_ending_bracket(L1,L2):-
   bypass_op(L1,BeforeWith,After),
   !,
   append(BeforeWith,[gid('clsAtomicEnd',-1)|After],L2),
   !.

@write_program(_,_,_,[]):-!.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicOper',GID)|T]):-
   db_content('prog',GID,[['op']]),
   db_content('args',GID,[['op',Op]]),
   atom_concat(SPC,Shift,SPC1),
   write(S,SPC1),
   write(S,Op), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,SP,S,[gid('clsAtomicComments',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(Shift,SP,S,[gid('clsAtomicInclude',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicBegin',GID)|T]):-
   db_content('prog',GID,[['{']]),
   write(S,SPC), write(S,Shift), write(S,'{'), nl(S),
   atom_concat(SPC,Shift,SPC1),
   atom_concat(SPC1,'  ',SPC2),
   write_program('',[SPC2,SPC1,SPC|ST],S,T),
   !.

@write_program(_,[_,SPC1,SPC|ST],S,[gid('clsAtomicEnd',_)|T]):-
   write(S,SPC1), write(S,'}'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicDo',GID)|T]):-
   db_content('prog',GID,[['do']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'do'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicWhile',GID)|T]):-
   db_content('prog',GID,[['while']]),
   db_content('args',GID,[['cond',Cond]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'while ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicFor',GID)|T]):-
   db_content('prog',GID,[['for']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift),
   write(S,'for ( '),
   !,
   db_content('args',GID,L),
   (
    member(['init',Init0],L), write(S, Init0),
    (
     (member(['init',Init],L), \+ =(Init,Init0), write(S, ','), write(S, Init), fail);
     (true,!)
    ),
    write(S, '; ')
   ),
   member(['cond',Cond],L),
   !,
   write(S, Cond),
   write(S, '; '),
   (
    member(['chng',Chng0],L), write(S, Chng0),
    (
     (member(['chng',Chng],L), \+ =(Chng,Chng0), write(S, ','), write(S, Chng), fail);
     (true,!)
    )
   ),
   !,
   write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicIf',GID)|T]):-
   db_content('prog',GID,[['if']]),
   db_content('args',GID,[['cond',Cond]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'if ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicElse',GID)|T]):-
   db_content('prog',GID,[['else']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'else'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicSwitch',GID)|T]):-
   db_content('prog',GID,[['switch']]),
   db_content('args',GID,[['arg',Arg]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(Shift), write(S,'switch ( '), write(S,Arg), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicAlternation',GID)|T]):-
   (
    (
     db_content('prog',GID,[['case']]),
     !,
     db_content('args',GID,[['arg',Arg]]),
     write(S,SPC), write(S,Shift), write(S,'case '), write(S,Arg), write(S,' : '), nl(S)
    );(
     db_content('prog',GID,[['default']]),
     !,
     write(S,SPC), write(S,Shift), write(S,'default : '), nl(S)
    )
   ),
   write_program(Shift,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicTypedef',GID)|T]):-
   db_content('prog',GID,[['type']]),
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,'typedef '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicCVar',GID)|T]):-
   db_content('prog',GID,[[TYPE]]),
   member(TYPE,['struct','union']),
   !,
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,TYPE), write(S,' '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsAtomicReturn',GID)|T]):-
   db_content('prog',GID,[['return']]),
   db_content('args',GID,[['arg',Arg]]),
   write(S,SPC), write(S,Shift), write(S,'return '), write(S,Arg), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,SP,S,[gid('clsAtomicPreproc',GID)|T]):-
   db_content('prog',GID,[['preproc']]),
   db_content('args',GID,[['body',Body]]),
   write(S,Body), nl(S),
   write_program(Shift,SP,S,T),
   !.

@write_program(_,[SPC|ST],S,[gid('clsAtomicFunction',GID)|T]):-
   db_content('prog',GID,[['func']]),
   db_content('args',GID,L),
   member(['name',ID],L),
   member(['args',Args],L),
   member(['ret',Ret],L),
   !,
   write(S,SPC), write(S, Ret), write(S, ' '), write(S, ID), write(S,'( '), write(S,Args), write(S,' )'),
   write_program('',[SPC|ST],S,T),
   !.

% Формирование текста программы FName по загруженным данным + преобразования
@recreate_program(FName):-
  open(FName,write,S),
  global_trace(TR),
  write_program('',[''],S,TR),
  close(S).

@create_all_splits:-
  predicate_property(atomic_function(_,_,_),'dynamic'),
  atomic_function(Fun,GID,NPrms),
  once(create_splits(Fun,GID,NPrms)),
  get_ftime(Fun,NPrms,_), % Time
%  write(Fun),write(':'),write(Time),nl,
  fail.

@create_all_splits:-
%  write('--------------'), nl,
  !.

@iterative_splits_times(0):-!.

% Итерационный алгоритм последовательного добавления splits и пересчета времен исполнения функций. Алгоритм заканчивается, когда
% времена исполнения практически перестают меняться (+/-1) или превышено число итераций N
@iterative_splits_times(N):-
  retractall(atomic_retime),
  retractall(atomic_splitted_time(_,_)),
  create_all_splits,
  predicate_property(atomic_retime,'dynamic'),
  atomic_retime,
  !,
  N1 is N-1,
  iterative_splits_times(N1).

@iterative_splits_times(_):-!.

@sum([],0.0):-!.

@sum([H|T],S):-
  sum(T,S0),
  S is S0+H,
  !.

@avr([],0.0):-!.

@avr(L,Avr):-
  sum(L,S),
  length(L,N),
  Avr is S/N.

% Определяем неэффективные splitted-запуски
@remove_splitteds:-
  predicate_property(atomic_splitted(_,_),'dynamic'),
  atomic_splitted(GID,_),
  predicate_property(atomic_ltime(_,_),'dynamic'),
  atomic_ltime(GID,BaseTime),
  predicate_property(atomic_splitted_time(_,_),'dynamic'),
  atomic_splitted_time(GID,Timings),
  call(avr(Timings,AvrTime)),
  g_read('$SplittedTime', SplittedTime),
  ParExecTime is AvrTime+SplittedTime, % С учетом расходов на собственно splitted
  ( % Принятие решения об исключении splitted
    >(ParExecTime,BaseTime)->(
      once(atomic_resplitteds(List)),
      retractall(atomic_resplitteds(_)),
      asserta(atomic_resplitteds([GID|List]))
    );
    true
  ),
  fail.

@remove_splitteds:-!.

@clear_ltimes_upper_loops(GID):-
   atomic_op(_,UpperGID,_,LGIDs,_),
   member(GID,LGIDs),
   !,
   (
      (retractall(atomic_ltime(UpperGID,_)),retractall(atomic_splitted_time(UpperGID,_)))
   ),
   clear_ltimes_upper_loops(UpperGID),
   !.

@clear_ltimes_upper_loops(_):-
   !.

% Удаляем пометки с операторов, GIDы которых прописаны в параметре-списке
@delete_splitteds([]):-!.

@delete_splitteds([H|T]):-
  retractall(atomic_splitted(H,_)),
  retractall(atomic_split(H,_,_,_,_)),
  retractall(atomic_ltime(H,_)),
  retractall(atomic_splitted_time(H,_)),
  !, clear_ltimes_upper_loops(H), !,
  global_trace(GT),
  append(LEFT,[gid(_,PragmaGID),gid(C,H)|RIGHT],GT),
  !,
  (
   db_content('prog',PragmaGID,[['preproc']])->
    (
     append(LEFT,[gid(C,H)|RIGHT],GT1),
     retractall(global_trace(_)),
     asserta(global_trace(GT1)),
     pragma_deleted(PragmaGID,H)
    );
    true
  ),
  delete_splitteds(T),
  !.

@process_splits_and_splitteds(0):-!.

% Главный цикл распараллеливания. Предварительно расставлены все возможные splitteds. Итеративный циклический алгоритм. Завершается,
% когда заканчиваются подлежащие удалению splitteds или превышено число итераций N
@process_splits_and_splitteds(N):-
  iterative_splits_times(15), % Расставляем splits (там, где еще не расставлены) и предсказываем время исполнения функций
  retractall(atomic_resplitteds(_)),
  asserta(atomic_resplitteds([])),
  remove_splitteds, % Определяем список splitteds (в списке-параметре факта atomic_resplitteds([...])), которые дают отрицательный эффект
  % для общего времени работы. Они подлежат удалению
  atomic_resplitteds([First|Rest]), % Если список удаляемых splitteds не пуст
  delete_splitteds([First|Rest]), % Удаляем пометки splitteds для неэффективных случаев
  !,
  N1 is N-1,
  process_splits_and_splitteds(N1).

@process_splits_and_splitteds(_):-!.

@populate(_, 0, []):-
  !.

@populate([V], N, [V|T]):-
  N1 is N-1,
  populate([V], N1, T),
  !.

@populate([V,V1|T], N, [V|T1]):-
  N1 is N-1,
  populate([V1|T], N1, T1),
  !.

@replacer(S,What,To,S1):-
  atom_concat(Left,Right,S),
  atom_concat(What,Rest,Right),
  !,
  atom_concat(Left,To,A1),
  replacer(Rest,What,To,Rest1),
  atom_concat(A1,Rest1,S1),
  !.

@replacer(S,_,_,S):-
  !.  

@collect_dims([],''):-
  !.

@collect_dims([V|T],DIMS):-
  collect_dims(T,DIMS1),
  atom_concat('[',V,A1),
  atom_concat(A1,']',A2),
  atom_concat(A2,DIMS1,DIMS),
  !.

@collect_size([],'1','&'):-
  !.

@collect_size([V],A,''):-
  atom_concat('(',V,V1),
  atom_concat(V1,')',A),
  !.

@collect_size([V1,V2|T],SZ,''):-
  collect_size([V2|T],DIMS1,_),
  atom_concat('(',V1,V11),
  atom_concat(V11,')',A11),
  atom_concat(A11,'*',A1),
  atom_concat(A1,DIMS1,SZ),
  !.

@insert_canal(LoopGID,GID,var(Name,Type,SZ),T,D,NewGID,Template):-
  replacer(Template,'$1',Name,Template1),
  replacer(Template1,'$2',Type,Template2),
  collect_dims(SZ,DIMS),
  atom_concat(Type,' ',A1),
  atom_concat(A1,Name,A2),
  atom_concat(A2,DIMS,A3),
  replacer(Template2,'$3',A3,Template3),
  collect_size(SZ,SIZE,S7),
  replacer(Template3,'$4',SIZE,Template4),
  replacer(Template4,'$5',T,Template5),
  replacer(Template5,'$6',D,Template6),
  replacer(Template6,'$7',S7,Template7),
  replacer(Template7,'$8',LoopGID,STR),
  asserta(db_content('prog',NewGID,[['op']])),
  asserta(db_content('args',NewGID,[['op',STR]])),
  once(global_trace(TR)),
  append(Left,[gid(C,GID)|Right],TR),
  append(Left,[gid(C,GID),gid('clsAtomicOper',NewGID)|Right],TR1),
  retractall(global_trace(_)),
  asserta(global_trace(TR1)),
  !.

@insert_canals_internal(_,_,[],[],[],NewGID1,NewGID1,_):-
  !.

@insert_canals_internal(ALoopGID,after(GID),[C|Canals],[T|Tols],[D|Degrees],NewGID1,NewGID2,Template):-
  insert_canal(ALoopGID,GID,C,T,D,NewGID1,Template),
  NewGID3 is NewGID1+1,
  insert_canals_internal(ALoopGID,after(NewGID1),Canals,Tols,Degrees,NewGID3,NewGID2,Template),
  !.

@insert_canals_internal(ALoopGID,before(GID),Canals,Tols,Degrees,NewGID1,NewGID2,Template):-
  global_trace(TR),
  append(_,[gid(_,PrevGID),gid(_,GID)|_],TR),
  insert_canals(ALoopGID,after(PrevGID),Canals,Tols,Degrees,NewGID1,NewGID2,Template),
  !.

@insert_canals(ALoopGID,Dir,Canals,Tols,Degrees,NewGID1,NewGID2,Template):-
  length(Canals, N),
  populate(Tols, N, Tols1),
  populate(Degrees, N, Degrees1),
  insert_canals_internal(ALoopGID,Dir,Canals,Tols1,Degrees1,NewGID1,NewGID2,Template),
  !.

@find_start_only(FirstGID0,FirstGID):-
   atomic_op('clsAtomicOper',FirstGID0,_,_,[arg(_,_,News,_,_,_,_,_)]),
   \+ =(News,[]),
   global_trace(TR),
   append(_,[gid(_,FirstGID0),gid(_,FirstGID1)|_],TR),
   find_start_only(FirstGID1,FirstGID),
   !.

@find_start_only(FirstGID0,FirstGID0):-
   !.

@pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,PragmaGID,SplitGID1,FinalGID1,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,LoopGID,SplitGID1,FinalGID1,Canals1)),
   fail.

@pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,StartGID,PragmaGID,FinalGID1,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,StartGID,LoopGID,FinalGID1,Canals1)),
   fail.

@pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,StartGID,SplitGID,PragmaGID,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,StartGID,SplitGID,LoopGID,Canals1)),
   fail.

@pragma_deleted(_,_):-
   !.

@restructure_loop(PragmaGID, LoopGID, Privates, Tols, Degrees, RestParams):-
  (
   (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(LoopGID,StartGID,SplitGID,FinalGID,Canals))->
     true;
     (
       global_trace(GTD),
       append(LEFT,[gid(_,PragmaGID)|RIGHT],GTD),
       pragma_deleted(PragmaGID,LoopGID),
       append(LEFT,RIGHT,GTPP),
       retractall(global_trace(_)),
       asserta(global_trace(GTPP)),
       fail
     )
  ),
  global_trace(GT),
  append(_,[gid(_,LoopGID),gid(_,BodyGID),gid(_,FirstGID0)|_],GT),
  find_start_only(FirstGID0,FirstGID),
  db_content('prog',BodyGID,[['{']]),
  retractall(db_content('args',PragmaGID,[['body',_]])),
  concat_privates(Privates,PPL),
  (
    =(PPL,'')->
      =(PPL2,'');
      (atom_concat('private(',PPL,PPL1), atom_concat(PPL1, ') ', PPL2))
  ),
  atom_concat(PPL2, RestParams, NewRestParams),
  atom_concat('#pragma omp parallel num_threads(2) ', NewRestParams, NewPragma),
  asserta(db_content('args',PragmaGID,[['body',NewPragma]])),
  NewBegGID is 50*LoopGID+10000,
  NewEndGID is NewBegGID+1,
  NewIdGID is NewBegGID+2,
  NewStartGID is NewBegGID+3,
  NewStartBegGID is NewBegGID+4,
  NewStartEndGID is NewBegGID+5,
  NewTransactBegGID is NewBegGID+6,
  NewPart1GID is NewBegGID+7,
  NewPart1BegGID is NewBegGID+8,
  NewPart1EndGID is NewBegGID+9,
  NewPart2GID is NewBegGID+10,
  NewPart2BegGID is NewBegGID+11,
  NewPart2EndGID is NewBegGID+12,
  NewTransactEndGID is NewBegGID+13,
  NewFinalGID is NewBegGID+14,
  NewFinalBegGID is NewBegGID+15,
  NewFinalEndGID is NewBegGID+16,
  NewTransactionGID is NewBegGID+17,
  AdditionalGID is NewBegGID+18,
  asserta(db_content('prog',NewBegGID,[['{']])),
  asserta(db_content('prog',NewEndGID,[['}']])),
  asserta(db_content('prog',NewIdGID,[['op']])),
  asserta(db_content('args',NewIdGID,[['op','int __id__ = omp_get_thread_num()']])),
  once(global_trace(TR)),
  append(Left,[gid(C,LoopGID)|Right],TR),
  bypass_op([gid(C,LoopGID)|Right],Loop,RIGHT),
  (
    =(C,'clsAtomicDo')->
      append(_,[gid(_,AfterLastGID),gid('clsAtomicWhile',_),gid('clsAtomicOper',_)],Loop);
      append(_,[gid(_,AfterLastGID)],Loop)
  ),
  !,
  append(Left,[gid('clsAtomicBegin',NewBegGID),gid('clsAtomicOper',NewIdGID)|Loop],L1),
  append(L1,[gid('clsAtomicEnd',NewEndGID)|RIGHT],TR1),
  retractall(global_trace(_)),
  asserta(global_trace(TR1)),
  (
   =(StartGID, FirstGID)->
     true;
     (
      asserta(db_content('prog',NewStartGID,[['if']])),
      asserta(db_content('args',NewStartGID,[['cond','__id__ == 0']])),
      asserta(db_content('prog',NewStartBegGID,[['{']])),
      asserta(db_content('prog',NewStartEndGID,[['}']])),
      once(global_trace(TR2)),
      append(Left2,[gid(C2,FirstGID)|Right2],TR2),
      !,
      append(Left2,[gid('clsAtomicIf',NewStartGID),gid('clsAtomicBegin',NewStartBegGID),gid(C2,FirstGID)|Right2],L2),
      append(Left3,[gid(C3,StartGID)|Right3],L2),
      append(Left3,[gid('clsAtomicEnd',NewStartEndGID),gid(C3,StartGID)|Right3],TR3),
      retractall(global_trace(_)),
      asserta(global_trace(TR3)),
      !
     )
  ),
  asserta(db_content('prog',NewTransactionGID,[['preproc']])),
  number_atom(LoopGID,ALoopGID),
  atom_concat('transaction_atomic("',ALoopGID,ALoop1),
  atom_concat(ALoop1,'")',TrID),
  !,
  asserta(db_content('args',NewTransactionGID,[['body',TrID]])),
  asserta(db_content('prog',NewTransactBegGID,[['{']])),
  asserta(db_content('prog',NewTransactEndGID,[['}']])),
  asserta(db_content('prog',NewPart1GID,[['if']])),
  asserta(db_content('args',NewPart1GID,[['cond','__id__ == 0']])),
  asserta(db_content('prog',NewPart1BegGID,[['{']])),
  asserta(db_content('prog',NewPart1EndGID,[['}']])),
  asserta(db_content('prog',NewPart2GID,[['else']])),
  asserta(db_content('prog',NewPart2BegGID,[['{']])),
  asserta(db_content('prog',NewPart2EndGID,[['}']])),
  once(global_trace(TR6)),
  append(Left6,[gid(C6,StartGID)|Right6],TR6),
  !,
  append(Left6,[gid('clsAtomicPreproc',NewTransactionGID),gid('clsAtomicBegin',NewTransactBegGID),
     gid('clsAtomicIf',NewPart1GID),gid('clsAtomicBegin',NewPart1BegGID),gid(C6,StartGID)|Right6],L6),
  append(Left7,[gid(C7,SplitGID)|Right7],L6),
  append(Left7,[gid('clsAtomicEnd',NewPart1EndGID),gid('clsAtomicElse',NewPart2GID),gid('clsAtomicBegin',NewPart2BegGID),
     gid(C7,SplitGID)|Right7],L7),
  append(Left8,[gid(C8,FinalGID)|Right8],L7),
  append(Left8,[gid('clsAtomicEnd',NewPart2EndGID),gid('clsAtomicEnd',NewTransactEndGID),gid(C8,FinalGID)|Right8],TR8),
  retractall(global_trace(_)),
  asserta(global_trace(TR8)),
  insert_canals(ALoopGID,after(NewIdGID),Canals,Tols,Degrees,AdditionalGID,AdditionalGID1,'TOut<$2> * out_$1 = __id__ == 0 ? new TOut<$2>("$1$8", $4, $6, $5, -1, "$8") : NULL'),
  P1 is AdditionalGID1-1,
  insert_canals(ALoopGID,after(P1),Canals,Tols,Degrees,AdditionalGID1,AdditionalGID2,'TIn<$2> * in_$1 = __id__ == 1 ? new TIn<$2>("$1$8", $4, $6, $5, -1, "$8") : NULL'),
  insert_canals(ALoopGID,before(NewEndGID),Canals,Tols,Degrees,AdditionalGID2,AdditionalGID3,'delete out_$1'),
  P2 is AdditionalGID3-1,
  insert_canals(ALoopGID,before(P2),Canals,Tols,Degrees,AdditionalGID3,AdditionalGID4,'delete in_$1'),
  insert_canals(ALoopGID,before(NewPart1EndGID),Canals,Tols,Degrees,AdditionalGID4,AdditionalGID5,'out_$1->put(($2 *)$7$1)'),
  insert_canals(ALoopGID,after(NewPart2BegGID),Canals,Tols,Degrees,AdditionalGID5,AdditionalGID6,'$3'),
  P3 is AdditionalGID6-1,
  insert_canals(ALoopGID,after(P3),Canals,Tols,Degrees,AdditionalGID6,_,'in_$1->get(($2 *)$7$1, 0)'),
  (
   =(FinalGID, AfterLastGID)->
     true;
     (
      asserta(db_content('prog',NewFinalGID,[['if']])),
      asserta(db_content('args',NewFinalGID,[['cond','__id__ == 0']])),
      asserta(db_content('prog',NewFinalBegGID,[['{']])),
      asserta(db_content('prog',NewFinalEndGID,[['}']])),
      once(global_trace(TR4)),
      append(Left4,[gid(C4,FinalGID)|Right4],TR4),
      !,
      append(Left4,[gid('clsAtomicIf',NewFinalGID),gid('clsAtomicBegin',NewFinalBegGID),gid(C4,FinalGID)|Right4],L4),
      append(Left5,[gid(C5,AfterLastGID)|Right5],L4),
      append(Left5,[gid('clsAtomicEnd',NewFinalEndGID),gid(C5,AfterLastGID)|Right5],TR5),
      retractall(global_trace(_)),
      asserta(global_trace(TR5)),
      !
     )
  ),
  !.

@restructure:-
  atomic_splitted(LoopGID,params(_,Privates,Tols,Degrees,RestParams)),
  global_trace(GT),
  append(_,[gid(_,PragmaGID),gid(_,LoopGID)|_],GT),
  call(restructure_loop(PragmaGID, LoopGID,  Privates, Tols, Degrees, RestParams)),
  fail.

@restructure:-
  !.

@insert_transact_h:-
  predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
  atomic_split(_,_,_,_,_),
  !,
  asserta(db_content('prog',1000000,[['preproc']])),
  asserta(db_content('args',1000000,[['body','#include "transact.h"']])),
  asserta(db_content('prog',1000002,[['preproc']])),
  asserta(db_content('args',1000002,[['body','#define split_private /* split-private */']])),
  once(global_trace(TR)),
  retractall(global_trace(_)),
  asserta(global_trace([gid('clsAtomicPreproc',1000000),gid('clsAtomicPreproc',1000002)|TR])),
  !.

@insert_transact_h:-
  !.

@processing:-
  g_assign('$DefFTime', 15.0), % Время исполнения функции/процедуры по умолчанию (внешней или внутренней до расчета)
  g_assign('$SplittedTime', 25.0), % Время исполнения splitted по умолчанию
  g_assign('$DefOperTime', 1.0), % Время исполнения элементарного математического выражения без функций по умолчанию
  prepare_atomic,
  retractall(atomic_split(_,_,_,_,_)),
  process_splits_and_splitteds(5),
  restructure,
  insert_transact_h,
  recreate_program('_atomic.cpp').

@collect_global_trace:-
  prog(Cls, GID, _, _),
  global_trace(G),
  number_atom(NGID, GID),
  append(G, [gid(Cls, NGID)], GNEW),
  retractall(global_trace(_)),
  asserta(global_trace(GNEW)),
  fail.

@collect_global_trace:-
  !.

@atomic_debug:-
  asserta(global_trace([])),
  collect_global_trace,
  processing.

@goal:-
  atomic_debug.
};

#endif
