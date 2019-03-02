Flags = -Og -Wall -Wextra

main: main.o less.o
	gcc $(Flags) -o main main.o less.o
less.o: less.s
	gcc  -c $(Flags) -Og -Wall -Wextra less.s -o less.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o less.o main
