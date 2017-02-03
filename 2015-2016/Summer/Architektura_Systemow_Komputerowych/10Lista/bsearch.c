/*
 * Binary search vs. heap search.
 *
 * $ ./bsearch -n 22 -t 23 -v 0
 * Time elapsed: 5.754351 seconds.
 * $ ./bsearch -n 22 -t 23 -v 1
 * Time elapsed: 0.898724 seconds.
 */
#include "common.h"
#include <math.h>
void fill(int *arr, int n) {
	/* Yeah, gcc allows that, though it's non-standard extension ;) */
	int icmp(const void *a, const void *b) {
		int x = *(const int *)a;
		int y = *(const int *)b;
		if (x < y) return -1;
		if (x > y) return 1;
		return 0;
	}

	for (int i = 0; i < n; i++)
		arr[i] = rand();

	qsort(arr, n, sizeof(int), icmp);
}

void heapify(int *dst, int *src, int n) {
	/* Fill in this procedure! Removed 5 lines here. */
		int i=0;
		int jump =n+1;
		int offset = n/2;
		int place=0;
	while(1){
		place += offset;
		while(place < n){
			dst[i++] = src[place];
			place += jump;
		}
		jump /= 2;
		place = 0;
		offset /=2;
		if (jump < 2)	return;
	}
}

bool binary_search(int *arr, int size, int x) {
	do {
		size >>= 1;
		int y = arr[size];
		if (y == x)
			return true;
		if (y < x)
			arr += size + 1;
	} while (size > 0);

	return false;
}

bool heap_search(int *arr, int size, int x) {
	int i=0;
	while(i < size){
		if (arr[i] == x )	return true;
		/*int b = arr[i] < x;
		i += b ? i + 2 : i + 1 ;
		*/
		if (arr[i] > x) i = (i << 1) +1;
		else i = (i << 1) + 2;
//	Oba wyrazenie (zakomentowane i nie) tlumaczone sa na cmove
	}
	return false;
}

int main(int argc, char **argv) {
/*
TESTOWANIE POPRAWONOSCI WYSZUKIWANIA
	int one[7] = {0,1,2,3,4,5,6};
	int two[7];
	heapify(two,one,7);
	printf("sorted: [ ");
	for(int i=0; i<7; i++){
		printf("%d ",two[i]);
	}
	printf("]\n");
	for(int i=0; i<10; i++){
	printf("i:%d\tbool:%d\n",i, heap_search(two, 7, i));
	}

*/	
	
	int opt, exp = -1, times = -1, var = -1;
	bool err = false;

	while ((opt = getopt(argc, argv, "n:t:v:")) != -1) {
		if (opt == 'n')
			exp = atoi(optarg);
		else if (opt == 't')
			times = 1 << atoi(optarg);
		else if (opt == 'v')
			var = atoi(optarg);
		else
			err = true;
	}

	if (err || exp < 0 || times < 0 || var < 0 || var >= 2) {
		fprintf(stderr,
						"Usage: %s -n log2(size) -t log2(times) -v variant\n", argv[0]);
		return 1;
	}

	int n = (1 << exp) - 1;
	int size = n * sizeof(int);
	int *arr = NULL, *tmp = NULL;
 
	posix_memalign((void **)&arr, getpagesize(), size);

	printf("Generate array of 2^%d-1 elements (%d KiB)\n", exp, size >> 10);

	fill(arr, n);
	if (var == 1) {
		posix_memalign((void **)&tmp, getpagesize(), size);
		heapify(tmp, arr, n);
		free(arr);
		arr = tmp;
	}
	flush_cache();

	printf("Performing %d searches.\n", times);

	_timer_t timer;
	timer_reset(&timer);
	timer_start(&timer);
	for (int i = 0; i < times; i++) {
		if (var == 0) {
			binary_search(arr, n, rand());
		} else {
			heap_search(arr, n, rand());
		}
	}
	timer_stop(&timer);
	timer_print(&timer);

	free(arr);
	return 0;
}
