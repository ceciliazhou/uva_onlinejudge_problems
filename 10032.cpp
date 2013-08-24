#include <iostream>
#include <algorithm>

using namespace std;

int maxSumOfHalfArray(int array[], const int size, int noMoreThan){
  bool canSumTo[100/2+1][450*100/2+1] = {};
  canSumTo[0][0] = true;
  int lastRow = (size+1)/2;  

  // canSumTo[j][sum] represents whether there is a subset of j elements in the array sums to sum.
  for(int i = 0; i < size; i++){
    for(int j = min(i+1, lastRow); j >= 1; j--){
      for(int sum = array[i]; sum <= noMoreThan; sum++){
				if(canSumTo[j-1][sum - array[i]]){
					canSumTo[j][sum] = true;
				}
      }
    }
  }
  

  while(noMoreThan > 0){
    if(canSumTo[lastRow][noMoreThan]) return noMoreThan;
    noMoreThan--;
  }
  return 0;
}

int main(){
  int cases = 0;
  cin >> cases;
  int weight[100] = {};

  while(cases-- > 0){

    int num = 0, sum = 0;
    cin >> num;
    for(int i = 0; i < num; i++){
      cin >> weight[i];
      sum += weight[i];
    }
    
    int s = maxSumOfHalfArray(weight, num, sum/2);    
    cout << s << " " << sum - s << endl;

    if(cases != 0)
      cout << endl;
  }
}
