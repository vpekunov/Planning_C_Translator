#ifndef __GPU_LOOP_COMPILE_H__
#define __GPU_LOOP_COMPILE_H__

#parse(clsGPUProgram,clsGPUSpace,clsGPUInclude,clsGPUPreproc,clsGPUComments,clsGPUTypedef,clsGPUCVar,clsGPUFunction,clsGPUFor,clsGPUSwitch,clsGPUWhile,clsGPUIf,clsGPUElse,clsGPUDo,clsGPUAlternation,clsGPUReturn,clsGPUOper,clsGPUBegin,clsGPUEnd,clsGPUTerminator)

#def_pattern clsGPUAlternation => [prog] ('clsGPUAlternation', gid(), /root/TYPE/@Value, [['arg', /root/CASE/@Value]]) {
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

#def_pattern clsGPUBegin => [prog] ('clsGPUBegin', gid(), '{', '') {
  (((^)|(\;)+|\}|\{|\\n|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\{)
    (\s|\\t)*
  @end
};

#def_pattern clsGPUComments => [comment] ('clsGPUComments', gid(), /root/CONTENT/@Value) {
  @begin
    ((\/\/([^\\]*)->{CONTENT}(\\n))|(\/\*(.*?)->{CONTENT}\*\/))
  @end
};

#def_pattern clsGPUCVar => [prog] ('clsGPUCVar', gid(), /root/TYPE/@Value, [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (struct|union)->{TYPE}(\\n|\s|\\t)+
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')})
    (\s|\\t)*
  @end
};

