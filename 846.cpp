#include <iostream>
#include <climits>

#define MAX_STEPS 100000 // 100000*(100000-1)/2 > 2^31
#define MAX_END 0x7FFFFFFF
using namespace std;

/* db[i] is the max number of distance can be reached by i steps. */
int preprocess(int* db, int size){
	db[0] = 0;
	int step = 1;
	while(step < size){
		int maxLen = (step+1)/2;
		if(db[step-1] > INT_MAX - maxLen)
			return step-1;
		db[step] = db[step-1] + maxLen;	
		step++;
	}
	return step-1;
}

/* return the index of the smallest integer which is larger than or equal to findMe */
int searchCeil(int findMe, int *db, int low, int hi){
	if(low == hi) return low;
	
	int mid = (low + hi)/2;
	if(findMe <= db[mid])
		hi = mid;
	else
		low = mid+1;
	return searchCeil(findMe, db, low, hi);
}

int main(){
	int cases = 0;
	cin >> cases;
	
	int *db = new int[MAX_STEPS];
	int maxStep = preprocess(db, MAX_STEPS);
	
	while(cases--){
		int from, to;
		cin >> from >> to;
		if(to-from > db[maxStep])
			cout << maxStep + 1 << endl;	
		else
			cout << searchCeil(to-from, db, 0, maxStep) << endl;
	}
	delete[] db;
}