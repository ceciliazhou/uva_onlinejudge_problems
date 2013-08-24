#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_COLOR 50
using namespace std;

bool validate(int graph[][MAX_COLOR+1], int size = MAX_COLOR+1){
		for(int i = 1; i < size; i++)
				if(graph[i][0] % 2 != 0)
						return false;
		return true;
}

void dfs(int graph[][MAX_COLOR+1], int size, int from, vector<int>& path){
		for(int to = 1; to < size; to++){
				if(graph[from][to] > 0){
						graph[from][to]--;
						graph[to][from]--;
						dfs(graph, size, to, path);
				}
		}
		path.push_back(from);
}

int main(){
		int graph[MAX_COLOR+1][MAX_COLOR+1]; //graph[i][0] is degree of i.
		int cases = 0, caseNo = 0;
		cin >> cases;
		while(++caseNo <= cases){
				fill(&graph[0][0], &graph[MAX_COLOR][MAX_COLOR]+1, 0);
		
				int beads = 0, s = 0, t = 0;
				cin >> beads;
				for(int i = 0; i < beads; i++){
						cin >> s >> t;
						graph[s][t]++;
						graph[t][s]++;
						graph[s][0]++; 
						graph[t][0]++; 
				}
				
				cout << "Case #" << caseNo << endl;
				if(!validate(graph))
						cout << "some beads may be lost" << endl;
				else{
						vector<int> path; 
						dfs(graph, MAX_COLOR+1, t, path);
						for(int i = 1; i < path.size(); i++)
								cout << path[i-1] << " " << path[i] << endl;
				}
						
				if(caseNo < cases)
						cout << endl;
		}

}