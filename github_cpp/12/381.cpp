#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"\n Enter the no of vertices";
    int n,i,j,k;
    cin>>n;
    int **ar=(int **)malloc((n+1)*sizeof(int *));
    for(i=0;i<=n;i++)
        ar[i]=(int *)malloc(n*sizeof(int));
    cout<<"Enter adjacency matrix\n";
    for(i=1;i<n+1;i++)
        for(j=1;j<n+1;j++)
        {
            cin>>ar[i][j];
            if((ar[i][j]==0))
                ar[i][j]=INT_MAX;
        }
        for(i=0;i<n+1;i++)ar[i][i]=0;

       for(k=1;k<=n;k++)
            for(i=1;i<=n;i++)
               for(j=1;j<=n;j++)
                    if(ar[i][k]!=INT_MAX&&ar[k][j]!=INT_MAX&&ar[i][j]>ar[i][k]+ar[k][j])
                        ar[i][j]=ar[i][k]+ar[k][j];

        cout<<"Shortest path among all pair of verices are:-\n";
        for(i=1;i<n+1;i++)
            for(j=1;j<n+1;j++)
            {
                if (i==j) continue;
                if(ar[i][j]==INT_MAX)
                    cout<<"\nFrom vertex "<<i<<" to "<<j<<"--  INFINITY";
                else
                    cout<<"\nFrom vertex "<<i<<" to "<<j<<"--  "<<ar[i][j];
            }
        return 1;
}
/*
0 5 0 10
0 0 3 0
0 0 0 1
0 0 0 0
*/
