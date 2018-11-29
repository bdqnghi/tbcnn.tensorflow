import java.util.*;
class Graph{
  int V;
  LinkedList<Integer>[] adj;
  Graph(int V){
    this.V=V;
    adj = new LinkedList[V];
    for(int i=0; i<V; i++)
      adj[i] = new LinkedList<Integer>();
  }
  void addEdge(int v, int w){
    adj[v].add(w);
  }
  void topologicalSort(){
    Stack<Integer> stack = new Stack<Integer>();
    boolean[] visited = new boolean[V];
    for(int i=0; i<V; i++)
      if(!visited[i])
        topologicalSortUtil(i,visited,stack);

    while(!stack.empty()){
      int n = stack.pop();
      System.out.print(n+" ");
    }
  }

  void topologicalSortUtil(int v,boolean[] visited, Stack stack){
    //System.out.print(v+" ");
    visited[v]=true;
    Iterator<Integer> iterator = adj[v].iterator();
    while(iterator.hasNext()){
      int n = iterator.next();
      if(!visited[n]){
        topologicalSortUtil(n,visited,stack);
      }
    }
    stack.push(new Integer(v));
  }
}

class topologicalsort{
  public static void main(String[] args) {
    Graph g = new Graph(6);
       g.addEdge(5, 2);
       g.addEdge(5, 0);
       g.addEdge(4, 0);
       g.addEdge(4, 1);
       g.addEdge(2, 3);
       g.addEdge(3, 1);
    g.topologicalSort();
  }
}
