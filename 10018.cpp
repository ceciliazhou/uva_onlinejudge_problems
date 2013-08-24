#include <iostream>
using namespace std;

long long reverse(long long inputNum){
	long long outputNum = 0;
	while (inputNum) {
		outputNum = outputNum * 10 + inputNum % 10;
		inputNum = inputNum / 10;
	}
	return outputNum;
}

int main()
{
	int t = 0;
	long long num, reverseNum;
	cin >> t;
	while( t-- > 0){
		cin >> num;
		int count = 0;
		reverseNum = reverse(num);
		while (reverseNum != num)
		{
			count++;
			num += reverseNum;
			reverseNum = reverse(num);
		}
		cout << count << " " << num << endl;
	}
}
	