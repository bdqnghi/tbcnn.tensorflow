// ----------------------------------------------------------
/**
 * Breadth-First-Search using a Directed Graph
 *
 * ----------------------------------------------------------

 */

 public class DirectedBFS{

   //True if path from s to marked[v]
   private boolean[] marked;
   private int[] distTo;
   private int[] edgeTo;

   //Constructor marks vertices reachable from source
   public DirectedBFS(Digraph G, int s){
     marked = new boolean[G.V()];
     distTo = new int[G.V()];
     edgeTo = new int[G.V()];
     bfs(G, s);
   }

   //Recursively performs dfs
   private void bfs(Digraph G, int V){
     Queue<Integer> q = new Queue<Integer>();

     //Initialise all distances to infinity
     for(int v = 0; v < G.V(); v++)
      distTo[v] = INFINITY;

     //Process source(s) first
     distTo[s] = 0;
     marked[s] = true;
     q.enqueue(s);

     while(!q.isEmpty()){
       int v = q.dequeue();

       //Process vertices adjacent to v
       for(int w : G.adj(v)){
         if(!marked[w]){
           edgeTo[w] = v;
           distTo[w] = distTo[v] + 1;
           marked[w] = true;
           q.enqueue(w);
         }
       }
     }
   }

   public boolean visited(int v){
     return marked[v];
   }
 }
