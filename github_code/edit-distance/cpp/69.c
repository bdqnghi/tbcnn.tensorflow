#include <stdio.h>
using namespace std;

int min(int a,int b)
{return a<b?a:b;}

int editDist(char *c1, char *c2, int n1,int n2)
{
    int ed[n1+1][n2+1];
    
    for(int i=0;i<=n1;i++)
        for(int j=0;j<=n2;j++)
        {
            if(i==0 or j==0)
                ed[i][j]=i+j;
            else if(c1[i-1]==c2[j-1])
                ed[i][j]=ed[i-1][j-1];
            else
                ed[i][j]=min(min(ed[i-1][j],ed[i][j-1]),ed[i-1][j-1])+1;
        }

    return ed[n1][n2];
}

int main() {
	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
    int t;
    scanf("%d",&t);
    
    while(t--)
    {
        int n1,n2;
        scanf("%d%d",&n1,&n2);

        char c1[n1],c2[n2];
        scanf("%s%s",c1,c2);
        //printf("%s%s",c1,c2);
        printf("%d\n",editDist(c1,c2,n1,n2));
    }
	return 0;
}
