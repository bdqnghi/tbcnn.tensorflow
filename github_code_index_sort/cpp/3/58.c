/*input
4
0 1
3 1 
1 3 
3 2
*/
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;

struct GraphNode
{
    int value;
    set<int> adj;
    GraphNode():value(-1){}
    GraphNode(int val):value(val){}
};
class DAG
{
    public:
        unordered_map<int,GraphNode *> val_to_node;
    
        void add_edge(int left,int right);
};

void DAG::add_edge(int left,int right)
{
    GraphNode *leftnode,*rightnode;
    
    if(val_to_node.count(left)==0) //left not in graph
    {
        leftnode = new GraphNode(left);
        val_to_node[left]=leftnode;
    }
    if(val_to_node.count(right)==0) //right not in graph
    {
        rightnode = new GraphNode(right);
        val_to_node[right]=rightnode;
    }
    leftnode = val_to_node[left];
    leftnode->adj.insert(right);
}


bool DFS(DAG &theGraph,int elem,unordered_set<int> &in_stack,unordered_set<int> &visited)
{
	cout<<"ROOT "<<elem<<endl;
	if(in_stack.count(elem)==1)
		return false;
	if(visited.count(elem)==1)
		return true;
	set<int> &st = theGraph.val_to_node[elem]->adj;
	
	in_stack.insert(elem);
	visited.insert(elem);
	//cout<<st.size()<<endl;
	for(auto it=st.begin();it!=st.end();it++)
	{
		if(DFS(theGraph,*it,in_stack,visited)==false)
		{
			return false;
		}

	}
	in_stack.erase(elem);
	return true;
}

int main()
{
	int n;
	cin>>n;
	int l,u;
	DAG courses;
	for(int i=0;i<n;i++)
	{
		cin>>l>>u;
		courses.add_edge(u,l);
	}
	unordered_set<int> in_stack,visited;
	for(auto it = courses.val_to_node.begin();it!=courses.val_to_node.end();it++)
	{
		int elem = (*it).first;
		if(DFS(courses,elem,in_stack,visited)==false)
			{
				cout<<false<<endl;
				return 0;
			}
	}
	cout<<true;
	//cout<<"VA"<< DFS(courses,0,in_stack,visited)<<endl;
}