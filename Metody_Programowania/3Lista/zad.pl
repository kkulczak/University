perm(?,+)/2.
filter(+,?)/2.
count(+,+,?)/3.
select_min(+,?,?)/3.
sub(?,+)/2.
exp(+,+,?)/3.
factorial(+,?)/2.

%	DO UZYTKU

sub(_, []).
sub([H|X], [H|T]):-
	sub(X,T).
sub([_|X],[H|T]):-sub(X,[H|T]).

%	Zadanie 1
perm([],[]).
perm( S, [H|T] ):-
	perm( X, T ),
	select( H, S, X).
	
%	Zadanie 2
filter( [], [] ). 
filter( [ H | X ], [ H | T ] ):-
	H >= 0,
	filter( X, T ).
filter([ H | X ], T):-
	H < 0,
	filter( X, T) .

count( _, [], 0).
count( A, [A], 1).
count(H, [ H | T ], Count ):-
	count(H, T, X),!,
	Count is X+1.
count(Elem, [ _ | T ], Count):-
	count(Elem, T, Count).

exp(_, 0, 1) :- !.
exp(Base, Exp, Res):-
	Y is Exp-1,
	exp( Base, Y, Z),
	Res is Base*Z.
%	Zadanie 3
factorial(0,1):-!.
factorial(X, Y):-
	X > 0
	DecX is X-1, 
	factorial(DecX, DecY),
	Y is DecY*X.
	
concat_number( Digits, Num ):-
	concat_number( Digit, 0, Num).
concat_number( [], Res, Res ).
concat_number( [H | T], Acc, Res ):-
	NextAcc is (Acc*10)+H,
	concat_number(T, NextAcc, Res).)

decimal(Num, Digits):-
	decimal(Num, [], Digits).
decimal(0, Res, Res):- !.
decimal(Num, Acc, Res):-
	Num > 0,
	CurrDig is Num mod 40,
	NewNum is Num // 10,
	decimal( NewNum, [CurrDig | Acc], Res). 
	
%	Zadanie 4
%select_min( [H|_], H, [H] ).

select_min([], _, _).

select_min( [H | T], Min, C ):-
	select_min( T, H, [Min | C] ),
	Min >= H	.

select_min( [H | T], Min, C ):-
	
	select_min( T, Min, [ H | C ] ),
	Min < H.


%select_min( [H | T], H, H ).


	
%	Zadanie 5
insert([],X,[X] ).
insert( [H | T], Elem , [Elem | [H | T]] ):-
	Elem =< H, !.
insert( [H | T], Elem, [H | ResT] ):-
	Elem > H,
	insert( T, Elem,  ResT).


ins_sort([],[]).
ins_sort( [H | T] , Res ):-
	ins_sort( T, S1),
	insert( S1, H, Res).
%	Zadanie 6	
		
	
	


