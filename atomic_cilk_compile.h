#ifndef __ATOMIC_CILK_COMPILE_H__
#define __ATOMIC_CILK_COMPILE_H__

#parse(clsProgram,clsSpace,clsInclude,clsPreproc,clsComments,clsTypedef,clsCVar,clsFunction,clsFor,clsSwitch,clsWhile,clsIf,clsElse,clsDo,clsAlternation,clsReturn,clsOper,clsBegin,clsEnd,clsTerminator)

#preproc_passes(1,"_atomic_cilk.cpp")

#def_pattern clsAlternation => [prog] ('clsAlternation', gid(), /root/TYPE/@Value, [['arg', /root/CASE/@Value]]) {
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

#def_pattern clsBegin => [prog] ('clsBegin', gid(), '{', '') {
  (((^)|(\;)+|\}|\{|\\n|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\{)
    (\s|\\t)*
  @end
};

#def_pattern clsComments => [comment] ('clsComments', gid(), /root/CONTENT/@Value) {
  @begin
    ((\/\/([^\\]*)->{CONTENT}(\\n))|(\/\*(.*?)->{CONTENT}\*\/))
  @end
};

#def_pattern clsCVar => [prog] ('clsCVar', gid(), /root/TYPE/@Value, [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (struct|union)->{TYPE}(\\n|\s|\\t)+
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')})
    (\s|\\t)*
  @end
};

#def_pattern clsDo => [prog] ('clsDo', gid(), 'do', '') {
  (((^)|(\;)+|\}|\{|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (do)
  @end
  (\s|\\t)*
  ((\s|\{|\\n|\\t))
  (\s|\\t)*
};

#def_pattern clsElse => [prog] ('clsElse', gid(), 'else', '') {
  (((\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (else)
  @end
  (\s|\\t)*
  (\s|\{|\\n|\\t)
  (\s|\\t)*
};

#def_pattern clsEnd => [prog] ('clsEnd', gid(), '}', '') {
  (((\;)+|\}|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ()->{GID}
    (\s|\\t)*
    (\})
    (\s|\\t)*
  @end
};

#def_pattern clsFor => [prog] ('clsFor', gid(), 'for', [['init', /root/INITF/@Value],['init', /root/INITN/@Value],['cond', /root/COND/@Value],['chng', /root/CHNGF/@Value],['chng', /root/CHNGN/@Value]]) {
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

#def_pattern clsFunction => [prog] ('clsFunction', gid(), 'func', [['arg', //FIRST_REF/@Value], ['type', //FIRST_TYPE/@Value], ['arg', //FIRST/@Value], ['idxs', //FIRST_IDXS/@Value], ['arg', //OTHER_REF/@Value], ['type', //OTHER_TYPE/@Value], ['arg', //OTHER/@Value], ['idxs', //OTHER_IDXS/@Value], ['arg', //THREEP/@Value], ['args', /root/ARGS/@Value], ['ret', /root/RETTYPE/@Value], ['name', /root/ID/@Value]]) {
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

#def_pattern clsIf => [prog] ('clsIf', gid(), 'if', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (if(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsInclude => [include] ('clsInclude', gid(), /root/FILE/@Value) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#include(\s|\\t)*\x22([^\x22]+)->{FILE}\x22(\\n|($))
    )
    (\s|\\t)*
  @end
};

#def_pattern clsOper => [prog] ('clsOper', gid(), 'op', [['op', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    ((([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsPreproc => [prog] ('clsPreproc', gid(), 'preproc', [['body', /root/BODY/@Value]]) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#([^\\]*\\\\\\n)*[^\\]*(\\n|($))
    )->{BODY}
    (\s|\\t)*
  @end
};

#def_pattern clsReturn => [prog] ('clsReturn', gid(), 'return', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (return(\\n|\s|\\t)+(([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
    )
    (\s|\\t)*
  @end
};

