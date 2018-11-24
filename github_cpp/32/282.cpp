#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;
int m;                       
int n;
int z;
int a[100][100];          
int dist[100];              
int prev[100];				
int MAX_VALUE=10000;    
char pname[30][100];
char pnum[5];
void dijkstra()               
{
	if(m<0||m>n)              //当无顶点的情况
		return;
	bool *s=new bool[n+1];
	for(int i=0;i<n;i++)
	{
		dist[i]=a[0][i];       //与源点相连的权值
		s[i]=false;
		if(dist[i]==MAX_VALUE) //与源点无连接的顶点
			prev[i]=0;         //设置对应权值为
		else
			prev[i]=m;         //与源点相连接的顶点设置为m
	}
	dist[m]=0;
	s[m]=true;
	for(int i1=0;i1<n;i1++)
	{
		float temp=MAX_VALUE;
		int u=m;
		for(int j=0;j<n;j++)
			if((!s[j])&&(dist[j]<temp))//与源点相连的顶点
			{
				u=j;                    
				temp=dist[j];          //设置temp成为与源点相连的顶点权值
			}
		s[u]=true;
		for(int j1=0;j1<n;j1++)
			if((!s[j1])&&(a[u][j1]<MAX_VALUE))
			{
				float newdist=dist[u]+a[u][j1];  //算出与源点不直接相连的权值和
				if(newdist<dist[j1])
				{
					dist[j1]=newdist;
					prev[j1]=u;
				}
			}
	}
}
void path()
{
	for(int i=0;i<n;i++)
		if(i!=m&&dist[i]<MAX_VALUE && i==z)
		{
			cout<<"由源到顶点"<<i<<"的最短路径为：(终点位置)  "<<i;
			int temp=i;
			do
			{
				temp=prev[temp];
				cout<<" <-- "<<temp;
			}while(temp!=m);
			cout<<"  (源位置)。最短路径长度为："<<dist[i]<<endl;
		}
}
/**
void path()
{
	for(int i=0;i<n;i++)
		if(i!=m&&dist[i]<MAX_VALUE && i==z)
		{
			cout<<"由源到顶点"<<i<<"的最短路径为：(终点位置)  "<<i;
			int temp=i;
			do
			{
				temp=prev[temp];
				cout<<" <-- "<<temp;
			}while(temp!=m);
			cout<<"  (源位置)。最短路径长度为："<<dist[i]<<endl;
		}
}

**/
int main()
{
	gets(pnum);
	n=atoi(pnum);
	memset(a,0x0,100*100*sizeof(int));
	for(int i=0;i<n;i++){
		gets(pname[i]);
		cout<<pname[i]<<endl;
	}
	gets(pnum);
	int line_num=atoi(pnum);
	char buf[100];
	char snode[50],enode[50];
	char juli[20];
	for(int i=0;i<line_num;i++){
		gets(buf);
		//cout<<buf<<endl;
		sscanf(buf,"%s %s %s",snode,enode,juli);
		int snodeno=-1,enodeno=-1;
		for(int j=0;j<n;j++){
			if(strcmp(snode,pname[j])==0)
				snodeno=j;
			if(strcmp(enode,pname[j])==0)
				enodeno=j;
			if(snodeno>=0 && enodeno>=0)
				break;
		}
		a[snodeno][enodeno]=atoi(juli);
		a[enodeno][snodeno]=atoi(juli);
		cout<<snode<<snodeno<<"-"<<enode<<enodeno<<" = "<<juli<<endl;
	}
	gets(pnum);
	int juli_num=atoi(pnum);
	for(int i=0;i<juli_num;i++){
		gets(buf);
		sscanf(buf,"%s %s",snode,enode);
		int snodeno=-1,enodeno=-1;
		for(int j=0;j<n;j++){
			if(strcmp(snode,pname[j])==0)
				snodeno=j;
			if(strcmp(enode,pname[j])==0)
				enodeno=j;
			if(snodeno>=0 && enodeno>=0)
				break;
		}
		m=snodeno;
		z=enodeno;
		cout<<"start:"<<m<<" end:"<<z<<endl;
		dijkstra();
		path();
	}
	
	return 0;
	cout<<"请输入顶点的个数：";
	cin>>n;
	cout<<"请分别对两顶点之间赋权值(若无此连接，赋'0'值,请注意两顶点之间的方向):"<<endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(i==j)
				continue;
			cout<<"顶点"<<i<<"到顶点"<<j<<"的权值为：";
			cin>>a[i][j];
			if(a[i][j]==0)
				a[i][j]=MAX_VALUE;
		}
	cout<<"请输入此带权有向图的源顶点的编号：";
	cin>>m;
	dijkstra();
	path();

	return 0;
}
