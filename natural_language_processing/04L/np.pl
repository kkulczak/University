%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Dictionary
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


:- [skladnicaTagsBases].

hasTag(Word, Tag) :- tagAndBase(Word,_Base,Tag).
hasTag(w, prep:loc).

:- [walenty_subst].
% hasWalent(Word1, Word2, P) :- walenty(Word1, Word2, P).
:- op(1050, xfx, ==>).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GRAMMAR
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


likeAdj(adj:L:P:R:_, L, P, R).
likeAdj(ppas:L:P:R:_, L, P, R).
likeAdj(pact:L:P:R:_, L, P, R).


likeRzecz(subst:L:P:R, L, P, R).
likeRzecz(ger:L:P:R, L, P, R).
likeRzecz(depr:L:P:R, L, P, R).
% is(brev:_, L, P, R).




np(L,P,R) ==> adj(L,P,R), np(L,P,R).
% 
% dodane preze KACPER
% 
np(L,P,R) ==> np(L,P,R), adj(L,P,R).
np(_,P,_) ==> [X], [Y], np(_,P,_), {walenty(X,Y,P)}.
np(L,P,R) ==> np(L,P,R), [','], np(L,P,R).

np(L,P,R) ==> liczebnik(L,P,R,_), np(L,P,R).
np(L,P,R) ==> np(L,P,R), [w], np(_, loc, _).
np(L,P,R) ==> np(L,P,R), [z], np(_, inst, _).

% np(L,P,R) ==> np(L,P,R), [w], [X], {hasTag(X, subst:_:loc:_)}.
%


% np(L,P,R) ==> [X], ['.'], np(L,P,R), {hasTag(X, brev:pun)}.



% np(L,P,R) ==> [X], np(L,P,R), {hasTag(X, brev:npun)}.


liczebnik(L,P,R,A) ==> [X], {hasTag(X, num:L:P:R:A)}.

% np(L,P,R) ==> np(L,P,R), [X], {hasTag(X, fin:L:ter:_)}.
% np(L,P,R) ==> np(L,P,R), [X], np(_, gen, _), {hasTag(X, fin:L:ter:_)}.
np(pl,P,R1) ==> np(_,P,R1), [oraz], np(_,P,_R2).
np(pl,P,R1) ==> np(_,P,R1), [więc], np(_,P,_R2).



% ppron3(L,P,R) ==> [X], {hasTag(X, ppron3:L:P:R:_:_:_)}.
% np(L,_,R) ==> ppron3(L,gen,R), np(L,nom,_).

% np(L,P,R) ==> rzeczownik(L,P,R), rzeczownik(L,P,R).
% rzeczownik(L,P,R) ==> [X], {hasTag(X, subst:L:P:R)}.

% 
% DODANE PREZE ZNAS END
% 
np(L,P,R) ==> np(L,P,R), np(_,gen,_).


np(pl,P,R1) ==> np(_,P,R1), [i], np(_,P,_R2).

% np(L,P,R) ==> [X], {hasTag(X, subst:L:P:R)}.
np(L,P,R) ==> [X], {hasTag(X, Tag), likeRzecz(Tag, L, P, R)}.


adj(L,P,R) ==> [X], {hasTag(X, Tag), likeAdj(Tag,L,P,R)}.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
commasToList((X,Y), [X|Rest]) :- 
   !, commasToList(Y,Rest).
commasToList(X,[X]).   


allign( [[W]| Rest], [W|T], Alligment) :-
   !,allign(Rest, T, Alligment). 
allign( [At|Rest], Ts, [ (At,Pref) | ARest]):-
   Pref = [_|_],
   append(Pref, RestT, Ts),
   allign(Rest, RestT, ARest).
allign( [{C}], [], []) :- C.
allign( [], [], []).


   
parse(A,TokensToParse) :-
   (A ==> Right),
   commasToList(Right, ListRight),
   allign(ListRight, TokensToParse, Alligment),
   parsePairs(Alligment).
   
parsePairs([]).
parsePairs([(A,L)| Rest]):-
   parse(A,L),
   parsePairs(Rest).

writeList([A]) :- write(A),!.
writeList([A|As]):- write(A), write(' '),writeList(As).
   
parse0 :-
   see('phrases.pl'),
   % see('bad_phrases.pl'),
   parsing,
   seen.

parsing :-
   repeat,
   read(L),
   analyze(L),
   L = end_of_file,!.

analyze(end_of_file) :-
   write('DONE!'), nl, !.
analyze(L) :-   
   length(L,N),
   N < 7,
   parse(np(_,_,_), L),
   write('GOOD:'),
   writeList(L),nl,!.
analyze(L) :-
   write('BAD:'), writeList(L),nl,!.


:- parse0.