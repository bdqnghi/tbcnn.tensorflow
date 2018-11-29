import java.util.*;
/*Given a Directed and Acyclic Graph having N vertices and M edges, 
print topological sorting of the vertices.
If there are multiple ordering print the lexicographically smallest one.
Question for practice : https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/
*/

class TopologicalSort
{
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int t,v,e,i,x,y;
		t = sc.nextInt();
		while(t-- > 0)
		{
			v = sc.nextInt();
			e = sc.nextInt();
			ArrayList<PriorityQueue<Integer>> adjl = new ArrayList<PriorityQueue<Integer>>();
			for(i=0;i<=v;i++)
				adjl.add(new PriorityQueue<Integer>());
			for(i=0;i<e;i++)
			{
				x = sc.nextInt();
				y = sc.nextInt();
				adjl.get(x).add(y);
			}	
			Stack<Integer> topo = topoSort(adjl);
			while(!topo.isEmpty())
			{
				System.out.print(topo.pop()+" ");
			}
			pr("");
		}
	}
	//Getting topological order
	static Stack<Integer> topoSort(ArrayList<PriorityQueue<Integer>> adjl)
	{
		int i, v = adjl.size(),x,y,visitedCount = 0,time = 0;
		boolean isVisited[] = new boolean[v];//checking whether vertex is visited or not
		Stack<Integer> topo = new Stack<Integer>();//Storing final topological order
		int fin_time[] = new int[v];
		Stack<Integer> dfs = new Stack<Integer>();//using this for dfs traversal
		PriorityQueue<Integer> pq;
		dfs.push(v-1);
		while(!dfs.isEmpty())
		{
			x = dfs.pop();
			if(!isVisited[x])
			{
				dfs.push(x);
				++time;
				pq = adjl.get(x);
				while(!pq.isEmpty())
				{
					y = pq.poll();
					if(!isVisited[y])
						dfs.push(y);
				}
				isVisited[x] = true;
				visitedCount++;
			}
			else
			{
				if(fin_time[x] == 0)
				{
					fin_time[x] = ++time;
					topo.push(x);
				}	
			}
			if(dfs.isEmpty() && visitedCount != (v-1))
			{
				for(i=1;i<v;i++)
					if(!isVisited[i])
						dfs.push(i);
			}
		}
		//pr(topo+" ");
		return topo;
	}
	//Printing function
	static void pr(String s)
	{
		System.out.println(s);
	}
}

/*
Input:
2
5 6
1 2
1 3
2 3
2 4
3 4
3 5
6 6
6 1
6 3
5 1
5 2
3 4
4 2
Output:
1 2 3 4 5
5 6 1 3 4 2
*/
