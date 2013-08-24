#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

string getKey(const string& word){
	string ret;
	for(int i = 0; i < word.length(); i++){
		int j = 0;
		for(; j < i; j++){
			if(word[j] == word[i])
				break;
		}
		ret += '0'+j;
	}
	return ret;
}

map<string, queue<string> > getDictonary(){
	int numOfWords = 0;
	cin >> numOfWords;
	
	map<string, queue<string> > dict;
	while(numOfWords-- > 0){
		string word, eol;
		cin >> word;
		getline(cin, eol);
		string key = getKey(word);
		dict[key].push(word);
	}
	return dict;
}

string decript(const string& word, map<string, queue<string> > & dict){
	map<string, queue<string> >::iterator it = dict.find(getKey(word));
	string ret;
	if(it != dict.end()){
		ret = it->second.front();
		// if(it->second.size()>1)
			// it->second.pop();
	}
	else
		ret = string(word.length(), '*');
	return ret;
}

void decriptLine(const string& line, map<string, queue<string> >& dict){
		int lastWS = -1;
		int nextWS = line.find(' ');
		while(nextWS != string::npos){
			cout << decript(line.substr(lastWS+1, nextWS-lastWS-1), dict) << " ";
			lastWS = nextWS;
			nextWS = line.find(' ', lastWS+1);
		}	
		cout << decript(line.substr(lastWS+1), dict) << " ";
}

int main(){
	map<string, queue<string> > dict = getDictonary();
	string line;
	while(getline(cin, line)){
		decriptLine(line, dict);
		cout << endl;
	}
}
