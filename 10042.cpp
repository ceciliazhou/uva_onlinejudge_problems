#include <iostream>
#include <bitset>
#include <vector>
#define MAX_FACTOR 35000  //35000^2 > 10^9
using namespace std;

/* return all primes that smaller than MAX_FACTOR */
vector<int> preprocess(){
	vector<int> primes;
	primes.push_back(2);
	
	bitset<MAX_FACTOR> isPrime;
	isPrime.set();
	for(int i = 3; i < MAX_FACTOR; i+=2){
		if(isPrime[i]){
			primes.push_back(i);
			for(int k = 2, j = i*k; j < MAX_FACTOR; k++, j = i*k)
				isPrime.set(j, false);
		}
	}
	return primes;
}

int sumOfDigits(int num){
	int sum = 0;
	while(num){
		sum += num%10;
		num /= 10;
	}
	return sum;
}

/* return a collections of prime factors of target */
vector<int> primeFactors(int target, const vector<int>& knownPrimes){
	vector<int> factors;
	int num = target;
	for(int i = 0; i < knownPrimes.size() && knownPrimes[i]*knownPrimes[i] <= target; i++){
		while(num%knownPrimes[i] == 0){
			factors.push_back(knownPrimes[i]);
			num = num/knownPrimes[i];
		}
	}
	
	//there may be one more factor which is greater than factors[last] if the target is a big number.
	if(num != 1 && num != target) 
		factors.push_back(num);
	
	return factors;
}

int isSmithNumber(int num, const vector<int>& knownPrimes){
	vector<int> factors = primeFactors(num, knownPrimes);
	int s = 0;
	for(int i = 0; i < factors.size(); i++)
		s += sumOfDigits(factors[i]);

	return s == sumOfDigits(num);
}

int main(){
	int cases = 0;
	cin >> cases;
	vector<int> primes = preprocess();
	
	while(cases--){
		int num;
		cin >> num;
		while(!isSmithNumber(++num, primes));
		cout << num << endl;
	}
}