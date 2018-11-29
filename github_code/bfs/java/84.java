package net.largepixels.crackingcodinginterview.ch04.demo;

import net.largepixels.interviewstructures.nodes.graph.Node;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.SynchronousQueue;

/**
 * Created by johnminchuk on 2/16/16.
 */
public class BreadthFirstSearch {

    private void runMe() {
        //         b
        //       / |
        //     a - c
        //       \ |
        //         e - d

        Node a = new Node("a");
        Node b = new Node("b");
        Node c = new Node("c");
        Node d = new Node("d");
        Node e = new Node("e");

        a.nodes = new Node[]{b, c, e};
        b.nodes = new Node[]{a, c};
        c.nodes = new Node[]{a, b, e};
        d.nodes = new Node[]{e};
        e.nodes = new Node[]{a, c, d};

        breadthFirstSearch(d);
    }

    private void breadthFirstSearch(Node head) {
        Queue<Node> queue = new ArrayBlockingQueue<>(20);
        queue.add(head);
        visit(head);

        while (!queue.isEmpty()) {
            Node r = queue.remove();
            for (Node n : r.nodes) {
                if (!n.visited) {
                    visit(n);
                    queue.add(n);
                }
            }
        }
    }

    private void visit(Node n) {
        n.visited = true;
        System.out.println("Visiting: " + n.value);
    }

    public static void main(String args[]) {
        BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch();
        breadthFirstSearch.runMe();
    }

}
