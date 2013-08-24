/**
 *	Solution to problem <706>: LCD Display
 *	by: <Shuxiu Zhou>
 *	Implemented in C.
 *
 */
 
#include <stdio.h>

/**
	for row 1, 3, 5: 
		0 means there is no '-', while 1 means there is.
	for row 2, 4:
		1 means '|' on right side, while 2 means on left side and 3 means both.
 */
int digitStrings[10][5] = {	{1, 3, 0, 3, 1}, 
							{0, 1, 0, 1, 0}, 
							{1, 1, 1, 2, 1},
							{1, 1, 1, 1, 1},
							{0, 3, 1, 1, 0},
							{1, 2, 1, 1, 1},
							{1, 2, 1, 3, 1},
							{1, 1, 0, 1, 0},
							{1, 3, 1, 3, 1},
							{1, 3, 1, 1, 1}};

char** toString(int size, int digit){
	int width = size + 2, height = size * 2 + 3; 
	char** string = (char**) calloc(height, sizeof(char*));
	
	int i, j, k;
	for(i = 0, j = 0; i < 5; i++, j++){
		string[j] = (char*) calloc(width+1, sizeof(char));
		memset(string[j], ' ', width);
		
		if(i % 2 == 0){/* horizontal */
			if(digitStrings[digit][i] & 1)
				memset(&string[j][1], '-', size);
		}
		else{ /* vertical */			
			if(digitStrings[digit][i] & 1)
				string[j][width-1] = '|';
			if(digitStrings[digit][i] & 2)
				string[j][0] = '|';
			for(k = 1; k < size; k++, j++)
				string[j+1] = string[j];
		}
	}
	return string;
}


void LCDdisplay(char** digits[], int count, int row, int col){
	int i, j, k;
	for(i = 0; i < row; i++)
		for(j = count - 1; j >= 0; j--)
			printf("%s%c", digits[j][i], (j==0 ? '\n' : ' '));
	printf("\n");
}

void destroy(char** digit, int size){
	int i;
	for(i = 0; i < 5; i++)
		free(digit[i/2*(size+1)+(i%2)]);
	free(digit);	
}


void processNumber(int s, int n){
	/* 0 <= n <= 99 999 999, no more than 8 digits */
	char** digits[8]; 
	int count = 0;
	do{
		digits[count++] = toString(s, n % 10);		
		n /= 10;
	}while(n != 0);
	
	LCDdisplay(digits, count, s*2+3, s+2);
	while(count > 0)
		destroy(digits[--count], s);
}


int main(void){
	int s, n;
	while(fscanf(stdin, "%d%d", &s, &n) == 2 && s >= 1 && s <= 10 && n >= 0 && n <= 99999999)
		processNumber(s, n);
	return 0;
}
