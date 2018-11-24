#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e4 + 5;
/* Finds the sum of weights of the edges of the Minimum Spanning Tree.
    Graph is represented as adjacency list using array of vectors.  MAX 
    is an upper  limit on number of vertices.
   g[u] represents adjacency list of vertex u,  Every element of this list 
   is a pair<w,v>  where v is another vertex and w is weight of edge (u, v)
  Note : Vertex numbers start with 1 and don't need to be contiguous.   */
int spanningTree(vector <pair<int,int> > g[], int MAX)
{
	set<int> mst_not;
	set<int> mst;
	set<int>::iterator it;
	int hemap[MAX];
	for(int i=0;i<MAX;i++){
		if(g[i].size())
			mst_not.insert(i);
		hemap[i]=MAX;
	}
	it=mst_not.begin();
	hemap[*it]=0;
	
	vector< pair<int,int> >::iterator it1;
	int n=mst_not.size();
	int sum=0;
	while(mst.size()!=n){
		
		int min = INT_MAX, min_index;
		for (int v = 0; v < MAX; v++)
			if (mst.find(v) == mst.end() && hemap[v] < min)
				min = hemap[v], min_index = v;
		
		mst.insert(min_index);
		sum=sum+min;
		
		for(it1=g[min_index].begin();it1!=g[min_index].end();it1++){
			if(mst.find(it1->second)==mst.end() && it1->first<hemap[it1->second])
				hemap[it1->second]=it1->first;
		}
	}
	return sum;
}

int main()
{
	int t ;
	cin>>t;
	while(t--)
	{
	vector <pair<int,int> > adj[MAX];
    int n,e;
    int w, mC;
    cin >> n>> e;
    for(int i = 0;i < e;++i)
    {
    	int x,y;
        cin >> x >> y >> w;
        adj[x].push_back({w, y});
        adj[y].push_back({w, x});
    }
  
    mC= spanningTree(adj, MAX);
    cout << mC << endl;
	}
    return 0;
}
