package sojourner;

import java.util.ArrayList;
import java.util.Random;

public class FORD_FULKERSON {
	Vertex s;
	Vertex t;
	double flow;
	double bottleneck;
	Graph g;
	BFS bfs;
	public FORD_FULKERSON(Graph g, int a, int b){
		this.g = g;
		this.s = this.g.getVertexFromId(a);
		this.t = this.g.getVertexFromId(b);
		this.flow = 0;
	}
	public void augment(ArrayList<Edge> eTemp){
		// Retrieve the least weight edge from the set of edges (eTemp) from searched s-t path
		this.bottleneck = this.bfs.getMinimumWeightEdgeInSTPath();
		this.flow += this.bottleneck;
		for(Edge e : eTemp){
			// increase the flow (value of current flow) value with the current amount of flow (bottleneck)
			this.g.getEdgeObject(e.getFrom().getId(), e.getTo().getId()).increaseFlow(this.bottleneck);
			//e.increaseFlow(this.bottleneck);
			// flow == capacity => no more flow possible through this edge, hence remove it
			if(this.g.getEdgeObject(e.getFrom().getId(), e.getTo().getId()).getResidualCapacity() == 0){
				this.g.removeEdge(e.getFrom().getId(), e.getTo().getId());
			}
			// add a backward edge, if not already present (in which case increase flow value in the edge)
			this.g.addEdge(e.getTo().getId(), e.getFrom().getId(), this.bottleneck);
		}
		System.out.println("FORD_FULKERSON.augment: Flow: " + this.bottleneck + " ----- remove later");
	}
	/*
	 * Circular Flow situation in fractional flow
	 */
	public double augmentFractionFlow(ArrayList<Edge> eTemp){
		Random rand = new Random();
		// Retrieve the least weight edge from the set of edges (eTemp) from searched s-t path
		this.bottleneck = rand.nextDouble();//bfs.getMinimumWeightEdgeInSTPath();
		//this.flow += this.bottleneck;
		for(Edge e : eTemp){
			// increase the flow (value of current flow) value with the current amount of flow (bottleneck)
			e.increaseFlow(this.bottleneck);
			// flow == capacity => no more flow possible through this edge, hence remove it
			if(e.getResidualCapacity() == 0){
				g.removeEdge(e.getFrom().getId(), e.getTo().getId());
			}
			// add a backward edge, if not already present (in which case increase flow value in the edge)
			this.g.addEdge(e.getTo().getId(), e.getFrom().getId(), this.bottleneck);
		}
		System.out.println("FORD_FULKERSON.augment:28 Flow: " + this.bottleneck + " ----- remove later");
		return this.bottleneck;
	}
	/*
	 * Principal implementation of Ford-Fulkerson Algorithm, Kleinberg-Tardos: Chapter 7
	 */
	public void MAX_FLOW(){
		this.bfs = new BFS(this.g, this.s.getId());
		// search for s-t path
		bfs.performSearchNew(this.s.getId());
		// if s-t path found
		while(bfs.getPath(this.t.getId())){
			System.out.println(bfs.s_tPath());
			// construct Residual Graph 
			augment(bfs.getBFSPathEdges());
			// search for s-t path in Residual Graph
			bfs.performSearch();
		}
		System.out.println("Total Flow: " + this.flow);
	}
	/*
	 * NOT WORKING PROPERLY: Implementation of Ford-Fulkerson Algorithm, from a given flow state (intermediate state)
	 */
	public void MAX_FLOW_INTERMEDIATE(String currentFlow){
		this.bfs = new BFS(this.g, this.s.getId());
		this.g.setCurrentFlow(currentFlow);
		/*
		for(Edge eTemp : this.g.edg){
			this.flow += eTemp.getFlow();
		}
		*/
		// search for s-t path
		bfs.performSearchNew(this.s.getId());
		// if s-t path found
		while(bfs.getPath(this.t.getId())){
			System.out.println(bfs.s_tPath());
			// construct Residual Graph 
			augment(bfs.getBFSPathEdges());
			// search for s-t path in Residual Graph
			bfs.performSearch();
		}
		System.out.println("Total Flow: " + this.flow);
	}
	/*
	 * NOT WORKING PROPERLY: Ford-Fulkerson algorithm using Capacity Scaling
	 */
	public void MAX_FLOW_CAPACITY_SCALING(int factor){
		int minCap = getInitialScaling(factor);
		while(minCap >= 1){
			System.out.println("Scaling: " + minCap);
			this.g.formScalingSubgraph(minCap);
			this.bfs = new BFS(this.g, this.s.getId());
			bfs.performSearchOnActiveEdge(this.s.getId());
			while(bfs.getPath(this.t.getId())){
				System.out.println(bfs.s_tPath());
				// construct Residual Graph 
				augment(bfs.getBFSPathEdges());
				// search for s-t path in Residual Graph
				//gf = this.g.getScalingSubgraph(minCap);
				//this.bfs = new BFS(gf, this.s.getId());
				this.g.initializeState(this.s);
				bfs.performSearchOnActiveEdge(this.s.getId());
			}
			minCap /= factor;
		}
		System.out.println("Total Flow: " + this.flow);
	}
	private int getInitialScaling(int factor){
		int scale = 1;
		double max = 0;
		// find max outgoing edge capacity of s
		for(Edge eTemp : this.g.getAdjacentEdges(this.s.getId())){
			if(eTemp.getCapacity() > max){
				max = eTemp.getCapacity();
			}
		}
		while(true){
			int temp = scale * factor;
			if(temp > max){
				break;
			}
			else{
				scale = temp;
			}
		}
		return scale;
	}
	/*
	 * Ford-Fulkerson implementation to handle fractional flow
	 */
	public void MAX_FLOW_FRACTIONAL(){
		this.bfs = new BFS(this.g, this.s.getId());
		// search for s-t path
		bfs.performSearch();
		// if s-t path found
		while(bfs.getPath(this.t.getId())){
			System.out.println(bfs.s_tPath());
			// construct Residual Graph 
			augment(bfs.getBFSPathEdges());
			// search for s-t path in Residual Graph
			bfs.performSearch();
		}
		System.out.println("Total Flow: " + this.flow);
	}
	/*
	 * Max-Flow Min-Cut Theorem: Finding the Min-Cut
	 */
	public String MIN_CUT(){
		String cut = "";
		this.bfs = new BFS(this.g, this.s.getId());
		bfs.performSearch();
		cut += this.g.verticesReachable() + ", " + this.g.verticesUnreachable();
		return cut;
	}
}