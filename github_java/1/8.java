package �׷���;
/*
 * ������: 2017-07-21
 * ������: ����
 * ������: x
 * ������: x
 * ���� :BFS (Breadth-First Search)
 * ���� :
 *�׷����� ��ȸ�� ���ϰ��̴�. ��ȸ�� �׷����� ��� ��带 �湮.
 *BFS�� �ʺ� �켱 Ž���̴�.
 *���ɿ��� ���·� �湮�� �Ѵ�.
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/*
 * ť�� ���� �ʺ� �켱 Ž��. 
 * 1.���� ��带 cehck�ؼ� �̹� �湮�Ͽ��ٰ� ǥ���Ѵ�.
 * 2.��߳�带 ť�� �ִ´�.
 * 3.ť�� ������ while ����. ������� ��  uncheck�� ���� üũ�ϰ�, ť�� �ִ´�.
 * 
 * �Է�:����/������ �׷��� G=(E,V)�� ��߳�� s��V
 * ��� :��� ��� V�� ���Ͽ�
 * d[v]:s-v���� �ִܰ���� ����(Edge ����)
 * ��[v]:s-v���� �ִܰ�λ󿡼� v�� �������
 */
public class BFS
{
	SimplexBFS simplexBFS;
	MultiplexBFS multiplexBFS;
	public static final int SIMPLEX=0;
	public static final int MULTIPLEX=1;
	
	
	Queue<Integer> queue;
	ArrayList<Integer> []Array;
	int[] vertex;
	boolean[] checked;
	
	public BFS()
	{
		queue = new LinkedList();				
		//queue=new Queue<Integer>();		
	}

	public BFS(int v,int type){
		if(type==MULTIPLEX)
		multiplexBFS =new MultiplexBFS(v);
		else
		simplexBFS = new SimplexBFS(v);
			
	}
	
	public void addEdge_sim(int v,int w){
		simplexBFS.addEdge(v, w);
	}
	    
	public void start_SimplexDFS(int v){
		simplexBFS.BFS(v);
	
	}
		
		 
	public void addEdge_mul(int v,int w){
		multiplexBFS.addEdge(v, w);
	}
	    
	public void start_MultiplexDFS(int v){
		multiplexBFS.BFS(v);
	
	}
		
	
	public void insert(int size,int [][]edge)
	{
		for(int i=0;i<size;i++)
		{
			Array[edge[i][0]].add(edge[i][1]);
			Array[edge[i][1]].add(edge[i][0]);
		}
		
	}
	
	public void BFS_Check(int start,int size,int [][]edge)
	{
		Array = new ArrayList[size];
		checked = new boolean[size];
		for(int i=0;i<5;i++)
		{
			Array[i] =new ArrayList<Integer>();
		}
		
				
		insert(size,edge);
		queue.offer(start);
		checked[start] = true;				
		while(!queue.isEmpty())
		{
			int nowVertex = queue.poll();
			System.out.print("["+nowVertex+"]");
			for(int i=0;i<Array[nowVertex].size();i++)
			{
				if(checked[Array[nowVertex].get(i)]==false)
				{
					queue.offer(Array[nowVertex].get(i));
					checked[Array[nowVertex].get(i)]=true;
				}
			}
		//	Array[nowVertex].size()
			
		}
		
		
	}
	class SimplexBFS{
		private int V;
		private LinkedList<Integer> adj[];
		Queue<Integer> que;
		SimplexBFS(int v) {
			
			V=v;
			que= new LinkedList<Integer>();
			adj = new LinkedList[V];
			for(int i=0;i<V;i++)
				adj[i]=new LinkedList();
			// TODO Auto-generated constructor stub
		}
		
		  void addEdge(int v, int w)
		    {
		        adj[v].add(w);  		       
		    }
		 
		    void BFSUtil(int v,boolean visited[])
		    {
		    
		    	if(visited[v]!=true)
		    		System.out.print(v+" ");
		    	
		        visited[v] = true;
		 
		        LinkedList<Integer> list = adj[v];
		        
		 		        
		        for(int i=0;i<list.size();i++){	        	        	
		        	 if (!visited[list.get(i)]){
		        		 System.out.print(list.get(i)+" ");
		        		 visited[list.get(i)]=true;
		        		 que.offer(list.get(i));
		        	 }
		        }
		        for(int i=0;i<que.size();i++){
		        	int nowvertex=que.poll();
		        	BFSUtil(nowvertex, visited);
		        }
		        
		       		   
		    }
		 
		    void BFS(int v)
		    {
		        boolean visited[] = new boolean[V];		        
		        que.offer(v);
		        
		        BFSUtil(que.poll(), visited);
		    }	
	}
	
	class MultiplexBFS{
		private int V;
		private LinkedList<Integer> adj[];
		Queue<Integer> que;
		MultiplexBFS(int v) {
			
			V=v;
			que= new LinkedList<Integer>();
			adj = new LinkedList[V];
			for(int i=0;i<V;i++)
				adj[i]=new LinkedList();
			// TODO Auto-generated constructor stub
		}
		
		  void addEdge(int v, int w)
		    {
		        adj[v].add(w);  
		        adj[w].add(v);
		    }
		 
		    void BFSUtil(int v,boolean visited[])
		    {
		    
		    	if(visited[v]!=true)
		    		System.out.print(v+" ");
		    	
		        visited[v] = true;
		 
		        LinkedList<Integer> list = adj[v];
		        
		 		        
		        for(int i=0;i<list.size();i++){	        	        	
		        	 if (!visited[list.get(i)]){
		        		 System.out.print(list.get(i)+" ");
		        		 visited[list.get(i)]=true;
		        		 que.offer(list.get(i));
		        	 }
		        }
		        for(int i=0;i<que.size();i++){
		        	int nowvertex=que.poll();
		        	BFSUtil(nowvertex, visited);
		        }
		        
		       		   
		    }
		 
		    void BFS(int v)
		    {
		        boolean visited[] = new boolean[V];		        
		        que.offer(v);
		        
		        BFSUtil(que.poll(), visited);
		    }	
		
	}
	
	
	public static void main(String[] args)
	{
		
		/*
		BFS bfs = new BFS();
		int start = 1;
		int edgeSize=6;
		int vertex=5;
		int [][]edge =
			{
					{0,1},
					{0,2},
					{1,3},
					{2,3},
					{2,4},
					{3,4}
			};
	
		bfs.BFS_Check(start,edgeSize, edge);
		
		*/
		
    	BFS bfs= new BFS(5,SIMPLEX);
    	
    	bfs.addEdge_sim(0, 1);
    	bfs.addEdge_sim(0, 2);
    	bfs.addEdge_sim(0, 4);
    	bfs.addEdge_sim(1, 2);
    	bfs.addEdge_sim(2, 0);
    	bfs.addEdge_sim(2, 3);
    	bfs.addEdge_sim(4, 3);
    	bfs.addEdge_sim(3, 4);
    
    	System.out.println("�ܹ��� BFS������ ����.");
    	bfs.start_SimplexDFS(1);
 
     	BFS bfs2= new BFS(5,MULTIPLEX);
    	bfs2.addEdge_mul(0, 1);
    	bfs2.addEdge_mul(0, 2);
    	bfs2.addEdge_mul(1, 3);
    	bfs2.addEdge_mul(2, 3);
    	bfs2.addEdge_mul(2, 4);
    	bfs2.addEdge_mul(3, 4);
   
    	System.out.println("\n����� BFS������ ����.");
    	bfs2.start_MultiplexDFS(1);
	}
	
}
