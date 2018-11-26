#include <iostream>
#include <cstring>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

bool v[101][101];
int bfsIndex[101][101];
int r, c;
int x1, y1, x2, y2;

bool legal(int x, int y) {
    return x >= 0 && x < r && y >=0 && y < c;
}

int bfs() {
    bfsIndex[x1][y1] = 0;
    queue<pair<int, int> > q;
    q.push(make_pair(x1, y1));
    while(!q.empty() && bfsIndex[x2][y2] == -1) {
        pair<int, int> next = q.front();
	// cout << "visiting " << next.first << ", " << next.second << endl;
        q.pop();
        int x = next.first;
        int y = next.second;
        if(legal(x-1, y-1) && v[x-1][y-1] && bfsIndex[x-1][y-1] == -1) {
            bfsIndex[x-1][y-1] = bfsIndex[x][y] + 1;
	    q.push(make_pair(x-1, y-1));
        }
	if(legal(x-1, y) && v[x-1][y] && bfsIndex[x-1][y] == -1) {
	  bfsIndex[x-1][y] = bfsIndex[x][y] + 1;
	  q.push(make_pair(x-1, y));
        }
	if(legal(x-1, y+1) && v[x-1][y+1] && bfsIndex[x-1][y+1] == -1) {
	  bfsIndex[x-1][y+1] = bfsIndex[x][y] + 1;
	  q.push(make_pair(x-1, y+1));
        }
	if(legal(x, y-1) && v[x][y-1] && bfsIndex[x][y-1] == -1) {
	  bfsIndex[x][y-1] = bfsIndex[x][y] + 1;
	  q.push(make_pair(x, y-1));
        }
	if(legal(x, y+1) && v[x][y+1] && bfsIndex[x][y+1] == -1) {
	  bfsIndex[x][y+1] = bfsIndex[x][y] + 1;
	  q.push(make_pair(x, y+1));
	}
	if(legal(x+1, y-1) && v[x+1][y-1] && bfsIndex[x+1][y-1] == -1) {
            bfsIndex[x+1][y-1] = bfsIndex[x][y] + 1;
	    q.push(make_pair(x+1, y-1));
        }
	if(legal(x+1, y) && v[x+1][y] && bfsIndex[x+1][y] == -1) {
	  bfsIndex[x+1][y] = bfsIndex[x][y] + 1;
	  q.push(make_pair(x+1, y));
        }
	if(legal(x+1, y+1) && v[x+1][y+1] && bfsIndex[x+1][y+1] == -1) {
            bfsIndex[x+1][y+1] = bfsIndex[x][y] + 1;
	    q.push(make_pair(x+1, y+1));
        }
    }
    return bfsIndex[x2][y2];
}

int main() {
    int tc;
    cin >> tc;
    while(tc--) {
       cin >> r >> c;
       string line;
       getline(cin, line);
       vector<string> board;
       for(int i= 0; i < r; i++) {
            getline(cin, line);
            board.push_back(line);
       }
       memset(v, true, sizeof v);
       for(int i= 0; i < r; i++) { 
            for(int j = 0; j < c; j++) {
               if(board[i][j] == 'A') {
                    x1 = i;
                    y1 = j;
               }
	       if(board[i][j] == 'B') {
		 v[i][j] = true;
		 x2 = i;
		 y2 = j;
               }
               if(board[i][j] == 'Z') {
                   v[i][j] = false;
                   if(legal(i-1, j-2)) {
                       v[i-1][j-2] = false; 
                   }
                   if(legal(i-1, j+2)) {
                       v[i-1][j+2] = false; 
                   }
                   if(legal(i+1, j+2)) {
                       v[i+1][j+2] = false; 
                   }
                   if(legal(i+1, j-2)) {
                       v[i+1][j-2] = false; 
                   }
                   if(legal(i-2, j-1)) {
                       v[i-2][j-1] = false; 
                   }
                   if(legal(i-2, j+1)) {
                       v[i-2][j+1] = false; 
                   }
                   if(legal(i+2, j+1)) {
                       v[i+2][j+1] = false; 
                   }
                   if(legal(i+2, j-1)) {
                       v[i+2][j-1] = false; 
                   }
               }

            }
       }
       v[x1][y1] = true;
       v[x2][y2] = true;
       memset(bfsIndex, -1, sizeof bfsIndex);
       int result = bfs();
       if (result == -1) {
           cout << "King Peter, you can't go now!" << endl;
       } else {
           cout << "Minimal possible length of a trip is " << result << endl;
       }

    }
    return 0;
}
