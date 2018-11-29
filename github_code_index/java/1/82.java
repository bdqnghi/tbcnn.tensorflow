package graph;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class BreadthFirstSearch {
	private static final int INFINITY=Integer.MAX_VALUE;
	private boolean[] marked;
	private int[] edgeTo;
	private int[] distTo;
	
	public BreadthFirstSearch(Graph g,int s){
		marked=new boolean[g.countVertices()];
		distTo=new int[g.countVertices()];
		edgeTo=new int[g.countVertices()];
		for(int v=0;v<g.countVertices();v++)
			distTo[v]=INFINITY;
		bfs(g,new Node(s));
	}
	
	private void bfs(Graph g,Node n){
		Queue<Integer> q= new LinkedList<Integer>();
		marked[n.getId()]=true;
		distTo[n.getId()]=0;
		q.add(n.getId());
		while(!q.isEmpty()){
			int v=q.remove();
			for (Edge e:g.getOutboundForVertex(v)){
					int w=e.getEnd().getId();
					if(!marked[w]){
						edgeTo[w]=v;
						distTo[w]=distTo[v]+1;
						marked[w]=true;
						q.add(w);
					}
		
			}
		}
	} 
	
	
	
	
	
	

	public boolean hasPathTo(int v){
		return marked[v];
	}
	
	public int distTo(int v){
		return distTo[v];
	}
	
	public LinkedList<Integer> pathTo(int v){
		if(!hasPathTo(v)) return null;
		LinkedList<Integer> path=new LinkedList<Integer>();
		int x;
		for(x=v;distTo[x]!=0;x=edgeTo[x])
			path.add(x);
		path.add(x);
		return path;
	}
	
	
	
}

