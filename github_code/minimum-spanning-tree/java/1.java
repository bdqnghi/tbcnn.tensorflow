
public class MinimumSpanningTree 
{
	private static int[][] m_graph;
	private static boolean[] m_visited; //indicate whether the index is included in MST or not
	private static int[] m_parent; //Stores the indexes of of parent nodes in MST
	private static int[] m_key; //stores the keys as nodes get added to MST

	private static int getMinIndex()
	{
		//From the nodes not part of MST, add the node - v with the least key to MST
		int minIndex = -1;
		int minValue = Integer.MAX_VALUE;

		for(int i = 0; i < m_graph.length; i++)
		{
			if(!m_visited[i] && (m_key[i] < minValue))
			{
				minValue = m_key[i];
				minIndex = i;
			}
		}
		
		return minIndex;
	}
	
	//Prim's minimum spanning tree
	private static void minimumSpanningTree()
	{
		m_visited = new boolean[m_graph.length];
		m_key = new int[m_graph.length];
		m_parent = new int[m_graph.length];
		
		//indicate no nodes are part of MST (m_mst)
		//initialize the MST indexes are all 0 (m_parent)
		//initialize the keys of all vertexes to infinity (m_key)
		for(int i = 0; i < m_graph.length; i++)
		{
			m_visited[i] = false;
			m_parent[i] = 0;
			m_key[i] = Integer.MAX_VALUE;
		}
		
		//initialize the key of vertex-0 to zero
		m_key[0] = 0;
		m_parent[0] = 0;
		
		//while all the nodes are not part of MST
		for(int i = 0; i < m_graph.length; i++)
		{
			//from the nodes not part of MST, add the node - v with the least key to MST
			int v = getMinIndex();
			
			//update m_mst and m_parent			
			m_visited[v] = true;
			//m_parent[i] = v;
		
			//Update key value and parent index of the adjacent vertices of the picked vertex. Consider only those
            //vertices which are not yet included in MST
			for(int j = 0; j < m_graph.length; j++)
				if((m_graph[i][j] != 0) && (m_graph[i][j] < m_key[j]) && (!m_visited[j]))
				{
					m_parent[j] = v;
					m_key[j] = m_graph[v][j];
				}
			
				//if(m_visited[j])
				//	for(int k = 0; k < m_graph.length; k++) 
				//	{
				//		int vw_weight = m_graph[j][k];
				//		
				//		//(if existing weight on edge v-w is less key[w], update key[w]. else leave as-is
				//		if((vw_weight > 0) && (vw_weight < m_key[k]))
				//		{
				//			m_parent[k] = v;
				//			m_key[k] = vw_weight;
				//		}
				//	}
		}
	}
	
	public static void main(String[] args) 
	{		
		//Graph
		//
        //     2    3
        // (0)--(1)--(2)
        //  |   / \   |
        // 6| 8/   \5 |7
        //  | /     \ |
        // (3)-------(4)
        //       9 
		//
		m_graph = new int[][] {
			{0,2,0,6,0},
			{2,0,3,8,5},
			{0,3,0,0,7},
			{6,8,0,0,9},
			{0,5,7,9,0}
		};
		
		minimumSpanningTree();
		
		//print minimum spanning tree
		System.out.println("Edge      Weight");
		for(int i = 1; i < m_graph.length; i++)
			System.out.println(m_parent[i] + " - " + i + "       " + m_graph[i][m_parent[i]]);
	}
}
