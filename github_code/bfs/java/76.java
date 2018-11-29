package graphlab_v1.pkg0;

import static graphlab_v1.pkg0.GraphLab_V10.matrix;
import static graphlab_v1.pkg0.GraphLab_V10.size;
import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.Queue;
/**
 *
 * @author kaleb.himes
 */
public class BFS extends GraphLab_V10 {
    /* procedure BFS(Graph,vertex) is
     create a queue Q
     create a set Vertexes
     enqueue v1 onto Q
     add v1 to V
     while Q is not empty loop
     t ← Q.dequeue()
     if t is what we are looking for then
     return t
     end if
     for all edges e in G.adjacentEdges(t) loop
     u ← G.adjacentVertex(t,e)
     if u is not in V then
     add u to V
     enqueue u onto Q
     end if
     end loop
     end loop
     return none
     end BFS
     */

    public static Queue<String> theQueue = new ArrayDeque<String>();
    public static Vertex[] nodes = new Vertex[size];
    public static char iterate = 'A';
    public static int row = 0;
    public static int nodesPopped = 0;

    public static void Run() {
        //create our nodes
        for (int i = 0; i < matrix.size(); i++) {
            nodes[i] = new Vertex(Character.toString(iterate), false);
            iterate++;
            System.out.print("[" + nodes[i].getNode() + "]");
        }
        System.out.println();
        Search();

    }//end Run()

    public static void Search() {

        //ADD START NODE TO QUEUE IF IT IS UNVISITED
        if (nodes[0].getVisited() != true) {
            theQueue.add(nodes[nodesPopped].getNode());
            //MARK AS VISITED
            nodes[nodesPopped].setVisited(true);
            //user friendly print statement
            System.out.println("added " + nodes[0].getNode() + " to the queue");
        }

        for (int j = 0; j < size; j++) {
            //inside the loop get each value of current row
            String s = matrix.get(row).get(j);
            //if the value is a 1 add to queue and mark visited
            if (s.equals("1") && nodes[j].getVisited() != true) {
                System.out.println(nodes[j].getNode()+" is a child of " + nodes[nodesPopped].getNode() + " add it to the Queue");
                //ADD CHILDREN TO QUEUE
                theQueue.add(nodes[j].getNode());
                //user friendly print statement
                System.out.println("added " + nodes[j].getNode() + " to the queue");
                //MARK VISITED
                nodes[j].setVisited(true);
            }//end if statement
        }//end for loop
        System.out.print(theQueue);
        System.out.println();
        //POP FRONT OF QUE
        System.out.println("popping " + nodes[nodesPopped].getNode());
        theQueue.remove(nodes[nodesPopped].getNode());
        if (theQueue.size() > 2) {
            nodesPopped++;
        } else if (theQueue.size() == 2) {
            nodesPopped+=2;
        } else {
            nodesPopped--;
        }

        if (row < size - 1) {
            //LOOK AT ROW CORRESPONDING TO A's FIRST ALPHABETICAL CHILD
            row++;
            Search();
        }else{
        System.out.println("The matrix has been breadth first searched, Hooray!");
        }
    }
}
