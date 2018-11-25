#include "ford_fulkerson.hh"

FordFulkerson::FordFulkerson(){}

FordFulkerson::FordFulkerson(const vector<vector<int> > &C, const vector<vector<int> > &E){
	this->C = C;
	this->E = E;
	this->k = C[0].size();
    this->n = C[0].size();
}

bool FordFulkerson::is_path(int _s, int _t)
    {
        if(_s == _t) return true;
        if(visited[_s]) return false;
        visited[_s] = true;
        for(int i = 0; i < E[_s].size(); i++){
            int v = E[_s][i];
            if(C[_s][v] - F[_s][v] > 0 && is_path(v, _t))
            {
                F[_s][v]++;
                F[v][_s]--;
                return true;
            }
        }
            
        return false;
    }

pair<int, vector<vector<int> > > FordFulkerson::max_flow(){
    int f = 0;
    F = vector<vector<int> > (n, vector<int>(n, 0));
    C[S][s] = C[t][T] = C[s][t] = k;
    visited = vector<bool> (n, false);

    while(is_path(S, T)){
        ++f;
        visited = vector<bool>(n, false);
    }

    
    return make_pair(k-F[s][t], F);
}

    

   
    

