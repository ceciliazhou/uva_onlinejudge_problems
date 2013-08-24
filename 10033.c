/**
 *	Solution to problem <10033>: Interpreter
 *	by: <Shuxiu Zhou>
 *	Implemented in C.
 *
 */

#include <stdio.h>

void readCase(int RAM[], int ramSize){
	char ch;
	int i = 0, instr;
	while(fscanf(stdin, "%c", &ch) == 1 && ch != '\n'){
		fscanf(stdin, "%d%*c", &instr);
		RAM[i++] = (ch - '0')*100 + instr;
	}
}

void execute(int RAM[], int* ip, int registers[]){
	int instruction = RAM[*ip];
	int op1 = instruction/10%10;
	int op2 = instruction%10;
	(*ip)++;
	switch(instruction/100){
		case 0:
			if(registers[op2] != 0)
				*ip = registers[op1];
			break;
		case 2:
			registers[op1] = op2;
			break;
		case 3:
			registers[op1] += op2;
			registers[op1] %= 1000;
			break;
		case 4:
			registers[op1] *= op2;
			registers[op1] %= 1000;
			break;
		case 5:
			registers[op1] = registers[op2]%1000;
			break;
		case 6:
			registers[op1] += registers[op2];
			registers[op1] %= 1000;
			break;
		case 7:
			registers[op1] *= registers[op2];
			registers[op1] %= 1000;
			break;
		case 8:
			registers[op1] = RAM[registers[op2]]%1000;
			break;
		case 9:
			RAM[registers[op2]] = registers[op1]%1000;
			break;		
	}
}

int runCase(int RAM[], int registers[]){
	int ip = 0, count = 0; 
	while(RAM[ip] != 100){
		execute(RAM, &ip, registers);
		count++;
	}
	return count+1;
}

int main(void){
	int RAM[1000];
	int registers[10];
	int numOfCases = 0;
	fscanf(stdin, "%d%*c%*c", &numOfCases);
	while(numOfCases > 0){
		memset(RAM, 0, 1000*sizeof(int));
		memset(registers, 0, 10*sizeof(int));
		readCase(RAM, 1000);
		int numOfInstr = runCase(RAM, registers);
		printf("%d%s", numOfInstr, (numOfCases == 1 ? "\n" : "\n\n"));
		numOfCases--;
	}
	
	return 0;
}
