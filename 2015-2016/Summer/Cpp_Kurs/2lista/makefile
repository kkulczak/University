
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -g -Wpedantic  -Wall -Wextra -std=c++11
CPP = g++


main : makefile   main.o rational.o matrix.o 
	$(CPP) $(Flags) -o main   main.o rational.o matrix.o 

main.o : makefile   main.cpp   matrix.h rational.h vector.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


rational.o : makefile   rational.cpp   rational.h 
	$(CPP) -c $(Flags) rational.cpp -o  rational.o


matrix.o : makefile   matrix.cpp   matrix.h rational.h vector.h 
	$(CPP) -c $(Flags) matrix.cpp -o  matrix.o
