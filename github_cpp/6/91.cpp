#include <cstdio>
#include <vector>
using namespace std;

const int max_n = 1e3+5;
const int max_m = 1e4+5;
int n,m,s,t;
struct edge{
    int w;
    long long len;
};
long long dis[max_n];
vector<edge> graph[max_n];

int main()
{
    while(scanf("%d%d%d%d", &n, &m, &s, &t)!=EOF)
    {
        for(int i = 0 ; i < max_n; i++)
        {
            graph[i].clear();
        }
        
        for(int i = 0; i < m; i++)
        {
            int v,w,len;
            scanf("%d%d%d", &v, &w, &len);
            edge temp1, temp2;
            temp1.w = w;
            temp2.w = v;
            temp1.len = len;
            temp2.len = len;
            graph[v].push_back(temp1);
            graph[w].push_back(temp2);
        }
        
        for(int i = 0 ; i < max_n; i++)
        {
            dis[i] = max_n * max_m + 5;
        }
        
        dis[t] = 0;
        for( int i = 0 ; i < n ; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                for(int k = 0; k < graph[j].size(); k++)
                {
                    int w = graph[j][k].w;
                    int len = graph[j][k].len;
                    if(dis[j] > dis[w] + len)
                    {
                        dis[j] = dis[w] + len;
						printf("%lld\n", dis[j]);
                    }
                }
            }
        }
        
        printf("%lld", dis[s]);
    }
}
