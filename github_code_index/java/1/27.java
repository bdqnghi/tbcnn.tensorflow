import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class SAP {
   private Digraph graphSAP;
   
   // constructor takes a digraph (not necessarily a DAG)
   public SAP(Digraph G)
   {
       graphSAP = new Digraph(G);
   }

   // length of shortest ancestral path between v and w; -1 if no such path
   public int length(int v, int w)
   {
       if (!isValidVertex(v) || !isValidVertex(w))
           throw new java.lang.IndexOutOfBoundsException();
       BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths(graphSAP, v);
       BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths(graphSAP, w);
       int dist = Integer.MAX_VALUE;
       int ancestor = -1;
       for (int candidate = 0; candidate < graphSAP.V(); candidate++) {
          if (vBFS.hasPathTo(candidate) && wBFS.hasPathTo(candidate)) 
               if (vBFS.distTo(candidate) + wBFS.distTo(candidate) < dist) {
                   dist = vBFS.distTo(candidate) + wBFS.distTo(candidate);
                   ancestor = candidate;
               }
               
           
       }
       if (ancestor < 0)
           return -1;
       return dist;
   }

   // a common ancestor of v and w that participates in a shortest ancestral path; -1 if no such path
   public int ancestor(int v, int w)
   {
       if (!isValidVertex(v) || !isValidVertex(w))
           throw new java.lang.IndexOutOfBoundsException();
       BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths(graphSAP, v);
       BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths(graphSAP, w);
       int ancestor = -1;
       int dist = Integer.MAX_VALUE;
       for (int candidate = 0; candidate < graphSAP.V(); candidate++) {
           if (vBFS.hasPathTo(candidate) && wBFS.hasPathTo(candidate)) {
               if (vBFS.distTo(candidate) + wBFS.distTo(candidate) < dist) {
                   ancestor = candidate;
                   dist = vBFS.distTo(candidate) + wBFS.distTo(candidate);
               }
           }
       }
       return ancestor;
   }

   // length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
   public int length(Iterable<Integer> v, Iterable<Integer> w)
   {
       if (v == null || w == null)
           throw new java.lang.NullPointerException();
       BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths(graphSAP, v);
       BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths(graphSAP, w);
       int ancestor = -1;
       int dist = Integer.MAX_VALUE;
       for (int candidate = 0; candidate < graphSAP.V(); candidate++) {
           if (vBFS.hasPathTo(candidate) && wBFS.hasPathTo(candidate)) {
               if (vBFS.distTo(candidate) + wBFS.distTo(candidate) < dist) {
                   ancestor = candidate;
                   dist = vBFS.distTo(candidate) + wBFS.distTo(candidate);
               }
           }
       }
       if (ancestor < 0)
           return -1;
       return dist;
   }

   // a common ancestor that participates in shortest ancestral path; -1 if no such path
   public int ancestor(Iterable<Integer> v, Iterable<Integer> w)
   {
       if (v == null || w == null)
           throw new java.lang.NullPointerException();
       BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths(graphSAP, v);
       BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths(graphSAP, w);
       int ancestor = -1;
       int dist = Integer.MAX_VALUE;
       for (int candidate = 0; candidate < graphSAP.V(); candidate++) {
           if (vBFS.hasPathTo(candidate) && wBFS.hasPathTo(candidate)) {
               if (vBFS.distTo(candidate) + wBFS.distTo(candidate) < dist) {
                   ancestor = candidate;
                   dist = vBFS.distTo(candidate) + wBFS.distTo(candidate);
               }
           }
       }
       return ancestor;
   }
   private boolean isValidVertex(int v)
   {
       return (v >= 0 && v < graphSAP.V());
   }
   
   // do unit testing of this class
   public static void main(String[] args)
   {
       In in = new In("wordnet\\digraph3.txt");
       Digraph G = new Digraph(in);
       SAP sap = new SAP(G);
       int v = 10;
       int w = 3;
       int length   = sap.length(v, w);
       int ancestor = sap.ancestor(v, w);
       StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
   }
}