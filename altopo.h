#ifndef __ALTOPO_H__
#define __ALTOPO_H__

#def_module(plan_topology) altopo(Templates, Expression) {
/*
% expr = sum_expr
% sum_expr = sum_expr "+" unar_expr | sum_expr "-" unar_expr | unar_expr
% unar_expr = "+" const_with_mul_expr | "-" const_with_mul_expr | const_with_mul_expr
% const_with_mul_expr = const "*" mul_expr | mul_expr
% mul_expr = pow_expr "*" mul_expr | pow_expr
% pow_expr = var_expr "**" const | var_expr
% var_expr = "(" expr ")" | name "/" const | name
% name = ident "[]" | ident "[" const "]" | ident
*/
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

@find_number2([Sym|Tag], Num, Rest):-
  number_sym(Sym),
  find_number2(Tag, TNum, Rest),
  atom_concat(Sym, TNum, Num),
  !.
@find_number2(L, '', L):-!.

@lex([], []):-!.

@lex(['*','*'|Tag], [opPow|L1]):-
  !,
  lex(Tag, L1).

@lex(['*'|Tag], [opMul|L1]):-
  !,
  lex(Tag, L1).

@lex(['+'|Tag], [opAdd|L1]):-
  !,
  lex(Tag, L1).

@lex(['-'|Tag], [opSub|L1]):-
  !,
  lex(Tag, L1).

@lex(['/'|Tag], [opDiv|L1]):-
  !,
  lex(Tag, L1).

@lex([')'|Tag], [tail(Tag)]):-
  !.

@lex(['('|Tag], [opGroup(G)|L1]):-
  !,
  lex(Tag, Lexems),
  !,
  (
   append(G,[tail(Tag2)], Lexems) -> (lex(Tag2, L1), !, true); (!, fail)
  ).

@lex([' '|Tag], L1):-
  !,
  lex(Tag, L1).

@lex([Sym|Tag], [id(Id, Mode)|L1]):-
  ident_first_sym(Sym),
  !,
  find_ident2(Tag, TId, Rest),
  atom_concat(Sym, TId, Id),
  !,
  (
   append(['[',']'], RestP, Rest) ->
     (=(Mode, 'plural'), lex(RestP, L1));
     (
      append(['['|Num], [']'|RestP], Rest) ->
       (atom_chars(Mode, Num), lex(RestP, L1));
       (=(Mode, '1'), lex(Rest, L1))
     )
  ),
  !.

@lex([Sym|Tag], [num(Num)|L1]):-
  number_sym(Sym),
  !,
  find_number2(Tag, TNum, Rest),
  atom_concat(Sym, TNum, Num),
  !,
  lex(Rest, L1).

@tokenize(Str, Lexs):-
  atom_chars(Str, SymList),
  lex(SymList, Lexs),
  (
   append(_, [tail(_)], Lexs) -> (!, fail); true
  ),
  !.

@neg([[opSub|TI]|TL],[TI|TL1]):-
  neg(TL, TL1),
  !.
@neg([[opAdd|TI]|TL],[[opSub|TI]|TL1]):-
  neg(TL, TL1),
  !.
@neg([[HI|TI]|TL],[[opSub,HI|TI]|TL1]):-
  neg(TL, TL1),
  !.
@neg([],[]):-!.

// [... +a ...] + [... -a ...]
@add([[opAdd|TI]|TL], L2, L):-
  append(L1, [[opSub|TI]|TL3], L2),
  !,
  append(L1, TL3, L4),
  add(TL, L4, L),
  !.
// [... +a ...] + [...  ...]
@add([[opAdd|TI]|TL], L2, L):-
  add(TL, L2, L3),
  append([[opAdd|TI]], L3, L),
  !.
// [... -a ...] + [... +a ...]
@add([[opSub|TI]|TL], L2, L):-
  append(L1, [[opAdd|TI]|TL3], L2),
  !,
  append(L1, TL3, L4),
  add(TL, L4, L),
  !.
// [... -a ...] + [... -a ...]
@add([[opSub|TI]|TL], L2, [[opSub|TI],[opSub|TI]|L]):-
  append(L1, [[opSub|TI]|TL3], L2),
  !,
  append(L1, TL3, L4),
  add(TL, L4, L),
  !.
