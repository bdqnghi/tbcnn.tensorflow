//C++ Code :  Max Flow

#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<algorithm>
#include<fstream>
using namespace std;

#define START -1
#define UNUSED -2



/***************** Max Flow Algorithm***************
****************************************************/
const int maxINDX=102;
int flow[maxINDX][maxINDX],originalcap[maxINDX][maxINDX], cap[maxINDX][maxINDX];
int path[maxINDX]; // stores parent of each node
int src,dest;

/* BFS using a matrix */
int BFS(int node) {
	int i,item,cf;
	queue<int> q;
	for(i=1;i<=node;i++) path[i]=UNUSED;
	q.push(src);
	path[src]=START;
	while(!q.empty()) {
		item=q.front();
		q.pop();


		if(item==dest) {
			/* crawl back through the path to find min cost */
			i=dest;
			cf=INT_MAX;
			while(path[i]!=START) {
				if(cf>cap[path[i]][i]) cf=cap[path[i]][i];

				i=path[i];
			}
			return cf;
		}


		for(i=1;i<=node;i++) {
			if(cap[item][i]!=0 && path[i]==UNUSED) {
				q.push(i);
				path[i]=item;
			}
		}
	} // end of while loop
	return 0;
}

void computeCap(int node){
	for(int i = 0; i < node; i++) {
		for(int j = 0; j < node; j++) {
			cap[i][j] = originalcap[i][j] - flow[i][j] + flow[j][i];
		}
	}
}

int maxflow(int node) {
	int i,cf,totalflow=0;
	while(true) {
		cf = BFS(node);
		if (cf == 0) break;
		

		totalflow+=cf;
		i=dest;

		while(path[i]!=START) {
			flow[path[i]][i]+=cf;

			if(flow[path[i]][i] > 0 && flow[i][path[i]] > 0) {
				cout << "in here " << endl;
				if(flow[path[i]][i] > flow[i][path[i]]) {
					flow[path[i]][i] -= flow[i][path[i]];
					flow[i][path[i]] = 0;
				} else {
					flow[i][path[i]] -= flow[path[i]][i];
					flow[path[i]][i] = 0;
				}
			}

			i=path[i];
		}

		computeCap(node);
	}


	return totalflow;
}

void graph_initial(int node){
	int i,j;
	for(i=1;i<=node;i++){
		for(j=1;j<=node;j++) {
			originalcap[i][j]=0;
			cap[i][j]=0;
			flow[i][j]=0;
		}
	}

}


int main()
{
	ifstream inFile("input2.txt");
	ofstream outFile1("output2.txt");

	//freopen("out.txt","wt",stdout);

	int node,edge,a,b,c,resultedFlow;

	inFile >> src >> dest >> node >> edge;

	graph_initial(node);

	for(int i = 0; i < edge; i++) {
		inFile >> a >> b >> c;
		originalcap[a][b]=c;
	}

	computeCap(node);

	inFile.close();
	
	resultedFlow=maxflow(node);

	outFile1 << "  |\t" << 0 << "\t";
	for (int i = 1; i < node; i++) outFile1 << i << "\t";
	outFile1 << endl << " ---------------------------------------------" << endl;

	for (int i = 0; i < node; i++) {
		outFile1 << i << " |\t";
		for(int j = 0; j < node; j++) {
			outFile1 << flow[i][j] << "\t";
		}
		outFile1 << endl;
	}

	outFile1 << endl << "maxFlow: " << resultedFlow << endl;
	
	outFile1.close();

	cout << "finished" << endl;
	 int blah;
	 cin >> blah;
	 return 0;
// End of main function........
return 0;
}
