#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

bool viable[30][30][30];
int bfsIndex[30][30][30];
int l, r, c;
int x1, y1, z1;
int x2, y2, z2;

struct Triple {
  Triple(int x, int y, int z) : a(x), b(y), c(z) {};
  int a, b, c;
};

int bfs() {
  bfsIndex[x1][y1][z1] = 0;
  queue<Triple> q;
  Triple each(x1, y1, z1);
  q.push(each);
  while(bfsIndex[x2][y2][z2] == -1 && !q.empty()) {
    Triple next = q.front();
    q.pop();
    int x = next.a;
    int y = next.b;
    int z = next.c;
    if(x-1 >= 0 && bfsIndex[x-1][y][z] == -1 && viable[x-1][y][z]) {
      bfsIndex[x-1][y][z] = bfsIndex[x][y][z] + 1;
      Triple next(x-1, y, z);
      q.push(next);
    }
    if(x+1 < l && bfsIndex[x+1][y][z] == -1 && viable[x+1][y][z]) {
      bfsIndex[x+1][y][z] = bfsIndex[x][y][z] + 1;
      Triple next(x+1, y, z);
      q.push(next);
    }
    if(y-1 >= 0 && bfsIndex[x][y-1][z] == -1 && viable[x][y-1][z]) {
      bfsIndex[x][y-1][z] = bfsIndex[x][y][z] + 1;
      Triple next(x, y-1, z);
      q.push(next);
    }
    if(y+1 < r && bfsIndex[x][y+1][z] == -1 && viable[x][y+1][z]) {
      bfsIndex[x][y+1][z] = bfsIndex[x][y][z] + 1;
      Triple next(x, y+1, z);
      q.push(next);
    }
    if(z-1 >= 0 && bfsIndex[x][y][z-1] == -1 && viable[x][y][z-1]) {
      bfsIndex[x][y][z-1] = bfsIndex[x][y][z] + 1;
      Triple next(x, y, z-1);
      q.push(next);
    }
    if(z+1 < c && bfsIndex[x][y][z+1] == -1 && viable[x][y][z+1]) {
      bfsIndex[x][y][z+1] = bfsIndex[x][y][z] + 1;
      Triple next(x, y, z+1);
      q.push(next);
    }
  }
  return bfsIndex[x2][y2][z2];
}

int main() {
  string line;
  while(cin >> l >> r >> c && (l || r || c)) {
    getline(cin, line);
    memset(viable, false, sizeof viable);
    memset(bfsIndex, -1, sizeof bfsIndex);
    for(int i= 0; i < l; i++) {
      for(int j= 0; j < r; j++) {
	getline(cin, line);
	for(int k =0; k < c; k++) {
	  if(line[k] == 'S') {
	    x1 = i;
	    y1 = j;
	    z1 = k;
	    viable[i][j][k] = true;
	  }
	  else if (line[k] == '.') {
	    viable[i][j][k] = true;
	  }
	  else if (line[k] == 'E') {
	    x2 = i;
	    y2 = j;
	    z2 = k;
	    viable[i][j][k] = true;
	  }
	  else if (line[k] == '#') {
	    viable[i][j][k] = false;
	  }
	}
      }
      getline(cin, line);
    }
    int result = bfs();
    if(result == -1)
      cout << "Trapped!" << endl;
    else
      cout << "Escaped in " << result << " minute(s)." << endl;
  }
  return 0;
}
