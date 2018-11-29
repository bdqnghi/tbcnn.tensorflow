package com.hieblmi.graphs;

import com.hieblmi.graphs.Node;

import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

class BFS<T> {

    private Node<T> start;

    BFS(Node<T> start) {
        this.start = start;
    }

    public boolean find(Node<T> n) {

        List<Node<T>> queue = new LinkedList<>();
        queue.add(start);

        while(!queue.isEmpty()) {
            Node<T> c = queue.remove(0);
            System.out.println("Inspect " + c.getData());
            if(c.equals(n)) {
                return true;
            }

            queue.addAll(c.neighbors());
        }

        return false;
    }
}
