package Algorithms;

import Structures.Graph.Graph;
import Structures.Graph.Vertex;
import Structures.LinkedList.LinkedList;
import Structures.Hashtable.Hashtable;
import Structures.Queue.Queue;
import Utils.Color;
import Utils.Iterator;

/**
* BFS algorithm for finding the shortest path between vertex a and b. Only works with a weightless graph
*/

public class BFS extends PathFinder{
    public Graph graph;
    public BFS(Graph graph){
        super(graph);
        this.graph=graph;
    }
    @Override
    public Path shortestPath(Vertex a, Vertex b) {
        Hashtable<Vertex,Color> color=new Hashtable<Vertex,Color>(graph.getVertices().size()*2);
        Hashtable<Vertex,Vertex> tree=new Hashtable<Vertex,Vertex>(graph.getVertices().size()*2);
        Hashtable<Vertex,Integer> distance=new Hashtable<Vertex,Integer>(graph.getVertices().size()*2);
        LinkedList<Vertex> vertices = graph.getVertices();
        Iterator<Vertex> j = new Iterator<Vertex>(vertices);
        while(j.hasNext()){
            Vertex v = j.getNext();
            color.put(v,Color.WHITE);
            tree.put(v,null);
            distance.put(v,Integer.MAX_VALUE);
        }
        Queue<Vertex> queue = new Queue<Vertex>();
        color.put(a,Color.GREY);
        distance.put(a,0);
        queue.enqueue(a);
        while(!queue.isEmpty()){
            Vertex u=queue.dequeue();
            LinkedList<Vertex> adjacencyVertices=graph.getAdjacencyVertices(u);
            Iterator<Vertex> r = new Iterator<Vertex>(adjacencyVertices);
            while(r.hasNext()){
                Vertex h = r.getNext();
                if(color.get(h)==Color.WHITE){
                    color.put(h, Color.GREY);
                    tree.put(h,u);
                    distance.put(h, distance.get(u)+1);
                    queue.enqueue(h);
                }
            }
            color.put(u, Color.BLACK);
        }
        if(distance.get(b)==Integer.MAX_VALUE){
            return null;
        }
        return super.getPath(a,b,tree,distance);
    }
}
