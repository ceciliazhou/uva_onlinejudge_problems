#include <stdio.h>

void parseData(int data[102][102], int row, int col){
	int i, j;
	char ch = 0;
	
	for(i = 0; i < row + 2; i++){
		for(j = 0; j < col + 2; j++)
			data[i][j] = 0; 
	}
	
	for(i = 1; i <= row; i++){
		for(j = 1; j <= col; j++){
			ch = 0;
			while(ch != '.' && ch != '*')
				fscanf(stdin, "%c", &ch);
			if(ch == '*'){
				data[i-1][j-1]++;
				data[i-1][j]++;
				data[i-1][j+1]++;
				data[i][j-1]++;
				data[i][j+1]++;
				data[i+1][j-1]++;
				data[i+1][j]++;
				data[i+1][j+1]++;
				data[i][j] = -100; 
			}
		}	
	}
}

void display(int data[102][102], int row, int col){
	int i, j;
	for(i = 1; i <= row; i++){
		for(j = 1; j <= col; j++){
			if(data[i][j] < 0)
				printf("*");
			else
				printf("%d", data[i][j]);		
		}
		printf("\n");
	}
}

int main(void){
	int data[102][102];
	int row = 0,  col = 0;
	long index = 0;
	while(scanf("%i%i", &row, &col) == 2 && row > 0 && row <= 100 && col > 0 && col <= 100 ){
		parseData(data, row, col);
		if(index > 0)
			printf("\n");
		printf("Field #%ld:\n", ++index);
		display(data, row, col);
	}

	return 0;
}
