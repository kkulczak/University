#include <stdio.h>

extern void insert_sort(long *first, long *last);

int main(){
	long tab[5]={7,2,10,6,0};
	insert_sort(tab, tab+4);
	int i=0;
	while(i<5 ){
		printf("%ld ", tab[i]);
		i++;
	}
	printf("\n");
	return 0;
}
