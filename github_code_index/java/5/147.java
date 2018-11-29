public class DepthFirstSearch {
	
	private boolean[] marked; //tracks if dfs has been called for specific vertex
	private int count; //counts the number of marked vertices 
	
	public DepthFirstSearch(Graph G, int s){
		marked = new boolean[G.V()];	
		dfs(G,s); 
	}
	
	private void dfs(Graph G, int v){
		marked[v] = true; //marks passed vertex as true
		count++;
		//recursively go to each connected vertex of each vertex
		for (int w: G.adj(v)){
			if(!marked[w]){
				dfs(G,w);
			}
		}
	}
	
	//returns if a specific vertex has been marked
	public boolean marked(int w){
		return marked[w];
	}
	
	public int count(){
		return count;
	}
}
