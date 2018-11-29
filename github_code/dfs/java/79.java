package com.meancat.study.datastructures;

import java.util.Stack;

public class Dfs {


    public static boolean search(int value, Node node) {
        Stack<Node> stack = new Stack<Node>();
        stack.push(node);
        node.visited = true;
        while(!stack.isEmpty()) {
            Node t = stack.pop();
            if (t.value == value) {
                return true; // found it!
            }
            for(Node vertex : t.vertices) {
                if (!vertex.visited) {
                    vertex.visited = true;
                    stack.push(vertex);
                }
            }
        }
        return false;
    }
}
