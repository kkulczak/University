#include <stdio.h>
#include <stdlib.h>

extern unsigned long fib(unsigned long a);

int main(int argc, char* args[]){
	unsigned long a;
	if(argc != 2){
		fprintf(stderr,"Zle dane wejscia, plik liczba\n");
		return 1;
	}
	sscanf(args[1], "%lu", &a);	
	a= fib(a);
	printf("%lu\n", a );
	
	return 0;
}
