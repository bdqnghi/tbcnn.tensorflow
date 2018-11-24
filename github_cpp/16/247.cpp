//https://practice.geeksforgeeks.org/problems/topological-sort/1

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

void dfs(vector<int> graph[],int cur,vector<bool> &visited,stack<int> &st)
{
    visited[cur] = true;
    
    for(auto it=graph[cur].begin();it!=graph[cur].end();it++)
      if(!visited[*it])
        dfs(graph,*it,visited,st);
        
    st.push(cur);
}


/* You need to complete this function */
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