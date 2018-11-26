/*************************************************************************
> File Name: kruskals_minimum_spanning_tree.cpp
> Author: yoghourt->ilvcr 
> Mail: liyaoliu@foxmail.com  @@  ilvcr@outlook.com 
> Created Time: 2018年07月24日 星期二 15时26分42秒
> Description: 
 ************************************************************************/

#include<iostream>
using namespace std;


#define V 6
#define INFINITY 99999

int graph[V][V] = {
    {0, 4, 1, 4, INFINITY, INFINITY},
    {4, 0, 3, 8, 3, INFINITY},
    {1, 3, 0, INFINITY, 1, INFINITY},
    {4, 8, INFINITY, 0, 5, 7},
    {INFINITY, 3, 1, 5, 0, INFINITY},
    {INFINITY, INFINITY, INFINITY, 8, INFINITY, 0}
};

void findMinimumEdge(){
    for(int i=0; i < V; i++){
        int min = INFINITY;
        int minIndex = 0;
        for(int j=0; j < V; j++){
            if(graph[i][j] != 0 && graph[i][j] < min){
                min = graph[i][j];
                minIndex = j;
            }
        }
        cout << "  -  " << minIndex << "\t" << graph[i][minIndex] << "\n";
    }
}


int main(int argc, char* argv[]){

    findMinimumEdge();
    return 0;
}



