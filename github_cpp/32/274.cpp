#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
///////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////
int MAX = 100000;
pair <int, pair <int, int> >p[100000];
int id[100000];

////////////////////////////////////////////
// INIT FUNCTION FOR UNION FIND
//////////////////////////////////////////////
void init(){
	for(int i=0;i<MAX;i++)
		id[i] = i;
}
/////////////////////////////////////////////
// ROOT FOR UNION FIND
////////////////////////////////////////////
int root(int x){

	while(x!=id[x]){
		id[x] = id[id[x]];
		x = id[x];
	}
	return x;
}
//////////////////////////////////////////////
// UNION FOR UNION FIND
//////////////////////////////////////////////
void union1(int x, int y){

	int p = root(x);
	int q =root(y);
	id[p] = id[q];
}
//////////////////////////////////////////////
// KRUSKAL MINCOST FUNCTION
//////////////////////////////////////////////
int kruskal(int edges){
	int x,y,weight,mincost = 0;
	for(int i =0;i<edges;i++){
		x = p[i].second.first;
		y = p[i].second.second;
		weight = p[i].first;
		//cout<<root(x)<<" "<<root(y)<<endl;
		if(root(x) != root(y)){
			//cout<<weight<<endl;
			mincost += weight;
			union1(x, y);
		}
	}
	return mincost;

}
//////////////////////////////////////////////
// DRIVER FUNCTION
/////////////////////////////////////////////
int main(void){
	int n,x,y,w;
	cout<<"Enter no. of edges\n";
	cin>>n;
	init();
	cout<<"Enter edges and weights respectively\n";
	for(int i=0;i<n;i++){
		cin>>x>>y>>w;
		p[i] = make_pair(w, make_pair(x, y));
	}
	sort(p,p+n);
	cout<<"The mincost tree is ="<<kruskal(n)<<endl;
}