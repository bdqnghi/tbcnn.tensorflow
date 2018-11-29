package com.company;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Stack;

/**
 * Created by jiteshnambiar on 4/12/16.
 */
public class TopologicalSort {
    int V;
    LinkedList<Integer>[] adj;

    TopologicalSort(int V){
        this.V=V;
        adj=new LinkedList[V];
        for(int i=0;i<V;i++){
            adj[i]=new LinkedList<>();
        }
    }


    void addEdge(int v,int w){
        adj[v].add(w);
    }

    void tsort(){
        boolean[] visited=new boolean[V];
        for(int i=0;i<V;i++){
            visited[i]=false;
        }

        Stack<Integer> stack=new Stack();
        for(int i=0;i<V;i++){
            if(!visited[i]){
                tsortUtil(visited,i,stack);
            }
        }
        while(!stack.isEmpty()){
            System.out.println(stack.pop());
        }


    }

    void tsortUtil(boolean[] visited,int start,Stack<Integer> stack){

        visited[start]=true;
        Integer next;
        Iterator<Integer> iterator=adj[start].iterator();
        while(iterator.hasNext()){
            next=iterator.next();
            if(!visited[next]){
                tsortUtil(visited,next,stack);
            }
        }

        stack.push(start);
    }





    public static  void main(String[] args){
        TopologicalSort topologicalSort=new TopologicalSort(6);
        topologicalSort.addEdge(5, 2);
        topologicalSort.addEdge(5, 0);
        topologicalSort.addEdge(4, 0);
        topologicalSort.addEdge(4, 1);
        topologicalSort.addEdge(2, 3);
        topologicalSort.addEdge(3, 1);
        topologicalSort.tsort();
    }
}
