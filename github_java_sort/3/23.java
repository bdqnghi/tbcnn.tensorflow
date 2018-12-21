

package com.mhhe.clrs2e;



public class TopoSort
{
    
    private SentinelDLL list;

    
    private class TopoSortDFS extends DFS
    {
	
	protected void finish(AdjacencyListGraph g, Vertex u)
	{
	    list.insert(u);
	}
    }    

    
    public Vertex[] topologicalSort(AdjacencyListGraph g)
    {
	list = new SentinelDLL(); 
	
	
	
	(new TopoSortDFS()).search(g);

	
	Vertex[] result = new Vertex[g.getCardV()];
	list.toArray(result);

	return result;
    }
}






