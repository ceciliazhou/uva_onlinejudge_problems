#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>

#define MAX_APP 26
#define MAX_HOST 10
#define MAX_NODE 38
using namespace std;

void augment(int flow[][MAX_NODE], int from[MAX_NODE]){
		int v = MAX_NODE-1;
		while(v != 0){
				flow[from[v]][v]++;
				flow[v][from[v]]--;
				v = from[v];
		}
}

bool findAugmentPath(int cap[][MAX_NODE], int flow[][MAX_NODE]){
    int from[MAX_NODE];
    fill(from,from+MAX_NODE,-1);
    
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        
        for(int v = 0; v < MAX_NODE; v++){
            if(flow[u][v] < cap[u][v] && from[v]==-1){
                from[v]=u;
                if(v == MAX_NODE-1) {
										augment(flow, from);
										return true;
								}
                Q.push(v);
            }
        }
    }
    return false;
}

int main(){
		string line;
		int cap[MAX_NODE][MAX_NODE]; //capacity graph, s = 0, t = MAX_NODE-1
		int flow[MAX_NODE][MAX_NODE]; //flow graph, s = 0, t = MAX_NODE-1
		
		while(getline(cin, line) && !line.empty()){
				fill(&cap[0][0], &cap[MAX_NODE-1][MAX_NODE-1] + 1, 0);
				fill(&flow[0][0], &flow[MAX_NODE-1][MAX_NODE-1] + 1, 0);
				
				//set up the capacity graph based on input
				for(int i = MAX_APP+1; i <= MAX_APP+MAX_HOST; i++)
						cap[i][MAX_NODE-1] = 1;
				int numOfApp = 0;
				do{
						int app = line[0] - 'A' + 1;
						int num = line[1] - '0';
						numOfApp += num;
						cap[0][app] = num;
						for(int i = 3; line[i] != ';'; i++){
								int host = line[i] - '0' + MAX_APP + 1;
								cap[app][host] = 1;
						}
				}while(getline(cin, line) && line != "");
				
				int maxflow = 0;
				while(findAugmentPath(cap, flow)) 
						maxflow++;
				
				if(maxflow != numOfApp)
						cout << "!" << endl;
				else{
						for(int i = 0; i < MAX_HOST; i++){
								int host = i + MAX_APP + 1;
								char c = '_';
								for(int app = 1; app <= MAX_APP; app++){
										if(flow[app][host] == 1){
												c = app + 'A' - 1;
												break;
										}
								}
								cout << c;
						}
						cout<<endl;
				}
		}
}