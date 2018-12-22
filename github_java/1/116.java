package GraphDS;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by divya on 11/4/17.
 */
public class BreadthFirstSearch {

    private Graph<Integer> graph;

    BreadthFirstSearch(Graph<Integer> graph){
        this.graph = graph;
    }

    void getBfsRoute(int sourceRoot){

        boolean[] visited = new boolean[graph.getAllVertex().size()];

        Queue<Vertex<Integer>> queue = new LinkedList<>();

        queue.add(graph.getVertex(sourceRoot));

        visited[sourceRoot] = true;

        while (!queue.isEmpty()){
            Vertex vertex = queue.poll();

            System.out.println(vertex.getData());

            Iterator<Vertex> iterator = vertex.getAdjacentVertexes().iterator();

            while (iterator.hasNext()){
                Vertex vertex1 = iterator.next();

                if(!visited[(int)vertex1.getId()]){
                    queue.add(vertex1);
                    visited[(int)vertex1.getId()] = true;
                }
            }
        }

    }
}
