package algorithms;

import java.util.ArrayList;
import java.util.List;

public class MinimumSpanningTree
{
    public static void main(String[] args)
    {
        List<Vertex> vertices = new ArrayList();

        Vertex a = new Vertex('a');
        Vertex b = new Vertex('b');
        Vertex c = new Vertex('c');
        Vertex d = new Vertex('d');
        Vertex e = new Vertex('e');
        Vertex f = new Vertex('f');
        Vertex g = new Vertex('g');
        Vertex h = new Vertex('h');
        Vertex i = new Vertex('i');

        vertices.add(a);
        vertices.add(b);
        vertices.add(c);
        vertices.add(d);
        vertices.add(e);
        vertices.add(f);
        vertices.add(g);
        vertices.add(h);
        vertices.add(i);

        a.edges.add(new Edge(a, b, 4));
        a.edges.add(new Edge(a, h, 8));
        b.edges.add(new Edge(b, a, 4));
        b.edges.add(new Edge(b, h, 11));
        b.edges.add(new Edge(b, c, 8));
        c.edges.add(new Edge(c, b, 8));
        c.edges.add(new Edge(c, i, 2));
        c.edges.add(new Edge(c, d, 7));
        c.edges.add(new Edge(c, f, 4));
        d.edges.add(new Edge(d, c, 7));
        d.edges.add(new Edge(d, e, 9));
        d.edges.add(new Edge(d, f, 14));
        e.edges.add(new Edge(e, d, 9));
        e.edges.add(new Edge(e, f, 10));
        f.edges.add(new Edge(f, d, 14));
        f.edges.add(new Edge(f, e, 10));
        f.edges.add(new Edge(f, c, 4));
        f.edges.add(new Edge(f, g, 2));
        g.edges.add(new Edge(g, f, 2));
        g.edges.add(new Edge(g, i, 6));
        g.edges.add(new Edge(g, h, 1));
        h.edges.add(new Edge(h, g, 1));
        h.edges.add(new Edge(h, i, 7));
        h.edges.add(new Edge(h, b, 11));
        h.edges.add(new Edge(h, a, 8));
        i.edges.add(new Edge(i, c, 2));
        i.edges.add(new Edge(i, g, 6));
        i.edges.add(new Edge(i, h, 7));

        Graph graph = new Graph(vertices);

        minimumSpanningTree(graph);
    }

    private static void minimumSpanningTree(Graph graph)
    {
        List<Vertex> remainingVertices = new ArrayList<Vertex>(graph.vertices);
        List<Vertex> usedVertices = new ArrayList<Vertex>();
        List<Edge> minEdges = new ArrayList<Edge>();
        List<Edge> treeEdges = new ArrayList<Edge>();

        usedVertices.add(remainingVertices.get(0));
        remainingVertices.remove(0);

        while (!remainingVertices.isEmpty())
        {
            for(Vertex vertex : usedVertices)
            {
                Edge minEdge = null;
                for(Edge edge : vertex.edges)
                {
                    if(remainingVertices.contains(edge.to))
                        if (minEdge == null || edge.weight < minEdge.weight)
                            minEdge = edge;
                }
                if(minEdge != null)
                    minEdges.add(minEdge);
            }
            Edge minEdge = getMinEdge(minEdges);
            treeEdges.add(minEdge);
            usedVertices.add(minEdge.to);
            remainingVertices.remove(minEdge.to);
            minEdges.clear();
        }

        for (Edge edge : treeEdges)
            System.out.println(edge.from.value + " : " + edge.to.value + " : " + edge.weight);
    }

    private static Edge getMinEdge(List<Edge> minEdges)
    {
        Edge minEdge = minEdges.get(0);
        for (Edge edge : minEdges)
            if(edge.weight < minEdge.weight)
                minEdge = edge;
        return minEdge;
    }


}

class Graph
{
    List<Vertex> vertices;

    public Graph(List<Vertex> vertices)
    {
        this.vertices = vertices;
    }
}

class Vertex
{
    char value;
    Color color;
    List<Edge> edges = new ArrayList<Edge>();

    public Vertex(char value)
    {
        this.value = value;
    }
}

class Edge
{
    Vertex from;
    Vertex to;
    int weight;

    public Edge(Vertex from, Vertex to, int weight)
    {
        this.from = from;
        this.to = to;
        this.weight = weight;
    }
}

enum Color
{
    WHITE, BLACK
}