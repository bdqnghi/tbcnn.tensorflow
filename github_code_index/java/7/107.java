package com.hrishikeshmishra.dsjava.practise.graph;


import java.util.*;

/**
 * <p>
 *     Topological
 * </p>
 * Created by hrishikesh.mishra
 */
public class TopologicalSortNonRecursive {

    public static class DirectedGraph<V>{

        public static final double DEFAULT_WEIGHT = 1.0;

        public static class Vertex<V>{

            private V v;

            private List<Edge<V>> neighbors;

            public Vertex(V v) {
                this.v = v;
                neighbors = new ArrayList<>();
            }

            public V getName() {
                return v;
            }

            public void addNeighbor(Edge<V> edge){
                neighbors.add(edge);
            }

            public List<Edge<V>> getNeighbors(){
                return neighbors;
            }

            @Override
            public boolean equals(Object o) {
                if (this == o) return true;
                if (!(o instanceof Vertex)) return false;

                Vertex vertex = (Vertex) o;
                if (v != null ? !v.equals(vertex.v) : vertex.v != null) return false;

                return true;
            }

            @Override
            public int hashCode() {
                int result = v != null ? v.hashCode() : 0;
                result = 31 * result;
                return result;
            }

            @Override
            public String toString() {
                return "Vertex(" + v + ')';
            }
        }

        public static class Edge<V> {
            private Vertex<V> start;
            private Vertex<V> end;
            private String name;
            private double weight;

            public Edge(Vertex<V> start, Vertex<V> end, String name) {
                this(start, end, name, DEFAULT_WEIGHT);
            }

            public Edge(Vertex<V> start, Vertex<V> end, String name, double weight) {
                this.start = start;
                this.end = end;
                this.name = name;
                this.weight = weight;
            }

            public Vertex<V> getStart() {
                return start;
            }

            public Vertex<V> getEnd() {
                return end;
            }

            public String getName() {
                return name;
            }

            public double getWeight() {
                return weight;
            }

            @Override
            public boolean equals(Object o) {
                if (this == o) return true;
                if (!(o instanceof Edge)) return false;

                Edge edge = (Edge) o;

                if (end != null ? !end.equals(edge.end) : edge.end != null) return false;
                if (start != null ? !start.equals(edge.start) : edge.start != null) return false;

                return true;
            }

            @Override
            public int hashCode() {
                int result;
                result = start != null ? start.hashCode() : 0;
                result = 31 * result + (end != null ? end.hashCode() : 0);
                return result;
            }
        }


        private Map<V, Vertex<V>> vertices;
        private List<Edge<V>> edges;

        public DirectedGraph() {
            vertices = new HashMap<>();
            edges = new ArrayList<>();
        }

        public void addVertex(Vertex<V> v){
            if(vertices.containsKey(v))
                return;
            vertices.put(v.getName(), v);
        }

        public void addEdge(Vertex<V> start, Vertex<V> end, String name){
            if(!vertices.containsKey(start.getName()) || !vertices.containsKey(end.getName()))
                throw new RuntimeException("start or end vertex is not found. ");

            Edge<V> e = new Edge<V>(start, end, name);

            /** Duplicate edge **/
            if(edges.contains(e)) return;

            /** Outgoing edge from start **/
            start.addNeighbor(e);

            edges.add(e);
        }

        public int getOutDegree(Vertex<V> v){
            return getOutgoingEdge(v).size();
        }

        public List<Edge<V>> getOutgoingEdge(Vertex<V> v) {
            return v.getNeighbors();
        }
        public List<Edge<V>> getIncomingEdge(Vertex<V> v){
            List<Edge<V>> incomingEdges = new ArrayList<>();

            for (Edge<V> e: edges)
                if(e.getEnd().equals(v))
                    incomingEdges.add(e);


            return incomingEdges;

        }

        public int getInDegree(Vertex<V> v){
            return getIncomingEdge(v).size();
        }

        public Vertex<V> getOppositeVertexOfEdge(Edge<V> e, Vertex<V> v){
            if(!edges.contains(e))
                return null;

            if(e.getStart().equals(v))
                return e.getEnd();
            else if(e.getEnd().equals(v))
                return e.getEnd();
            else
                return null;

        }

