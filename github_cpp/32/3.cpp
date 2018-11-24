/*

//Kruskal’s Minimum Spanning Tree Algorithm

#include <iostream>
#include<stack>
#include<vector>
#include<stdlib.h>
#include<limits.h>
#include<algorithm>
using namespace std;

struct Edge{
	int src;
	int dest;
	int wt;
	bool toInclude;
};

int compare(struct Edge* e1,struct Edge* e2){
	return (e1->wt)<(e2->wt);
}

int findParent(int x,int parent[]){
	if(parent[x]==-1){
		return x;
	}
	return findParent(parent[x],parent);
}

void unionNodes(int x,int y,int parent[]){
	int x_=findParent(x,parent);
	int y_=findParent(y,parent);

	parent[x_]=y_;
}
int main(){
	vector<struct Edge*> v;
	int N,M;
	int src,dest,wt;
	cin>>N>>M;
	for(int i=0;i<M;i++){
		cin>>src>>dest>>wt;
		struct Edge* e=(struct Edge*)malloc(sizeof(struct Edge));
		e->src=src;
		e->dest=dest;
		e->wt=wt;
		e->toInclude=false;
		v.push_back(e);
		//cout<<"Entered edge"<<endl;

		struct Edge* e1=(struct Edge*)malloc(sizeof(struct Edge));
				e1->src=dest;
				e1->dest=src;
				e1->wt=wt;
				e1->toInclude=false;
				v.push_back(e1);
		//		cout<<"Entered edge 2"<<endl;
	}

	sort(v.begin(),v.end(),compare);

	vector<struct Edge*>::iterator it;
	vector<struct Edge*> result;
	int parent[N+1];
	for(int i=1;i<=N;i++){
		parent[i]=-1;
	}
	cout<<"Size of vector is "<<v.size()<<endl;
	for(it=v.begin();it!=v.end();it++){
		struct Edge* e=*it;

		if(e->toInclude==false){
		int x=findParent(e->src,parent);
		int y=findParent(e->dest,parent);

		if(x!=y){
			cout<<"Merging "<<e->src<<" "<<e->dest<<" "<<e->wt<<endl;
			e->toInclude=true;
			v.erase(it);
			result.push_back(e);
			cout<<"Erasing 1 :"<<e->src<<" "<<e->dest<<" "<<e->wt<<endl;
			v.push_back(e);
			unionNodes(x,y,parent);


		}
		else {
			cout<<"Erasing 2 :"<<e->src<<" "<<e->dest<<" "<<e->wt<<endl;
			v.erase(it);
		}
		}
	}

	for(it=result.begin();it!=result.end();it++){
		struct Edge* e=*it;

			cout<<e->src<<" "<<e->dest<<" "<<e->wt<<endl;

}

}


*/
