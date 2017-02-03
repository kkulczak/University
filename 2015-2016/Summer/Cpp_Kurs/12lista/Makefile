# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Link = -lGL -lGLU -lsfml-graphics -lsfml-window -lsfml-system

Flags = -Wall -Wextra -Wpedantic -std=c++11 -O -g
CPP = g++


life : Makefile   life.o figure.o grid.o 
	$(CPP) $(Flags) -o life   life.o figure.o grid.o $(Link)

life.o : Makefile   life.cpp   figure.h grid.h 
	$(CPP) -c $(Flags) life.cpp -o  life.o


figure.o : Makefile   figure.cpp   figure.h 
	$(CPP) -c $(Flags) figure.cpp -o  figure.o


grid.o : Makefile   grid.cpp   grid.h 
	$(CPP) -c $(Flags) grid.cpp -o  grid.o

clean:
	rm -f *.o life

