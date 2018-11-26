#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

queue<int> q;

//displaying the graph as adjacency list.
void display(vector<list<int> > &v){
    for(unsigned int i = 0; i < v.size(); i++){
        cout<<i + 1<<" -> ";
        list<int>::iterator it;
        for(it = v[i].begin(); it != v[i].end(); it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    return;
}

//For breadth-first-search we print all the vertex of graph "level-by-level".
//By picking the source vertex and printing it, we then print all the adjacent vertex of source vertex(level),
//and keep repeating till we discovered the entire graph.
void bfs(vector<list<int> > &v,vector<int> &visited, int start){

    q.push(start);
    while(!q.empty()){
        int index = q.front();
        cout<<index<<" ";
        visited[index - 1] = 1;
        list<int>::iterator it = v[index - 1].begin();
        for(; it != v[index - 1].end(); it++){
            if(!visited[*it - 1]){
                q.push(*it);
                visited[*it - 1] = 1;
            }
        }
        q.pop();
    }
    fill(visited.begin(),visited.end(),0);
    cout<<endl;
    return;
}

int main(){
    unsigned int n = 0;int data = 0;
    cout<<"ENTER THE NO. OF VERTICES :-\n";
    cin>>n;
    vector<list<int> > v(n);
    vector<int> visited(n,0);
    for(unsigned int i = 0; i < n; i++){
        cout<<"ENTER THE VERTICES ADJACENT TO "<<i + 1<<endl;
        while(1){
            cout<<"DATA ADJACENT TO "<<i + 1<<" (-1 TO EXIT) ";
            cin>>data;
            if(data == -1)
                break;
            v[i].push_back(data);
        }
    }
    cout<<"DISPLAY :\n";
    display(v);
    cout<<"BFS :-\n";
    bfs(v, visited, 1);
    return 0;
}
