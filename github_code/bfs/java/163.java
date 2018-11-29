package com.vincii.tree;

import java.util.Iterator;
import java.util.LinkedList;

public class BFS {



        int V;
        LinkedList<Integer>[] adjList;

        public BFS(int v){
            this.V = v;
            adjList = new LinkedList[V];

            for(int i = 0; i<V; i++){
                adjList[i] = new LinkedList<Integer>();
            }
        }

        public void addEdge(int src,int dest){
            adjList[src].add(dest);
        }

        public void BFSearch(int s){

            boolean[] visited = new boolean[V];
            LinkedList<Integer> queue = new LinkedList<Integer>();

            visited[s] = true;
            queue.add(s);

            while(queue.size() != 0){

                s = queue.poll();
                System.out.print(s + " ");

                Iterator<Integer> i = adjList[s].listIterator();
                while(i.hasNext()){
                    int n = i.next();
                    if(!visited[n]){
                        visited[n] = true;
                        queue.add(n);
                    }
                }
            }
        }

}
