package ex42;

import ds.BagX;
import ds.Seq;
import graph.AllTopologicalSorts;
import graph.DigraphX;
import graph.TopologicalX;

/* p597
  4.2.10  Given a DAG, does there exist a topological order that cannot result from ap-
  plying a DFS-based algorithm, no matter in what order the vertices adjacent to each
  vertex are chosen? Prove your answer.
  
  Sometimes. For example for the graph 0->1 the only topological order is found with DFS
  as shown below. But if a DAG is branched there will be an order unreachable with DFS. 
  For example for 1<-0->2->3 the order (0,2,1,3) is unreachable with DFS as shown below. 
  Thus sometimes a proof can be done with specific examples.
  
 */                                                   

public class Ex4210TopologicalOrderInDAGnotReachableUsingDFS {

  public static void main(String[] args) {
    
    DigraphX g = new DigraphX(2);
    g.addEdge(0,1);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    TopologicalX t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,1]
    
    g = new DigraphX(4);
    g.addEdge(0,1); g.addEdge(0,2); g.addEdge(2,3);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,1,2,3]
    
    g = new DigraphX(4);
    g.addEdge(0,1); g.addEdge(2,3); g.addEdge(0,2);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,1,2,3]
    
    g = new DigraphX(4);
    g.addEdge(0,2); g.addEdge(2,3); g.addEdge(0,1);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,2,3,1]
    
    g = new DigraphX(4);
    g.addEdge(0,2); g.addEdge(0,1); g.addEdge(2,3);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,2,3,1]
    
    g = new DigraphX(4);
    g.addEdge(2,3); g.addEdge(0,2); g.addEdge(0,1);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,2,3,1]
    
    g = new DigraphX(4);
    g.addEdge(2,3); g.addEdge(0,1); g.addEdge(0,2);
    System.out.println("\nadj="+(new Seq<BagX<Integer>>(g.adj())));
    System.out.println("allTopologicalSorts="+AllTopologicalSorts.allTopologicalSorts(g)); 
    // ((0,1,2,3),(0,2,1,3),(0,2,3,1))
    t = new TopologicalX(g);
    System.out.println("topologicalSortWithDFS="+t.order()); //[0,2,3,1]
    
  }

}



