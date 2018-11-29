package com.hackerrank.algorithm.graph_theory.breadth_first_search;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.TreeMap;

/**
 * @author mukesh
 */
public class BreadthFirstSearch {

  private static class Graph {
    private int numberOfVertices;
    private List<Node> listOfVertices;
    private Map<Node, LinkedList<Node>> adjacencyList;

    Graph() {}

    Graph(int numberOfVertices) {
      this.numberOfVertices = numberOfVertices;
      adjacencyList = new TreeMap<Node, LinkedList<Node>>();
      for (int i = 0; i < this.numberOfVertices; i++) {
        adjacencyList.put(new Node(null, i, i), new LinkedList<Node>());
      }
      listOfVertices = new ArrayList<Node>(adjacencyList.keySet());
    }

    void addEdge(Node v, Node w) {
      adjacencyList.get(v).add(w);
      adjacencyList.get(w).add(v);
    }

    List<Node> getListOfVertices() {
      return this.listOfVertices;
    }

  }

  private static class Node implements Comparable {
    Node predecesor;
    long distanceFromSource = -1;
    int data;
    int key;

    Node() {}

    Node(Node predecesor, int data, int key) {
      this.predecesor = predecesor;
      this.data = data;
      this.key = key;
    }

    public Node getPredecesor() {
      return predecesor;
    }

    public void setPredecesor(Node predecesor) {
      this.predecesor = predecesor;
    }

    public long getDistanceFromSource() {
      return distanceFromSource;
    }

    public void setDistanceFromSource(long distanceFromSource) {
      this.distanceFromSource = distanceFromSource;
    }

    public int getData() {
      return data;
    }

    public void setData(int data) {
      this.data = data;
    }

    public int getKey() {
      return key;
    }

    public void setKey(int key) {
      this.key = key;
    }

    @Override
    public int hashCode() {
      return key;
    }

    @Override
    public boolean equals(Object obj) {
      if (this == obj)
        return true;
      if (obj == null)
        return false;
      if (getClass() != obj.getClass())
        return false;
      Node other = (Node) obj;
      if (key != other.key)
        return false;
      return true;
    }

    public int compareTo(Object o) {
      if (this.hashCode() > o.hashCode()) {
        return 1;
      } else if (this.hashCode() < o.hashCode()) {
        return -1;
      }
      return 0;
    }
  }

  static void breadthFirstSearch(Graph graph, int sourceNodeKey) {
    boolean[] visitedNode = new boolean[graph.getListOfVertices().size()];
    Queue<Node> queue = new LinkedList<Node>();
    Node tempNode = graph.getListOfVertices().get(sourceNodeKey);
    tempNode.setDistanceFromSource(0);
    queue.add(tempNode);
    visitedNode[sourceNodeKey] = true;
    while (!queue.isEmpty()) {
      tempNode = queue.poll();
      Iterator<Node> itr = graph.adjacencyList.get(tempNode).iterator();
      while (itr.hasNext()) {
        Node itrNode = itr.next();
        if (!visitedNode[itrNode.getKey()]) {
          visitedNode[itrNode.getKey()] = true;
          queue.add(itrNode);
          itrNode.setDistanceFromSource(tempNode.getDistanceFromSource() + 6);
          itrNode.setPredecesor(tempNode);
        }
      }
    }
    for (Node node : graph.adjacencyList.keySet()) {
      if (node.getKey() != sourceNodeKey) {
      System.out.print(node.getDistanceFromSource() + " ");
      }
    }
    System.out.println();
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int numberOfQueries = scanner.nextInt();
    int numberOfVertices;
    int numberOfEdges;
    int sourceNode;

    for (int q_i = 0; q_i < numberOfQueries; q_i++) {
      numberOfVertices = scanner.nextInt();
      Graph graph = new Graph(numberOfVertices);
      numberOfEdges = scanner.nextInt();
      for (int i = 0; i < numberOfEdges; i++) {
        graph.addEdge(graph.getListOfVertices().get(scanner.nextInt() - 1),
            graph.getListOfVertices().get(scanner.nextInt() - 1));
      }
      sourceNode = scanner.nextInt();
      breadthFirstSearch(graph, sourceNode - 1);
    }
  }
}