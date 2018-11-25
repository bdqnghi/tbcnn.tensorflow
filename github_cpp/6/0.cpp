#include<iostream>

using namespace std;

int stack[20], top=-1;

void push(int a)
{
	top++;
	stack[top]=a;
}

int pop()
{
	top--;
	return (stack[top+1]);
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

void dfs(int a[][10],int n,int status[])
{
	int m,p,v;
	cout<<"\n Enter First Vertex "<<endl;
	cin>>v;
	push(v);
	while(top!=-1)
	{
		p=pop();
		status[p]=2;
		cout<<p;
		for(int i=n-1;i>=0;i--)
		{
			if(a[p][i]==1 && status[i]==1)
			{
				push(i);
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
	dfs(a,n,status);
	return 0;
}



















