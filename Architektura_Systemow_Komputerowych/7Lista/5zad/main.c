#include <stdio.h>
#include <stdlib.h>


extern unsigned int mulf(unsigned int a,unsigned int b);

int main(int argc, char* args[]){
	unsigned int a,b;
	if(argc != 3){
		fprintf(stderr,"Zle dane wejscia, plik liczba liczba\n");
		return 1;
	}
	sscanf(args[1], "%u", &a);
	sscanf(args[2], "%u", &b);	
	printf("%u\n",mulf(a,b) );
	
	return 0;
}
