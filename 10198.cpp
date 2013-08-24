#include <iostream>
#include <map>

using namespace std;

/******* auxiliary class ********/

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


/******* algorithm ********/

const int NUM_OF_CHOICES = 4;
const int VALUE[] = {1, 2, 3, 1};
	
BigInt waysToSumN(int sum, map<int, BigInt>& db){
	if(sum == 0) return 1;
	if(sum < 0) return 0;
	if(db.find(sum) != db.end()) return db[sum];
	
	BigInt ways = 0;
	for(int i = 0; i < NUM_OF_CHOICES; i++){
		ways += waysToSumN(sum - VALUE[i], db);
	}
	
	db[sum] = ways;
	return ways;
}

int main(){
	int N;
	map<int, BigInt> db;	
	while(cin >> N){
		cout << waysToSumN(N, db) << endl;	
	}
}