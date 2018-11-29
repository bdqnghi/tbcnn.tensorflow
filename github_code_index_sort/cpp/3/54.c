#include<bits/stdc++.h>
using namespace std;
vector<int> graph[10001];
int * topoSort(vector<int> graph[],int N);
int main()
{
int T;
cin>>T;
while(T--)
{
    memset(graph,0,sizeof graph);
    int N,E;
    cin>>E>>N;
    for(int i=0;i<E;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
    }
    int *res = topoSort(graph,N);
    bool valid =true;
    for(int i=0;i<N;i++)
    {
        int n=graph[res[i]].size();
        for(int j=0;j<graph[res[i]].size();j++)
        {
            for(int k=i+1;k<N;k++)
            {
                if(res[k]==graph[res[i] ] [j] )
                    n--;
            }
        }
        if(n!=0)
        {
            valid =false;
            break;
        }
    }
    if(valid==false)
        cout<<0<<endl;
    else
        cout<<1<<endl;
}
}
/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* You need to complete this function */
inline void dfs(vector<int> graph[],bool visited[],int node,int N,stack<int> &st){
    if(!visited[node]){
        visited[node]=true;
        for(int i=0;i<graph[node].size();i++){
            if(!visited[graph[node][i]])
                dfs(graph,visited,graph[node][i],N,st);
        }
        st.push(node);
    }
}
int * topoSort(vector<int> graph[], int N)
{
   // Your code here
    stack<int> st;
    bool visited[N]={false};
    for(int i=0;i<N;i++){
        dfs(graph,visited,i,N,st);
    }
    int *arr=(int*)calloc(N,sizeof(int));
    for(int i=0;i<N&&!st.empty();i++){
        arr[i]=st.top();
        st.pop();
    }
    /*for(int i=0;i<N;i++)
    	cout<<arr[i]<<" ";
    cout<<endl;*/
    return arr;
}