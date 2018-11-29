package mazesearch.cse.miamioh.edu;

import java.util.Collections;

public class DepthFirstSearch extends SearchStrategy {


	public DepthFirstSearch(Maze maze) {
		super(maze);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void solve() {
		explored.add(maze.getStart());
		
		dfs(new ParentSquare(maze.getStart(), null));
	}
	private void dfs(ParentSquare parentSquare){

		Square currentSquare = parentSquare.getCurrent();;
		
		//base case
		if(currentSquare.equals(maze.getGoal())){
			ParentSquare s = parentSquare;			
			while(s.getParent() != null){
				path.add(s.getCurrent());
				s = s.getParent();	
			}
			Collections.reverse(path);
			return;
		}
		explored.add(currentSquare);
		
		//check square one row up
		Square next = new Square(currentSquare.getRow() - 1, currentSquare.getColumn());
		if (!maze.isBlocked(next)&& !explored.contains(next)) {
			dfs(new ParentSquare(next, parentSquare));
			return;
		}

		// check square one row down
		next = new Square(currentSquare.getRow() + 1, currentSquare.getColumn());
		if (!maze.isBlocked(next)&& !explored.contains(next)) {
			dfs(new ParentSquare(next,parentSquare));
			return;
		}

		// check square one col up
		next = new Square(currentSquare.getRow(), currentSquare.getColumn()-1);
		if (!maze.isBlocked(next)&& !explored.contains(next)) {
			dfs(new ParentSquare(next, parentSquare));
			return;
		}

		// check square one col down
		next = new Square(currentSquare.getRow(), currentSquare.getColumn()+1);
		if (!maze.isBlocked(next)&& !explored.contains(next)) {
			dfs(new ParentSquare(next, parentSquare));
			return;
		}
		//go back one if there is a dead end
		dfs(parentSquare.getParent());

	}

}
