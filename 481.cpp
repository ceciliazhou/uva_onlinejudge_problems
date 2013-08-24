#include <iostream>
#include <vector>

using namespace std;

int successor(const vector<int>& input, const vector<int>& index, int target){
	int low = 0, hi = index.size()-1;
	while(low < hi){
		int mid = (low + hi)/2;
		if(input[target] > input[index[mid]])
			low = mid + 1;
		else
			hi = mid;
	}	
	return low;
}

vector<int> LIS(const vector<int>& input){
	vector<int> ret;
	if(input.empty()) return ret;
	
	ret.push_back(0);
	
	vector<int> prev(input.size(), -1);
	for(int i = 1; i < input.size(); i++){
		if(input[i] > input[ret.back()]){
			prev[i] = ret.back();
			ret.push_back(i);
			continue;
		}
	
		int replace = successor(input, ret, i);
		if(input[ret[replace]] > input[i]){
			ret[replace] = i;
			if(replace > 0) 
				prev[i] = ret[replace-1];
		}		
	}
	
	int last = ret.back();
	int i = ret.size() - 1;
	while(last >= 0 && i >= 0){
		ret[i--] = input[last];
		last = prev[last];
	}
	
	return ret;
}

int main(){
  vector<int> numbers;
  int temp;
  while(cin >> temp)
    numbers.push_back(temp);

  vector<int> result = LIS(numbers);
  
  cout << result.size() << endl << "-" << endl;
  for(int i = 0; i < result.size(); i++)
    cout << result[i] << endl;
}
