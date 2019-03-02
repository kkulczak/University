Format danych:

wiersze z dwoma słowami:

<wynik> <kod-planszy>
1 __________________0_10_____011_____0001_______11________________

kod planszy składa się z 64 znaków, opisujących kolejne wiersze planszy. Znaczenie:
'1' -- czarny pionek
'0' -- biały pionek
'_' -- pole puste


-1 zwycięstwo białego (mina, 0)
+1 zwycięstwo czarnego (maxa, 1)
(remisów nie ma, w danych są jedynie sytuacje, które dały przynajmniej 7 punktową przewagę któremuś z graczy)


Dwa pliki z danymi:
smaller.dat -- wartość planszy szacowana za pomocą kilku gier 
bigger.dat -- wartość planszy szacowana za pomocą (potencjalnie) jednej gry
