/* 

Problem statement link https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/ioi-2050-2/

*/


#include<iostream>
#include<list>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>

using namespace std;

typedef long long ll;

struct node{
	ll wt;
	pair<ll, ll> edge;
};

struct node2{
	bool visited = false;
	vector< pair<ll, ll> > l;
};

struct node3{
	ll size;
	ll val;
};

bool comparator(const node& a, const node& b){
	return a.wt < b.wt;
}

vector<node3> arr(1005);

void initialize(ll n){
	for(ll i=0; i<n; i++){
		node3 temp;
		temp.val = i;
		temp.size = 1;

		arr.at(i) = temp;
	}
}

ll root(ll i){
	while(arr.at(i).val != i){
		arr.at(i).val = arr.at(arr.at(i).val).val;
		i = arr.at(i).val;
	}

	return i;
}

void Union(ll a, ll b){
	ll r_a = root(a);
	ll r_b = root(b);

	if(r_a == r_b)
		return ;

	if(arr.at(r_a).size < arr.at(r_b).size){
		arr.at(r_a).val = arr.at(r_b).val;
		arr.at(r_b).size += arr.at(r_a).size;
	}
	else{
		arr.at(r_b).val = arr.at(r_a).val;
		arr.at(r_a).size += arr.at(r_b).size;
	}

}

ll find(ll a, ll b){
	return root(a) == root(b);
}

ll Dist[1005][1005];

void dfs(vector<node2> &graph, ll u, ll dist, ll start){
	graph.at(u).visited = true;
	Dist[start][u] = dist;

	for(auto y: graph.at(u).l){
		if(!graph.at(y.first).visited){
			dfs(graph, y.first, dist+y.second, start);
		}
	}
}

void makefalse(vector<node2> &graph){
	for(auto &y: graph){
		y.visited = false;
	}
}

void makeMST(vector<node> &Graph, ll n, ll q){
	vector<node2> graph(n+1);

	for(auto y: Graph){

		if(!find(y.edge.first, y.edge.second)){
			Union(y.edge.first, y.edge.second);

			graph.at(y.edge.first).l.push_back({y.edge.second, y.wt});
			graph.at(y.edge.second).l.push_back({y.edge.first, y.wt});
		}
	}

	memset(Dist, 0, (n+1)*(n+1)*sizeof(ll));

	for(ll i=1; i<=n; i++){
		dfs(graph, i, 0, i);
		makefalse(graph);
	}

	while(q--){
		ll u, v;
		cin>>u>>v;

		cout<<Dist[u][v]<<endl;
	}
}

int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll t;
	cin>>t;

	for(ll i=1; i<=t; i++){
		ll n,m,q;
		cin>>n>>m>>q;

		vector<node> Graph(m+1);

		initialize(n+1);

		for(ll i=1; i<=m; i++){
			ll u,v,w;
			cin>>u>>v>>w;

			Graph.at(i).wt = w;
			Graph.at(i).edge = {u,v};	
		}

		sort(Graph.begin(), Graph.end(), comparator);

		cout<<"Case: "<<i<<endl;
		makeMST(Graph, n, q);
	}
	
	return 0;

}