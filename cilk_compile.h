#ifndef __CILK_COMPILE_H__
#define __CILK_COMPILE_H__

#parse(clsCilkProgram,clsCilkSpace,clsCilkInclude,clsCilkPreproc,clsCilkComments,clsCilkTypedef,clsCilkCVar,clsCilkFunction,clsCilkFor,clsCilkSwitch,clsCilkWhile,clsCilkIf,clsCilkElse,clsCilkDo,clsCilkAlternation,clsCilkReturn,clsCilkOper,clsCilkBegin,clsCilkEnd,clsCilkTerminator)

#def_pattern clsCilkAlternation => [prog] ('clsCilkAlternation', gid(), /root/TYPE/@Value, [['arg', /root/CASE/@Value]]) {
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

#def_pattern clsCilkBegin => [prog] ('clsCilkBegin', gid(), '{', '') {
  (((^)|(\;)+|\}|\{|\\n|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\{)
    (\s|\\t)*
  @end
};

#def_pattern clsCilkComments => [comment] ('clsCilkComments', gid(), /root/CONTENT/@Value) {
  @begin
    ((\/\/([^\\]*)->{CONTENT}(\\n))|(\/\*(.*?)->{CONTENT}\*\/))
  @end
};

#def_pattern clsCilkCVar => [prog] ('clsCilkCVar', gid(), /root/TYPE/@Value, [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (struct|union)->{TYPE}(\\n|\s|\\t)+
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')})
    (\s|\\t)*
  @end
};

