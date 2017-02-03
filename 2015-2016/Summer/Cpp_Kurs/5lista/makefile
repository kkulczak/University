

Flags = -g -Wpedantic -Wall -Wextra -std=c++11 -Wshadow
CPP = g++


main : makefile   tree.o main.o 
	$(CPP) $(Flags) -o main   tree.o main.o 

tree.o : makefile   tree.cpp   tree.h 
	$(CPP) -c $(Flags) tree.cpp -o  tree.o


main.o : makefile   main.cpp   tree.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o

