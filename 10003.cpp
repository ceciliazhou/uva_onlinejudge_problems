#include <iostream>
using namespace std;

const int MAX_CUT = 50, MAX_COST = 1000*50;
/*
  C[L, R] = (c[R] - c[L]) + C[L, i] + C[i, R];
 */

int minCost(int (*cost)[MAX_CUT+2], int start, int end, int* cuts){
  if(start+1 >= end) return 0;
  if(cost[start][end] != MAX_COST) return cost[start][end];

  for(int i = start+1; i < end; i++){
    int c = minCost(cost, start, i, cuts) + minCost(cost, i, end, cuts) + cuts[end] - cuts[start];
    if(c < cost[start][end])
      cost[start][end] = c;
  }
  
  return cost[start][end];
}


int main(){
  int len = 0;
  int cuts[MAX_CUT+2];
  int cost[MAX_CUT+2][MAX_CUT+2];

  while(cin >> len && len > 0){
    int numOfCuts = 0;
    cin >> numOfCuts;
    cuts[0] = 0; 
    cuts[numOfCuts+1] = len;
    for(int i = 1; i <= numOfCuts; i++)
      cin >> cuts[i];

    for(int i = 0; i <= MAX_CUT+1; i++){
      cost[i][i+1] = 0;
      for(int j = i+2; j <= MAX_CUT+1; j++){
	cost[i][j] = MAX_COST;
      }
    }
    cout << "The minimum cutting is " << minCost(cost, 0, numOfCuts+1, cuts) << "." << endl;
  }
}
