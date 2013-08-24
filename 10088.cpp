#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
	int x, y;
	Point(int _x, int _y):x(_x), y(_y){}
};

int gcd(int a, int b){
	if(b == 0) return a;
	if(b > a) return gcd(b, a);
	return gcd(b, a%b);
}

int boundaryIntPoints(const vector<Point>& polygon){
	int pts = 0;
	int N = polygon.size();
	for(int i = 0; i < N; i++){
		int deltX = abs(polygon[i].x - polygon[(i+1)%N].x);
		int deltY = abs(polygon[i].y - polygon[(i+1)%N].y);
		if(deltX == 0) 
			pts += deltY - 1;
		else if(deltY == 0)
			pts += deltX - 1;
		else
			pts += gcd(deltX, deltY) - 1;  
	}
	return pts+N;
}

double area(const vector<Point>& polygon){
	int N = polygon.size();
	double result = 0, x1, y1, x2, y2;
	for (int i = 0; i < N; i++) {
		x1 = polygon[i].x; x2 = polygon[(i+1)%N].x;
		y1 = polygon[i].y; y2 = polygon[(i+1)%N].y;
		result += (x1 * y2 - x2 * y1);
	}
	return result > 0 ? result/2.0 : -result/2.0;
}

int main(){
	int N = 0;
	vector<Point> polygon;
	while(cin >> N && N > 0){
		polygon.clear();
		int x, y;
		for(int i = 0; i < N; i++){
			cin >> x >> y;
			polygon.push_back(Point(x, y));
		}
		
		long long pts = area(polygon) - boundaryIntPoints(polygon)/2.0 + 1;
		cout << pts << endl;
	}
}