#include<bits/stdc++.h>
using namespace std;
vector<int>path;
int matrix[100][100],next[100][100];
void findpath(int i, int j)
{
    path.clear();
    path.push_back(i);
    while(i!=j)
    {
        i=next[i][j];
        path.push_back(i);
    }
    for(i=path.size()-1;i>=0;i--)
    {
        printf("%d",path[i]);
        if(i)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int i,j,k,node,edge;


    memset(matrix,0,sizeof(matrix));

    scanf("%d %d",&node,&edge);
    for(i=0;i<edge;i++)
    {
        scanf("%d %d",&j,&k);
        matrix[j][k]=1;
    }
    for(i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            next[i][j]=j;
        }
    }
    for(k=0;k<node;k++)
    {
        for(i=0;i<node;i++)
        {
            for(j=0;j<node;j++)
            {
                if(matrix[i][k]+matrix[k][j]<matrix[i][j])
                {
                    matrix[i][j]=matrix[i][k]+matrix[k][j];
                    next[i][j]=next[i][k];
                }
            }
        }
    }

    return 0;
}
