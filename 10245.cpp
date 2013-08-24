#include <iostream>
#include <vector>
#include<algorithm>
#include <iomanip>
#include <set>
#include<cmath>

#define MAX_DIST 10000
#define EPS 1e-10
using namespace std;

class Point{
public:
	double x, y;
	Point(double _x, double _y):x(_x), y(_y){}
};

double dist(const Point &p1, const Point &p2){
	double xd = p1.x - p2.x, yd = p1.y - p2.y;
	return sqrt(xd*xd + yd*yd);
}

bool compareX(const Point &p1, const Point &p2){
	return (fabs(p1.x - p2.x) > EPS) ? p1.x < p2.x : p1.y < p2.y;
}

struct compareY{ 
	bool operator()(const Point &p1, const Point &p2) const {
		return (fabs(p1.y - p2.y) > EPS) ? p1.y < p2.y : p1.x < p2.x;
	}
};
 
double minDist(vector<Point> &X){
    int N = X.size();
    set<Point, compareY> Y; 
    
    sort(X.begin(), X.end(), compareX);
    int firstInRange = 0;           
	double d = MAX_DIST;
    for (int i = 0; i < N; i++){
        while (X[i].x - X[firstInRange].x > d)
            Y.erase(X[firstInRange++]);
 
        set<Point, compareY>::const_iterator low = lower_bound(Y.begin(), Y.end(), Point(X[i].x, X[i].y - d), compareY());
        set<Point, compareY>::const_iterator up = upper_bound(Y.begin(), Y.end(), Point(X[i].x, X[i].y + d), compareY());
        for (set<Point, compareY>::const_iterator candidate = low; candidate != up; ++candidate)
            d = min(d, dist(X[i], *candidate));
 
        Y.insert(X[i]);  
    }
    return d;
}

int main(){
	int N = 0;
	double x, y;
	vector<Point> points;
	while(cin >> N && N > 0){
		points.clear();
		for(int i = 0; i < N; i++){
			cin >> x >> y;
			points.push_back(Point(x, y));
		}
		
		double dist = minDist(points);
		if(dist < MAX_DIST)
			cout << setprecision(4) << std::fixed << dist << endl;
		else
			cout << "INFINITY" << endl;
	}
}