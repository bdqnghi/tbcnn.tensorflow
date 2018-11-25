







#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

static const char *CC[] ={"数学分析","高等代数","空间解析几何","复变函数","常微分方程","计算方法","实变函数","泛函分析","高等几何"};
static const int MAXV = 1010;
static vector<int> G[MAXV];
static int inDegree[MAXV], N, M;

static int count_printf = 0;
static bool topological_sort(void){
    int num = 0;
    queue<int> q;
    for(int i = 0; i< N; i++){
        if(inDegree[i] == 0){
            q.push(i);
        }
    }
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < G[u].size(); i++){
            int v = G[u][i];
            inDegree[v]--;
            if(inDegree[v] == 0){
                q.push(v);
            }
        }
        if(count_printf != 0)printf(" -> ");
        printf("%s", CC[u]);
        count_printf++;
        G[u].clear();
        num++;
    }
    
    if(num == N)return true;
    else return false;
    
}

int topological(void){
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    memset(inDegree, 0, sizeof(inDegree));
    int u, v;
    for(int i = 0; i < M; i++){
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        inDegree[v]++;
    }
    
    topological_sort();
    
    
    return 0;
}
