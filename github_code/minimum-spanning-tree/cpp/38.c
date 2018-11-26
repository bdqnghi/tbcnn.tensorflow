/* https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/quantitative-coefficient/ */

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

typedef long long ll;

struct node1{
	ll weight;
	pair<ll, ll> edge; 
};

struct node3{
	ll size;
	ll val;
};

bool comparator(const node1& nodea, const node1& nodeb){
	return nodea.weight < nodeb.weight;
}

vector<node3> arr;

void initialize(ll n){
    //arr.resize(n);
	for(ll i=0; i<n; i++){
		node3 temp;
		temp.val = i;
		temp.size = 1;

		arr.push_back(temp);
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
	ll root_a = root(a);
	ll root_b = root(b);

	if(root_a == root_b)
		return;

	if(arr.at(root_a).size < arr.at(root_b).size){
		arr.at(root_a).val = arr.at(root_b).val;
        arr.at(root_b).size +=  arr.at(root_a).size;
	}

	else{
		arr.at(root_b).val = arr.at(root_a).val;
        arr.at(root_a).size +=  arr.at(root_b).size;
	}
}

ll find(ll a, ll b){
	return (root(a) == root(b));
}

ll m = 1000000007;

ll kruskal(vector<node1> &graph){
	ll mincost = 1;
	//vector<ll> path;

	for(auto& i: graph){
		if(!find(i.edge.first, i.edge.second)){
			Union(i.edge.first, i.edge.second);
			mincost  = (mincost * i.weight) % m;
			//path.push_back(i.weight);
		}
	}

	return mincost;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    ll t;
    cin>>t;

    while(t--) {
        ll n, m;
        cin>>n>>m;

        initialize(n);
        vector<node1> graph(m);

        for(ll i = 0; i < m; ++i) {
            ll x, y, w;
            cin>>x>>y>>w;

            graph.at(i).weight = w;
            graph.at(i).edge = make_pair(--x, --y);
        }

        sort(graph.begin(), graph.end(), comparator);

        cout<<kruskal(graph)<<endl;
        graph.clear();
        arr.clear();
    }
    
    return 0;
}