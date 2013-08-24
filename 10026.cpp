#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Pair{
	double cost;
	int index;
	Pair(double c, int i):cost(c), index(i){}
	bool operator < (const Pair& other) const {
		if(cost != other.cost)
			return cost > other.cost;
		return index < other.index;
	}
};

int main(){
	int t, n;
	cin >> t;
	vector<Pair> data;
	for(int caseID = 1; caseID <= t; caseID++) {
		cin >> n;
		data.clear();
		for(int i=0; i<n; i++){
			double time, fine;
			cin >> time >> fine;
			data.push_back(Pair(fine/time, i+1));
		}
		sort(data.begin(), data.end());
		
		if(caseID > 1) cout << endl;	
        for(int i=0; i < n; i++){
            if(i > 0) cout << " ";
            cout << data[i].index;
        }
        cout << endl;
	}
}