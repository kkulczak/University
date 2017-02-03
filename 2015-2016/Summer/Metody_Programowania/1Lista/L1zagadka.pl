dom\6(numer,kolor,właściciel,zwierze,peipierosy,napoj)

sasiaduje(X,Y) :- X=1,Y=2.
sasiaduje(X,Y) :- X=2,Y=3.
sasiaduje(X,Y) :- X=3, Y=4.
sasiaduje(X,Y) :- X=4, Y=5.
sasiaduje(X,Y) :- Y=1, X=2.
sasiaduje(X,Y) :- Y=2, X=3.
sasiaduje(X,Y) :- Y=3, X=4.
sasiaduje(X,Y) :- Y=4, X=5.




dom(_,czerwony,anglik,_,_,_).
dom(_,_,hiszpan,pies,_,_).
dom(_,zielony,_,_,_,kawa).
dom(_,_,ukrainiec,_,_,herbata).
dom(X,zielony,_,_,_,_) :- dom(Y,bialy,_,_,_,_),sasiaduje(X,Y).
dom(_,_,_,waz,winstony,_).
dom(_,zolty,_,_,koole,_).
dom(3,_,_,_,_,mleko).
dom(1,_,norweg,_,_,_).
dom(X,_,_,lis,_,_) :- dom(Y,_,_,_,chesterfieldy,_),sasiaduje(X,Y).
dom(_,_,_,_,lucky_stricki,sok).
dom(_,_,japonczyk,_,kentry,_).
dom(X,_,norweg,_,_,_) :- dom(Y,niebieski,_,_,_,_),sasiaduje(X,Y).
dom(X,_,_,kon,_,_) :- dom(Y,_,_,_,koole,_), sasiaduje(X,Y).
