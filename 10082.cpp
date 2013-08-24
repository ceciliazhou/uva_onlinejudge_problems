#include <iostream>

using namespace std;

char translatePunc(char input){
	switch(input) {
		case '-': return '0';
		case '=': return '-';
		case '[': return 'P';
		case ']': return '[';
		case '\\': return ']';
		case ';': return 'L';
		case '\'': return ';';
		case ',': return 'M';
		case '.': return ',';
		case '/': return '.';
	}
	return 0;
}

int main(){
	char ch[]= {0, 'V', 'X', 'S', 'W', 'D', 'F',
							 'G', 'U', 'H', 'J', 'K', 'N', 'B',
							 'I', 'O', 0, 'E', 'A', 'R',
							 'Y', 'C', 'Q', 'Z', 'T', 0};
	
	char digit[] = {'9', '`', '1', '2', '3', '4', '5', '6', '7', '8'};
	string line, output;
	while(getline(cin, line)){
		output = "";
		for(int i = 0; i < line.length(); i++){
			char c = line[i];
			if(c == ' ') 
				output += " ";
			else if(c < 'Z'  && c > 'A')
				output += ch[c-'A'];
			else if(c <= '9' && c >= '0')
				output += digit[c-'0'];
			else 
				output += translatePunc(c);
		}
		cout << output << endl;
	}
}