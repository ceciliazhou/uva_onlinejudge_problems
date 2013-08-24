#include <iostream>
#include <cstring>

#define MAX_FACE 6
#define MAX_COLOR 100
#define MAX_CUBES 500
using namespace std;

struct Tower{
		int height;
		int belowCube;
		int belowColor;
		Tower():height(0), belowCube(0), belowColor(0){}
		void set(int h, int cube, int color){height = h; belowCube = cube; belowColor = color;}
		
		void print(){cout << height << "-" << belowCube << "-" << belowColor;}
};

/* return a string representing the face upside according to a given pair of colors. */
string upsideFace(const int cube[][MAX_FACE], int cubeID, int upColor, int downColor){
		if(cubeID <= 0) return "";
		
		const string FACE_NAME[] = {"front", "back", "left", "right", "top", "bottom"};
		for(int i = 0; i < MAX_FACE; i++){
				int opposite = i%2 == 0 ? i+1 : i-1;
				if(cube[cubeID][i] == upColor && (downColor == 0 || cube[cubeID][opposite] == downColor))
						return FACE_NAME[i];
		}
		return "";
}

/* 	for each pair of (i, j), calculate tower[i][j], and return the top of the highest tower.
		tower[i][j] means the number of cubes in the highest tower standing on cube[i] with its j colored face upside.
*/
Tower calcMaxHeight(const int cube[][MAX_FACE], Tower tower[][MAX_COLOR+1], int N){
		Tower top;
		for(int i = N; i >= 1; i--){
				for(int j = 0; j < MAX_FACE; j++){
						int color = cube[i][j];
						int opposite = j%2 == 0 ? j+1 : j-1;
						int match = cube[i][opposite];
						if(tower[i][color].height == 0)
								tower[i][color].height = 1;

						for(int k = i+1; k <= N; k++)
								if(tower[i][color].height < tower[k][match].height+1)
										tower[i][color].set(tower[k][match].height+1, k, match);

						if(top.height < tower[i][color].height)
								top.set(tower[i][color].height, i, color);
				}
		}
		return top;
}

int main(){
		/* tower[i][j] means the number of cubes in the highest tower standing on cube[i] with its j colored face upside. */
		Tower tower[MAX_CUBES+1][MAX_COLOR+1];
		int N = 0, caseID = 0;
		
		int cube[MAX_CUBES+1][MAX_FACE];
		while(cin >> N && N > 0){
				memset(tower, 0, sizeof(tower));
				for(int i = 1; i <= N; i++){
						for(int j = 0; j < MAX_FACE; j++)
								cin >> cube[i][j];
				}
				
				Tower top = calcMaxHeight(cube, tower, N);
				if(caseID > 0) cout << endl;
				cout << "Case #" << ++caseID << endl;
				cout << top.height << endl;
				
				while(top.belowCube > 0){
						int nextCube = tower[top.belowCube][top.belowColor].belowCube;
						int nextColor = tower[top.belowCube][top.belowColor].belowColor;
						cout << top.belowCube << " " << upsideFace(cube, top.belowCube, top.belowColor, nextColor) << endl;
						top.set(0, nextCube, nextColor);
				}
		}
}

