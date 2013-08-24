#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class BigInt{
private:
	string digits;
	char addDigit(char a, char b, int& carry) const {
		int sum = a - '0' + b - '0' + carry;
		carry = sum > 9 ? 1 : 0;
		sum = sum > 9 ? sum - 10 : sum;
		return sum + '0';
	}
	
	string intToString(int num){
		string result;
		do{
			result.insert(0, 1, num%10+'0');
			num /= 10;
		} while(num != 0);
		return result;		
	}
	
public:
	BigInt(const string& d):digits(d){}
	BigInt():digits(""){}
	BigInt(int num){
		digits = intToString(num);
	}
	
	BigInt& operator= (int num) {digits = intToString(num); return *this;}
	BigInt& operator= (const BigInt& other) {digits = other.digits; return *this;}
	BigInt& operator+= (const BigInt& other) { digits = (this->operator+(other)).digits; return *this; }
	BigInt operator+ (const BigInt& other) const {
		const string& shorter = other.digits.length() > digits.length() ? digits : other.digits;
		const string& longer = other.digits.length() > digits.length() ? other.digits : digits;
		int carry = 0;
		int i = shorter.length() - 1, j = longer.length() - 1;
		string ret;
		while(i >= 0)			
			ret.insert(0, 1, addDigit(shorter[i--], longer[j--], carry));
		while(j >= 0)
			ret.insert(0, 1, addDigit('0', longer[j--], carry));
		if(carry != 0)
			ret.insert(0, 1, carry + '0');
		return BigInt(ret);
	}
	
	string getDigits() const { return digits; }
};

ostream& operator<< (ostream& out, const BigInt& integer){
	return out << integer.getDigits();
}

/*
	occur[i][j]: the number of occurrences of Z[0...j] in X[0...j] as a subsequence.
	occur[-1][j] = 1; means empty string occurs once in any string.
	occur[i][j] = occur[i][j-1] + (if only X[j] == Z[i]) occur[i-1][j-1], 0 <= i < lenZ, i+1 <= j < lenX;
*/
BigInt occurrenceSeq(const string& X, const string& Z, BigInt* occur){
	int lenX = X.length();
	int lenZ = Z.length();
	if(lenX == 0 || lenZ == 0)
		return 0;
	
	for(int i = 0; i < lenX; i++){
		occur[i] = 1;
	}
	
	BigInt last, temp;
	for(int i = 0; i < lenZ; i++){
		last = occur[i];
		occur[i] = (X.substr(0, i+1) == Z.substr(0, i+1)) ? 1 : 0;
		for(int j = i+1; j < lenX; j++){
			temp = occur[j];
			occur[j] = occur[j-1];
			if(X[j] == Z[i]){
				occur[j] += last;
			}
			last = temp;
		}
	}	
	return occur[lenX-1];
}

int main(){
	int cases = 0;
	string X, Z;
	BigInt occur[10000];
	cin >> cases;
	getline(cin, X);
	
	while(cases-- > 0){
		getline(cin, X);
		getline(cin, Z);
		cout << occurrenceSeq(X, Z, occur) << endl;	
	}
}