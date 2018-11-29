import java.util.*;

public class DepthFirstSearch{
    public static void mainDFS(Graph g, int startVertex, HashMap<Integer, Boolean> isExplored){
        LinkedList<Integer> edges = g.getEdges(startVertex);
        for (int edge: edges){
            if (!isExplored.get(edge)){
                isExplored.put(edge, true);
                mainDFS(g, edge, isExplored);
            }
        }
    }


    public static void main(String[] args){

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
