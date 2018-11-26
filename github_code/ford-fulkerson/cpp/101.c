#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Ford-Fulkerson algorithm for finding the maximum flow
// in the Edmonds-Karp variant.
// Runs in O(|V|.|E|^2) in general case.
// O(|V|.|E|) in case capacities are only 0 or 1.

/*pdf*/
// Input: A symmetric oriented graph on the vertices {0,...,N-1} with M edges.
// Multiedges are allowed.
// C[i][0] gives the capacity of oriented edge E[i][0] -> E[i][1]
// C[i][1] gives the capacity of oriented edge E[i][1] -> E[i][0]
// s is a source vertex, t is a target vertex.
// Returns field F, F[i][0] is flow in the edge E[i][0] -> E[i][1], F[i][1] is the flow in
// the opposite edge. Size of the flow is stored in F_size.
int ** ford_fulkerson(int N, int M, int E[][2], int C[][2], int s, int t, int * F_size) {
	int ** F = new int * [M];
	int ** R = new int * [M];
	for (int i = 0; i < M; i++) { F[i] = new int [2]; R[i] = new int [2]; }
	int * from = new int [N];

	vector<int> * Ne = new vector<int> [N];
	for (int i = 0; i < M; i++) {
		Ne[E[i][0]].push_back(i); Ne[E[i][1]].push_back(i); }

	// In each step, we try to find an augmenting path with BFS
	do {
		found:
		for (int i = 0; i < N; i++)
			from[i] = -1;
		
		// Construct a residual network
		for (int i = 0; i < M; i++) {
			R[i][0] = C[i][0] - F[i][0] + F[i][1];
			R[i][1] = C[i][1] - F[i][1] + F[i][0];
		}
		queue<int> Q;
		Q.push(s);
		from[s] = 1<<30;

		while (!Q.empty()) {
			int v = Q.front(); Q.pop();
			for (int i = 0; i < (int)Ne[v].size(); i++) {
				int e = Ne[v][i]; // e = (v,w)
				bool o = E[e][1] == v;
				int w = E[e][1-o];
				int r = R[e][o];

				if (r > 0 && from[w] == -1) {
					from[w] = e;
					Q.push(w);
				}
				if (r > 0 && w == t) {
					// Augmenting path found, the flow will be increased
					int delta = 1<<30;
					vector<int> edg, ori;
					int p = t;
					int f = e;
					while (p != s) {
						int ot = p != E[f][1];
						edg.push_back(f);
						ori.push_back(ot);
						delta = min(delta, R[f][ot]);
						p = E[f][ot];
						f = from[p];
					}
					for (int i = (int)edg.size() - 1; i >= 0; i--) {
						f = edg[i]; int ot = ori[i];
						int d = delta - (C[f][ot] -  F[f][ot]);
						F[f][ot] += min(delta, C[f][ot] - F[f][ot]);
						if (d >= 0) F[f][1-ot] -= d;
					}
					goto found;
				}
			}
		}
	} while (false);

	*F_size = 0;
	for (int i = 0; i < (int)Ne[s].size(); i++) {
		if (s == E[i][0]) *F_size += F[i][0] - F[i][1];
		else			  *F_size += F[i][1] - F[i][0];
	}

	for (int i = 0; i < M; i++) delete R[i];
	delete [] R;
	delete [] from;
	return F;
}
/*pdf*/

void ford_fulkerson_demo() {
	int N1 = 4, M1 = 5;
	int E1[5][2] = { {0, 1},  {0, 2}, {1, 2}, {1, 3}, {2, 3}};
	int C1[5][2] = { {500, 0}, {400, 0},  {1, 0}, {200, 0},  {300, 0} };
	int s1 = 0, t1 = 3;
	int F1size;
	int ** F1 = ford_fulkerson(N1, M1, E1, C1, s1, t1, &F1size);
	printf("Max flow size: %d\n", F1size);
	for (int i = 0; i < M1; i++) {
		printf("Edge e = %d -> %d, c(e) = %d, f(e) = %d\n", E1[i][0], E1[i][1], C1[i][0],
		F1[i][0]);
		printf("Edge e = %d -> %d, c(e) = %d, f(e) = %d\n", E1[i][1], E1[i][0], C1[i][1],
		F1[i][1]);
	}
}

#ifdef RUNDEMO
int main() { ford_fulkerson_demo(); return 0; }
#endif
