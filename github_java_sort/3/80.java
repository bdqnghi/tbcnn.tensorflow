import java.util.*;

class Graph
{
	private int v;
	private List<Integer>[] l;
	public Graph(int v)
	{
		this.v=v;
		l=new ArrayList[v];
		for(int i=0;i<v;i++)
		{	
			l[i]=new ArrayList<Integer>();
		}
	}

	public void addEdge(int src,int dest)
	{
		l[src].add(dest);
	}
	public void topologicalsortmethodutil(int i,boolean[] visited,Stack<Integer> stack)
	{
		visited[i]=true;
		for(int dest: l[i])
		{
			if(visited[dest]==false)
			{
				topologicalsortmethodutil(dest,visited,stack);
			}
		}
		stack.push(i);
	}

	public void topologicalsortmethod()
	{
		boolean[] visited=new boolean[v];
		for(int i=0;i<v;i++)
		{
			visited[i]=false;
		}
		Stack<Integer> stack=new Stack<Integer>();
		for(int i=0;i<v;i++)
		{
			if(visited[i]==false)
				topologicalsortmethodutil(i,visited,stack);
		}
		while(!stack.empty())
		{
			System.out.println(stack.pop());
		}
	}
}

class topologicalsort
{
	public static void main(String[] args) 
	{
		Graph g=new Graph(6);
		g.addEdge(5, 2);
		g.addEdge(5, 0);
		g.addEdge(4, 0);
		g.addEdge(4, 1);
		g.addEdge(2, 3);
		g.addEdge(3, 1);
		g.topologicalsortmethod();
	}
}