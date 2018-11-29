package breadth_first;

import java.util.ArrayDeque;
import java.util.ArrayList;

import abstracted.Pathfinding;
import gui.GridInterface;

public class BreadthFirstPathfinding extends Pathfinding<BreadthFirstVertex, ArrayDeque<BreadthFirstVertex>> {
	boolean fromStart = true; // indicates which direction to look at (since it's bi-directional)
	ArrayDeque<BreadthFirstVertex> openEnd;
	int hit1, hit2; // two vertices that hit, indicating a solution
	
	public BreadthFirstPathfinding(int start, int target, boolean[] obstacles, boolean orthogonal) {
		super(start, target, obstacles, orthogonal);
		
		map = new BreadthFirstVertex[GridInterface.GRID_X * GridInterface.GRID_Y];
		for (int i = 0; i < map.length; i++) {
			map[i] = new BreadthFirstVertex(i);
			if (obstacles != null) {
				map[i].isObstacle = obstacles[i];
			}
		}
		
		open = new ArrayDeque<BreadthFirstVertex>();
		openEnd = new ArrayDeque<BreadthFirstVertex>();
		init(start);
	}
	
	@Override
	public void init (int start) {
		map[start].evaluated = true;
		map[start].isSolution = true;
		map[start].parentID = -1;
		map[start].fromStart = true;
		open.add(map[start]);
		

		map[target].evaluated = true;
		map[target].isSolution = true;
		map[target].parentID = -1;
		map[target].fromStart = false;
		openEnd.add(map[target]);
	}
	
	public boolean step() {
		passes++;
		ArrayDeque<BreadthFirstVertex> openToUse = fromStart ? open : openEnd;
		if (!openToUse.isEmpty()) {
			BreadthFirstVertex n = openToUse.poll();
			
			// loop through neighbours
			for (BreadthFirstVertex adj : adjacents(n.id)) {
				if (!adj.evaluated) {
					adj.evaluated = true;
					adj.parentID = n.id;
					adj.fromStart = fromStart;
					openToUse.add(adj);
				} else if (adj.fromStart != n.fromStart) {
					hit1 = n.id;
					hit2 = adj.id;
					lockIn();
					return true;
				}
			}
			
			// mark self
			n.marked = true;
			
			fromStart = !fromStart;
			return false;	
		}
		
		return true;
	}

	protected void lockIn() {
		int search = hit1;
		pathLength = 0;
		while (search != -1) {
			map[search].isSolution = true;
			if (map[search].parentID != -1) // to avoid counting dist(start, -1)
				pathLength += dist(search, map[search].parentID);
			search = map[search].parentID;
		}
		search = hit2;
		while (search != -1) {
			map[search].isSolution = true;
			if (map[search].parentID != -1) // to avoid counting dist(target, -1)
				pathLength += dist(search, map[search].parentID);
			search = map[search].parentID;
		}
		pathLength += dist(hit1, hit2);

		open.clear();
		openEnd.clear();
		solved = true;
	}

	private int dist(int id, int id2) {
		boolean orth = (id % GridInterface.GRID_X == id2 % GridInterface.GRID_X) || (id / GridInterface.GRID_X == id2 / GridInterface.GRID_X);
		int dist = orth ? 10 :  14;
		return dist;
	}
	
	@Override
	public void reset() {
		super.reset();
		openEnd.clear();
		hit1 = 0;
		hit2 = 0;
	}
	
	protected ArrayList<BreadthFirstVertex> adjacents(int n) {
		ArrayList<BreadthFirstVertex> adj = new ArrayList<BreadthFirstVertex>();
		int nx = n % GridInterface.GRID_X;
		int ny = n / GridInterface.GRID_X;
		
		for (int x = nx - 1; x <= nx + 1; x++) {
			for (int y = ny - 1; y <= ny + 1; y++) {
				if (x >= 0 && y >= 0 && x < GridInterface.GRID_X && y < GridInterface.GRID_Y) {
					if (!(x == nx && y == ny)) {
						if (!(orthogonal && !(x == nx || y == ny))) {
							BreadthFirstVertex v = map[x + y * GridInterface.GRID_X];
							if (!v.isObstacle)
								adj.add(v);
						}
					}
				}
			}
		}
		
		return adj;
	}

	@Override
	public String getDoneMsg() {
		return "Bi-directional breadth-first -- PathLength: " + pathLength + " Passes: " + passes;
	}
}
