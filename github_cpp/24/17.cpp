#include <iostream>
#include <algorithm>

using namespace std;

const long long maxx =1e4+5;
pair <long long , pair <int, int> > adj[maxx];
int main_root[maxx];
int nodes, edges;

int root(int x)
{
    while(main_root[x]!=x)
    {
        main_root[x]=main_root[main_root[x]];
        x=main_root[x];
    }
    return x;
}

void unions(int x, int y)
{
    main_root[root(y)] = main_root[root(x)];
}

long long  MST(pair <long long , pair <int, int> > adj[])
{
    int i, x, y;
    long long weight=0, w;

    for(i=0; i<edges; i++)
    {
        x = adj[i].second.first;
        y = adj[i].second.second;
        w = adj[i].first;

        if(root(x)!=root(y))
        {
            weight += w;
            unions(x,y);
        }
    }
    return weight;
}


int main()
{
    int i;
    cin>>nodes>>edges;

    for(i=0; i<edges; i++)
    {
        int x,y;
        long long w;
        cin>>x>>y>>w;
        adj[i] = make_pair(w, make_pair(x, y));
    }

    for(i=0; i<=maxx; i++)
        main_root[i]=i;

    sort(adj , adj + edges);
    cout<<MST(adj)<<endl;

    /*
    for(i=0; i<=5; i++)
        cout<<main_root[i]<<" ";
        */

    return 0;
}