// [... -a ...] + [... a ...]
@add([[opSub|TI]|TL], L2, L):-
  append(L1, [TI|TL3], L2),
  !,
  append(L1, TL3, L4),
  add(TL, L4, L),
  !.
// [... -a ...] + [...  ...]
@add([[opSub|TI]|TL], L2, L):-
  add(TL, L2, L3),
  append([[opSub|TI]], L3, L),
  !.
// [... a ...] + [... -a ...]
@add([TI|TL], L2, L):-
  append(L1, [[opSub|TI]|TL3], L2),
  !,
  append(L1, TL3, L4),
  add(TL, L4, L),
  !.
// [... a ...] + [...  ...]
@add([TI|TL], L2, L):-
  add(TL, L2, L3),
  append([TI], L3, L),
  !.
@add([], L, L):-!.
@add(L, [], L):-!.

@sub(L1, L2, L):-
  neg(L2, L3),
  add(L1, L3, L),
  !.

@mul11([opAdd|T1], [opAdd|T2], L):-
  append(T1, [opMul|T2], L),
  !.
@mul11([opAdd|T1], [opSub|T2], L):-
  append([opSub|T1], [opMul|T2], L),
  !.
@mul11([opSub|T1], [opAdd|T2], L):-
  append([opSub|T1], [opMul|T2], L),
  !.
@mul11([opSub|T1], [opSub|T2], L):-
  append(T1, [opMul|T2], L),
  !.
@mul11([opAdd|T1], T2, L):-
  append(T1, [opMul|T2], L),
  !.
@mul11([opSub|T1], T2, L):-
  append([opSub|T1], [opMul|T2], L),
  !.
@mul11(T1, [opAdd|T2], L):-
  append(T1, [opMul|T2], L),
  !.
@mul11(T1, [opSub|T2], L):-
  append([opSub|T1], [opMul|T2], L),
  !.
@mul11(T1, T2, L):-
  append(T1, [opMul|T2], L),
  !.

@mul1(A, [B|T], L):-
  mul11(A, B, C),
  mul1(A, T, L1),
  add([C], L1, L),
  !.
@mul1(_, [], []).

@mul([H|T], L1, L):-
  mul1(H, L1, L2),
  mul(T, L1, L3),
  add(L2, L3, L),
  !.
@mul([], _, []):-!.
@mul(_, [], []):-!.

@muln(_,0,[]):-!.
@muln(L,1,L):-!.
@muln(L1,N,L):-
  N1 is N-1,
  muln(L1,N1,L11),
  add(L11,L1,L),
  !.

@pow(L, 1, L):-!.
@pow(L, N, L1):-
  N1 is N-1,
  pow(L, N1, L2),
  mul(L2, L, L1),
  !.
 
@var_explode([opGroup(G)], L):-
  sum_explode(G, L),
  !.
@var_explode([id(Id, Mode), opDiv, num(N)], [[id(Id, Mode), opDiv, num(N)]]):-!.
@var_explode([id(Id, Mode)], [[id(Id, Mode)]]):-!.

@pow_explode(Lexs, L):-
  append(VE, [opPow, num(N)], Lexs),
  var_explode(VE, Op1),
  number_atom(NN, N),
  pow(Op1, NN, L),
  !.
@pow_explode(Lexs, L):-
  var_explode(Lexs, L),
  !.

@mul_explode(Lexs, L):-
  append(PE, [opMul|ME], Lexs),
  pow_explode(PE, Op1),
  mul_explode(ME, Op2),
  mul(Op1, Op2, L),
  !.
@mul_explode(Lexs, L):-
  pow_explode(Lexs, L),
  !.

@cmul_explode([num(N),opMul|T], L):-
  mul_explode(T, L1),
  number_atom(NN, N),
  muln(L1, NN, L),
  !.
@cmul_explode(Lexs, L):-
  mul_explode(Lexs, L),
  !.

@unar_explode([opAdd|ME], L):-
  cmul_explode(ME, L),
  !.
@unar_explode([opSub|ME], L):-
  cmul_explode(ME, Op),
  neg(Op, L),
  !.
@unar_explode(Lexs, L):-
  cmul_explode(Lexs, L),
  !.

@sum_explode(Lexs, L):-
  append(SE, [opAdd|UE], Lexs),
  sum_explode(SE, Op1),
  unar_explode(UE, Op2),
  add(Op1, Op2, L),
  !.
