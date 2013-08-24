#include <iostream>
#include <vector>

using namespace std;

vector<vector<string> > getInput(){
	vector<vector<string> > input;
	string line;
	while(getline(cin, line)){
		vector<string> paragraph;
		if(!line.empty()){
			paragraph.push_back(line);
			while(getline(cin, line) && !line.empty())
				paragraph.push_back(line);
		}
		input.push_back(paragraph);
	}	
	return input;
}

void breakLine(string& line, vector<string>& paragraph){
	paragraph.push_back(line.substr( 0, line.find_last_not_of( " \t" ) + 1 ));
	line.erase();
} 

vector<string> format(const vector<string>& paragraph){
	vector<string> newPara;
	string line;
	for(int i = 0; i < paragraph.size(); i++){
		//combine two consecutive lines by replacing newline character with space
        if (!line.empty()) line += " "; 
		
		//break line if blank line follows.
		string curLine = paragraph[i];
		if((curLine[0] == ' ' || curLine[0] == '\t') && i > 0)
			breakLine(line, newPara);

		for(int j = 0; j < curLine.length();j++){
			//always keep non-newline white spaces
			if(curLine[j] == ' ' || curLine[j] == '\t')
				line += curLine[j];
			else{ 
				int nextWS = curLine.find_first_of(" \t\n", j);
				int nextWordLength = (nextWS == string::npos) ? curLine.length() - j : nextWS - j;
				//break line if next word doesn't fit current line.
				if(line.length() + nextWordLength > 72){
					breakLine(line, newPara);
				}
				
				//take in next word, whether a line-break occurs or not.
				line += curLine.substr(j, nextWordLength);
				j += nextWordLength - 1;
			}
		}
	}
    line = line.substr( 0, line.find_last_not_of(" \t\n") + 1 );
	if(!line.empty()) newPara.push_back(line);
 
    return newPara;	
}

void printParagraph(const vector<string>& paragraph){
	for(int i = 0; i < paragraph.size(); i++)
		cout << paragraph[i] << endl;
}

int main(){
	vector<vector<string> > input = getInput();
	for(int i = 0; i < input.size(); i++){
		printParagraph(format(input[i]));
		if(i < input.size() - 1)
			cout << endl;
	}
}

