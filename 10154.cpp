#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct Turtle Turtle;
struct Turtle{
	int weight;
	int strength;
	Turtle(int w, int s):weight(w), strength(s){}
};

// bool sortByW(Turtle a, Turtle b) { 
	// if(a.weight != b.weight)
		// return a.strength <= b.strength;
	// return a.weight < b.weight;	
// }

bool sortByC(Turtle a, Turtle b) { 
	if(a.weight != b.weight)
		return a.strength <= b.strength;
	return a.weight < b.weight;	
}

int nextStackable(const vector<Turtle>& turtles, int top, int without){
	int next = without > top ? without + 1 : top + 1;
	while(next >= 0 && next < turtles.size() && turtles[next].strength > turtles[top].strength - turtles[top].weight)
		next++;
	return next;
}

int howManyStackable(const vector<Turtle>& turtles, int top, int without){
	int next = nextStackable(turtles, top, without);
	if(next >= turtles.size() || next < 0)
		return 0;
	
	int num1 = howManyStackable(turtles, top, next);
	int num2 = howManyStackable(turtles, next, -1) + 1;
	cout << "howManyStackable(" << top << ", " << without << ") ------ " << max(num2, num1) << endl;
	return max(num2, num1);
}

int main(){
	map<int, int> minWeight;
	int w, c;
	while(cin >> w >> c){
		if(minWeight.find(c) != minWeight.end())
			minWeight[c] = w;
		else
			minWeight[c] = min(minWeight[c], w);
	}
	
	vector<Turtle> turtles;
	int bottom = -1, maxCap = 0, i = 0;
	for(map<int, int>::iterator it = minWeight.begin(); it != minWeight.end(); it++, i++){
		turtles.push_back(Turtle(it->first, it->second));
		if(it->first - it->second > maxCap){
			maxCap = it->first - it->second;
			bottom = i;
		}
	}
	
	if(bottom >= 0){
		Turtle temp = turtles[0];
		turtles[0] = turtles[bottom];
		turtles[bottom] = temp;
	}
	
	sort(turtles.begin()+1, turtles.end(), sortByC);
	cout << howManyStackable(turtles, 0, -1) << endl;
}