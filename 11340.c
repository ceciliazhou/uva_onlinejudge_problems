#include <stdio.h>
#include <limits.h>

void readValues(int* values){
	int numOfCh, value;
	fscanf(stdin, "%d%*c", &numOfCh);
	unsigned char ch;
	while(numOfCh-- > 0){
		fscanf(stdin, "%c%d%*c", &ch, &value);
		values[ch] = value;
	}
}

int evaluateArticle(int* values){
	int numOfLines = 0, total = 0;
	fscanf(stdin, "%d%*c", &numOfLines);
	unsigned char ch;
	while(numOfLines > 0 && fscanf(stdin, "%c", &ch) == 1){
		
		if(ch == '\n')
			numOfLines--;
		else
			total += values[ch];
	}	
	return total;
}

int main(){
	int numOfTests = 0;
	fscanf(stdin, "%d%*c", &numOfTests);
	int values[UCHAR_MAX+1];
	while(numOfTests-- > 0){
		memset(values, 0, (UCHAR_MAX+1)*sizeof(int));
		readValues(values);		
		int total = evaluateArticle(values);
		printf("%.2f$\n", total/100.0);
	}
}

