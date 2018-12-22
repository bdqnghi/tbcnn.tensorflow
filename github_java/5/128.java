package graphs;

import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class DepthFirstSearch {
  
  static class Node {
    int value;
    LinkedList<Node> neighbours;
    
    public Node(int val) {
      this.value = val;
      this.neighbours = new LinkedList<Node>();
    }
    
    public void add(Node... nodes) {
      for (Node node : nodes)
      neighbours.add(node);
    }
  }

  /**
   * Path from 1 to 10;
   * 2--(1)---3
   *     |    |
   *     4----5     8
   *          |     |
   *          6-----7---(10)
   *                |
   *    11---12     9   
   *         |
   *         13
   */
  public static void main(String[] args) {
    
    // I could probably shorten this by using an array.
    Node node1 = new Node(1);
    Node node2 = new Node(2);
    Node node3 = new Node(3);
    Node node4 = new Node(4);
    Node node5 = new Node(5);
    Node node6 = new Node(6);
    Node node7 = new Node(7);
    Node node8 = new Node(8);
    Node node9 = new Node(9);
    Node node10 = new Node(10);
    Node node11 = new Node(11);
    Node node12 = new Node(12);
    Node node13 = new Node(13);
    
    
    node2.add(node1);
    node1.add(node2, node3, node4);
    node3.add(node1, node5);
    node4.add(node1, node5);
    node5.add(node3,node4,  node6);
    node6.add(node5, node7);
    node7.add(node8, node6, node9, node10);
    node8.add(node7);
    node9.add(node8);
    node10.add(node7);
    node11.add(node12);
    node12.add(node11, node13);
    node13.add(node12);
    
    System.out.println(" Path exist between 1 and 10? :" + pathExist(node1, node10));
    System.out.println(" Path exist between 1 and 12? :" + pathExist(node1, node12));
    System.out.println(" Path exist between 11 and 13? :" + pathExist(node11, node13));
  }
  
  static boolean pathExist(Node start, Node dest) {
    Set<Integer> visited = new HashSet<Integer>();
    Queue<Node> toBeVisited = new LinkedList<Node>();
    
    // for all neighbours, if not in visited, add to toBeVisited,
    toBeVisited.add(start);
    visited.add(start.value);
    
    while (toBeVisited.size() != 0) {
      Node node = toBeVisited.remove();
      System.out.println("Visiting node: " + node.value);
      if (node.equals(dest)) {
        return true;
      } else {
        Iterator<Node> itr = node.neighbours.iterator();
        while (itr.hasNext()) {
          Node nextLink = itr.next();
          if (!visited.contains(nextLink.value)) {
            toBeVisited.add(nextLink);
            visited.add(nextLink.value);
          }
        }
      }
    }
    return false;
  }
}
  
//  static boolean visit (Node curr, Node dest, Set<Integer> visited, Queue<Node> toBeVisited) {
//    if (curr.equals(dest)) {
//      return true;
//    }
//    Iterator<Node> itr = curr.neighbours.iterator();
//    while (itr.hasNext()) {
//      Node node = itr.next();
//      if (node.equals(dest)) {
//        return true;
//      }
//      
//      if (!visited.contains(node.value)) {
//        toBeVisited.add(node);
//      }
//    }