#def_pattern clsSwitch => [prog] ('clsSwitch', gid(), 'switch', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (switch(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{EXPR}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsTypedef => [prog] ('clsTypedef', gid(), 'type', [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\)|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    typedef((\\n|\s|\\t)+)
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsWhile => [prog] ('clsWhile', gid(), 'while', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (while(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsTerminator => parallelize (gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() parallelize(AfterLastID) {
@goal:-brackets_off.

% #pragma auto for -- включает Cilk-автораспараллеливание циклов
% #pragma auto pure(fun1,fun2,...) -- обозначает функции без сторонних эффектов по отношению к текущей итерации цикла for
% #pragma auto split(auto|(var1[N1],var2[N1][N2],var3,...)) [omp-params] -- помечает цикл как потенциально параллелизуемый расщеплением
% split_private type var-decl -- помечает переменную как локальную при распараллеливании циклов. Такие переменные попадают в private-пометки,
%   если они не указаны явно
% #pragma auto parallelize -- Atomic-распараллеливает циклы, насколько возможно

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

@clk_into_paired_list_f(_, [], []).

@clk_into_paired_list_f(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(clk_into_paired_list_f(TYPE, T, LL)).

@clk_into_paired_list_f(TYPE, V, [[TYPE, V]]).

@clk_strip_list_f([[arg,''], [idxs,'']], []).

@clk_strip_list_f(L, L).

@clk_into_paired_list(_, '', []).

@clk_into_paired_list(_, [], []).

@clk_into_paired_list(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(clk_into_paired_list(TYPE, T, LL)).

@clk_into_paired_list(TYPE, V, [[TYPE, V]]).

@clk_make_arg(TYPE, F, N, L):-
  once(clk_into_paired_list(TYPE, F, L1)),
  once(clk_into_paired_list(TYPE, N, L2)),
  append(L1, L2, L).

@clk_make_fargs([], [], [], []).

@clk_make_fargs([['arg','']|REFT],[NM|NMT],[IDXS|IDXST], [NM,IDXS|T]):-
  once(clk_make_fargs(REFT, NMT, IDXST, T)).

@clk_make_fargs([REF|REFT],[NM|NMT],[IDXS|IDXST], [REF,NM,IDXS|T]):-
  once(clk_make_fargs(REFT, NMT, IDXST, T)).

@clk_analyze_args(_, _, '').

@clk_analyze_args(GID, _, [[Name, Val]]):-
  asserta(db_content('args', GID, [[Name, Val]])).

@clk_analyze_args(GID, 'for', [['init',INITF], ['init',INITN], ['cond',COND], ['chng',CHNGF], ['chng',CHNGN]]):-
  once(clk_make_arg('init', INITF, INITN, L1)),
  once(clk_make_arg('chng', CHNGF, CHNGN, L2)),
  append(L1, [['cond',COND]], L3),
  append(L3, L2, L4),
  asserta(db_content('args', GID, L4)).

@clk_analyze_args(GID, 'func', [['arg',REF1], ['type',_], ['arg',NM1], ['idxs',IDXS1], ['arg',REFN], ['type',_], ['arg',NMN], ['idxs',IDXSN], ['arg',THREEP], ARGSV, RETV, NAMEV]):-
  once(clk_into_paired_list_f('arg', REF1, REF1L)),
  once(clk_into_paired_list_f('arg', NM1, NM1L)),
  once(clk_into_paired_list_f('idxs', IDXS1, IDXS1L)),
  once(clk_make_fargs(REF1L, NM1L, IDXS1L, L1)),
  once(clk_strip_list_f(L1, L11)),
  once(clk_into_paired_list_f('arg', REFN, REFNL)),
  once(clk_into_paired_list_f('arg', NMN, NMNL)),
  once(clk_into_paired_list_f('idxs', IDXSN, IDXSNL)),
  once(clk_make_fargs(REFNL, NMNL, IDXSNL, L2)),
  once(clk_strip_list_f(L2, L22)),
  append(L11, L22, LM),
  once((
    =(THREEP, '...')->
     append(LM, [['arg', '...']], LK);
     =(LK, LM)
  )),
  append(LK, [ARGSV, RETV, NAMEV], LL),
  asserta(db_content('args', GID, LL)).

@clk_read_db:-
  prog(_, GID, TYPE, ARGS),
  number_atom(NGID, GID),
  asserta(db_content('prog', NGID, [[TYPE]])),
  clk_analyze_args(NGID, TYPE, ARGS),
  fail.

@clk_read_db:-
  !.

@clk_number_sym(C):-
  member(C, ['0','1','2','3','4','5','6','7','8','9']),
  !.

@clk_ident_first_sym(C):-
  member(C, ['_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']),
  !.

@clk_ident_other_sym(C):-
  (
   clk_ident_first_sym(C) -> true; clk_number_sym(C)
  ),
  !.

@clk_find_ident2([Sym|Tag], Id, Rest):-
  clk_ident_other_sym(Sym),
  clk_find_ident2(Tag, TId, Rest),
  atom_concat(Sym, TId, Id),
  !.
@clk_find_ident2(L, '', L):-!.

@clk_find_ident([Sym|Tag], Id, Rest):-
  clk_ident_first_sym(Sym),
  !,
  clk_find_ident2(Tag, S, Rest),
  atom_concat(Sym, S, Id),
  !.

@clk_find_intn([Sym|Tag], Num, Rest):-
  clk_number_sym(Sym),
  clk_find_intn(Tag, TNum, Rest),
  atom_concat(Sym, TNum, Num),
  !.
@clk_find_intn(L, '', L):-!.

@clk_find_int2([Sym|Tag], Num, Rest):-
  clk_number_sym(Sym),
  clk_find_intn([Sym|Tag], Num, Rest),
  !.

@clk_find_int([Sym|Tag], Num, Rest):-
  clk_number_sym(Sym),
  clk_find_ident2(Tag, T, Rest),
  atom_concat(Sym, T, Num),
  !.

@clk_find_real(L, Num, Rest):-
  clk_find_int2(L, _, R1),
  (append(['.'], R2, R1), clk_find_int2(R2, _, R3); =(R3, R1)),
  (append(['E'], R4, R3); append(['e'], R4, R3)),
  !,
  (append(['+'], R5, R4); append(['-'], R5, R4); =(R5, R4)),
  !,
  clk_find_ident2(R5, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@clk_find_real(L, Num, Rest):-
  clk_find_int2(L, _, R1),
  append(['.'], R2, R1),
  clk_find_ident2(R2, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@clk_parse_string(_,[], [], []):-!,fail.

@clk_parse_string(Delim, [Delim,Delim|T], [Delim|S1], Rest):-
  clk_parse_string(Delim, T, S1, Rest),
  !.

@clk_parse_string(Delim, [Delim|T], [], T):-
  !.

@clk_parse_string(Delim, [H|T], [H|S1], R):-
  clk_parse_string(Delim, T, S1, R),
  !.

@clk_parse_expr2([], []):-!.

@clk_parse_expr2([First|RR], L):-
  member(First, [' ', '\t', '\n', '\r']),
  clk_parse_expr2(RR, L).

@clk_parse_expr2(CL, L):-
  append(['\\', '\\', 'n'], RR, CL),
  clk_parse_expr2(RR, L).

@clk_parse_expr2(CL, L):-
  append(['\\', '\\', 't'], RR, CL),
  clk_parse_expr2(RR, L).

@clk_parse_expr2(['"'|RR], [dstring(H)|T]):-
  clk_parse_string('"', RR, HH, Rest),
  atom_chars(H,HH),
  clk_parse_expr2(Rest, T).

@clk_parse_expr2(['/','*'|RR], T):-
  append(_,['*','/'|Rest],RR),
  !,
  clk_parse_expr2(Rest, T).

@clk_parse_expr2([''''|RR], [cstring(H)|T]):-
  clk_parse_string('''', RR, HH, Rest),
  atom_chars(H,HH),
  clk_parse_expr2(Rest, T).

@clk_parse_expr2(CL, [H|T]):-
  append([First], RR, CL),
  (
   clk_ident_other_sym(First)->(
    (
     (clk_find_real(CL, HH, R),
      =(H, real(HH)));
     (clk_find_int(CL, HH, R),
      =(H, integ(HH)));
     (clk_find_ident(CL, HH, R),
      =(H, id(HH)))
    ),
    !,
    clk_parse_expr2(R, T)
   );(
     =(H, First),
     !,
     clk_parse_expr2(RR, T)
   )
  ),
  !.

@clk_parse_expr(S,L):-
  atom_chars(S,CL),
  clk_parse_expr2(CL, L).

@clk_get_balanced(Depth,['('|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  clk_get_balanced(Depth1,T,Delims,BAL0,[')'|R0]),
  clk_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['('|BAL0],[')'|BAL1],BAL),
  !.

@clk_get_balanced(Depth,['['|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  clk_get_balanced(Depth1,T,Delims,BAL0,[']'|R0]),
  clk_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['['|BAL0],[']'|BAL1],BAL),
  !.

@clk_get_balanced(Depth,['{'|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  clk_get_balanced(Depth1,T,Delims,BAL0,['}'|R0]),
  clk_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['{'|BAL0],['}'|BAL1],BAL),
  !.

@clk_get_balanced(Depth,[H|T],_,[],[H|T]):-
  \+ =(Depth,0),
  member(H,[')',']','}']),
  !.

@clk_get_balanced(Depth,[H|T],Delims,[],[H|T]):-
  =(Depth,0),
  member(H,Delims),
  !.

@clk_get_balanced(Depth,[H|T],Delims,[H|T1],Rest):-
  clk_get_balanced(Depth,T,Delims,T1,Rest),
  !.

@clk_get_balanced(0,[],_,[],[]):-!.

@clk_get_balanced(_,[],_,_,_):-!,fail.

@clk_union([H|T], L, L1):-
  member(H, L),
  clk_union(T, L, L1),
  !.
@clk_union([H|T], L, [H|T1]):-
  clk_union(T, L, T1),
  !.
@clk_union([], L, L):-!.

@clk_intersect([], _, []):-!.

@clk_intersect(_, [], []):-!.

@clk_intersect([H|T],V,[H|T1]):-
   member(H,V),
   !,
   subtract(V,[H],V1),
   !,
   clk_intersect(T,V1,T1),
   !.

@clk_intersect([_|T],V,T1):-
   clk_intersect(T,V,T1).

@clk_unique([],[]):-!.

@clk_unique([H|T],L):-
   append(Left,[H|Right],T),
   append(Left,Right,T1),
   !,
   clk_unique([H|T1],L),
   !.

@clk_unique([H|T],[H|T1]):-
   clk_unique(T,T1),
   !.

@clk_bypass_idxs(['['|T],T1,INS,OUTS,FUNS,Lazies):-
   clk_get_balanced(0,T,[']'],EXPR,[']'|T0]),
   clk_get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   clk_bypass_idxs(T0,T1,INS1,OUTS1,FUNS1,LZ1),
   clk_union(INS0,INS1,INS), clk_union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), clk_union(LZ0,LZ1,Lazies),
   !.

@clk_bypass_idxs(L,L,[],[],[],[]):-!.

@clk_rbypass_idxs(L,L1,INS,OUTS,FUNS,Lazies):-
   last(L,']'),
   !,
   append(Left1,['['|Right1],L),
   clk_get_balanced(0,Right1,[']'],EXPR,[']']),
   clk_get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   clk_rbypass_idxs(Left1,L1,INS1,OUTS1,FUNS1,LZ1),
   clk_union(INS0,INS1,INS), clk_union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), clk_union(LZ0,LZ1,Lazies),
   !.

@clk_rbypass_idxs(L,L,[],[],[],[]):-!.

@clk_rbypass_var(L,V,R,INS,OUTS,FUNS,Lazies):-
   clk_rbypass_idxs(L,R0,INS0,OUTS0,FUNS0,LZ0),
   append(Left,[id(VV)],R0),
   !,
   (
    ( append(Left1,['.'],Left); append(Left1,['-','>'],Left) )->
     (
      clk_rbypass_var(Left1,V,R,INS1,OUTS1,FUNS1,LZ1),
      clk_union(INS0,INS1,INS), clk_union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), clk_union(LZ0,LZ1,Lazies)
     );
     (=(V,VV),=(R,Left),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0))
   ),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['<','<','='|Right],L),
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['>','>','='|Right],L),
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,[A,'='|Right],L),
   member(A,['+','-','*','/','|','&','^','%']),
   !,
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+'|Right],L),
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-'|Right],L),
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+',id(V)|Right],L),
   clk_bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-',id(V)|Right],L),
   clk_bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,[V|OUTST],Ins,Funs,Lazs):-
   append(Left,['='|Right],L),
   last(Left,A),
   \+ member(A,['=','!','<','>']),
   \+ =(Right,['='|_]),
   !,
   clk_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   clk_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   clk_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   clk_union(OUTST1,OUTST2,OUTST3), clk_union(OUTST3,Outs0,OUTST),
   clk_union(Ins1,Ins2,Ins3), clk_union(Ins3,Ins0,Ins),
   clk_union(Funs1,Funs2,Funs3), clk_union(Funs3,Funs0,Funs),
   clk_union(Laz1,Laz2,Laz3), clk_union(Laz3,Laz0,Lazs),
   !.

@clk_get_assgns(L,Outs,Ins,Funs,Lazs):-
   clk_get_vars(L,Ins,Outs,Funs,Lazs),
   !.

@clk_bypass_var([id(_)|T],R,INS,OUTS,FUNS,Lazies):-
   clk_bypass_idxs(T,R0,INS0,OUTS0,FUNS0,LZ0),
   (
    ( =(['.'|R1],R0); =(['-','>'|R1],R0) )->
     (
      clk_bypass_var(R1,R,INS1,OUTS1,FUNS1,LZ1),
      clk_union(INS0,INS1,INS), clk_union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), clk_union(LZ0,LZ1,Lazies)
     );(
      =(R,R0),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0)
     )
   ),
   !.

@clk_glob_prefixate([],[]):-!.

@clk_glob_prefixate([H|T],[global(H)|T1]):-
   clk_glob_prefixate(T,T1).

@clk_get_glob_lazies(Fun,NPrms,GP,LP,ILP):-
   cilk_function(Fun,GID,NPrms),
   predicate_property(cilk_fanalyzed(_,_,_,_,_),'dynamic'),
   cilk_fanalyzed(Fun,GID,Globs,LP,ILP),
   clk_glob_prefixate(Globs, GP),
   !.

@clk_get_glob_lazies(_,_,[],0,[]):-!.

@clk_get_ftime(Fun,NPrms,T):-
   cilk_function(Fun,GID,NPrms),
   predicate_property(cilk_ftime(_,_,_),'dynamic'),
   cilk_ftime(Fun,GID,T),
   !.

@clk_get_ftime(_,_,T):-  % Содержит время исполнения функции по умолчанию
  g_read('$DefFTime',T),
  !.

@clk_put_ftime(Fun,NPrms,T):-
   cilk_function(Fun,GID,NPrms),
   (
    (predicate_property(cilk_ftime(_,_,_),'dynamic'), cilk_ftime(Fun,GID,T0))->(
         D is T-T0,
         (
          ;(<(D,-1),>(D,1))->(
             retractall(cilk_ftime(Fun,GID,_)),
             asserta(cilk_ftime(Fun,GID,T)),
             retractall(cilk_retime),
             asserta(cilk_retime)
            );
            true
         )
       );(
         retractall(cilk_retime),
         asserta(cilk_retime),
         asserta(cilk_ftime(Fun,GID,T))
       )
   ),
   !.

@clk_put_for_time(GID,T):-
   (
    (predicate_property(cilk_for_time(_,_),'dynamic'), cilk_for_time(GID,T0))->(
         D is T-T0,
         (
          ;(<(D,-1),>(D,1))->(
             retractall(cilk_for_time(GID,_)),
             asserta(cilk_for_time(GID,T))
            );
            true
         )
       );(
         asserta(cilk_for_time(GID,T))
       )
   ),
   !.

@clk_getTime([],T):-
   g_read('$DefOperTime', T),
   !.

@clk_getTime([V|T],TM):-
   =..(V,[_,F,Prms]),
   length(Prms,N),
   clk_get_ftime(F,N,T0),
   clk_getTime(T,T1),
   TM is T0+T1,
   !.

@clk_extract_singles([],[]):-!.

@clk_extract_singles([[]|T],L):-
  clk_extract_singles(T,L),
  !.

@clk_extract_singles([[V]|T],[V|L]):-
  clk_extract_singles(T,L),
  !.

% Анализ вызова функций на предмет наличия ленивых переменных (модифицируемых глобальных и модифицируемых &|*-параметров)
% Если уже есть результаты предварительного анализа в фактах cilk_fanalyzed, то данные о "ленивости" берутся из них, если же их
% нет, то считается, что глобальных ленивых переменных для этой функции нет, а ленивыми являются все &|*-параметры
% Во втором параметре принимает список разобранных параметров, каждый из которых = список токенов
% В третьем параметре возвращает список ленивых переменных [global(имя),...,par(функция,имя_параметра,переданная переменная),...]
% В четвертом параметре возвращается список имен, переданных в неленивые &|* - параметры
% В пятом параметре принимается список-карта переданных значений. Элемент = множество из одного элемента (имя переданной переменной)
%  или пустое множество (если в параметре передано выражение).
% В шестом параметре возвращается список имен переданных в качестве параметров переменных, значения которых используются на чтение в функции
@clk_get_lazies(Fun, [], GP, [], _, []):-
     clk_get_glob_lazies(Fun,0,GP,_,_),
     !.

@clk_get_lazies(Fun, Params, [], _, ParSingleMap, _):-
   predicate_property(cilk_farg(_,_,_,_),'dynamic')->(
     length(Params,N),
     once(cilk_farg(Fun,N,_,_)),
     asserta(counter(0)),
     clk_get_glob_lazies(Fun,N,GP,LP,ReadParams),
     asserta(params(GP)),
     asserta(isingles([])),
     asserta(refs([])),
     cilk_farg(Fun,_,REF,V),
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
     clk_bypass_var([id(P)|TT],[],_,_,_,_),
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

@clk_get_lazies(_, Params, LZ, Refs, _, ISingles):-
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

@clk_get_lazies(_, _, [], [], ParSingleMap, ISingles):-
   clk_extract_singles(ParSingleMap,ISingles),
   !.

@clk_get_fparams(Mode, Fun, NPrms, []):-
   predicate_property(cilk_farg(_,_,_,_),'dynamic')->(
     once(cilk_farg(Fun,NPrms,_,_)),
     asserta(counter(0)),
     asserta(params([])),
     cilk_farg(Fun,_,REF,V),
     once(counter(I)),
     I1 is I+1,
     retract(counter(I)),
     asserta(counter(I1)),
     (
      =(Mode,lazy)->once(member(REF,['&','*','**','***','[]']));true
     ),
     once(params(LZ)),
     retract(params(_)),
     once(append(LZ,[V],LZ1)),
     asserta(params(LZ1)),
     fail
   );(
     true,!
   ).

@clk_get_fparams(_, _, NPrms, LZ):-
   predicate_property(params(_),'dynamic'),
   params(LZ),
   counter(NPrms),
   retractall(params(_)),
   retractall(counter(_)),
   !.

@clk_get_fparams(_, _, _, []):-!.

@clk_get_funs(L,[func(F,Params)|T],INS,OUTS,Lazies):-
   append(_,[id(F),'('|Right],L),
   !,
   clk_get_fun_params(F,Right,[')'|Rest],Params,INS0,ParSingleMap,OUTS0,FUNS0,LZZ),
   !,
   clk_get_lazies(F,Params,LZ0,_,ParSingleMap,INSI),
   !,
   clk_get_funs(Rest,FUNS1,INS1,OUTS1,LZ1),
   clk_union(OUTS0,OUTS1,OUTS),
   clk_union(INS0,INS1,INS2), clk_union(INS2,INSI,INS),
   append(FUNS0,FUNS1,T),
   clk_union(LZZ,LZ0,LZ2),
   clk_union(LZ2,LZ1,Lazies),
   !.

@clk_get_funs(_,[],[],[],[]):-!.

@clk_extract_lzv([],[]):-!.

@clk_extract_lzv([par(_,_,V)|T],[V|T1]):-
   clk_extract_lzv(T,T1),
   !.

@clk_extract_lzv([global(V)|T],[V|T1]):-
   clk_extract_lzv(T,T1),
   !.

@clk_get_vars([],[],[],[],[]):-!.

@clk_get_vars([id(V),A|T],[V|TT],Outs,FUNS,Lazies):-
   \+ =(A,'('),
   clk_bypass_var([id(V),A|T],T0,INS0,OUTS0,FUNS0,LZ0),
   !,
   clk_get_vars(T0,INS1,OUTS1,FUNS1,LZ1),
   clk_union(INS0,INS1,TT), clk_union(OUTS0,OUTS1,Outs),
   append(FUNS0,FUNS1,FUNS), clk_union(LZ0,LZ1,Lazies).

@clk_get_vars([id(_),'('|T],Ins,Outs,FUNS,Lazies):-
   clk_get_balanced(0,T,[')'],_,[')'|T0]),
   !,
   clk_get_vars(T0,Ins,Outs,FUNS,Lazies).

@clk_get_vars([id(V)],[V],[],[],[]):-
   !.

@clk_get_vars([_|T],INS,OUTS,FUNS,Lazies):-
   clk_get_vars(T,INS,OUTS,FUNS,Lazies).   

@clk_get_expr(L,INS,OUTS,FUNS,Lazies):-
   clk_get_assgns(L,OUTS0,INS0,FUNSV,LZV),!,
   clk_get_funs(L,FUNS0,INS1,OUTS1,LZ0),
   clk_union(INS0,INS1,INS2),
   clk_unique(INS2,INS),
   clk_union(OUTS0,OUTS1,OUTS2),
   clk_unique(OUTS2,OUTS20), !,
   append(FUNS0,FUNSV,FUNS),
   clk_union(LZ0,LZV,LZB),
   clk_unique(LZB,Lazies),
   clk_extract_lzv(Lazies,LaziesV),
   clk_union(OUTS20,LaziesV,OUTSZ),
   clk_unique(OUTSZ,OUTS),
   !.

@clk_check_arg([id(V)|Rest],[V]):-
   clk_bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@clk_check_arg(['&',id(V)|Rest],[V]):-
   clk_bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@clk_check_arg(_,[]):-
   !.

@clk_get_fun_params(_,[')'|R],[')'|R],[],[],[],[],[],[]):-!.

@clk_get_fun_params(Fun,L,R,[P|T],INS,[V|MAP],OUTS,FUNS,Lazies):-
   clk_get_balanced(0,L,[',',')'],P,[','|Rest]),
   clk_get_expr(P,INS1,OUTS1,FUNS1,LZ1),
   ((cilk_function(Fun,_,_),=(OUTS3,[]));clk_check_arg(P,OUTS3)),
   clk_check_arg(P,V),
   !,
   clk_get_fun_params(Fun,Rest,R,T,INS2,MAP,OUTS2,FUNS2,LZ2),
   (
    =(V,[Single])->
      subtract(INS1,[Single],INSQ);
      =(INSQ,INS1)
   ),
   clk_union(INSQ,INS2,INS),
   clk_union(OUTS1,OUTS2,OUTSK), clk_union(OUTSK,OUTS3,OUTS), append(FUNS1,FUNS2,FUNS), clk_union(LZ1,LZ2,Lazies),
   !.

@clk_get_fun_params(Fun,L,[')'|Rest],[Item],INS,[V],OUTS,FUNS,Lazies):-
   clk_get_balanced(0,L,[',',')'],Item,[')'|Rest]),
   clk_get_expr(Item,INS1,OUTS0,FUNS,Lazies),
   ((cilk_function(Fun,_,_),=(OUTS3,[]));clk_check_arg(Item,OUTS3)),
   clk_check_arg(Item,V),
   !,
   (
    =(V,[Single])->
      subtract(INS1,[Single],INS);
      =(INS,INS1)
   ),
   clk_union(OUTS0,OUTS3,OUTS),
   !.

@clk_analyze_item_expr(intros,[id(V)|T],INS,[V|OUTT],[V],FUNS,[],[],[]):-
   clk_bypass_idxs(T,['='|Rest],INS0,OUTS0,FUNS0,_),
   \+ =(Rest,['='|_]),
   clk_get_expr(Rest,INS1,OUTS1,FUNS1,_),
   !,
   clk_union(INS0,INS1,INSA), clk_union(OUTS0,OUTS1,OUTTA), append(FUNS0,FUNS1,FUNS),
   clk_unique(INSA,INS), clk_unique(OUTTA,OUTT),
   !.

@clk_analyze_item_expr(intros,[id(V)|T],INS,[V|OUTS],[V],FUNS,[],[],LAZIES):-
   clk_bypass_idxs(T,[],INS,OUTS,FUNS,LAZIES),
   !.

@clk_analyze_item_expr(inits,[id(V),'('|T],INS,OUTS,[],FUNS,[proc(V,L)],REFS,Lazies):-
   clk_get_fun_params(V,T,[')'],L,INS0,ParSingleMap,OUTS0,FUNS,LZ0),
   !,
   clk_get_lazies(V,L,Lazies,Refs0,ParSingleMap,INSI),
   !,
   % clk_get_lazies возвращает ленивые выходные переменные Lazies уже с учетом результатов анализа. Возвращает Refs0 -- переменные
   % в параметрах &|*, не являющиеся выходными. Возвращает INSI -- все входные переменные в параметрах, используемые в функции
   clk_extract_lzv(LZ0,LZV),
   clk_union(OUTS0,LZV,OUTP),
   clk_extract_lzv(Lazies,LaziesV),
   subtract(Refs0,LaziesV,REFS),
   clk_union(OUTP,LaziesV,OUTS2),
   clk_unique(OUTS2,OUTS),
   clk_union(INS0,INSI,INS2), clk_unique(INS2,INS),
   !.

@clk_analyze_item_expr(inits,L,INS,OUTS,[],FUNS,[expr],[],[]):-
   clk_get_expr(L,INS,OUTS,FUNS,_),
   !.

@clk_analyze_list_expr(_,[],[],[],[],[],[],[],[]):-!.

@clk_analyze_list_expr(Mode,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   clk_get_balanced(0,L,[','],Item,Rest),
   (=([','|T],Rest)->true;=(T,Rest)),
   !,
   clk_analyze_item_expr(Mode,Item,INS0,OUTS0,NEWS0,FUNS0,PROCS0,REFS0,LZ0),
   !,
   clk_analyze_list_expr(Mode,T,INS1,OUTS1,NEWS1,FUNS1,PROCS1,REFS1,LZ1),
   clk_union(INS0,INS1,INS2),
   clk_union(OUTS0,OUTS1,OUTS2),
   clk_union(NEWS0,NEWS1,NEWS2),
   append(FUNS0,FUNS1,FUNS),
   clk_union(PROCS0,PROCS1,PROCS2),
   clk_union(REFS0,REFS1,REFS2),
   clk_union(LZ0,LZ1,LZ2),
   !,
   clk_unique(INS2,INS), clk_unique(OUTS2,OUTS), clk_unique(NEWS2,NEWS),
   clk_unique(PROCS2,PROCS), clk_unique(REFS2,REFS), clk_unique(LZ2,Lazies),
   !.

@clk_declaration([id(_)]):-!.

@clk_declaration([id(_)|T]):-
  clk_declaration(T).

% clk_analyze_expr(parsed_list,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES)
% INS -- список переменных, значения которых = входные для выражения
% OUTS -- список переменных, которые в выражении получают значения в результате ПРИСВАИВАНИЙ (простых и совмещенных) и в &-параметрах
%           функций (не ленивых). Ленивая -- только главная функция! Новые переменные выходными НЕ ЯВЛЯЮТСЯ!
% NEWS -- переменные, декларированные в текущем выражении
% FUNS -- список элементов func(V,L) = вызываемых функций с именами V и списками аргументов L
% PROCS -- список элементов proc(V,L) = вызываемых процедур с именами V и списками аргументов L. В норме -- список из одного элемента
% REFS -- список выходных (&,*)-параметров в процедуре, не относящихся к ленивым. Они не получают в такой процедуре значения
% LAZIES -- список потенциально ленивых переменных = выходных (&,*) в процедуре. Не имеет прямого отношения к OUTS, ДОЛЖЕН с ним пересекаться
@clk_analyze_expr([],[],[],[],[],[],[],[]):-!.

@clk_analyze_expr(['*'|Rest],Ins,Outs,News,Funs,Procs,Refs,Lazies):-
   clk_analyze_expr(Rest,Ins,Outs,News,Funs,Procs,Refs,Lazies),
   !.

@clk_analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*',id(V1)],L),
   clk_declaration(D),
   !.

@clk_analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*','*',id(V1)],L),
   clk_declaration(D),
   !.

@clk_analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*','*','*',id(V1)],L),
   clk_declaration(D),
   !.

@clk_analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['&',id(V1)],L),
   clk_declaration(D),
   !.

@clk_analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,[id(V1)],L),
   clk_declaration(D),
   !.

@clk_analyze_expr([id(V)],[V],[],[],[],[],[],[]):-
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*',id(V1),A|T1],L),
   clk_declaration(D),
   member(A,['=',',','[']),
   !,
   clk_analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*',id(V1),A|T1],L),
   clk_declaration(D),
   member(A,['=',',','[']),
   !,
   clk_analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*','*',id(V1),A|T1],L),
   clk_declaration(D),
   member(A,['=',',','[']),
   !,
   clk_analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['&',id(V1),A|T1],L),
   clk_declaration(D),
   member(A,['=',',','[']),
   !,
   clk_analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,[id(V1),A|T1],L),
   clk_declaration(D),
   member(A,['=',',','[']),
   !,
   clk_analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   clk_analyze_list_expr(inits,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies),
   !.

@clk_get_params_length([], 0):-!.

@clk_get_params_length([[arg,'...']],infinity):-!.

@clk_get_params_length([[idxs,_]|T], N):-
   clk_get_params_length(T,N),
   !.

@clk_get_params_length([[arg,'&']|T], N):-
   clk_get_params_length(T,N),
   !.

@clk_get_params_length([[arg,'*']|T], N):-
   clk_get_params_length(T,N),
   !.

@clk_get_params_length([[arg,'**']|T], N):-
   clk_get_params_length(T,N),
   !.

@clk_get_params_length([[arg,'***']|T], N):-
   clk_get_params_length(T,N),
   !.

@clk_get_params_length([_|T], N1):-
   clk_get_params_length(T,N),
   (
    =(N,infinity)->
     =(N1,infinity);
     N1 is N+1
   ),
   !.

@clk_prepare_cilk_function(_,_,[]):-!.

@clk_prepare_cilk_function(Name,N,[[name,Name]|T]):-
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[ret,_]|T]):-
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[args,_]|T]):-
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,V],[idxs,Idxs]|T]):-
   \+ atom_length(Idxs,0),
   assertz(cilk_farg(Name,N,'[]',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,'&'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'&',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,'*'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'*',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,'**'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'**',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,'***'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'***',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_function(Name,N,[[arg,V],[idxs,'']|T]):-
   assertz(cilk_farg(Name,N,'',V)),
   !,
   clk_prepare_cilk_function(Name,N,T).

@clk_prepare_cilk_functions:-
   global_trace(TR),
   db_content('prog',GID,[[func]]),
   db_content('args',GID,Params),
   once(append(_,[gid('clsFunction',GID),gid('clsBegin',_)|_],TR)),
   member([name,Name],Params),
   clk_get_params_length(Params,N),
   \+ =(N,infinity),
   N1 is N-3, % -args, -ret, -name
   asserta(cilk_function(Name,GID,N1)),
   call(clk_prepare_cilk_function(Name,N1,Params)),
   fail.

@clk_prepare_cilk_functions:-!.

@clk_prepare_ifor([],_,[]):-!.

@clk_prepare_ifor([[Type,V]|T],Type,[VAL|TT]):-
   clk_parse_expr(V,L),
   !,
   clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !,
   =..(VAL,[Type,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L]]),
   clk_prepare_ifor(T,Type,TT).

@clk_prepare_ifor([_|T],Type,TT):-
   !,
   clk_prepare_ifor(T,Type,TT).

@clk_prepare_ops(Type,GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   member(Type,['clsWhile','clsSwitch','clsIf','clsReturn','clsOper']),
   !,
   db_content('args',GID,[[_,Opnd]]),
   !,
   clk_parse_expr(Opnd,L),
   !,
   clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

@clk_prepare_ops('clsPreproc',GID,[arg([],[],[],[],[],[],[],[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   clk_parse_expr(Opnd,L),
   !.

@clk_prepare_ops('clsAlternation',GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   clk_parse_expr(Opnd,L),
   !,
   clk_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

% (default:) in switch-case
@clk_prepare_ops('clsAlternation',_,[arg([],[],[],[],[],[],[],[])]):-
   !.

@clk_prepare_ops('clsFor',GID,OPL):-
   db_content('args',GID,L),
   clk_prepare_ifor(L,'init',OPL1),
   clk_prepare_ifor(L,'cond',OPL2),
   clk_prepare_ifor(L,'chng',OPL3),
   !,
   append(OPL1,OPL2,OPLP), append(OPLP,OPL3,OPL),
   !.

% Помещает в базу факт cilk_op(Class,GID1,GID2,IDs,Ops) только втом случае, если его еще в базе не было,
% или он был, но с другими ops. В последнем случае устанавливается флаг-факт cilk_recalculate. Это требуется
% для нормальной работы итеративной процедуры уточнения состава ленивых переменных/параметров для каждой функции
@clk_put_cilk_op(Class,GID1,GID2,IDs,Ops):-
   (
      (predicate_property(cilk_op(_,_,_,_,_),'dynamic'), cilk_op(Class,GID1,GID2,IDs,Ops1))->(
        =(Ops,Ops1)->(
          true, !
        );(
          retractall(cilk_op(Class,GID1,GID2,_,_)),
          (
           (predicate_property(cilk_reanalyze,'dynamic'), cilk_reanalyze)->(
             true, !
           );(
             asserta(cilk_reanalyze)
           )
          ),
          asserta(cilk_op(Class,GID1,GID2,IDs,Ops))
        )
      );(
        asserta(cilk_op(Class,GID1,GID2,IDs,Ops))
      )
   ),
   !.

@clk_get_cilk_fseq([gid('clsEnd',GID)|Rest],[gid('clsEnd',GID)|Rest],[]):-!.

@clk_get_cilk_fseq(L,Rest,[GID|IDT]):-
   clk_get_cilk_fop(L,Rest0,GID),
   !,
   clk_get_cilk_fseq(Rest0,Rest,IDT),
   !.

@clk_get_cilk_fop([gid('clsBegin',GID1)|T],Rest,GID1):-
   clk_get_cilk_fseq(T,[gid('clsEnd',GID2)|Rest],IDs),
   !,
   clk_put_cilk_op('clsBegin',GID1,GID2,IDs,[]),
   !.

@clk_get_cilk_fop([gid(Type,GID)|T],Rest,GID):-
   member(Type,['clsFor','clsSwitch','clsWhile']),
   !,
   clk_get_cilk_fop(T,Rest,OPID),
   !,
   clk_prepare_ops(Type,GID,OPL),
   clk_put_cilk_op(Type,GID,-1,[OPID],OPL),
   !.

@clk_get_cilk_fop([gid('clsDo',GID)|T],Rest,GID):-
   clk_get_cilk_fop(T,[gid('clsWhile',GID1),gid('clsOper',EmptyGID)|Rest],OPID),
   db_content('args',EmptyGID,[[op,'']]),
   !,
   clk_prepare_ops('clsWhile',GID1,OPL),
   clk_put_cilk_op('clsDo',GID,GID1,[OPID],OPL),
   !.

@clk_get_cilk_fop([gid('clsIf',GID)|T],Rest,GID):-
   clk_get_cilk_fop(T,Rest0,OPID0),
   !,
   clk_prepare_ops('clsIf',GID,OPL),
   (
    =(Rest0,[gid('clsElse',GID1)|Rest1])->(
       clk_get_cilk_fop(Rest1,Rest,OPID1),
       clk_put_cilk_op('clsIf',GID,GID1,[OPID0,OPID1],OPL)
    );(
       clk_put_cilk_op('clsIf',GID,-1,[OPID0],OPL),
       =(Rest,Rest0)
    )
   ),
   !.

@clk_get_cilk_fop([gid(Type,GID)|T],T,GID):-
   clk_prepare_ops(Type,GID,OPL),
   clk_put_cilk_op(Type,GID,-1,[],OPL),
   !.

@clk_get_cilk_fprocs([],[]):-!.

@clk_get_cilk_fprocs([GID|T],[GID|TT]):-
   cilk_op('clsOper',GID,_,[],[arg(_,_,_,_,[proc(Name,_)],_,_,_)]),
   cilk_function(Name,_,_),
   !,
   clk_get_cilk_fprocs(T,TT),
   !.
   
@clk_get_cilk_fprocs([GID|T],PGIDS):-
   cilk_op(_,GID,_,LGIDs,_),
   !,
   clk_get_cilk_fprocs(LGIDs,PGIDS0),
   clk_get_cilk_fprocs(T,PGIDS1),
   !,
   append(PGIDS0,PGIDS1,PGIDS),
   !.

@clk_build_cilk_function(Fun,FGID,Body):-
   clk_get_cilk_fop(Body,[],OPID),
   clk_put_cilk_op('clsFunction',FGID,-1,[OPID],[]),
   clk_get_cilk_fprocs([OPID],ProcsGIDs),
   asserta(cilk_fprocs(Fun,FGID,ProcsGIDs)),
   !.

% Анализ (структурный, в глубину) всех функций с разбором выражений, результаты которого попадают в cilk_op
@clk_build_cilk_functions:-
   global_trace(TR),
   retractall(cilk_fprocs(_,_,_)),
   !,
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Fun,GID,_),
      once(append(_,[gid('clsFunction',GID)|T],TR)),
      clk_bypass_complex(T,Body,_),
      call(clk_build_cilk_function(Fun,GID,Body)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@clk_get_globals([],[]):-!.

@clk_get_globals([gid('clsCVar',GID)|T],[V|T1]):-
   db_content('args',GID,[[_,Arg]]),
   !,
   clk_parse_expr(Arg,L),
   clk_rbypass_var(L,V,_,_,_,_,_),
   clk_get_globals(T,T1).

@clk_get_globals([gid('clsOper',GID)|T],T1):-
   db_content('args',GID,[[_,Arg]]),
   !,
   clk_parse_expr(Arg,L),
   clk_analyze_expr(L,_,_,NEWS,_,_,_,_),
   clk_get_globals(T,T0),
   append(NEWS,T0,T1),
   !.

@clk_get_globals([gid('clsFunction',_)|T],T1):-
   clk_bypass_complex(T,_,After),
   clk_get_globals(After,T1),
   !.

@clk_get_globals([_|T],T1):-
   clk_get_globals(T,T1).

@clk_find_globals:-
   global_trace(TR),
   clk_get_globals(TR,GLOBS),
   asserta(cilk_globals(GLOBS)),
   !.

@clk_addLocals([],News,[News]):-!.

@clk_addLocals([L|T],News,[L1|T]):-
   append(L,News,L0),
   !,
   clk_unique(L0,L1),
   !.

@clk_excludeLocals(V,[],V):-!.

@clk_excludeLocals(Vars,[Locs|T],Outs):-
   subtract(Vars,Locs,Vars0),
   clk_excludeLocals(Vars0,T,Outs),
   !.

@clk_getNewInOutLazies([],[],[],[],[],0.0):-!.

@clk_getNewInOutLazies([V|T],News,Ins,Outs,Lazies,TM):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,_,_,Laz0,_]),
   clk_getTime(Funs0,T0),
   clk_getNewInOutLazies(T,News1,Ins1,Outs1,Laz1,T1),
   !,
   append(News0,News1,News2), append(Outs0,Outs1,Outs2), append(Laz0,Laz1,Laz2), append(Ins0,Ins1,Ins2),
   clk_unique(News2,News), clk_unique(Outs2,Outs), clk_unique(Laz2,Lazies), clk_unique(Ins2,Ins),
   TM is T0+T1,
   !.

@clk_analyze_one_flazies([],_,_,_,[],[],[]):-!.

% ReadParams -- читаемые в самой функции ее ленивые параметры (не только выходные, но и входные).
@clk_analyze_one_flazies([GID|GIDS],Globs,Pars,Locals,GLazies,PLazies,ReadParams):-
   cilk_op(_,GID,_,IGIDs,Ops),
   clk_getNewInOutLazies(Ops,News,Ins,Outs,_,_),
   clk_addLocals(Locals,News,Locals1),
   clk_excludeLocals(Outs,Locals1,PreOuts),
   clk_excludeLocals(Ins,Locals1,PreIns),
   clk_intersect(PreOuts,Pars,PLA),
   clk_intersect(PreIns,Pars,ILA),
   subtract(PreOuts,PLA,PreOuts1),
   clk_intersect(PreOuts1,Globs,GLA),
   clk_analyze_one_flazies(IGIDs,Globs,Pars,[News|Locals],GL0,PL0,IL0),
   clk_analyze_one_flazies(GIDS,Globs,Pars,Locals1,GL1,PL1,IL1),
   append(GL0,GL1,GL2), append(GL2,GLA,GL3), append(PL0,PL1,PL2), append(PL2,PLA,PL3),
   append(IL0,IL1,IL2), append(IL2,ILA,IL3),
   clk_unique(GL3,GLazies), clk_unique(PL3,PLazies), clk_unique(IL3,ReadParams),
   !.

@clk_analyze_flazies(Fun,NPrms,GLazies,PLazies,ReadParams):-
   cilk_function(Fun,GID,NPrms),
   !,
   (
    (predicate_property(cilk_fanalyzed(_,_,_,_,_),'dynamic'), cilk_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams))->(
     true,!
     );(
     clk_get_fparams(lazy,Fun,NPrms,LPars0),
     !,
     cilk_globals(Glob0),
     !,
     asserta(cilk_fanalyzed(Fun,GID,[],LPars0,LPars0)),
     clk_analyze_one_flazies([GID],Glob0,LPars0,[],GLazies,PLazies,ReadParams),
     retractall(cilk_fanalyzed(Fun,GID,[],_,_)),
     asserta(cilk_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams)),
     !
    )
   ).

% Определение выходных переменных (глобальных и потенциально модифицируемых параметров) для каждой функции. Для этого проводится
% структурный анализ функции в глубину (с отслеживанием локально декларированных переменных, изменение которых нас здесь не интересует),
% выявляются модифицируемые переменные. Модифицируемые глобалы и параметры попадают в cilk_fanalyzed
@clk_analyze_cilk_functions:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Fun,_,N),
      call(clk_analyze_flazies(Fun,N,_,_,_)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Итерационное сходящееся уточнение состава ленивых переменных/параметров функций (cilk_fanalyzed). На каждой итерации
% для каждой функции уточняется список модифицируемых глобальных переменных и &|*-параметров. Это делается в clk_analyze_cilk_functions.
% Это уточнение может влиять на другие функции, вызывающие уточненные. Сначала считается, что функция модифицирует все свои &|*-параметры,
% они входят в соответствующие списки cilk_fanalyzed, потом эти списки урезаются, в то время как списки глобальных переменных расщиряются.
% Проходит "волна" уточнений, в результате которой, например, функции int p1(int &x) { p2(x); }, int p2(int & x) { cout << x; } в последнем
% приближении уже не имеют выходных ленивых значений вообще, в то время как функции int p1() { p2(); }, int p2() { X = 11; } имеют один
% ленивый результат -- глобальную переменную X.
% После оередного уточнения, выполняется перестройка cilk_op-фактов, в которых выполняется новый разбор выражений с учетом новых данных
% о ленивости. Если при этом изменится хоть один факт, то устанавливается cilk_reanalyze, что свидетельствует о необходимости как минимум
% еще одной итерации.
@clk_iterative_build_funs:-
   retractall(cilk_reanalyze),
   clk_build_cilk_functions,
   (
    (predicate_property(cilk_reanalyze,'dynamic'), cilk_reanalyze)->(
      retractall(cilk_fanalyzed(_,_,_,_,_)),
      clk_analyze_cilk_functions,
      clk_iterative_build_funs,
      !
    );(
      true, !
    )
   ),
   !.

@clk_get_flist_deps([]):-
   !.

@clk_get_flist_deps([V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   !,
   (
    (predicate_property(cilk_fpure(_),'dynamic'), cilk_fpure(Name));
    (
     predicate_property(cilk_function(_,_,_),'dynamic'),
     cilk_function(Name,_,NPrms),
     predicate_property(cilk_fdependent(_,_,_),'dynamic'),
     cilk_fdependent(Name,NPrms,f)
    )
   ),
   !,
   clk_get_flist_deps(T),
   !.

@clk_get_fexpr_deps([]):-
   !.

@clk_get_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   !,
   clk_get_flist_deps(FUNS),
   clk_get_fexpr_deps(T),
   !.

@clk_get_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   !,
   clk_get_flist_deps(FUNS),
   !,
   clk_get_flist_deps(PROCS),
   clk_get_fexpr_deps(T),
   !.

@clk_get_fblock_deps([]):-
   !.

@clk_get_fblock_deps([GID|T]):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   clk_get_fexpr_deps(Exprs),
   !,
   clk_get_fblock_deps(LGIDs),
   !,
   clk_get_fblock_deps(T),
   !.

% Имеет ли блок внутри cilk_sync?
@clk_block_has_sync([]):-
   !,
   fail.

@clk_block_has_sync([GID|T]):-
   !,
   (
    (predicate_property(cilk_sync(_),'dynamic'),cilk_sync(GID))->
       true;
       (
        cilk_op(_,GID,_,LGIDs,_),
        !,
        (
         clk_block_has_sync(LGIDs)->
           true;
           clk_block_has_sync(T)
        )
       )
   ).

@clk_exprs_has_no_derefs([]):-
   !.

@clk_exprs_has_no_derefs([E|T]):-
   =..(E,[_,_,_,_,_,_,_,_,[L]]),
   !,
   \+ (
     append(['*'],_,L);
     (append(_,[S,'*'|_],L),member(S,['(','[','+','-','*','%','!','~','=','<','>',',',';']))
   ),
   !,
   clk_exprs_has_no_derefs(T).

% Содержит ли блок разыменование указателей
@clk_block_has_no_derefs([]):-
   !.

@clk_block_has_no_derefs([GID|T]):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   clk_exprs_has_no_derefs(Exprs),
   !,
   clk_block_has_no_derefs(LGIDs),
   clk_block_has_no_derefs(T).

@clk_extract_var_names([],[]):-
   !.

@clk_extract_var_names([var(Name,_)|T],[Name|T1]):-
   clk_extract_var_names(T,T1),
   !.

@clk_exprs_in_outs([],[],[],[]):-
   !.

@clk_exprs_in_outs([E|T],Ins,Outs,News):-
   =..(E,[_,Ins0,Outs0,News0,_,_,_,_,_]),
   !,
   clk_extract_var_names(News0, NewsE),
   !,
   clk_exprs_in_outs(T,Ins1,Outs1,News1),
   clk_union(Ins0,Ins1,Ins),
   clk_union(Outs0,Outs1,Outs),
   clk_union(NewsE,News1,News),
   !.

@clk_for_in_outs([],[],[],[]):-
   !.

@clk_for_in_outs([GID|T],Ins,Outs,News):-
   cilk_op(C,GID,_,LGIDs,Exprs),
   !,
   (
    =(C,'clsFor')->
      (clk_exprs_in_outs(Exprs,Ins0,_,News0),=(Outs0,[]));
      clk_exprs_in_outs(Exprs,Ins0,Outs0,News0)
   ),
   !,
   clk_for_in_outs(LGIDs,Ins1,Outs1,News1),
   clk_for_in_outs(T,Ins2,Outs2,News2),
   !,
   clk_union(Ins0,Ins1,InsA), clk_union(InsA,Ins2,Ins),
   clk_union(Outs0,Outs1,OutsA), clk_union(OutsA,Outs2,Outs),
   clk_union(News0,News1,NewsA), clk_union(NewsA,News2,News),
   !.

@clk_extract_idx(['-','>',id(_)|Rest],EXPR):-
   clk_extract_idx(Rest,EXPR),
   !.

@clk_extract_idx(['.',id(_)|Rest],EXPR):-
   clk_extract_idx(Rest,EXPR),
   !.

@clk_extract_idx(['['|Rest],[EXPR|EXPRT]):-
   clk_get_balanced(0,Rest,[']'],EXPR,[']'|Rest0]),
   !,
   clk_extract_idx(Rest0,EXPRT),
   !.

@clk_extract_idx(_,[]):-
   !.

@clk_extract_idxs(L,T):-
   append(_,[id(V)|TT],L),
   !,
   clk_extract_idx(TT,Idxs),
   !,
   clk_extract_idxs(TT,T0),
   clk_union([var(V,Idxs)],T0,T),
   !.

@clk_extract_idxs(_,[]):-
   !.

@clk_get_expr_idxs([],[]):-
   !.

@clk_get_expr_idxs([E|T],Idxs):-
   =..(E,[_,_,_,_,_,_,_,_,[L]]),
   !,
   clk_extract_idxs(L,Idxs1),
   clk_get_expr_idxs(T,Idxs2),
   clk_union(Idxs1,Idxs2,Idxs),
   !.

@clk_get_var_idxs([],[]):-
   !.

@clk_get_var_idxs([GID|T],Idxs):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   clk_get_expr_idxs(Exprs,Idxs0),
   !,
   clk_get_var_idxs(LGIDs,Idxs1),
   clk_get_var_idxs(T,Idxs2),
   clk_union(Idxs0,Idxs1,IdxsA), clk_union(IdxsA,Idxs2,Idxs),
   !.

@clk_check_idx_one(_,[]):-
   !.

@clk_check_idx_one(V,[L|T]):-
   !,
   \+ member(id(V),L),
   clk_check_idx_one(V,T).

@clk_check_idx(_,[]):-
   !.

@clk_check_idx(V,[var(_,Idxs)|T]):-
   clk_check_idx_one(V,Idxs),
   clk_check_idx(V,T).

% Проверка -- зависит ли индекс от выходных переменных
@clk_check_idxs([],_):-
   !.

@clk_check_idxs([V|T],VarIdxs):-
   clk_check_idx(V,VarIdxs),
   !,
   clk_check_idxs(T,VarIdxs).

@clk_filter_idx_one(_,_,[],[]):-
   !.

@clk_filter_idx_one(V,N,[L|T],[idx(N,L)|TT]):-
   member(id(V),L),
   !,
   N1 is N+1,
   clk_filter_idx_one(V,N1,T,TT).

@clk_filter_idx_one(V,N,[_|T],TT):-
   clk_filter_idx_one(V,N,T,TT).

@clk_filter_idxs(_,[],[]):-
   !.

% Превращаем индексы в список зависящих от счетчика индексов
@clk_filter_idxs(V,[var(P,Idxs)|T],[var(P,OIdxs)|TT]):-
   call(clk_filter_idx_one(V,0,Idxs,OIdxs)),
   !,
   clk_filter_idxs(V,T,TT),
   !.

@clk_same_indexes(_,_,[]):-
   !.

@clk_same_indexes(V,Idxs,[var(V,Idxs1)|T]):-
   !,
   =(Idxs,Idxs1),
   clk_same_indexes(V,Idxs,T),
   !.

@clk_same_indexes(V,Idxs,[_|T]):-
   !,
   clk_same_indexes(V,Idxs,T).

@clk_eq_indexes(V,FIdxs):-
   append(_,[var(V,Idxs)|T],FIdxs),
   !,
   clk_same_indexes(V,Idxs,T).

@clk_eq_indexes(_,_):-
   !.

@clk_check_outs_by_idxs([],_,_):-
   !.

@clk_check_outs_by_idxs([V|T],Ins,FIdxs):-
   !,
   \+ member(var(V,[]),FIdxs), % Выходная переменная должна зависеть от индекса
   !,
   (
    \+ member(V,Ins); % Выходная переменная -- не входная
    clk_eq_indexes(V,FIdxs) % Выходная переменная имеет везде одинаковую индексацию по счетчику
   ),
   !,
   clk_check_outs_by_idxs(T,Ins,FIdxs).

% Не содержит ли цикл связей между итерациями по индексам
@clk_for_content(Counter,LGIDs):-
   once(clk_for_in_outs(LGIDs,Ins,Outs0,News)),
   subtract(Outs0,News,Outs),
   clk_get_var_idxs(LGIDs,VarIdxs),
   clk_check_idxs(Outs,VarIdxs),
   !,
   clk_filter_idxs(Counter,VarIdxs,FIdxs),
   !,
   clk_check_outs_by_idxs(Outs,Ins,FIdxs).

% Анализ возможности распараллелить for
@clk_analyze_for(GID):-
   cilk_op('clsFor',GID,_,LGIDs,Exprs),
   (
    (predicate_property(cilk_for_time(_,_),'dynamic'),cilk_for_time(GID,T))->
       (g_read('$SpawnTime',TSP), g_read('$SyncTime',TSY), TPAR is T + 3*(TSP + TSY), TSEQ is 8*T, TPAR < TSEQ); % 2^3 = 8 (бинарное дерево ветвления)
       true
   ),
   \+ once(clk_block_has_sync(LGIDs)),
   member(init(_,_,_,_,_,_,_,[[id(Counter),'='|_]]),Exprs),
   (
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'<','='|_]]),Exprs);
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'>','='|_]]),Exprs);
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'<'|_]]),Exprs);
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'>'|_]]),Exprs);
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'=','='|_]]),Exprs);
    member(cond(_,[],_,_,_,_,_,[[id(Counter),'!','='|_]]),Exprs)
   ),
   (
    member(chng(_,[Counter],_,_,_,_,_,[[id(Counter),'+','='|_]]),Exprs);
    member(chng(_,[Counter],_,_,_,_,_,[[id(Counter),'-','='|_]]),Exprs);
    member(chng(_,[Counter],_,_,_,_,_,[[id(Counter),'+','+']]),Exprs);
    member(chng(_,[Counter],_,_,_,_,_,[[id(Counter),'-','-']]),Exprs)
   ),
   once(clk_block_has_no_derefs(LGIDs)),
   once(clk_get_fblock_deps(LGIDs)),
   once(clk_for_content(Counter,LGIDs)),
   asserta(cilk_for(GID)),
   !.