#def_pattern clsCilkDo => [prog] ('clsCilkDo', gid(), 'do', '') {
  (((^)|(\;)+|\}|\{|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (do)
  @end
  (\s|\\t)*
  ((\s|\{|\\n|\\t))
  (\s|\\t)*
};

#def_pattern clsCilkElse => [prog] ('clsCilkElse', gid(), 'else', '') {
  (((\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (else)
  @end
  (\s|\\t)*
  ((\s|\\t|\{|\\n))
  (\s|\\t)*
};

#def_pattern clsCilkEnd => [prog] ('clsCilkEnd', gid(), '}', '') {
  (((\;)+|\}|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ()->{GID}
    (\s|\\t)*
    (\})
    (\s|\\t)*
  @end
};

#def_pattern clsCilkFor => [prog] ('clsCilkFor', gid(), 'for', [['init', /root/INITF/@Value],['init', /root/INITN/@Value],['cond', /root/COND/@Value],['chng', /root/CHNGF/@Value],['chng', /root/CHNGN/@Value]]) {
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

#def_pattern clsCilkFunction => [prog] ('clsCilkFunction', gid(), 'func', [['arg', //FIRST_REF/@Value], ['arg', //FIRST/@Value], ['idxs', //FIRST_IDXS/@Value], ['arg', //OTHER_REF/@Value], ['arg', //OTHER/@Value], ['idxs', //OTHER_IDXS/@Value], ['arg', //THREEP/@Value], ['args', /root/ARGS/@Value], ['ret', /root/RETTYPE/@Value], ['name', /root/ID/@Value]]) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
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
  @end
  (\{|\;)
};

#def_pattern clsCilkIf => [prog] ('clsCilkIf', gid(), 'if', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (if(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkInclude => [include] ('clsCilkInclude', gid(), /root/FILE/@Value) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#include(\s|\\t)*\x22([^\x22]+)->{FILE}\x22(\\n|($))
    )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkOper => [prog] ('clsCilkOper', gid(), 'op', [['op', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    ((([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkPreproc => [prog] ('clsCilkPreproc', gid(), 'preproc', [['body', /root/BODY/@Value]]) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#([^\\]*\\\\\\n)*[^\\]*(\\n|($))
    )->{BODY}
    (\s|\\t)*
  @end
};

#def_pattern clsCilkReturn => [prog] ('clsCilkReturn', gid(), 'return', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (return(\\n|\s|\\t)+(([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
    )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkSwitch => [prog] ('clsCilkSwitch', gid(), 'switch', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (switch(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{EXPR}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkTypedef => [prog] ('clsCilkTypedef', gid(), 'type', [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\)|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    typedef((\\n|\s|\\t)+)
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkWhile => [prog] ('clsCilkWhile', gid(), 'while', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (while(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsCilkTerminator => parallelize (gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() parallelize(AfterLastID) {
@goal:-brackets_off.

% #pragma auto for -- включает автораспараллеливание циклов
% #pragma auto pure(fun1,fun2,...) -- обозначает функции без сторонних эффектов по отношению к текущей итерации цикла for

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
  unecapel(T,T1).

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

@strip_list_f([[arg,''], [idxs,'']], []).

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

@make_fargs([], [], [], []).

@make_fargs([['arg','']|REFT],[NM|NMT],[IDXS|IDXST], [NM,IDXS|T]):-
  once(make_fargs(REFT, NMT, IDXST, T)).

@make_fargs([REF|REFT],[NM|NMT],[IDXS|IDXST], [REF,NM,IDXS|T]):-
  once(make_fargs(REFT, NMT, IDXST, T)).

@analyze_args(_, _, '').

@analyze_args(GID, _, [[Name, Val]]):-
  asserta(db_content('args', GID, [[Name, Val]])).

@analyze_args(GID, 'for', [['init',INITF], ['init',INITN], ['cond',COND], ['chng',CHNGF], ['chng',CHNGN]]):-
  once(make_arg('init', INITF, INITN, L1)),
  once(make_arg('chng', CHNGF, CHNGN, L2)),
  append(L1, [['cond',COND]], L3),
  append(L3, L2, L4),
  asserta(db_content('args', GID, L4)).

@analyze_args(GID, 'func', [['arg',REF1], ['arg',NM1], ['idxs',IDXS1], ['arg',REFN], ['arg',NMN], ['idxs',IDXSN], ['arg',THREEP], ARGSV, RETV, NAMEV]):-
  once(into_paired_list_f('arg', REF1, REF1L)),
  once(into_paired_list_f('arg', NM1, NM1L)),
  once(into_paired_list_f('idxs', IDXS1, IDXS1L)),
  once(make_fargs(REF1L, NM1L, IDXS1L, L1)),
  once(strip_list_f(L1, L11)),
  once(into_paired_list_f('arg', REFN, REFNL)),
  once(into_paired_list_f('arg', NMN, NMNL)),
  once(into_paired_list_f('idxs', IDXSN, IDXSNL)),
  once(make_fargs(REFNL, NMNL, IDXSNL, L2)),
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

@glob_prefixate([H|T],[global(H)|T1]):-
   glob_prefixate(T,T1).

@get_glob_lazies(Fun,NPrms,GP,LP,ILP):-
   cilk_function(Fun,GID,NPrms),
   predicate_property(cilk_fanalyzed(_,_,_,_,_),'dynamic'),
   cilk_fanalyzed(Fun,GID,Globs,LP,ILP),
   glob_prefixate(Globs, GP),
   !.

@get_glob_lazies(_,_,[],0,[]):-!.

@get_ftime(Fun,NPrms,T):-
   cilk_function(Fun,GID,NPrms),
   predicate_property(cilk_ftime(_,_,_),'dynamic'),
   cilk_ftime(Fun,GID,T),
   !.

@get_ftime(_,_,T):-  % Содержит время исполнения функции по умолчанию
  g_read('$DefFTime',T),
  !.

@put_ftime(Fun,NPrms,T):-
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

@put_for_time(GID,T):-
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
% Если уже есть результаты предварительного анализа в фактах cilk_fanalyzed, то данные о "ленивости" берутся из них, если же их
% нет, то считается, что глобальных ленивых переменных для этой функции нет, а ленивыми являются все &|*-параметры
% Во втором параметре принимает список разобранных параметров, каждый из которых = список токенов
% В третьем параметре возвращает список ленивых переменных [global(имя),...,par(функция,имя_параметра,переданная переменная),...]
% В четвертом параметре возвращается список имен, переданных в неленивые &|* - параметры
% В пятом параметре принимается список-карта переданных значений. Элемент = множество из одного элемента (имя переданной переменной)
%  или пустое множество (если в параметре передано выражение).
% В шестом параметре возвращается список имен переданных в качестве параметров переменных, значения которых используются на чтение в функции
@get_lazies(Fun, Params, [], _, ParSingleMap, _):-
   predicate_property(cilk_farg(_,_,_,_),'dynamic')->(
     length(Params,N),
     once(cilk_farg(Fun,N,_,_)),
     asserta(counter(0)),
     get_glob_lazies(Fun,N,GP,LP,ReadParams),
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

@extract_lzv([global(V)|T],[V|T1]):-
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
   ((cilk_function(Fun,_,_),=(OUTS3,[]));check_arg(P,OUTS3)),
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
   ((cilk_function(Fun,_,_),=(OUTS3,[]));check_arg(Item,OUTS3)),
   check_arg(Item,V),
   !,
   (
    =(V,[Single])->
      subtract(INS1,[Single],INS);
      =(INS,INS1)
   ),
   union(OUTS0,OUTS3,OUTS),
   !.

@analyze_item_expr(intros,[id(V)|T],INS,[V|OUTT],[V],FUNS,[],[],[]):-
   bypass_idxs(T,['='|Rest],INS0,OUTS0,FUNS0,_),
   \+ =(Rest,['='|_]),
   get_expr(Rest,INS1,OUTS1,FUNS1,_),
   !,
   union(INS0,INS1,INSA), union(OUTS0,OUTS1,OUTTA), append(FUNS0,FUNS1,FUNS),
   unique(INSA,INS), unique(OUTTA,OUTT),
   !.

@analyze_item_expr(intros,[id(V)|T],INS,[V|OUTS],[V],FUNS,[],[],LAZIES):-
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

@analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*',id(V1)],L),
   declaration(D),
   !.

@analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*','*',id(V1)],L),
   declaration(D),
   !.

@analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['*','*','*',id(V1)],L),
   declaration(D),
   !.

@analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,['&',id(V1)],L),
   declaration(D),
   !.

@analyze_expr(L,[],[],[V1],[],[],[],[]):-
   append(D,[id(V1)],L),
   declaration(D),
   !.

@analyze_expr([id(V)],[V],[],[],[],[],[],[]):-
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*','*',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['&',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,[id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   analyze_list_expr(intros,[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   subtract(OUTS0,NEWS,OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   analyze_list_expr(inits,L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies),
   !.

@get_params_length([], 0):-!.

@get_params_length([[arg,'...']],infinity):-!.

@get_params_length([[idxs,_]|T], N):-
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

@prepare_cilk_function(_,_,[]):-!.

@prepare_cilk_function(Name,N,[[name,Name]|T]):-
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[args,_]|T]):-
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,V],[idxs,Idxs]|T]):-
   \+ atom_length(Idxs,0),
   assertz(cilk_farg(Name,N,'[]',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,'&'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'&',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,'*'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'*',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,'**'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'**',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,'***'],[arg,V],[idxs,_]|T]):-
   assertz(cilk_farg(Name,N,'***',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_function(Name,N,[[arg,V],[idxs,'']|T]):-
   assertz(cilk_farg(Name,N,'',V)),
   !,
   prepare_cilk_function(Name,N,T).

@prepare_cilk_functions:-
   global_trace(TR),
   db_content('prog',GID,[[func]]),
   db_content('args',GID,Params),
   once(append(_,[gid('clsCilkFunction',GID),gid('clsCilkBegin',_)|_],TR)),
   member([name,Name],Params),
   get_params_length(Params,N),
   \+ =(N,infinity),
   N1 is N-3, % -args, -ret, -name
   asserta(cilk_function(Name,GID,N1)),
   call(prepare_cilk_function(Name,N1,Params)),
   fail.

@prepare_cilk_functions:-!.

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
   member(Type,['clsCilkWhile','clsCilkSwitch','clsCilkIf','clsCilkReturn','clsCilkOper']),
   !,
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

@prepare_ops('clsCilkAlternation',GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

% (default:) in switch-case
@prepare_ops('clsCilkAlternation',_,[arg([],[],[],[],[],[],[],[])]):-
   !.

@prepare_ops('clsCilkFor',GID,OPL):-
   db_content('args',GID,L),
   prepare_ifor(L,'init',OPL1),
   prepare_ifor(L,'cond',OPL2),
   prepare_ifor(L,'chng',OPL3),
   !,
   append(OPL1,OPL2,OPLP), append(OPLP,OPL3,OPL),
   !.

% Помещает в базу факт cilk_op(Class,GID1,GID2,IDs,Ops) только втом случае, если его еще в базе не было,
% или он был, но с другими ops. В последнем случае устанавливается флаг-факт cilk_recalculate. Это требуется
% для нормальной работы итеративной процедуры уточнения состава ленивых переменных/параметров для каждой функции
@put_cilk_op(Class,GID1,GID2,IDs,Ops):-
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

@get_cilk_fseq([gid('clsCilkEnd',GID)|Rest],[gid('clsCilkEnd',GID)|Rest],[]):-!.

@get_cilk_fseq(L,Rest,[GID|IDT]):-
   get_cilk_fop(L,Rest0,GID),
   !,
   get_cilk_fseq(Rest0,Rest,IDT),
   !.

@get_cilk_fop([gid('clsCilkBegin',GID1)|T],Rest,GID1):-
   get_cilk_fseq(T,[gid('clsCilkEnd',GID2)|Rest],IDs),
   !,
   put_cilk_op('clsCilkBegin',GID1,GID2,IDs,[]),
   !.

@get_cilk_fop([gid(Type,GID)|T],Rest,GID):-
   member(Type,['clsCilkFor','clsCilkSwitch','clsCilkWhile']),
   !,
   get_cilk_fop(T,Rest,OPID),
   !,
   prepare_ops(Type,GID,OPL),
   put_cilk_op(Type,GID,-1,[OPID],OPL),
   !.

@get_cilk_fop([gid('clsCilkDo',GID)|T],Rest,GID):-
   get_cilk_fop(T,[gid('clsCilkWhile',GID1),gid('clsCilkOper',EmptyGID)|Rest],OPID),
   db_content('args',EmptyGID,[[op,'']]),
   !,
   prepare_ops('clsCilkWhile',GID1,OPL),
   put_cilk_op('clsCilkDo',GID,GID1,[OPID],OPL),
   !.

@get_cilk_fop([gid('clsCilkIf',GID)|T],Rest,GID):-
   get_cilk_fop(T,Rest0,OPID0),
   !,
   prepare_ops('clsCilkIf',GID,OPL),
   (
    =(Rest0,[gid('clsCilkElse',GID1)|Rest1])->(
       get_cilk_fop(Rest1,Rest,OPID1),
       put_cilk_op('clsCilkIf',GID,GID1,[OPID0,OPID1],OPL)
    );(
       put_cilk_op('clsCilkIf',GID,-1,[OPID0],OPL),
       =(Rest,Rest0)
    )
   ),
   !.

@get_cilk_fop([gid(Type,GID)|T],T,GID):-
   prepare_ops(Type,GID,OPL),
   put_cilk_op(Type,GID,-1,[],OPL),
   !.

@get_cilk_fprocs([],[]):-!.

@get_cilk_fprocs([GID|T],[GID|TT]):-
   cilk_op('clsCilkOper',GID,_,[],[arg(_,_,_,_,[proc(Name,_)],_,_,_)]),
   cilk_function(Name,_,_),
   !,
   get_cilk_fprocs(T,TT),
   !.
   
@get_cilk_fprocs([GID|T],PGIDS):-
   cilk_op(_,GID,_,LGIDs,_),
   !,
   get_cilk_fprocs(LGIDs,PGIDS0),
   get_cilk_fprocs(T,PGIDS1),
   !,
   append(PGIDS0,PGIDS1,PGIDS),
   !.

@build_cilk_function(Fun,FGID,Body):-
   get_cilk_fop(Body,[],OPID),
   put_cilk_op('clsCilkFunction',FGID,-1,[OPID],[]),
   get_cilk_fprocs([OPID],ProcsGIDs),
   asserta(cilk_fprocs(Fun,FGID,ProcsGIDs)),
   !.

% Анализ (структурный, в глубину) всех функций с разбором выражений, результаты которого попадают в cilk_op
@build_cilk_functions:-
   global_trace(TR),
   retractall(cilk_fprocs(_,_,_)),
   !,
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Fun,GID,_),
      once(append(_,[gid('clsCilkFunction',GID)|T],TR)),
      bypass_complex(T,Body,_),
      call(build_cilk_function(Fun,GID,Body)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@get_globals([],[]):-!.

@get_globals([gid('clsCilkCVar',GID)|T],[V|T1]):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   rbypass_var(L,V,_,_,_,_,_),
   get_globals(T,T1).

@get_globals([gid('clsCilkOper',GID)|T],T1):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   analyze_expr(L,_,_,NEWS,_,_,_,_),
   get_globals(T,T0),
   append(NEWS,T0,T1),
   !.

@get_globals([gid('clsCilkFunction',_)|T],T1):-
   bypass_complex(T,_,After),
   get_globals(After,T1),
   !.

@get_globals([_|T],T1):-
   get_globals(T,T1).

@find_globals:-
   global_trace(TR),
   get_globals(TR,GLOBS),
   asserta(cilk_globals(GLOBS)),
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

@analyze_one_flazies([],_,_,_,[],[],[]):-!.

% ReadParams -- читаемые в самой функции ее ленивые параметры (не только выходные, но и входные).
@analyze_one_flazies([GID|GIDS],Globs,Pars,Locals,GLazies,PLazies,ReadParams):-
   cilk_op(_,GID,_,IGIDs,Ops),
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
   cilk_function(Fun,GID,NPrms),
   !,
   (
    (predicate_property(cilk_fanalyzed(_,_,_,_,_),'dynamic'), cilk_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams))->(
     true,!
     );(
     get_fparams(lazy,Fun,NPrms,LPars0),
     !,
     cilk_globals(Glob0),
     !,
     asserta(cilk_fanalyzed(Fun,GID,[],LPars0,LPars0)),
     analyze_one_flazies([GID],Glob0,LPars0,[],GLazies,PLazies,ReadParams),
     retractall(cilk_fanalyzed(Fun,GID,[],_,_)),
     asserta(cilk_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams)),
     !
    )
   ).

% Определение выходных переменных (глобальных и потенциально модифицируемых параметров) для каждой функции. Для этого проводится
% структурный анализ функции в глубину (с отслеживанием локально декларированных переменных, изменение которых нас здесь не интересует),
% выявляются модифицируемые переменные. Модифицируемые глобалы и параметры попадают в cilk_fanalyzed
@analyze_cilk_functions:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Fun,_,N),
      call(analyze_flazies(Fun,N,_,_,_)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Итерационное сходящееся уточнение состава ленивых переменных/параметров функций (cilk_fanalyzed). На каждой итерации
% для каждой функции уточняется список модифицируемых глобальных переменных и &|*-параметров. Это делается в analyze_cilk_functions.
% Это уточнение может влиять на другие функции, вызывающие уточненные. Сначала считается, что функция модифицирует все свои &|*-параметры,
% они входят в соответствующие списки cilk_fanalyzed, потом эти списки урезаются, в то время как списки глобальных переменных расщиряются.
% Проходит "волна" уточнений, в результате которой, например, функции int p1(int &x) { p2(x); }, int p2(int & x) { cout << x; } в последнем
% приближении уже не имеют выходных ленивых значений вообще, в то время как функции int p1() { p2(); }, int p2() { X = 11; } имеют один
% ленивый результат -- глобальную переменную X.
% После оередного уточнения, выполняется перестройка cilk_op-фактов, в которых выполняется новый разбор выражений с учетом новых данных
% о ленивости. Если при этом изменится хоть один факт, то устанавливается cilk_reanalyze, что свидетельствует о необходимости как минимум
% еще одной итерации.
@iterative_build_funs:-
   retractall(cilk_reanalyze),
   build_cilk_functions,
   (
    (predicate_property(cilk_reanalyze,'dynamic'), cilk_reanalyze)->(
      retractall(cilk_fanalyzed(_,_,_,_,_)),
      analyze_cilk_functions,
      iterative_build_funs,
      !
    );(
      true, !
    )
   ),
   !.

@get_flist_deps([]):-
   !.

@get_flist_deps([V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   !,
   (
    predicate_property(cilk_function(_,_,_),'dynamic'),
    cilk_function(Name,_,NPrms),
    predicate_property(cilk_fdependent(_,_,_),'dynamic'),
    cilk_fdependent(Name,NPrms,f)
   ),
   get_flist_deps(T),
   !.

@get_fexpr_deps([]):-
   !.

@get_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   !,
   get_flist_deps(FUNS),
   get_fexpr_deps(T),
   !.

@get_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   !,
   get_flist_deps(FUNS),
   !,
   get_flist_deps(PROCS),
   get_fexpr_deps(T),
   !.

@get_fblock_deps([]):-
   !.

@get_fblock_deps([GID|T]):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   get_fexpr_deps(Exprs),
   !,
   get_fblock_deps(LGIDs),
   !,
   get_fblock_deps(T),
   !.

% Имеет ли блок внутри cilk_sync?
@block_has_sync([]):-
   !,
   fail.

@block_has_sync([GID|T]):-
   !,
   (
    (predicate_property(cilk_sync(_),'dynamic'),cilk_sync(GID))->
       true;
       (
        cilk_op(_,GID,_,LGIDs,_),
        !,
        (
         block_has_sync(LGIDs)->
           true;
           block_has_sync(T)
        )
       )
   ).

@exprs_has_no_derefs([]):-
   !.

@exprs_has_no_derefs([E|T]):-
   =..(E,[_,_,_,_,_,_,_,_,[L]]),
   !,
   \+ (
     append(['*'],_,L);
     (append(_,[S,'*'|_],L),member(S,['(','[','+','-','*','%','!','~','=','<','>',',',';']))
   ),
   !,
   exprs_has_no_derefs(T).

% Содержит ли блок разыменование указателей
@block_has_no_derefs([]):-
   !.

@block_has_no_derefs([GID|T]):-
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   exprs_has_no_derefs(Exprs),
   !,
   block_has_no_derefs(LGIDs),
   block_has_no_derefs(T).

@exprs_in_outs([],[],[]):-
   !.

@exprs_in_outs([E|T],Ins,Outs):-
   =..(E,[_,Ins0,Outs0,_,_,_,_,_,_]),
   !,
   exprs_in_outs(T,Ins1,Outs1),
   union(Ins0,Ins1,Ins),
   union(Outs0,Outs1,Outs),
   !.

@for_in_outs([],[],[]):-
   !.

@for_in_outs([GID|T],Ins,Outs):-
   cilk_op(C,GID,_,LGIDs,Exprs),
   !,
   (
    =(C,'clsCilkFor')->
      (exprs_in_outs(Exprs,Ins0,_),=(Outs0,[]));
      exprs_in_outs(Exprs,Ins0,Outs0)
   ),
   !,
   for_in_outs(LGIDs,Ins1,Outs1),
   for_in_outs(T,Ins2,Outs2),
   !,
   union(Ins0,Ins1,InsA), union(InsA,Ins2,Ins),
   union(Outs0,Outs1,OutsA), union(OutsA,Outs2,Outs),
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
   cilk_op(_,GID,_,LGIDs,Exprs),
   !,
   get_expr_idxs(Exprs,Idxs0),
   !,
   get_var_idxs(LGIDs,Idxs1),
   get_var_idxs(T,Idxs2),
   union(Idxs0,Idxs1,IdxsA), union(IdxsA,Idxs2,Idxs),
   !.

@check_idx_one(_,[]):-
   !.

@check_idx_one(V,[L|T]):-
   !,
   \+ member(id(V),L),
   check_idx_one(V,T).

@check_idx(_,[]):-
   !.

@check_idx(V,[var(_,Idxs)|T]):-
   check_idx_one(V,Idxs),
   check_idx(V,T).

% Проверка -- зависит ли индекс от выходных переменных
@check_idxs([],_):-
   !.

@check_idxs([V|T],VarIdxs):-
   check_idx(V,VarIdxs),
   !,
   check_idxs(T,VarIdxs).

@filter_idx_one(_,_,[],[]):-
   !.

@filter_idx_one(V,N,[L|T],[idx(N,L)|TT]):-
   member(id(V),L),
   !,
   N1 is N+1,
   filter_idx_one(V,N1,T,TT).

@filter_idx_one(V,N,[_|T],TT):-
   filter_idx_one(V,N,T,TT).

@filter_idxs(_,[],[]):-
   !.

% Превращаем индексы в список зависящих от счетчика индексов
@filter_idxs(V,[var(P,Idxs)|T],[var(P,OIdxs)|TT]):-
   call(filter_idx_one(V,0,Idxs,OIdxs)),
   !,
   filter_idxs(V,T,TT),
   !.

@same_indexes(_,_,[]):-
   !.

@same_indexes(V,Idxs,[var(V,Idxs1)|T]):-
   !,
   =(Idxs,Idxs1),
   same_indexes(V,Idxs,T),
   !.

@same_indexes(V,Idxs,[_|T]):-
   !,
   same_indexes(V,Idxs,T).

@eq_indexes(V,FIdxs):-
   append(_,[var(V,Idxs)|T],FIdxs),
   !,
   same_indexes(V,Idxs,T).

@eq_indexes(_,_):-
   !.

@check_outs_by_idxs([],_,_):-
   !.

@check_outs_by_idxs([V|T],Ins,FIdxs):-
   !,
   \+ member(var(V,[]),FIdxs), % Выходная переменная должна зависеть от индекса
   !,
   (
    \+ member(V,Ins); % Выходная переменная -- не входная
    eq_indexes(V,FIdxs) % Выходная переменная имеет везде одинаковую индексацию по счетчику
   ),
   !,
   check_outs_by_idxs(T,Ins,FIdxs).

% Не содержит ли цикл связей между итерациями по индексам
@for_content(Counter,LGIDs):-
   once(for_in_outs(LGIDs,Ins,Outs)),
   get_var_idxs(LGIDs,VarIdxs),
   check_idxs(Outs,VarIdxs),
   !,
   filter_idxs(Counter,VarIdxs,FIdxs),
   !,
   check_outs_by_idxs(Outs,Ins,FIdxs).

% Анализ возможности распараллелить for
@analyze_for(GID):-
   cilk_op('clsCilkFor',GID,_,LGIDs,Exprs),
   (
    (predicate_property(cilk_for_time(_,_),'dynamic'),cilk_for_time(GID,T))->
       (g_read('$SpawnTime',TSP), g_read('$SyncTime',TSY), TPAR is T + 3*(TSP + TSY), TSEQ is 8*T, TPAR < TSEQ); % 2^3 = 8 (бинарное дерево ветвления)
       true
   ),
   \+ once(block_has_sync(LGIDs)),
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
   once(block_has_no_derefs(LGIDs)),
   once(get_fblock_deps(LGIDs)),
   once(for_content(Counter,LGIDs)),
   asserta(cilk_for(GID)),
   !.

% Нельзя распараллелить for
@analyze_for(GID):-
   cilk_op('clsCilkFor',GID,_,_,_),
   !.

@get_fors([],_):-!.

@get_fors([GID|T],_):-
   cilk_op(_,GID,_,[],_),
   !,
   get_fors(T,t),
   !.
   
% Пытаемся распараллелить самый внешний цикл
@get_fors([GID|T],Flag):-
   cilk_op('clsCilkFor',GID,_,[LGID],_),
   cilk_op('clsCilkFor',LGID,_,_,_),
   !,
   (
    =(Flag,t)->(
      analyze_for(GID),
      (
       (predicate_property(cilk_for(_),'dynamic'),cilk_for(GID))->
         get_fors([LGID],f);
         get_fors([LGID],t)
      )
    );(
      get_fors([LGID],f)
    )
   ),
   !,
   get_fors(T,t),
   !.

% Пытаемся распараллелить цикл
@get_fors([GID|T],Flag):-
   cilk_op('clsCilkFor',GID,_,LGIDs,_),
   !,
   (
    =(Flag,t)->
      analyze_for(GID);
      true
   ),
   !,
   get_fors(LGIDs,t),
   !,
   get_fors(T,t),
   !.

% Прочие составные операторы
@get_fors([GID|T],_):-
   cilk_op(_,GID,_,LGIDs,_),
   !,
   get_fors(LGIDs,t),
   !,
   get_fors(T,t),
   !.
   
% Обработка и распараллеливание циклов в функции Fun
@handle_fors_in_function(FGID):-
   cilk_op('clsCilkFunction',FGID,_,LGIDs,_),
   get_fors(LGIDs,t),
   !.

% Обработка и распараллеливание подходящих циклов в каждой функции
@handle_fors:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(_,GID,_),
      call(handle_fors_in_function(GID)),
      fail);
     true,!
    );(
     true,!
    )
   ).

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
   cilk_op(_,GID,_,LGIDs,Exprs),
   get_expr_deps(NamePath,Exprs),
   get_block_deps(NamePath,LGIDs),
   !,
   get_block_deps(NamePath,T),
   !.

@mark_deps([]):-
   !.

@mark_deps([path(Name,NPrms)|T]):-
   (
    (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,t))->(
      true,!
    );(
      retractall(cilk_fdependent(Name,NPrms,_)), asserta(cilk_fdependent(Name,NPrms,t))
    )
   ),
   mark_deps(T).

@get_fdeps(Name,NamePath,NPrms):-
   member(path(Name,NPrms),NamePath),
   !.

@get_fdeps(Name,NamePath,NPrms):-
   cilk_function(Name,GID,NPrms),
   cilk_op('clsCilkFunction',GID,_,LGIDs,_),
   (
    (predicate_property(cilk_fdependent(_,_,_),'dynamic'),cilk_fdependent(Name,NPrms,_))->(
      true,!
    );(
      get_block_deps([path(Name,NPrms)|NamePath],LGIDs),
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
        mark_deps(NamePath);
        true
   ).

@get_fdeps(Name,NamePath,NPrms):-
   \+ cilk_function(Name,_,NPrms),
   (
    (predicate_property(cilk_fpure(_),'dynamic'),cilk_fpure(Name))->
       true;
       mark_deps(NamePath)
   ),
   !.

% Определение зависимостей функций от внешних функций
@find_dependents:-
   (
    predicate_property(cilk_function(_,_,_),'dynamic')->(
     (
      cilk_function(Name,_,NPrms),
      call(get_fdeps(Name,[],NPrms)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@get_comma_list([id(F),')'],[F]):-
   !.

@get_comma_list([id(F),','|R],[F|T]):-
   get_comma_list(R,T).

@analyze_pragma_pure([]):-
   !.

@analyze_pragma_pure([F|T]):-
   (
    (predicate_property(cilk_fpure(_),'dynamic'),cilk_fpure(F))->
       true;
       asserta(cilk_fpure(F))
   ),
   !,
   analyze_pragma_pure(T).

% Очистка + Загрузка необходимых данных перед анализом
@prepare_cilk:-
   retractall(db_content(_,_,_)),
   retractall(cilk_function(_,_,_)),
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
   read_db,
   (
    (db_content('prog',GID,[['preproc']]),db_content('args',GID,[[body,S]]),parse_expr(S,['#',id('pragma'),id('auto'),id('for')]))->
     (
      !,
      (
       (predicate_property(cilk_auto_for,'dynamic'), cilk_auto_for)->
         true;
         asserta(cilk_auto_for)
      )
     );
     true
   ),
   !,
   (
    (db_content('prog',GID1,[['preproc']]),
     db_content('args',GID1,[[body,S1]]),
     once(parse_expr(S1,['#',id('pragma'),id('auto'),id('pure'),'('|R1])),
     once(get_comma_list(R1,L1)),
     once(analyze_pragma_pure(L1)),
     fail);
     true
   ),
   !,
   prepare_cilk_functions,
   !,
   find_globals,
   !,
   build_cilk_functions,
   !,
   analyze_cilk_functions,
   !,
   iterative_build_funs,
   !,
   find_dependents,
   !.

@find_lvar(V,[Globals],global(V)):-
   member(global(V),Globals),
   !.

@find_lvar(V,[TopVars|_],loc(TopGID,V)):-
   member(loc(TopGID,V),TopVars),
   !.

@find_lvar(V,[_|RestVars],V1):-
   find_lvar(V,RestVars,V1),
   !.

@find_lvars([],_,[]):-!.

@find_lvars([global(V)|T],Vars,[global(V)|T1]):-
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

@loc_prefixate(TopGID,[V|T],[loc(TopGID,V)|T1]):-
   loc_prefixate(TopGID,T,T1),
   !.

@getNewInOutRefLazies(_,_,[],[],[],[],[],[],0.0):-!.

@getNewInOutRefLazies(TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM):-
   =..(V,[_,Ins0,Outs0,News0,Funs0,_,Ref0,Laz0,_]),
   find_lvars(Ins0,Vars,InsP),
   find_lvars(Outs0,Vars,OutsP),
   find_lvars(Ref0,Vars,RefsP),
   find_lvars(Laz0,Vars,LazP),
   loc_prefixate(TopGID,News0,NewsP),
   !,
   getTime(Funs0,T0),
   getNewInOutRefLazies(TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1),
   !,
   append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
   append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
   unique(News2,News), unique(Ins2,Ins), unique(Laz2,Lazies),
   unique(Outs2,Outs), unique(Ref2,Refs),
   TM is T0+T1,
   !.

@getForNewInOutRefLazies(_,_,_,[],[],[],[],[],[],0.0):-!.

@getForNewInOutRefLazies(Types,TopGID,Vars,[V|T],News,Ins,Outs,Refs,Lazies,TM):-
   =..(V,[Type,Ins0,Outs0,News0,Funs0,_,Ref0,Laz0,_]),
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
      getForNewInOutRefLazies(Types,TopGID,Vars,T,News1,Ins1,Outs1,Refs1,Laz1,T1),
      !,
      append(NewsP,News1,News2), append(InsP,Ins1,Ins2), append(LazP,Laz1,Laz2),
      append(OutsP,Outs1,Outs2), append(RefsP,Refs1,Ref2),
      unique(News2,News), unique(Ins2,Ins), unique(Laz2,Lazies),
      unique(Outs2,Outs), unique(Ref2,Refs),
      TM is T0+T1
    );(
      getForNewInOutRefLazies(Types,TopGID,Vars,T,News,Ins,Outs,Refs,Lazies,TM)
    )
   ),
   !.

@put_cilk_sync(GID):-
   (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->
      (true, !);
      (asserta(cilk_sync(GID))).

@inc_spawns([],[],_):-!.

@inc_spawns([trace(S,Fun,NPrms,T0)|T1],[trace(S,Fun,NPrms,TR)|T2],Delta):-
   TR is T0+Delta,
   inc_spawns(T1,T2,Delta).

@start_spawn(GID,Fun,NPrms,L,[trace(GID,Fun,NPrms,0.0)|L],T1,T2):-
   g_read('$SpawnTime', A),  % +Затраты на собственно spawn
   T2 is T1+A.

@stop_spawns([],[],T,T):-!.

@stop_spawns([trace(GID,Fun,NPrm,T1)|T],[],T0,TMax):-
   get_ftime(Fun,NPrm,TF),
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
         asserta(cilk_spawn_time(GID,[TT|Timings]))
      );(
         asserta(cilk_spawn_time(GID,[TT]))
      )
   ),
   stop_spawns(T,[],T0,TC),
   (
    >(TT,TC)->
      =(TMax,TT);
      =(TMax,TC)
   ),
   !.

% Альтернативы из switch {}
@traverse_alters([CurGID|GIDs], [TopGID|StackGIDs], [switch(TopGID,Pass)|StackConstrs], StackConstrs, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time, NAlt):-
   cilk_op('clsCilkAlternation',CurGID,_,[],_),
   (
    (append(ALT,[NextGID|_],GIDs),cilk_op('clsCilkOper',NextGID,_,[],_),db_content('args',NextGID,[['op','break']]),!)->
       (
        !,
        traverse_fun(NextGID,ALT,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazV,InRefs,RefV,ISpawns,OSP1,T1),
        !
       );
       (
        traverse_fun(NextGID,GIDs,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazV,InRefs,RefV,ISpawns,OSP1,T1),
        !
       )
   ),
   retractall(cilk_break(_)),
   (
    (append(_,[NextGID1|Rest1],GIDs),cilk_op('clsCilkAlternation',NextGID1,_,[],_))->(
       !,
       traverse_alters([NextGID1|Rest1],[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,InLazies,LazVV,InRefs,RefVV,OSP1,OSpawns,T2,NAlt1),
       append(LazV,LazVV,Laz1), append(RefV,RefVV,Ref1),
       unique(Laz1,OutLazies), unique(Ref1,OutRefs),
       Time is T1+T2,
       NAlt is NAlt1+1,
       !
    );(
       =(OutLazies,LazV), =(OutRefs,RefV), =(OSpawns,OSP1), =(Time,T1), =(NAlt,1),
       !
    )
   ),
   !.

@traverse_alters([], [TopGID|_], [switch(TopGID,_)|CRest], CRest, _, InLazies, InLazies, InRefs, InRefs, ISpawns, ISpawns, 0.0, 0):-!.

% Окончание while
@traverse_fun(SyncGID,[], [TopGID|StackGIDs], [while(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkWhile',TopGID,_,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,TP)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2), intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(TP,0.0)
        );(
          (
           cilk_op('clsCilkBegin',IGID,EGID,_,_)->
            put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsCilkWhile',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsCilkWhile',TopGID,-1,[NewIGID],Ops)),
             asserta(cilk_op('clsCilkBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsCilkBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsCilkOper',NewDGID),gid('clsCilkEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,TP)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
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
          cilk_op('clsCilkWhile',TopGID,_,[IGID1],_),
          traverse_fun(_,[IGID1],[TopGID|StackGIDs],[while(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T1)
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
@traverse_fun(_,[CurGID|_], StackGIDs, [Top|StackConstrs], StackConstrs, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','break']]),
   !,
   asserta(cilk_break(CurGID)),
   =..(Top,[_,TopGID,_]),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     traverse_fun(CurGID,[],[CurTopGID|Rest],[Top|StackConstrs],_,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
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
@traverse_fun(_,[CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','continue']]),
   !,
   asserta(cilk_continue(CurGID)),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(st(ST0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     traverse_fun(CurGID,[],[CurTopGID|Rest],ST0,ST1,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
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
@traverse_fun(_,[CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkReturn',CurGID,_,[],_),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(lz(InLazies)), asserta(rf(InRefs)), asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(sp(ISpawns)), asserta(tm(0.0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(lz(LZ0)), once(rf(RF0)), once(st(ST0)), once(vr(VAR0)), once(sp(SP0)), once(tm(T0)),
     traverse_fun(CurGID,[],[CurTopGID|Rest],ST0,ST1,VAR0,LZ0,LZ1,RF0,RF1,SP0,SP1,TT),
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
@traverse_fun(SyncGID,[], [TopGID|StackGIDs], [do(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkDo',TopGID,LastGID,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2), intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          (
           cilk_op('clsCilkBegin',IGID,EGID,_,_)->
            put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsCilkDo',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsCilkDo',TopGID,LastGID,[NewIGID],Ops)),
             asserta(cilk_op('clsCilkBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsCilkBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsCilkOper',NewDGID),gid('clsCilkEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
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
          cilk_op('clsCilkDo',TopGID,LastGID,[IGID1],_),
          traverse_fun(_,[IGID1],[TopGID|StackGIDs],[do(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T2)
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
@traverse_fun(SyncGID,[], [TopGID|StackGIDs], [for(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkFor',TopGID,_,[IGID],Ops),
   !,
   (=(SyncGID,IGID);true), % Если SyncGID не связан, то получает значение IGID, иначе значение SyncGID сохраняется
   !,
   getForNewInOutRefLazies(['cond','chng'],TopGID,[LVars|Vars],Ops,_,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2), intersect(LVars,InRefs,Decision3),
       (
        (=(Decision1,[]),=(Decision2,[]),=(Decision3,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          (
           cilk_op('clsCilkBegin',IGID,EGID,_,_)->
            put_cilk_sync(EGID);
            (
             retractall(cilk_op('clsCilkFor',TopGID,_,[IGID],Ops)),
             NewIGID is IGID+10000,
             NewEGID is NewIGID+1,
             NewDGID is NewIGID+2,
             asserta(cilk_op('clsCilkFor',TopGID,-1,[NewIGID],Ops)),
             asserta(cilk_op('clsCilkBegin',NewIGID,NewEGID,[IGID,NewDGID],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkOper',NewDGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(cilk_op('clsCilkEnd',NewEGID,-1,[],[arg([],[],[],[],[],[],[],[])])),
             asserta(db_content('prog',NewIGID,[['{']])),
             asserta(db_content('prog',NewEGID,[['}']])),
             asserta(db_content('prog',NewDGID,[['op']])),
             asserta(db_content('args',NewDGID,[['op','']])),
             once(global_trace(TR)),
             append(Left,[gid(C,IGID)|Right],TR),
             bypass_op([gid(C,IGID)|Right],OPP,RIGHT),
             append(Left,[gid('clsCilkBegin',NewIGID)|OPP],LL1),
             append(LL1,[gid('clsCilkOper',NewDGID),gid('clsCilkEnd',NewEGID)|RIGHT],TR1),
             retractall(global_trace(_)),
             asserta(global_trace(TR1)),
             !,
             put_cilk_sync(NewDGID)
            )
          ),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
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
          cilk_op('clsCilkFor',TopGID,_,[IGID1],_),
          traverse_fun(_,[IGID1],[TopGID|StackGIDs],[for(TopGID,2)|StackConstrs],_,[LVars|Vars],Laz1,OutLazies,Ref1,OutRefs,OSP1,OSpawns,T2),
          put_for_time(TopGID,T2)
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
@traverse_fun(SyncGID,[], [TopGID|_], StackConstrs, StackConstrs, [LVars|_], InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkBegin',TopGID,EndGID,_,_),
   !,
   (=(SyncGID,EndGID);true), % Если SyncGID не связан, то получает значение EndGID, иначе значение SyncGID сохраняется
   !,
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(OutLazies,[]), =(OutRefs,[]), stop_spawns(ISpawns,OSpawns,0.0,Time)
      );(
       intersect(InLazies,LVars,Decision2), intersect(InRefs,LVars,Decision3),
       (
        (=(Decision2,[]),=(Decision3,[]))->(
          =(OutLazies,InLazies), =(OutRefs,InRefs), =(OSpawns,ISpawns), =(Time,0.0)
        );(
          put_cilk_sync(SyncGID),
          =(OutLazies,[]), =(OutRefs,[]), stop_spawns(ISpawns,OSpawns,0.0,Time)
        )
       )
      )
   ),
   !.

% Окончание функции
@traverse_fun(_,[], [-1], StackConstrs, StackConstrs, _, _, [], _, [], ISpawns, ISpawns, 0.0):-
   !.

% Окончание произвольного (не{}) оператора. Может вызываться в операторе окончания различных конструктов
@traverse_fun(_,[], [TopGID|_], StackConstrs, StackConstrs, [LVars|_], InLazies, OutLazies, InRefs, OutRefs, ISpawns, ISpawns, 0.0):-
   \+ cilk_op('clsCilkBegin',TopGID,_,_,_),
   !,
   intersect(InLazies,LVars,Decision2), intersect(InRefs,LVars,Decision3),
   (
    (=(Decision2,[]),=(Decision3,[]))->(
      =(OutLazies,InLazies), =(OutRefs,InRefs)
    );(
      fail % Непонятно: текущий оператор имеет локальную ленивую переменную, причем не в {}. Как это возможно?
    )
   ),
   !.

% Полный if-else, IGIDs = [IfGID,EGID]. Краткий if -- обрабатывается обычным образом, IGIDs = [IfGID]
@traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkIf',CurGID,_,[IfGID,EGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
   !,
   traverse_fun(_,[IfGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz20,Ref1,Ref20,OSP1,OSP20,T20),
   traverse_fun(_,[EGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz21,Ref1,Ref21,OSP1,OSP21,T21),
   append(Laz20,Laz21,Laz22), unique(Laz22,Laz2), !,
   append(Ref20,Ref21,Ref22), unique(Ref22,Ref2), !,
   append(OSP20,OSP21,OSP22),
   traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP22,OSpawns,T3),
   Time is T1+BaseTime+0.5*(T20+T21)+T3,
   !.

% Полный while
@traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkWhile',CurGID,_,[IGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
   !,
   traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[while(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
   !,
   traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
   Time is T1+BaseTime+T2+T3,
   !.

% Полный for
@traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkFor',CurGID,_,[IGID],Ops),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   getForNewInOutRefLazies(['init','cond'],CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
   !,
   traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[for(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
   !,
   traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
   Time is T1+BaseTime+T2+T3,
   !.

% Полный do-while
@traverse_fun(_,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkDo',CurGID,_,[IGID],_),
   !,
   traverse_fun(_,[IGID],[CurGID,TopGID|StackGIDs],[do(CurGID,1)|StackConstrs],_,[[]|Vars],InLazies,Laz2,InRefs,Ref2,ISpawns,OSP1,T1),
   !,
   traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP1,OSpawns,T2),
   Time is T1+T2,
   !.

% switch
@traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   cilk_op('clsCilkSwitch',CurGID,_,[IGID],Ops),
   cilk_op('clsCilkBegin',IGID,_,IGIDs,_),
   !,
   (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
   inc_spawns(ISpawns,ISP,BaseTime),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID))->(
       =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
      );(
       intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2),
       (
        (=(Decision1,[]),=(Decision2,[]))->(
          =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP), =(T1,0.0)
        );(
          put_cilk_sync(SyncGID),
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP,OSP1,0.0,T1)
        )
       )
      )
   ),
   append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
   unique(Laz0,Laz1), unique(Ref0,Ref1),
   !,
   traverse_alters(IGIDs,[CurGID,TopGID|StackGIDs],[switch(CurGID,1)|StackConstrs],_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,TNN,NAlt),
   !,
   traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T2),
   (
    =(NAlt,0)->
      Time is T1+BaseTime+T2;
      Time is T1+BaseTime+TNN/NAlt+T2
   ),
   !.

@traverse_fun(SyncGID,[CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, InLazies, OutLazies, InRefs, OutRefs, ISpawns, OSpawns, Time):-
   (predicate_property(cilk_break(_),'dynamic'), cilk_break(BreakGID))->(
      traverse_fun(BreakGID,[], [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,InLazies,OutLazies,InRefs,OutRefs,ISpawns,OSpawns,Time),
      !
   );(
      cilk_op(_,CurGID,_,IGIDs,Ops),
      !,
      (=(SyncGID,CurGID);true), % Если SyncGID не связан, то получает значение CurGID, иначе значение SyncGID сохраняется
      !,
      getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,Refs,Lazs,BaseTime),
      inc_spawns(ISpawns,ISP,BaseTime),
      (
       (predicate_property(cilk_spawn(_),'dynamic'), cilk_spawn(CurGID))->
          (
           cilk_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)]),
           length(Prms,NPrms),
           start_spawn(CurGID,Fun,NPrms,ISP,ISP1,0.0,TSP));
          (
           ( % Если это не spawn, но запуск процедуры, то прибавляем время ее исполнения
            cilk_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)])->
              (getTime([proc(Fun,Prms)],TSP1), g_read('$DefOperTime',TOp0), TSP is TSP1-TOp0);
              =(TSP,0.0)
           ),
           =(ISP1,ISP)
          )
      ),
      (
       (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(SyncGID),
        ((predicate_property(cilk_spawn(_),'dynamic'),=(SyncGID,CurGID))->(\+ cilk_spawn(SyncGID));true)
       )->(
          =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP1,OSP1,0.0,T1)
         );(
          intersect(InLazies,Ins,Decision1), intersect(InRefs,Outs,Decision2),
          (
           (=(Decision1,[]),=(Decision2,[]))->(
             =(NextLazies,InLazies), =(NextRefs,InRefs), =(OSP1,ISP1), =(T1,0.0)
           );(
             put_cilk_sync(SyncGID),
             =(NextLazies,[]), =(NextRefs,[]), stop_spawns(ISP1,OSP1,0.0,T1)
           )
          )
         )
      ),
      addLocals(Vars,News,Vars1),
      append(NextLazies,Lazs,Laz0), append(NextRefs,Refs,Ref0),
      unique(Laz0,Laz1), unique(Ref0,Ref1),
      !,
      traverse_fun(_,IGIDs,[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Laz1,Laz2,Ref1,Ref2,OSP1,OSP2,T2),
      traverse_fun(_,GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars1,Laz2,OutLazies,Ref2,OutRefs,OSP2,OSpawns,T3),
      Time is TSP+T1+BaseTime+T2+T3,
      !
   ).

@create_syncs(Fun,GID,NPrms):-
   retractall(cilk_break(_)),
   retractall(cilk_continue(_)),
   cilk_globals(GLOB),
   glob_prefixate(GLOB,G1),
   get_fparams(all,Fun,NPrms,PARMS),
   loc_prefixate(GID,PARMS,P1),
   traverse_fun(_,[GID],[-1],[],_,[P1,G1],[],_,[],_,[],OSP,Time0),
   stop_spawns(OSP,[],Time0,Time),
   put_ftime(Fun,NPrms,Time),
   !.

@bypass_sequence([],[],[]):-!.

@bypass_sequence([gid('clsCilkEnd',GID)|T],[],[gid('clsCilkEnd',GID)|T]):-
   !.

@bypass_sequence([gid('clsCilkBegin',GID)|T],TT,T3):-
   bypass_complex([gid('clsCilkBegin',GID)|T],T0,T1),
   bypass_sequence(T1,T2,T3),
   append(T0,T2,TT),
   !.

@bypass_sequence([H|T],[H|T1],T2):-
   bypass_sequence(T,T1,T2),
   !.

@bypass_complex([gid('clsCilkBegin',GID)|T],[gid('clsCilkBegin',GID)|T1],T2):-
   bypass_sequence(T,T0,[gid('clsCilkEnd',GID2)|T2]),
   append(T0,[gid('clsCilkEnd',GID2)],T1).

@bypass_op([A|T],[A|BeforeWith],After):-
   member(A,[gid('clsCilkFor',_),gid('clsCilkSwitch',_),gid('clsCilkWhile',_)]),
   !,
   bypass_op(T,BeforeWith,After),
   !.

@bypass_op([gid('clsCilkDo',GID)|T],[gid('clsCilkDo',GID)|T1],T2):-
   bypass_op(T,BeforeWhile,[gid('clsCilkWhile',GIDW),gid('clsCilkOper',EMPTY)|T2]),
   append(BeforeWhile,[gid('clsCilkWhile',GIDW),gid('clsCilkOper',EMPTY)],T1),
   !.

@bypass_op([gid('clsCilkIf',GID)|T],[gid('clsCilkIf',GID)|T1],T2):-
   bypass_op(T,BeforeWith,[A|AfterT]),
   (
    =(gid('clsCilkElse',_),A)->(
      bypass_op(AfterT,BeforeWith2,T2),
      append(BeforeWith,[A|BeforeWith2],T1),
      !
    );(
      =(T1,BeforeWith),=(T2,[A|AfterT]),!
    )
   ),
   !.

@bypass_op([gid('clsCilkBegin',GID)|T],T1,T2):-
   bypass_complex([gid('clsCilkBegin',GID)|T],T1,T2),
   !.

@bypass_op([A|T],[A],T):-!.

@insert_ending_bracket(L1,L2):-
   bypass_op(L1,BeforeWith,After),
   !,
   append(BeforeWith,[gid('clsCilkEnd',-1)|After],L2),
   !.

@write_sync(S,Shift,OShift,[SPC|ST],OSPC,T,OT,GID):-
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
         insert_ending_bracket(T,OT),
         !
      )
    );(
      =(OShift,Shift),=(OSPC,[SPC|ST]),=(OT,T),!
    )
   ).

@write_program(_,_,_,[]):-!.

@write_program(IShift,SPCS,S,[gid('clsCilkOper',GID)|T]):-
   db_content('prog',GID,[['op']]),
   db_content('args',GID,[['op',Op]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkOper',GID)|T],[_|T1],GID),
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
   write_program('',[SPC|ST],S,T1),
   !.

@write_program(Shift,SP,S,[gid('clsCilkComments',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(Shift,SP,S,[gid('clsCilkInclude',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(IShift,[SPC0|ST0],S,[gid('clsCilkBegin',GID)|T]):-
   db_content('prog',GID,[['{']]),
   (
    (predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->(
      write(S,SPC0),write(S,IShift),write(S,'{'),nl(S),
      write(S,SPC0),write(S,IShift),write(S,'  cilk_sync;'), nl(S),!,
      atom_concat(SPC0,IShift,SPC10),
      atom_concat(SPC10,'  ',SPC20),
      =(Shift,''),
      =([SPC|ST],[SPC20,SPC10,SPC0|ST0]),
      insert_ending_bracket([gid('clsCilkBegin',GID)|T],[_|T1]),
      !
    );(
      =(Shift,IShift),=([SPC|ST],[SPC0|ST0]),=(T1,T),!
    )
   ),
   write(S,SPC), write(S,Shift), write(S,'{'), nl(S),
   atom_concat(SPC,Shift,SPC1),
   atom_concat(SPC1,'  ',SPC2),
   write_program('',[SPC2,SPC1,SPC|ST],S,T1),
   !.

@write_program(_,[SPC2,SPC1,SPC|ST],S,[gid('clsCilkEnd',GID)|T]):-
   (
     (db_content('prog',GID,[['}']]), predicate_property(cilk_sync(_),'dynamic'), cilk_sync(GID))->(
       write(S,SPC2), write(S,'cilk_sync;'), nl(S), !
     );(
       true, !
     )
   ),
   write(S,SPC1), write(S,'}'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsCilkDo',GID)|T]):-
   db_content('prog',GID,[['do']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'do'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkWhile',GID)|T]):-
   db_content('prog',GID,[['while']]),
   db_content('args',GID,[['cond',Cond]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkWhile',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'while ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T1),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkFor',GID)|T]):-
   db_content('prog',GID,[['for']]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkFor',GID)|T],[_|T1],GID),
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
   write_program(Shift1,[SPC|ST],S,T1),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkIf',GID)|T]):-
   db_content('prog',GID,[['if']]),
   db_content('args',GID,[['cond',Cond]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkIf',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'if ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T1),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsCilkElse',GID)|T]):-
   db_content('prog',GID,[['else']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'else'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkSwitch',GID)|T]):-
   db_content('prog',GID,[['switch']]),
   db_content('args',GID,[['arg',Arg]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkSwitch',GID)|T],[_|T1],GID),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(Shift), write(S,'switch ( '), write(S,Arg), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T1),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsCilkAlternation',GID)|T]):-
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

@write_program(Shift,[SPC|ST],S,[gid('clsCilkTypedef',GID)|T]):-
   db_content('prog',GID,[['type']]),
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,'typedef '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkCVar',GID)|T]):-
   db_content('prog',GID,[[TYPE]]),
   member(TYPE,['struct','union']),
   !,
   db_content('args',GID,[['def',Def]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkCVar',GID)|T],[_|T1],GID),
   write(S,SPC), write(S,Shift), write(S,TYPE), write(S,' '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T1),
   !.

@write_program(IShift,SPCS,S,[gid('clsCilkReturn',GID)|T]):-
   db_content('prog',GID,[['return']]),
   db_content('args',GID,[['arg',Arg]]),
   write_sync(S,IShift,Shift,SPCS,[SPC|ST],[gid('clsCilkReturn',GID)|T],[_|T1],GID),
   write(S,SPC), write(S,Shift), write(S,'return '), write(S,Arg), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T1),
   !.

@write_program(Shift,SP,S,[gid('clsCilkPreproc',GID)|T]):-
   db_content('prog',GID,[['preproc']]),
   db_content('args',GID,[['body',Body]]),
   write(S,Body), nl(S),
   write_program(Shift,SP,S,T),
   !.

@write_program(_,[SPC|ST],S,[gid('clsCilkFunction',GID)|T]):-
   db_content('prog',GID,[['func']]),
   db_content('args',GID,L),
   member(['name',ID],L),
   member(['args',Args],L),
   member(['ret',Ret],L),
   !,
   write(S,SPC), write(S, Ret), write(S, ' '), write(S, ID), write(S,'( '), write(S,Args), write(S,' )'),
   write_program('',[SPC|ST],S,T),
   !.

% Формирование текста программы FName по загруженным данным + spawn/sync
@recreate_program(FName):-
  open(FName,write,S),
  global_trace(TR),
  write_program('',[''],S,TR),
  close(S).

@put_all_spawns:-
  retractall(cilk_spawn(_)),
  predicate_property(cilk_fprocs(_,_,_),'dynamic'),
  cilk_fprocs(_,_,GIDs),
  member(GID,GIDs),
  asserta(cilk_spawn(GID)),
  fail.

@put_all_spawns:-!.

@create_all_syncs:-
  predicate_property(cilk_function(_,_,_),'dynamic'),
  cilk_function(Fun,GID,NPrms),
  once(create_syncs(Fun,GID,NPrms)),
  get_ftime(Fun,NPrms,_), % Time
%  write(Fun),write(':'),write(Time),nl,
  fail.

@create_all_syncs:-
%  write('--------------'), nl,
  !.

@iterative_syncs_times(0):-!.

% Итерационный алгоритм последовательного добавления syncs и пересчета времен исполнения функций. Алгоритм заканчивается, когда
% времена исполнения практически перестают меняться (+/-1) или превышено число итераций N
@iterative_syncs_times(N):-
  retractall(cilk_retime),
  retractall(cilk_spawn_time(_,_)),
  create_all_syncs,
  cilk_retime,
  !,
  N1 is N-1,
  iterative_syncs_times(N1).

@iterative_syncs_times(_):-!.

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

% Определяем неэффективные spawn-запуски
@remove_spawns:-
  predicate_property(cilk_spawn(_),'dynamic'),
  cilk_spawn(GID),
  cilk_op(_,GID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)]),
  length(Prms,NPrms),
  cilk_function(Fun,FunGID,NPrms),
  cilk_ftime(Fun,FunGID,BaseTime),
  cilk_spawn_time(GID,Timings),
  call(avr(Timings,AvrTime)),
  g_read('$SpawnTime', SpawnTime),
  ParExecTime is AvrTime+SpawnTime, % С учетом расходов на собственно spawn
  ( % Принятие решения об исключении spawn
    >(ParExecTime,BaseTime)->(
      once(cilk_respawn(List)),
      retractall(cilk_respawn(_)),
      asserta(cilk_respawn([GID|List]))
    );
    true
  ),
  fail.

@remove_spawns:-!.

% Удаляем пометки spawn с операторов, GIDы которых прописаны в параметре-списке
@delete_spawns([]):-!.

@delete_spawns([H|T]):-
  retractall(cilk_spawn(H)),
  delete_spawns(T).

@process_syncs_and_spawns(0):-!.

% Главный цикл распараллеливания. Предварительно расставлены все возможные spawns. Итеративный циклический алгоритм. Завершается,
% когда заканчиваются подлежащие удалению spawns или превышено число итераций N
@process_syncs_and_spawns(N):-
  iterative_syncs_times(15), % Расставляем syncs (там, где еще не расставлены) и предсказываем время исполнения функций
  retractall(cilk_respawn(_)),
  asserta(cilk_respawn([])),
  remove_spawns, % Определяем список spawns (в списке-параметре факта cilk_respawn([...])), которые дают отрицательный эффект
  % для общего времени работы. Они подлежат удалению
  cilk_respawn([First|Rest]), % Если список удаляемых spawns не пуст
  delete_spawns([First|Rest]), % Удаляем пометки spawn для неэффективных случаев
  !,
  N1 is N-1,
  process_syncs_and_spawns(N1).

@process_syncs_and_spawns(_):-!.

@has_spawns(GID):-
   predicate_property(cilk_spawn(_),'dynamic'),
   cilk_spawn(GID),
   !.

@has_spawns(GID):-
   cilk_op(_,GID,_,IGIDs,_),
   !,
   member(IGID,IGIDs),
   has_spawns(IGID)->
    (true,!);
    fail.

@remove_syncs(GID):-
   predicate_property(cilk_sync(_),'dynamic'),
   once(cilk_sync(GID)),
   retractall(cilk_sync(GID)).

@remove_syncs(GID):-
   cilk_op(_,GID,_,IGIDs,_),
   !,
   member(IGID,IGIDs),
   remove_syncs(IGID),
   fail.

@remove_syncs(_):-!.

% Удаление syncs из функций, в которых уже нет spawns
@remove_unnecessary_syncs:-
  cilk_function(_,FunGID,_),
  \+ call(has_spawns(FunGID)),
  call(remove_syncs(FunGID)),
  fail.

@remove_unnecessary_syncs:-!.

@processing:-
  g_assign('$DefFTime', 15.0), % Время исполнения функции/процедуры по умолчанию (внешней или внутренней до расчета)
  g_assign('$SpawnTime', 5.0), % Время, затрачиваемое мастер-процессом на ответвление spawn-процесса
  g_assign('$DefOperTime', 1.0), % Время исполнения элементарного математического выражения без функций по умолчанию
  g_assign('$SyncTime', 5.0), % Время, затрачиваемое собственно вызовом sync (без ожидания)
  prepare_cilk,
  put_all_spawns,
  retractall(cilk_sync(_)),
  process_syncs_and_spawns(5),
  remove_unnecessary_syncs,
  (
   (predicate_property(cilk_auto_for,'dynamic'), cilk_auto_for)->handle_fors;true
  ),
  recreate_program('_cilk.cpp').

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

@cilk_debug:-
  asserta(global_trace([])),
  collect_global_trace,
  processing.

@goal:-
  cilk_debug.
};

#endif
