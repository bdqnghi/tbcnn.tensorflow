import java.util.Scanner;
import java.util.*;
class topologicalsort
{
	static LinkedList<Integer> list[];
	public static void main(String[]args)
	{
		Scanner scan=new Scanner(System.in);
		int t,i,j,k,l;
		// no of vertex
		int vertex=scan.nextInt();
		// no of edges
		int edges=scan.nextInt();
		list=new LinkedList[vertex];
		for(k=0;k<vertex;k++)
		{
			list[k]=new LinkedList();
		}
		for(i=0;i<edges;i++)
		{	
			int a=scan.nextInt();
			int b=scan.nextInt();
			list[a].add(b);
		}	
		boolean visited[]=new boolean[vertex];
		Stack stack=new Stack();
		for(j=0;j<vertex;j++)
		{
			visited[j]=false;
		}

		for(k=0;k<vertex;k++)
		{
			if(!visited[k])
			{
				topologicalutil(k,visited,stack);
			}
		}
		for(l=0;l<vertex;l++)
		{
			System.out.print(stack.pop()+" ");
		}
	}
	static void topologicalutil(int v,boolean visited[], Stack stack)
	{
		visited[v]=true;
		Iterator<Integer> it=list[v].iterator();
		int o;
		while(it.hasNext())
		{
			o=it.next();
			if(!visited[o])
			{
				topologicalutil(o,visited, stack);
			}
		}
		stack.push(v);
	}
}