#include <iostream>
#include <cstring>

using namespace std;

/*
    PRIM's algorithm
    --start from a vertex
    1.find smallest cost to next vertex, and add that vertex
    1.1 mark the vertex as true
    2.update the cost values, according to new vertex
*/
/**
    Finds the MST, and stores it in an array so that a[n] is connected to a[n+1]
    @param n -- size of tree
    @param costs[][] -- the costs
    @param result[] -- the array to hold the results
*/
void prim(size_t n, int** costs, int* result) {
    bool flag[n];// = new int[n];     //is this vertex in the tree
    int lowest[n];// = new int[n];    //cost of adding this vertex
    memset(flag,0,sizeof(flag));
    memset(lowest,0,sizeof(lowest));
    memset(result,0,sizeof(result));
    int cur = 0;                  //stores current index
    bool done = 0,cnt = 0;
    int m,mindex; // min
    memcpy(lowest,costs[cur],n);
    while (!done) {
        m=costs[cur][0]; mindex=0; //initialize the min
        result[cnt++]=cur;         //store the result
        flag[cur]=1;               //set the thing to be true
        done = 1;                  //set done = true
        for (size_t i = 1; i < n; i++) {
            if (!flag[i]) done=0;   //a value is still not added, so not done
            if (costs[cur][i]<m && !flag[i]) {
                mindex=i;
                m=costs[cur][i];
            }
        }
        if (done) break;
        cur=mindex;
        for (size_t i = 0; i < n; i++) {
            lowest[i]=(lowest[i]<costs[cur][i])?lowest[i]:costs[cur][i];
        }
    }
}


/* Kruskal's Algorithm
    --add edges until V-1 has been added (using disjoint set data structure)
    1. sort all the edges
    2. start from smallest edge; connect elements if they are not in the same set
    2.1 when connecting, make a union of the sets the vertices belong to
*/
void kruskal(size_t n, int** costs, int* result) {

}

int main(void) {

}
