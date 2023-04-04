	send :- current_predicate(A), listing(A), fail.
	send :- write("Ok").

	mars_send(FName) :- mars(on), send, mars(FName).
	mars_recv(FName) :- mars_decode(FName).

	add_object(ID, ClassID, ParamsList, Desc) :-
		g_read('$ObjFactID', ObjFactID),
		=..(Obj, [ObjFactID, ID, ClassID, ParamsList, Desc]),
		assertz(Obj).
	del_object(ID) :-
		g_read('$ObjFactID', ObjFactID),
		g_read('$ObjLinkID', ObjLinkID),
		=..(Obj, [ObjFactID, ID, _, _, _]),
		retractall(Obj),
		=..(Link1, [ObjLinkID, ID, _, _, _, _]),
		=..(Link2, [ObjLinkID, _, _, ID, _, _]),
		retractall(Link1),
		retractall(Link2).
	add_link(ID1, CntID1, ID2, CntID2, Inform) :- % Inform = t/f
		g_read('$ObjLinkID', ObjLinkID),
		=..(Link, [ObjLinkID, ID1, CntID1, ID2, CntID2, Inform]),
		assertz(Link).
	del_link(ID1, CntID1, ID2, CntID2) :-
		g_read('$ObjLinkID', ObjLinkID),
		=..(Link, [ObjLinkID, ID1, CntID1, ID2, CntID2, _]),
		retractall(Link).
	del_all_objects :-
		g_read('$ObjFactID', ObjFactID),
		g_read('$ObjLinkID', ObjLinkID),
		=..(Obj, [ObjFactID, _, _, _, _]),
		=..(Link, [ObjLinkID, _, _, _, _, _]),
		retractall(Obj),
		retractall(Link).
	class_prepare_params(_, []).
	class_prepare_params(S, [param(Name, Val)|T]):-
		write(S, ' '), write(S, Name), write(S, '="'), write(S, Val), write(S,'"'),
		class_prepare_params(S, T).
	write_ilinks(S, ID, ContID):-
		g_read('$ObjLinkID', ObjLinkID),
		=..(Link, [ObjLinkID, ID2, Cont2, ID, ContID, Informational]),
		Link,
		g_read('$ObjFactID', ObjFactID),
		=..(Obj, [ObjFactID, ID2, ClassID2, _, _]),
		once(Obj),
		ocontacts(ID2, OP),
		member(contact(Cont2, Code), OP),
		write(S, '<Link Code="'), write(S, Code), write(S, '" />'), nl(S),
		fail.
	write_ilinks(_, _, _).
	class_prepare_ilinks(S, ID) :-
		icontacts(ID, IC),
		member(contact(ContID, Ref), IC),
		write(S, '<I ID="'), write(S, ContID), write(S, '" Ref="'), write(S, Ref), write(S, '">'), nl(S),
		once(write_ilinks(S, ID, ContID)),
		write(S, '</I>'), nl(S),
		fail.
	class_prepare_ilinks(_,_).
	write_olinks(S, ID, ContID):-
		g_read('$ObjLinkID', ObjLinkID),
		=..(Link, [ObjLinkID, ID, ContID, ID2, Cont2, Informational]),
		Link,
		g_read('$ObjFactID', ObjFactID),
		=..(Obj, [ObjFactID, ID2, ClassID2, _, _]),
		once(Obj),
		icontacts(ID2, IP),
		member(contact(Cont2, Code), IP),
		write(S, '<Link Code="'), write(S, Code), write(S, '" />'), nl(S),
		fail.
	write_olinks(_, _, _).
	class_prepare_olinks(S, ID) :-
		ocontacts(ID, OP),
		member(contact(ContID, Ref), OP),
		write(S, '<O ID="'), write(S, ContID), write(S, '" Ref="'), write(S, Ref), write(S, '">'), nl(S),
		once(write_olinks(S, ID, ContID)),
		write(S, '</O>'), nl(S),
		fail.
	class_prepare_olinks(_,_).
	class_prepare_objs(S):-
		g_read('$ObjFactID', ObjFactID),
		asserta(counter(1)),
		=..(Obj, [ObjFactID, ID, ClassID, ParamsList, Desc]),
		Obj,
		counter(GID),
		write(S, '<'), write(S, ClassID), write(S, ' GID="'), write(S, GID),
		write(S, '" WORDS="'),
		atom_hexs(Desc, DescH), atom_concat(DescH, ' ', DescHH), write(S, DescHH),
		write(S, '" ID="'), write(S, ID), write(S, '"'),
		once(class_prepare_params(S, ParamsList)),
		write(S, '>'), nl(S),
		once(class_prepare_ilinks(S, ID)),
		once(class_prepare_olinks(S, ID)),
		write(S, '</'), write(S, ClassID), write(S, '>'), nl(S),
		NewGID is GID+1,
		retractall(counter(_)),
		asserta(counter(NewGID)),
		fail.
	class_prepare_objs(_) :- retractall(counter(_)).
	create_refs :-
		g_read('$ObjFactID', ObjFactID),
		=..(Obj, [ObjFactID, ID, ClassID, _, _]),
		Obj,
		(
		  get_icontacts(ClassID, IC)->
			asserta(icontacts(ID, IC));
			true
		),
		(
		  get_ocontacts(ClassID, OP)->
			asserta(ocontacts(ID, OP));
			true
		),
		fail.
	create_refs.
	prepare_model_for_induct(A) :-
		(
		 var(A)->
			=(A,'_prepared.xml');
			true
		),
		open(A, write, S),
		write(S, '<OBJS>'), nl(S),
		asserta(icontacts('','')), retractall(icontacts(_,_)),
		asserta(ocontacts('','')), retractall(ocontacts(_,_)),
		g_read('$ObjLinkID', ObjLinkID),
		=..(Link, [ObjLinkID, '', '', '', '', '']),
		g_read('$ObjFactID', ObjFactID),
		=..(Obj, [ObjFactID, '', '', '', '']),
		asserta(Link), retractall(Link),
		asserta(Obj), retractall(Obj),
		once(create_refs),
		once(class_prepare_objs(S)),
		write(S, '</OBJS>'), nl(S),
		close(S).
