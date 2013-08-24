#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main(){
		int N = 0, R = 0, caseID = 0;
		const int MAX_CITIES = 100;
		int graph[MAX_CITIES+1][MAX_CITIES+1];
		
		while(cin >> N >> R && (N != 0 || R != 0)){
				memset(graph, 0, sizeof(graph));

				int A = 0, B = 0, limit = 0;
				for(int i = 0; i < R; i++){
						cin >> A >> B >> limit;
						graph[A][B] = limit;
						graph[B][A] = limit;
				}
				
				int from = 0, to = 0, passengers = 0;
				cin >> from >> to >> passengers;
				for(int passby = 1; passby <= N; passby++){
						for(int i = 1; i <= N; i++){
								for(int j = 1; j <= N; j++){
										graph[i][j] = max(graph[i][j], min(graph[i][passby], graph[passby][j]));
								}
						}
				}
				
				int trip = static_cast<int>(ceil(((double)passengers)/(graph[from][to]-1)));
				cout << "Scenario #" << ++caseID << endl;
				cout << "Minimum Number of Trips = " << trip << endl << endl;
		}

}