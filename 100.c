/**
 *	Solution to problem <100>: 3n+1
 *	by: <Shuxiu Zhou>
 *	Implemented in C.
 *
 */

#include <stdio.h>
#include <stdlib.h>

unsigned cycleLen(unsigned i, unsigned* cache, int size){
	if(i == 1) return 1;
	if(i < size && cache[i] > 0) return cache[i];
	
	unsigned result = (i & 1) ? (cycleLen(i*3+1, cache, size) + 1) : (cycleLen(i>>1, cache, size) + 1);
	if(i < size) cache[i] = result;
	return result;
}

unsigned maxCycle(unsigned i, unsigned j, unsigned* cache, int size){
	if(i > j) {
		unsigned temp = i;
		i = j;
		j = temp;
	}
	
	unsigned max = 0;
	for(; i <= j; i++){
		unsigned cycle = cycleLen(i, cache, size);
		if(max < cycle)
			max = cycle;
	}
	return max;
}

int main(void){
	unsigned* cache = (unsigned*)calloc(100000, sizeof(unsigned));
	unsigned i = 0, j = 0;
	
	while(fscanf(stdin, "%d%d", &i, &j) == 2){
		unsigned max = maxCycle(i, j, cache, 100000);
		printf("%d %d %d\n", i, j, max);	
	}
	
	free(cache);
	return 0;
}
