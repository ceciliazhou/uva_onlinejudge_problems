#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

#define MAX_CHIPS 200
#define RADIUS 2.5

struct Point{
	double x, y;
	Point(double _x = 0, double _y = 0):x(_x), y(_y){}
};

double dist(const Point& p1, const Point& p2){
	double xd = p1.x - p2.x, yd = p1.y - p2.y;
	return sqrt(xd*xd + yd*yd);
}

int pointsInCircle(Point chips[], int size, Point center, double r){
	int nCount = 0;
	for (int i = 0; i < size; i++){
		double distance = dist(chips[i], center);
		if (distance > r) continue;
		nCount++;
	}
	return nCount;
}

int main(int ac, char *av[]){
	int cases = 0;
	Point chips[MAX_CHIPS];
	string line;
	
	cin >> cases;
	getline(cin, line);
	getline(cin, line);

	while (cases--){
		int count = 0;
		while (getline(cin, line), line.length()){
			istringstream ss(line);
			ss >> chips[count].x >> chips[count].y;
			count++;
		}

		int maximum = 1;
		for (int i = 0; i < count - 1; i++){
			for (int j = i + 1; j < count; j++){
			
				double d = dist(chips[i], chips[j]);
				if (d > 2*RADIUS) continue;
					
				Point median((chips[i].x + chips[j].x)/2, (chips[i].y + chips[j].y)/2);
				double sinA = fabs(chips[j].x - chips[i].x)/d;
				double cosA = sqrt(1 - sinA * sinA);
				double segment = sqrt(RADIUS * RADIUS - d /2 * d / 2);
				maximum = max(maximum, pointsInCircle(chips, count, Point(median.x + segment * cosA, median.y + segment * sinA), RADIUS));
				maximum = max(maximum, pointsInCircle(chips, count, Point(median.x - segment * cosA, median.y - segment * sinA), RADIUS));
			}
		}
		
		cout << maximum << endl;
		if(cases > 0) cout << endl;
	}

	return 0;
}