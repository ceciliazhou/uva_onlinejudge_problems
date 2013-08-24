#include <stdio.h>
#include <stdlib.h>

int isJolly(int num[], int size){
	int* exist = (int*) calloc(size, sizeof(int));
	int i = 1;
	for(; i < size; i++){
		int index = abs(num[i] - num[i-1]);
		if(index > size-1 || exist[index]){
			free(exist);
			return 0;
		}
		exist[index] = 1;
	}
	free(exist);
	return 1;	
}

int* readNumbers(int count){
	int *numbers = (int*) calloc(count, sizeof(int));
	int i = 0;
	for(; i < count; i++)
		fscanf(stdin, "%d", &numbers[i]);	
	return numbers;
}

int main(void){
	int num = 0, last = 0;
	while(fscanf(stdin, "%d", &num) == 1 && num > 0){
		int* numbers = readNumbers(num);
		if(isJolly(numbers, num))
			printf("Jolly\n");
		else
			printf("Not jolly\n");
		free(numbers);
		
	}

	return 0;
}
