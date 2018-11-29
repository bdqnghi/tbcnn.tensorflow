package retiming;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

import scheduler.Graph;
import scheduler.Node;

/**
 * This class contains basic operations required for retiming of nodes in a graph.
 * @author Mitja Stachowiak, Ludwig Meysel
 */
public abstract class Retimer {
  protected final Graph graph;
  private final ArrayList<Node> topologicalSort;
  private static class TopologicalComparator implements Comparator<Node> {
    @Override
    public int compare(Node o1, Node o2) { return o1.getDepth() - o2.getDepth(); }
  }
  private final TopologicalComparator topologicalComp = new TopologicalComparator();
  
  public Retimer (Graph graph) {
    this.graph = graph;
    this.topologicalSort = new ArrayList<Node>(graph.size());
    Iterator<Node> it = graph.iterator();
    while (it.hasNext()) topologicalSort.add(it.next());
  }
  
  /**
   * @return the longest path (delayed) in the graph. This will be the duration of a ASAP or ALAP-schedule
   */
  protected int longestPath () {
    topologicalSort.sort(topologicalComp);
    // set tmp1 to 0
    if (graph.tmp1Used) throw new IllegalArgumentException("An other function is using tmp1 in this graph!");
    else graph.tmp1Used = true;
    for (int i = 0; i < topologicalSort.size(); i++) topologicalSort.get(i).tmp1 = 0;
    // set start times in paths
    for (int i = 0; i < topologicalSort.size(); i++) {
      int nextStartTime = topologicalSort.get(i).tmp1 + topologicalSort.get(i).getDelay();
      HashMap<Node, Integer> succ = topologicalSort.get(i).allSuccessors();
      Iterator<Entry<Node, Integer>> it = succ.entrySet().iterator();
      while (it.hasNext()) {
        Entry<Node, Integer> e = it.next();
        if (e.getValue() != 0) continue; // don't regard edges to later iterations
        if (nextStartTime > e.getKey().tmp1) e.getKey().tmp1 = nextStartTime;
      }
    }
    // add last node's delay to paths and store maximum
    int longestPath = 0;
    for (int i = 0; i < topologicalSort.size(); i++) {
      topologicalSort.get(i).tmp1 += topologicalSort.get(i).getDelay();
      if (topologicalSort.get(i).tmp1 > longestPath) longestPath = topologicalSort.get(i).tmp1;
    }
    graph.tmp1Used = false;
    return longestPath;
  }
  
  /**
   * Processes a retiming on the graph, that was given to this retimer in the constructor
   * @return
   * returns an array of three integers, holding the start and the end cost and the number of needed cycles.
   */
  public abstract int[] retime (int quality);
}
