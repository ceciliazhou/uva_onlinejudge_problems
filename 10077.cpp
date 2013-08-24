#include <iostream>
using namespace std;

/******* auxiliary class ********/

class WeirdFaction{
private:
	int numerator;
	int denominator;
	
public:
	WeirdFaction(int n, int d): numerator(n), denominator(d){};
	
	WeirdFaction operator=(const WeirdFaction& other){
		numerator = other.numerator;
		denominator = other.denominator;
	}
	
	WeirdFaction operator+(const WeirdFaction& other) const{
		return WeirdFaction(numerator+other.numerator, denominator+other.denominator);
	}
	
	bool operator<(const WeirdFaction& other) const{
		return numerator*other.denominator < denominator*other.numerator;
	}
	
	bool operator==(const WeirdFaction& other) const{
		return numerator == other.numerator && denominator == other.denominator;
	}
};

/******* algorithm ********/

void findPath(const WeirdFaction& findMe, string& path, WeirdFaction& left, WeirdFaction& mid, WeirdFaction& right){
	if(findMe == mid) 
		return;
		
	if(findMe < mid){
		right = mid;
		mid = left + mid;
		path = path+"L";
	}
	else{
		left = mid;
		mid = right + mid;
		path = path+"R";
	}
	findPath(findMe, path, left, mid, right);
} 

int main(){
	int numerator = 1, denominator = 1;
	cin >> numerator >> denominator;
	
	while(numerator != 1 || denominator != 1){
		string path;
		WeirdFaction findMe(numerator, denominator);
		WeirdFaction left(0, 1);
		WeirdFaction mid(1, 1);
		WeirdFaction right(1, 0);
		findPath(findMe, path, left, mid, right);
		cout << path << endl;
		cin >> numerator >> denominator;
	}
}