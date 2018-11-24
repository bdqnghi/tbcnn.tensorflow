#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for(int k=1;k<=t;k++)
    {
    int d[1005],edge_u[2005],edge_v[2005],cost[2005];
    int edge,node;
    for(int i=0;i<=1000;i++)
    {
        d[i]=1000000000;
    }
    cin>>node>>edge;
    for(int i=1;i<=edge;i++)
    {
        cin>>edge_u[i]>>edge_v[i]>>cost[i];//Edges and cost
    }
    int source=0,destination;
    //cin>>source>>destination;//Input source and Destination
    d[source]=0;
    bool neg_cycle=false;
    for(int i=1;i<=node;i++)
    {
        bool update=false;
        for(int j=1;j<=edge;j++)
        {
            int u=edge_u[j],v=edge_v[j];
            if(d[u]+cost[j]<d[v])
            {
                d[v]=d[u]+cost[j];
                update=true;
                if(i==node)
                neg_cycle=true;
            }
        }
        if(update==false)
        break;
    }
    if(neg_cycle)
    {
        cout<<"possible\n";
    }
    else
        cout<<"not possible\n";
    }
    return 0;
}
