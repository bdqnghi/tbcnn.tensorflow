import java.util.*;

/*
拓扑排序及其Java实现
https://blog.csdn.net/sinat_22013331/article/details/52046101
https://www.cnblogs.com/skywang12345/p/3711494.html
*/

public class TopologicalSort {
  private List<Node> res;
  private Queue<Node> zeroInDegree;
  private Graph graph;
  
  public boolean TopologicalSortBFS(Graph di) {
    this.graph = di;
    res = new ArrayList<>();
    zeroInDegree = new LinkedList<>();
    //初始化:将入度为零的点入队
    for (Node curr : graph.nodes) {
      if (curr.pathIn == 0) {
        zeroInDegree.offer(curr);
      }
    }
    while (!zeroInDegree.isEmpty()) {
      Node curr = zeroInDegree.poll();
      //队列里的点都是入度为零的点
      res.add(curr);
      for (Node to : graph.adj.get(curr)) {
        //更新改点邻居的入度
        to.pathIn--;
        //把更新后入度为零的点入队
        if (to.pathIn == 0) {
          zeroInDegree.offer(to);
        }
      }
      //更新改点邻居的入度并把改点入结果集后 在图中删除该点
      graph.nodes.remove(curr);
      graph.adj.remove(curr);
    }
    //图中还存在边 则表示有环 不能拓扑排序
    if (!graph.nodes.isEmpty()) {
      return false;
    }
    return true;
  }
  
  public boolean TopologicalSortDFS(Graph di) {
    Stack<Node> stack = new Stack<>();
    Set<Node> isLoop = new HashSet<>();
    Set<Node> visited = new HashSet<>();
    res = new ArrayList<>();
    for (Node curr : di.nodes) {
      if (!dfs(di, curr, isLoop, visited, stack)) return false;
    }
    while (!stack.isEmpty()) {
      res.add(stack.pop());
    }
  
    return true;
  }
  
  /*
  深搜 过程中完成两个目标:
  1.判断是否有环 2.把经过节点按照dfs postoder存起来
  使用两个set作为标记数组记录经过的点. isLoop用来判断是否有环,每次进入递归之前标记. 
  isLoop == true 说明在深搜的过程中又一次访问到该点,并不是回溯的过程 -> 有环  
  visited用来判断回溯的过程中经过了的节点,在递归之后标记. visited == true 证明在回溯的路上
  访问过这个点 -> 不是因为环 
  */
  private boolean dfs(Graph di, Node curr, Set<Node> isLoop,
                      Set<Node> visited, Stack<Node> stack) {
    if (visited.contains(curr)) return true;
    if (isLoop.contains(curr)) return false;
    isLoop.add(curr);  //递归前标记
    for (Node neibor : di.adj.get(curr)) {
      if (!dfs(di, neibor, isLoop, visited, stack)) return false;
    }
    visited.add(curr); //递归后标记
    stack.push(curr);  //dfs postorder
    return true;
  }
  
  public Iterable<Node> getRes() {
    return res;
  }
}
