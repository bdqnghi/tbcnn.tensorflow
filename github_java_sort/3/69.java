package epi.graph;
import java.util.List;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;


public class TeamPhotoDay2 {
	public static void main(String[] args) {
 		List<GraphVertex> G = new ArrayList<>(3);
	    for (int i = 0; i < 3; i++) {
	      G.add(new GraphVertex());
	    }
	    G.get(0).edges.add(G.get(2));
	    G.get(1).edges.add(G.get(2));
	    
	    System.out.println(findLargestNumberTeams(G));

	    List<GraphVertex> G2 = new ArrayList<>();

	    G2.add(new GraphVertex(0));
	    G2.add(new GraphVertex(1));
	    G2.add(new GraphVertex(2));
	    G2.add(new GraphVertex(3));
	    G2.add(new GraphVertex(4));
	    G2.add(new GraphVertex(5));
	    G2.add(new GraphVertex(6));

	    G2.get(0).edges.add(G2.get(1));
	    G2.get(0).edges.add(G2.get(2));
	    G2.get(0).edges.add(G2.get(5));
	    G2.get(1).edges.add(G2.get(4));
	    G2.get(3).edges.add(G2.get(2));
	    G2.get(3).edges.add(G2.get(4));
	    G2.get(3).edges.add(G2.get(5));
	    G2.get(3).edges.add(G2.get(6));
	    G2.get(5).edges.add(G2.get(2));
	    G2.get(6).edges.add(G2.get(0));
	    G2.get(6).edges.add(G2.get(4));

	    System.out.println(buildTopologicalOrdering(G2));
	}


	public static int findLargestNumberTeams(List<GraphVertex> G) {
		Deque<GraphVertex> orderedVertices = buildTopologicalOrdering(G);

		return findLongestPath(orderedVertices);
	}

	public static Deque<GraphVertex> buildTopologicalOrdering(List<GraphVertex> G) {
		Deque<GraphVertex> orderedVertices = new LinkedList<>();

		for (GraphVertex v : G) {
			if (v.maxDistance == 0) {
				DFS(v, orderedVertices);
			} 
		}
		return orderedVertices;
	}

	public static void DFS(GraphVertex curr, Deque<GraphVertex> orderedVertices) {
		curr.maxDistance = 1;
		for (GraphVertex v : curr.edges) {
			if (v.maxDistance == 0) {
				DFS(v, orderedVertices);
			}
		}
		orderedVertices.addFirst(curr);
	}

	public static int findLongestPath(Deque<GraphVertex> orderedVertices) {
		int maxDistance = 0 ;

		while (!orderedVertices.isEmpty()) {
			GraphVertex u = orderedVertices.peekFirst();
			maxDistance = Math.max(maxDistance, u.maxDistance);
			
			for (GraphVertex v : u.edges) {
				v.maxDistance = Math.max(v.maxDistance, u.maxDistance + 1);
			}

			orderedVertices.removeFirst();
		}

		return maxDistance;
	}


	public static class GraphVertex {
		public List<GraphVertex> edges = new ArrayList<>();
		
		public int maxDistance = 0;

		
		public int id;

		GraphVertex() {

		}

		GraphVertex(int id) {
			this.id = id;
		}

		public String toString() {
			return id + "";
		}
  	}
}