e(1,2).
e(1,5).
e(2,3).
e(5,6).
e(3,4).
e(4,6).
%	Stack
empty([]).
put(E, S, [E|S]).
get([E|S],E,S).
addall(E,G,S,R):-
	findall(E,G,L),
	append(L,S,R).
/*
search(From, To):-
	empty(Temp),
	put(From, Temp, Stack),
	search(Stack,[],To).
search(Stack,_, To):-
	get(Stack,To, _),!.
search(Stack, Visited, To):-
	get(Stack, H, NewStack),
	member(H, Visited),!,
	search(NewStack, Visited, To).
search(Stack, Visited, To):-
	get(Stack, H, TempStack),
	addall(E, e(H,E), TempStack, NewStack),
	search(NewStack, [H|Visited], To).
*/
%rozw w teorii
extend_path([H|Path], NewPath):-
	e( H, V),
	NewPath= [V,H|Path].
search(From, To, Path):-
	empty(S),
	put([From],S, NewS),
	search(NewS, [], To, RevPath),
	reverse(RevPath, Path).
search(S, _, To, Path):-
	get(S, Path, _),
	Path = [To | _],!.
search(S, Vis, To, Path):-
	get(S, [H|_], NewS),
	member(H, Vis),!,
	search(NewS, Vis, To, Path).
search(S, Vis, To, Path):-
	get(S, [H|T], NewS),
	addall(P, extend_path([H|T],P),NewS, NewNewS), 
	search(NewNewS, [H|Vis], To, Path).















