Flags = -g -Wpedantic -Wall -Wextra -std=c++11

main : makefile main.o stack.o
	g++ $(Flags) -o main main.o stack.o

main.o : makefile main.cpp stack.h
	g++ -c $(Flags) -o main.o	main.cpp

stack.o : makefile stack.cpp stack.h
	g++ -c $(Flags) -o stack.o	stack.cpp
