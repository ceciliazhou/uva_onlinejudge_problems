#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef struct City{
		string name;
		int level;
		int num;
		int low;
		int children;
		vector<int> neighbors;
		City(string n):name(n), num(-1), level(0), children(0){}
		
		// void print(){cout << name <<": "<<num<<"/"<<low<<"/"<<level<<"/"<<children<<"/"<<endl;}
} City;

void articPointDFS(vector<City>& citys, int v, vector<string>& ap, int& dfsCounter, int level = 1){
		// citys[v].print();
		citys[v].num = dfsCounter++;
		citys[v].low = citys[v].num;
		citys[v].level = level++;
		
		int maxLow = 0;
		for(vector<int>::iterator n = citys[v].neighbors.begin(); n != citys[v].neighbors.end(); ++n){
				if(citys[*n].num == -1){ //undiscovered node
						citys[v].children++;
						articPointDFS(citys, *n, ap, dfsCounter, level);
						citys[v].low = min(citys[v].low, citys[*n].low);
						maxLow = max(maxLow, citys[*n].low);
				}
				else if(citys[*n].level < citys[v].level-1) //back edge
						citys[v].low = min(citys[v].low, citys[*n].num);
		}		
		// citys[v].print();
		
		if((citys[v].level == 1 && citys[v].children > 1)
				 || (citys[v].level > 1 && maxLow >= citys[v].num))
						ap.push_back(citys[v].name);
}

// void print(vector<City>& citys){
		// for(vector<City>::iterator it = citys.begin(); it != citys.end(); ++it){
				// cout << it->name << endl << "\t";
				// for(vector<int>::iterator n = it->neighbors.begin(); n != it->neighbors.end(); ++n)
						// cout << citys[*n].name << "\t";
				// cout << endl;
		// }
// }

int main(){
		map<string, int> citymap;
		vector<City> citys;
		vector<string> ap;
		int numOfCitys = 0, routes = 0, caseID = 0;
		string line;
		while(cin >> numOfCitys && numOfCitys > 0){
				if(++caseID > 1)
						cout << endl;
						
				citymap.clear();
				citys.clear();
				ap.clear();
				
				for(int i = 0; i < numOfCitys; i++){
						cin >> line;
						citymap[line] = i;
						citys.push_back(City(line));
				}
				cin >> routes;
				for(int i = 0; i < routes; i++){
						cin >> line;
						int u = citymap[line];
						cin >> line;
						int v = citymap[line];
						citys[u].neighbors.push_back(v);
						citys[v].neighbors.push_back(u);
				}
				
				// cout << "-----------------------------" << endl;
				// print(citys);
				
				int dfsCounter = 1;
				for(int i = 0; i < citys.size(); i++){
						if(citys[i].num == -1)
								articPointDFS(citys, i, ap, dfsCounter);
				}
				sort(ap.begin(), ap.end());
				cout << "City map #" << caseID << ": " << ap.size() << " camera(s) found" << endl;
				for(vector<string>::iterator it = ap.begin(); it != ap.end(); ++it)
						cout << *it << endl;
		}

}