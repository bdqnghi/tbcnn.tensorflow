import java.util.LinkedList;


public class BFS
{
	private AdjacencyList g;
	private boolean[] visit;
	private int[] edgeTo;

	// private Stack<Integer> path;
	public BFS(AdjacencyList g)
	{
		this.g = g;
		this.visit = new boolean[g.getVertNum()];
		this.edgeTo = new int [g.getVertNum()];
	}

	public void setEverythingFalse()
	{
		for (int i = 0; i < this.visit.length; i++)
		{
			this.visit[i] = false;
		}
	}

	public void bfs(int v)
	{
		LinkedList <Integer> queue = new LinkedList<Integer>();
		queue.add(v);
		
		while(queue.size() > 0)
		{
			int n = queue.remove();
			for(int i : g.getVert(n))
			{
				if(!visit[i])
				{
					queue.add(i);
					visit[i] = true;
					this.edgeTo[n] = i;
				}
			}
		}
	}
	

	public boolean[] getvisit()
	{
		return visit;
	}

	public boolean connected(int a, int b)
	{
		bfs(a);
		return (visit[a] && visit[b]);
	}

	
	public int [] getEdgeTo()
	{
		return edgeTo;
	}
	
}
