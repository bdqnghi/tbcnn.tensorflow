import java.util.ArrayList;
import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class BaseballElimination {
	private int num;
	private ArrayList<String> teams;
	private int[] w,l,r;
	private int[][] g;
	
	public BaseballElimination(String filename) {
		// create a baseball division from given filename in format specified below
		In in = new In(filename);
		num = in.readInt();
		teams = new ArrayList<String>();
		w = new int[num];
		l = new int[num];
		r = new int[num];
		g = new int[num][num];
		for (int i = 0; i < num; i++) {
			teams.add(in.readString());
			w[i] = in.readInt();
			l[i] = in.readInt();
			r[i] = in.readInt();
			for (int j = 0; j < num; j++)
				g[i][j] = in.readInt();
		}
	}
	
	public int numberOfTeams() {
		// number of teams
		return num;
	}
	
	public Iterable<String> teams() {
		// all teams
		return teams;
	}
	
	public int wins(String team) {  
		// number of wins for given team
		isValid(team);	
		return w[teams.indexOf(team)];
	}
	
	public int losses(String team) {
		// number of losses for given team
		isValid(team);	
		return l[teams.indexOf(team)];
	}
	
	public int remaining(String team) {
		// number of remaining games for given team
		isValid(team);	
		return r[teams.indexOf(team)];
	}
	
	public int against(String team1, String team2) {
		// number of remaining games between team1 and team2
		isValid(team1); isValid(team2);
		return g[teams.indexOf(team1)][teams.indexOf(team2)];
	}
	
	public boolean isEliminated(String team) {
		// is given team eliminated?
		isValid(team);	
		FordFulkerson fordFulkerson = contruct(team);
		if (fordFulkerson == null) return true;
		for (int v = 0; v < (num-2)*(num-1)/2; v++)
			if (fordFulkerson.inCut(v)) return true;	
		return false;
	}
	
	public Iterable<String> certificateOfElimination(String team) {
		// subset R of teams that eliminates given team; null if not eliminated
		isValid(team);
		ArrayList<String> subset = new ArrayList<>();
		int t = teams.indexOf(team);
		if (isEliminated(team)) 
		{
			FordFulkerson fordFulkerson = contruct(team);
			if (fordFulkerson == null)
			{
				int max = w[t]+r[t];
				int index = 0;
				for (int i = 0; i < num; i++){
					if (w[i] > max) {
						max = w[i];
						index = i;
					}		
				}
				subset.add(teams.get(index));
				return subset;
			}	
			else
			{
				int G = (num-2)*(num-1)/2;
				//System.out.println(fordFulkerson.value());
				for (int v = G; v < G+num-1; v++){
					int i = v-G;
					if (i >= t) i++;
					if (fordFulkerson.inCut(v))
						subset.add(teams.get(i));
				}
				return subset;
			}
		}
		return null;
	}
	
	private FordFulkerson contruct(String team) {
		int t = teams.indexOf(team);	
		int V = (num-1)+(num-2)*(num-1)/2+2, G = (num-2)*(num-1)/2;
		int S = V-2, T = V-1;
		FlowNetwork network = new FlowNetwork(V);
		int vv = 0;
		l1:for (int i = 0; i < num; i++)
		{
			if (i == t) continue l1;
			l2:for (int j = i+1; j < num; j++)
			{
				if (j == t) continue l2;
				network.addEdge(new FlowEdge(S, vv, g[i][j]));
				//System.out.println("s->"+i+"-"+j+"("+vv+") "+g[i][j]);
				network.addEdge(new FlowEdge(vv, i>t?G+i-1:G+i, Double.POSITIVE_INFINITY));
				//int a = i>t?G+i-1:G+i;
				//System.out.println(i+"-"+j+"("+vv+")->"+i+"("+a+")");
				network.addEdge(new FlowEdge(vv, j>t?G+j-1:G+j, Double.POSITIVE_INFINITY));
				//int b = j>t?G+j-1:G+j;
				//System.out.println(i+"-"+j+"("+vv+")->"+j+"("+b+")");
				vv++;
			}
		}	
		for (int v = G; v < G+num-1; v++) {
			int i = v - G;
			if (i >= t) i++;
			if (w[t]+r[t]-w[i] < 0) return null;
			network.addEdge(new FlowEdge(v, T, w[t]+r[t]-w[i]));
			//int a = w[t]+r[t]-w[i];
			//System.out.println(i+"("+v+")->t "+a);
		}
		FordFulkerson fordFulkerson = new FordFulkerson(network, S, T);
		return fordFulkerson;
	}
	
	private void isValid(String team) {
		int t = teams.indexOf(team);
		if (t == -1) throw new IllegalArgumentException();
	}
	
	private void print() {
		StringBuffer s = new StringBuffer();
		for (int i = 0; i < num; i++) {
			s.append(String.format("%-3d ", i));
			s.append(String.format("%-14s", teams.get(i)));
			s.append(String.format("%-2d %-2d %-2d  ", w[i],l[i],r[i]));
			for (int j = 0; j < num; j++)
				s.append(g[i][j]+" ");
			s.append("\n");
		}
		System.out.println(s);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	    BaseballElimination division = new BaseballElimination("baseball/teams4a.txt");
	    division.print();
	    for (String team : division.teams()) {
	        if (division.isEliminated(team)) {
	        	StdOut.println(team + " is eliminated by the subset R = { ");
	            for (String t : division.certificateOfElimination(team)) {
	                StdOut.print(t + " ");
	            }
	            StdOut.println("}");
	           
	        }
	        else {
	            StdOut.println(team + " is not eliminated");
	        }
	    }
	}
}
