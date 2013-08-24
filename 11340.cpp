#include <iostream>
#include <cstring>
#include <climits>
#include <iomanip>

using namespace std;

void readValues(int* price){
	int K, p;
	unsigned char ch;
	cin >> K;
	while(K-- > 0 && cin >> ch >> p)
		price[ch] = p;	
}

int evaluateArticle(int* price){
	int M, total = 0;
	unsigned char ch;
	cin >> M;
	cin >> noskipws >> ch;
	while(M > 0 && cin >> ch){
		if(ch == '\n')
			M--;
		else
			total += price[ch];
	}	
	cin >> skipws;
	return total;
}

int main(){
	int numOfTests = 0;
	int price[UCHAR_MAX+1];	
	cin >> numOfTests;
	while(numOfTests-- > 0){
		memset(price, 0, (UCHAR_MAX+1)*sizeof(int));
		readValues(price);		
		int total = evaluateArticle(price);
		cout << fixed << setprecision(2) << total/100.0 << "$" << endl;
	}
}

