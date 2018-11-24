#include <iostream>
using namespace std;
int main()
{
    int e[10][10],i,j,k,m,n,t1,t2,t3;
    int inf = 9999999;
    cin>>n>>m;
    //initialize
    for( i=1; i<=n; i++ )
        for( j=1; j<=n; j++ )
        if(i==j) e[i][j]=0;
        else e[i][j]=inf;

    //read edge读入边
    for(i=1; i<=m; i++)
    {
        cin>>t1>>t2>>t3;
        e[t1][t2]=t3;
    }
    //algorithm core
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
            if( e[i][j] > e[i][k]+e[k][j] )
                e[i][j] = e[i][k]+e[k][j];
    //output results
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n ;j++)
            cout<<e[i][j]<<' ';
        cout<<endl;
    }
    return 0;
}
