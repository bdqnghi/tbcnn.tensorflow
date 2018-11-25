



void dfs(vector<int> graph[],int cur,vector<bool> &visited,stack<int> &st)
{
    visited[cur] = true;
    
    for(auto it=graph[cur].begin();it!=graph[cur].end();it++)
      if(!visited[*it])
        dfs(graph,*it,visited,st);
        
    st.push(cur);
}



int * topoSort(vector<int> graph[], int N)
{
   stack<int> st;
   vector<bool> visited(N,false);
   
   for(int i=0;i<N;i++)
      if(!visited[i])
         dfs(graph,i,visited,st);
   
   
   int* arr=(int*)malloc(sizeof(int)*N);
   
   for(int i=0;i<N;i++,st.pop())
       arr[i] = st.top();
       
    return arr;
}