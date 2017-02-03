Flags = -Wall -Wextra -pedantic -std=c++11 -Wno-unused-parameter -g -std=c++11
CPP = g++


main : Makefile   main.o ../5lista/tree.o matching.o rewrite_system.o
	$(CPP) $(Flags) -o main   main.o ../5lista/tree.o matching.o rewrite_system.o

main.o : Makefile   main.cpp   rewrite_system.h ../5lista/tree.h matching.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


../5lista/tree.o : Makefile   ../5lista/tree.cpp   ../5lista/tree.h 
	$(CPP) -c $(Flags) ../5lista/tree.cpp -o  ../5lista/tree.o


matching.o : Makefile   matching.cpp   matching.h ../5lista/tree.h 
	$(CPP) -c $(Flags) matching.cpp -o  matching.o

rewrite_system.o: Makefile rewrite_system.cpp rewrite_system.h
	$(CPP) -c $(Flags) rewrite_system.cpp -o rewrite_system.o

