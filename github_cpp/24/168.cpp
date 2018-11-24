template < class EDGE_TYPE, class ANSWER_TYPE = EDGE_TYPE >
struct minimum_spanning_tree {
	struct dsu {
		int n;
		vector < int > parents, size;
		void initialize(int k) {
			int i;
			n=k;
			parents = vector < int > (n+1);
			size = vector < int > (n+1);
			for(i=1;i<=n;i++) {
				parents[i]=i;
				size[i]=1;
			}
		}
		int find(int x) {
			while(x!=parents[x]) {
				parents[x]=parents[parents[x]];
				x=parents[x];
			}
			return x;
		}
		bool join(int x, int y) {
			int fx=find(x),fy=find(y);
			if(fx==fy) return false;
			if(size[fx]>=size[fy]) {
				size[fx]+=size[fy];
				parents[fy]=fx;
			}
			else {
				size[fy]+=size[fx];
				parents[fx]=fy;
			}
			return true;
		}
		bool connected(int x, int y) {
			return (find(x)==find(y));
		}
	};

	struct edge {
        int from,to;
        EDGE_TYPE w;
        bool operator <(const edge &a) const {
            return w<a.w;
        }
        edge(){}
        edge(int a, int b, EDGE_TYPE c): from(a), to(b), w(c) {}
    };

    dsu uf;
    int n;
    vector < edge > edges,mst;

    void initialize(int k) {
        n=k;
        uf.initialize(n);
        edges.clear();
        mst.clear();
    }

    void add_edge(int a, int b, EDGE_TYPE c) {
        edges.push_back(edge(a,b,c));
    }

    ANSWER_TYPE run() {
        int i;
        ANSWER_TYPE ans = 0;
        sort(edges.begin(),edges.end());
        for(i=0;i<(int)(edges.size());i++) if(uf.join(edges[i].from,edges[i].to)) {
            mst.push_back(edges[i]);
            ans+=edges[i].w;
        }
        return ans;
    }
};
