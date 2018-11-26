#include<iostream>
using namespace std;
int cost[10][10],m,i,j,k,n,qu[10],front,rear,v,visit[10],visited[10];
int main()
{
cout<<"enter no. of vertices\n";
cin>>n;
cout<<"enter no.of edges\n";
cin>>m;
cout<<"\nEdges\n";
for(k=1;k<=m;k++)
    {
cin>>i>>j;
cost[i][j]=1;
}
cout<<"enter initial vertex\n";
cin>>v;
cout<<"visited vertex\n";
cout<<v<<" ";
visited[v]=1;
k=1;
while(k<n){
    for(j=1;j<=n;j++){
        if(cost[v][j]!=0 && visited[j]!=1 && visit[j]!=1){
            visit[j]=1;
            qu[rear++]=j;
        }
    }
    v=qu[front++];
    cout<<v<<" ";
    k++;
}
return 0;
}
