package chap4;

public class DepthFirstSearch implements Searchable
{
	private boolean[] visited;
	private int count;
	private int source;

	public DepthFirstSearch(Graph g, int source)
	{
		this.setSource(source);
		this.visited = new boolean[g.getV()];

		dfs(g, source);
	}

	private void dfs(Graph g, int v)
	{
		this.visited[v] = true;
		this.count++;

		for (int w : g.adj(v))
		{
			if (!this.marked(w))
			{
				dfs(g, w);
			}
		}
	}

	@Override
	public void setSource(int source)
	{
		this.source = source;
	}

	@Override
	public boolean marked(int dest)
	{
		return this.visited[dest];
	}

	@Override
	public int count()
	{
		return this.count;
	}

	public int getSource()
	{
		return source;
	}

}
