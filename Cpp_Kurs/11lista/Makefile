Flags = -std=c++11 -Wall -Wextra -Wpedantic 

main:	main.o figures.o
	g++ $(Flags) -o main main.o figures.o

main.o:	main.cpp figures.h
	g++ $(Flags) -c -o main.o main.cpp

figures.o: figures.cpp figures.h
	g++ $(Flags) -c -o figures.o figures.cpp


clean:
	rm -f *.o main
