/**
 *	Solution to problem <10189>: Minesweeper
 *	by: <Shuxiu Zhou>
 *	Implemented in C.
 *
 */

#include <stdio.h>
#include <stdlib.h>

char** readField(int row, int col){
	char** data = (char**) calloc(row + 2, sizeof(char*));
	if(!data) return 0;
	
	data[0] = data[row+1] = (char*) calloc(col + 2, sizeof(char));
	int i, j;
	for(i = 1; i <= row; i++){
		data[i] = (char*) calloc(col+2, sizeof(char));
		for(j = 1; j <= col; j++){
			/* skip any character other than '*' and '.', maybe too much considered? */
			while(data[i][j] != '*' && data[i][j] != '.')
				fscanf(stdin, "%c", &data[i][j]);
		}
	}
	return data;
}

int countMines(char** data, int r, int c){
	int count = 0;
	int i, j;
	for(i = r - 1; i <= r + 1; i++){
		for(j = c - 1; j <= c + 1; j++)
			if(data[i][j] == '*')
				count++;
	}
	return count;
}

void parseField(char** data, int row, int col){
	int i, j;
	for(i = 1; i <= row; i++){
		for(j = 1; j <= col; j++){
			if(data[i][j] != '*')
				data[i][j] = '0' + countMines(data, i, j);
		}
	}
}

void display(char** data, int row, int col){
	int i, j;
	for(i = 1; i <= row; i++){
		for(j = 1; j <= col; j++)
			printf("%c", data[i][j]);
		printf("\n");		
	}	
}

void destroy(char** data, int row){
	int i;
	for(i = 0; i < row; i++)
		free(data[i]);
	free(data);
}

int main(void){
	int row = 0, col = 0;
	int fieldNum = 0;
	while(fscanf(stdin, "%d%d", &row, &col) == 2 && row > 0 && row <= 100 && col > 0 && col <= 100){
		char** data = readField(row, col);
		parseField(data, row, col);

		if(fieldNum > 0)
			printf("\n");
		printf("Field #%d:\n", ++fieldNum);
		display(data, row, col);
		
		destroy(data, row);
	}	
	return 0;
}

