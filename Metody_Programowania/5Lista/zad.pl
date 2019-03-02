%	Zadanie 1
% cwiczenia
appn([],[]).
appn([H | T], Exit):-
	append(H, Res, Exit ),
	appn(T, Res).
%	Zadanie 2
flatten(List,Exit):-
	flatten(List, [], Exit).
flatten([], Exit, Exit).
flatten([H | T], Acc, Exit):-
	is_list(H),!,
	flatten(T, Acc, Acc1),
	flatten(H, Acc1, Exit).
flatten( [H|T], Acc,[H| Exit]):-
	flatten(T, Acc, Exit).
%	Zadanie 3
halve(List, Left, Right):-
	halve( List, Left, List, Right).
halve([H|T],[H|Left],[_,_|RTemp],Right):-
	halve( T, Left , RTemp, Right),!.
halve(T,[],_,T).
%	Zadanie 4
merge( X, [], X ):-!.
merge( [], X, X):-!.
merge([H1 | T1], [H2 | T2], [H1|Result]):-
	H1 < H2,!,
	merge( T1 , [H2 | T2], Result).
merge([H1 | T1], [H2 | T2], [H2|Result]):-
	merge([H1 | T1], T2, Result).

merge_sort([],[]):-!.
merge_sort([X],[X]):-!.
merge_sort( List, Exit):-
	halve(List, HalfList1, HalfList2),
	merge_sort(HalfList1, Res1),
	merge_sort(HalfList2, Res2),
	merge(Res1, Res2, Exit).
%	Zadanie 5
second_list_part(0, Exit, Exit).
second_list_part(Num, [_ | T], Exit):-
	NextNum is Num - 1,
	second_list_part(NextNum, T, Exit).

merge_sort([H | _], 1, [H]).
merge_sort( _, 0, []).
merge_sort(List, N, Exit ):-
	N1 is N // 2,
	N2 is N- N1,
	merge_sort(List, N1, Res1),
	second_list_part(N1, List, PartList ),
	merge_sort(PartList, N2, Res2),
	merge(Res1, Res2, Exit),!.
	
merge_sort2(List, Exit):-
	length(List, N),
	merge_sort(List, N, Exit). 
%	Zadanie 6
make_lists(List , Exit):-
	make_lists( List, [], Exit).
make_lists([], Exit, Exit).
make_lists([H|T], Acc, Exit):-
	make_lists( T, [[H] | Acc], Exit).

rev_merge_sort(List, Exit):-
	make_lists(List, NewList),
	merge_double(NewList, Exit),!.

merge_double([Exit],Exit).
merge_double(List, Exit):-
	merge_double( List, [], Result),
	merge_double(Result, Exit).
merge_double( [], Acc, Acc).
merge_double( [X], Acc, [X|Acc]).
merge_double( [H1, H2| T], Acc, Exit):-
	merge(H1, H2, Res),!,
	merge_double( T, [Res | Acc], Exit).
%	Zadanie 7
split(List, M, Small, Big):-
	split(List, M, Small, Big, [], []).
split([], _, Small, Big, Small, Big).
split([H|T], M, Small, Big, SAcc, BAcc):-
	H < M,!,
	split(T,M,Small,Big, [H|SAcc], BAcc).
split([H|T], M, Small, Big, SAcc, BAcc):-
	split(T,M, Small,Big, SAcc,[H| BAcc]).
	
qsort(List, Exit):-
	qsort(List, [], Exit).
qsort([], Exit, Exit).
qsort([H|T], Acc, Exit):-
	split(T, H, Small, Big),
	qsort(Big,Acc,NextAcc),
	qsort(Small,  [H | NextAcc], Exit).
%	Zadanie 9
%generowanie naturalnych
next(0).
next(X):-
	next(X1),
	X is X1+1.
%Robimy zadanie
%alter -> genrujemy = 0;1;-1;2;-2;3;-3;...
alter(0).
alter(X):-
	next(X1),
	(X is X1; X is -X1).
% Uproszczenie zadania do samych Naturalnych
sum(0,0,0).
sum(X,Y,Z):-
	next(Z),
	next_to(0,X,Z),
	Y is Z - X.
	
next_to(Y,Y,Z).
next_to(Y,X,Z):-
	Y1 is Y +1,
	Y1 < Z,
	next_to(Y1,X,Z).
	











