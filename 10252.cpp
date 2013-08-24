#include <string>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


string longestCommon(const string& a, const string& b){
	int countA[26] = {};
	int countB[26] = {};
	string result;
	
	for(int i = 0; i < a.length(); i++){
			countA[a[i]-'a']++;
	}
	
	for(int i = 0; i < b.length(); i++){
			countB[b[i]-'a']++;
	}
	
	for(int i = 0; i < 26; i++){
		int com = countA[i] < countB[i] ? countA[i] : countB[i];
		for(int j = 0; j < com; j++)
			result += 'a'+i;
	}
	return result;
}

int main(){
	string a, b; 
	while(getline(cin, a) && getline(cin, b)){
		string common = longestCommon(a, b);
		sort(common.begin(), common.end());
		cout << common << endl;
	}
}