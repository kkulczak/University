empty(leaf).

insert(Elem, leaf, node(leaf, Elem, leaf) ):-!.
insert(Elem, node(LeftTree, Elem, RightTree), node(LeftTree, Elem, RightTree)):-!.
insert(Elem, node(LeftTree, Var, RightTree), node(NewLeft, Var, RightTree)):-
	Elem < Var,!,
	insert(Elem, LeftTree, NewLeft).
insert(Elem, node(LeftTree, Var, RightTree), node(LeftTree, Var, NewRight)):-
	insert(Elem, RightTree, NewRight).

find(_, leaf):-!,false.
find(Elem, node(_,Elem,_) ):-!.
find(Elem, node(L, Var, _)):-
	Elem < Var,!,
	find(Elem,L).
find(Elem , node(_, _, R)):-
	find(Elem, R).

findMax(node(_,Elem,leaf),Elem):-!.
findMax(node(_,_,R),Elem):-
	findMax(R,Elem).


delMax(node(leaf,_,leaf), leaf ):-!.
delMax(node(L,_,leaf), L):-!.
delMax(node(L,V,R), node(L,V,NewR)):-
	delMax(R, NewR).

delete(E,node(leaf,E,leaf),leaf) :- !.
delete(E,node(L,X,R),node(L1,X,R)) :-
    E < X, !,
    delete(E,L,L1).
delete(E,node(L,X,R),node(L,X,R1)) :-
    delete(E,R,R1).
delete(E,node(L,E,R),R1) :-
    insertRight(R,L,R1).

insertRight(T,node(L,E,leaf),node(L,E,T)) :- !.
insertRight(T,node(L,E,R), node(L,E,R1)) :-
    insertRight(T,R,R1).

find_next()



