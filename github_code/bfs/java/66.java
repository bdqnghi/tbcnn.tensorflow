import java.util.*;

public class BreadthFirstSearch{
    public static void mainBFS(Graph g, int[] nodes, int startVertex){
        HashMap<Integer, Boolean> isExplored = new HashMap<Integer, Boolean>();
        for (int i: nodes){
            isExplored.put(i, false);
        }

        isExplored.put(startVertex,true);

        Queue<Integer> q = new Queue<Integer>();
        q.add(startVertex);

        if (q.poll()!=null){
            int v = q.remove();
            LinkedList<Integer> edges = graph.getEdges(v);
            for (int i=0; i<edges.size(); i++){
                int edge = edges.get(i);
                if (!isExplored.get(edge)){
                    isExplored.put(edge,true);
                    q.add(edge);
                }
            }
        }
    }

    //applications: shortest path (with unit lengths)
    //undirected connectivity: segmented parts of graph

    public static void main(String[] args){
        int[] nodes = {1,2,3,4,5};
        Graph g = new Graph(nodes);
        g.addEdge(1,2);
        g.addEdge(1,3);
        g.addEdge(2,4);
        g.addEdge(3,4);
        g.addEdge(3,5);
    }
}

class Graph{
    HashMap<Integer, LinkedList<Integer>> adjacencyList;

    public Graph(int[] nodes){
        adjacencyList = new HashMap<Integer,LinkedList<Integer>>();
        for (int i: nodes){
            adjacencyList.put(i, new LinkedList<Integer>());
        }
    }

    public void addEdge(int v1, int v2){
        adjacencyList.get(v1).add(v2);
    }

    public List<Integer> getEdges(int v1){
        return adjacencyList.get(v1);
    }
}
