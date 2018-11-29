import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.Stack;

public class DepthFirstSearch {
	
	public DepthFirstSearch( UndirectedGraph graph, int source )
	{
		this.marked_ = new boolean[ graph.VertexCount() ];
		this.pathFrom_ = new int[ graph.VertexCount() ];
		this.source_ = source;
		
		DfsImpl( graph, source );
	}
	
	boolean HasPathTo( int v )
	{
		return marked_[ v ];
	}
	
	@SuppressWarnings("unchecked")
	private void DfsImpl( UndirectedGraph graph, int source )
	{		
		Iterator<Integer>[] adj = ( Iterator<Integer>[] ) new Iterator[ graph.VertexCount() ];
        for ( int v = 0; v < graph.VertexCount(); v++ )
            adj[v] = graph.Adg(v).iterator();
		
		Stack< Integer > vertexes = new Stack< Integer >();
		marked_[ source ] = true;
		vertexes.push( source );
		
		
		while ( !vertexes.empty() )			
		{			
			int v = vertexes.peek();			
			
			if ( adj[ v ].hasNext() )
			{
				int w = adj[ v ].next();
				
				if ( !marked_[ w ] )
				{
					marked_[ w ] = true;
					pathFrom_[ w ] = v;
					vertexes.push( w );
				}
			}
			else
			{
				vertexes.pop();
			}
		}
	}
	
	public static void main(String[] args) 
	{		
		In in = new In( args[0] );
		UndirectedGraph graph = new UndirectedGraph( in );
		
		int source = Integer.parseInt( args[1] );
		
		DepthFirstSearch dfs = new DepthFirstSearch( graph, source );
	}
	
	private int source_;
	private boolean[] marked_;
	private int[] pathFrom_;
}