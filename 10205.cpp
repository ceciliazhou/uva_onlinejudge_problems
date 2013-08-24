#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string cardToString(unsigned card){
	const static string valueString[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	const static string suitString[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	return valueString[card%13] + " of " + suitString[card/13];
}


void displayCardDeck(const vector<unsigned> &deck){
	for(vector<unsigned>::const_iterator it = deck.begin(); it != deck.end(); it++)
		cout << cardToString(*it) << endl;
}

vector<unsigned> newCardDeck(){
	vector<unsigned> v;
	for(unsigned i = 0; i < 52; i++)
		v.push_back(i);
	return v;
}

vector<vector<unsigned> > readShuffle(){
	unsigned numOfShuffles = 0;
	cin >> numOfShuffles;
		
	vector<vector<unsigned> > shuffles;
	unsigned temp = 0;
	for(unsigned i = 0; i < numOfShuffles; i++){
		vector<unsigned> s;
		for(unsigned j = 0; j < 52; j++){
			cin >> temp;
			s.push_back(temp-1);
		}
		shuffles.push_back(s);
	}
	return shuffles;
}

vector<unsigned> shuffle(vector<unsigned> &orig, const vector<unsigned> &shuffles){
	vector<unsigned> changed(orig);
	for(int i = 0; i < shuffles.size(); i++){
		if(shuffles[i] != i)
			changed[i] = orig[shuffles[i]];
	}
	return changed;
}

int main(){
	unsigned numOfCases = 0;
	cin >> numOfCases;
	while(numOfCases > 0){
		vector<unsigned> deck = newCardDeck();
		vector<vector<unsigned> > shuffles = readShuffle();
		char line[100] = {};
		cin.getline(line, 100);
		cin.getline(line, 100);
		while(line[0] != 0){
			int whichShuffle = 0;
			stringstream(string(line)) >> whichShuffle;
			deck = shuffle(deck, shuffles[whichShuffle-1]);
			cin.getline(line, 100);
		}
		displayCardDeck(deck);
		numOfCases--;
		if(numOfCases > 0) cout << endl;
	}
	
	return 0;
}
