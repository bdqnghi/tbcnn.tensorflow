package Graph;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Stack;

/**
 * Created by Shivangi on 5/28/2017.
 */
public class TopologicalSort {

    int V;
    LinkedList<Integer> adj[];

    TopologicalSort(int V){
        this.V = V;
        adj = new LinkedList[V];
        for(int i=0; i<V; i++)
            adj[i] = new LinkedList();
    }

    public void addEdges(int v, int w){
        adj[v].add(w);
    }

    public void topologicalSort(){
        Stack stack = new Stack();

        boolean visited[] = new boolean[V]; //default value is false

        for(int i=0; i<V; i++){
            if(!visited[i])
                topologicalSort(i,stack, visited);
        }

        while (!stack.isEmpty())
            System.out.print(stack.pop() + "  ");

        System.out.println();
    }

    public void topologicalSort(int v, Stack stack, boolean visited[]){
        visited[v] = true;

        Iterator<Integer> it = adj[v].iterator();
        while (it.hasNext()){
            Integer i = it.next();
            if(!visited[i])
                topologicalSort(i,stack,visited);
        }

        stack.push(new Integer(v));
    }

    public static void main(String args[]){
        TopologicalSort graph = new TopologicalSort(6);

        graph.addEdges(5,2);
        graph.addEdges(5,0);
        graph.addEdges(4,0);
        graph.addEdges(4,1);
        graph.addEdges(2,3);
        graph.addEdges(3,1);

        graph.topologicalSort();
    }
}
