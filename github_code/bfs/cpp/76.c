#include "../../include/graph_search.hpp"

void breadth_first_traverse(const unordered_map<int, vector<int>> adjList, int root, unordered_map<int, bool>& visited){
     /*
        perform BPS using queue tracker.
    */
    if(root == -1) cerr<<"The root node does not exist !"<<endl;

    cout<<"Breadth-First-Search"<<endl;
    queue<int> nodeQueue;
    int outdegree = 0;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
         // pop the top of the stack
        int cur_node = nodeQueue.front();
        visited[cur_node] = true;
        cout<<"Node "<<cur_node<<" visited"<<endl;
        nodeQueue.pop();
        vector<int> targetList = adjList.at(cur_node);
        outdegree = targetList.size();
        // push all non-visited children into the stack
        if(outdegree == 0) continue;
        for(auto target: targetList){
            if (visited[target] == false)
                nodeQueue.push(target);
        }
    }
    cout<<"Finishing traversing. "<<endl;
}

bool breadth_first_search(const unordered_map<int, vector<int>> adjList, int root, int target, unordered_map<int, bool>& visited){
     /*
        perform BFS using layer-wise queue tracking
    */
    if(root == -1) cerr<<"The root node does not exist !"<<endl;

    cout<<"Breadth-First-Search"<<endl;
    queue<int> nodeQueue;
    int outdegree = 0;
    bool result = false;
    int cur_node;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
         // pop the top of the stack
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
        // push all non-visited children into the stack
        if(outdegree == 0) continue;
        for(auto target: targetList){
            if (visited[target] == false)
                nodeQueue.push(target);
        }
    }
    return result;
}



//=========================================================
//void breadth_first_traverse(vector<vector<int>> adjList, int root, vector<bool>& visited, unorderied_map<int, int>& nodeIdxMap){
//    /*
//        The adjacent list is a vector of vectors, with each row being [source target1, target2, ... ]
//        visited[i], indicates if the node (vector index i) is visited
//        nodeIdxMap[nodeIdx][vectorIdx] is the map between the graph node index and the vector index i 
//    */
//    if(adjList.empty()) cerr<<"The input graph is empty !"<<endl;
//    int n = adjList.size();
//    int rootIdx = -1;
//    if(~ visited.empty()) visited.clear();
//    visited.assign(n, false);
//
//    if(~ nodeIdxMap.empty()) nodeIdxMap.clear();
//
//    for (int i=0; i<n; i++){
//         nodeIdxMap[adjList[i][0]] = i;
//         if(adjList[i][0] == root)
//             rootIdx = i;
//    }
//
//    if(rootIdx == -1) cerr<<"The root node does not exist !"<<endl;
//
//    cout<<"Breadth-First-Search"<<endl;
//    queue<int> nodeQueue;
//    int nodeIdx = -1;
//    int outdegree = 0;
//    int childIdx = -1;
//
//    while(rootIdx != -1){
//       nodeQueue.push(rootIdx);
//       while(~nodeQueue.empty()){
//           // pop the front of the queue
//           nodeIdx = nodeQueue.front();
//           visited[nodeIdx] = true;
//           cout<<"Node "<<adjList[nodeIdx][0]<<" visited"<<endl;
//           nodeQueue.pop();
//           outdegree = adjList[nodeIdx].size();
//           // add all non-visited children into the queue
//           for(int j=1; j< outdegree; j++){
//               childIdx = nodeIdxMap[adjList[nodeIdx][j]];
//               if (visited[childIdx] == false)
//                  nodeQueue.push(childIdx);
//           }
//       }
//       rootIdx = -1;
//       for(int i=0; i<n; i++){
//          if(visited[i] == false)
//              rootIdx = i;
//       }
//       if(~nodeQueue.empty()) nodeQueue.clear();
//    }
//
//    cout<<"End of BFS search."<<endl;
//
//}
//
//
//bool breadth_first_search(vector<vector<int>> adjList, int root, int target, vector<bool>& visited,  unordered_map<int, int>& nodeIdxMap){
//    /*
//        The adjacent list is a vector of vectors, with each row being [source target1, target2, ... ]
//        visited[i], indicates if the node (vector index i) is visited
//        nodeIdxMap[nodeIdx][vectorIdx] is the map between the graph node index and the vector index i 
//    */
//    if(adjList.empty()) cerr<<"The input graph is empty !"<<endl;
//    if(root == target) return true;
//    bool result = false;
//    int n = adjList.size();
//    int rootIdx = -1;
//    if(~ visited.empty()) visited.clear();
//    visited.assign(n, false);
//
//    if(~ nodeIdxMap.empty()) nodeIdxMap.clear();
//
//    for (int i=0; i<n; i++){
//         nodeIdxMap[adjList[i][0]] = i;
//         if(adjList[i][0] == root)
//             rootIdx = i;
//    }
//
//    if(rootIdx == -1) cerr<<"The root node does not exist !"<<endl;
//
//    cout<<"Breadth-First-Search"<<endl;
//    queue<int> nodeQueue;
//    int nodeIdx = -1;
//    int outdegree = 0;
//    int childIdx = -1;
//    while(rootIdx != -1){
//       nodeQueue.push(rootIdx);
//       while(~nodeQueue.empty()){
//           // pop the front of the queue
//           nodeIdx = nodeQueue.front();
//           visited[nodeIdx] = true;
//           cout<<"Node "<<adjList[nodeIdx][0]<<" visited"<<endl;
//           nodeQueue.pop();
//           if(adjList[nodeIdx][0] == target){
//                result = true;
//                break;
//           }
//           outdegree = adjList[nodeIdx].size();
//           // add all non-visited children into the queue
//           for(int j=1; j< outdegree; j++){
//               childIdx = nodeIdxMap[adjList[nodeIdx][j]];
//               if (visited[childIdx] == false)
//                  nodeQueue.push(childIdx);
//           }
//       }
//       if(result == true) break;
//       rootIdx = -1;
//       for(int i=0; i<n; i++){
//          if(visited[i] == false)
//              rootIdx = i;
//       }
//       if(~nodeQueue.empty()) nodeQueue.clear();
//    }
//    cout<<"End of BFS search."<<endl;
//    return result;
//}
//
//
