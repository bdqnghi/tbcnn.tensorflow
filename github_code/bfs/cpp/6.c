#include <iostream>
#include <cstring>
#include <sstream>
#include <utility>
#include <queue>

using namespace std;

int bfsIndex[8][8];

int bfs(int x1, int y1, int x2, int y2) {
  bfsIndex[x1][y1] = 0;
  queue<pair<int, int> > q;
  q.push(make_pair(x1, y1));
  while(!q.empty() && bfsIndex[x2][y2] == -1) {
    pair<int, int> next = q.front();
    q.pop();
    int x = next.first;
    int y = next.second;
    if(x - 2 >= 0 && y -1 >= 0 && bfsIndex[x-2][y-1] == -1) {
      bfsIndex[x-2][y-1] = bfsIndex[x][y] + 1;
      q.push(make_pair(x-2, y-1));
    }
    if(x - 2 >= 0 && y+1 < 8 && bfsIndex[x-2][y+1] == -1) {
      bfsIndex[x-2][y+1] = bfsIndex[x][y] + 1;
      q.push(make_pair(x-2, y+1));
    }
    if(x + 2 < 8 && y -1 >= 0 && bfsIndex[x+2][y-1] == -1) {
      bfsIndex[x+2][y-1] = bfsIndex[x][y] + 1;
      q.push(make_pair(x+2, y-1));
    }
    if(x + 2 < 8 && y +1 < 8 && bfsIndex[x+2][y+1] == -1) {
      bfsIndex[x+2][y+1] = bfsIndex[x][y] + 1;
      q.push(make_pair(x+2, y+1));
    }

    if(x - 1 >= 0 && y -2 >= 0 && bfsIndex[x-1][y-2] == -1) {
      bfsIndex[x-1][y-2] = bfsIndex[x][y] + 1;
      q.push(make_pair(x-1, y-2));
    }
    if(x - 1 >= 0 && y+2 < 8 && bfsIndex[x-1][y+2] == -1) {
      bfsIndex[x-1][y+2] = bfsIndex[x][y] + 1;
      q.push(make_pair(x-1, y+2));
    }
    if(x + 1 < 8 && y -2 >= 0 && bfsIndex[x+1][y-2] == -1) {
      bfsIndex[x+1][y-2] = bfsIndex[x][y] + 1;
      q.push(make_pair(x+1, y-2));
    }
    if(x + 1 < 8 && y +2 < 8 && bfsIndex[x+1][y+2] == -1) {
      bfsIndex[x+1][y+2] = bfsIndex[x][y] + 1;
      q.push(make_pair(x+1, y+2));
    }
  }
  return bfsIndex[x2][y2];
}

int main() {
  string line;
  while(getline(cin, line)) {
    istringstream iss(line.c_str());
    string start, end;
    getline(iss, start, ' ');
    getline(iss, end);
    memset(bfsIndex, -1, sizeof bfsIndex);
    int result = bfs(start[0] - 'a', start[1] - '1', end[0] - 'a', end[1] - '1');
    cout << "To get from " << start << " to " << end << " takes " << result << " knight moves." << endl;
  }
  return 0;
}