% Нельзя распараллелить for
@clk_analyze_for(GID):-
   cilk_op('clsFor',GID,_,_,_),
   !.

@clk_get_fors([],_):-!.

@clk_get_fors([GID|T],_):-
   cilk_op(S,GID,_,[],_),
   !,
   clk_get_fors(T,t),
   !.
   
% Пытаемся распараллелить самый внешний цикл
@clk_get_fors([GID|T],Flag):-
   cilk_op('clsFor',GID,_,[LGID],_),
   cilk_op('clsFor',LGID,_,_,_),
   !,
   (
    =(Flag,t)->(
      clk_analyze_for(GID),
      (
       (predicate_property(cilk_for(_),'dynamic'),cilk_for(GID))->
         clk_get_fors([LGID],f);
         clk_get_fors([LGID],t)
      )
    );(
      clk_get_fors([LGID],f)
    )
   ),
   !,
   clk_get_fors(T,t),
   !.

% Пытаемся распараллелить цикл
@clk_get_fors([GID|T],Flag):-
   cilk_op('clsFor',GID,_,LGIDs,_),
   !,
   (
    =(Flag,t)->
      clk_analyze_for(GID);
      true
   ),
   !,
   clk_get_fors(LGIDs,t),
   !,
   clk_get_fors(T,t),
   !.

% Прочие составные операторы
@clk_get_fors([GID|T],_):-
   cilk_op(_,GID,_,LGIDs,_),
   !,
   clk_get_fors(LGIDs,t),
   !,
   clk_get_fors(T,t),
   !.
   
% Обработка и распараллеливание циклов в функции Fun
@clk_handle_fors_in_function(FGID):-
   cilk_op('clsFunction',FGID,_,LGIDs,_),
   clk_get_fors(LGIDs,t),
   !.

% Обработка и распараллеливание подходящих циклов в каждой функции
@clk_handle_fors:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(_,GID,_),
      call(clk_handle_fors_in_function(GID)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@clk_get_list_deps(_,[]):-
   !.

@clk_get_list_deps(NamePath,[V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   clk_get_fdeps(Name,NamePath,NPrms),
   clk_get_list_deps(NamePath,T),
   !.

@clk_get_expr_deps(_,[]):-
   !.

@clk_get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   clk_get_list_deps(NamePath,FUNS),
   clk_get_expr_deps(NamePath,T),
   !.

@clk_get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   clk_get_list_deps(NamePath,FUNS),
   clk_get_list_deps(NamePath,PROCS),
   clk_get_expr_deps(NamePath,T),
   !.

@clk_get_block_deps(_,[]):-
   !.

@clk_get_block_deps(NamePath,[GID|T]):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   clk_get_expr_deps(NamePath,Exprs),
   clk_get_block_deps(NamePath,LGIDs),
   !,
   clk_get_block_deps(NamePath,T),
   !.

@clk_mark_deps([]):-
   !.

@clk_mark_deps([path(Name,NPrms)|T]):-
   (
    (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,t))->(
      true,!
    );(
      retractall(cilk_fdependent(Name,NPrms,_)), asserta(cilk_fdependent(Name,NPrms,t))
    )
   ),
   clk_mark_deps(T).

@clk_get_fdeps(Name,NamePath,NPrms):-
   member(path(Name,NPrms),NamePath),
   !.

@clk_get_fdeps(Name,NamePath,NPrms):-
   cilk_function(Name,GID,NPrms),
   cilk_op('clsFunction',GID,_,LGIDs,_),
   (
    (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,_))->(
      true,!
    );(
      clk_get_block_deps([path(Name,NPrms)|NamePath],LGIDs),
      (
       (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,_))->(
         true,!
       );(
         asserta(cilk_fdependent(Name,NPrms,f))
       )
      )
    )
   ),
   (
     (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,t))->
        clk_mark_deps(NamePath);
        true
   ).

@clk_get_fdeps(Name,NamePath,NPrms):-
   \+ cilk_function(Name,_,NPrms),
   (
    (predicate_property(cilk_fpure(_),'dynamic'),cilk_fpure(Name))->
       true;
       clk_mark_deps(NamePath)
   ),
   !.

% Определение зависимостей функций от внешних функций
@clk_find_dependents:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Name,_,NPrms),
      call(clk_get_fdeps(Name,[],NPrms)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@clk_get_comma_list([id(F),')'],[F]):-
   !.

@clk_get_comma_list([id(F),','|R],[F|T]):-
   clk_get_comma_list(R,T).

@clk_analyze_pragma_pure([]):-
   !.

@clk_analyze_pragma_pure([F|T]):-
   (
    (predicate_property(cilk_fpure(_),'dynamic'),cilk_fpure(F))->
       true;
       asserta(cilk_fpure(F))
   ),
   !,
   clk_analyze_pragma_pure(T).

% Очистка + Загрузка необходимых данных перед анализом
@clk_prepare_cilk:-
   retractall(db_content(_,_,_)),
   asserta(cilk_function('','','')), retractall(cilk_function(_,_,_)),
   retractall(cilk_fdependent(_,_,_)),
   retractall(cilk_fpure(_)),
   retractall(cilk_farg(_,_,_,_)),
   retractall(cilk_fprocs(_,_,_)),
   retractall(cilk_op(_,_,_,_,_)),
   retractall(cilk_globals(_)),
   retractall(cilk_fanalyzed(_,_,_,_,_)),
   retractall(cilk_ftime(_,_,_)),
   retractall(cilk_auto_for),
   retractall(cilk_for_time(_,_)),
   asserta(cilk_retime), retractall(cilk_retime),
   asserta(cilk_reanalyze), retractall(cilk_reanalyze),
   retractall(cilk_spawn(_)),
   retractall(cilk_spawn_time(_,_)),
   retractall(cilk_sync(_)),
   retractall(cilk_for(_)),
   retractall(cilk_break(_)),
   retractall(cilk_continue(_)),
   retractall(params(_)),
   retractall(counter(_)),
   clk_read_db,
   (
    (db_content('prog',GID,[['preproc']]),db_content('args',GID,[[body,S]]),clk_parse_expr(S,['#',id('pragma'),id('auto'),id('for')]))->
     (
      !,
      (
       (predicate_property(cilk_auto_for,'dynamic'), cilk_auto_for)->
         true;
         asserta(cilk_auto_for)
      ),
      once(global_trace(GTR)),
      append(LEFTR,[gid(_,GID)|RIGHTR],GTR),
      append(LEFTR,RIGHTR,GTR2),
      once(retractall(global_trace(_))),
      once(asserta(global_trace(GTR2)))
     );
     true
   ),
   !,
   (
    (db_content('prog',GID1,[['preproc']]),
     db_content('args',GID1,[[body,S1]]),
     once(clk_parse_expr(S1,['#',id('pragma'),id('auto'),id('pure'),'('|R1])),
     once(clk_get_comma_list(R1,L1)),
     once(clk_analyze_pragma_pure(L1)),
     once(global_trace(GTRX)),
     append(LEFTRX,[gid(_,GID1)|RIGHTRX],GTRX),
     append(LEFTRX,RIGHTRX,GTR2X),
     once(retractall(global_trace(_))),
     once(asserta(global_trace(GTR2X))),
     fail);
     true
   ),
   !,
   clk_prepare_cilk_functions,
   !,
   clk_find_globals,
   !,
   clk_build_cilk_functions,
   !,
   clk_analyze_cilk_functions,
   !,
   clk_iterative_build_funs,
   !,
   clk_find_dependents,
   !.

@clk_find_lvar(V,[Globals],global(V)):-
   member(global(V),Globals),
   !.

@clk_find_lvar(V,[TopVars|_],loc(TopGID,V)):-
   member(loc(TopGID,V),TopVars),
   !.

@clk_find_lvar(V,[_|RestVars],V1):-
   clk_find_lvar(V,RestVars,V1),
   !.

@clk_find_lvars([],_,[]):-!.

@clk_find_lvars([global(V)|T],Vars,[global(V)|T1]):-
   clk_find_lvars(T,Vars,T1),
   !.

@clk_find_lvars([par(_,_,V)|T],Vars,[V1|T1]):-
   clk_find_lvar(V,Vars,V1),
   clk_find_lvars(T,Vars,T1),
   !.

@clk_find_lvars([V|T],Vars,[V1|T1]):-
   clk_find_lvar(V,Vars,V1),
   clk_find_lvars(T,Vars,T1),
   !.

@clk_find_lvars([V|T],Vars,T1):-
   \+ clk_find_lvar(V,Vars,_),
   clk_find_lvars(T,Vars,T1),
   !.

@clk_loc_prefixate(_,[],[]):-!.

@clk_loc_prefixate(TopGID,[V|T],[loc(TopGID,V)|T1]):-
   clk_loc_prefixate(TopGID,T,T1),
   !.

@clk_getNewInOutRefLazies(_,_,[],[],[],[],[],[],0.0):-!.

@clk_getNewInOutRefLazies(TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,_,Ref0,Laz0,_]),
   clk_find_lvars(Ins0,Vars,InsP),
   clk_find_lvars(Outs0,Vars,OutsP),
   clk_find_lvars(Ref0,Vars,RefsP),
   clk_find_lvars(Laz0,Vars,LazP),
   clk_loc_prefixate(TopGID,News0,NewsP),
   !,
   clk_getTime(Funs0,T0),
   clk_getNewInOutRefLazies(TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1),
   !,
   append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
   append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
   clk_unique(News2,News), clk_unique(Ins2,Ins), clk_unique(Laz2,Lazies),
   clk_unique(Outs2,Outs), clk_unique(Ref2,Refs),
   TM is T0+T1,
   !.

@clk_getForNewInOutRefLazies(_,_,_,[],[],[],[],[],[],0.0):-!.

@clk_getForNewInOutRefLazies(Types,TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM):-
   =..(V,[Type,Ins0,Outs0,News0,Funs0,_,Ref0,Laz0,_]),
   (
    member(Type,Types)->(
      !,
      clk_find_lvars(Ins0,Vars,InsP),
      clk_find_lvars(Outs0,Vars,OutsP),
      clk_find_lvars(Ref0,Vars,RefsP),
      clk_find_lvars(Laz0,Vars,LazP),
      clk_loc_prefixate(TopGID,News0,NewsP),
      !,
      clk_getTime(Funs0,T0),
      clk_getForNewInOutRefLazies(Types,TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1),
      !,
      append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
      append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
      clk_unique(News2,News), clk_unique(Ins2,Ins), clk_unique(Laz2,Lazies),
      clk_unique(Outs2,Outs), clk_unique(Ref2,Refs),
      TM is T0+T1
    );(
      clk_getForNewInOutRefLazies(Types,TopGID,Vars,T,News,Ins,Outs,Refs,Lazies,TM)
    )
   ),
   !.

