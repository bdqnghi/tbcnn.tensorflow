#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unordered_map>

using namespace std;

void dfs(vector< vector<int> > &list, vector<int> &visited, int node)
{
    visited.at(node) = 1;
    cout << node << endl;

    for(int i=0; i<list.at(node).size(); i++)
    {
        if (visited[list.at(node).at(i)] == 0)
        {
            dfs(list, visited, list.at(node).at(i));
        }
    }

}


int main()
{
    
    
    
    vector< vector<int> > list(10);
    list.at(1).push_back(2);
    

    list.at(1).push_back(4);
    

    list.at(2).push_back(3);
    

    list.at(3).push_back(5);
    list.at(3).push_back(6);
    list.at(6).push_back(7);
    vector<int> visited(10);
    dfs(list, visited, 1);
}
