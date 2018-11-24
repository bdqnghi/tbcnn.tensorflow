struct UnionFind{
    vector<int> data;
    UnionFind(int size) : data(size, -1) {}
    bool unionSet(int x,int y){
        x=root(x);y=root(y);
        if(x==y)return 0;
        if(data[y]<data[x])swap(x,y);
        data[x]+=data[y],data[y]=x;
        return 1;
    }
    bool findSet(int x,int y){
        return root(x)==root(y);
    }
    int root(int x){
        return data[x]<0 ? x : data[x]=root(data[x]);
    }
    int size(int x){
        return -data[root(x)];
    }
};
class KRK{//c++11
	public:
	struct edge{
		int from,to,cost;
	};
	vector<edge>G;
	int n;
	KRK(int size){
		n=size;
	}
	void add_edge(int a,int b,int c){
		edge e={a,b,c};
		G.pb(e);
	}
	int krk(){
		int sum=0;
		sort(all(G),[](edge a,edge b){
			return a.cost<b.cost;
		});
		UnionFind uf(n);
		rep(i,G.size()){
			edge e=G[i];
			if(!uf.findSet(e.from,e.to)){
				sum+=e.cost;
				uf.unionSet(e.from,e.to);
			}
		}
		return sum;
	}
};
int main(){
	int n,m;
	cin>>n>>m;
	KRK krk(n);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		krk.add_edge(a,b,c);
	}
	cout<<krk.krk()<<endl;
}