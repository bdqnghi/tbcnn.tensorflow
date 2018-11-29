package solver;

import java.awt.Point;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

public class BreadthFirstSearch extends AbstractSolver {
	

	@Override
	public List<Point> solve(int[][] maze, Point start, Point goal) {
		Queue<List<Point>> agenda = new LinkedList<>();
		List<Point> startPath = new ArrayList<Point>();
        startPath.add(start);
        agenda.add(startPath);
		Set<Point> pointsVisited = new HashSet<>();
	
		
		while(!agenda.isEmpty()) {
			List<Point> existingPath = agenda.poll();
			Point existingPoint = existingPath.get(existingPath.size()-1);
			if(existingPoint.equals(goal)) {
				return existingPath;
			}
			pointsVisited.add(existingPath.get(existingPath.size()-1)); 
			for (Point neighbour: getNeighbours(existingPoint,maze)) {
				if(!pointsVisited.contains(neighbour)) {
					List<Point> newPath = new ArrayList<>();
					newPath.addAll(existingPath);
					newPath.add(neighbour);
					agenda.add(newPath);
				}
				
				
			}
			
				
			
		}
		return null;
	}

}