@sum_explode(Lexs, L):-
  append(SE, [opSub|UE], Lexs),
  sum_explode(SE, Op1),
  unar_explode(UE, Op2),
  sub(Op1, Op2, L),
  !.
@sum_explode(Lexs, L):-
  unar_explode(Lexs, L),
  !.

@positive([]):-!.
@positive([[opSub|_]|_]):-!, fail.
@positive([_|T]):-
  positive(T),
  !.

@create_nodes_ids_item([], []):-!.
@create_nodes_ids_item([id(Id,Mode)|T],T1):-
  create_nodes_ids_item(T, T1),
  member(node(Id,Modes), T1),
  member(Mode, Modes),
  !.
@create_nodes_ids_item([id(Id,Mode)|T],T11):-
  create_nodes_ids_item(T, T1),
  append(L,[node(Id,Modes)|R], T1),
  append(L,[node(Id,[Mode|Modes])|R], T11),
  !.
@create_nodes_ids_item([id(Id,Mode)|T],[node(Id,[Mode])|T1]):-
  create_nodes_ids_item(T, T1),
  !.
@create_nodes_ids_item([_|T], T1):-
  create_nodes_ids_item(T, T1),
  !.

@union([H|T], L, L1):-
  member(H, L),
  union(T, L, L1),
  !.
@union([H|T], L, [H|T1]):-
  union(T, L, T1),
  !.
@union([], L, L):-!.

@union_ids([node(Id,Modes1)|T], L, [node(Id,Modes)|T1]):-
  append(Left,[node(Id,Modes2)|Right], L),
  union(Modes1, Modes2, Modes),
  append(Left, Right, L2),
  union_ids(T, L2, T1),
  !.
@union_ids([H|T], L, [H|T1]):-
  union_ids(T, L, T1),
  !.
@union_ids([], L, L):-!.

@create_nodes_ids([H|T], IDs):-
  create_nodes_ids_item(H, IDs1),
  create_nodes_ids(T, IDs2),
  union_ids(IDs1, IDs2, IDs),
  !.
@create_nodes_ids([],[]):-!.

@create_seq(0, []):-!.
@create_seq(N, [NN|T]):-
  number_atom(N, NN),
  N1 is N-1,
  create_seq(N1, T),
  !.

@make_node_indexes_item(Id, [Number|TI], Idxs1, [id(Id,plural)|T], [id(Id,Number)|T1]):-
  make_node_indexes_item(Id, TI, Idxs1, T, T1),
  !.
@make_node_indexes_item(Id, Idxs, Idxs1, [H|T], [H|T1]):-
  make_node_indexes_item(Id, Idxs, Idxs1, T, T1),
  !.
@make_node_indexes_item(_, Idxs, Idxs, [], []):-!.

@make_node_indexes(Id, Idxs, [H|T], [H1|T1]):-
  make_node_indexes_item(Id, Idxs, Idxs1, H, H1),
  make_node_indexes(Id, Idxs1, T, T1),
  !.
@make_node_indexes(_, _, [], []):-!.

@isubtract(L, [H|T], L1):-
  append(Left, [H|Right], L),
  append(Left, Right, L2),
  !,
  isubtract(L2, T, L1),
  !.
@isubtract(L, [_|T], L1):-
  isubtract(L, T, L1),
  !.
@isubtract(L, [], L):-!.

@make_nodes_indexes([node(Id, Modes)|T], L1, L2):-
  isubtract(Modes,[plural],Modes1),
  create_seq(1024, Indexes),
  reverse(Indexes, RIndexes),
  isubtract(RIndexes, Modes1, Indexes1),
  make_node_indexes(Id, Indexes1, L1, L11),
  make_nodes_indexes(T, L11, L2),
  !.
@make_nodes_indexes([], L, L):-!.

// Расставляем индексы у членов вида id(Id,plural), заменяя plural уникальным атомом-числом.
@make_indexes(L1, L2):-
  create_nodes_ids(L1, IDs),
  make_nodes_indexes(IDs, L1, L2),
  !.

@make_nprocs_item([id(Id,Number), opDiv, num(NProcs)|T], [id(Id,Number,NProcs)|T1]):-
  make_nprocs_item(T, T1),
  !.
