package com.ashish.aac;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Stack;

public class FordFulkerson {

	static int n;
	int MAXSIZE = 51;
	int f[][] = new int[MAXSIZE][MAXSIZE];
	int residualCapacity[][] = new int[MAXSIZE][MAXSIZE] ;
	ArrayList path = new ArrayList();
	int p[] = new int[MAXSIZE];
	
	public FordFulkerson(Graph G, int s, int t)
	{
		
		
		
		
		
		
		for (int i=1;i<=n;i++)
		{
			
			for (int j=1;j<=n;j++)
			{
			if (G.adj[i][j]==1)
				f[i][j]=0;
				residualCapacity[i][j] = G.cf[i][j]-f[i][j];

				f[j][i]=0;
				residualCapacity[i][j] = G.cf[i][j]-f[i][j];

			}
		}
		while(hasAugmentingPath(G,s,t))
		{
			//System.out.println(hasAugmentingPath(G,s,t));
			path.clear();
			path.add(s);
			System.out.print("\n"+s);
			int j=s;
			while(j!=t)
			{
				System.out.print("-->"+p[j]);
				path.add(p[j]);
				j=p[j];
				
				
			}
			for(int i =1; i<=n;i++)
				System.out.print(" "+i+"-"+p[i]);
			
			int mincf = residualCapacity[(int) path.get(0)][(int) path.get(1)];
			for(int i=1;i<path.size()-1;i++)
			{	
				int x=(int) path.get(i);
				int y=(int) path.get(i+1);
				
				if (residualCapacity[x][y]<mincf)
					mincf=residualCapacity[x][y];
				
				
			}
				System.out.println("Minimum Capacity on the path "+mincf);
				
				for(int i=0;i<path.size()-1;i++)
				{	
					int x=(int) path.get(i);
					int y=(int) path.get(i+1);
					
					f[x][y]=f[x][y]+mincf;
					residualCapacity[x][y] = G.cf[x][y]-f[x][y];
					
					f[y][x]=-f[x][y];
					residualCapacity[y][x] = G.cf[y][x]-f[y][x];
	
				}
		}
		
		
	}
	
	private boolean hasAugmentingPath(Graph G, int s, int t) {
		// TODO Auto-generated method stub
		
		
		int visited[]= new int[MAXSIZE];
		
		for(int i = 1; i<MAXSIZE; i++)
			{
				visited[i]=0;
				p[i]=0;
			}
		
		Stack<Integer> q = new Stack<Integer>();
		q.push(s);
		System.out.println("\nDFS traversal for given graph is : ");

		while(!q.isEmpty())
		{
			int u =  q.pop();
			if(visited[u]==0)
			{
				System.out.print("\n"+u);
				visited[u]=1;
			}
			for (int i=1;i<=n;i++)
			{

				if((G.adj[u][i]==1) && (visited[i]==0) && (residualCapacity[u][i]>0) )
				{
					
					q.push(u);
					visited[i]=1;
					p[u]=i;
					if(i==t)
					{
						
						System.out.println("\nPath found!");
						return true;
					}
					u = i;
					i=1;
				}
			}
		}
		System.out.println("\nPath not found");		
		
		return false;
	}

	/**
	 * @param args
	 * @throws IOException 
	 * @throws NumberFormatException 
	 */
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader ( new InputStreamReader (System.in));
		
		System.out.println("Enter number of vertices");
		n=Integer.parseInt(br.readLine());
		
		Graph g = new Graph(n);
		g.createGraph();
		
		System.out.println("\nEnter the source node:");
		int s = g.getNumber();
		System.out.println("\nEnter the target node:");
		int t = g.getNumber();
		
		FordFulkerson ff = new FordFulkerson(g,s,t);
		
		System.out.println("\nFinal Residual Network with no augmenting path");
		
		System.out.print("\nCapacity Flow matrix for your graph is :\n");
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			System.out.print("     "+ff.f[i][j]+"/"+g.cf[i][j]);
			System.out.print("\n");
		}

		int maxflow=0;
		
		System.out.println("\n Max flow is: ");
		for(int i=1; i<=n;i++)
			if(g.adj[s][i]==1)
				maxflow=maxflow + ff.f[s][i];
		
		System.out.println(maxflow);

	}

}

