#include<iostream>
#include<list>
#include<stack>
using namespace std;

class graph
{public:
int v;
list<int> *array;
list<int> p; //keeps the topological order
stack <int> s; //to maintain dfs
bool *visited;

	graph(int);
	void add(int src,int des);
	void dfs(int);
	void topologicalsort(int);
};

graph::graph(int a)
	{
	v=a;
	array=new list<int>[v];
 	visited=new bool[v+1];
	for(int i=0;i<=v;i++)
	visited[i]=false;
	}

void graph::add(int src,int des)
	{
	array[src].push_back(des);
	}
void graph::topologicalsort(int l)
	{
	dfs(l);
	 while(!p.empty())
    		{
        	cout << p.front() << " ";
        	p.pop_front();
    		}
	}
void graph::dfs(int v)
	{
	
	s.push(v);
	visited[v]=true;
	list<int>::iterator i;
    
        while(!s.empty())
	{
        int now=s.top();
	
	p.push_back(now);
	s.pop();
	for(i=array[now].begin();i!=array[now].end();i++)
		{
		if(visited[*i]==false)
			dfs(*i);
		}
	
	}
        }
int main()
{
graph g(6);
//g.add(5, 2);
//g.add(5, 0);
g.add(4, 2);
g.add(4, 1);
g.add(3, 2);
g.add(3, 1);
 
cout << "Following is a Topological Sort of the given graph ";
g.topologicalsort(4);
//g.print();
return 0;
}