        public List<Vertex<V>> getVertices() {
            List<Vertex<V>> vertexList = new ArrayList<>();
            for(Vertex<V> v: vertices.values())
                vertexList.add(v);

            return vertexList;
        }
    }

    public <V> List<DirectedGraph.Vertex<V>> topologicalSort(DirectedGraph<V> g){

        List<DirectedGraph.Vertex<V>> topo = new LinkedList<>();

        Stack<DirectedGraph.Vertex<V>> ready = new Stack<>();
        Map<DirectedGraph.Vertex<V>, Integer> inCount = new HashMap<>();

        for(DirectedGraph.Vertex<V> v: g.getVertices()) {
            inCount.put(v, g.getInDegree(v));
            if(inCount.get(v) == 0 ){
                ready.push(v);
            }
        }


        while(!ready.isEmpty()){
            DirectedGraph.Vertex<V> u = ready.pop();
            topo.add(u);
            for(DirectedGraph.Edge<V> e: g.getOutgoingEdge(u)){
                DirectedGraph.Vertex<V> v = g.getOppositeVertexOfEdge(e, u);
                inCount.put(v, inCount.get(v) - 1);
                if(inCount.get(v) == 0){
                    ready.push(v);
                }
            }
        }

        return topo;

    }


}


class TopologicalSortNonRecursiveTest{

    public static void main(String[] args) {
        //example1();
        example2();

    }

    private static void example1(){
        TopologicalSortNonRecursive.DirectedGraph<String> g = new TopologicalSortNonRecursive.DirectedGraph<>();

        TopologicalSortNonRecursive topoSort = new TopologicalSortNonRecursive();

        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> v1 = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("1");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> v2 = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("2");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> v3 = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("3");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> v4 = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("4");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> v5 = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("5");

        g.addVertex(v1);
        g.addVertex(v2);
        g.addVertex(v3);
        g.addVertex(v4);
        g.addVertex(v5);

        g.addEdge(v1, v2, "v1->v2");
        g.addEdge(v2, v3, "v2->v3");
        g.addEdge(v2, v4, "v2->v4");
        g.addEdge(v3, v5, "v3->v5");
        g.addEdge(v4, v5, "v3->v5");

        List<TopologicalSortNonRecursive.DirectedGraph.Vertex<String>> vertexes = topoSort.topologicalSort(g);
        vertexes.forEach(v -> { System.out.print(v.getName() + "->");});
    }

    private static void example2(){

        TopologicalSortNonRecursive.DirectedGraph<String> graph = new TopologicalSortNonRecursive.DirectedGraph<>();

        TopologicalSortNonRecursive topoSort = new TopologicalSortNonRecursive();

        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> a = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("A");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> b = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("B");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> c = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("C");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> d = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("D");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> e = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("E");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> f = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("F");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> g = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("G");
        TopologicalSortNonRecursive.DirectedGraph.Vertex<String> h = new TopologicalSortNonRecursive.DirectedGraph.Vertex<>("H");

        graph.addVertex(a);
        graph.addVertex(b);
        graph.addVertex(c);
        graph.addVertex(d);
        graph.addVertex(e);
        graph.addVertex(f);
        graph.addVertex(g);
        graph.addVertex(h);

        graph.addEdge(a, c, "A->C");
        graph.addEdge(a, d, "A->D");

        graph.addEdge(b, d, "B->D");
        graph.addEdge(b, f, "B->F");

        graph.addEdge(c, d, "C->D");
        graph.addEdge(c, e, "C->E");
        graph.addEdge(c, h, "C->H");

        graph.addEdge(d, f, "D->F");

        graph.addEdge(e, g, "E->G");

        graph.addEdge(f, g, "F->G");
        graph.addEdge(f, h, "F->H");

        graph.addEdge(g, h, "G->H");


        List<TopologicalSortNonRecursive.DirectedGraph.Vertex<String>> vertexes = topoSort.topologicalSort(graph);
        vertexes.forEach(v -> { System.out.print("->" + v.getName());});
    }

}