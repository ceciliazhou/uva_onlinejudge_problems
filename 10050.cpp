#include <iostream>
#include <bitset>
using namespace std;

int calcLostDays(const int total, int hartal[], int numOfP){
	bitset<3650> occur;
	for(int i = 0; i < numOfP; i++)
		for(int j = hartal[i]-1; j < total; j += hartal[i])
			if((j) % 7 < 5)
				occur.set(j);
	return occur.count();
}

int main(){
	int numOfCases = 0;
	cin >> numOfCases;
	while(numOfCases > 0){
		int totalDays = 0, numOfParties = 0;
		cin >> totalDays >> numOfParties;
		
		int* hartal = new int[numOfParties];
		for(int i = 0; i < numOfParties; i++)
			cin >> hartal[i];
		
		int daysLost = calcLostDays(totalDays, hartal, numOfParties);
		cout << daysLost << endl;	
		delete[] hartal;
		numOfCases--;
	}
}
