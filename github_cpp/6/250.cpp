#include<iostream>
using namespace std;
int main()
{
    int dis[10],bak[10],u[10],v[10],w[10];
    int inf=9999999;
    int n,m;
    cin>>n>>m;//输入顶点和边数
    //读入边
    for(int i=1; i<=m; i++)
        cin>>u[i]>>v[i]>>w[i];
    //初始化dis数组
    for(int i=1; i<=n; i++)
        dis[i]=inf;
    dis[1]=0;
    //bellman-ford核心
    for(int k=1; k<=m; k++){
        int check=0;//标记本轮松弛中dis数组是否发生更新
        for(int i=1; i<=m; i++){
            if( dis[v[i]]>dis[u[i]]+w[i] ){
                dis[v[i]]=dis[u[i]]+w[i];
                check=1;
            }
        }
        if(check==0)
            break;
    }
    //检测负权回路
    int flag=0;
    for(int i=1; i<=m; i++)
        if(dis[v[i]]>dis[u[i]]+w[i])
        flag=1;
    if(flag)
        cout<<"this tu hava fuquanhuilu.\n";
    else{
        for(int i=1; i<=n; i++)
            cout<<"origin to "<<i<<" distance is : "<<dis[i]<<endl;
    }

}
