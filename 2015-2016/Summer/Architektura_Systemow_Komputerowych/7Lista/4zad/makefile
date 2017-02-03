Flags = -Og -Wall -Wextra

main: main.o fib.o
	gcc $(Flags) -o main main.o fib.o
fib.o: fib.s
	gcc  -c $(Flags) -Og -Wall -Wextra fib.s -o fib.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o fib.o main
