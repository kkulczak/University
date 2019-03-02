%	Zadanie 1
stack_empty([]).
stack_put(Elem, Stack, [Elem | Stack]).
stack_get([Elem | Stack], Elem, Stack).
stack_addall(E,G,S,R):-
	findall(E,G,L),
	append(L,S,R).
/*stack_addall(_, _, [],[]):- 
	!,
	false. 
stack_addall(H, H, [H | S], S).
stack_addall(Exit, Goal, [H | T], [H|NewStack]):-
	stack_addall(Exit, Goal,  T, NewStack).
*/

queue_empty(X-Y):-
	X==Y.
queue_get(Elem, [Elem|Queue]-End,Queue-End).
queue_put(Elem, Queue-End, Queue-[Elem|End]).
queue_addall(E,G,S-L, S-Hole):-
	findall(E,G,L,Hole)).
%ćwiczenia
app(X-Y, Y-Z, X-Z).
snoc(E, X-[E|Y],X-Y).

