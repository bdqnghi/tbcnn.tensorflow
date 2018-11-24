#include<bits/stdc++.h>
#define REP(i,a,b) for (int i = (a); i <= (b); i++)
#define pb push_back
namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi pset(1000);

void initSet(int N){
	REP(i,0,N)
		pset[i] = i;
}

int findSet(int i){
	return (pset[i] == i) ? i : pset[i] = findSet(pset[i]);
}

void unionSet(int i, int j){
	pset[findSet(i)] = findSet(j);
}

int isSameSet(int i, int j){
	return findSet(i) == findSet(j);
}

vector< pair<int, ii> > EdgeList;

int main(){

 return 0;
}


