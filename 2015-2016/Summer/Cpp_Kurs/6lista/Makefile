Flags = -Wextra -Wpedantic -g -Wall -std=c++11 -O3 -flto
CPP = g++ 


nr06 : Makefile   nr06.o listtest.o vectortest.o 
	$(CPP) $(Flags) -o nr06   nr06.o listtest.o vectortest.o 

nr06.o : Makefile   nr06.cpp   vectortest.h listtest.h 
	$(CPP) -c $(Flags) nr06.cpp -o  nr06.o


listtest.o : Makefile   listtest.cpp   listtest.h 
	$(CPP) -c $(Flags) listtest.cpp -o  listtest.o


vectortest.o : Makefile   vectortest.cpp   vectortest.h 
	$(CPP) -c $(Flags) vectortest.cpp -o  vectortest.o
	
clean:
	rm -f nr06 nr06.o listtest.o vectortest.o
