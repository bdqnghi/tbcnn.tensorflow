package algs.search;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

import util.GraphNode;

/*
 * BreadthFirstSearch of an undirected graph
 * TODO, complete and test
 */
public class BreadthFirstSearch {

    private BreadthFirstSearch() {}

    public static GraphNode search(GraphNode start, int endData) {
        //Initialize an empty queue of visited nodes
        if (start.data==endData || start==null){
            return start;
        }

        Queue<GraphNode> queue = new LinkedList<>();
        Set<GraphNode> visitedSet = new HashSet<>();
        queue.add(start);

        //add current node to the queue.
        //add each adjacent node to the queue, if it is not in visited Set.
        GraphNode curr;
        while(!queue.isEmpty()) {

            curr = queue.poll();

            if( !visitedSet.contains(curr) ) {
                //Check for victory case!
                if(curr.data == endData){
                    return curr;
                }

                visitedSet.add(curr);

                for(GraphNode neighbor : curr.edges) {

                    if( !visitedSet.contains(neighbor) ) {
                        queue.add(neighbor);
                    }

                }
            }
        }

        return null;
    }

}
