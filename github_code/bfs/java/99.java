package com.algorithm.example.tree.search;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * @author Kiran Pariyar <kiranpariyar@lftechnology.com>
 */
public class BreadthFirstSearch {
    private Queue<Node> queue = new LinkedList<>();
    private List<Integer> result = new ArrayList<>();

    public void bfs(Node node){
        if(node == null) return;
        queue.add(node);
        while (!queue.isEmpty()){
            Node element = queue.remove();
            result.add(element.getData());
            if(element.getLeft() != null) queue.add(element.getLeft());
            if(element.getRight() != null) queue.add(element.getRight());
        }
    }

    public static void main(String[] args){
        int[] numbers = {15, 200, 25, -5, 0, 100, 20, 12, 126, 1000, -150};
        Node node= new Node(20);
        for(int num : numbers){
            node.addNode(num);
        }
        BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch();
        breadthFirstSearch.bfs(node);
        System.out.println("Result :" + breadthFirstSearch.result);
    }
}
