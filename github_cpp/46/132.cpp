#include<bits/stdc++.h>
using namespace std;

#define size 100005

int arr[size];
int tree[4*size];

void construct(int node, int low, int high)
{
    int mid;
    if(low==high)
    {
        tree[node] = arr[low];
        return;
    }

    mid = (low+high)/2;
    construct(node*2,low,mid);
    construct(node*2+1,mid+1,high);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int query(int i,int j,int low,int high,int node)
{
    int mid;
    if(i>high || j<low)
    {
        return 0;
    }
    if(low>=i && high<=j)
    {
        return tree[node];
    }
    mid = (low+high)/2;
    int x = query(i,j,low,mid,node*2);
    int y = query(i,j,mid+1,high,node*2+1);
    return x+y;
}

void update(int i,int low,int high,int node,int newval)
{
    int mid;
    if(i>high || i<low)
    {
        return;
    }
    if(low>=i && high<=i)
    {
        tree[node]+=newval;
        return;
    }
    mid = (low+high)/2;
    update(i,low,mid,node*2,newval);
    update(i,mid+1,high,node*2+1,newval);
    tree[node] = tree[node*2]+tree[node*2+1];
}


int main()
{
	return 0;
}
