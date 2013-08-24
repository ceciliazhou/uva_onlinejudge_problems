#include <iostream>
#include <algorithm>
#include <climits>
#include <sstream>
using namespace std;


int distToOthers(int *r, int num, int from){
	int sum = 0;
	for(int i = 0; i < num; i++)
		sum += abs(r[i] - r[from]);
	return sum;
}

int minDistSum(int *r, int num){
	sort(r, r+num);
	return distToOthers(r, num, num/2);
}

int main(){
	int cases = 0;
	cin >> cases;
	int r[500];
	while(cases-- > 0){
		int num;
		cin >> num;
		for(int i = 0; i < num; i++)
			cin >> r[i];
		cout << minDistSum(r, num) << endl;
	}
}