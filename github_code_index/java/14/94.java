import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.StringTokenizer;


public class B 
{
	static class Scanner
	{
		BufferedReader br;
		StringTokenizer st;
		
		public Scanner()
		{
	    	System.setOut(new PrintStream(new BufferedOutputStream(System.out), true));
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		
		public String next()
		{
			while(st == null || !st.hasMoreTokens())
			{
				try { st = new StringTokenizer(br.readLine()); }
				catch(Exception e) { throw new RuntimeException(); }
			}
			return st.nextToken();
		}

		public int nextInt()
		{
			return Integer.parseInt(next());
		}
		
		public double nextDouble()
		{
			return Double.parseDouble(next());
		}
		
		public String nextLine()
		{
			st = null;
			try { return br.readLine(); }
			catch(Exception e) { throw new RuntimeException(); }
		}
		
		public boolean endLine()
		{
			try 
			{
				String next = br.readLine();
				while(next != null && next.trim().isEmpty())
					next = br.readLine();
				if(next == null)
					return true;
				st = new StringTokenizer(next);
				return !st.hasMoreTokens();
			}
			catch(Exception e) { throw new RuntimeException(); }
		}
	}
	
	static int query(ArrayList <Integer> tree, int a, int b) 
	{
		if (a == 0)
		{
			int sum = 0;
			for (; b >= 0; b = (b & (b + 1)) - 1)
				sum += tree.get(b);
			return sum;
		} 
		else
			return query(tree, 0, b) - query(tree, 0, a-1);
	}
	
	static void increase(ArrayList <Integer> tree, int k, int inc) 
	{
		for (; k < tree.size(); k |= k + 1)
			tree.set(k, tree.get(k) + inc);
	}
	
	public static void main(String[] args)
	{
		Scanner sc = new Scanner();
		while(!sc.endLine())
		{
			int n = sc.nextInt();
			ArrayList <Integer> subida = new ArrayList <Integer> (n + 1);
			ArrayList <Integer> bajada = new ArrayList <Integer> (n + 1);
			for(int i = 0; i < n + 1; i++)
			{
				subida.add(0);
				bajada.add(0);
			}
			long[] res = new long[n];
			int[] vals = new int[n];
			for(int i = 0; i < n; i++)
			{
				vals[i] = sc.nextInt();
				res[i] = query(subida, vals[i] + 1, n);
				increase(subida, vals[i], 1);
			}
			long total = 0;
			for(int i = n - 1; i >= 0; i--)
			{
				if(vals[i] + 1 <= n)
					res[i] *= query(bajada, 0, vals[i] - 1);
				increase(bajada, vals[i], 1);
				total += res[i];
			}
			System.out.println(total);
		}
	}

}
