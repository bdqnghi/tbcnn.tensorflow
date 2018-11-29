package Q4_07_Build_Order.DFS;

import java.util.ArrayList;
import java.util.Stack;

/*
 * Build order: you are given a list of projects and a list of dependencies (which is a list of pairs of projects, where
 * the second project is dependent on the first project). all of a project's dependencies must be built before the
 * project is. find a build order that will allow the projects to be built. if there is no valid build order, return an
 * error.
 *
 * Example:
 * Input:
 *  projects: a, b, c,d, e,f
 *  dependencies: (a,d), (f,b), (b,d),(f,a), (d,c)
 * Output: f, e, a, b, d,c
 *
 * Hint 26: build a directed graph representing the dependencies. each node is a project and an edge exists from A to B
 * if B depends on A (A must be built before B). you can also build it the other way if it's easier for you.
 *
 * hint 47: look at this graph. is there any node you can identify that will definitely be okay to build first?
 *
 * hint 60: if you identify a node without any incoming edges, then it can definitely be built.
 * find this node(there could be multiple) and add it to the build order. then, what does this mean for its outgoing edges?
 *
 * hint 85: once you decide to build a node, its outgoing edge can be deleted. after you've done this,
 * can you find other nodes that are free and clear to build?
 *
 * hint 125: as a totally different approach: consider doing a depth-first-search starting from an arbitrary node.
 * what is the relationship between this depth-first-search and a valid build order?
 *
 * hint 133: pick an arbitrary node and do a depth-first-search on it. once we get to the end of a path,
 * we know that this node can be the last one built. since no nodes depend on it. what does this mean about the nodes right before it?
 */
public class Question {

  /**
   * Build the graph, adding the edge (a, b) if b is dependent on a. Assumes a pair is listed in “build order” (which is
   * the reverse of dependency order). The pair (a, b) in dependencies indicates that b depends on a and a must be built
   * before b.
   */
  public static Graph buildGraph(String[] projects, String[][] dependencies) {
    Graph graph = new Graph();

    for (String project : projects) {
      graph.getOrCreateNode(project);
    }

    for (String[] dependency : dependencies) {
      String first = dependency[0];
      String second = dependency[1];
      graph.addEdge(first, second);
    }

    return graph;
  }

  /**
   * in DFS, we visit a node A and then iterate through each of A's neighbors. when we visiting a node B that is a a
   * neighbor of A, we visit all of B's neighbors before going on to A's other neighbors. that is, a exhaustively search
   * B's branch before any of its other neighbors.
   */
  public static boolean doDepthFirstSearch(Project project, Stack<Project> stack) {
    if (project.getState() == Project.State.PARTIAL) {
      return false; // Cycle
    }

    if (project.getState() == Project.State.BLANK) {
      project.setState(Project.State.PARTIAL);

      ArrayList<Project> children = project.getChildren();
      for (Project child : children) {
        if (!doDepthFirstSearch(child, stack)) {
          return false;
        }
      }

      project.setState(Project.State.COMPLETE);
      stack.push(project);
    }

    return true;
  }

  public static Stack<Project> orderProjects(ArrayList<Project> projects) {
    Stack<Project> stack = new Stack<Project>();

    for (Project project : projects) {
      if (project.getState() == Project.State.BLANK) {
        if (!doDepthFirstSearch(project, stack)) {
          return null;
        }
      }
    }
    return stack;
  }

  public static String[] convertToStringList(Stack<Project> projects) {
    String[] buildOrder = new String[projects.size()];
    for (int i = 0; i < buildOrder.length; i++) {
      buildOrder[i] = projects.pop().getName();
    }
    return buildOrder;
  }

  public static Stack<Project> findBuildOrder(String[] projects, String[][] dependencies) {
    Graph graph = buildGraph(projects, dependencies);
    return orderProjects(graph.getNodes());
  }

  public static String[] buildOrderWrapper(String[] projects, String[][] dependencies) {
    Stack<Project> buildOrder = findBuildOrder(projects, dependencies);
    if (buildOrder == null) {
      return null;
    }
    String[] buildOrderString = convertToStringList(buildOrder);
    return buildOrderString;
  }

  public static void main(String[] args) {
    String[] projects = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    String[][] dependencies = {
        {"a", "b"},
        {"b", "c"},
        {"a", "c"},
        {"d", "e"},
        {"b", "d"},
        {"e", "f"},
        {"a", "f"},
        {"h", "i"},
        {"h", "j"},
        {"i", "j"},
        {"g", "j"}};

    String[] buildOrder = buildOrderWrapper(projects, dependencies);
    if (buildOrder == null) {
      System.out.println("Circular Dependency.");
    } else {
      for (String s : buildOrder) {
        System.out.println(s);
      }
    }
  }

}
