#include<bits/stdc++.h>
using namespace std;
vector<int> graph[10001];


void dfs(int i,bool visited[], vector<int> v[10001], stack<int>& st){
	visited[i]=true;
	vector<int>::iterator it;
	for(it=v[i].begin();it!=v[i].end();it++)
		if(!visited[*it])
			dfs(*it,visited,v,st);
		
	st.push(i);
}


int * topoSort(vector<int> graph[], int N)
{
   // Your code here
   bool *visited=new bool[N];
   for(int i=0;i<N;i++)
    	visited[i]=false;
    
    int *arr=new int[N];
    stack<int> st;
    for(int i=0;i<N;i++){
		if(!visited[i]){
			dfs(i,visited,graph,st);
		}
	}
	
	int temp=0;
	while(!st.empty()){
		int n=st.top();
		st.pop();
		arr[temp]=n;
		temp++;
	}
	int *ptr=arr;
	return ptr;
}




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


