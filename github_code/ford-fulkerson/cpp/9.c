#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
using namespace std;
#define INF 1<<20

int DEBUG=0;

class Edge{
  public:
	int from;
	int to;
	int cost;
	bool done;

	Edge(){};

	Edge(int f,int t,int c){
		from=f;
		to=t;
		cost=c;
		done=false;
	}
};

map<int,map<int,Edge> > edges;
map<int,bool> nodes;

typedef map<int,bool>::iterator itemib;
typedef map<int,Edge>::iterator itemiedge;
typedef vector<int>::iterator itevi;

void show_edges(){
	cout<<"show_edges"<<endl;
	for(map<int,map<int,Edge> >::iterator it=edges.begin();\
		it!=edges.end();++it){
		for(map<int,Edge>::iterator _it=it->second.begin();\
		_it!=it->second.end();++_it){
			if(_it->second.from==0&&_it->second.to==0) exit(10);
			cout<<_it->second.from<<" to "<<_it->second.to<<" :"<<_it->second.cost<<endl;

		}

	}
}

vector<int> routes;
int dfs(int s, int g, int cost){

	if(s==g){
		routes.push_back(s);
		return cost;
	}

	nodes[s]=true;

	//show_edges();
	for(itemiedge it=edges[s].begin();\
		it!=edges[s].end();++it){

		Edge* e=&(it->second);
		Edge* eto=&edges[e->to][s];

		if(!nodes[e->to] && e->cost>0){
			int d=dfs(e->to,g,min(e->cost,cost));

			if(d>0){
				routes.push_back(s);

				e->cost-=d;
				eto->cost+=d;

				return d;
			}
		}
	}
	return 0;
}

void show_routes(){
	reverse(routes.begin(),routes.end());
	for(itevi it=routes.begin();\
		it!=routes.end();++it){
		if(DEBUG==1){
			cout<<*it;
			if(it!=routes.end()-1){
				cout<<"->";
			}
		}
	}
}

void flagoff(){
	for(itemib it=nodes.begin();\
		it!=nodes.end();++it){
		it->second=false;
	}
	
}

int main(int argc, char* argv[]){
	if(argc==2&&atoi(argv[1])==1) DEBUG=1;
	cout<<"[Maximum flow search by ford fulkerson algorithm]"<<endl<<endl;

	int T;
	cin>>T;

	int from,to,cost;
	for(int i=0;i<T;++i){
		cin>>from>>to>>cost;
		edges[from][to]=Edge(from,to,cost);
		edges[to][from]=Edge(to,from,0);
		nodes[from]=false;
	}
	int start,goal;
	cin>>start>>goal;

	//show_edges();
	int flow=0;
	for(;;){
		flagoff();
		from=dfs(start,goal,INF);
		show_routes();
		routes.clear();
		if(from==0){
			break;
		}
		if(DEBUG==1) cout<<":"<<from<<endl;
		flow+=from;
	}
	cout<<"Max flow is "<<flow<<"."<<endl;

}