@clk_put_cilk_sync(GID):-
   (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->
      (true, !);
      (asserta(cilk_sync(GID))).

@clk_inc_spawns([],[],_):-!.

@clk_inc_spawns([trace(S,Fun,NPrms,T0)|T1],[trace(S,Fun,NPrms,TR)|T2],Delta):-
   TR is T0+Delta,
   clk_inc_spawns(T1,T2,Delta).

@clk_start_spawn(GID,Fun,NPrms,L,[trace(GID,Fun,NPrms,0.0)|L],T1,T2):-
   g_read('$SpawnTime', A),  % +Затраты на собственно spawn
   T2 is T1+A.

@clk_stop_spawns([],[],T,T):-!.

@clk_stop_spawns([trace(GID,Fun,NPrm,T1)|T],[],T0,TMax):-
   clk_get_ftime(Fun,NPrm,TF),
   g_read('$SyncTime', SyncTime),
   (
    <(T1,TF)->
      TT is T0+TF-T1+SyncTime;
      TT is T0+SyncTime % Затраты на собственно sync
   ),
   (
    (predicate_property(cilk_spawn_time(_,_),'dynamic'), cilk_spawn_time(GID,Timings))->
      (
         retractall(cilk_spawn_time(GID,_)),
         asserta(cilk_spawn_time(GID,[T1|Timings]))
      );(
         asserta(cilk_spawn_time(GID,[T1]))
      )
   ),
   clk_stop_spawns(T,[],T0,TC),
   (
    >(TT,TC)->
      =(TMax,TT);
      =(TMax,TC)
   ),
   !.

% Альтернативы из switch {}
@clk_traverse_alters([CurGID|GIDs], [TopGID|StackGIDs], [switch(TopGID,Pass)|StackConstrs], StackConstrs, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time, NAlt):-
   cilk_op('clsAlternation',CurGID,_,[],_),
   (
    (append(ALT,[NextGID|_],GIDs),cilk_op('clsOper',NextGID,_,[],_),db_content('args',NextGID,[['op','break']]),!)->
       (
        !,
        clk_traverse_fun(NextGID,ALT,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazV,InRefs,RefV,ISpawns,OSP1,T1),
        !
       );
       (
        clk_traverse_fun(NextGID,GIDs,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazV,InRefs,RefV,ISpawns,OSP1,T1),
        !
       )
   ),
   retractall(cilk_break(_)),
   (
    (append(_,[NextGID1|Rest1],GIDs),cilk_op('clsAlternation',NextGID1,_,[],_))->(
       !,
       clk_traverse_alters([NextGID1|Rest1],[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazVV,InRefs,RefVV,OSP1,OSpawns,T2,NAlt1),
       append(LazV,LazVV,Laz1), append(RefV,RefVV,Ref1),
       clk_unique(Laz1,OutLazies), clk_unique(Ref1,OutRefs),
       Time is T1+T2,
       NAlt is NAlt1+1,
       !
    );(
       =(OutLazies,LazV), =(OutRefs,RefV), =(OSpawns,OSP1), =(Time,T1), =(NAlt,1),
       !
    )
   ),
   !.

@clk_traverse_alters([], [TopGID|_], [switch(TopGID,_)|CRest], CRest, _, InLazies, InLazies, InRefs, InRefs, ISpawns, ISpawns, 0.0, 0):-!.

% Окончание while
@clk_traverse_fun(SyncGID,[], [TopGID|StackGIDs], [while(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsWhile',TopGID,_,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   clk_getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,TP)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2), clk_intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(TP,0.0)
        );(
          (
           cilk_op('clsBegin',IGID,EGID,_,_)->
            clk_put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsWhile',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsWhile',TopGID,-1,[NewIGID],Ops)),
             asserta(cilk_op('clsBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             clk_bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsOper',NewDGID),gid('clsEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             clk_put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,TP)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   (
    (predicate_property(cilk_continue(_),'dynamic'), cilk_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(cilk_continue(_)),
   (
    (predicate_property(cilk_break(_),'dynamic'), cilk_break(_))->(
       retractall(cilk_break(_)),
       =(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns,OSP1), =(T1,0.0)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          cilk_op('clsWhile',TopGID,_,[IGID1],_),
          clk_traverse_fun(_,[IGID1],[TopGID|StackGIDs],[while(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T1)
         );
         (=(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns, OSP1), =(T1,0.0))
      )
   ),
   (
    (=(CONT,1))->(
      Time is TP+BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is TP+T1+BaseTime
    )
   ),
   !.

% Прерывание break
@clk_traverse_fun(_,[CurGID|_], StackGIDs, [Top|StackConstrs], StackConstrs, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','break']]),
   !,
   asserta(cilk_break(CurGID)),
   =..(Top,[_,TopGID,_]),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     clk_traverse_fun(CurGID,[],[CurTopGID|Rest],[Top|StackConstrs],_,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
     T1 is T0+TT,
     retractall(lz(_)), retractall(rf(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(lz(LZ1)), asserta(rf(RF1)), asserta(vr(VAR1)), asserta(sp(SP1)), asserta(tm(T1)),
     =(TopGID,CurTopGID), % Проверка -- условие окончания цикла
   !,
   =(OutLazies,LZ1), =(OutRefs,RF1), =(OSpawns,SP1), =(Time,T1),
   retractall(lz(_)), retractall(rf(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
   !.

% Возобновление continue
@clk_traverse_fun(_,[CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','continue']]),
   !,
   asserta(cilk_continue(CurGID)),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(st(ST0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     clk_traverse_fun(CurGID,[],[CurTopGID|Rest],ST0,ST1,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
     T1 is T0+TT,
     retractall(lz(_)), retractall(rf(_)), retractall(st(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(lz(LZ1)), asserta(rf(RF1)), asserta(st(ST1)), asserta(vr(VAR1)), asserta(sp(SP1)), asserta(tm(T1)),
     \+ cilk_continue(CurGID), % Проверка -- условие окончания цикла
   !,
   =(OutLazies,LZ1), =(OutRefs,RF1), =(OutCStack,ST1), =(OSpawns,SP1), =(Time,T1),
   retractall(lz(_)), retractall(rf(_)), retractall(st(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
   !.

% Возврат return
@clk_traverse_fun(_,[CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsReturn',CurGID,_,[],_),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(st(ST0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     clk_traverse_fun(CurGID,[],[CurTopGID|Rest],ST0,ST1,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
     T1 is T0+TT,
     retractall(lz(_)), retractall(rf(_)), retractall(st(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
     =(VAR0,[_|VAR1]),
     asserta(lz(LZ1)), asserta(rf(RF1)), asserta(st(ST1)), asserta(vr(VAR1)), asserta(sp(SP1)), asserta(tm(T1)),
     =(Rest,[-1]), % Проверка -- условие окончания цикла
   !,
   =(OutLazies,LZ1), =(OutRefs,RF1), =(OutCStack,ST1), =(OSpawns,SP1), =(Time,T1),
   retractall(lz(_)), retractall(rf(_)), retractall(st(_)), retractall(vr(_)), retractall(sp(_)), retractall(tm(_)),
   !.

% Окончание do-while
@clk_traverse_fun(SyncGID,[], [TopGID|StackGIDs], [do(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsDo',TopGID,LastGID,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   clk_getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2), clk_intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          (
           cilk_op('clsBegin',IGID,EGID,_,_)->
            clk_put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsDo',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsDo',TopGID,LastGID,[NewIGID],Ops)),
             asserta(cilk_op('clsBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             clk_bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsOper',NewDGID),gid('clsEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             clk_put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   (
    (predicate_property(cilk_continue(_),'dynamic'), cilk_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(cilk_continue(_)),
   (
    (predicate_property(cilk_break(_),'dynamic'), cilk_break(_))->(
       retractall(cilk_break(_)),
       =(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns,OSP1), =(T2,0.0)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          cilk_op('clsDo',TopGID,LastGID,[IGID1],_),
          clk_traverse_fun(_,[IGID1],[TopGID|StackGIDs],[do(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T2)
         );
         (=(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns,OSP1), =(T2,0.0))
      )
   ),
   (
    (=(CONT,1))->(
      Time is T1+BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is T1+T2+BaseTime
    )
   ),
   !.

% Окончание for
@clk_traverse_fun(SyncGID,[], [TopGID|StackGIDs], [for(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsFor',TopGID,_,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   clk_getForNewInOutRefLazies(['cond','chng'],TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2), clk_intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          (
           cilk_op('clsBegin',IGID,EGID,_,_)->
            clk_put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsFor',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsFor',TopGID,-1,[NewIGID],Ops)),
             asserta(cilk_op('clsBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             clk_bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsOper',NewDGID),gid('clsEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             clk_put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   (
    (predicate_property(cilk_continue(_),'dynamic'), cilk_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(cilk_continue(_)),
   (
    (predicate_property(cilk_break(_),'dynamic'), cilk_break(_))->(
       retractall(cilk_break(_)),
       =(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns,OSP1), =(T2,0.0)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться выше (при преобразовании одиночного оператора в {})
          cilk_op('clsFor',TopGID,_,[IGID1],_),
          clk_traverse_fun(_,[IGID1],[TopGID|StackGIDs],[for(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T2),
          clk_put_for_time(TopGID,T2)
         );
         (=(OutLazies,Laz1), =(OutRefs,Ref1), =(OSpawns,OSP1), =(T2,0.0))
      )
   ),
   (
    (=(CONT,1))->(
      Time is T1+BaseTime % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      Time is T1+T2+BaseTime
    )
   ),
   !.

% Окончание произвольного {}
@clk_traverse_fun(SyncGID,[], [TopGID|_], StackConstrs, StackConstrs, [LVars|_], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsBegin',TopGID,EndGID,_,_),
   !,
   (=(SyncGID,EndGID);true), % Если SyncGID не связан, то получает значение EndGID, иначе значение SyncGID сохраняется
   !,
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(OutLazies,[]), =(OutRefs,[]), clk_stop_spawns(ISpawns,OSpawns,0.0,Time)
      );(
       clk_intersect(InLazies,LVars,Decision2), clk_intersect(InRefs,LVars,Decision3),
       (
        (=(Decision2,[]),=(Decision3,[]))->(
          =(OutLazies,InLazies), =(OutRefs,InRefs), =(OSpawns,ISpawns), =(Time,0.0)
        );(
          clk_put_cilk_sync(SyncGID),
          =(OutLazies,[]), =(OutRefs,[]), clk_stop_spawns(ISpawns,OSpawns,0.0,Time)
        )
       )
      )
   ),
   !.

% Окончание функции
@clk_traverse_fun(_,[], [-1], StackConstrs, StackConstrs, _, _, [], _, [], ISpawns, ISpawns, 0.0):-
   !.

% Окончание произвольного (не{}) оператора. Может вызываться в операторе окончания различных конструктов
@clk_traverse_fun(_,[], [TopGID|_], StackConstrs, StackConstrs, [LVars|_], InLazies, OutLazies, InRefs, OutRefs, ISpawns, ISpawns, 0.0):-
   \+ cilk_op('clsBegin',TopGID,_,_,_),
   !,
   clk_intersect(InLazies,LVars,Decision2), clk_intersect(InRefs,LVars,Decision3),
   (
    (=(Decision2,[]),=(Decision3,[]))->(
      =(OutLazies,InLazies), =(OutRefs,InRefs)
    );(
      fail % Непонятно: текущий оператор имеет локальную ленивую переменную, причем не в {}. Как это возможно?
    )
   ),
   !.

% Полный if-else, IGIDs = [IfGID,EGID]. Краткий if -- обрабатывается обычным образом, IGIDs = [IfGID]
@clk_traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsIf',CurGID,_,[IfGID,EGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   clk_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          clk_put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   clk_traverse_fun(_,[IfGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz20,Ref1,Ref20,OSP1,OSP20,T20),
   clk_traverse_fun(_,[EGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz21,Ref1,Ref21,OSP1,OSP21,T21),
   append(Laz20,Laz21,Laz22), clk_unique(Laz22,Laz2), !,
   append(Ref20,Ref21,Ref22), clk_unique(Ref22,Ref2), !,
   append(OSP20,OSP21,OSP22),
   clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP22,OSpawns,T3),
   Time is T1+BaseTime+0.5*(T20+T21)+T3,
   !.

% Полный while
@clk_traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsWhile',CurGID,_,[IGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   clk_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          clk_put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   clk_traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[while(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
   !,
   clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
   Time is T1+BaseTime+T2+T3,
   !.

% Полный for
@clk_traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsFor',CurGID,_,[IGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   clk_getForNewInOutRefLazies(['init','cond'],CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          clk_put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   clk_traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[for(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
   !,
   clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
   Time is T1+BaseTime+T2+T3,
   !.

% Полный do-while
@clk_traverse_fun(_,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsDo',CurGID,_,[IGID],_),
   !,
   clk_traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[do(CurGID,1)|StackConstrs],_,[[]|Vars],InLazies,Laz2,InRefs,Ref2,ISpawns,OSP1,T1),
   !,
   clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP1,OSpawns,T2),
   Time is T1+T2,
   !.

% switch
@clk_traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsSwitch',CurGID,_,[IGID],Ops),
   cilk_op('clsBegin',IGID,_,IGIDs,_),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   clk_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   clk_inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
      );(
       clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          clk_put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
   !,
   clk_traverse_alters(IGIDs,[CurGID,TopGID|StackGIDs],[switch(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,TNN,NAlt),
   !,
   clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T2),
   (
    =(NAlt,0)->
      Time is T1+BaseTime+T2;
      Time is T1+BaseTime+TNN/NAlt+T2
   ),
   !.

@clk_traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   (predicate_property(cilk_break(_),'dynamic'), cilk_break(BreakGID))->(
      clk_traverse_fun(BreakGID,[], [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,InLazies,OutLazies,InRefs,OutRefs,ISpawns,OSpawns,Time),
      !
   );(
      cilk_op(_,CurGID,_,IGIDs,Ops),
      !,
      (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
      !,
      clk_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
      clk_inc_spawns(ISpawns,ISP,BaseTime),
      (
       (predicate_property(cilk_spawn(_),'dynamic'), cilk_spawn(CurGID))->
          (
           cilk_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)]),
           length(Prms,NPrms),
           clk_start_spawn(CurGID,Fun,NPrms,ISP,ISP1,0.0,TSP)
          );
          (
           ( % Если это не spawn, но запуск процедуры, то прибавляем время ее исполнения
            cilk_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)])->
              (clk_getTime([proc(Fun,Prms)],TSP1), g_read('$DefOperTime',TOp0), TSP is TSP1-TOp0);
              =(TSP,0.0)
           ),
           =(ISP1,ISP)
          )
      ),
      (
       (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID),
        ((predicate_property(cilk_spawn(_),'dynamic'),=(SyncGID,CurGID))->(\+ cilk_spawn(SyncGID));true)
       )->(
          =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP1,OSP1,0.0,T1)
         );(
          clk_intersect(InLazies,Ins,Decision1), clk_intersect(InRefs,Outs,Decision2),
          (
           (=(Decision1,[]),=(Decision2,[]))->(
             =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP1), =(T1,0.0)
           );(
             clk_put_cilk_sync(SyncGID),
             =(NextLazies,[]), =(NextRefs,[]), clk_stop_spawns(ISP1,OSP1,0.0,T1)
           )
          )
         )
      ),
      clk_addLocals(Vars,News,Vars1),
      append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
      clk_unique(Laz0,Laz1), clk_unique(Ref0,Ref1),
      !,
      clk_traverse_fun(_,IGIDs,[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
      clk_traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars1,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
      Time is TSP+T1+BaseTime+T2+T3,
      !
   ).

@clk_create_syncs(Fun,GID,NPrms):-
   retractall(cilk_break(_)),
   retractall(cilk_continue(_)),
   cilk_globals(GLOB),
   clk_glob_prefixate(GLOB,G1),
   clk_get_fparams(all,Fun,NPrms,PARMS),
   clk_loc_prefixate(GID,PARMS,P1),
   clk_traverse_fun(_,[GID],[-1],[],_,[P1,G1],[],_,[],_,[],OSP,Time0),
   clk_stop_spawns(OSP,[],Time0,Time),
   clk_put_ftime(Fun,NPrms,Time),
   !.

@clk_bypass_sequence([],[],[]):-!.

@clk_bypass_sequence([gid('clsEnd',GID)|T],[],[gid('clsEnd',GID)|T]):-
   !.

@clk_bypass_sequence([gid('clsBegin',GID)|T],TT,T3):-
   clk_bypass_complex([gid('clsBegin',GID)|T],T0,T1),
   clk_bypass_sequence(T1,T2,T3),
   append(T0,T2,TT),
   !.

@clk_bypass_sequence([H|T],[H|T1],T2):-
   clk_bypass_sequence(T,T1,T2),
   !.

@clk_bypass_complex([gid('clsBegin',GID)|T],[gid('clsBegin',GID)|T1],T2):-
   clk_bypass_sequence(T,T0,[gid('clsEnd',GID2)|T2]),
   append(T0,[gid('clsEnd',GID2)],T1).

@clk_bypass_op([A|T],[A|BeforeWith],After):-
   member(A,[gid('clsFor',_),gid('clsSwitch',_),gid('clsWhile',_)]),
   !,
   clk_bypass_op(T,BeforeWith,After),
   !.

@clk_bypass_op([gid('clsDo',GID)|T],[gid('clsDo',GID)|T1],T2):-
   clk_bypass_op(T,BeforeWhile,[gid('clsWhile',GIDW),gid('clsOper',EMPTY)|T2]),
   append(BeforeWhile,[gid('clsWhile',GIDW),gid('clsOper',EMPTY)],T1),
   !.

@clk_bypass_op([gid('clsIf',GID)|T],[gid('clsIf',GID)|T1],T2):-
   clk_bypass_op(T,BeforeWith,[A|AfterT]),
   (
    =(gid('clsElse',_),A)->(
      clk_bypass_op(AfterT,BeforeWith2,T2),
      append(BeforeWith,[A|BeforeWith2],T1),
      !
    );(
      =(T1,BeforeWith),=(T2,[A|AfterT]),!
    )
   ),
   !.

@clk_bypass_op([gid('clsBegin',GID)|T],T1,T2):-
   clk_bypass_complex([gid('clsBegin',GID)|T],T1,T2),
   !.

@clk_bypass_op([A|T],[A],T):-!.

@clk_insert_ending_bracket(L1,L2):-
   clk_bypass_op(L1,BeforeWith,After),
   !,
   append(BeforeWith,[gid('clsEnd',-1)|After],L2),
   !.

@clk_write_sync(S,Shift,OShift,[SPC|ST],OSPC,T,OT,GID):-
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->(
      =(Shift,'')->(
         write(S,SPC),write(S,'cilk_sync;'), nl(S),!,
         =(OShift,Shift),=(OSPC,[SPC|ST]),=(OT,T),!
      );(
         write(S,SPC),write(S,Shift),write(S,'{'),nl(S),
         write(S,SPC),write(S,Shift),write(S,'  cilk_sync;'), nl(S),!,
         atom_concat(SPC,Shift,SPC1),
         atom_concat(SPC1,'  ',SPC2),
         =(OShift,''),
         =(OSPC,[SPC2,SPC1,SPC|ST]),
         clk_insert_ending_bracket(T,OT),
         !
      )
    );(
      =(OShift,Shift),=(OSPC,[SPC|ST]),=(OT,T),!
    )
   ).

@clk_write_program(_,_,_,[]):-!.

@clk_write_program(IShift,SPCS,S,[gid('clsOper',GID)|T]):-
   db_content('prog',GID,[['op']]),
   db_content('args',GID,[['op',Op]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsOper',GID)|T],[_|T1],GID),
   atom_concat(SPC,Shift,SPC1),
   write(S,SPC1),
   (
    predicate_property(cilk_spawn(_),'dynamic'), cilk_spawn(GID)->(
      write(S,'cilk_spawn '),!
    );(
      true,!
    )
   ),
   write(S,Op), write(S,';'), nl(S),
   clk_write_program('',[SPC|ST],S,T1),
   !.

@clk_write_program(Shift,SP,S,[gid('clsComments',_)|T]):-
   clk_write_program(Shift,SP,S,T),
   !.

@clk_write_program(Shift,SP,S,[gid('clsInclude',_)|T]):-
   clk_write_program(Shift,SP,S,T),
   !.

@clk_write_program(IShift,[SPC0|ST0],S,[gid('clsBegin',GID)|T]):-
   db_content('prog',GID,[['{']]),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->(
      write(S,SPC0),write(S,IShift),write(S,'{'),nl(S),
      write(S,SPC0),write(S,IShift),write(S,'  cilk_sync;'), nl(S),!,
      atom_concat(SPC0,IShift,SPC10),
      atom_concat(SPC10,'  ',SPC20),
      =(Shift,''),
      =([SPC|ST],[SPC20,SPC10,SPC0|ST0]),
      clk_insert_ending_bracket([gid('clsBegin',GID)|T],[_|T1]),
      !
    );(
      =(Shift,IShift),=([SPC|ST],[SPC0|ST0]),=(T1,T),!
    )
   ),
   write(S,SPC), write(S,Shift), write(S,'{'), nl(S),
   atom_concat(SPC,Shift,SPC1),
   atom_concat(SPC1,'  ',SPC2),
   clk_write_program('',[SPC2,SPC1,SPC|ST],S,T1),
   !.

@clk_write_program(_,[SPC2,SPC1,SPC|ST],S,[gid('clsEnd',GID)|T]):-
   (
     (db_content('prog',GID,[['}']]), predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->(
       write(S,SPC2), write(S,'cilk_sync;'), nl(S), !
     );(
       true, !
     )
   ),
   write(S,SPC1), write(S,'}'), nl(S),
   clk_write_program('',[SPC|ST],S,T),
   !.

@clk_write_program(Shift,[SPC|ST],S,[gid('clsDo',GID)|T]):-
   db_content('prog',GID,[['do']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'do'), nl(S),
   clk_write_program(Shift1,[SPC|ST],S,T),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsWhile',GID)|T]):-
   db_content('prog',GID,[['while']]),
   db_content('args',GID,[['cond',Cond]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsWhile',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'while ( '), write(S,Cond), write(S,' )'), nl(S),
   clk_write_program(Shift1,[SPC|ST],S,T1),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsFor',GID)|T]):-
   db_content('prog',GID,[['for']]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsFor',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift),
   (
    (predicate_property(cilk_for(_),'dynamic'), cilk_for(GID))->
      write(S,'cilk_for ( ');
      write(S,'for ( ')
   ),
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
   clk_write_program(Shift1,[SPC|ST],S,T1),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsIf',GID)|T]):-
   db_content('prog',GID,[['if']]),
   db_content('args',GID,[['cond',Cond]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsIf',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'if ( '), write(S,Cond), write(S,' )'), nl(S),
   clk_write_program(Shift1,[SPC|ST],S,T1),
   !.

@clk_write_program(Shift,[SPC|ST],S,[gid('clsElse',GID)|T]):-
   db_content('prog',GID,[['else']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'else'), nl(S),
   clk_write_program(Shift1,[SPC|ST],S,T),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsSwitch',GID)|T]):-
   db_content('prog',GID,[['switch']]),
   db_content('args',GID,[['arg',Arg]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsSwitch',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(Shift), write(S,'switch ( '), write(S,Arg), write(S,' )'), nl(S),
   clk_write_program(Shift1,[SPC|ST],S,T1),
   !.

@clk_write_program(Shift,[SPC|ST],S,[gid('clsAlternation',GID)|T]):-
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
   clk_write_program(Shift,[SPC|ST],S,T),
   !.

@clk_write_program(Shift,[SPC|ST],S,[gid('clsTypedef',GID)|T]):-
   db_content('prog',GID,[['type']]),
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,'typedef '), write(S,Def), write(S,';'), nl(S),
   clk_write_program('',[SPC|ST],S,T),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsCVar',GID)|T]):-
   db_content('prog',GID,[[TYPE]]),
   member(TYPE,['struct','union']),
   !,
   db_content('args',GID,[['def',Def]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCVar',GID)|T],[_|T1],GID),
   write(S,SPC), write(S,Shift), write(S,TYPE), write(S,' '), write(S,Def), write(S,';'), nl(S),
   clk_write_program('',[SPC|ST],S,T1),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsReturn',GID)|T]):-
   db_content('prog',GID,[['return']]),
   db_content('args',GID,[['arg',Arg]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsReturn',GID)|T],[_|T1],GID),
   write(S,SPC), write(S,Shift), write(S,'return '), write(S,Arg), write(S,';'), nl(S),
   clk_write_program('',[SPC|ST],S,T1),
   !.

@clk_write_program(IShift,SPCS,S,[gid('clsPreproc',GID)|T]):-
   db_content('prog',GID,[['preproc']]),
   db_content('args',GID,[['body',Body]]),
   clk_write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsPreproc',GID)|T],[_|T1],GID),
   write(S,SPC), write(S,Shift), write(S,Body), nl(S),
   clk_write_program('',[SPC|ST],S,T1),
   !.

@clk_write_program(_,[SPC|ST],S,[gid('clsFunction',GID)|T]):-
   db_content('prog',GID,[['func']]),
   db_content('args',GID,L),
   member(['name',ID],L),
   member(['args',Args],L),
   member(['ret',Ret],L),
   !,
   write(S,SPC), write(S, Ret), write(S, ' '), write(S, ID), write(S,'( '), write(S,Args), write(S,' )'),
   clk_write_program('',[SPC|ST],S,T),
   !.

% Формирование текста программы FName по загруженным данным + spawn/sync
@clk_recreate_program(FName):-
  open(FName,write,S),
  global_trace(TR),
  clk_write_program('',[''],S,TR),
  close(S).

@clk_put_all_spawns:-
  retractall(cilk_spawn(_)),
  predicate_property(cilk_fprocs(_,_,_),'dynamic'),
  cilk_fprocs(_,_,GIDs),
  member(GID,GIDs),
  asserta(cilk_spawn(GID)),
  fail.

@clk_put_all_spawns:-!.

@clk_create_all_syncs:-
  predicate_property(cilk_function(_,_,_),'dynamic'),
  cilk_function(Fun,GID,NPrms),
  once(clk_create_syncs(Fun,GID,NPrms)),
  clk_get_ftime(Fun,NPrms,_), % Time
%  write(Fun),write(':'),write(Time),nl,
  fail.

@clk_create_all_syncs:-
%  write('--------------'), nl,
  !.

@clk_iterative_syncs_times(0):-!.

% Итерационный алгоритм последовательного добавления syncs и пересчета времен исполнения функций. Алгоритм заканчивается, когда
% времена исполнения практически перестают меняться (+/-1) или превышено число итераций N
@clk_iterative_syncs_times(N):-
  retractall(cilk_retime),
  retractall(cilk_spawn_time(_,_)),
  clk_create_all_syncs,
  cilk_retime,
  !,
  N1 is N-1,
  clk_iterative_syncs_times(N1).

@clk_iterative_syncs_times(_):-!.

@clk_sum([],0.0):-!.

@clk_sum([H|T],S):-
  clk_sum(T,S0),
  S is S0+H,
  !.

@clk_avr([],0.0):-!.

@clk_avr(L,clk_Avr):-
  clk_sum(L,S),
  length(L,N),
  clk_Avr is S/N.

% Определяем неэффективные spawn-запуски
@clk_remove_spawns:-
  predicate_property(cilk_spawn(_),'dynamic'),
  cilk_spawn(GID),
  cilk_op(_,GID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)]),
  length(Prms,NPrms),
  cilk_function(Fun,FunGID,NPrms),
  cilk_ftime(Fun,FunGID,BaseTime),
  cilk_spawn_time(GID,Timings),
  call(clk_avr(Timings,AvrTime)),
  (>(BaseTime,AvrTime) -> =(MAX,BaseTime); =(MAX,AvrTime)),
  g_read('$SpawnTime', SpawnTime),
  g_read('$SyncTime', SyncTime),
  ParExecTime is SyncTime+MAX+SpawnTime, % С учетом расходов на собственно spawn
  NonParTime is BaseTime+AvrTime,
  ( % Принятие решения об исключении spawn
    >(ParExecTime,NonParTime)->(
      once(cilk_respawn(List)),
      retractall(cilk_respawn(_)),
      asserta(cilk_respawn([GID|List]))
    );
    true
  ),
  fail.

@clk_remove_spawns:-!.

% Удаляем пометки spawn с операторов, GIDы которых прописаны в параметре-списке
@clk_delete_spawns([]):-!.

@clk_delete_spawns([H|T]):-
  retractall(cilk_spawn(H)),
  clk_delete_spawns(T).

@clk_process_syncs_and_spawns(0):-!.

% Главный цикл распараллеливания. Предварительно расставлены все возможные spawns. Итеративный циклический алгоритм. Завершается,
% когда заканчиваются подлежащие удалению spawns или превышено число итераций N
@clk_process_syncs_and_spawns(N):-
  clk_iterative_syncs_times(15), % Расставляем syncs (там, где еще не расставлены) и предсказываем время исполнения функций
  retractall(cilk_respawn(_)),
  asserta(cilk_respawn([])),
  clk_remove_spawns, % Определяем список spawns (в списке-параметре факта cilk_respawn([...])), которые дают отрицательный эффект
  % для общего времени работы. Они подлежат удалению
  cilk_respawn([First|Rest]), % Если список удаляемых spawns не пуст
  clk_delete_spawns([First|Rest]), % Удаляем пометки spawn для неэффективных случаев
  !,
  N1 is N-1,
  clk_process_syncs_and_spawns(N1).

@clk_process_syncs_and_spawns(_):-!.

@clk_has_spawns(GID):-
   predicate_property(cilk_spawn(_),'dynamic'),
   cilk_spawn(GID),
   !.

@clk_has_spawns(GID):-
   cilk_op(_,GID,_,IGIDs,_),
   !,
   member(IGID,IGIDs),
   clk_has_spawns(IGID)->
    (true,!);
    fail.

@clk_remove_syncs(GID):-
   predicate_property(cilk_sync(_),'dynamic'),
   once(cilk_sync(GID)),
   retractall(cilk_sync(GID)).

@clk_remove_syncs(GID):-
   cilk_op(_,GID,_,IGIDs,_),
   !,
   member(IGID,IGIDs),
   clk_remove_syncs(IGID),
   fail.

@clk_remove_syncs(_):-!.

% Удаление syncs из функций, в которых уже нет spawns
@clk_remove_unnecessary_syncs:-
  cilk_function(_,FunGID,_),
  \+ call(clk_has_spawns(FunGID)),
  call(clk_remove_syncs(FunGID)),
  fail.

@clk_remove_unnecessary_syncs:-!.

@clk_processing:-
  clk_prepare_cilk,
  clk_put_all_spawns,
  retractall(cilk_sync(_)),
  clk_process_syncs_and_spawns(5),
  clk_remove_unnecessary_syncs,
  (
   (predicate_property(cilk_auto_for,'dynamic'), cilk_auto_for)->clk_handle_fors;true
  ).

@atom_into_paired_list_f(_, [], []).

@atom_into_paired_list_f(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(atom_into_paired_list_f(TYPE, T, LL)).

@atom_into_paired_list_f(TYPE, V, [[TYPE, V]]).

@atom_strip_list_f([[type,''], [arg,''], [idxs,'']], []).

@atom_strip_list_f(L, L).

@atom_into_paired_list(_, '', []).

@atom_into_paired_list(_, [], []).

@atom_into_paired_list(TYPE, [H|T], [[TYPE, H]|LL]):-
  once(atom_into_paired_list(TYPE, T, LL)).

@atom_into_paired_list(TYPE, V, [[TYPE, V]]).

@atom_make_arg(TYPE, F, N, L):-
  once(atom_into_paired_list(TYPE, F, L1)),
  once(atom_into_paired_list(TYPE, N, L2)),
  append(L1, L2, L).

@atom_make_fargs([], [], [], [], []).

@atom_make_fargs([['arg','']|REFT],[TP|TPT],[NM|NMT],[IDXS|IDXST], [TP,NM,IDXS|T]):-
  once(atom_make_fargs(REFT, TPT, NMT, IDXST, T)).

@atom_make_fargs([REF|REFT],[TP|TPT],[NM|NMT],[IDXS|IDXST], [REF,TP,NM,IDXS|T]):-
  once(atom_make_fargs(REFT, TPT, NMT, IDXST, T)).

@atom_analyze_args(_, _, '').

@atom_analyze_args(GID, _, [[Name, Val]]):-
  asserta(db_content('args', GID, [[Name, Val]])).

@atom_analyze_args(GID, 'for', [['init',INITF], ['init',INITN], ['cond',COND], ['chng',CHNGF], ['chng',CHNGN]]):-
  once(atom_make_arg('init', INITF, INITN, L1)),
  once(atom_make_arg('chng', CHNGF, CHNGN, L2)),
  append(L1, [['cond',COND]], L3),
  append(L3, L2, L4),
  asserta(db_content('args', GID, L4)).

@atom_analyze_args(GID, 'func', [['arg',REF1], ['type',TYPE1], ['arg',NM1], ['idxs',IDXS1], ['arg',REFN], ['type',TYPEN], ['arg',NMN], ['idxs',IDXSN], ['arg',THREEP], ARGSV, RETV, NAMEV]):-
  once(atom_into_paired_list_f('arg', REF1, REF1L)),
  once(atom_into_paired_list_f('type', TYPE1, TYPE1L)),
  once(atom_into_paired_list_f('arg', NM1, NM1L)),
  once(atom_into_paired_list_f('idxs', IDXS1, IDXS1L)),
  once(atom_make_fargs(REF1L, TYPE1L, NM1L, IDXS1L, L1)),
  once(atom_strip_list_f(L1, L11)),
  once(atom_into_paired_list_f('arg', REFN, REFNL)),
  once(atom_into_paired_list_f('type', TYPEN, TYPENL)),
  once(atom_into_paired_list_f('arg', NMN, NMNL)),
  once(atom_into_paired_list_f('idxs', IDXSN, IDXSNL)),
  once(atom_make_fargs(REFNL, TYPENL, NMNL, IDXSNL, L2)),
  once(atom_strip_list_f(L2, L22)),
  append(L11, L22, LM),
  once((
    =(THREEP, '...')->
     append(LM, [['arg', '...']], LK);
     =(LK, LM)
  )),
  append(LK, [ARGSV, RETV, NAMEV], LL),
  asserta(db_content('args', GID, LL)).

@atom_number_sym(C):-
  member(C, ['0','1','2','3','4','5','6','7','8','9']),
  !.

@atom_ident_first_sym(C):-
  member(C, ['_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']),
  !.

@atom_ident_other_sym(C):-
  (
   atom_ident_first_sym(C) -> true; atom_number_sym(C)
  ),
  !.

@atom_find_ident2([Sym|Tag], Id, Rest):-
  atom_ident_other_sym(Sym),
  atom_find_ident2(Tag, TId, Rest),
  atom_concat(Sym, TId, Id),
  !.
@atom_find_ident2(L, '', L):-!.

@atom_find_ident([Sym|Tag], Id, Rest):-
  atom_ident_first_sym(Sym),
  !,
  atom_find_ident2(Tag, S, Rest),
  atom_concat(Sym, S, Id),
  !.

@atom_find_intn([Sym|Tag], Num, Rest):-
  atom_number_sym(Sym),
  atom_find_intn(Tag, TNum, Rest),
  atom_concat(Sym, TNum, Num),
  !.
@atom_find_intn(L, '', L):-!.

@atom_find_int2([Sym|Tag], Num, Rest):-
  atom_number_sym(Sym),
  atom_find_intn([Sym|Tag], Num, Rest),
  !.

@atom_find_int([Sym|Tag], Num, Rest):-
  atom_number_sym(Sym),
  atom_find_ident2(Tag, T, Rest),
  atom_concat(Sym, T, Num),
  !.

@atom_find_real(L, Num, Rest):-
  atom_find_int2(L, _, R1),
  (append(['.'], R2, R1), atom_find_int2(R2, _, R3); =(R3, R1)),
  (append(['E'], R4, R3); append(['e'], R4, R3)),
  !,
  (append(['+'], R5, R4); append(['-'], R5, R4); =(R5, R4)),
  !,
  atom_find_ident2(R5, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@atom_find_real(L, Num, Rest):-
  atom_find_int2(L, _, R1),
  append(['.'], R2, R1),
  atom_find_ident2(R2, _, Rest),
  append(NumL, Rest, L),
  atom_chars(Num, NumL),
  !.

@atom_parse_string(_,[], [], []):-!,fail.

@atom_parse_string(Delim, [Delim,Delim|T], [Delim|S1], Rest):-
  atom_parse_string(Delim, T, S1, Rest),
  !.

@atom_parse_string(Delim, [Delim|T], [], T):-
  !.

@atom_parse_string(Delim, [H|T], [H|S1], R):-
  atom_parse_string(Delim, T, S1, R),
  !.

@atom_parse_expr2([], []):-!.

@atom_parse_expr2([First|RR], L):-
  member(First, [' ', '\t', '\n', '\r']),
  atom_parse_expr2(RR, L).

@atom_parse_expr2(CL, L):-
  append(['\\', '\\', 'n'], RR, CL),
  atom_parse_expr2(RR, L).

@atom_parse_expr2(CL, L):-
  append(['\\', '\\', 't'], RR, CL),
  atom_parse_expr2(RR, L).

@atom_parse_expr2(['"'|RR], [dstring(H)|T]):-
  atom_parse_string('"', RR, HH, Rest),
  atom_chars(H,HH),
  atom_parse_expr2(Rest, T).

@atom_parse_expr2(['/','*'|RR], T):-
  append(_,['*','/'|Rest],RR),
  !,
  atom_parse_expr2(Rest, T).

@atom_parse_expr2([''''|RR], [cstring(H)|T]):-
  atom_parse_string('''', RR, HH, Rest),
  atom_chars(H,HH),
  atom_parse_expr2(Rest, T).

@atom_parse_expr2(CL, [H|T]):-
  append([First], RR, CL),
  (
   atom_ident_other_sym(First)->(
    (
     (atom_find_real(CL, HH, R),
      =(H, real(HH)));
     (atom_find_int(CL, HH, R),
      =(H, integ(HH)));
     (atom_find_ident(CL, HH, R),
      =(H, id(HH)))
    ),
    !,
    atom_parse_expr2(R, T)
   );(
     =(H, First),
     !,
     atom_parse_expr2(RR, T)
   )
  ),
  !.

@atom_parse_expr(S,L):-
  atom_chars(S,CL),
  atom_parse_expr2(CL, L).

@atom_get_balanced(Depth,['('|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  atom_get_balanced(Depth1,T,Delims,BAL0,[')'|R0]),
  atom_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['('|BAL0],[')'|BAL1],BAL),
  !.

@atom_get_balanced(Depth,['['|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  atom_get_balanced(Depth1,T,Delims,BAL0,[']'|R0]),
  atom_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['['|BAL0],[']'|BAL1],BAL),
  !.

@atom_get_balanced(Depth,['{'|T],Delims,BAL,Rest):-
  !,
  Depth1 is Depth+1,
  atom_get_balanced(Depth1,T,Delims,BAL0,['}'|R0]),
  atom_get_balanced(Depth,R0,Delims,BAL1,Rest),
  append(['{'|BAL0],['}'|BAL1],BAL),
  !.

@atom_get_balanced(Depth,[H|T],_,[],[H|T]):-
  \+ =(Depth,0),
  member(H,[')',']','}']),
  !.

@atom_get_balanced(Depth,[H|T],Delims,[],[H|T]):-
  =(Depth,0),
  member(H,Delims),
  !.

@atom_get_balanced(Depth,[H|T],Delims,[H|T1],Rest):-
  atom_get_balanced(Depth,T,Delims,T1,Rest),
  !.

@atom_get_balanced(0,[],_,[],[]):-!.

@atom_get_balanced(_,[],_,_,_):-!,fail.

@atom_union([H|T], L, L1):-
  member(H, L),
  atom_union(T, L, L1),
  !.
@atom_union([H|T], L, [H|T1]):-
  atom_union(T, L, T1),
  !.
@atom_union([], L, L):-!.

@atom_intersect([], _, []):-!.

@atom_intersect(_, [], []):-!.

@atom_intersect([H|T],V,[H|T1]):-
   member(H,V),
   !,
   subtract(V,[H],V1),
   !,
   atom_intersect(T,V1,T1),
   !.

@atom_intersect([_|T],V,T1):-
   atom_intersect(T,V,T1).

@atom_unique([],[]):-!.

@atom_unique([H|T],L):-
   append(Left,[H|Right],T),
   append(Left,Right,T1),
   !,
   atom_unique([H|T1],L),
   !.

@atom_unique([H|T],[H|T1]):-
   atom_unique(T,T1),
   !.

@atom_bypass_idxs(['['|T],T1,INS,OUTS,FUNS,Lazies):-
   atom_get_balanced(0,T,[']'],EXPR,[']'|T0]),
   atom_get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   atom_bypass_idxs(T0,T1,INS1,OUTS1,FUNS1,LZ1),
   atom_union(INS0,INS1,INS), atom_union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), atom_union(LZ0,LZ1,Lazies),
   !.

@atom_bypass_idxs(L,L,[],[],[],[]):-!.

@atom_rbypass_idxs(L,L1,INS,OUTS,FUNS,Lazies):-
   last(L,']'),
   !,
   append(Left1,['['|Right1],L),
   atom_get_balanced(0,Right1,[']'],EXPR,[']']),
   atom_get_expr(EXPR,INS0,OUTS0,FUNS0,LZ0),
   atom_rbypass_idxs(Left1,L1,INS1,OUTS1,FUNS1,LZ1),
   atom_union(INS0,INS1,INS), atom_union(OUTS0,OUTS1,OUTS),
   append(FUNS0,FUNS1,FUNS), atom_union(LZ0,LZ1,Lazies),
   !.

@atom_rbypass_idxs(L,L,[],[],[],[]):-!.

@atom_rbypass_var(L,V,R,INS,OUTS,FUNS,Lazies):-
   atom_rbypass_idxs(L,R0,INS0,OUTS0,FUNS0,LZ0),
   append(Left,[id(VV)],R0),
   !,
   (
    ( append(Left1,['.'],Left); append(Left1,['-','>'],Left) )->
     (
      atom_rbypass_var(Left1,V,R,INS1,OUTS1,FUNS1,LZ1),
      atom_union(INS0,INS1,INS), atom_union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), atom_union(LZ0,LZ1,Lazies)
     );
     (=(V,VV),=(R,Left),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0))
   ),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['<','<','='|Right],L),
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['>','>','='|Right],L),
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,[A,'='|Right],L),
   member(A,['+','-','*','/','|','&','^','%']),
   !,
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+'|Right],L),
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-'|Right],L),
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['+','+',id(V)|Right],L),
   atom_bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],[V|Ins],Funs,Lazs):-
   append(Left,['-','-',id(V)|Right],L),
   atom_bypass_var([id(V)|Right],Right0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right0,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,[V|OUTST],Ins,Funs,Lazs):-
   append(Left,['='|Right],L),
   last(Left,A),
   \+ member(A,['=','!','<','>']),
   \+ =(Right,['='|_]),
   !,
   atom_rbypass_var(Left,V,Left0,Ins0,Outs0,Funs0,Laz0),
   !,
   atom_get_assgns(Left0,OUTST1,Ins1,Funs1,Laz1),
   atom_get_assgns(Right,OUTST2,Ins2,Funs2,Laz2),
   !,
   atom_union(OUTST1,OUTST2,OUTST3), atom_union(OUTST3,Outs0,OUTST),
   atom_union(Ins1,Ins2,Ins3), atom_union(Ins3,Ins0,Ins),
   atom_union(Funs1,Funs2,Funs3), atom_union(Funs3,Funs0,Funs),
   atom_union(Laz1,Laz2,Laz3), atom_union(Laz3,Laz0,Lazs),
   !.

@atom_get_assgns(L,Outs,Ins,Funs,Lazs):-
   atom_get_vars(L,Ins,Outs,Funs,Lazs),
   !.

@atom_bypass_var([id(_)|T],R,INS,OUTS,FUNS,Lazies):-
   atom_bypass_idxs(T,R0,INS0,OUTS0,FUNS0,LZ0),
   (
    ( =(['.'|R1],R0); =(['-','>'|R1],R0) )->
     (
      atom_bypass_var(R1,R,INS1,OUTS1,FUNS1,LZ1),
      atom_union(INS0,INS1,INS), atom_union(OUTS0,OUTS1,OUTS),
      append(FUNS0,FUNS1,FUNS), atom_union(LZ0,LZ1,Lazies)
     );(
      =(R,R0),=(INS,INS0),=(OUTS,OUTS0),=(FUNS,FUNS0),=(Lazies,LZ0)
     )
   ),
   !.

@atom_glob_prefixate([],[]):-!.

@atom_glob_prefixate([var(H,TP)|T],[global(H,TP)|T1]):-
   atom_glob_prefixate(T,T1).

@atom_get_glob_lazies(Fun,NPrms,GP,LP,ILP):-
   atomic_function(Fun,GID,NPrms),
   predicate_property(atomic_fanalyzed(_,_,_,_,_),'dynamic'),
   atomic_fanalyzed(Fun,GID,Globs,LP,ILP),
   atom_glob_prefixate(Globs, GP),
   !.

@atom_get_glob_lazies(_,_,[],0,[]):-!.

@atom_get_ftime(Fun,NPrms,T):-
   atomic_function(Fun,GID,NPrms),
   predicate_property(atomic_ftime(_,_,_),'dynamic'),
   atomic_ftime(Fun,GID,T),
   !.

@atom_get_ftime(_,_,T):-  % Содержит время исполнения функции по умолчанию
  g_read('$DefFTime',T),
  !.

@atom_put_ftime(Fun,NPrms,T):-
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

@atom_put_ltime(GID,T):-
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

@atom_getTime([],T):-
   g_read('$DefOperTime', T),
   !.

@atom_getTime([V|T],TM):-
   =..(V,[_,F,Prms]),
   length(Prms,N),
   atom_get_ftime(F,N,T0),
   atom_getTime(T,T1),
   TM is T0+T1,
   !.

@atom_extract_singles([],[]):-!.

@atom_extract_singles([[]|T],L):-
  atom_extract_singles(T,L),
  !.

@atom_extract_singles([[V]|T],[V|L]):-
  atom_extract_singles(T,L),
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
@atom_get_lazies(Fun, [], GP, [], _, []):-
     atom_get_glob_lazies(Fun,0,GP,_,_),
     !.

@atom_get_lazies(Fun, Params, [], _, ParSingleMap, _):-
   predicate_property(atomic_farg(_,_,_,_,_,_),'dynamic')->(
     length(Params,N),
     once(atomic_farg(Fun,N,_,_,_,_)),
     asserta(counter(0)),
     atom_get_glob_lazies(Fun,N,GP,LP,ReadParams),
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
     atom_bypass_var([id(P)|TT],[],_,_,_,_),
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

@atom_get_lazies(_, Params, LZ, Refs, _, ISingles):-
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

@atom_get_lazies(_, _, [], [], ParSingleMap, ISingles):-
   atom_extract_singles(ParSingleMap,ISingles),
   !.

@atom_get_fparams(Mode, Fun, NPrms, []):-
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
     ( =(Idxs,'[]')->once(=(ParsedIdxs,[]));once(atom_parse_expr(Idxs,ParsedIdxs)) ),
     once(atom_parse_expr(Type,ParsedType)),
     once(append(LZ,[var(V,type(ParsedType,ParsedIdxs))],LZ1)),
     asserta(params(LZ1)),
     fail
   );(
     true,!
   ).

@atom_get_fparams(_, _, NPrms, LZ):-
   predicate_property(params(_),'dynamic'),
   params(LZ),
   counter(NPrms),
   retractall(params(_)),
   retractall(counter(_)),
   !.

@atom_get_fparams(_, _, _, []):-!.

@atom_get_funs(L,[func(F,Params)|T],INS,OUTS,Lazies):-
   append(_,[id(F),'('|Right],L),
   !,
   atom_get_fun_params(F,Right,[')'|Rest],Params,INS0,ParSingleMap,OUTS0,FUNS0,LZZ),
   !,
   atom_get_lazies(F,Params,LZ0,_,ParSingleMap,INSI),
   !,
   atom_get_funs(Rest,FUNS1,INS1,OUTS1,LZ1),
   atom_union(OUTS0,OUTS1,OUTS),
   atom_union(INS0,INS1,INS2), atom_union(INS2,INSI,INS),
   append(FUNS0,FUNS1,T),
   atom_union(LZZ,LZ0,LZ2),
   atom_union(LZ2,LZ1,Lazies),
   !.

@atom_get_funs(_,[],[],[],[]):-!.

@atom_extract_lzv([],[]):-!.

@atom_extract_lzv([par(_,_,V)|T],[V|T1]):-
   atom_extract_lzv(T,T1),
   !.

@atom_extract_lzv([global(V,_)|T],[V|T1]):-
   atom_extract_lzv(T,T1),
   !.

@atom_get_vars([],[],[],[],[]):-!.

@atom_get_vars([id(V),A|T],[V|TT],Outs,FUNS,Lazies):-
   \+ =(A,'('),
   atom_bypass_var([id(V),A|T],T0,INS0,OUTS0,FUNS0,LZ0),
   !,
   atom_get_vars(T0,INS1,OUTS1,FUNS1,LZ1),
   atom_union(INS0,INS1,TT), atom_union(OUTS0,OUTS1,Outs),
   append(FUNS0,FUNS1,FUNS), atom_union(LZ0,LZ1,Lazies).

@atom_get_vars([id(_),'('|T],Ins,Outs,FUNS,Lazies):-
   atom_get_balanced(0,T,[')'],_,[')'|T0]),
   !,
   atom_get_vars(T0,Ins,Outs,FUNS,Lazies).

@atom_get_vars([id(V)],[V],[],[],[]):-
   !.

@atom_get_vars([_|T],INS,OUTS,FUNS,Lazies):-
   atom_get_vars(T,INS,OUTS,FUNS,Lazies).   

@atom_get_expr(L,INS,OUTS,FUNS,Lazies):-
   atom_get_assgns(L,OUTS0,INS0,FUNSV,LZV),!,
   atom_get_funs(L,FUNS0,INS1,OUTS1,LZ0),
   atom_union(INS0,INS1,INS2),
   atom_unique(INS2,INS),
   atom_union(OUTS0,OUTS1,OUTS2),
   atom_unique(OUTS2,OUTS20), !,
   append(FUNS0,FUNSV,FUNS),
   atom_union(LZ0,LZV,LZB),
   atom_unique(LZB,Lazies),
   atom_extract_lzv(Lazies,LaziesV),
   atom_union(OUTS20,LaziesV,OUTSZ),
   atom_unique(OUTSZ,OUTS),
   !.

@atom_check_arg([id(V)|Rest],[V]):-
   atom_bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@atom_check_arg(['&',id(V)|Rest],[V]):-
   atom_bypass_var([id(V)|Rest],[],_,_,_,_),
   !.

@atom_check_arg(_,[]):-
   !.

@atom_get_fun_params(_,[')'|R],[')'|R],[],[],[],[],[],[]):-!.

@atom_get_fun_params(Fun,L,R,[P|T],INS,[V|MAP],OUTS,FUNS,Lazies):-
   atom_get_balanced(0,L,[',',')'],P,[','|Rest]),
   atom_get_expr(P,INS1,OUTS1,FUNS1,LZ1),
   ((atomic_function(Fun,_,_),=(OUTS3,[]));atom_check_arg(P,OUTS3)),
   atom_check_arg(P,V),
   !,
   atom_get_fun_params(Fun,Rest,R,T,INS2,MAP,OUTS2,FUNS2,LZ2),
   (
    =(V,[Single])->
      subtract(INS1,[Single],INSQ);
      =(INSQ,INS1)
   ),
   atom_union(INSQ,INS2,INS),
   atom_union(OUTS1,OUTS2,OUTSK), atom_union(OUTSK,OUTS3,OUTS), append(FUNS1,FUNS2,FUNS), atom_union(LZ1,LZ2,Lazies),
   !.

@atom_get_fun_params(Fun,L,[')'|Rest],[Item],INS,[V],OUTS,FUNS,Lazies):-
   atom_get_balanced(0,L,[',',')'],Item,[')'|Rest]),
   atom_get_expr(Item,INS1,OUTS0,FUNS,Lazies),
   ((atomic_function(Fun,_,_),=(OUTS3,[]));atom_check_arg(Item,OUTS3)),
   atom_check_arg(Item,V),
   !,
   (
    =(V,[Single])->
      subtract(INS1,[Single],INS);
      =(INS,INS1)
   ),
   atom_union(OUTS0,OUTS3,OUTS),
   !.

@atom_analyze_item_expr(intros(TP),[id(V)|T],INS,[V|OUTT],[var(V,type(TP,IDXS))],FUNS,[],[],[]):-
   atom_bypass_idxs(T,['='|Rest],INS0,OUTS0,FUNS0,_),
   append(IDXS,['='|Rest],T),
   \+ =(Rest,['='|_]),
   atom_get_expr(Rest,INS1,OUTS1,FUNS1,_),
   !,
   atom_union(INS0,INS1,INSA), atom_union(OUTS0,OUTS1,OUTTA), append(FUNS0,FUNS1,FUNS),
   atom_unique(INSA,INS), atom_unique(OUTTA,OUTT),
   !.

@atom_analyze_item_expr(intros(TP),[id(V)|T],INS,[V|OUTS],[var(V,type(TP,T))],FUNS,[],[],LAZIES):-
   atom_bypass_idxs(T,[],INS,OUTS,FUNS,LAZIES),
   !.

@atom_analyze_item_expr(inits,[id(V),'('|T],INS,OUTS,[],FUNS,[proc(V,L)],REFS,Lazies):-
   atom_get_fun_params(V,T,[')'],L,INS0,ParSingleMap,OUTS0,FUNS,LZ0),
   !,
   atom_get_lazies(V,L,Lazies,Refs0,ParSingleMap,INSI),
   !,
   % atom_get_lazies возвращает ленивые выходные переменные Lazies уже с учетом результатов анализа. Возвращает Refs0 -- переменные
   % в параметрах &|*, не являющиеся выходными. Возвращает INSI -- все входные переменные в параметрах, используемые в функции
   atom_extract_lzv(LZ0,LZV),
   atom_union(OUTS0,LZV,OUTP),
   atom_extract_lzv(Lazies,LaziesV),
   subtract(Refs0,LaziesV,REFS),
   atom_union(OUTP,LaziesV,OUTS2),
   atom_unique(OUTS2,OUTS),
   atom_union(INS0,INSI,INS2), atom_unique(INS2,INS),
   !.

@atom_analyze_item_expr(inits,L,INS,OUTS,[],FUNS,[expr],[],[]):-
   atom_get_expr(L,INS,OUTS,FUNS,_),
   !.

@atom_analyze_list_expr(_,[],[],[],[],[],[],[],[]):-!.

@atom_analyze_list_expr(Mode,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   atom_get_balanced(0,L,[','],Item,Rest),
   (=([','|T],Rest)->true;=(T,Rest)),
   !,
   atom_analyze_item_expr(Mode,Item,INS0,OUTS0,NEWS0,FUNS0,PROCS0,REFS0,LZ0),
   !,
   atom_analyze_list_expr(Mode,T,INS1,OUTS1,NEWS1,FUNS1,PROCS1,REFS1,LZ1),
   atom_union(INS0,INS1,INS2),
   atom_union(OUTS0,OUTS1,OUTS2),
   atom_union(NEWS0,NEWS1,NEWS2),
   append(FUNS0,FUNS1,FUNS),
   atom_union(PROCS0,PROCS1,PROCS2),
   atom_union(REFS0,REFS1,REFS2),
   atom_union(LZ0,LZ1,LZ2),
   !,
   atom_unique(INS2,INS), atom_unique(OUTS2,OUTS), atom_unique(NEWS2,NEWS),
   atom_unique(PROCS2,PROCS), atom_unique(REFS2,REFS), atom_unique(LZ2,Lazies),
   !.

@atom_declaration([id(_)]):-!.

@atom_declaration([id(_)|T]):-
  atom_declaration(T).

% atom_analyze_expr(parsed_list,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES)
% INS -- список переменных, значения которых = входные для выражения
% OUTS -- список переменных, которые в выражении получают значения в результате ПРИСВАИВАНИЙ (простых и совмещенных) и в &-параметрах
%           функций (не ленивых). Ленивая -- только главная функция! Новые переменные выходными НЕ ЯВЛЯЮТСЯ!
% NEWS -- переменные, декларированные в текущем выражении
% FUNS -- список элементов func(V,L) = вызываемых функций с именами V и списками аргументов L
% PROCS -- список элементов proc(V,L) = вызываемых процедур с именами V и списками аргументов L. В норме -- список из одного элемента
% REFS -- список выходных (&,*)-параметров в процедуре, не относящихся к ленивым. Они не получают в такой процедуре значения
% LAZIES -- список потенциально ленивых переменных = выходных (&,*) в процедуре. Не имеет прямого отношения к OUTS, ДОЛЖЕН с ним пересекаться
@atom_analyze_expr([],[],[],[],[],[],[],[]):-!.

@atom_analyze_expr(['*'|Rest],Ins,Outs,News,Funs,Procs,Refs,Lazies):-
   atom_analyze_expr(Rest,Ins,Outs,News,Funs,Procs,Refs,Lazies),
   !.

@atom_analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*',id(V1)],L),
   append(D,['*'],DD),
   atom_declaration(D),
   !.

@atom_analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*',id(V1)],L),
   append(D,['*','*'],DD),
   atom_declaration(D),
   !.

@atom_analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*','*',id(V1)],L),
   append(D,['*','*','*'],DD),
   atom_declaration(D),
   !.

@atom_analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['&',id(V1)],L),
   append(D,['&'],DD),
   atom_declaration(D),
   !.

@atom_analyze_expr(L,[],[V1],[var(V1,type(D,[]))],[],[],[],[]):-
   append(D,[id(V1)],L),
   atom_declaration(D),
   !.

@atom_analyze_expr([id(V)],[V],[],[],[],[],[],[]):-
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*',id(V1),A|T1],L),
   atom_declaration(D),
   append(D,['*'],DD),
   member(A,['=',',','[']),
   !,
   atom_analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   atom_union(OUTS0,[V1],OUTS),
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*',id(V1),A|T1],L),
   atom_declaration(D),
   append(D,['*','*'],DD),
   member(A,['=',',','[']),
   !,
   atom_analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   atom_union(OUTS0,[V1],OUTS),
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*','*',id(V1),A|T1],L),
   atom_declaration(D),
   append(D,['*','*','*'],DD),
   member(A,['=',',','[']),
   !,
   atom_analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   atom_union(OUTS0,[V1],OUTS),
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['&',id(V1),A|T1],L),
   atom_declaration(D),
   append(D,['&'],DD),
   member(A,['=',',','[']),
   !,
   atom_analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   atom_union(OUTS0,[V1],OUTS),
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,[id(V1),A|T1],L),
   atom_declaration(D),
   member(A,['=',',','[']),
   !,
   atom_analyze_list_expr(intros(D),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   atom_union(OUTS0,[V1],OUTS),
   !.

@atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   atom_analyze_list_expr(inits,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies),
   !.

@atom_get_params_length([], 0):-!.

@atom_get_params_length([[arg,'...']],infinity):-!.

@atom_get_params_length([[idxs,_]|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([[type,_]|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([[arg,'&']|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([[arg,'*']|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([[arg,'**']|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([[arg,'***']|T], N):-
   atom_get_params_length(T,N),
   !.

@atom_get_params_length([_|T], N1):-
   atom_get_params_length(T,N),
   (
    =(N,infinity)->
     =(N1,infinity);
     N1 is N+1
   ),
   !.

@atom_prepare_atomic_function(_,_,[]):-!.

@atom_prepare_atomic_function(Name,N,[[name,Name]|T]):-
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[args,_]|T]):-
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[type,TP],[arg,V],[idxs,Idxs]|T]):-
   \+ atom_length(Idxs,0),
   assertz(atomic_farg(Name,N,'[]',V,TP,Idxs)),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[arg,'&'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'&',V,TP,[])),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[arg,'*'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'*',V,TP,[])),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[arg,'**'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'**',V,TP,[])),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[arg,'***'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(atomic_farg(Name,N,'***',V,TP,[])),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_function(Name,N,[[type,TP],[arg,V],[idxs,'']|T]):-
   assertz(atomic_farg(Name,N,'',V,TP,[])),
   !,
   atom_prepare_atomic_function(Name,N,T).

@atom_prepare_atomic_functions:-
   global_trace(TR),
   db_content('prog',GID,[[func]]),
   db_content('args',GID,Params),
   once(append(_,[gid('clsFunction',GID),gid('clsBegin',_)|_],TR)),
   member([name,Name],Params),
   atom_get_params_length(Params,N),
   \+ =(N,infinity),
   N1 is N-3, % -args, -ret, -name
   asserta(atomic_function(Name,GID,N1)),
   call(atom_prepare_atomic_function(Name,N1,Params)),write(Params),
   fail.

@atom_prepare_atomic_functions:-!.

@atom_prepare_ifor([],_,[]):-!.

@atom_prepare_ifor([[Type,V]|T],Type,[VAL|TT]):-
   atom_parse_expr(V,L),
   !,
   atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !,
   =..(VAL,[Type,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L]]),
   atom_prepare_ifor(T,Type,TT).

@atom_prepare_ifor([_|T],Type,TT):-
   !,
   atom_prepare_ifor(T,Type,TT).

@atom_prepare_ops(Type,GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   member(Type,['clsWhile','clsSwitch','clsIf','clsReturn','clsOper']),
   !,
   db_content('args',GID,[[_,Opnd]]),
   !,
   atom_parse_expr(Opnd,L),
   !,
   atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

@atom_prepare_ops('clsAlternation',GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   atom_parse_expr(Opnd,L),
   !,
   atom_analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

% (default:) in switch-case
@atom_prepare_ops('clsAlternation',_,[arg([],[],[],[],[],[],[],[])]):-
   !.

@atom_prepare_ops('clsFor',GID,OPL):-
   db_content('args',GID,L),
   atom_prepare_ifor(L,'init',OPL1),
   atom_prepare_ifor(L,'cond',OPL2),
   atom_prepare_ifor(L,'chng',OPL3),
   !,
   append(OPL1,OPL2,OPLP), append(OPLP,OPL3,OPL),
   !.

% Помещает в базу факт atomic_op(Class,GID1,GID2,IDs,Ops) только втом случае, если его еще в базе не было,
% или он был, но с другими ops. В последнем случае устанавливается флаг-факт atomic_recalculate. Это требуется
% для нормальной работы итеративной процедуры уточнения состава ленивых переменных/параметров для каждой функции
@atom_put_atomic_op(Class,GID1,GID2,IDs,Ops):-
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

@atom_get_atomic_fseq([gid('clsEnd',GID)|Rest],[gid('clsEnd',GID)|Rest],[]):-!.

@atom_get_atomic_fseq(L,Rest,[GID|IDT]):-
   atom_get_atomic_fop(L,Rest0,GID),
   !,
   atom_get_atomic_fseq(Rest0,Rest,IDT),
   !.

@atom_get_atomic_fop([gid('clsBegin',GID1)|T],Rest,GID1):-
   atom_get_atomic_fseq(T,[gid('clsEnd',GID2)|Rest],IDs),
   !,
   atom_put_atomic_op('clsBegin',GID1,GID2,IDs,[]),
   !.

@atom_get_atomic_fop([gid(Type,GID)|T],Rest,GID):-
   member(Type,['clsFor','clsSwitch','clsWhile']),
   !,
   atom_get_atomic_fop(T,Rest,OPID),
   !,
   atom_prepare_ops(Type,GID,OPL),
   atom_put_atomic_op(Type,GID,-1,[OPID],OPL),
   !.

@atom_get_atomic_fop([gid('clsDo',GID)|T],Rest,GID):-
   atom_get_atomic_fop(T,[gid('clsWhile',GID1),gid('clsOper',EmptyGID)|Rest],OPID),
   db_content('args',EmptyGID,[[op,'']]),
   !,
   atom_prepare_ops('clsWhile',GID1,OPL),
   atom_put_atomic_op('clsDo',GID,GID1,[OPID],OPL),
   !.

@atom_get_atomic_fop([gid('clsIf',GID)|T],Rest,GID):-
   atom_get_atomic_fop(T,Rest0,OPID0),
   !,
   atom_prepare_ops('clsIf',GID,OPL),
   (
    =(Rest0,[gid('clsElse',GID1)|Rest1])->(
       atom_get_atomic_fop(Rest1,Rest,OPID1),
       atom_put_atomic_op('clsIf',GID,GID1,[OPID0,OPID1],OPL)
    );(
       atom_put_atomic_op('clsIf',GID,-1,[OPID0],OPL),
       =(Rest,Rest0)
    )
   ),
   !.

@atom_get_atomic_fop([gid('clsPreproc',GID)|T],T,GID):-
   atom_put_atomic_op('clsPreproc',GID,-1,[],[]),
   !.

@atom_get_atomic_fop([gid(Type,GID)|T],T,GID):-
   atom_prepare_ops(Type,GID,OPL),
   atom_put_atomic_op(Type,GID,-1,[],OPL),
   !.

@atom_get_atomic_fprocs([],[]):-!.

@atom_get_atomic_fprocs([GID|T],[GID|TT]):-
   atomic_op('clsOper',GID,_,[],[arg(_,_,_,_,[proc(Name,_)],_,_,_)]),
   atomic_function(Name,_,_),
   !,
   atom_get_atomic_fprocs(T,TT),
   !.
   
@atom_get_atomic_fprocs([GID|T],PGIDS):-
   atomic_op(_,GID,_,LGIDs,_),
   !,
   atom_get_atomic_fprocs(LGIDs,PGIDS0),
   atom_get_atomic_fprocs(T,PGIDS1),
   !,
   append(PGIDS0,PGIDS1,PGIDS),
   !.

@atom_build_atomic_function(Fun,FGID,Body):-
   atom_get_atomic_fop(Body,[],OPID),
   atom_put_atomic_op('clsFunction',FGID,-1,[OPID],[]),
   atom_get_atomic_fprocs([OPID],ProcsGIDs),
   asserta(atomic_fprocs(Fun,FGID,ProcsGIDs)),
   !.

% Анализ (структурный, в глубину) всех функций с разбором выражений, результаты которого попадают в atomic_op
@atom_build_atomic_functions:-
   global_trace(TR),
   retractall(atomic_fprocs(_,_,_)),
   !,
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Fun,GID,_),
      once(append(_,[gid('clsFunction',GID)|T],TR)),
      atom_bypass_complex(T,Body,_),
      call(atom_build_atomic_function(Fun,GID,Body)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@atom_get_globals([],[]):-!.

@atom_get_globals([gid('clsCVar',GID)|T],[var(V,type(TP,IDXS))|T1]):-
   db_content('args',GID,[[_,Arg]]),
   !,
   atom_parse_expr(Arg,L),
   atom_rbypass_var(L,V,TP,_,_,_,_),
   append(TP,[id(V)|IDXS],L),
   atom_get_globals(T,T1).

@atom_get_globals([gid('clsOper',GID)|T],T1):-
   db_content('args',GID,[[_,Arg]]),
   !,
   atom_parse_expr(Arg,L),
   atom_analyze_expr(L,_,_,NEWS,_,_,_,_),
   atom_get_globals(T,T0),
   append(NEWS,T0,T1),
   !.

@atom_get_globals([gid('clsFunction',_)|T],T1):-
   atom_bypass_complex(T,_,After),
   atom_get_globals(After,T1),
   !.

@atom_get_globals([_|T],T1):-
   atom_get_globals(T,T1).

@atom_find_globals:-
   global_trace(TR),
   atom_get_globals(TR,GLOBS),
   asserta(atomic_globals(GLOBS)),
   !.

@atom_addLocals([],News,[News]):-!.

@atom_addLocals([L|T],News,[L1|T]):-
   append(L,News,L0),
   !,
   atom_unique(L0,L1),
   !.

@atom_excludeLocals(V,[],V):-!.

@atom_excludeLocals(Vars,[Locs|T],Outs):-
   subtract(Vars,Locs,Vars0),
   atom_excludeLocals(Vars0,T,Outs),
   !.

@atom_getNewInOutLazies([],[],[],[],[],0.0):-!.

@atom_getNewInOutLazies([V|T],News,Ins,Outs,Lazies,TM):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,_,_,Laz0,_]),
   atom_getTime(Funs0,T0),
   atom_getNewInOutLazies(T,News1,Ins1,Outs1,Laz1,T1),
   !,
   append(News0,News1,News2), append(Outs0,Outs1,Outs2), append(Laz0,Laz1,Laz2), append(Ins0,Ins1,Ins2),
   atom_unique(News2,News), atom_unique(Outs2,Outs), atom_unique(Laz2,Lazies), atom_unique(Ins2,Ins),
   TM is T0+T1,
   !.

@atom_extract_var_names([],[]):-
   !.

@atom_extract_var_names([var(Name,_)|T],[Name|T1]):-
   atom_extract_var_names(T,T1),
   !.

@atom_analyze_one_flazies([],_,_,_,[],[],[]):-!.

% ReadParams -- читаемые в самой функции ее ленивые параметры (не только выходные, но и входные)
@atom_analyze_one_flazies([GID|GIDS],Globs,Pars,Locals,GLazies,PLazies,ReadParams):-
   atomic_op(_,GID,_,IGIDs,Ops),
   atom_getNewInOutLazies(Ops,News,Ins,Outs,_,_),
   atom_addLocals(Locals,News,Locals1),
   atom_excludeLocals(Outs,Locals1,PreOuts),
   atom_excludeLocals(Ins,Locals1,PreIns),
   atom_intersect(PreOuts,Pars,PLA),
   atom_intersect(PreIns,Pars,ILA),
   subtract(PreOuts,PLA,PreOuts1),
   atom_intersect(PreOuts1,Globs,GLA),
   atom_analyze_one_flazies(IGIDs,Globs,Pars,[News|Locals],GL0,PL0,IL0),
   atom_analyze_one_flazies(GIDS,Globs,Pars,Locals1,GL1,PL1,IL1),
   append(GL0,GL1,GL2), append(GL2,GLA,GL3), append(PL0,PL1,PL2), append(PL2,PLA,PL3),
   append(IL0,IL1,IL2), append(IL2,ILA,IL3),
   atom_unique(GL3,GLazies), atom_unique(PL3,PLazies), atom_unique(IL3,ReadParams),
   !.

@atom_analyze_flazies(Fun,NPrms,GLazies,PLazies,ReadParams):-
   atomic_function(Fun,GID,NPrms),
   !,
   (
    (predicate_property(atomic_fanalyzed(_,_,_,_,_),'dynamic'), atomic_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams))->(
     true,!
     );(
     atom_get_fparams(lazy,Fun,NPrms,LPars0),
     !,
     atomic_globals(GlobVars),
     atom_extract_var_names(GlobVars,Glob0),
     !,
     asserta(atomic_fanalyzed(Fun,GID,[],LPars0,LPars0)),
     atom_analyze_one_flazies([GID],Glob0,LPars0,[],GLazies,PLazies,ReadParams),
     retractall(atomic_fanalyzed(Fun,GID,[],_,_)),
     asserta(atomic_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams)),
     !
    )
   ).

% Определение выходных переменных (глобальных и потенциально модифицируемых параметров) для каждой функции. Для этого проводится
% структурный анализ функции в глубину (с отслеживанием локально декларированных переменных, изменение которых нас здесь не интересует),
% выявляются модифицируемые переменные. Модифицируемые глобалы и параметры попадают в atomic_fanalyzed
@atom_analyze_atomic_functions:-
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Fun,_,N),
      call(atom_analyze_flazies(Fun,N,_,_,_)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Итерационное сходящееся уточнение состава ленивых переменных/параметров функций (atomic_fanalyzed). На каждой итерации
% для каждой функции уточняется список модифицируемых глобальных переменных и &|*-параметров. Это делается в atom_analyze_atomic_functions.
% Это уточнение может влиять на другие функции, вызывающие уточненные. Сначала считается, что функция модифицирует все свои &|*-параметры,
% они входят в соответствующие списки atomic_fanalyzed, потом эти списки урезаются, в то время как списки глобальных переменных расщиряются.
% Проходит "волна" уточнений, в результате которой, например, функции int p1(int &x) { p2(x); }, int p2(int & x) { cout << x; } в последнем
% приближении уже не имеют выходных ленивых значений вообще, в то время как функции int p1() { p2(); }, int p2() { X = 11; } имеют один
% ленивый результат -- глобальную переменную X.
% После оередного уточнения, выполняется перестройка atomic_op-фактов, в которых выполняется новый разбор выражений с учетом новых данных
% о ленивости. Если при этом изменится хоть один факт, то устанавливается atomic_reanalyze, что свидетельствует о необходимости как минимум
% еще одной итерации.
@atom_iterative_build_funs:-
   retractall(atomic_reanalyze),
   atom_build_atomic_functions,
   (
    (predicate_property(atomic_reanalyze,'dynamic'), atomic_reanalyze)->(
      retractall(atomic_fanalyzed(_,_,_,_,_)),
      atom_analyze_atomic_functions,
      atom_iterative_build_funs,
      !
    );(
      true, !
    )
   ),
   !.

@atom_extract_idx(['-','>',id(_)|Rest],EXPR):-
   atom_extract_idx(Rest,EXPR),
   !.

@atom_extract_idx(['.',id(_)|Rest],EXPR):-
   atom_extract_idx(Rest,EXPR),
   !.

@atom_extract_idx(['['|Rest],[EXPR|EXPRT]):-
   atom_get_balanced(0,Rest,[']'],EXPR,[']'|Rest0]),
   !,
   atom_extract_idx(Rest0,EXPRT),
   !.

@atom_extract_idx(_,[]):-
   !.

@atom_extract_idxs(L,T):-
   append(_,[id(V)|TT],L),
   !,
   atom_extract_idx(TT,Idxs),
   !,
   atom_extract_idxs(TT,T0),
   atom_union([var(V,Idxs)],T0,T),
   !.

@atom_extract_idxs(_,[]):-
   !.

@atom_get_expr_idxs([],[]):-
   !.

@atom_get_expr_idxs([E|T],Idxs):-
   =..(E,[_,_,_,_,_,_,_,_,[L]]),
   !,
   atom_extract_idxs(L,Idxs1),
   atom_get_expr_idxs(T,Idxs2),
   atom_union(Idxs1,Idxs2,Idxs),
   !.

@atom_get_var_idxs([],[]):-
   !.

@atom_get_var_idxs([GID|T],Idxs):-
   atomic_op(_,GID,_,LGIDs,Exprs),
   !,
   atom_get_expr_idxs(Exprs,Idxs0),
   !,
   atom_get_var_idxs(LGIDs,Idxs1),
   atom_get_var_idxs(T,Idxs2),
   atom_union(Idxs0,Idxs1,IdxsA), atom_union(IdxsA,Idxs2,Idxs),
   !.

@atom_get_list_deps(_,[]):-
   !.

@atom_get_list_deps(NamePath,[V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   atom_get_fdeps(Name,NamePath,NPrms),
   atom_get_list_deps(NamePath,T),
   !.

@atom_get_expr_deps(_,[]):-
   !.

@atom_get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   atom_get_list_deps(NamePath,FUNS),
   atom_get_expr_deps(NamePath,T),
   !.

@atom_get_expr_deps(NamePath,[V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   atom_get_list_deps(NamePath,FUNS),
   atom_get_list_deps(NamePath,PROCS),
   atom_get_expr_deps(NamePath,T),
   !.

@atom_get_block_deps(_,[]):-
   !.

@atom_get_block_deps(NamePath,[GID|T]):-
   atomic_op(_,GID,_,LGIDs,Exprs),
   atom_get_expr_deps(NamePath,Exprs),
   atom_get_block_deps(NamePath,LGIDs),
   !,
   atom_get_block_deps(NamePath,T),
   !.

@atom_mark_deps([]):-
   !.

@atom_mark_deps([path(Name,NPrms)|T]):-
   (
    (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,t))->(
      true,!
    );(
      retractall(atomic_fdependent(Name,NPrms,_)), asserta(atomic_fdependent(Name,NPrms,t))
    )
   ),
   atom_mark_deps(T).

@atom_get_fdeps(Name,NamePath,NPrms):-
   member(path(Name,NPrms),NamePath),
   !.

@atom_get_fdeps(Name,NamePath,NPrms):-
   atomic_function(Name,GID,NPrms),
   atomic_op('clsFunction',GID,_,LGIDs,_),
   (
    (predicate_property(atomic_fdependent(_,_,_),'dynamic'),atomic_fdependent(Name,NPrms,_))->(
      true,!
    );(
      atom_get_block_deps([path(Name,NPrms)|NamePath],LGIDs),
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
        atom_mark_deps(NamePath);
        true
   ).

@atom_get_fdeps(Name,NamePath,NPrms):-
   \+ atomic_function(Name,_,NPrms),
   (
    (predicate_property(cilk_fpure(_),'dynamic'),cilk_fpure(Name))->
       true;
       atom_mark_deps(NamePath)
   ),
   !.

% Определение зависимостей функций от внешних функций
@atom_find_dependents:-
   (
    predicate_property(atomic_function(_,_,_),'dynamic')->(
     (
      atomic_function(Name,_,NPrms),
      call(atom_get_fdeps(Name,[],NPrms)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@atom_get_comma_list([V,')'],[F]):-
   =..(V,[_,F]),
   !.

@atom_get_comma_list([V,','|R],[F|T]):-
   =..(V,[_,F]),
   atom_get_comma_list(R,T).

@atom_get_next_op(GID,Next):-
   atomic_op(_,_,_,GIDs,_),
   append(_,[GID,Next|_],GIDs),
   !.

@atom_get_next_op(GID,Next):-
   global_trace(GIDs),
   append(_,[gid(_,GID),gid(_,Next)|_],GIDs),
   !.

@atom_into_atom([],_,''):-
   !.

@atom_into_atom([id(V)|T],Gap,A):-
   atom_into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@atom_into_atom([real(V)|T],Gap,A):-
   atom_into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@atom_into_atom([integ(V)|T],Gap,A):-
   atom_into_atom(T,Gap,A1),
   atom_concat(V,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@atom_into_atom([Z|T],Gap,A):-
   atom_into_atom(T,Gap,A1),
   atom_concat(Z,Gap,A2),
   atom_concat(A2,A1,A),
   !.

@atom_analyze_pragma_split([id(F),')'|T],[F],T):-
   !.

@atom_analyze_pragma_split([id(F),','|R],[F|T],Rest):-
   atom_analyze_pragma_split(R,T,Rest),
   !.

@atom_analyze_privates(Params,Privates,REST):-
   append(Left,[id(private),'('|T],Params),
   append(L,[')'|Right],T),
   !,
   append(L,[')'],L1),
   atom_get_comma_list(L1,Privates),
   append(Left,Right,REST),
   !.

@atom_analyze_privates(L,[],L):-
   !.

@atom_analyze_param(Params,ID,Out,_,OParams):-
   append(L0,[id(ID),'('|T],Params),
   append(L,[')'|L1],T),
   !,
   append(L0,L1,OParams),
   !,
   append(L,[')'],L2),
   atom_get_comma_list(L2,Out),
   !.

@atom_analyze_param(Params,_,Def,Def,Params):-
   !.

@atom_insert_splitteds([],_,[]):-
   !.

@atom_insert_splitteds([gid(C1,PrevGID),gid(C2,LoopGID),gid(C3,BodyGID)|RIGHT],NewGID,[gid(C1,PrevGID),gid('clsPreproc',NewGID),gid(C2,LoopGID)|RIGHT1]):-
   db_content('prog',PrevGID,[[PrevType]]),
   \+ member(PrevType,['preproc','do','while','for']),
   db_content('prog',LoopGID,[[LType]]),
   member(LType,['do','for','while']),
   db_content('prog',BodyGID,[['{']]),
   asserta(db_content('prog',NewGID,[['preproc']])),
   asserta(db_content('args',NewGID,[['body','#pragma auto split(auto) tol(0.01) degree(2)']])),
   asserta(atomic_auto(LoopGID)),
   NextGID is NewGID-1,
   atom_insert_splitteds([gid(C3,BodyGID)|RIGHT],NextGID,RIGHT1),
   !.

@atom_insert_splitteds([H|T],NewGID,[H|T1]):-
   atom_insert_splitteds(T,NewGID,T1),
   !.

% Очистка + Загрузка необходимых данных перед анализом
@atom_prepare_atomic:-
   retractall(atomic_function(_,_,_)),
   retractall(atomic_fdependent(_,_,_)),
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
   !,
   (
    (db_content('prog',GID3,[['preproc']]),
     db_content('args',GID3,[[body,S3]]),
     once(atom_parse_expr(S3,['#',id('pragma'),id('auto'),id('parallelize')])),
     once(global_trace(GT)),
     once(atom_insert_splitteds(GT,-10,GT1)),
     append(LEFT1,[gid(_,GID3)|RIGHT1],GT1),
     append(LEFT1,RIGHT1,GT2),
     once(retractall(global_trace(_))),
     once(asserta(global_trace(GT2))),
     fail);
     true
   ),
   !,
   atom_prepare_atomic_functions,
   !,
   atom_find_globals,
   !,
   atom_build_atomic_functions,
   !,
   atom_analyze_atomic_functions,
   !,
   atom_iterative_build_funs,
   !,
   atom_find_dependents,
   !,
   (
    (db_content('prog',GID2,[['preproc']]),
     db_content('args',GID2,[[body,S2]]),
     once(atom_parse_expr(S2,['#',id('pragma'),id('auto'),id('split'),'('|R2])),
     once(atom_get_next_op(GID2,GIDK)),
     once(atom_analyze_pragma_split(R2,L2,R3)),
     once(atom_analyze_privates(R3,Privates,R4)),
     once(atom_analyze_param(R4,'tol',Tol,[0.01],R5)),
     once(atom_analyze_param(R5,'degree',Degree,[2],R6)),
     once(atom_into_atom(R6,' ',A5)),
     asserta(atomic_splitted(GIDK,params(L2,Privates,Tol,Degree,A5))),
     fail);
     true
   ),
   !.

@atom_find_lvar(V,[Globals],global(V,TP)):-
   member(global(V,TP),Globals),
   !.

@atom_find_lvar(V,[TopVars|_],loc(TopGID,V,TP)):-
   member(loc(TopGID,V,TP),TopVars),
   !.

@atom_find_lvar(V,[_|RestVars],V1):-
   atom_find_lvar(V,RestVars,V1),
   !.

@atom_find_lvars([],_,[]):-!.

@atom_find_lvars([global(V,TP)|T],Vars,[global(V,TP)|T1]):-
   atom_find_lvars(T,Vars,T1),
   !.

@atom_find_lvars([par(_,_,V)|T],Vars,[V1|T1]):-
   atom_find_lvar(V,Vars,V1),
   atom_find_lvars(T,Vars,T1),
   !.

@atom_find_lvars([V|T],Vars,[V1|T1]):-
   atom_find_lvar(V,Vars,V1),
   atom_find_lvars(T,Vars,T1),
   !.

@atom_find_lvars([V|T],Vars,T1):-
   \+ atom_find_lvar(V,Vars,_),
   atom_find_lvars(T,Vars,T1),
   !.

@atom_loc_prefixate(_,[],[]):-!.

@atom_loc_prefixate(TopGID,[var(V,TP)|T],[loc(TopGID,V,TP)|T1]):-
   atom_loc_prefixate(TopGID,T,T1),
   !.

@atom_analyze_fpdeps_list([],t):-
   !.

@atom_analyze_fpdeps_list([H|_],f):-
   =..(H,[_,Name,LPrms]),
   length(LPrms,L),
   (
    atomic_function(Name,_,L)->
      atomic_fdependent(Name,L,t);
      \+ (predicate_property(cilk_fpure(_),'dynamic'), cilk_fpure(Name))
   ),
   !.

@atom_analyze_fpdeps_list([_|T],Allow):-
   atom_analyze_fpdeps_list(T,Allow),
   !.

@atom_analyze_fpdeps(Funs,Procs,Allow):-
   append(Funs,Procs,FP),
   atom_analyze_fpdeps_list(FP,Allow),
   !.

@atom_getNewInOutRefLazies(_,_,[],[],[],[],[],[],0.0,t):-!.

@atom_getNewInOutRefLazies(TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM,Allow):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,Procs0,Ref0,Laz0,_]),
   atom_analyze_fpdeps(Funs0,Procs0,Allow0),
   atom_find_lvars(Ins0,Vars,InsP),
   atom_find_lvars(Outs0,Vars,OutsP),
   atom_find_lvars(Ref0,Vars,RefsP),
   atom_find_lvars(Laz0,Vars,LazP),
   atom_loc_prefixate(TopGID,News0,NewsP),
   !,
   atom_getTime(Funs0,T0),
   atom_getNewInOutRefLazies(TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1,Allow1),
   !,
   (
     (=(Allow0,f);=(Allow1,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
   append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
   atom_unique(News2,News), atom_unique(Ins2,Ins), atom_unique(Laz2,Lazies),
   append(Outs2,News,Outs3), atom_unique(Outs3,Outs), atom_unique(Ref2,Refs),
   TM is T0+T1,
   !.

@atom_getForNewInOutRefLazies(_,_,_,[],[],[],[],[],[],0.0,t):-!.

@atom_getForNewInOutRefLazies(Types,TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM,Allow):-
   =..(V,[Type,Ins0,Outs0,News0,Funs0,Procs0,Ref0,Laz0,_]),
   atom_analyze_fpdeps(Funs0,Procs0,Allow0),
   (
    member(Type,Types)->(
      !,
      atom_find_lvars(Ins0,Vars,InsP),
      atom_find_lvars(Outs0,Vars,OutsP),
      atom_find_lvars(Ref0,Vars,RefsP),
      atom_find_lvars(Laz0,Vars,LazP),
      atom_loc_prefixate(TopGID,News0,NewsP),
      !,
      atom_getTime(Funs0,T0),
      atom_getForNewInOutRefLazies(Types,TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1,Allow1),
      !,
      append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
      append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
      atom_unique(News2,News), atom_unique(Ins2,Ins), atom_unique(Laz2,Lazies),
      atom_unique(Outs2,Outs), atom_unique(Ref2,Refs),
      TM is T0+T1
    );(
      atom_getForNewInOutRefLazies(Types,TopGID,Vars,T,News,Ins,Outs,Refs,Lazies,TM,Allow1)
    )
   ),
   (
     (=(Allow0,f);=(Allow1,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   !.

@atom_register_splitted_time(GID,TTP,TTN,TT1):-
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
@atom_traverse_alters([op(CurGID,Time,Ins2,Outs2,Allow)], [CurGID|GIDs], [TopGID|StackGIDs], [switch(TopGID,Pass)|StackConstrs], StackConstrs, Vars, Time, NAlt):-
   atomic_op('clsAlternation',CurGID,_,[],_),
   (
    (append(ALT,[NextGID|_],GIDs),atomic_op('clsOper',NextGID,_,[],_),db_content('args',NextGID,[['op','break']]),!)->
       (
        !,
        atom_traverse_fun(t,Splitted1, ALT,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T1),
        !
       );
       (
        atom_traverse_fun(t,Splitted1, GIDs,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T1),
        !
       )
   ),
   atom_collecting(Splitted1, [], [], Ins1, Outs1, Allow1),
   retractall(atomic_break(_)),
   (
    (append(_,[NextGID1|Rest1],GIDs),atomic_op('clsAlternation',NextGID1,_,[],_))->(
       !,
       atom_traverse_alters(Splitted2, [NextGID1|Rest1],[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T2,NAlt1),
       Time is T1+T2,
       NAlt is NAlt1+1,
       !,
       atom_collecting(Splitted2, Ins1, Outs1, Ins2, Outs2, Allow2),
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

@atom_traverse_alters([], [], [TopGID|_], [switch(TopGID,_)|CRest], CRest, _, 0.0, 0):-!.

@atom_exclude_locs(_, [], []):-
   !.

@atom_exclude_locs(GID, [loc(GID,_,_)|T], T1):-
   atom_exclude_locs(GID, T, T1),
   !.

@atom_exclude_locs(GID, [H|T], [H|T1]):-
   atom_exclude_locs(GID, T, T1),
   !.

@atom_collecting([], Ins, Outs, Ins, Outs, t):-
   !.

@atom_collecting([op(GID,_,I,O,Allow1)|T],Ins,Outs,Ins3,Outs3,Allow):-
   atom_collecting(T,Ins,Outs,Ins1,Outs1,Allow2),
   atom_exclude_locs(GID,Ins1,Ins2),
   atom_exclude_locs(GID,Outs1,Outs2),
   atom_union(I,Ins2,Ins3),
   atom_union(O,Outs2,Outs3),
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   !.

@atom_purge_owns([],_,[]):-
   !.

@atom_purge_owns([loc(CurGID,_,_)|T],CurGID,T1):-
   atom_purge_owns(T,CurGID,T1),
   !.

@atom_purge_owns([H|T],CurGID,[H|T1]):-
   atom_purge_owns(T,CurGID,T1),
   !.

@atom_check_split(CurGID,1000000.0):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopID,_,CurGID,_,_),
   predicate_property(atomic_splitted(_,_),'dynamic'),
   atomic_splitted(LoopID,_),
   !.

@atom_check_split(_,1.0):-
   !.

@atom_exclude_vars([],_,[]):-
   !.

@atom_exclude_vars([loc(_,V,_)|T],Vars,T1):-
   member(V,Vars),
   !,
   atom_exclude_vars(T,Vars,T1),
   !.

@atom_exclude_vars([global(V,_)|T],Vars,T1):-
   member(V,Vars),
   !,
   atom_exclude_vars(T,Vars,T1),
   !.

@atom_exclude_vars([H|T],Vars,[H|T1]):-
   atom_exclude_vars(T,Vars,T1),
   !.

@atom_exclude_canals([],[auto],[],[]):-
   !.

@atom_exclude_canals([],Canals,Canals,[]):-
   !.

@atom_exclude_canals([loc(_,V,Type)|T],[auto],[V|T1],[]):-
   \+ member('*', Type), \+ member('&', Type),
   atom_exclude_canals(T,[auto],T1,[]),
   !.

@atom_exclude_canals([global(V,Type)|T],[auto],[V|T1],[]):-
   \+ member('*', Type), \+ member('&', Type),
   atom_exclude_canals(T,[auto],T1,[]),
   !.

@atom_exclude_canals(_,[auto|_],[],[error]):-
   !.

@atom_exclude_canals([loc(_,V,Type)|T],Canals,Canals,T1):-
   \+ member('*', Type), \+ member('&', Type),
   member(V,Canals),
   !,
   atom_exclude_canals(T,Canals,Canals,T1),
   !.

@atom_exclude_canals([global(V,Type)|T],Canals,Canals,T1):-
   \+ member('*', Type), \+ member('&', Type),
   member(V,Canals),
   !,
   atom_exclude_canals(T,Canals,Canals,T1),
   !.

@atom_exclude_canals([H|T],Canals,Canals,[H|T1]):-
   atom_exclude_canals(T,Canals,Canals,T1),
   !.

@atom_purge_trace([],_,[]):-
   !.

@atom_purge_trace([op(GID,Time,Ins,Outs,Allow)|T],Privates,[op(GID,Time,Ins1,Outs1,Allow)|T1]):-
   atom_exclude_vars(Ins,Privates,Ins1),
   atom_exclude_vars(Outs,Privates,Outs1),
   atom_purge_trace(T,Privates,T1),
   !.

@atom_get_best([],_,_,_,_,_):-
   !, fail.

@atom_get_best([variant(St,G,Fin,Tm,CDecls)],St,G,Fin,Tm,CDecls):-
   !.

@atom_get_best([variant(St,G,Fin,Tm,CDecls)|T],StartGID,GID,FinGID,Time,CDECLS):-
   atom_get_best(T,St1,G1,Fin1,Tm1,CDecls1),
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

@atom_analyze_part([],[],[],0.0):-
   !.

@atom_analyze_part([op(_,Tm,I,O,_)|T],Ins,Outs,T1):-
   atom_analyze_part(T,Ins1,Outs1,T2),
   atom_union(I,Ins1,Ins),
   atom_union(O,Outs1,Outs),
   T1 is T2+Tm,
   !.

@atom_indexes_split([], []):-
   !.

@atom_indexes_split(L, [IDX|T]):-
   append(['['|IDXS],[']','['|Next],L),
   !,
   atom_into_atom(IDXS,'',IDX),
   atom_indexes_split(['['|Next],T),
   !.

@atom_indexes_split(L, [IDX]):-
   append(['['|IDXS],[']'],L),
   !,
   atom_into_atom(IDXS,'',IDX),
   !.

@atom_find_decl(V,Vars,var(V,Type,Idxs)):-
   member(global(V,type(TypeSEQ,IdxSEQ)),Vars),
   atom_indexes_split(IdxSEQ,Idxs),
   atom_into_atom(TypeSEQ,' ',Type),
   !.

@atom_find_decl(V,Vars,var(V,Type,Idxs)):-
   member(loc(_,V,type(TypeSEQ,IdxSEQ)),Vars),
   atom_indexes_split(IdxSEQ,Idxs),
   atom_into_atom(TypeSEQ,' ',Type),
   !.

@atom_get_canal_decls([],_,[]):-
   !.

@atom_get_canal_decls([C|T],Vars,[CDecl|T1]):-
   atom_find_decl(C,Vars,CDecl),
   atom_get_canal_decls(T,Vars,T1),
   !.

@atom_belongs(op(GID,_,_,_,_),LoopGID):-
   atomic_op(_,LoopGID,_,LGIDs,_),
   member(GID,LGIDs),
   !.
   
@atom_belongs(op(GID,_,_,_,_),LoopGID):-
   atomic_op('clsBegin',UpperGID,_,LGIDs,_),
   member(GID,LGIDs),
   !,
   atomic_op(_,LoopGID,_,LGIDs2,_),
   member(UpperGID,LGIDs2),
   !.

@atom_delete_splitted_gids([],_,[]):-
   !.

@atom_delete_splitted_gids([op(GID,_,_,_,_)|T],GID,T1):-
   atom_delete_splitted_gids(T,GID,T1),
   !.
   
@atom_delete_splitted_gids([op(GID,A,B,C,D)|T],GID1,[op(GID,A,B,C,D)|T1]):-
   atom_delete_splitted_gids(T,GID1,T1),
   !.
   
@atom_find_start([],[],GID,GID):-
   !.

@atom_find_start(Splitted11,Splitted1,FirstGID0,FirstGID):-
   atomic_op('clsOper',FirstGID0,_,_,[arg(_,_,News,_,_,_,_,_)]),
   \+ =(News,[]),
   global_trace(TR),
   append(_,[gid(_,FirstGID0),gid(_,FirstGID1)|_],TR),
   atom_delete_splitted_gids(Splitted11,FirstGID0,Splitted12),
   atom_find_start(Splitted12,Splitted1,FirstGID1,FirstGID),
   !.

@atom_find_start(Splitted1,Splitted1,FirstGID0,FirstGID0):-
   !.

@atom_generate_variants(_,_,_,[],[]):-
   !.

@atom_generate_variants(LoopGID,Canals,First,[H|Last1],V):-
   append(First,[H],First1),
   !,
   atom_generate_variants(LoopGID,Canals,First1,Last1,V0),
   !,
   atom_analyze_part(First,Ins1,Outs1,T1),
   atom_analyze_part([H|Last1],Ins2,Outs2,T2),
   atom_intersect(Outs1,Ins2,P1),
   atom_exclude_canals(P1, Canals, FoundCanals, P11),
   atom_intersect(Outs2,Ins1,P2),
   (
     (
      (append(_,[op(PrevGID,_,_,_,_)],First), =(P11,[]), =(P2,[]), \+ atomic_op('clsPreproc',PrevGID,_,_,_), atom_belongs(H,LoopGID))->
        (Time is max(T1,T2), =(H,op(GID,_,_,_,_)), atom_get_canal_decls(FoundCanals,P1,CDS), =(V,[variant(-1,GID,-1,Time,CDS)|V0]));
        =(V,V0)
     )
   ),
   !.

@atom_try_split(_,_,[],_,_,_):-
   !, fail.

@atom_try_split(_,_,[_],_,_,_):-
   !, fail.

@atom_try_split(LoopGID,Canals,[H|T],GID,Time,CDecls):-
   atom_generate_variants(LoopGID,Canals,[H],T,V),
   !,
   atom_get_best(V,_,GID,_,Time,CDecls).

@atom_try_forwards(_,_,_,_,[],V,V):-
   !.

@atom_try_forwards(LoopGID,Canals,BaseTime,FinGID,[op(PrevGID,Time,_,_,_)|T],Vars0,Vars1):-
   ThisTime is BaseTime+Time,
   atom_try_forwards(LoopGID,Canals,ThisTime,FinGID,T,Vars0,V0),
   !,
   (
    (\+ atomic_op('clsPreproc',PrevGID,_,_,_), atom_try_split(LoopGID,Canals,T,GID,TS,CDS), =(T,[H|_]), atom_belongs(H,LoopGID))->
      (Time1 is ThisTime+TS, =(T,[op(StartGID,_,_,_,_)|_]), =(Vars1,[variant(StartGID,GID,FinGID,Time1,CDS)|V0]));
      (=(Vars1,V0))
   ),
   !.

@atom_try_backwards(_,_,_,_,[],V,V):-
   !.

@atom_try_backwards(LoopGID,Canals,BaseTime,StartGID,L,Vars0,Vars1):-
   append(T,[op(FinGID,Time,_,_,_)], L),
   ThisTime is BaseTime+Time,
   atom_try_backwards(LoopGID,Canals,ThisTime,StartGID,T,Vars0,V0),
   !,
   (
    (
     (append(_,[op(PrevGID,_,_,_,_)],T), \+ atomic_op('clsPreproc',PrevGID,_,_,_), atom_try_split(LoopGID,Canals,T,GID,TS,CDS),
      =(T,[H|_]), atom_belongs(H,LoopGID))->
       (Time1 is ThisTime+TS, =(Vars1,[variant(StartGID,GID,FinGID,Time1,CDS)|V0]));
       (=(Vars1,V0))
    )
   ),
   !.

@atom_create_split(CurGID,VarCanals,Privates,Splitted):-
   (member(op(_,_,_,_,f),Splitted), predicate_property(atomic_auto(_),'dynamic'), atomic_auto(CurGID))->
     ( retractall(atomic_split(CurGID,_,_,_,_)),! );
     (
       atom_purge_trace(Splitted,Privates,Splitted0),
       append(Splitted11,[op(0,-1,[],[],t)|_],Splitted0),
       !,
       global_trace(GT),
       append(_,[gid(_,CurGID),gid(_,_),gid(_,FirstGID0)|_],GT),
       atom_find_start(Splitted11,Splitted1,FirstGID0,FirstGID),
       !,
       append(_,[gid(C,CurGID)|Right],GT),
       !,
       atom_bypass_op([gid(C,CurGID)|Right],Loop,_),
       (
         =(C,'clsDo')->
          append(_,[gid(_,AfterLastGID),gid('clsWhile',_),gid('clsOper',_)],Loop);
          append(_,[gid(_,AfterLastGID)],Loop)
       ),
       !,
       (
          (atom_try_split(CurGID,VarCanals,Splitted1,GID0,Time0,CDS)->
            (
             =(V0,[variant(FirstGID,GID0,AfterLastGID,Time0,CDS)])
            );
             =(V0,[])
          ),
          (
           atom_try_forwards(CurGID,VarCanals,0.0,AfterLastGID,Splitted1,V0,V1),
           atom_try_backwards(CurGID,VarCanals,0.0,FirstGID,Splitted1,V1,V2),
           !,
           (
            atom_get_best(V2,StartGID,GID,FinGID,_,CDecls)->
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

@atom_find_split_privates_one([], []):-
   !.

@atom_find_split_privates_one([global(V,type([id(split_private)|_],_))|T], [V|T1]):-
   atom_find_split_privates_one(T, T1),
   !.

@atom_find_split_privates_one([loc(_,V,type([id(split_private)|_],_))|T], [V|T1]):-
   atom_find_split_privates_one(T, T1),
   !.

@atom_find_split_privates_one([_|T], T1):-
   atom_find_split_privates_one(T, T1),
   !.

@atom_find_split_privates([], []):-
   !.

@atom_find_split_privates([VARS|T], Privates):-
   atom_find_split_privates_one(VARS, P0),
   atom_find_split_privates(T, P1),
   atom_union(P0, P1, Privates),
   !.

@atom_concat_privates([], ''):-
   !.

@atom_concat_privates([V], V):-
   !.

@atom_concat_privates([V1,V2|T], S):-
   atom_concat_privates([V2|T], S1),
   atom_concat(V1,',',S2),
   atom_concat(S2,S1,S),
   !.

@atom_analyze_splitted(CurGID,Vars):-
   atomic_splitted(CurGID,params(Canals,OldPrivates,Tol,Degree,RestParams)),
   !,
   atom_find_split_privates(Vars,Privates),
   length(OldPrivates,OLD),
   length(Privates,NEW),
   !,
   (
     >(NEW,OLD)->
       (retractall(atomic_splitted(CurGID,_)), asserta(atomic_splitted(CurGID,params(Canals,Privates,Tol,Degree,RestParams))));
       true
   ),
   !.

@atom_analyze_splitted(_,_):-
   !.

% Окончание while
@atom_traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [while(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsWhile',TopGID,_,[_],Ops),
   !,
   atom_getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
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
          atomic_op('clsWhile',TopGID,_,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          atom_traverse_fun(SMode,Splitted1, [IGID1],[TopGID|StackGIDs],[while(TopGID,2)|StackConstrs],_,[LVars|Vars],T11),
          (
           <(T11,1000000.0)->
             (atom_put_ltime(TopGID,T11), T1 is T11);
             (
              T01 is round(T11/1000000),
              T02 is round(T11-T01*1000000.0),
              T1N is T01+T02,
              T1P is max(T01,T02),
              atom_register_splitted_time(TopGID,T1P,T1N,T1)
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
@atom_traverse_fun(_, [], [CurGID|_], StackGIDs, [Top|StackConstrs], StackConstrs, Vars, Time):-
   atomic_op('clsOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','break']]),
   !,
   atom_check_split(CurGID,K),
   asserta(atomic_break(CurGID)),
   =..(Top,[_,TopGID,_]),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(vr(VAR0)), once(tm(T0)),
     atom_traverse_fun(t, _, [],[CurTopGID|Rest],[Top|StackConstrs],_,VAR0,TT),
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
@atom_traverse_fun(_, [], [CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','continue']]),
   !,
   atom_check_split(CurGID,K),
   asserta(atomic_continue(CurGID)),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)),
     atom_traverse_fun(t, _, [],[CurTopGID|Rest],ST0,ST1,VAR0,TT),
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
@atom_traverse_fun(_, [], [CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsReturn',CurGID,_,[],_),
   !,
   atom_check_split(CurGID,K),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)),
     atom_traverse_fun(t, _, [],[CurTopGID|Rest],ST0,ST1,VAR0,TT),
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
@atom_traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [do(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsDo',TopGID,LastGID,[_],Ops),
   !,
   atom_getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
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
          atomic_op('clsDo',TopGID,LastGID,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          atom_traverse_fun(SMode, Splitted1, [IGID1],[TopGID|StackGIDs],[do(TopGID,2)|StackConstrs],_,[LVars|Vars],T22),
          (
           <(T22,1000000.0)->
             (atom_put_ltime(TopGID,T22), T2 is T22);
             (
              T01 is round(T22/1000000),
              T02 is round(T22-T01*1000000.0),
              T2N is T01+T02,
              T2P is max(T01,T02),
              atom_register_splitted_time(TopGID,T2P,T2N,T2)
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
@atom_traverse_fun(_, OSplitted, [], [TopGID|StackGIDs], [for(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Time):-
   atomic_op('clsFor',TopGID,_,[_],Ops),
   !,
   atom_getForNewInOutRefLazies(['cond','chng'],TopGID,[LVars|Vars],Ops,_,_,_,_,_,BaseTime,_),
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
          atomic_op('clsFor',TopGID,_,[IGID1],_),
          !,
          (
            (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(TopGID,_))->
              (=(SMode,f));
              (=(SMode,t))
          ),
          atom_traverse_fun(SMode, Splitted1, [IGID1],[TopGID|StackGIDs],[for(TopGID,2)|StackConstrs],_,[LVars|Vars],T22),
          (
           <(T22,1000000.0)->
             (atom_put_ltime(TopGID,T22), T2 is T22);
             (
              T01 is round(T22/1000000),
              T02 is round(T22-T01*1000000.0),
              T2N is T01+T02,
              T2P is max(T01,T02),
              atom_register_splitted_time(TopGID,T2P,T2N,T2)
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
@atom_traverse_fun(_, [], [], [TopGID|_], StackConstrs, StackConstrs, _, 0.0):-
   atomic_op('clsBegin',TopGID,_,_,_),
   !,
   (
     true
   ),
   !.

% Окончание функции
@atom_traverse_fun(_, [], [], [-1], StackConstrs, StackConstrs, _, 0.0):-
   !.

% Окончание произвольного (не{}) оператора. Может вызываться в операторе окончания различных конструктов
@atom_traverse_fun(_, [], [], [TopGID|_], StackConstrs, StackConstrs, _, 0.0):-
   \+ atomic_op('clsBegin',TopGID,_,_,_),
   !,
   (
     true
   ),
   !.

% Полный if-else, IGIDs = [IfGID,EGID]. Краткий if -- обрабатывается обычным образом, IGIDs = [IfGID]
@atom_traverse_fun(Mode, [op(CurGID,OTime,Ins2,Outs2,Allow)|Splitted3], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsIf',CurGID,_,[IfGID,EGID],Ops),
   !,
   atom_check_split(CurGID,K),
   atom_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   atom_traverse_fun(t, Splitted1,[IfGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T20),
   atom_traverse_fun(t, Splitted2,[EGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T21),
   !,
   atom_collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
   atom_collecting(Splitted2, Ins1, Outs1, Ins2, Outs2, Allow3),
   !,
   (
     OTime is BaseTime+0.5*(T20+T21)
   ),
   atom_traverse_fun(Mode, Splitted3, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f);=(Allow3,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(BaseTime+0.5*(T20+T21)+T3),
   !.

% Полный while
@atom_traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsWhile',CurGID,_,[IGID],Ops),
   !,
   atom_check_split(CurGID,K),
   atom_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   atom_traverse_fun(SMode, Splitted1,[IGID],[CurGID,TopGID|StackGIDs],[while(CurGID,1)|StackConstrs],_,[News|Vars],T2),
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
     atom_analyze_splitted(CurGID,Vars),
     atom_collecting(Splitted1, Ins, Outs, Ins0, Outs1, Allow2),
     atom_purge_owns(Ins0,CurGID,Ins1)
   ),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             atom_create_split(CurGID,Canals,Privates,Splitted1)
         )
       );
       (true)
   ),
   atom_traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(BaseTime+T3+CheckedTime),
   !.

% Полный for
@atom_traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsFor',CurGID,_,[IGID],Ops),
   !,
   atom_check_split(CurGID,K),
   atom_getForNewInOutRefLazies(['init','cond'],CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   atom_traverse_fun(SMode, Splitted1,[IGID],[CurGID,TopGID|StackGIDs],[for(CurGID,1)|StackConstrs],_,[News|Vars],T2),
   !,
   atom_analyze_splitted(CurGID,Vars),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             atom_create_split(CurGID,Canals,Privates,Splitted1)
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
      atom_collecting(Splitted1, Ins, Outs, Ins0, Outs1, Allow2),
      atom_purge_owns(Ins0,CurGID,Ins1)
   ),
   !,
   atom_traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T3),
   !,
   (
     (=(Allow1,f);=(Allow2,f))->
       =(Allow,f);
       =(Allow,t)
   ),
   Time is K*(T3+BaseTime+CheckedTime),
   !.

% Полный do-while
@atom_traverse_fun(Mode, [op(CurGID,CheckedTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsDo',CurGID,_,[IGID],_),
   !,
   atom_check_split(CurGID,K),
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,_))->
       (=(SMode,f));
       (=(SMode,t))
   ),
   atom_traverse_fun(SMode, Splitted1, [IGID],[CurGID,TopGID|StackGIDs],[do(CurGID,1)|StackConstrs],_,[[]|Vars],T1),
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
   atom_analyze_splitted(CurGID,Vars),
   atom_collecting(Splitted1, [], [], Ins0, Outs1, Allow),
   atom_purge_owns(Ins0,CurGID,Ins1),
   !,
   (
     (predicate_property(atomic_splitted(_,_),'dynamic'),atomic_splitted(CurGID,params(Canals,Privates,_,_,_)))->
       (
         (
           (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(CurGID,_,_,_,_))->
             true;
             atom_create_split(CurGID,Canals,Privates,Splitted1)
         )
       );
       (true)
   ),
   atom_traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T2),
   !,
   Time is K*(CheckedTime+T2),
   !.

% switch
@atom_traverse_fun(Mode, [op(CurGID,OTime,Ins1,Outs1,Allow)|Splitted2], [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atomic_op('clsSwitch',CurGID,_,[IGID],Ops),
   atomic_op('clsBegin',IGID,_,IGIDs,_),
   !,
   atom_check_split(CurGID,K),
   atom_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
   !,
   atom_traverse_alters(Splitted1, IGIDs,[CurGID,TopGID|StackGIDs],[switch(CurGID,1)|StackConstrs],_,[News|Vars],TNN,NAlt),
   !,
   atom_collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
   !,
   (
     =(NAlt,0)->
       OTime is BaseTime;
       OTime is BaseTime+TNN/NAlt
   ),
   !,
   atom_traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,T2),
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

@atom_traverse_fun(Mode, OSplitted, [CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Time):-
   atom_check_split(CurGID,K),
   (
    (predicate_property(atomic_break(_),'dynamic'), atomic_break(_))->(
       atom_traverse_fun(Mode, OSplitted, [], [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Time1),
       Time is Time1*K,
       !
    );(
       atomic_op(_,CurGID,_,IGIDs,Ops),
       !,
       atom_getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime,Allow1),
       (
        ( % Если это запуск процедуры, то прибавляем время ее исполнения
          atomic_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)])->
            (atom_getTime([proc(Fun,Prms)],TSP1), g_read('$DefOperTime',TOp0), TSP is TSP1-TOp0);
            =(TSP,0.0)
        )
       ),
       atom_addLocals(Vars,News,Vars1),
       !,
       atom_traverse_fun(t, Splitted1, IGIDs,[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],T2),
       !,
       atom_traverse_fun(Mode, Splitted2, GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars1,T3),
       !,
       (=(Mode,t)->
         (
            OTime is TSP+BaseTime+T2,
            atom_collecting(Splitted1, Ins, Outs, Ins1, Outs1, Allow2),
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

@atom_create_splits(Fun,GID,NPrms):-
   retractall(atomic_break(_)),
   retractall(atomic_continue(_)),
   atomic_globals(GLOB),
   atom_glob_prefixate(GLOB,G1),
   atom_get_fparams(all,Fun,NPrms,PARMS),
   atom_loc_prefixate(GID,PARMS,P1),
   atom_traverse_fun(f, _, [GID],[-1],[],_,[P1,G1],Time),
   atom_put_ftime(Fun,NPrms,Time),
   !.

@atom_bypass_sequence([],[],[]):-!.

@atom_bypass_sequence([gid('clsEnd',GID)|T],[],[gid('clsEnd',GID)|T]):-
   !.

@atom_bypass_sequence([gid('clsBegin',GID)|T],TT,T3):-
   atom_bypass_complex([gid('clsBegin',GID)|T],T0,T1),
   atom_bypass_sequence(T1,T2,T3),
   append(T0,T2,TT),
   !.

@atom_bypass_sequence([H|T],[H|T1],T2):-
   atom_bypass_sequence(T,T1,T2),
   !.

@atom_bypass_complex([gid('clsBegin',GID)|T],[gid('clsBegin',GID)|T1],T2):-
   atom_bypass_sequence(T,T0,[gid('clsEnd',GID2)|T2]),
   append(T0,[gid('clsEnd',GID2)],T1).

@atom_bypass_op([A|T],[A|BeforeWith],After):-
   member(A,[gid('clsFor',_),gid('clsSwitch',_),gid('clsWhile',_)]),
   !,
   atom_bypass_op(T,BeforeWith,After),
   !.

@atom_bypass_op([gid('clsDo',GID)|T],[gid('clsDo',GID)|T1],T2):-
   atom_bypass_op(T,BeforeWhile,[gid('clsWhile',GIDW),gid('clsOper',EMPTY)|T2]),
   append(BeforeWhile,[gid('clsWhile',GIDW),gid('clsOper',EMPTY)],T1),
   !.

@atom_bypass_op([gid('clsIf',GID)|T],[gid('clsIf',GID)|T1],T2):-
   atom_bypass_op(T,BeforeWith,[A|AfterT]),
   (
    =(gid('clsElse',_),A)->(
      atom_bypass_op(AfterT,BeforeWith2,T2),
      append(BeforeWith,[A|BeforeWith2],T1),
      !
    );(
      =(T1,BeforeWith),=(T2,[A|AfterT]),!
    )
   ),
   !.

@atom_bypass_op([gid('clsBegin',GID)|T],T1,T2):-
   atom_bypass_complex([gid('clsBegin',GID)|T],T1,T2),
   !.

@atom_bypass_op([A|T],[A],T):-!.

@atom_insert_ending_bracket(L1,L2):-
   atom_bypass_op(L1,BeforeWith,After),
   !,
   append(BeforeWith,[gid('clsEnd',-1)|After],L2),
   !.

@atom_create_all_splits:-
  predicate_property(atomic_function(_,_,_),'dynamic'),
  atomic_function(Fun,GID,NPrms),
  once(atom_create_splits(Fun,GID,NPrms)),
  atom_get_ftime(Fun,NPrms,_), % Time
%  write(Fun),write(':'),write(Time),nl,
  fail.

@atom_create_all_splits:-
%  write('--------------'), nl,
  !.

@atom_iterative_splits_times(0):-!.

% Итерационный алгоритм последовательного добавления splits и пересчета времен исполнения функций. Алгоритм заканчивается, когда
% времена исполнения практически перестают меняться (+/-1) или превышено число итераций N
@atom_iterative_splits_times(N):-
  retractall(atomic_retime),
  retractall(atomic_splitted_time(_,_)),
  atom_create_all_splits,
  predicate_property(atomic_retime,'dynamic'),
  atomic_retime,
  !,
  N1 is N-1,
  atom_iterative_splits_times(N1).

@atom_iterative_splits_times(_):-!.

@atom_sum([],0.0):-!.

@atom_sum([H|T],S):-
  atom_sum(T,S0),
  S is S0+H,
  !.

@atom_avr([],0.0):-!.

@atom_avr(L,atom_Avr):-
  atom_sum(L,S),
  length(L,N),
  atom_Avr is S/N.

% Определяем неэффективные splitted-запуски
@atom_remove_splitteds:-
  predicate_property(atomic_splitted(_,_),'dynamic'),
  atomic_splitted(GID,_),
  predicate_property(atomic_ltime(_,_),'dynamic'),
  atomic_ltime(GID,BaseTime),
  predicate_property(atomic_splitted_time(_,_),'dynamic'),
  atomic_splitted_time(GID,Timings),
  call(atom_avr(Timings,AvrTime)),
  g_read('$SplittedTime', SplittedTime),
  ParExecTime is AvrTime+SplittedTime, % С учетом расходов на собственно splitted
  ( % Принятие решения об исключении splitted
    >(ParExecTime,BaseTime)->(
      once(atomic_resplitteds(List)),
      retractall(atomic_resplitteds(_)),
      asserta(atomic_resplitteds([GID|List]))
    ); % Теперь сравним с возможным распараллеливанием cilk_for
    ( (predicate_property(cilk_for(_),'dynamic'), cilk_for(GID))->
        (
         (predicate_property(cilk_for_time(_,_),'dynamic'), cilk_for_time(GID,CILKT))->
           (
            g_read('$SpawnTime',TSP), g_read('$SyncTime',TSY),
            TPARCILK is (CILKT + 3*(TSP + TSY)), % 2^3 = 8 (бинарное дерево ветвления)
            TPARSPLITTED is 8*AvrTime+SplittedTime, % С учетом расходов на собственно splitted
            ( <(TPARCILK, TPARSPLITTED)->
                (
                  once(atomic_resplitteds(List)),
                  retractall(atomic_resplitteds(_)),
                  asserta(atomic_resplitteds([GID|List]))
                );
                retractall(cilk_for(GID))
            )
           );
           true
        );
        true
    )
  ),
  fail.

@atom_remove_splitteds:-!.

@atom_clear_ltimes_upper_loops(GID):-
   atomic_op(_,UpperGID,_,LGIDs,_),
   member(GID,LGIDs),
   !,
   (
      (retractall(atomic_ltime(UpperGID,_)),retractall(atomic_splitted_time(UpperGID,_)))
   ),
   atom_clear_ltimes_upper_loops(UpperGID),
   !.

@atom_clear_ltimes_upper_loops(_):-
   !.

% Удаляем пометки с операторов, GIDы которых прописаны в параметре-списке
@atom_delete_splitteds([]):-!.

@atom_delete_splitteds([H|T]):-
  retractall(atomic_splitted(H,_)),
  retractall(atomic_split(H,_,_,_,_)),
  retractall(atomic_ltime(H,_)),
  retractall(atomic_splitted_time(H,_)),
  !, atom_clear_ltimes_upper_loops(H), !,
  global_trace(GT),
  append(LEFT,[gid(_,PragmaGID),gid(C,H)|RIGHT],GT),
  !,
  (
   db_content('prog',PragmaGID,[['preproc']])->
    (
     append(LEFT,[gid(C,H)|RIGHT],GT1),
     retractall(global_trace(_)),
     asserta(global_trace(GT1)),
     atom_pragma_deleted(PragmaGID,H)
    );
    true
  ),
  atom_delete_splitteds(T),
  !.

@atom_process_splits_and_splitteds(0):-!.

% Главный цикл распараллеливания. Предварительно расставлены все возможные splitteds. Итеративный циклический алгоритм. Завершается,
% когда заканчиваются подлежащие удалению splitteds или превышено число итераций N
@atom_process_splits_and_splitteds(N):-
  atom_iterative_splits_times(15), % Расставляем splits (там, где еще не расставлены) и предсказываем время исполнения функций
  retractall(atomic_resplitteds(_)),
  asserta(atomic_resplitteds([])),
  atom_remove_splitteds, % Определяем список splitteds (в списке-параметре факта atomic_resplitteds([...])), которые дают отрицательный эффект
  % для общего времени работы. Они подлежат удалению
  atomic_resplitteds([First|Rest]), % Если список удаляемых splitteds не пуст
  atom_delete_splitteds([First|Rest]), % Удаляем пометки splitteds для неэффективных случаев
  !,
  N1 is N-1,
  atom_process_splits_and_splitteds(N1).

@atom_process_splits_and_splitteds(_):-!.

@atom_populate(_, 0, []):-
  !.

@atom_populate([V], N, [V|T]):-
  N1 is N-1,
  atom_populate([V], N1, T),
  !.

@atom_populate([V,V1|T], N, [V|T1]):-
  N1 is N-1,
  atom_populate([V1|T], N1, T1),
  !.

@atom_replacer(S,What,To,S1):-
  atom_concat(Left,Right,S),
  atom_concat(What,Rest,Right),
  !,
  atom_concat(Left,To,A1),
  atom_replacer(Rest,What,To,Rest1),
  atom_concat(A1,Rest1,S1),
  !.

@atom_replacer(S,_,_,S):-
  !.  

@atom_collect_dims([],''):-
  !.

@atom_collect_dims([V|T],DIMS):-
  atom_collect_dims(T,DIMS1),
  atom_concat('[',V,A1),
  atom_concat(A1,']',A2),
  atom_concat(A2,DIMS1,DIMS),
  !.

@atom_collect_size([],'1','&'):-
  !.

@atom_collect_size([V],A,''):-
  atom_concat('(',V,V1),
  atom_concat(V1,')',A),
  !.

@atom_collect_size([V1,V2|T],SZ,''):-
  atom_collect_size([V2|T],DIMS1,_),
  atom_concat('(',V1,V11),
  atom_concat(V11,')',A11),
  atom_concat(A11,'*',A1),
  atom_concat(A1,DIMS1,SZ),
  !.

@atom_insert_canal(LoopGID,GID,var(Name,Type,SZ),T,D,NewGID,Template):-
  atom_replacer(Template,'$1',Name,Template1),
  atom_replacer(Template1,'$2',Type,Template2),
  atom_collect_dims(SZ,DIMS),
  atom_concat(Type,' ',A1),
  atom_concat(A1,Name,A2),
  atom_concat(A2,DIMS,A3),
  atom_replacer(Template2,'$3',A3,Template3),
  atom_collect_size(SZ,SIZE,S7),
  atom_replacer(Template3,'$4',SIZE,Template4),
  atom_replacer(Template4,'$5',T,Template5),
  atom_replacer(Template5,'$6',D,Template6),
  atom_replacer(Template6,'$7',S7,Template7),
  atom_replacer(Template7,'$8',LoopGID,STR),
  asserta(db_content('prog',NewGID,[['op']])),
  asserta(db_content('args',NewGID,[['op',STR]])),
  once(global_trace(TR)),
  append(Left,[gid(C,GID)|Right],TR),
  append(Left,[gid(C,GID),gid('clsOper',NewGID)|Right],TR1),
  retractall(global_trace(_)),
  asserta(global_trace(TR1)),
  !.

@atom_insert_canals_internal(_,_,[],[],[],NewGID1,NewGID1,_):-
  !.

@atom_insert_canals_internal(ALoopGID,after(GID),[C|Canals],[T|Tols],[D|Degrees],NewGID1,NewGID2,Template):-
  atom_insert_canal(ALoopGID,GID,C,T,D,NewGID1,Template),
  NewGID3 is NewGID1+1,
  atom_insert_canals_internal(ALoopGID,after(NewGID1),Canals,Tols,Degrees,NewGID3,NewGID2,Template),
  !.

@atom_insert_canals_internal(ALoopGID,before(GID),Canals,Tols,Degrees,NewGID1,NewGID2,Template):-
  global_trace(TR),
  append(_,[gid(_,PrevGID),gid(_,GID)|_],TR),
  atom_insert_canals(ALoopGID,after(PrevGID),Canals,Tols,Degrees,NewGID1,NewGID2,Template),
  !.

@atom_insert_canals(ALoopGID,Dir,Canals,Tols,Degrees,NewGID1,NewGID2,Template):-
  length(Canals, N),
  atom_populate(Tols, N, Tols1),
  atom_populate(Degrees, N, Degrees1),
  atom_insert_canals_internal(ALoopGID,Dir,Canals,Tols1,Degrees1,NewGID1,NewGID2,Template),
  !.

@atom_find_start_only(FirstGID0,FirstGID):-
   atomic_op('clsOper',FirstGID0,_,_,[arg(_,_,News,_,_,_,_,_)]),
   \+ =(News,[]),
   global_trace(TR),
   append(_,[gid(_,FirstGID0),gid(_,FirstGID1)|_],TR),
   atom_find_start_only(FirstGID1,FirstGID),
   !.

@atom_find_start_only(FirstGID0,FirstGID0):-
   !.

@atom_pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,PragmaGID,SplitGID1,FinalGID1,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,LoopGID,SplitGID1,FinalGID1,Canals1)),
   fail.

@atom_pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,StartGID,PragmaGID,FinalGID1,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,StartGID,LoopGID,FinalGID1,Canals1)),
   fail.

@atom_pragma_deleted(PragmaGID,LoopGID):-
   predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
   atomic_split(LoopGID1,StartGID,SplitGID,PragmaGID,Canals1),
   retractall(atomic_split(LoopGID1,_,_,_,_)),
   asserta(atomic_split(LoopGID1,StartGID,SplitGID,LoopGID,Canals1)),
   fail.

@atom_pragma_deleted(_,_):-
   !.

@atom_contain_del_syncs([], f):-!.

@atom_contain_del_syncs([GID|T], t):-
   (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID)),
   retractall(cilk_sync(GID)),
   atomic_op(_,GID,_,LGIDs,_),
   !,
   atom_contain_del_syncs(LGIDs, _),
   atom_contain_del_syncs(T, _),
   !.

@atom_contain_del_syncs([GID|T], Result):-
   \+ (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID)),
   atomic_op(_,GID,_,LGIDs,_),
   !,
   atom_contain_del_syncs(LGIDs, Result1),
   atom_contain_del_syncs(T, Result2),
   ((=(Result1,t); =(Result2,t))->
     =(Result, t);
     =(Result, f)
   ),
   !.

% Удаление cilk_sync из цикла LoopGID. Если они там были, то cilk_sync навешивается на PragmaGID
@atom_move_syncs_from_splitted(PragmaGID, LoopGID):-
  atom_contain_del_syncs([LoopGID], t),
  ((predicate_property(cilk_sync(_),'dynamic'), cilk_sync(PragmaGID))->
     true;
     asserta(cilk_sync(PragmaGID))
  ).

@atom_move_syncs_from_splitted(_, _):-!.

@atom_restructure_loop(PragmaGID, LoopGID, Privates, Tols, Degrees, RestParams):-
  (
   (predicate_property(atomic_split(_,_,_,_,_),'dynamic'), atomic_split(LoopGID,StartGID,SplitGID,FinalGID,Canals))->
     true;
     (
       global_trace(GTD),
       append(LEFT,[gid(_,PragmaGID)|RIGHT],GTD),
       atom_pragma_deleted(PragmaGID,LoopGID),
       append(LEFT,RIGHT,GTPP),
       retractall(global_trace(_)),
       asserta(global_trace(GTPP)),
       fail
     )
  ),
  global_trace(GT),
  append(_,[gid(_,LoopGID),gid(_,BodyGID),gid(_,FirstGID0)|_],GT),
  atom_find_start_only(FirstGID0,FirstGID),
  db_content('prog',BodyGID,[['{']]),
  retractall(db_content('args',PragmaGID,[['body',_]])),
  atom_concat_privates(Privates,PPL),
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
  atom_bypass_op([gid(C,LoopGID)|Right],Loop,RIGHT),
  (
    =(C,'clsDo')->
      append(_,[gid(_,AfterLastGID),gid('clsWhile',_),gid('clsOper',_)],Loop);
      append(_,[gid(_,AfterLastGID)],Loop)
  ),
  !,
  append(Left,[gid('clsBegin',NewBegGID),gid('clsOper',NewIdGID)|Loop],L1),
  append(L1,[gid('clsEnd',NewEndGID)|RIGHT],TR1),
  retractall(global_trace(_)),
  asserta(global_trace(TR1)),
  atom_move_syncs_from_splitted(PragmaGID, LoopGID),
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
      append(Left2,[gid('clsIf',NewStartGID),gid('clsBegin',NewStartBegGID),gid(C2,FirstGID)|Right2],L2),
      append(Left3,[gid(C3,StartGID)|Right3],L2),
      append(Left3,[gid('clsEnd',NewStartEndGID),gid(C3,StartGID)|Right3],TR3),
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
  append(Left6,[gid('clsPreproc',NewTransactionGID),gid('clsBegin',NewTransactBegGID),
     gid('clsIf',NewPart1GID),gid('clsBegin',NewPart1BegGID),gid(C6,StartGID)|Right6],L6),
  append(Left7,[gid(C7,SplitGID)|Right7],L6),
  append(Left7,[gid('clsEnd',NewPart1EndGID),gid('clsElse',NewPart2GID),gid('clsBegin',NewPart2BegGID),
     gid(C7,SplitGID)|Right7],L7),
  append(Left8,[gid(C8,FinalGID)|Right8],L7),
  append(Left8,[gid('clsEnd',NewPart2EndGID),gid('clsEnd',NewTransactEndGID),gid(C8,FinalGID)|Right8],TR8),
  retractall(global_trace(_)),
  asserta(global_trace(TR8)),
  atom_insert_canals(ALoopGID,after(NewIdGID),Canals,Tols,Degrees,AdditionalGID,AdditionalGID1,'TOut<$2> * out_$1 = __id__ == 0 ? new TOut<$2>("$1$8", $4, $6, $5, -1, "$8") : NULL'),
  P1 is AdditionalGID1-1,
  atom_insert_canals(ALoopGID,after(P1),Canals,Tols,Degrees,AdditionalGID1,AdditionalGID2,'TIn<$2> * in_$1 = __id__ == 1 ? new TIn<$2>("$1$8", $4, $6, $5, -1, "$8") : NULL'),
  atom_insert_canals(ALoopGID,before(NewEndGID),Canals,Tols,Degrees,AdditionalGID2,AdditionalGID3,'delete out_$1'),
  P2 is AdditionalGID3-1,
  atom_insert_canals(ALoopGID,before(P2),Canals,Tols,Degrees,AdditionalGID3,AdditionalGID4,'delete in_$1'),
  atom_insert_canals(ALoopGID,before(NewPart1EndGID),Canals,Tols,Degrees,AdditionalGID4,AdditionalGID5,'out_$1->put(($2 *)$7$1)'),
  atom_insert_canals(ALoopGID,after(NewPart2BegGID),Canals,Tols,Degrees,AdditionalGID5,AdditionalGID6,'$3'),
  P3 is AdditionalGID6-1,
  atom_insert_canals(ALoopGID,after(P3),Canals,Tols,Degrees,AdditionalGID6,_,'in_$1->get(($2 *)$7$1, 0)'),
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
      append(Left4,[gid('clsIf',NewFinalGID),gid('clsBegin',NewFinalBegGID),gid(C4,FinalGID)|Right4],L4),
      append(Left5,[gid(C5,AfterLastGID)|Right5],L4),
      append(Left5,[gid('clsEnd',NewFinalEndGID),gid(C5,AfterLastGID)|Right5],TR5),
      retractall(global_trace(_)),
      asserta(global_trace(TR5)),
      !
     )
  ),
  !.

@atom_restructure:-
  atomic_splitted(LoopGID,params(_,Privates,Tols,Degrees,RestParams)),
  global_trace(GT),
  append(_,[gid(_,PragmaGID),gid(_,LoopGID)|_],GT),
  call(atom_restructure_loop(PragmaGID, LoopGID,  Privates, Tols, Degrees, RestParams)),
  fail.

@atom_restructure:-
  !.

@atom_insert_transact_h:-
  predicate_property(atomic_split(_,_,_,_,_),'dynamic'),
  atomic_split(_,_,_,_,_),
  !,
  asserta(db_content('prog',1000000,[['preproc']])),
  asserta(db_content('args',1000000,[['body','#include "transact.h"']])),
  asserta(db_content('prog',1000002,[['preproc']])),
  asserta(db_content('args',1000002,[['body','#define split_private /* split-private */']])),
  once(global_trace(TR)),
  retractall(global_trace(_)),
  asserta(global_trace([gid('clsPreproc',1000000),gid('clsPreproc',1000002)|TR])),
  !.

@atom_insert_transact_h:-
  !.

@atom_processing:-
  atom_prepare_atomic,
  retractall(atomic_split(_,_,_,_,_)),
  atom_process_splits_and_splitteds(5),
  atom_restructure,
  atom_insert_transact_h.

@atom_collect_global_trace:-
  prog(Cls, GID, _, _),
  global_trace(G),
  number_atom(NGID, GID),
  append(G, [gid(Cls, NGID)], GNEW),
  retractall(global_trace(_)),
  asserta(global_trace(GNEW)),
  fail.

@atom_collect_global_trace:-
  !.

@main_debug:-
  asserta(global_trace([])),
  atom_collect_global_trace,
  g_assign('$DefFTime', 15.0), % Время исполнения функции/процедуры по умолчанию (внешней или внутренней до расчета)
  g_assign('$SpawnTime', 5.0), % Время, затрачиваемое мастер-процессом на ответвление spawn-процесса
  g_assign('$SyncTime', 5.0), % Время, затрачиваемое собственно вызовом sync (без ожидания)
  g_assign('$SplittedTime', 25.0), % Время исполнения splitted по умолчанию
  g_assign('$DefOperTime', 1.0), % Время исполнения элементарного математического выражения без функций по умолчанию
  clk_processing,
  !,
  atom_processing,
  !,
  clk_recreate_program('_atomic_cilk.cpp').

@goal:-
  main_debug.
};

#endif
