#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct time_duration time_duration;

struct time_duration{
	public:
		int start;
		int end;
	public:
		time_duration(int s, int e): start(s), end(e){}

		int getMins() {
			return end - start;
		}
};

bool before(const time_duration& ap1, const time_duration& ap2){
	return ap1.start <= ap2.start;
}

time_duration calculateLongestGap(vector<time_duration>& schedule){
	sort(schedule.begin(), schedule.end(), before);
	time_duration longest(600, schedule[0].start);
	for(int i = 1; i < schedule.size(); i++){
		time_duration cur(schedule[i-1].end, schedule[i].start);
		if(longest.getMins() < cur.getMins()) longest = cur;
	}
	
	time_duration last(schedule[schedule.size()-1].end, 1080);
	if(longest.getMins() < last.getMins()) longest = last;
	return longest;
}

vector<time_duration> getSchedule(int app){
	vector<time_duration> schedule;
	int sh, sm, eh, em; 
	char description[300];
	for(int i = 0; i < app; i++){			
		scanf("%d:%d %d:%d", &sh, &sm, &eh, &em);
		gets(description);
		schedule.push_back(time_duration(sh*60+sm, eh*60+em));		
	}
	return schedule;
}

int main(){
	int appointments = 0;
	int caseNo = 1;
	while(scanf("%d", &appointments) == 1){
		vector<time_duration> schedule = getSchedule(appointments);
		time_duration longestGap = calculateLongestGap(schedule);
		char durationStr[50];
		int h = longestGap.getMins()/60;
		sprintf(durationStr, "%d hours and ", h);
		printf("Day #%d: the longest nap starts at %2d:%02d and will last for %s%d minutes.\n", 
				caseNo++, longestGap.start/60, longestGap.start%60, 
				(h ? durationStr : ""), 
				longestGap.getMins()%60);				
	}
}