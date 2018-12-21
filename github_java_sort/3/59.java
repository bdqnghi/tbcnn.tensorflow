import java.util.*;


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
	
	static Stack<Integer> topoSort(ArrayList<PriorityQueue<Integer>> adjl)
	{
		int i, v = adjl.size(),x,y,visitedCount = 0,time = 0;
		boolean isVisited[] = new boolean[v];
		Stack<Integer> topo = new Stack<Integer>();
		int fin_time[] = new int[v];
		Stack<Integer> dfs = new Stack<Integer>();
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
		
		return topo;
	}
	
	static void pr(String s)
	{
		System.out.println(s);
	}
}


