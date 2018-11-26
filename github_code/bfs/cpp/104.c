#include<iostream>
using namespace std;
int que[20], f=-1, r=-1;
int enque(int n)
{
	if(r==20)
	cout<<"\n Stack Full";
	else if (f==-1 and r==-1)
	{
	r++;
	f++;
	que[r]=n;
	}
	else
	{
		r++;
		que[r]=n;
	}
}

int deque()
{
	f++;
	return(que[f-1]);
}
void create(int a[][10], int n)
{
	char ch;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		a[i][j]=0;
	}

	for (int i=0;i<n;i++)
	{
			for(int j=0;j<n;j++)
		{
			if(a[i][j]==1 || i==j)
				continue;
			cout<<"\n Edge Between "<<i<<" and "<<j<<" (y/n)?"<<endl;
			cin>>ch;
			if(ch!='n')
				a[i][j]=a[j][i]=1;
			else
				a[i][j]=a[j][i]=0;
		}
	}
}
void bfs(int a[][10],int n,int status[])
{
	int m,p,v;
	cout<<"\n Enter First Vertex "<<endl;
	cin>>v;
	status[v]=2;
	enque(v);
	while(f<=r && f!=-1 && r!=-1)
	{
		p=deque();
		status[p]=3;
		cout<<p;
		for(int i=n-1;i>=0;i--)
		{
			if(a[p][i]==1 && status[i]==1)
			{
				enque(i);
				status[i]=2;
			}
		}
	}
}
int main()
{
	int n,no,x,y,val,ch;
	cout<<"\n Enter number of vertices ";
	cin>>n;
	int a[n][10];
	create(a,n);
	int status[n];
	for(int i=0;i<n;i++)
	status[i]=1;
	bfs(a,n,status);
}



















