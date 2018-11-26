     //边的表示
public class Edge implements Comparable<Edge>{
	public final int v;
	public final int w;
	public final double weight；
	public Edge(int v,int w,double weight){
		this.v=v;
		this.w=w;
		this.weight=weight;
	}

	public double weight(){
		return weight;
	}

	public int either(){
		return v;
	}
	public int other(int vertex){
		if(vertex == v) return w;
		else if(vertex == w) return v；
		else throw new RuntimeException("Inconsistent edge");
	}

	public int compareTo(Edge that){
		if(this.weight()<that.weight) return -1;
		else if(this.weight()>that.weight()) return 1;
		else return 0 ;
	}

	public String toString(){
		return String.format("%d-%d %.2f",v,w,weight);
	}
}


   //图的表示,保存了所有顶点和所有的边所构成的一幅图,接下去在prims算法中构造一个MST,(从一幅图中重构一幅MST)
   //所有lazy algorithm的核心在于 Ⅰ 保存切分,和判定权重,

public class EdgeWeightedGraph{
	public final int V；
	private int E;
	private Bag<Edge>[] adj;

	EdgeWeightedGraph(int v){
		this.V=V;
		this.E=0;
		adj =(Bag<Edge>[]) new Bag[V];
		for(int v = 0 ; v < V ; v++){
			adj[v] = new Bag<Edge>();
		}
	}

	EdgeWeightedGraph(In in){
		//see 练习4.3.9
	}

	public int V(){ return V;}
	public int E(){ return E;}

	public void addEdge(Edge e){//这个要着重看下很重要哦,这个才是图形成的关键
		int v = e.either();w=e.other();
		adj[v].add(e);
		adj[w].add(e);
		E++;
	}

	public Iterable<Edge> adj(int v){
		return adj[v];
	}

	public Iterable<Edge> edges(){}//图的所有边

	public String toString(){}
}

   //最小生成树

public class MST{
	public MST(EdgeWeightedGraph G){

	}

	public Iterable<Edge> edges(){}//all edges in MST

	public double weight(){}//MST total weights
}


   //prim算法
public class LazyPrimMST{
	private boolean[] marked;
	private Queue<Edge> mst;
	private MinPQ<Edge> pq;

	public void visit(EdgeWeightedGraph G,int v){
		marked[v]=true;
		for(Edge e:G.adj[v]){
			if(!marked[e.other(v)]) pq.insert(e);
		}
	}

	public LazyPrimMST(EdgeWeightedGraph G){
		pq = new MinPQ<Edge>();
		marked=new boolean[G.V()];
		mst = new Queue<Edge>();
		
		visit(G,0);
		while(!pq.isEmpty()){
			Edge e = pq.delMin();
			int v = e.either(); int w = e.other(v);
			if(marked[v] && marked[w]) continue;
			mst.enqueue(e);
			if(!marked[v]) visit(G,v);
			if(!marked[w]) visit(G,w);
		}
	}

	public Iterable<Edge> edges(){
		return mst;
	}

	public double weight()
}

public class LazyPrimMST{
	private boolean[] marked;
	private Queue<Edge> mst;
	private MinPQ<Edge> pq;

	public LazyPrimMST(EdgeWeightedGraph G){
		pq = new MinPQ<Edge>();
		marked = new boolean[G.V()];
		mst = new Queue<Edge>();

		//从起点开始 visit(G,0);
		visit(G,0);//标记顶点v并将所有连接v和未被标记的顶点的遍加入pq

		while(!pq.isEmpty()){
			Edge e = pq.delMin();//从PQ中得到权重最小的边 , Ⅰ 判定权重
			int v = e.either(), w = e.other(v);
			if(marked[v] && marked[w]) continue;//跳过失效的边
			mst.enqueue(e);//将边添加到树中
			if(!marked[v]) visit(G,v);//顶点v or w 添加到树中
			if(!marked[w]) visit(G,w);
		}
	}


	private void visit(EdgeWeightedGraph G , int v){
		marked[v] = true;//标记顶点v并将所有连接v和未被标记的顶点的遍加入pq
		for(Edge e:G.adj(v)){
			if(!marked[e.other(v)]) pq.insert(e);
		}
	}

	public Iterable<Edge> edges(){
		return mst;
	}

	public double weight(){ // exercise 4.3.31}
}


