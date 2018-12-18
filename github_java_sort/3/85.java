import java.util.ArrayList;

import edu.bilgics.GraphADT.*;





public class TopDfs {
	int time;
	IGraph g;
	ArrayList<IVertex> l=new ArrayList<IVertex>();
	public TopDfs() {
		
	}
	
	
	public static ArrayList<IVertex> getAllAdjacentVertices(IGraph g, IVertex v) {
		
		ArrayList<IVertex> res = new ArrayList<IVertex>();
		
		IEdge edge = null;
		try {
			try {
				edge = g.getFirstEdge();
			} catch (EmptyVerticeSetException e) {
				
				e.printStackTrace();
			}
			while (edge != null) {
				
				if (edge.getOriginatingVertex().equals(v)) {
					
					res.add(edge.getDestinationVertex());
				}
				
				try {
					edge = g.getNextEdge();
				} catch (EmptyVerticeSetException e) {
					
					e.printStackTrace();
				}
			}
		} catch (EmptyGraphException e) {
			
			e.printStackTrace();
		}

		return res;
	}
	
	
	public void dfsVisit(IVertex u){
		u.setColour("Gray");
		time=time+1;
		u.setDi(time);
		for(IVertex v : getAllAdjacentVertices(g, u)){
			if(v.getColour()=="White"){
				v.setPi(u);
				dfsVisit(v);
			}
		}
		u.setColour("Black");
		l.add(u);
		time=time+1;
		u.setF(time);
		
	}
	
	public void dfs(IGraph g){
		IVertex u;
		try {
			u=g.getFirstVertex();
			while(u!=null){
				u.setColour("White");
				u.setPi(null);
				u=g.getNextVertex();
			}
			time=0;
			u=g.getFirstVertex();
			while(u!=null){
				if(u.getColour()=="White"){
					dfsVisit(u);
				}
				u=g.getNextVertex();
			}
		} catch (Exception e) {
			
		}

	}
	
	
	public void topologicalSort(){
		dfs(g);
		
	}
	public static void main(String[] args) {
		IGraph graph1 = new Graph(); 
		
		IVertex A = new Vertex("A");
		IVertex B = new Vertex("B");
		IVertex C = new Vertex("C");
		IVertex D = new Vertex("D");
		IVertex E = new Vertex("E");
		IVertex F = new Vertex("F");
		try {
			graph1.addVertex(A);
			graph1.addVertex(B);
			graph1.addVertex(C);
			graph1.addVertex(D);
			graph1.addVertex(E);
			graph1.addVertex(F);	
		} catch (Exception e) {
			
		}
		IEdge AB = new Edge(A, B);
		IEdge AC = new Edge(A, C);
		IEdge BE = new Edge(B, E);
		IEdge BD = new Edge(B, D);
		IEdge ED = new Edge(E, D);
		IEdge CE = new Edge(C, E);
		IEdge DF = new Edge(D, F);
		IEdge CF = new Edge(C, F);
		
		try {
			graph1.addEdge(AB);
			graph1.addEdge(AC);
			graph1.addEdge(CE);
			graph1.addEdge(BD);
			graph1.addEdge(BE);
			graph1.addEdge(ED);
			graph1.addEdge(DF);
			graph1.addEdge(CF);
		} catch (Exception e) {
			
		}
		
		System.out.println(graph1);
		
		TopDfs t=new TopDfs();
		t.g=graph1;
		t.topologicalSort();
		String s="";
		for(int i=t.l.size()-1;i>=0;i--){
			s=s+" "+t.l.get(i);
		}
		
		System.out.println(s);	
		
		IGraph graph=new Graph();
		
		IVertex S=new Vertex("S");
		IVertex T=new Vertex("T");
		IVertex X=new Vertex("X");
		IVertex Y=new Vertex("Y");
		IVertex Z=new Vertex("Z");
		
		try {
			graph.addVertex(S);
			graph.addVertex(T);
			graph.addVertex(X);
			graph.addVertex(Y);
			graph.addVertex(Z);
		} catch (Exception e) {
			
		}
		
		IEdge ST=new Edge(S,T);
		IEdge SY=new Edge(S,Y);
		IEdge TX=new Edge(T,X);
		IEdge TY=new Edge(T,Y);
		IEdge YX=new Edge(Y,X);
		IEdge YZ=new Edge(Y,Z);
		IEdge XZ=new Edge(X,Z);
		
		try {
			graph.addEdge(ST);
			graph.addEdge(SY);
			graph.addEdge(TX);
			graph.addEdge(TY);
			graph.addEdge(YX);
			graph.addEdge(YZ);
			graph.addEdge(XZ);
			
		} catch (Exception e) {
			
		}
		System.out.println(graph);
		
		TopDfs t1=new TopDfs();

		t1.g=graph;
		t1.topologicalSort();
		String s1="";
		for(int i=t1.l.size()-1;i>=0;i--){
			s1=s1+" "+t1.l.get(i);
		}
		
		System.out.println(s1);			
		
		IGraph gr=new Graph();
		
		IVertex K=new Vertex("K");
		IVertex L=new Vertex("L");
		IVertex M=new Vertex("M");
		try {
			gr.addVertex(K);
			gr.addVertex(L);
			gr.addVertex(M);
		} catch (Exception e) {
			
		}
		IEdge KM=new Edge(K,M);
		IEdge KL=new Edge(K,L);
		try {
			gr.addEdge(KM);
			gr.addEdge(KL);
		} catch (Exception e) {
			
		}
		System.out.println(gr);
		
		TopDfs t2=new TopDfs();

		t2.g=gr;
		t2.topologicalSort();
		String s2="";
		for(int i=t2.l.size()-1;i>=0;i--){
			s2=s2+" "+t2.l.get(i);
		}
		
		System.out.println(s2);
		
	}

}
