#include <stdio.h>
#include <stdlib.h>

extern int clz(long a);

int main(int argc, char* args[]){
	long a;
	if(argc != 2){
		fprintf(stderr,"Zle dane wejscia, plik liczba\n");
		return 1;
	}
	sscanf(args[1], "%lx", &a);
	printf("%d\n", clz(a) );
	
	return 0;
}
