package Graph;

import java.util.Iterator;
import java.util.LinkedList;

import java.util.ArrayList;
import java.util.Stack;

/**
 * Created by shailendralohia on 1/31/18.
 */
public class TopologicalSort {
    private int vertex;
    private LinkedList<Integer> adj[];

    public TopologicalSort(int v) {
        vertex = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; i++) {
            adj[i] = new LinkedList<>();
        }
    }
    void addEdge(int v, int e) {
        adj[v].add(e);
    }

    public static void main(String[] args) {
        TopologicalSort topologicalSort=new TopologicalSort(6);
        topologicalSort.addEdge(5,2);
        topologicalSort.addEdge(5,0);
        topologicalSort.addEdge(4,0);
        topologicalSort.addEdge(4,1);
        topologicalSort.addEdge(2,3);
        topologicalSort.addEdge(3,1);

        topologicalSort.topologicalSort();
    }

    public  void topologicalSort() {
        Stack stack=new Stack();
        boolean visited[]=new boolean[vertex];
        for(int i=0;i<vertex;i++) {
            visited[i]=false;
        }
        for(int j=0;j<vertex;j++) {
            if(visited[j]==false) {
                topologicalSortUtil(visited,stack,j);
            }
        }
        while(stack.empty()==false) {
            System.out.println(stack.pop() + " ");
        }
    }

    public void topologicalSortUtil(boolean[] visited, Stack stack,int vertexData) {
        //if (!visited[vertexData]) {
            visited[vertexData] = true;
            //Integer nextData;
           // System.out.println("adj[vertexData]: " + adj[vertexData]);
            Iterator<Integer> iterator = adj[vertexData].iterator();
            while (iterator.hasNext()) {
                //System.out.println(iterator.next());
                int nextData = iterator.next();
                //System.out.println("nextData: " + nextData);
                if (!visited[nextData]) {
                    topologicalSortUtil(visited, stack, nextData);
                }
                //System.out.println("vertexData:" + vertexData);

            }
            stack.push(vertexData);
        //}
    }

}
