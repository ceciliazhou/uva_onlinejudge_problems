#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct Node{
	char color; //0: not-colored, 1: white, 2: black
	vector<int> neighbors;
	Node(char c = 0):color(c), neighbors(){}
	void addNeighbor(int n){ neighbors.push_back(n); }
	void reset(){color = 0; neighbors.clear();}
};

/* BFS to color the nodes.
   return failure if:
	 1. a node is found painted in the same color with one of its neighbor 
	 2. or there is no color can be used.
*/
bool bicolorGraph(Node *nodes, char *choice, int V){
		nodes[0].color = 1;
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()){
				int u = Q.front();
				Q.pop();
				for(int i = 0; i < nodes[u].neighbors.size(); i++){
						int v = nodes[u].neighbors[i];
						//paint non-colored neighbors.
						if(nodes[v].color == 0){ 
								//disallow neighbor to be colored in the same color with current nodes'.
								choice[v] ^= nodes[u].color; 
								if(choice[v] == 0)
									return false;
								nodes[v].color = choice[v];
								Q.push(v);
						}
						else if(nodes[v].color == nodes[u].color)
								return false;
				}
		}
		
		return true;
}

int main(){
		int V = 0, E = 0;
		const int MAX_SIZE = 200;
		Node nodes[MAX_SIZE];
		char choice[MAX_SIZE]; //choice[i] is the set of color usable by nodes[i]. 0: none usable, 1: white, 3: white and black
		while(cin >> V && V > 0){
				cin >> E;
				for(int i = 0; i < V; i++){
						nodes[i].reset();
						choice[i] = 3;
				}
						
				for(int i = 0; i < E; i++){
						int u = -1, v = -1;
						cin >> u >> v;
						nodes[u].addNeighbor(v);
						nodes[v].addNeighbor(u);
				}
				
				string output = bicolorGraph(nodes, choice, V) ? "BICOLORABLE." : "NOT BICOLORABLE." ;
				cout << output << endl; 
		}
}