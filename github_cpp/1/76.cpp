#include "../../include/graph_search.hpp"

void breadth_first_traverse(const unordered_map<int, vector<int>> adjList, int root, unordered_map<int, bool>& visited){
     
    if(root == -1) cerr<<"The root node does not exist !"<<endl;

    cout<<"Breadth-First-Search"<<endl;
    queue<int> nodeQueue;
    int outdegree = 0;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
         
        int cur_node = nodeQueue.front();
        visited[cur_node] = true;
        cout<<"Node "<<cur_node<<" visited"<<endl;
        nodeQueue.pop();
        vector<int> targetList = adjList.at(cur_node);
        outdegree = targetList.size();
        
        if(outdegree == 0) continue;
        for(auto target: targetList){
            if (visited[target] == false)
                nodeQueue.push(target);
        }
    }
    cout<<"Finishing traversing. "<<endl;
}

bool breadth_first_search(const unordered_map<int, vector<int>> adjList, int root, int target, unordered_map<int, bool>& visited){
     
    if(root == -1) cerr<<"The root node does not exist !"<<endl;

    cout<<"Breadth-First-Search"<<endl;
    queue<int> nodeQueue;
    int outdegree = 0;
    bool result = false;
    int cur_node;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
         
        cur_node = nodeQueue.front();
        visited[cur_node] = true;
        cout<<"Node "<<cur_node<<" visited"<<endl;
        nodeQueue.pop();
        if(cur_node == target){
            result = true;
            break;
        }
        vector<int> targetList = adjList.at(cur_node);
        outdegree = targetList.size();
        
        if(outdegree == 0) continue;
        for(auto target: targetList){
            if (visited[target] == false)
                nodeQueue.push(target);
        }
    }
    return result;
}



























































































































