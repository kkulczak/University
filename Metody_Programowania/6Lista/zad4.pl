solve([X,Y|T], Wyn):-
	Z = last(T),
	solve(X,Y,Z,T,Wyn).
genP(0).
genP(2).
genP(4).
genP(6).
genP(8).
genN(1).
genN(3).
genN(5).
genN(7).
genN(9).

make(L, Wyn):-
	make(L, 0, Wyn).
make([],Acc, Acc).
make([c|T], Acc, Wyn):-
	genN(N),
	NewAcc is Acc * 10 + N,
	make(T, NewAcc, Wyn).
make([s|T], Acc, Wyn):-
	genP(N),
	NewAcc is Acc * 10 + N,
	make(T, NewAcc, Wyn).
solve(X, Y, Z, T, [NewX, NewY|Res]):-
	make(X, NewX),
	mke(Y, NewY),
	NewZ is NewX * NewY,
	make(Z, NewZ),
	check(NewX, NewY, T, Res, NewZ).
check(_,0,[_],[NewZ], NewZ).
check(NewX, NewY, [H|T], [NewH|Res], NewZ):-
	Ylast is NewY mod 10,
	NewH is NewX * Ylast,
	make(H, NewH),
	NewNewY is NewY div 10,
	check(NewX, NewNewY, T, Res, NewZ).
	

