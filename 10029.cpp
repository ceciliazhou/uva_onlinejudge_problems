#include <iostream>
#include <algorithm>
using namespace std;

//a dictionary implemented in a trie.
class Dictionary{
public:
		Dictionary():root(){}
		~Dictionary(){ root.destroy(); }
		void insert(const string& word, int val){ root.insert(word, val, 0); }
		int find(const string& word) const { return root.find(word, 0); }
		
private:
		struct Node{
				int val; // length of the "edit step ladder" which ends at this string/word.
				Node* next[26];
				Node(int v = 0):val(v){
						for(int i = 0; i < 26; i++)
								next[i] = NULL;
				}
				
				void insert(const string& word, int v, int cur){
						if(cur == word.length()){
								val = v;
								return;
						}
						
						int index = word[cur]-'a';
						if(next[index] == NULL)
								next[index] = new Node();
						next[index]->insert(word, v, cur+1);
				}
				
				int find(const string& word, int cur) const{
						if(cur == word.length()) return val;
						int index = word[cur]-'a';
						if(next[index] == NULL)
								return 0;
						return next[index]->find(word, cur+1);
				}
				
				void destroy(){
						for(int i = 0; i < 26; i++){
								if(next[i] != NULL)
										next[i]->destroy();
								delete next[i];
						}
				}
		};
		
		Node root;
};

int main(){
		Dictionary dict;
		string word;
		int maxLen = 0;
		
		while(cin >> word){
				int maxCur = 1;
				for(int i = 0; i < word.length(); i++){
						for(char c = 'a'; c <= 'z'; c++){
								//add a character
								if(c <= word[i]){
										string add = word.substr(0, i) + c + word.substr(i);
										maxCur = max(dict.find(add) + 1, maxCur);
								}
								//delete a character
								string del = word.substr(0, i) + word.substr(i+1);
								maxCur = max(dict.find(del) + 1, maxCur);
								//change a character
								if(c < word[i]){
										string change = word.substr(0, i) + c + word.substr(i+1);
										maxCur = max(dict.find(change) + 1, maxCur);	
								}
						}
				}
				dict.insert(word, maxCur);
				if(maxCur > maxLen)
						maxLen = maxCur;
		}
		
		cout << maxLen << endl;
}