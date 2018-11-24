#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin ("bellmanford.in");
std::ofstream fout ("bellmanford.out");

const int NMAX = 50001;
const int MMAX = 250000;
const int INF = (1<<30);

int N; int M; int dist[NMAX];

std::vector< std::pair<int, int> > G[NMAX];

void read() {

	fin >> N >> M;

	int x; int y; int cost; 

	for(int i = 0 ;i < M; ++i) {

		fin >> x >> y >> cost;

		G[x].push_back(std::make_pair(y, cost));

	}

}

bool BellmanFord(int start) {

	//optimizare:
	//Daca costul unui nod nu a fost imbunatait nu are rost sa mai luam muchiile care pleaca din el(nu pot imbunatai nimic)
	//Tinem o lista cu nodurile care au fost imbunataite la fiecare pas

	std::queue <int> Q; 
	int countQ[NMAX]; //numaram de cate ori un nod a fost bagat in coada, adica de cate ori a a imbunatatit un drum >= N => ciclu

	for(int i = 1; i <= N; ++i) 
		dist[i] = INF, countQ[i] = 0;
	

	Q.push(start);
	countQ[start] = 1;

	dist[start] = 0;

	while(!Q.empty()) {

		int j = Q.front();
		Q.pop();


		for(unsigned k = 0 ; k < G[j].size(); ++k) {
			//imbunatatim ceva daca se poate

			int node = G[j][k].first;
			int cost = G[j][k].second;

			if(dist[node] > dist[j] + cost) {

				dist[node] = dist[j] + cost;
				countQ[node]++;

				if(countQ[node] > N)
					return false; //ciclu negativ
				Q.push(node);
			}
				

		}
	}
	
	return true;

}

int main() {

	read();

	if(BellmanFord(1)) 
		for(int i = 2; i <= N; ++i)
			fout << dist[i] << " ";
	else fout << "Ciclu negativ!" << '\n';

	return 0;
}

//complexitate: O(V * (logV + E)), simplificat pentru grafuri conexe: O(E * log V)
//Dijkstra nu merge pt muchii negative pentru ca nu se repsecta propietatea de minim, intodeauna la un nod s.ar putea sa se ajunga prin altfel 
//cu un cost mai mic folosind o muchie negativa