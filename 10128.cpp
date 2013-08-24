#include <iostream>
using namespace std;

int permutations(int N, int P, int R){
	if(N < P || N < R || N <= 0 || P <= 0 || R <= 0) return 0;
	if(N == 1) return (P == 1 && R == 1) ? 1 : 0;
	return permutations(N-1, P, R)*(N-2) + permutations(N-1, P-1, R) + permutations(N-1, P, R-1);
}

int main(){
	int cases = 0;
	cin >> cases;
	while(cases-- > 0){
		int N = 0, P = 0, R = 0;
		cin >> N >> P >> R;
		cout << permutations(N, P, R) << endl;	
	}
}
