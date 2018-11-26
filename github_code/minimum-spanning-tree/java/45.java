package interview_tasks.graph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author vladov
 *         05/08/2018
 */
class vertex {
    private int id;
    private boolean visited;

    public vertex(int id, boolean visited) {
        super();
        this.id = id;
        this.visited = visited;
    }

    int getId() {
        return id;
    }

    void setId(int id) {
        this.id = id;
    }

    boolean isVisited() {
        return visited;
    }

    void setVisited(boolean visited) {
        this.visited = visited;
    }
}

class edge {
    private int weight;
    private boolean visited;
    private vertex src;
    private vertex dest;

    public edge(int weight, boolean visited, vertex src,
                vertex dest) {
        this.weight = weight;
        this.visited = visited;
        this.src = src;
        this.dest = dest;
    }

    int getWeight() {
        return weight;
    }

    void setWeight(int weight) {
        this.weight = weight;
    }

    boolean isVisited() {
        return visited;
    }

    void setVisited(boolean visited) {
        this.visited = visited;
    }

    vertex getSrc() {
        return src;
    }

    void setSrc(vertex src) {
        this.src = src;
    }

    vertex getDest() {
        return dest;
    }

    void setDest(vertex dest) {
        this.dest = dest;
    }
}

class graph {
    private List<vertex> g;   //vertices
    private List<edge> e;     //edges

    public graph(List<vertex> g, List<edge> e) {
        super();
        this.g = g;
        this.e = e;
    }

    public List<vertex> getG() {
        return g;
    }

    public void setG(List<vertex> g) {
        this.g = g;
    }

    public List<edge> getE() {
        return e;
    }

    public void setE(List<edge> e) {
        this.e = e;
    }

    // This method returns the vertex with a given id if it
    // already exists in the graph, returns NULL otherwise
    vertex vertex_exists(int id) {
        for (int i = 0; i < g.size(); i++) {
            if (g.get(i).getId() == id) {
                return g.get(i);
            }
        }
        return null;
    }

    // This method generates the graph with v vertices
    // and e edges
    void generate_graph(int vertices,
                        List<ArrayList<Integer>> edges) {
        // create vertices
        for (int i = 0; i < vertices; i++) {
            vertex v = new vertex(i + 1, false);
            g.add(v);
        }

        // create edges
        for (int i = 0; i < edges.size(); i++) {
            vertex src = vertex_exists(edges.get(i).get(1));
            vertex dest = vertex_exists(edges.get(i).get(2));
            edge e = new edge(edges.get(i).get(0), false, src,
                    dest);
            getE().add(e);
        }
    }

    // This method finds the MST of a graph using
    // Prim's Algorithm
    // returns the weight of the MST
    int find_min_spanning_tree() {
        int vertex_count = 0;
        int weight = 0;

        // Add first vertex to the MST
        vertex current = g.get(0);
        current.setVisited(true);
        vertex_count++;

        // Construct the remaining MST using the
        // smallest weight edge
        while (vertex_count < g.size()) {
            edge smallest = null;
            for (int i = 0; i < e.size(); i++) {
                if (!e.get(i).isVisited()
                        && !e.get(i).getDest().isVisited()) {
                    smallest = e.get(i);
                    break;
                }
            }

            for (int i = 0; i < e.size(); i++) {
                if (!e.get(i).isVisited()) {
                    if (e.get(i).getSrc().isVisited()
                            && !e.get(i).getDest().isVisited()
                            && (e.get(i).getWeight() < smallest
                            .getWeight())) {
                        smallest = e.get(i);
                    }
                }
            }

            smallest.setVisited(true);
            smallest.getDest().setVisited(true);
            weight += smallest.getWeight();
            vertex_count++;
        }
        return weight;
    }

    void print_graph() {
        for (int i = 0; i < g.size(); i++) {
            System.out.println(
                    g.get(i).getId() + " " + g.get(i).isVisited());
        }
        System.out.println();
        for (int i = 0; i < e.size(); i++) {
            System.out.println(e.get(i).getSrc().getId() + "->"
                    + e.get(i).getDest().getId() + "["
                    + e.get(i).getWeight() + ", "
                    + e.get(i).isVisited() + "]  ");
        }
        System.out.println("\n");
    }

    void print_mst(int w) {
        System.out.println("MST");
        for (int i = 0; i < e.size(); i++) {
            if (e.get(i).isVisited() == true) {
                System.out.println(e.get(i).getSrc().getId() + "->"
                        + e.get(i).getDest().getId());
            }
        }
        System.out.println("weight: " + w);
        System.out.println();
    }
};

class mst {
    public static void test_graph1() {
        graph g = new graph(new ArrayList<vertex>(),
                new ArrayList<edge>());
        int v = 5;

        // each edge contains the following: weight, src, dest
        ArrayList<Integer> e1 = new ArrayList<Integer>(
                Arrays.asList(1, 1, 2));
        ArrayList<Integer> e2 = new ArrayList<Integer>(
                Arrays.asList(1, 1, 3));
        ArrayList<Integer> e3 = new ArrayList<Integer>(
                Arrays.asList(2, 2, 3));
        ArrayList<Integer> e4 = new ArrayList<Integer>(
                Arrays.asList(3, 2, 4));
        ArrayList<Integer> e5 = new ArrayList<Integer>(
                Arrays.asList(3, 3, 5));
        ArrayList<Integer> e6 = new ArrayList<Integer>(
                Arrays.asList(2, 4, 5));

        List<ArrayList<Integer>> e = new ArrayList<ArrayList<Integer>>();
        e.add(e1);
        e.add(e2);
        e.add(e3);
        e.add(e4);
        e.add(e5);
        e.add(e6);

        g.generate_graph(v, e);
        System.out.println("Testing graph 1...");
        // g.print_graph();
        int w = g.find_min_spanning_tree();
        g.print_mst(w);
    }

    public static void test_graph2() {
        graph g = new graph(new ArrayList<vertex>(),
                new ArrayList<edge>());
        int v = 7;

        // each edge contains the following: weight, src, dest
        ArrayList<Integer> e1 = new ArrayList<Integer>(
                Arrays.asList(2, 1, 4));
        ArrayList<Integer> e2 = new ArrayList<Integer>(
                Arrays.asList(1, 1, 3));
        ArrayList<Integer> e3 = new ArrayList<Integer>(
                Arrays.asList(2, 1, 2));
        ArrayList<Integer> e4 = new ArrayList<Integer>(
                Arrays.asList(1, 3, 4));
        ArrayList<Integer> e5 = new ArrayList<Integer>(
                Arrays.asList(3, 2, 4));
        ArrayList<Integer> e6 = new ArrayList<Integer>(
                Arrays.asList(2, 3, 5));
        ArrayList<Integer> e7 = new ArrayList<Integer>(
                Arrays.asList(2, 4, 7));
        ArrayList<Integer> e8 = new ArrayList<Integer>(
                Arrays.asList(1, 5, 6));
        ArrayList<Integer> e9 = new ArrayList<Integer>(
                Arrays.asList(2, 5, 7));

        List<ArrayList<Integer>> e = new ArrayList<ArrayList<Integer>>();
        e.add(e1);
        e.add(e2);
        e.add(e3);
        e.add(e4);
        e.add(e5);
        e.add(e6);
        e.add(e7);
        e.add(e8);
        e.add(e9);

        g.generate_graph(v, e);
        System.out.println("Testing graph 2...");
        // g.print_graph();
        int w = g.find_min_spanning_tree();
        g.print_mst(w);
    }

    public static void main(String[] args) {
        test_graph1();
        test_graph2();

        System.out.println("Completed!");
    }
}
