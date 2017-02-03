%	Zadanie 1
len(X, Len ):-
	len(X, Len, 0).
len( [],Len, Len ).
len( [_ | T], Len, Acc ):-
	Len \== Acc,
	NextAcc is Acc+1,
	len(T,Len, NextAcc).
%	Zadanie 2
conn(a,b).
conn(b,c).
conn(c,d).
conn(d,a).
trip(X ,Y , T):-
	trip(X, Y, T, [Y] ).
trip(X,X,T,Z):-
	T = Z.
trip( X, Y, T, Exists ):-
	conn(Z,Y),
	\+ member(Z, Exists),
	trip(X, Z, T ,[Z | Exists]).
%	Zadanie 3

%	Zadanie 4
mirror(leaf,leaf).
mirror(node( Left1, Middle, Right1 ), node( Left2, Middle, Right2 )):-
	mirror( Right1 , Left2 ),
	mirror( Left1, Right2 ).

flattern(Tree, List):-
	flattern(Tree,[],List).
flattern(leaf,A,A).
flattern( node(Left,Middle,Right), Acc ,List ):-
	flattern(Right, Acc, Acc1),
	flattern(Left, [Middle | Acc1], List). 
%	Zadanie 5

insert(leaf, Enum, node(leaf,Enum,leaf)):-!.
insert(node(Left,Middle,Right), Elem, node(LeftNew,Middle,Right)):-
	Elem =< Middle,
	insert(Left, Elem, LeftNew).
insert(node(Left,Middle,Right), Elem, node(Left,Middle,RightNew)):-
	Elem > Middle,
	insert(Right, Elem, RightNew).
treesort(List, Result):-
	treesort(leaf, List, Result).
treesort(Tree, [], Result):-
	flattern(Tree, Result).
treesort(Tree,[H |T], Result):-
	insert(Tree, H, NewTree),
	treesort(NewTree, T, Result).

%	Zadanie 6
concat_number( Digits, Num ):-
	concat_number( Digits, 0, Num).
concat_number( [], Res, Res ).
concat_number( [H | T], Acc, Res ):-
	NextAcc is (Acc*10)+H,
	concat_number(T, NextAcc, Res).
sub(_, []).
sub([H|X], [H|T]):-
	sub(X,T).
sub([_|X],[H|T]):-sub(X,[H|T]).

%length(_L, 7),
%  sub([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], _L),
%  permutation([_A, _C, _E, _P, _R, _S, _U], _L),
%  _U \= 0,
%  _P \= 0, 
%  concat_number([_U, _S, _A], USA),
%  concat_number([_U, _S, _S, _R], USSR),
%  concat_number([_P, _E, _A, _C, _E], PEACE),
%  PEACE is USA + USSR.	

%	Zadanie 7
revall(List, Result):-
	revall(List,Result,[]).
revall([], X, X).
revall([Head | Tail], Result, Acc):-
	revall( Head, NewHead),!,
	revall(Tail, Result, [ NewHead | Acc]).
revall( [Head | Tail], Result, Acc ):-
	revall( Tail, Result, [Head | Acc]).
	

	
	





