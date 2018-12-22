import java.io.*;
import java.util.*;

class DFS{

    static Stack<Integer> stack = new Stack<>();
    static Map<Integer,Stack<Integer>> map = new HashMap<Integer,Stack<Integer>>();

    static class Graph{
        public void addEdge(int node1,int node2){
            map.putIfAbsent(node1,new Stack<>());
            map.get(node1).add(node2);
        }
        public void printEdges(){
            map.forEach((id, val) -> System.out.println(val));
        }
    }

    static void iterateGraph(int startNode){
        stack.add(startNode);
        System.out.println(startNode);
        while(stack.size() > 0){
            int n = stack.peek();
            if(map.get(n) == null && map.get(n).size() > 0){
                int num = map.get(n).pop();
                System.out.println(num);
                stack.push(num);
            }else{
                stack.pop();
            }
        }
    }

    public static void main(String[] args){
        Graph graph = new Graph();
        graph.addEdge(2,1);
        graph.addEdge(1,3);
        graph.addEdge(2,4);
        graph.addEdge(2,5);
        graph.addEdge(2,6);
        iterateGraph(2);
    }

}