Flags = -Og -Wall -Wextra

main: main.o clz.o
	gcc $(Flags) -o main main.o clz.o
clz.o: clz.s
	gcc  -c $(Flags) -Og -Wall -Wextra clz.s -o clz.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o clz.o main