#def_pattern clsGPUDo => [prog] ('clsGPUDo', gid(), 'do', '') {
  (((^)|(\;)+|\}|\{|\)|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (do)
  @end
  (\s|\\t)*
  ((\s|\{|\\n|\\t))
  (\s|\\t)*
};

#def_pattern clsGPUElse => [prog] ('clsGPUElse', gid(), 'else', '') {
  (((\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (else)
  @end
  (\s|\\t)*
  ((\s|\\t|\{|\\n))
  (\s|\\t)*
};

#def_pattern clsGPUEnd => [prog] ('clsGPUEnd', gid(), '}', '') {
  (((\;)+|\}|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    ()->{GID}
    (\s|\\t)*
    (\})
    (\s|\\t)*
  @end
};

#def_pattern clsGPUFor => [prog] ('clsGPUFor', gid(), 'for', [['init', /root/INITF/@Value],['init', /root/INITN/@Value],['cond', /root/COND/@Value],['chng', /root/CHNGF/@Value],['chng', /root/CHNGN/@Value]]) {
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

#def_pattern clsGPUFunction => [prog] ('clsGPUFunction', gid(), 'func', [['arg', //FIRST_REF/@Value], ['type', //FIRST_TYPE/@Value], ['arg', //FIRST/@Value], ['idxs', //FIRST_IDXS/@Value], ['arg', //OTHER_REF/@Value], ['type', //OTHER_TYPE/@Value], ['arg', //OTHER/@Value], ['idxs', //OTHER_IDXS/@Value], ['arg', //THREEP/@Value], ['args', /root/ARGS/@Value], ['ret', /root/RETTYPE/@Value], ['name', /root/ID/@Value]]) {
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

#def_pattern clsGPUIf => [prog] ('clsGPUIf', gid(), 'if', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (if(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUInclude => [include] ('clsGPUInclude', gid(), /root/FILE/@Value) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#include(\s|\\t)*\x22([^\x22]+)->{FILE}\x22(\\n|($))
    )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUOper => [prog] ('clsGPUOper', gid(), 'op', [['op', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    ((([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUPreproc => [prog] ('clsGPUPreproc', gid(), 'preproc', [['body', /root/BODY/@Value]]) {
  ((^)|\\n)(\s|\\t)*
  @begin
    (\s|\\t)*
    (\#([^\\]*\\\\\\n)*[^\\]*(\\n|($))
    )->{BODY}
    (\s|\\t)*
  @end
};

#def_pattern clsGPUReturn => [prog] ('clsGPUReturn', gid(), 'return', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (return(\\n|\s|\\t)+(([^\;]*)->{EXPR}\;)?=>{Predicates.BAL($,';')}
    )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUSwitch => [prog] ('clsGPUSwitch', gid(), 'switch', [['arg', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (switch(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{EXPR}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUTypedef => [prog] ('clsGPUTypedef', gid(), 'type', [['def', /root/EXPR/@Value]]) {
  (((^)|(\;)+|\}|\)|\{|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    typedef((\\n|\s|\\t)+)
    (((.{1,2048}?)->{EXPR}\;)?=>{Predicates.BAL($,';')}
         )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUWhile => [prog] ('clsGPUWhile', gid(), 'while', [['cond', /root/COND/@Value]]) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (while(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
  @end
};

#def_pattern clsGPUTerminator => parallelize (gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() parallelize(AfterLastID) {
@goal:-brackets_off.

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
  once(into_paired_list_f('type', TYPE1, TYPE1L)),
  once(into_paired_list_f('arg', REF1, REF1L)),
  once(into_paired_list_f('arg', NM1, NM1L)),
  once(into_paired_list_f('idxs', IDXS1, IDXS1L)),
  once(make_fargs(REF1L, TYPE1L, NM1L, IDXS1L, L1)),
  once(strip_list_f(L1, L11)),
  once(into_paired_list_f('type', TYPEN, TYPENL)),
  once(into_paired_list_f('arg', REFN, REFNL)),
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

@glob_prefixate([var(H,TP)|T],[global(H,TP)|T1]):-
   glob_prefixate(T,T1).

@get_glob_lazies(Fun,NPrms,GP,LP,ILP):-
   gpu_function(Fun,GID,NPrms),
   predicate_property(gpu_fanalyzed(_,_,_,_,_),'dynamic'),
   gpu_fanalyzed(Fun,GID,Globs,LP,ILP),
   glob_prefixate(Globs, GP),
   !.

@get_glob_lazies(_,_,[],0,[]):-!.

@get_ftime(Fun,NPrms,T):-
   gpu_function(Fun,GID,NPrms),
   predicate_property(gpu_ftime(_,_,_),'dynamic'),
   gpu_ftime(Fun,GID,T),
   !.

@get_ftime(_,_,T):-  % Содержит время исполнения функции по умолчанию
  g_read('$DefFTime',T),
  !.

@put_ftime(Fun,NPrms,T):-
   gpu_function(Fun,GID,NPrms),
   (
    (predicate_property(gpu_ftime(_,_,_),'dynamic'), gpu_ftime(Fun,GID,T0))->(
         D is T-T0,
         (
          ;(<(D,-1),>(D,1))->(
             retractall(gpu_ftime(Fun,GID,_)),
             asserta(gpu_ftime(Fun,GID,T)),
             retractall(gpu_retime),
             asserta(gpu_retime)
            );
            true
         )
       );(
         retractall(gpu_retime),
         asserta(gpu_retime),
         asserta(gpu_ftime(Fun,GID,T))
       )
   ),
   !.

@put_for_time(GID,T):-
   (
    (predicate_property(gpu_for_time(_,_),'dynamic'), gpu_for_time(GID,T0))->(
         D is T-T0,
         (
          ;(<(D,-1),>(D,1))->(
             retractall(gpu_for_time(GID,_)),
             asserta(gpu_for_time(GID,T))
            );
            true
         )
       );(
         asserta(gpu_for_time(GID,T))
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
% Если уже есть результаты предварительного анализа в фактах gpu_fanalyzed, то данные о "ленивости" берутся из них, если же их
% нет, то считается, что глобальных ленивых переменных для этой функции нет, а ленивыми являются все &|*-параметры
% Во втором параметре принимает список разобранных параметров, каждый из которых = список токенов
% В третьем параметре возвращает список ленивых переменных [global(имя,тип),...,par(функция,имя_параметра,переданная переменная,тип,индексы),...]
% В четвертом параметре возвращается список имен, переданных в неленивые &|* - параметры
% В пятом параметре принимается список-карта переданных значений. Элемент = множество из одного элемента (имя переданной переменной)
%  или пустое множество (если в параметре передано выражение).
% В шестом параметре возвращается список имен переданных в качестве параметров переменных, значения которых используются на чтение в функции
@get_lazies(Fun, Params, [], _, ParSingleMap, _):-
   predicate_property(gpu_farg(_,_,_,_,_,_),'dynamic')->(
     length(Params,N),
     once(gpu_farg(Fun,N,_,_,_,_)),
     asserta(counter(0)),
     get_glob_lazies(Fun,N,GP,LP,ReadParams),
     asserta(params(GP)),
     asserta(isingles([])),
     asserta(refs([])),
     gpu_farg(Fun,_,REF,V,_,_),
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
   predicate_property(gpu_farg(_,_,_,_,_,_),'dynamic')->(
     once(gpu_farg(Fun,NPrms,_,_,Type,Idxs)),
     asserta(counter(0)),
     asserta(params([])),
     gpu_farg(Fun,_,REF,V,_,_),
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
   ((gpu_function(Fun,_,_),=(OUTS3,[]));check_arg(P,OUTS3)),
   check_arg(P,V),
   !,
   get_fun_params(Fun,Rest,R,T,INS2,MAP,OUTS2,FUNS2,LZ2),
%   (
%    =(V,[Single])->
%      subtract(INS1,[Single],INSQ);
      =(INSQ,INS1),
%   ),
   union(INSQ,INS2,INS),
   union(OUTS1,OUTS2,OUTSK), union(OUTSK,OUTS3,OUTS), append(FUNS1,FUNS2,FUNS), union(LZ1,LZ2,Lazies),
   !.

@get_fun_params(Fun,L,[')'|Rest],[Item],INS,[V],OUTS,FUNS,Lazies):-
   get_balanced(0,L,[',',')'],Item,[')'|Rest]),
   get_expr(Item,INS1,OUTS0,FUNS,Lazies),
   ((gpu_function(Fun,_,_),=(OUTS3,[]));check_arg(Item,OUTS3)),
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
   declaration(D),
   append(D,['*'],DD),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*',id(V1)],L),
   declaration(D),
   append(D,['*','*'],DD),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['*','*','*',id(V1)],L),
   declaration(D),
   append(D,['*','*','*'],DD),
   !.

@analyze_expr(L,[],[V1],[var(V1,type(DD,[]))],[],[],[],[]):-
   append(D,['&',id(V1)],L),
   declaration(D),
   append(D,['&'],DD),
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
   member(A,['=',',','[']),
   !,
   append(D,['*'],DD),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   append(D,['*','*'],DD),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['*','*','*',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   append(D,['*','*','*'],DD),
   !,
   analyze_list_expr(intros(DD),[id(V1),A|T1],INS,OUTS0,NEWS,FUNS,PROCS,REFS,Lazies),
   union(OUTS0,[V1],OUTS),
   !.

@analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,Lazies):-
   append(D,['&',id(V1),A|T1],L),
   declaration(D),
   member(A,['=',',','[']),
   !,
   append(D,['&'],DD),
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

@get_params_length([[type,_]|T], N):-
   get_params_length(T,N),
   !.

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

@prepare_gpu_function(_,_,[]):-!.

@prepare_gpu_function(Name,N,[[name,Name]|T]):-
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[args,_]|T]):-
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[ret,_]|T]):-
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[type,TP],[arg,V],[idxs,Idxs]|T]):-
   \+ atom_length(Idxs,0),
   assertz(gpu_farg(Name,N,'[]',V,TP,Idxs)),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[arg,'&'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(gpu_farg(Name,N,'&',V,TP,[])),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[arg,'*'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(gpu_farg(Name,N,'*',V,TP,[])),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[arg,'**'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(gpu_farg(Name,N,'**',V,TP,[])),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[arg,'***'],[type,TP],[arg,V],[idxs,_]|T]):-
   assertz(gpu_farg(Name,N,'***',V,TP,[])),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_function(Name,N,[[type,TP],[arg,V],[idxs,'']|T]):-
   assertz(gpu_farg(Name,N,'',V,TP,[])),
   !,
   prepare_gpu_function(Name,N,T).

@prepare_gpu_functions:-
   global_trace(TR),
   db_content('prog',GID,[[func]]),
   db_content('args',GID,Params),
   once(append(_,[gid('clsGPUFunction',GID),gid('clsGPUBegin',_)|_],TR)),
   member([name,Name],Params),
   get_params_length(Params,N),
   \+ =(N,infinity),
   N1 is N-3, % -args, -ret, -name
   asserta(gpu_function(Name,GID,N1)),
   call(prepare_gpu_function(Name,N1,Params)),
   fail.

@prepare_gpu_functions:-!.

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
   member(Type,['clsGPUWhile','clsGPUSwitch','clsGPUIf','clsGPUReturn','clsGPUOper']),
   !,
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

@prepare_ops('clsGPUAlternation',GID,[arg(INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES,[L])]):-
   db_content('args',GID,[[_,Opnd]]),
   !,
   parse_expr(Opnd,L),
   !,
   analyze_expr(L,INS,OUTS,NEWS,FUNS,PROCS,REFS,LAZIES),
   !.

% (default:) in switch-case
@prepare_ops('clsGPUAlternation',_,[arg([],[],[],[],[],[],[],[])]):-
   !.

@prepare_ops('clsGPUFor',GID,OPL):-
   db_content('args',GID,L),
   prepare_ifor(L,'init',OPL1),
   prepare_ifor(L,'cond',OPL2),
   prepare_ifor(L,'chng',OPL3),
   !,
   append(OPL1,OPL2,OPLP), append(OPLP,OPL3,OPL),
   !.

% Помещает в базу факт gpu_op(Class,GID1,GID2,IDs,Ops) только в том случае, если его еще в базе не было,
% или он был, но с другими ops. В последнем случае устанавливается флаг-факт gpu_recalculate. Это требуется
% для нормальной работы итеративной процедуры уточнения состава ленивых переменных/параметров для каждой функции
@put_gpu_op(Class,GID1,GID2,IDs,Ops):-
   (
      (predicate_property(gpu_op(_,_,_,_,_),'dynamic'), gpu_op(Class,GID1,GID2,IDs,Ops1))->(
        =(Ops,Ops1)->(
          true, !
        );(
          retractall(gpu_op(Class,GID1,GID2,_,_)),
          (
           (predicate_property(gpu_reanalyze,'dynamic'), gpu_reanalyze)->(
             true, !
           );(
             asserta(gpu_reanalyze)
           )
          ),
          asserta(gpu_op(Class,GID1,GID2,IDs,Ops))
        )
      );(
        asserta(gpu_op(Class,GID1,GID2,IDs,Ops))
      )
   ),
   !.

@get_gpu_fseq([gid('clsGPUEnd',GID)|Rest],[gid('clsGPUEnd',GID)|Rest],[]):-!.

@get_gpu_fseq(L,Rest,[GID|IDT]):-
   get_gpu_fop(L,Rest0,GID),
   !,
   get_gpu_fseq(Rest0,Rest,IDT),
   !.

@get_gpu_fop([gid('clsGPUBegin',GID1)|T],Rest,GID1):-
   get_gpu_fseq(T,[gid('clsGPUEnd',GID2)|Rest],IDs),
   !,
   put_gpu_op('clsGPUBegin',GID1,GID2,IDs,[]),
   !.

@get_gpu_fop([gid(Type,GID)|T],Rest,GID):-
   member(Type,['clsGPUFor','clsGPUSwitch','clsGPUWhile']),
   !,
   get_gpu_fop(T,Rest,OPID),
   !,
   prepare_ops(Type,GID,OPL),
   put_gpu_op(Type,GID,-1,[OPID],OPL),
   !.

@get_gpu_fop([gid('clsGPUDo',GID)|T],Rest,GID):-
   get_gpu_fop(T,[gid('clsGPUWhile',GID1),gid('clsGPUOper',EmptyGID)|Rest],OPID),
   db_content('args',EmptyGID,[[op,'']]),
   !,
   prepare_ops('clsGPUWhile',GID1,OPL),
   put_gpu_op('clsGPUDo',GID,GID1,[OPID],OPL),
   !.

@get_gpu_fop([gid('clsGPUIf',GID)|T],Rest,GID):-
   get_gpu_fop(T,Rest0,OPID0),
   !,
   prepare_ops('clsGPUIf',GID,OPL),
   (
    =(Rest0,[gid('clsGPUElse',GID1)|Rest1])->(
       get_gpu_fop(Rest1,Rest,OPID1),
       put_gpu_op('clsGPUIf',GID,GID1,[OPID0,OPID1],OPL)
    );(
       put_gpu_op('clsGPUIf',GID,-1,[OPID0],OPL),
       =(Rest,Rest0)
    )
   ),
   !.

@get_gpu_fop([gid('clsGPUPreproc',GID)|T],T,GID):-
   put_gpu_op('clsGPUPreproc',GID,-1,[],[]),
   !.

@get_gpu_fop([gid(Type,GID)|T],T,GID):-
   prepare_ops(Type,GID,OPL),
   put_gpu_op(Type,GID,-1,[],OPL),
   !.

@get_gpu_fprocs([],[]):-!.

@get_gpu_fprocs([GID|T],[GID|TT]):-
   gpu_op('clsGPUOper',GID,_,[],[arg(_,_,_,_,[proc(Name,_)],_,_,_)]),
   gpu_function(Name,_,_),
   !,
   get_gpu_fprocs(T,TT),
   !.
   
@get_gpu_fprocs([GID|T],PGIDS):-
   gpu_op(_,GID,_,LGIDs,_),
   !,
   get_gpu_fprocs(LGIDs,PGIDS0),
   get_gpu_fprocs(T,PGIDS1),
   !,
   append(PGIDS0,PGIDS1,PGIDS),
   !.

@build_gpu_function(Fun,FGID,Body):-
   get_gpu_fop(Body,[],OPID),
   put_gpu_op('clsGPUFunction',FGID,-1,[OPID],[]),
   get_gpu_fprocs([OPID],ProcsGIDs),
   asserta(gpu_fprocs(Fun,FGID,ProcsGIDs)),
   !.

% Анализ (структурный, в глубину) всех функций с разбором выражений, результаты которого попадают в gpu_op
@build_gpu_functions:-
   global_trace(TR),
   retractall(gpu_fprocs(_,_,_)),
   !,
   (
    predicate_property(gpu_function(_,_,_),'dynamic')->(
     (
      gpu_function(Fun,GID,_),
      once(append(_,[gid('clsGPUFunction',GID)|T],TR)),
      bypass_complex(T,Body,_),
      call(build_gpu_function(Fun,GID,Body)),
      fail);
     true,!
    );(
     true,!
    )
   ).

@get_globals([],[]):-!.

@get_globals([gid('clsGPUCVar',GID)|T],[var(V,type(TP,IDXS))|T1]):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   rbypass_var(L,V,TP,_,_,_,_,_),
   append(TP,[id(V)|IDXS],L),
   get_globals(T,T1).

@get_globals([gid('clsGPUOper',GID)|T],T1):-
   db_content('args',GID,[[_,Arg]]),
   !,
   parse_expr(Arg,L),
   analyze_expr(L,_,_,NEWS,_,_,_,_),
   get_globals(T,T0),
   append(NEWS,T0,T1),
   !.

@get_globals([gid('clsGPUFunction',_)|T],T1):-
   bypass_complex(T,_,After),
   get_globals(After,T1),
   !.

@get_globals([_|T],T1):-
   get_globals(T,T1).

@find_globals:-
   global_trace(TR),
   get_globals(TR,GLOBS),
   asserta(gpu_globals(GLOBS)),
   !.

@extract_var_names([],[]):-
   !.

@extract_var_names([var(Name,_)|T],[Name|T1]):-
   extract_var_names(T,T1),
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

% ReadParams -- читаемые в самой функции ее ленивые параметры (не только выходные, но и входные)
@analyze_one_flazies([GID|GIDS],Globs,Pars,Locals,GLazies,PLazies,ReadParams):-
   gpu_op(_,GID,_,IGIDs,Ops),
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
   gpu_function(Fun,GID,NPrms),
   !,
   (
    (predicate_property(gpu_fanalyzed(_,_,_,_,_),'dynamic'), gpu_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams))->(
     true,!
     );(
     get_fparams(lazy,Fun,NPrms,LPars0),
     !,
     gpu_globals(GlobVars),
     extract_var_names(GlobVars,Glob0),
     !,
     asserta(gpu_fanalyzed(Fun,GID,[],LPars0,LPars0)),
     analyze_one_flazies([GID],Glob0,LPars0,[],GLazies,PLazies,ReadParams),
     retractall(gpu_fanalyzed(Fun,GID,[],_,_)),
     asserta(gpu_fanalyzed(Fun,GID,GLazies,PLazies,ReadParams)),
     !
    )
   ).

% Определение выходных переменных (глобальных и потенциально модифицируемых параметров) для каждой функции. Для этого проводится
% структурный анализ функции в глубину (с отслеживанием локально декларированных переменных, изменение которых нас здесь не интересует),
% выявляются модифицируемые переменные. Модифицируемые глобалы и параметры попадают в gpu_fanalyzed
@analyze_gpu_functions:-
   (
    predicate_property(gpu_function(_,_,_),'dynamic')->(
     (
      gpu_function(Fun,_,N),
      call(analyze_flazies(Fun,N,_,_,_)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Итерационное сходящееся уточнение состава ленивых переменных/параметров функций (gpu_fanalyzed). На каждой итерации
% для каждой функции уточняется список модифицируемых глобальных переменных и &|*-параметров. Это делается в analyze_gpu_functions.
% Это уточнение может влиять на другие функции, вызывающие уточненные. Сначала считается, что функция модифицирует все свои &|*-параметры,
% они входят в соответствующие списки gpu_fanalyzed, потом эти списки урезаются, в то время как списки глобальных переменных расщиряются.
% Проходит "волна" уточнений, в результате которой, например, функции int p1(int &x) { p2(x); }, int p2(int & x) { cout << x; } в последнем
% приближении уже не имеют выходных ленивых значений вообще, в то время как функции int p1() { p2(); }, int p2() { X = 11; } имеют один
% ленивый результат -- глобальную переменную X.
% После очередного уточнения, выполняется перестройка gpu_op-фактов, в которых выполняется новый разбор выражений с учетом новых данных
% о ленивости. Если при этом изменится хоть один факт, то устанавливается gpu_reanalyze, что свидетельствует о необходимости как минимум
% еще одной итерации.
@iterative_build_funs:-
   retractall(gpu_reanalyze),
   build_gpu_functions,
   (
    (predicate_property(gpu_reanalyze,'dynamic'), gpu_reanalyze)->(
      retractall(gpu_fanalyzed(_,_,_,_,_)),
      analyze_gpu_functions,
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
    (predicate_property(gpu_fpure(_),'dynamic'), gpu_fpure(Name));
    (
     predicate_property(gpu_function(_,_,_),'dynamic'),
     gpu_function(Name,_,NPrms),
     predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),
     gpu_fdependent(Name,NPrms,f,_)
    )
   ),
   !,
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
   gpu_op(_,GID,_,LGIDs,Exprs),
   !,
   get_fexpr_deps(Exprs),
   !,
   get_fblock_deps(LGIDs),
   !,
   get_fblock_deps(T),
   !.

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

@mark_flist_deps([]):-
   !.

@mark_flist_deps([V|T]):-
   =..(V,[_,Name,Prms]),
   length(Prms,NPrms),
   !,
   (
    (predicate_property(gpu_fpure(_),'dynamic'), gpu_fpure(Name));
    (
     predicate_property(gpu_function(_,_,_),'dynamic'),
     gpu_function(Name,GID,NPrms),
     predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),
     gpu_fdependent(Name,NPrms,f,_),
     (
      (predicate_property(gpu_do_not_worry(_,_,_),'dynamic'), gpu_do_not_worry(Name,GID,NPrms))->
        true;
        ( asserta(gpu_do_not_worry(Name,GID,NPrms)), mark_fblock_deps([GID]) )
     )
    )
   ),
   !,
   mark_flist_deps(T),
   !.

@mark_fexpr_deps([]):-
   !.

@mark_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,[expr],_,_,_]),
   !,
   mark_flist_deps(FUNS),
   mark_fexpr_deps(T),
   !.

@mark_fexpr_deps([V|T]):-
   =..(V,[_,_,_,_,FUNS,PROCS,_,_,_]),
   !,
   mark_flist_deps(FUNS),
   !,
   mark_flist_deps(PROCS),
   mark_fexpr_deps(T),
   !.

@mark_fblock_deps([]):-
   !.

@mark_fblock_deps([GID|T]):-
   gpu_op(_,GID,_,LGIDs,Exprs),
   !,
   mark_fexpr_deps(Exprs),
   !,
   mark_fblock_deps(LGIDs),
   !,
   mark_fblock_deps(T),
   !.

% Содержит ли блок разыменование указателей
@block_has_no_derefs([]):-
   !.

@block_has_no_derefs([GID|T]):-
   gpu_op(_,GID,_,LGIDs,Exprs),
   !,
   exprs_has_no_derefs(Exprs),
   !,
   block_has_no_derefs(LGIDs),
   block_has_no_derefs(T).

@exprs_in_outs([],[],[],[]):-
   !.

@exprs_in_outs([E|T],Ins,Outs,News):-
   =..(E,[_,Ins0,Outs0,News0,_,_,_,_,_]),
   !,
   extract_var_names(News0, NewsE),
   !,
   exprs_in_outs(T,Ins1,Outs1,News1),
   union(Ins0,Ins1,Ins),
   union(Outs0,Outs1,Outs),
   union(NewsE,News1,News),
   !.

@for_in_outs([],[],[],[]):-
   !.

@for_in_outs([GID|T],Ins,Outs,News):-
   gpu_op(C,GID,_,LGIDs,Exprs),
   !,
   (
    =(C,'clsGPUFor')->
      (exprs_in_outs(Exprs,Ins0,_,News0),=(Outs0,[]));
      exprs_in_outs(Exprs,Ins0,Outs0,News0)
   ),
   !,
   for_in_outs(LGIDs,Ins1,Outs1,News1),
   for_in_outs(T,Ins2,Outs2,News2),
   !,
   union(Ins0,Ins1,InsA), union(InsA,Ins2,Ins),
   union(Outs0,Outs1,OutsA), union(OutsA,Outs2,Outs),
   union(News0,News1,NewsA), union(NewsA,News2,News),
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
   gpu_op(_,GID,_,LGIDs,Exprs),
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
write(V),write(FIdxs),
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
   once(for_in_outs(LGIDs,Ins,Outs0,News)),
   subtract(Outs0,News,Outs),
   get_var_idxs(LGIDs,VarIdxs),
   check_idxs(Outs,VarIdxs),
   !,
   filter_idxs(Counter,VarIdxs,FIdxs),
   !,
   check_outs_by_idxs(Outs,Ins,FIdxs).

% Анализ возможности распараллелить for
@analyze_for(GID):-
   gpu_op('clsGPUFor',GID,_,LGIDs,Exprs),
   (
    (predicate_property(gpu_for_time(_,_),'dynamic'),gpu_for_time(GID,T))->
       (g_read('$SpawnTime',TSP), g_read('$SyncTime',TSY), TPAR is TSP + 2*T + TSY, TSEQ is 8*T, TPAR < TSEQ);
       true
   ),
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
   ( predicate_property(gpu_for_interface(_,_),'dynamic'), gpu_for_interface(GID,_) ),
   once(block_has_no_derefs(LGIDs)),
   once(get_fblock_deps(LGIDs)),
   once(for_content(Counter,LGIDs)),
   once(mark_fblock_deps(LGIDs)),
   asserta(gpu_for(GID)),
   !.

% Нельзя распараллелить for
@analyze_for(GID):-
   gpu_op('clsGPUFor',GID,_,_,_),
   !.

@get_fors([],_):-!.

@get_fors([GID|T],_):-
   gpu_op(_,GID,_,[],_),
   !,
   get_fors(T,t),
   !.
   
% Пытаемся распараллелить самый внешний цикл
@get_fors([GID|T],Flag):-
   gpu_op('clsGPUFor',GID,_,[LGID],_),
   gpu_op('clsGPUFor',LGID,_,_,_),
   !,
   (
    =(Flag,t)->(
      analyze_for(GID),
      (
       (predicate_property(gpu_for(_),'dynamic'),gpu_for(GID))->
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
   gpu_op('clsGPUFor',GID,_,LGIDs,_),
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
   gpu_op(_,GID,_,LGIDs,_),
   !,
   get_fors(LGIDs,t),
   !,
   get_fors(T,t),
   !.
   
% Обработка и распараллеливание циклов в функции Fun
@handle_fors_in_function(FGID):-
   gpu_op('clsGPUFunction',FGID,_,LGIDs,_),
   get_fors(LGIDs,t),
   !.

% Обработка и распараллеливание подходящих циклов в каждой функции на уровне Level
@handle_fors_level(Level):-
   (
    predicate_property(gpu_function(_,_,_),'dynamic')->(
     (
      gpu_function(Name,GID,NPrms),
      gpu_fdependent(Name,NPrms,_,Level),
      \+ gpu_do_not_worry(Name,GID,NPrms),
      call(handle_fors_in_function(GID)),
      fail);
     true,!
    );(
     true,!
    )
   ).

% Обработка и распараллеливание подходящих циклов
@handle_fors(Level,Max):-
   once(handle_fors_level(Level)),
   !,
   Level1 is Level + 1,
   !,
   (
    ==(Level,Max)->
      true;
      ( handle_fors(Level1,Max), ! )
   ),
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
   gpu_op(_,GID,_,LGIDs,Exprs),
   get_expr_deps(NamePath,Exprs),
   get_block_deps(NamePath,LGIDs),
   !,
   get_block_deps(NamePath,T),
   !.

@mark_deps([]):-
   !.

@mark_deps([path(Name,NPrms,Level)|T]):-
   (
    (predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),gpu_fdependent(Name,NPrms,t,_))->(
      true,!
    );(
      retractall(gpu_fdependent(Name,NPrms,_,_)), asserta(gpu_fdependent(Name,NPrms,t,Level))
    )
   ),
   mark_deps(T).

@get_fdeps(Name,NamePath,NPrms):-
   member(path(Name,NPrms,Level),NamePath),
   !,
% Важно! Кольцо рекурсии даже для независимых функций считается ЗАВИСИМОСТЯМИ, поскольку векторные вычислители с таким кольцом могут не работать!
   retractall(gpu_fdependent(Name,NPrms,_,_)), asserta(gpu_fdependent(Name,NPrms,t,Level)),
   !.

@get_fdeps(Name,NamePath,NPrms):-
   gpu_function(Name,GID,NPrms),
   gpu_op('clsGPUFunction',GID,_,LGIDs,_),
   (
    (predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),gpu_fdependent(Name,NPrms,_,_))->(
      true,!
    );(
      (
        =(NamePath,[])->
         =(Level,0);
         (=(NamePath,[path(_,_,Level0)|_]), Level is Level0 + 1)
      ),
      !,
      get_block_deps([path(Name,NPrms,Level)|NamePath],LGIDs),
      (
       (predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),gpu_fdependent(Name,NPrms,_,_))->(
         true,!
       );(
         asserta(gpu_fdependent(Name,NPrms,f,Level))
       )
      )
    )
   ),
   (
     (predicate_property(gpu_fdependent(_,_,_,_),'dynamic'),gpu_fdependent(Name,NPrms,t,_))->
        mark_deps(NamePath);
        true
   ).

@get_fdeps(Name,NamePath,NPrms):-
   \+ gpu_function(Name,_,NPrms),
   (
    (predicate_property(gpu_fpure(_),'dynamic'),gpu_fpure(Name))->
       true;
       mark_deps(NamePath)
   ),
   !.

% Определение зависимостей функций от внешних функций
@find_dependents:-
   (
    predicate_property(gpu_function(_,_,_),'dynamic')->(
     (
      gpu_function('main',_,NPrms),
      call(get_fdeps('main',[],NPrms)),
      gpu_function(Name,_,NPrms),
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
   gpu_op(_,_,_,GIDs,_),
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
    (predicate_property(gpu_fpure(_),'dynamic'),gpu_fpure(F))->
       true;
       asserta(gpu_fpure(F))
   ),
   !,
   analyze_pragma_pure(T).

% Очистка + Загрузка необходимых данных перед анализом
@prepare_data:-
   retractall(db_content(_,_,_)),
   retractall(gpu_function(_,_,_)),
   retractall(gpu_fdependent(_,_,_,_)),
   retractall(gpu_fpure(_)),
   retractall(gpu_farg(_,_,_,_,_,_)),
   retractall(gpu_fprocs(_,_,_)),
   retractall(gpu_op(_,_,_,_,_)),
   retractall(gpu_globals(_)),
   retractall(gpu_fanalyzed(_,_,_,_,_)),
   retractall(gpu_ftime(_,_,_)),
   retractall(gpu_for_time(_,_)),
   asserta(gpu_do_not_worry('','','')), retractall(gpu_do_not_worry(_,_,_)),
   asserta(gpu_for_interface('','')), retractall(gpu_for_interface(_,_)),
   asserta(gpu_retime), retractall(gpu_retime),
   asserta(gpu_reanalyze), retractall(gpu_reanalyze),
   asserta(gpu_for('')), retractall(gpu_for(_)),
   retractall(gpu_break(_)),
   retractall(gpu_continue(_)),
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
   prepare_gpu_functions,
   !,
   find_globals,
   !,
   build_gpu_functions,
   !,
   analyze_gpu_functions,
   !,
   iterative_build_funs,
   !,
   find_dependents,
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
   append(Outs2,News,Outs3), unique(Outs3,Outs), unique(Ref2,Refs),
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

@check_no_multidim_or_glob([]):-!.

@check_no_multidim_or_glob([loc(_,_,type(_,[]))|T]):-
   check_no_multidim_or_glob(T),
   !.

@check_no_multidim_or_glob([global(_,_)|_]):-
   !,
   fail.

@check_no_multidim_or_glob([loc(_,_,type(_,['['|IDXS]))|T]):-
   append(_,[']'|Rest],IDXS),
   !,
   (=(Rest,[])->
     (check_no_multidim_or_glob(T), !);
     (!, fail)
   ).

@find_pivot([],_):-
   !, fail.

@find_pivot([loc(_,Pivot,type([id('__pivot')|_],['['|_]))|_],Pivot):-
   !.

@find_pivot([global(Pivot,type([id('__pivot')|_],['['|_]))|_],Pivot):-
   !.

@find_pivot([_|T],Pivot):-
   find_pivot(T,Pivot).

@add_modifiers([],[]):-!.

@add_modifiers([loc(GID,Pivot,type([id('__pivot')|RestType],IDXS))|T],[loc(GID,Pivot,type([id('_pivot')|RestType],IDXS))|T1]):-
   add_modifiers(T,T1),
   !.

@add_modifiers([loc(GID,Name,type(TYPE,[]))|T],[loc(GID,Name,type([id('_global')|TYPE],[]))|T1]):-
   member('*',TYPE),
   !,
   add_modifiers(T,T1),
   !.

@add_modifiers([loc(GID,Name,type(TYPE,IDXS))|T],[loc(GID,Name,type([id('_global')|TYPE],IDXS))|T1]):-
   \+ =(IDXS,[]),
   \+ member('*',TYPE),
   !,
   add_modifiers(T,T1),
   !.

@add_modifiers([loc(GID,Name,type(TYPE,IDXS))|T],[loc(GID,Name,type(TYPE,IDXS))|T1]):-
   add_modifiers(T,T1),
   !.

@add_modifiers([global(Pivot,type([id('__pivot')|RestType],IDXS))|T],[global(Pivot,type([id('_pivot')|RestType],IDXS))|T1]):-
   add_modifiers(T,T1),
   !.

@add_modifiers([global(Name,type(TYPE,[]))|T],[global(Name,type([id('_global')|TYPE],[]))|T1]):-
   member('*',TYPE),
   !,
   add_modifiers(T,T1),
   !.

@add_modifiers([global(Name,type(TYPE,IDXS))|T],[global(Name,type([id('_global')|TYPE],IDXS))|T1]):-
   \+ =(IDXS,[]),
   \+ member('*',TYPE),
   !,
   add_modifiers(T,T1),
   !.

@add_modifiers([global(Name,type(TYPE,IDXS))|T],[global(Name,type(TYPE,IDXS))|T1]):-
   add_modifiers(T,T1),
   !.

@not_used(_).

% Альтернативы из switch {}
@traverse_alters([CurGID|GIDs], [TopGID|StackGIDs], [switch(TopGID,Pass)|StackConstrs], StackConstrs, Vars, Time, Used0, Used, NEWS0, NEWS, NAlt):-
   gpu_op('clsGPUAlternation',CurGID,_,[],_),
   (
    (append(ALT,[NextGID|_],GIDs),gpu_op('clsGPUOper',NextGID,_,[],_),db_content('args',NextGID,[['op','break']]),!)->
       (
        !,
        traverse_fun(ALT,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,Used0,Used1,NEWS0,NEWS1,T1),
        !
       );
       (
        traverse_fun(GIDs,[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,Used0,Used1,NEWS0,NEWS1,T1),
        !
       )
   ),
   retractall(gpu_break(_)),
   (
    (append(_,[NextGID1|Rest1],GIDs),gpu_op('clsGPUAlternation',NextGID1,_,[],_))->(
       !,
       traverse_alters([NextGID1|Rest1],[TopGID|StackGIDs],[switch(TopGID,Pass)|StackConstrs],_,Vars,T2,Used1,Used,NEWS1,NEWS,NAlt1),
       Time is T1+T2,
       NAlt is NAlt1+1,
       !
    );(
       =(Time,T1), =(NAlt,1), =(Used,Used1), =(NEWS,NEWS1),
       !
    )
   ),
   !.

@traverse_alters([], [TopGID|_], [switch(TopGID,_)|CRest], CRest, _, 0.0, Used, Used, NEWS, NEWS, 0):-!.

% Окончание while
@traverse_fun([], [TopGID|StackGIDs], [while(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUWhile',TopGID,_,[_],Ops),
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Used0, Ins, Used1), union(Used1, Outs, Used2), union(NEWS0, News, NEWSX), !,
   (
    (predicate_property(gpu_continue(_),'dynamic'), gpu_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(gpu_continue(_)),
   (
    (predicate_property(gpu_break(_),'dynamic'), gpu_break(_))->(
       retractall(gpu_break(_)),
       =(T1,0.0), =(Used, Used2), =(NEWS, NEWSX)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться
          gpu_op('clsGPUWhile',TopGID,_,[IGID1],_),
          traverse_fun([IGID1],[TopGID|StackGIDs],[while(TopGID,2)|StackConstrs],_,[LVars|Vars],Used2,Used,NEWSX,NEWS,T1)
         );
         (=(T1,0.0), =(Used, Used2), =(NEWS, NEWSX))
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
@traverse_fun([CurGID|_], StackGIDs, [Top|StackConstrs], StackConstrs, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','break']]),
   !,
   asserta(gpu_break(CurGID)),
   =..(Top,[_,TopGID,_]),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(vr(Vars)), asserta(tm(0.0)), asserta(us(Used0)), asserta(nw(NEWS0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(vr(VAR0)), once(tm(T0)), once(us(U0)), once(nw(N0)),
     traverse_fun([],[CurTopGID|Rest],[Top|StackConstrs],_,VAR0,U0,U1,N0,N1,TT),
     T1 is T0+TT,
     retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
     =(VAR0,[_|VAR1]),
     asserta(vr(VAR1)), asserta(tm(T1)), asserta(us(U1)), asserta(nw(N1)),
     =(TopGID,CurTopGID), % Проверка -- условие окончания цикла
   !,
   =(Time,T1), =(Used,U1), =(NEWS,N1),
   retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
   !.

% Возобновление continue
@traverse_fun([CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUOper',CurGID,_,[],_),
   db_content('args',CurGID,[['op','continue']]),
   !,
   asserta(gpu_continue(CurGID)),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)), asserta(us(Used0)), asserta(nw(NEWS0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)), once(us(U0)), once(nw(N0)),
     traverse_fun([],[CurTopGID|Rest],ST0,ST1,VAR0,U0,U1,N0,N1,TT),
     T1 is T0+TT,
     retractall(st(_)), retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
     =(VAR0,[_|VAR1]),
     asserta(st(ST1)), asserta(vr(VAR1)), asserta(tm(T1)), asserta(us(U1)), asserta(nw(N1)),
     \+ gpu_continue(CurGID), % Проверка -- условие окончания цикла
   !,
   =(OutCStack,ST1), =(Time,T1), =(Used,U1), =(NEWS,N1),
   retractall(st(_)), retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
   !.

% Возврат return
@traverse_fun([CurGID|_], StackGIDs, StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUReturn',CurGID,_,[],_),
   !, % Цикл выхода из конструкций верхнего уровня
     asserta(st(StackConstrs)), asserta(vr(Vars)), asserta(tm(0.0)), asserta(us(Used0)), asserta(nw(NEWS0)),
     append(_,[CurTopGID|Rest],StackGIDs),
     once(st(ST0)), once(vr(VAR0)), once(tm(T0)), once(us(U0)), once(nw(N0)),
     traverse_fun([],[CurTopGID|Rest],ST0,ST1,VAR0,U0,U1,N0,N1,TT),
     T1 is T0+TT,
     retractall(st(_)), retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
     =(VAR0,[_|VAR1]),
     asserta(st(ST1)), asserta(vr(VAR1)), asserta(tm(T1)), asserta(us(U1)), asserta(nw(N1)),
     =(Rest,[-1]), % Проверка -- условие окончания цикла
   !,
   =(OutCStack,ST1), =(Time,T1), =(Used,U1), =(NEWS,N1),
   retractall(st(_)), retractall(vr(_)), retractall(tm(_)), retractall(us(_)), retractall(nw(_)),
   !.

% Окончание do-while
@traverse_fun([], [TopGID|StackGIDs], [do(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUDo',TopGID,LastGID,[_],Ops),
   !,
   getNewInOutRefLazies(TopGID,[LVars|Vars],Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Used0, Ins, Used1), union(Used1, Outs, Used2), union(NEWS0, News, NEWSX), !,
   (
    (predicate_property(gpu_continue(_),'dynamic'), gpu_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(gpu_continue(_)),
   (
    (predicate_property(gpu_break(_),'dynamic'), gpu_break(_))->(
       retractall(gpu_break(_)),
       =(T2,0.0), =(Used,Used2), =(NEWS,NEWSX)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться
          gpu_op('clsGPUDo',TopGID,LastGID,[IGID1],_),
          traverse_fun([IGID1],[TopGID|StackGIDs],[do(TopGID,2)|StackConstrs],_,[LVars|Vars],Used2,Used,NEWSX,NEWS,T2)
         );
         (=(T2,0.0), =(Used,Used2), =(NEWS,NEWSX))
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
@traverse_fun([], [TopGID|StackGIDs], [for(TopGID,Pass)|StackConstrs], StackConstrs, [LVars|Vars], Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUFor',TopGID,_,[_],Ops),
   !,
   getForNewInOutRefLazies(['cond','chng'],TopGID,[LVars|Vars],Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Used0, Ins, Used1), union(Used1, Outs, Used2), union(NEWS0, News, NEWSX), !,
   (
    (predicate_property(gpu_continue(_),'dynamic'), gpu_continue(_))->(
      =(CONT,1) % Если это проход после continue, игнорируем время работы в этом витке, иначе оно завысит общее время исполнения
    );(
      =(CONT,0)
    )
   ),
   retractall(gpu_continue(_)),
   (
    (predicate_property(gpu_break(_),'dynamic'), gpu_break(_))->(
       retractall(gpu_break(_)),
       =(T2,0.0), =(Used,Used2), =(NEWS,NEWSX)
      );(
       =(Pass,1)->
         ( % IGID внутреннего оператора мог измениться
          gpu_op('clsGPUFor',TopGID,_,[IGID1],_),
          traverse_fun([IGID1],[TopGID|StackGIDs],[for(TopGID,2)|StackConstrs],_,[LVars|Vars],Used2,Used,NEWSX,NEWS,T2),
          put_for_time(TopGID,T2)
         );
         (=(T2,0.0), =(Used,Used2), =(NEWS, NEWSX))
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
@traverse_fun([], [TopGID|_], StackConstrs, StackConstrs, _, Used, Used, NEWS, NEWS, 0.0):-
   gpu_op('clsGPUBegin',TopGID,_,_,_),
   !.

% Окончание функции
@traverse_fun([], [-1], StackConstrs, StackConstrs, _, Used, Used, NEWS, NEWS, 0.0):-
   !.

% Окончание произвольного (не{}) оператора. Может вызываться в операторе окончания различных конструктов
@traverse_fun([], [TopGID|_], StackConstrs, StackConstrs, _, Used, Used, NEWS, NEWS, 0.0):-
   \+ gpu_op('clsGPUBegin',TopGID,_,_,_),
   !.

% Полный if-else, IGIDs = [IfGID,EGID]. Краткий if -- обрабатывается обычным образом, IGIDs = [IfGID]
@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUIf',CurGID,_,[IfGID,EGID],Ops),
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Ins, Outs, Used2), !,
   traverse_fun([IfGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Used2,Used30,News,NEWS30,T20),
   traverse_fun([EGID],[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Used2,Used31,News,NEWS31,T21),
   union(Used30,Used31,Used3X), union(Used0, Used3X, Used3XX),
   union(NEWS30, NEWS31, NEWS3X), subtract(Used3X, NEWS3X, Used3E), !,
   not_used(Used3E),
   traverse_fun(GIDs,[TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used3XX,Used,NEWS0,NEWS,T3),
   Time is BaseTime+0.5*(T20+T21)+T3,
   !.

% Полный while
@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUWhile',CurGID,_,[IGID],Ops),
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Ins, Outs, Used2), !,
   traverse_fun([IGID],[CurGID,TopGID|StackGIDs],[while(CurGID,1)|StackConstrs],_,[News|Vars],Used2,Used3,News,NEWSX,T2),
   !,
   union(Used0, Used3, Used3X), subtract(Used3, NEWSX, Used3E), !,
   not_used(Used3E),
   traverse_fun(GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used3X,Used,NEWS0,NEWS,T3),
   Time is BaseTime+T2+T3,
   !.

% Полный for
@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUFor',CurGID,_,[IGID],Ops),
   !,
   getForNewInOutRefLazies(['init','cond'],CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Ins, Outs, Used2), !,
   traverse_fun([IGID],[CurGID,TopGID|StackGIDs],[for(CurGID,1)|StackConstrs],_,[News|Vars],Used2,Used3,News,NEWS1,T2),
   !,
   union(Used3, Used0, Used3X), subtract(Used3, NEWS1, Used3E), !,
   retractall(gpu_for_interface(CurGID,_)),
   (
    once(find_pivot(Used3E,_)),
    once(check_no_multidim_or_glob(Used3E)),
    once(add_modifiers(Used3E,Used3F)),
    asserta(gpu_for_interface(CurGID,Used3F));
    true
   ),
   !,
   traverse_fun(GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used3X,Used,NEWS0,NEWS,T3),
   Time is BaseTime+T2+T3,
   !.

% Полный do-while
@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUDo',CurGID,_,[IGID],_),
   !,
   traverse_fun([IGID],[CurGID,TopGID|StackGIDs],[do(CurGID,1)|StackConstrs],_,[[]|Vars],[],Used1,[],NEWS1,T1),
   !,
   union(Used0, Used1, Used1X), subtract(Used1, NEWS1, Used1E), !,
   not_used(Used1E),
   traverse_fun(GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used1X,Used,NEWS0,NEWS,T2),
   Time is T1+T2,
   !.

% switch
@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   gpu_op('clsGPUSwitch',CurGID,_,[IGID],Ops),
   gpu_op('clsGPUBegin',IGID,_,IGIDs,_),
   !,
   getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime),
   !,
   union(Ins, Outs, Used2), !,
   traverse_alters(IGIDs,[CurGID,TopGID|StackGIDs],[switch(CurGID,1)|StackConstrs],_,[News|Vars],TNN,Used2,Used3,News,NEWS1,NAlt),
   !,
   union(Used0, Used3, Used3X), subtract(Used3, NEWS1, Used3E), !,
   not_used(Used3E),
   traverse_fun(GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used3X,Used,NEWS0,NEWS,T2),
   (
    =(NAlt,0)->
      Time is BaseTime+T2;
      Time is BaseTime+TNN/NAlt+T2
   ),
   !.

@traverse_fun([CurGID|GIDs], [TopGID|StackGIDs], StackConstrs, OutCStack, Vars, Used0, Used, NEWS0, NEWS, Time):-
   (predicate_property(gpu_break(_),'dynamic'), gpu_break(_))->(
      traverse_fun([], [TopGID|StackGIDs],StackConstrs,OutCStack,Vars,Used0,Used,NEWS0,NEWS,Time),
      !
   );(
      gpu_op(_,CurGID,_,IGIDs,Ops),
      !,
      getNewInOutRefLazies(CurGID,Vars,Ops,News,Ins,Outs,_,_,BaseTime),
      union(Ins, Outs, Used2), !,
      ( % Если это запуск процедуры, то прибавляем время ее исполнения
       gpu_op(_,CurGID,_,[],[arg(_,_,_,_,[proc(Fun,Prms)],_,_,_)])->
         (getTime([proc(Fun,Prms)],TSP1), g_read('$DefOperTime',TOp0), TSP is TSP1-TOp0);
         =(TSP,0.0)
      ),
      addLocals(Vars,News,Vars1),
      !,
      traverse_fun(IGIDs,[CurGID,TopGID|StackGIDs],StackConstrs,_,[News|Vars],Used2,Used3,News,NEWS1,T2),
      union(Used0, Used3, Used3X), union(NEWS0, NEWS1, NEWSX), !,
      traverse_fun(GIDs, [TopGID|StackGIDs],StackConstrs,OutCStack,Vars1,Used3X,Used,NEWSX,NEWS,T3),
      Time is TSP+BaseTime+T2+T3,
      !
   ).

@process_fun(Fun,GID,NPrms):-
   retractall(gpu_break(_)),
   retractall(gpu_continue(_)),
   gpu_globals(GLOB),
   glob_prefixate(GLOB,G1),
   get_fparams(all,Fun,NPrms,PARMS),
   loc_prefixate(GID,PARMS,P1),
   traverse_fun([GID],[-1],[],_,[P1,G1],[],_,[],_,Time),
   put_ftime(Fun,NPrms,Time),
   !.

@bypass_sequence([],[],[]):-!.

@bypass_sequence([gid('clsGPUEnd',GID)|T],[],[gid('clsGPUEnd',GID)|T]):-
   !.

@bypass_sequence([gid('clsGPUBegin',GID)|T],TT,T3):-
   bypass_complex([gid('clsGPUBegin',GID)|T],T0,T1),
   bypass_sequence(T1,T2,T3),
   append(T0,T2,TT),
   !.

@bypass_sequence([H|T],[H|T1],T2):-
   bypass_sequence(T,T1,T2),
   !.

@bypass_complex([gid('clsGPUBegin',GID)|T],[gid('clsGPUBegin',GID)|T1],T2):-
   bypass_sequence(T,T0,[gid('clsGPUEnd',GID2)|T2]),
   append(T0,[gid('clsGPUEnd',GID2)],T1).

@bypass_op([A|T],[A|BeforeWith],After):-
   member(A,[gid('clsGPUFor',_),gid('clsGPUSwitch',_),gid('clsGPUWhile',_)]),
   !,
   bypass_op(T,BeforeWith,After),
   !.

@bypass_op([gid('clsGPUDo',GID)|T],[gid('clsGPUDo',GID)|T1],T2):-
   bypass_op(T,BeforeWhile,[gid('clsGPUWhile',GIDW),gid('clsGPUOper',EMPTY)|T2]),
   append(BeforeWhile,[gid('clsGPUWhile',GIDW),gid('clsGPUOper',EMPTY)],T1),
   !.

@bypass_op([gid('clsGPUIf',GID)|T],[gid('clsGPUIf',GID)|T1],T2):-
   bypass_op(T,BeforeWith,[A|AfterT]),
   (
    =(gid('clsGPUElse',_),A)->(
      bypass_op(AfterT,BeforeWith2,T2),
      append(BeforeWith,[A|BeforeWith2],T1),
      !
    );(
      =(T1,BeforeWith),=(T2,[A|AfterT]),!
    )
   ),
   !.

@bypass_op([gid('clsGPUBegin',GID)|T],T1,T2):-
   bypass_complex([gid('clsGPUBegin',GID)|T],T1,T2),
   !.

@bypass_op([A|T],[A],T):-!.

@insert_ending_bracket(L1,L2):-
   bypass_op(L1,BeforeWith,After),
   !,
   append(BeforeWith,[gid('clsGPUEnd',-1)|After],L2),
   !.

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

@write_interface(S, []):-
   write(S, '_'),
   !.

@write_interface(S, [loc(_,Name,type(TYPE,[]))]):-
   into_atom(TYPE,' ', ATYPE),
   !,
   write(S, ATYPE), write(S, ' '), write(S, Name),
   !.

@write_interface(S, [loc(_,Name,type(TYPE,IDX))]):-
   into_atom(TYPE,' ', ATYPE),
   !,
   into_atom(IDX,'', AIDX),
   !,
   write(S, ATYPE), write(S, ' '), write(S, Name), write(S, AIDX),
   !.

@write_interface(S, [ITEM]):- write(S, ITEM), !.

@write_interface(S, [A,B|T]):-
   write_interface(S, [A]),
   !,
   write(S, ','),
   write_interface(S, [B|T]),
   !.

@write_program(_,_,_,[]):-!.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUOper',GID)|T]):-
   db_content('prog',GID,[['op']]),
   db_content('args',GID,[['op',Op]]),
   atom_concat(SPC,Shift,SPC1),
   write(S,SPC1),
   write(S,Op), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,SP,S,[gid('clsGPUComments',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(Shift,SP,S,[gid('clsGPUInclude',_)|T]):-
   write_program(Shift,SP,S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUBegin',GID)|T]):-
   db_content('prog',GID,[['{']]),
   !,
   write(S,SPC), write(S,Shift), write(S,'{'), nl(S),
   atom_concat(SPC,Shift,SPC1),
   atom_concat(SPC1,'  ',SPC2),
   write_program('',[SPC2,SPC1,SPC|ST],S,T),
   !.

@write_program(_,[_,SPC1,SPC|ST],S,[gid('clsGPUEnd',GIDE)|T]):-
   write(S,SPC1), write(S,'}'), nl(S),
   (
    ( predicate_property(gpu_end_function(_),'dynamic'), gpu_end_function(GIDE) )->
       ( write(S, '#pragma plan common end'), nl(S), nl(S), retractall(gpu_end_function(_)) );
       true
   ),
   !,
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUDo',GID)|T]):-
   db_content('prog',GID,[['do']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'do'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUWhile',GID)|T]):-
   db_content('prog',GID,[['while']]),
   db_content('args',GID,[['cond',Cond]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'while ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUFor',GID)|T]):-
   db_content('prog',GID,[['for']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift),
   (
    (predicate_property(gpu_for(_),'dynamic'), gpu_for(GID), gpu_for_interface(GID,INTRF))->
      (
       write(S,'vectorized(NULL,50) gpu<'), write_interface(S, INTRF), write(S,'> for ( ')
      );
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
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUIf',GID)|T]):-
   db_content('prog',GID,[['if']]),
   db_content('args',GID,[['cond',Cond]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'if ( '), write(S,Cond), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUElse',GID)|T]):-
   db_content('prog',GID,[['else']]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(S,Shift), write(S,'else'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUSwitch',GID)|T]):-
   db_content('prog',GID,[['switch']]),
   db_content('args',GID,[['arg',Arg]]),
   atom_concat(Shift,'  ',Shift1),
   write(S,SPC), write(Shift), write(S,'switch ( '), write(S,Arg), write(S,' )'), nl(S),
   write_program(Shift1,[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUAlternation',GID)|T]):-
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

@write_program(Shift,[SPC|ST],S,[gid('clsGPUTypedef',GID)|T]):-
   db_content('prog',GID,[['type']]),
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,'typedef '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUCVar',GID)|T]):-
   db_content('prog',GID,[[TYPE]]),
   member(TYPE,['struct','union']),
   !,
   db_content('args',GID,[['def',Def]]),
   write(S,SPC), write(S,Shift), write(S,TYPE), write(S,' '), write(S,Def), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,[SPC|ST],S,[gid('clsGPUReturn',GID)|T]):-
   db_content('prog',GID,[['return']]),
   db_content('args',GID,[['arg',Arg]]),
   write(S,SPC), write(S,Shift), write(S,'return '), write(S,Arg), write(S,';'), nl(S),
   write_program('',[SPC|ST],S,T),
   !.

@write_program(Shift,SP,S,[gid('clsGPUPreproc',GID)|T]):-
   db_content('prog',GID,[['preproc']]),
   db_content('args',GID,[['body',Body]]),
   write(S,Body), nl(S),
   write_program(Shift,SP,S,T),
   !.

@write_program(_,[SPC|ST],S,[gid('clsGPUFunction',GID)|T]):-
   db_content('prog',GID,[['func']]),
   db_content('args',GID,L),
   member(['name',ID],L),
   member(['args',Args],L),
   member(['ret',Ret],L),
   !,
   (
    (=(T,[gid('clsGPUBegin',_)|_]), predicate_property(gpu_do_not_worry(_,_,_),'dynamic'), gpu_do_not_worry(_,GID,_))->
      (
       write(S, '#pragma plan common begin'), nl(S), write(S,'$ '),
       bypass_complex(T,BODY,_),
       last(BODY,gid('clsGPUEnd',GIDE)),
       asserta(gpu_end_function(GIDE))
      );
      true
   ),
   !,
   write(S,SPC), write(S, Ret), write(S, ' '), write(S, ID), write(S,'( '), write(S,Args), write(S,' )'),
   write_program('',[SPC|ST],S,T),
   !.

@restructure_program:-
   asserta(gpu_new_id(10000)),
   (predicate_property(gpu_for(_),'dynamic'), gpu_for(GID), gpu_for_interface(GID,_)),
   gpu_new_id(NewBegGID),
   global_trace(TR),
   once(\+(append(_,[gid('clsGPUFor',GID),gid('clsGPUBegin',_)|_],TR))),
   retractall(gpu_new_id(_)),
   NewestGID is NewBegGID + 2,
   NewEndGID is NewBegGID + 1,
   asserta(gpu_new_id(NewestGID)),
   asserta(db_content('prog',NewBegGID,[['{']])),
   asserta(db_content('prog',NewEndGID,[['}']])),
   once(append(Left,[gid(C,GID)|Right],TR)),
   once(bypass_op([gid(C,GID)|Right],_,[NEXT|RIGHT])),
   once(append(BODY,[NEXT|RIGHT],Right)),
   once(append(Left,[gid(C,GID),gid('clsGPUBegin',NewBegGID)|BODY],L1)),
   once(append(L1,[gid('clsGPUEnd',NewEndGID)|[NEXT|RIGHT]],TR1)),
   retractall(global_trace(_)),
   asserta(global_trace(TR1)),
   fail.

@restructure_program.  

% Формирование текста программы FName по загруженным данным + spawn/sync
@recreate_program(FName):-
  open(FName,write,S),
  global_trace(TR),
  write(S, '#include "gpu_parallelize.h"'), nl(S), nl(S),
  write(S, '#define __pivot /* Pivot of optimized loops */'), nl(S), nl(S),
  write_program('',[''],S,TR),
  close(S).

@process_all_funs:-
  predicate_property(gpu_function(_,_,_),'dynamic'),
  gpu_function(Fun,GID,NPrms),
  once(process_fun(Fun,GID,NPrms)),
  get_ftime(Fun,NPrms,_), % Time
%  write(Fun),write(':'),write(Time),nl,
  fail.

@process_all_funs:-
%  write('--------------'), nl,
  !.

@iterative_times(0):-!.

% Итерационный алгоритм пересчета времен исполнения функций. Алгоритм заканчивается, когда
% времена исполнения практически перестают меняться (+/-1) или превышено число итераций N
@iterative_times(N):-
  retractall(gpu_retime),
  process_all_funs,
  gpu_retime,
  !,
  N1 is N-1,
  iterative_times(N1).

@iterative_times(_):-!.

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

@processing:-
  g_assign('$DefFTime', 15.0), % Время исполнения функции/процедуры по умолчанию (внешней или внутренней до расчета)
  g_assign('$SpawnTime', 5.0), % Время, затрачиваемое мастер-процессом на ответвление spawn-процесса
  g_assign('$DefOperTime', 1.0), % Время исполнения элементарного математического выражения без функций по умолчанию
  g_assign('$SyncTime', 5.0), % Время, затрачиваемое слиянием ответвленных процессов (без ожидания)
  prepare_data,
  iterative_times(15), % Предсказываем время исполнения функций
  handle_fors(0,15),
  restructure_program,
  recreate_program('_gpu.cpp').

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

@gpu_debug:-
  asserta(global_trace([])),
  collect_global_trace,
  processing.

@goal:-
  gpu_debug.
};

#endif