@make_nprocs_item([id(Id,Number)|T], [id(Id,Number,'0')|T1]):-
  make_nprocs_item(T, T1),
  !.
@make_nprocs_item([opMul|T], T1):-
  make_nprocs_item(T, T1),
  !.
@make_nprocs_item([], []):-!.

// Убираем деление на константу-число процессоров из выражения, внеся ее в id(Id,Number,NProcs) третьим членом
// Если член не делится на константу, то третьим членом вносится '0'. Членов id(Id,Number) более не будет.
@make_nprocs([H|T], [H1|T1]):-
  make_nprocs_item(H, H1),
  make_nprocs(T, T1),
  !.
@make_nprocs([], []):-!.

@get_links_item([id(Id1,Number1,NProcs1),id(Id2,Number2,NProcs2)|T], [link(Id1,Number1,NProcs1,Id2,Number2,NProcs2)|T1]):-
  get_links_item([id(Id2,Number2,NProcs2)|T], T1),
  !.
@get_links_item([_], []):-!.
@get_links_item([], []):-!.

// Преобразуем выражение из [[id(Id,Number,NProcs),...]] в [[link(Id1,Number1,NProcs1,Id2,Number2,NProcs2),...]]
@get_links([H|T], L):-
  get_links_item(H, L1),
  get_links(T, L2),
  append(L1, L2, L),
  !.
@get_links([], []):-!. 

@unique([link(Id1,Number1,_,Id2,Number2,_)|T1], T2):-
  member(link(Id1,Number1,_,Id2,Number2,_), T1),
  unique(T1, T2),
  !.
@unique([H|T1], [H|T2]):-
  unique(T1, T2),
  !.
@unique([], []):-!.

// cycled(L1, Id, Number, Id1, Number1). Проверка по списку прямых связей L1, есть ли путь из (Id1,Number1) в (Id,Number)
// Так мы проверяем, существует ли цикл, начинающийся в (Id,Number).
@cycled(_, Id, Number, Id, Number):-!.
@cycled(DirLinks, Id1, Number1, Id2, Number2):-
  append(DLLeft,[link(Id2, Number2, _, Idn, Numbern, _)|DLRight],DirLinks),
  append(DLLeft,DLRight,DirLinks1),
  cycled(DirLinks1, Id1, Number1, Idn, Numbern),
  !.
@cycled(_, _, _, _, _):-!, fail.

// classify(L1, L2, LD, LR). Классифицируем связи из L2 на прямые LD и обратные LR. L1 - список оставшихся прямых связей
@classify(DirLinks, [link(Id1,Number1,NProcs1,Id2,Number2,NProcs2)|T], LD, [link(Id1,Number1,NProcs1,Id2,Number2,NProcs2)|TR]):-
  cycled(DirLinks, Id1, Number1, Id2, Number2),
  append(DLLeft,[link(Id1,Number1,NProcs1,Id2,Number2,NProcs2)|DLRight],DirLinks),
  append(DLLeft,DLRight,DirLinks1),
  classify(DirLinks1, T, LD, TR),
  !.
@classify(DirLinks, [H|T], [H|TL], LR):-
  classify(DirLinks, T, TL, LR),
  !.
@classify(_, [], [], []):-!.

@out(Tmplts, Directive, [link(Id1,Number1,NProcs1,Id2,Number2,NProcs2)|T]):-
  member([Id1, Tmpl1], Tmplts),
  member([Id2, Tmpl2], Tmplts),
  write('  '), write(Directive), write('('),
    write(Id1), write('['), write(Number1), write(']'), write(Tmpl1), write('/'), write(NProcs1),
    write('->'),
    write(Id2), write('['), write(Number2), write(']'), write(Tmpl2), write('/'), write(NProcs2),
  write(');'),
  nl,
  out(Tmplts, Directive, T),
  !.
@out(_, _, []):-!.

@process(Tmplts, S):- tokenize(S, L1), sum_explode(L1, L2), positive(L2), make_indexes(L2, L3), make_nprocs(L3, L4),
  get_links(L4, LL), unique(LL, LL1), classify(LL1, LL1, LD, LR),
  out(Tmplts, 'plan_parallel_chain', LD), out(Tmplts, 'plan_parallel_reverse', LR).

@goal:- process(Templates, Expression).
};

#endif
