#include <bits/stdc++.h>
using namespace std;



int t= 0;
pair<int,int> times[10];

void dfsSingle(int current, vector<vector<int> > graph, pair<int,int> times[],
		int seenVertices[], int explored[]){
	times[current].first = t;
	t++;
	for(int i=explored[current]+1; i<10; i++){
		if(graph[current][i]==1 && seenVertices[i]==0){
			seenVertices[i]=1;
			explored[current] = i;
			dfsSingle(i,graph,times,seenVertices, explored);
		}
	}
	times[current].second = t;
	t++;
	seenVertices[current] = 2;
}

void dfs(vector<vector<int> > graph, pair<int,int> times[], 
			int seenVertices[], int explored[]){
	for(int i=0; i<10; i++){
		if(seenVertices[i]==0){
			seenVertices[i] = 1;
			dfsSingle(i,graph,times,seenVertices, explored);			
		}
	}
}

bool compare(int a, int b){
	return times[a].second>times[b].second;
}

vector<vector<int> > reverseGraph(vector<vector<int> > graph){
	vector<vector<int> > out(10, vector<int>(10,0));
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(graph[i][j]==1){out[j][i]=1;}
		}
	}
	return out;
}

int main(){
	vector<vector<int> >graph(10, vector<int>(10,0));
	int seenVertices[10];
	memset(seenVertices, 0, sizeof(seenVertices));
	memset(times, -1, sizeof(times));
	int explored[10];
	memset(explored, -1, sizeof(explored));
	graph[1][2] = 1;
	graph[2][3] = 1;
	graph[3][4] = 1;
	graph[4][3] = 1;
	graph[5][1] = 1;
	graph[2][5] = 1;
	graph[2][6] = 1;
	graph[5][6] = 1;
	graph[6][7] = 1;
	graph[7][6] = 1;
	graph[7][8] = 1;
	graph[3][7] = 1;
	graph[4][8] = 1;
	graph[8][8] = 1;
	dfs(graph, times, seenVertices, explored);
	vector<int> topologicalSort;
	for(int i=0; i<10; i++){
		topologicalSort.push_back(i);
	}
	sort(topologicalSort.begin(), topologicalSort.end(), compare);
	for(int i=0; i<10; i++){
		cout<< topologicalSort[i]<<endl;
	}
	cout<<"DONE"<<endl;
	vector<vector<int> > rGraph = reverseGraph(graph);
	memset(explored, 0, sizeof(explored));
	memset(seenVertices,0, sizeof(seenVertices));
	int alreadyDone[10];
	memset(alreadyDone, 0, sizeof(alreadyDone));
	int count = 1;
	for(int i=0; i<10; i++){
		
		if(seenVertices[topologicalSort[i]]==0){
			seenVertices[topologicalSort[i]] = 1;
			dfsSingle(topologicalSort[i],rGraph,times,seenVertices, explored);	
		}
		for(int i=0; i<10; i++){
			if(seenVertices[i]==2 && alreadyDone[i]==0){
				alreadyDone[i] = 1;
				cout<<i<<" ";
			}
		}
		cout<<endl;
	}
}