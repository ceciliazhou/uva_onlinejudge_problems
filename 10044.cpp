#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

vector<string> getAuthors(int count){
	vector<string> authors;
	for(int i = 0; i < count; i++){
		string name;
		getline(cin, name);
		authors.push_back(name);
	}
	return authors;
}

vector<string> parseNames(const string& names){
	vector<string> authors;
	int firstName = names.find(',');
	int start = 0;
	while(firstName != string::npos){
		int endOfCurName = names.find(',', firstName+1);
		string curName = names.substr(start, endOfCurName - start);
		authors.push_back(curName);
		start = endOfCurName + 2;
		if(endOfCurName != string::npos)
			firstName = names.find(',', endOfCurName+1);
		else
			firstName = string::npos;
	}
	return authors;	
}

map<string, set<string> > getConnections(int count){
	map<string, set<string> > connectionDB;
	for(int i = 0; i < count; i++){
		string line;
		getline(cin, line);
		vector<string> authors = parseNames(line.substr(0, line.find(':')));
		/* essentially set up a graph represented by a map storing pairs of < author, connected_authors > */
		for(vector<string>::iterator self = authors.begin(); self != authors.end(); self++){
			set<string>& connectedAuthors = connectionDB[*self];
			for(vector<string>::iterator other = authors.begin(); other != authors.end(); other++)
				if(other != self)
					connectedAuthors.insert(*other);
		}
	}
	return connectionDB;
}

map<string, int> calcErdosNumber(const map<string, set<string> >& connectionDB){
	/* a map used to check whether an author is already visited before */
	map<string, int> visited;
	visited["Erdos, P."] = 0;
	
	/* BFS search */
	queue<string> authorQ;
	authorQ.push("Erdos, P.");	
	while(!authorQ.empty()){
		string curAuthor = authorQ.front();
		authorQ.pop();
		map<string, set<string> >::const_iterator it = connectionDB.find(curAuthor);
		const set<string>& connected = it->second;
		int depth = visited.find(curAuthor)->second + 1;
		for(set<string>::const_iterator conn = connected.begin(); conn != connected.end(); conn++){
			if(visited.find(*conn) == visited.end()){
				visited[*conn] = depth;
				authorQ.push(*conn);
			}
		}	
	}
	return visited;
}

int main(){
	int numOfScenarios = 0;
	cin >> numOfScenarios;
	
	for(int i = 1; i <= numOfScenarios; i++){
	
		int P = 0, N = 0;
		cin >> P >> N;
		string endOfLine;
		getline(cin, endOfLine);
		
		map<string, set<string> > connectionDB = getConnections(P);
		vector<string> authors = getAuthors(N);
		map<string, int> reachable = calcErdosNumber(connectionDB);
		
		cout << "Scenario " << i << endl;
		for(vector<string>::iterator it = authors.begin(); it != authors.end(); it++){
			map<string, int>::iterator record = reachable.find(*it);
			if(record != reachable.end())
				cout << *it + " " << record->second << endl;
			else
				cout << *it + " infinity" << endl;			
		}		
	}
}
