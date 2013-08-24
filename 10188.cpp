#include <string>
#include <iostream>
using namespace std;

bool PE(const string& s1, const string& s2){
	int i = 0, j = 0, M = s1.length(), N = s2.length();
	while(i < M || j < N){
		while(i < M && (s1[i] < '0' || s1[i] > '9'))
			i++;
		while(j < N && (s2[j] < '0' || s2[j] > '9'))
			j++;
		if(i == M && j == N) return true;
		if(i == M || j == N || s1[i] != s2[j]) 
			return false;
		if(i < M) i++;
		if(j < N) j++;
	}
	return i >= M && j >= N;
}

int main(){
	int n = 0, m = 0, caseID = 0;
	while(cin >> n && n > 0){
		string solu, team, line;
		getline(cin, line);
		for(int i = 0; i < n; i++){
			getline(cin, line);
			solu += '\n'+line;
		}
		
		cin >> m; getline(cin, line);
		for(int i = 0; i < m; i++){
			getline(cin, line);
			team += '\n'+line;
		}
		
		if(solu == team)
			cout << "Run #" << ++caseID << ": Accepted" << endl;
		else if(PE(solu, team))
			cout << "Run #" << ++caseID << ": Presentation Error" << endl;
		else
			cout << "Run #" << ++caseID << ": Wrong Answer" << endl;
	}
}