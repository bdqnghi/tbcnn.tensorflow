/*O(V * E), se o grafo estiver armazenado em listas de adjacência*/
#include <bits/stdc++.h>

const int MAX = 1010;
const int INF = (int)1e8;

using namespace std;

typedef pair<int, int> ii;

vector <ii> adj[MAX];
int dist[MAX];

void bellman_ford(int s, int V){
    for(int i = 0; i < V; i++) dist[i] = INF;
    dist[s] = 0;
    
    //O fato de realizarmos a checagem V - 1 ocorre porquê um caminho em um grafo partindo de um vértice com destino em outro
    //terá no máximo V - 1 vértices
    for(int k = 0; k < V - 1; k++){
		for(int i = 0; i < V; i++){
			for(int j = 0; j < (int)adj[i].size(); j++){
				ii aux = adj[i][j];
				dist[aux.first] = min(dist[aux.first], dist[i] + aux.second);
			}
		}
	}
}

/*Após executar o algoritmo de bellman-ford, podemos verificar se há um ciclo negativo no grafo da seguinte maneira*/
bool negativeCycle(int V){
	for(int i = 0; i < V; i++){
		for(int j = 0; j < (int)adj[i].size(); j++){
			ii aux = adj[i][j];
			//Sim, isso é possível, e é exatamente o que garante a existência de um ciclo negativo no grafo
			if(dist[aux.first] > dist[i] + aux.second) return true;
		}
	}
	return false;
}

int main(){
    return 0;
}
