Flags = -g -Wpedantic  -Wall -Wextra -std=c++11
CPP = g++


solve : Makefile   solve.o fifteen.o 
	$(CPP) $(Flags) -o solve   solve.o fifteen.o 

solve.o : Makefile   solve.cpp   fifteen.h move.h 
	$(CPP) -c $(Flags) solve.cpp -o  solve.o


fifteen.o : Makefile   fifteen.cpp   fifteen.h move.h 
	$(CPP) -c $(Flags) fifteen.cpp -o  fifteen.o
	
clean:
	rm -f *.o solve
