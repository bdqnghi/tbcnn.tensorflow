import java.util.*;

class TopologicalSort{
 static LinkedList<Integer> arr[];
 static boolean visited[];
 static Stack<Integer> stack;
 TopologicalSort(int v){
  arr = new LinkedList[v];
  visited = new boolean[v];
  stack = new Stack<>();
  for(int i=0;i<v;i++){
   arr[i] = new LinkedList();
   visited[i] = false;
  }
 }
 public void addEdge(int src, int dest){
  arr[src].add(dest);
 }
 public void sort(int i){
  visited[i] = true;
  Iterator<Integer> ite = arr[i].listIterator();
  while(ite.hasNext()){
   int item = ite.next();
   if(!visited[item]){
     sort(item);
   }
  }
  stack.push(i);
 }
 public static void main(String[] args){
  System.out.println("Enter number of vertices");
  Scanner sc = new Scanner(System.in);
  int nov = sc.nextInt();
  TopologicalSort ts = new TopologicalSort(nov);
  System.out.println("Enter number of edges");
  int noe = sc.nextInt();
  System.out.println("Enter source and destination of edge");
  for(int i=0;i<noe;i++){
  int src=sc.nextInt();
  int dest = sc.nextInt();
  ts.addEdge(src, dest);
  }
  Iterator<Integer> ite;
 for(int i=0;i<nov;i++){
  ite = arr[i].listIterator();
  if(!visited[i]){
    ts.sort(i);
   }
  }
 System.out.println("Sorted vertices");
 while(!stack.isEmpty()){
    System.out.println(stack.pop());
  }
 }
}
