

#define SIZE 6
using namespace std;

double residualNetwork[][]=null;
double flowNetwork[][]=null;
int parent[SIZE];

double[][SIZE] residualNetwork(double c[][], double f[][]){
    double r[][] = new double[SIZE][SIZE];
    for(int xindex = 0; xindex < SIZE; xindex++){
        for(int yindex = 0; yindex < SIZE; yindex++)
            r[xindex][yindex] = c[xindex][yindex] - f[xindex][yindex];
    }
}

double augmentPath(double graph[][SIZE], int sp, int tp){
    double maxflow = INF;
    memset(parent, -1, sizeof(parent));
    queue<int> myqueue;
    myqueue.push(sp);

    while(!myqueue.empty()){
        int p = myqueue
    }

}

double edmondsKarpMaxFlow(double graph[][SIZE], int sp, int tp){
    double f[][] = new double[SIZE][SIZE];
    for(int xindex = 0; xindex < SIZE; xindex++){
        for(int yindex = 0; yindex < SIZE; yindex++)
            f[xindex][yindex] = 0;
    }

    double r[][] = residualNetwork(graph, f);
    double result = augmentPath(r, s, t);

    double sum = 0;
    while(result != -1){
        int cur = t;
        while(cur != s){
            f[parent[cur]][cur] += result;
            f[cur][parent[cur]] = -f[parent[cur]][cur];
            r[parent[cur]][cur] -= result;
            r[cur][parent[cur]] += result;
            cur = parent[cur];
        }

        sum += result;
        result = augmentPath(r, s, t);
    }

    residualNetwork = r;
    flowNetwork = f;

    return sum;
}

/*int main(){
    double graph[SIZE][SIZE] = {{0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}};
    cout << edmondsKarpMaxFlow(graph, 0, 5) << endl;
    return 0;
}*/
