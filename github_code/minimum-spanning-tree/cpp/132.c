#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
class UnionFind{
    private: vi rank, p;
             int sets;
    public:
             UnionFind(int N){
                 rank.assign(N, 0);
                 p.assign(N, 0);
                 sets = N;
                 for(int i = 0; i < N; i++){
                     p[i] = i;
                 }
             }
             int findSet(int i){
                 return ((p[i] == i) ? i : (p[i] = findSet(p[i])));
             }
             bool isSame(int i, int j){
                 return findSet(i) == findSet(j);
             }
             void unite(int i, int j){
                 int x = findSet(i), y = findSet(j);
                 if(x != y){
                     sets --;
                     if(rank[x] > rank[y]){
                         p[y] = x;
                     }
                     else{
                         p[x] = y;
                         if(rank[x] == rank[y])
                             rank[y]++;
                     }
                 }
             }
             int countsets(){
                 return sets;
             }

};


int main(){
    int N, M, u, v, w;
    while(true){
        scanf("%d%d",&N,&M);
        if(N == 0 && M == 0)
            break;
        if(M == 0){
            printf("Impossible\n");
            continue;
        }
        vector< pair<int, ii> > edges;
        for(int i = 0; i < M; i++){
            scanf("%d%d%d",&u,&v,&w);
            edges.push_back(make_pair(w, ii(u,v)));
        }
        sort(edges.begin(), edges.end());
        long long cost = 0;
        UnionFind uf(N);
        vii ans;
        for(int i = 0; i < M; i++){
            pair<int, ii> pop = edges[i];
            if(!uf.isSame(pop.second.first, pop.second.second)){
                cost += pop.first;
                if(pop.second.first <= pop.second.second)
                    ans.push_back(ii(pop.second.first, pop.second.second));
                else
                    ans.push_back(ii(pop.second.second, pop.second.first));
                uf.unite(pop.second.first, pop.second.second);
            }
        }
        if(uf.countsets() != 1){
            printf("Impossible\n");
            continue;
        }
        sort(ans.begin(), ans.end());
        printf("%lld\n",cost);
        for(int i = 0; i < ans.size(); i++)
            printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}