  //最小生成树 测试用例

public static void main(String[] args){
	In in = new In(args[0]);
	EdgeWeightedGraph G;
	G = new EdgeWeightedGraph(in);
	MST mst = new MST(G);
	for(Edge e:mst.edges()){
		StdOut.println(e);
		StdOut.println(mst.weight);
	}
}




//对lazy prim算法的改进  当我们将顶点v添加到mst中后,发现w其实和mst距离更近了
//
//在这个算法中,第一我们发现:失效的边做了无用功啊,也就是下面这段代码执行消耗了时间
//          Edge e = pq.delMin();//从PQ中得到权重最小的边 , Ⅰ 判定权重
//          int v = e.either(), w = e.other(v);
//			if(marked[v] && marked[w]) continue;


//prim算法的及时实现 eager implemention 
//IndexMinPQ 索引优先队列的问题

public class PrimMST{
	private Edge[] edgeTo;
	private double[] distTo;
	private boolean[] marked;
	private IndexMinPQ<Double> pq;

	public PrimMST(EdgeWeightedGraph G){
		edgeTo = new Edge[G.V()];
		distTo = new double[G.V()];
		marked = new boolean[G.V()];
		for (int v = 0; v < G.V() ; v++ ) {
			distTo[v] =Double.Positive_INFINITY;

			pq = new IndexMinPQ<Double>(G.V());
			distTo[0]=0.0;
			pq.insert(0,0.0);
			while(!pq.isEmpty()){
				visit(G,pq.delMin());
			}
		}
	}

	private void visit(EdgeWeightedGraph G,int v){
		marked[v] = true;
		for(Edge e:G.adj(v)){
			int w = e.other(v);
			if(marked[w]) continue;
			if(e.weight < distTo[w]){
				edgeTo[w] = e;
				distTo[w] = e.weight();
				if(pq.contains(w)) pq.change(w,distTo[w]);
				else pq.insert(w,distTo[w]);
			}
		}
	}

	public Iterable<Edge> edges(){
		return mst;
	}
}



public void visit(EdgeWeightedGraph G,int v){
	marked[v]=w;
	for (EdgeWeightedGraph e:G.adj(v)) {
		int w = e.other(v);
		if(!marked[w]) continue;
		if(e.weight()<distTo[w]){

		}
	}
}



public EagePrimMST{
	private  Edge[] edgeTo;//距离树最近的边
	private double[] distTo;//distTo[w] = edgeTo[w].weight();
	private boolean[] marked;//如果v在MST中标记为true
	private IndexMinPq


	public PrimMST(EdgeWeightedGraph G){
		edgeTo = new Edge[G.V()];
		distTo = new double[G.V()];
		marked = new boolean[G.V()];
		for(int v = 0;  v < G.V() ;v++){
			distTo[v] =Double.Positive_INFINITY;
			pq = new IndexMinPQ<Double>(G.V());

			distTo[0]=0.0;
			pq.insert(0,0.0);//用顶点0和权重0.0初始化
			while(!pq.isEmpty()){
				visit(G,pq.delMin())	//将最近的顶点添加到树中
			}
		} 
	}

	private void visit(EdgeWeightedGraph G , int v){
		marked[v] = true;
		for(Edge e:G.adj(v)){
			int w = e.other(v);
			if(marked[w]) continue;
			if(e.weight()<distTo[w]){
				edgeTo[w] = e;
				distTo[w] = e.weight();
				if(pq.contains(w)) pq.change(w,distTo[w]);//
				else pq.insert(w,distTo[w]);
			}
		}
	}

	public Iterable<Edge> edges(){
		
	}

	public double weight(){

	}
} 


//kruskal算法  查找最小的mst;


public class kruskalMST{
	private Queue<Edge> mst;
	public kruskalMST(EdgeWeightedGraph G){
		mst = new Queue<Edge>();
		MinPQ<Edge> pq = new MinPQ<Edge>();
		for(Edge e:G.edges()) pq.insert(e);
		UF uf  = new UF(G.V());
		while(!pq.isEmpty()&&mst.size()<G.V()-1){
			Edge e = pq.delMin();
			int v = e.either();w = e.other(v);
			if(uf.connected(v,w)) continue;
			uf.union(v,w);
			mst.enqueue(e);
		}
	}

	public Iterable edges(){
		return mst;
	}

	public double weight(){

	}
}



//