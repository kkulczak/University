
Flags = -Wpedantic -Wall -Wextra -std=c++11 -g
CPP = g++


main : Makefile   main.o varchain.o bigint.o rational.o 
	$(CPP) $(Flags) -o main   main.o varchain.o bigint.o rational.o 

main.o : Makefile   main.cpp   rational.h bigint.h polynomial.h varchain.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


varchain.o : Makefile   varchain.cpp   varchain.h 
	$(CPP) -c $(Flags) varchain.cpp -o  varchain.o


bigint.o : Makefile   bigint.cpp   bigint.h 
	$(CPP) -c $(Flags) bigint.cpp -o  bigint.o


rational.o : Makefile   rational.cpp   rational.h bigint.h 
	$(CPP) -c $(Flags) rational.cpp -o  rational.o
clean:
	rm -f main *.o


