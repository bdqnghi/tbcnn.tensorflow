/*
@theme: kruskal
@writer:pprp
@date:2017/8/19
@begin:21:19
@end:21:50
@declare:
*/

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000;
const int INF = 999999999;
int n , e;
struct node
{
    int x, y, w;
};
vector<node> vt;
int dad[maxn];//ÿ�����ĸ��׼���

bool cmp(const node& n1, const node& n2)
{
    return n1.w < n2.w;
}

int getfather(int x)
{
    if(x == dad[x])
        return x;
    dad[x] = getfather(dad[x]);
    return dad[x];
}

void kruskal()
{
    for(int i = 1; i <= n ;i++)
        dad[i] = i;
    int cnt = 1, ans = 0;
    for(int i = 1; i <= e ;i++)
    {
        if(getfather(vt[i-1].x)!=getfather(vt[i-1].y))
        {
            ans += vt[i-1].w;
            dad[getfather(vt[i-1].x)] = vt[i-1].y;
            cnt++;
            if(cnt == n)
            {
                cout << ans << endl;
                return ;
            }
        }
    }
    return ;
}


int main()
{
    freopen("in.txt","r",stdin);
    cin >> n >> e;
    for(int i = 0 ; i < e; i++)
    {
        node newnode;
        cin >>newnode.x >> newnode.y >> newnode.w;
        vt.push_back(newnode);
    }
    sort(vt.begin(),vt.end(),cmp);
    kruskal();

    return 0;
}
