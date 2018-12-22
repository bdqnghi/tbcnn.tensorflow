/*****************************************************************
Breadth First Search algorithm
Written by: Aadish Joshi

Learned about :-
LinkedList operations. 
1) list.poll() to delete from head;
2) list.size() for checking the size
Iterator.
Iterator<Integer> = linkedList.listIterator()
Iterator.hasNext().
*****************************************************************/
import java.util.*;
import java.io.*;

class Graph{
	int V;
	LinkedList<Integer> adj[];

	Graph(int v){
		this.V = v;
		adj = new LinkedList[v];
		for(int i=0;i<v;i++){
			this.adj[i] = new LinkedList();
		}
	}

	void addEdge(int v,int w){
		this.adj[v].add(w);
	}
}

class breadthFirstSearch{
	static Graph g; 
	static void bfs(int s){
		boolean visited[] = new boolean[g.V];
		LinkedList<Integer> queue = new LinkedList<Integer>();

		visited[s] = true;
		queue.add(s);

		while(queue.size() !=0){
			s = queue.poll();
			System.out.print(" "+s);

			Iterator<Integer> i = g.adj[s].listIterator();
			while(i.hasNext()){
				int n = i.next();
				if(!visited[n]){
					visited[n] = true;
					queue.add(n);
				}
			}
		}
	}

	public static void main(String args[]){
		g = new Graph(4);
		g.addEdge(0, 1); 
        g.addEdge(0, 2); 
        g.addEdge(1, 2); 
        g.addEdge(2, 0); 
        g.addEdge(2, 3); 
        g.addEdge(3, 3); 
  
        System.out.println("Following is Breadth First Traversal "+ 
                           "(starting from vertex 2)"); 
  
        bfs(2); 
	}

}