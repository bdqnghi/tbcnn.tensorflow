#include <iostream>
#include <climits>
using namespace std;

const int MAXINT = INT_MAX;
const int maxNum = 100;
// n -- 总点数
// s -- 原点
// w[][] -- 两点间路径权值
// dist[] -- 到原点的路径长度
// prev[] -- 前一个结点,用于确定最终路径

void dijkstra(int n, int s, int w[maxNum][maxNum], int *dist, int *prev) {

    // 表示结点是否已经确定到源的最短路径
    bool *isVisited = new bool[n];
    
    for(int i = 0; i < n; i++) {

        isVisited[i] = false;
        dist[i] = w[s][i];
        if(dist[i] == MAXINT) {
            prev[i] = -1;
        } else {
            prev[i] = s;
        }
    }

    dist[s] = 0;
    isVisited[s] = true;
    
    for(int i = 0; i < n; i++) {

        // 找出未确定最短路径的结点中,距离源s最近的结点
        int tmpDist = MAXINT;
        int nextNode = s;
        for(int j = 0; j < n; j++) {
            if(!isVisited[j] && dist[j] < tmpDist) {
                nextNode = j;
                tmpDist = dist[j];
            }
        }

        // 设为已确定最短路径
        isVisited[nextNode] = true;
        // 更新 dist
        for(int j = 0; j < n; j++) {
            if(!isVisited[j] && w[nextNode][j] < MAXINT) {
                int newdist = dist[nextNode] + w[nextNode][j];
                if(newdist < dist[j]) {
                    dist[j] = newdist;
                    prev[j] = nextNode;
                }
            }
        }
    }

    // 释放资源
    delete isVisited;

}


int main() {
   
    const int n = 5;

    int w[maxNum][maxNum] = {
        {MAXINT, 10, MAXINT, 30, 100},
        {MAXINT, MAXINT, 50, MAXINT, MAXINT},
        {MAXINT, MAXINT, MAXINT, MAXINT, 10},
        {MAXINT, MAXINT, 20, MAXINT, 60},
        {MAXINT, MAXINT, MAXINT, MAXINT, MAXINT}
    };

    int dist[n];
    int prev[n];

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++)
            cout << w[i][j] << " ";
        cout << endl;
    }
    dijkstra(5, 0, w, dist, prev);

    for(int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < n; i++) {
        cout << prev[i] << "->";
    }

    return 0;
}

