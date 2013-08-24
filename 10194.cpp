#include <cstdio>
#include <locale>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct team{
	string name;
	int games;
	int wins;
	int ties;
	int loss;
	int goalsScored;
	int goalsAgainst;
	team(string n):name(n), games(0), wins(0), ties(0), loss(0), goalsScored(0), goalsAgainst(0){}
};

bool before(const team& t1, const team& t2){
	int p1 = 3*t1.wins + 1*t1.ties;
	int p2 = 3*t2.wins + 1*t2.ties;
	if(p1 != p2) return p1 > p2;
	if(t1.wins != t2.wins) return t1.wins > t2.wins;
	
	int gd1 = t1.goalsScored - t1.goalsAgainst;
	int gd2 = t2.goalsScored - t2.goalsAgainst;
	if(gd1 != gd2) return gd1 > gd2;
	if(t1.goalsScored != t2.goalsScored) return t1.goalsScored > t2.goalsScored;
	if(t1.games != t2.games) return t1.games < t2.games;
	
	char n1[31], n2[31];
	transform(t1.name.begin(), t1.name.end(), n1, ::toupper);
	transform(t2.name.begin(), t2.name.end(), n2, ::toupper);
	n1[t1.name.length()] = 0;
	n2[t2.name.length()] = 0;
	return strcmp(n1, n2) < 0;
}

vector<team> getTeams(){
	int num = 0;
	cin >> num;
	string line;
	getline(cin, line);

	vector<team> teams;
	for(int i = 0; i < num; i++){
		getline(cin, line);
		teams.push_back(team(line));
	}
	return teams;
}

void updateTeams(vector<team>& teams, const string& team1, const string& team2, int g1, int g2){
	int t1, t2;
	for(int i = 0; i < teams.size(); i++){
		if(teams[i].name == team1) t1 = i;
		else if(teams[i].name == team2) t2 = i;
	}
	
	teams[t1].goalsScored += g1;
	teams[t1].goalsAgainst += g2;
	teams[t1].games++;
	teams[t2].goalsScored += g2;
	teams[t2].goalsAgainst += g1;	
	teams[t2].games++;	
	if(g1 == g2){
		teams[t1].ties++;
		teams[t2].ties++;
	}
	else if(g1 < g2){
		teams[t1].loss++;
		teams[t2].wins++;
	}
	else{
		teams[t1].wins++;
		teams[t2].loss++;
	}		
}

void setupTeams(vector<team>& teams){
	int num = 0;
	cin >> num;
	string line;
	getline(cin, line);
	
	for(int i = 0; i < num; i++){
		getline(cin, line);
		int firstSharp = line.find('#'); //Brazil#2@1#Scotland
		int secondSharp = line.find('#', firstSharp+1);
		string team1 = line.substr(0, firstSharp);
		string team2 = line.substr(secondSharp+1);
		stringstream ss(line.substr(firstSharp+1));
		int goals1, goals2;
		char at;
		ss >> goals1 >> at >> goals2;
		// printf("%s--%d--%d--%s\n", team1.c_str(), goals1, goals2, team2.c_str());
		updateTeams(teams, team1, team2, goals1, goals2);	
	}
}

int main(){
	int tournaments = 0;
	cin >> tournaments;	
	string tournamentName;
	getline(cin, tournamentName);
		
	while(tournaments-- > 0){
		getline(cin, tournamentName);
		vector<team> teams = getTeams();
		setupTeams(teams);
		sort(teams.begin(), teams.end(), before);
		printf("%s\n", tournamentName.c_str());
		for(int i = 0; i < teams.size(); i++)
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", 
					i+1, teams[i].name.c_str(), teams[i].wins*3+teams[i].ties,
					teams[i].games, teams[i].wins, teams[i].ties,
					teams[i].loss, teams[i].goalsScored - teams[i].goalsAgainst, 
					teams[i].goalsScored, teams[i].goalsAgainst);
		if(tournaments > 0)
			printf("\n");
	}
}
