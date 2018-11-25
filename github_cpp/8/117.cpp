#include<iostream>
#include<list>
#include<vector>
#include<stack>

using namespace std;

struct graph
{

	bool visited = false;
	list < int > l;
};

void add(vector < graph > & g, int index, int direct)
{
	g[index].l.push_back(direct);
}

void topological_sort(vector < graph >& g,stack < int > & s,int index)
{
	g[index].visited = true;

	for(auto& y: g[index].l)
	{
		if(!g[y].visited)
		topological_sort(g,s,y);
	}

	s.push(index);

}

int main()
{
	int n = 6;
	vector < graph > g(n);

	add(g,5,0);
	add(g,5,2);
	add(g,2,3);
	add(g,3,1);
	add(g,4,0);
	add(g,4,1);

	stack < int > s;

	for(int i=0;i<g.size();i++)
	{
		if(!g[i].visited)
		{
			topological_sort(g,s,i);
		}
	}

	while(!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}

	return 0;
}