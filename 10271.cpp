#include <iostream> 
#include <cstring>
using namespace std;

/*
badSum(i, j): minimul badness resulted from selecting i sets in the longest j chopsticks.
bad(j): (A - B)^2, (A = chopstick[j], B = chopstick[j-1])
badSum(i, j) = min( badSum(i-1, j-2)+bad(j) (j>=3*i),
                    badSum(i, j-1) (j>=3*i+1) )
*/

int main() 
{
		const int MAX_STICKS = 5000;
    int cases, N, K;   
		long badSum[MAX_STICKS+1], bad[MAX_STICKS+1]; 

		cin >> cases; 
    while(cases--)
    {
      cin >> K >> N;
			K += 8;
			int cur, next;
			cin >> cur;
			int i = N;
			while(i > 1){
				cin >> next;
				bad[i--] = (cur - next)*(cur - next);
				cur = next;
			}
			
			memset (badSum, 0, sizeof(badSum));
			for(int i = 1; i <= K; i++) 
			{ 
				for(int j = N; j >= 3*i; j--)   
					badSum[j] = badSum[j-2]+bad[j];   
				for(int j = 3*i+1; j <= N; j++)
					if (badSum[j-1] < badSum[j])
						badSum[j] = badSum[j-1];
			}
			cout << badSum[N] << endl;
    }
}
