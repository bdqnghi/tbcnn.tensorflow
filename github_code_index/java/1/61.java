import java.util.LinkedList;
import java.util.Queue;

/*
 * Author: John Hossler
 *
 * This is the class which stores the graph, so it makes sense it is also the class
 *    which holds the search algorithm. That is why the breadth-first-search algorithm
 *    is inside this class, under BFS.
 */

public class Puzzle {

	private char[][] board; // Storing the board as a matrix of characters saves space
	private int width; // Stored width and height separately to allow for nonsquare matrices
	private int height;

  // getters and setters
	public int getHeight() { return height; }
	public int getWidth() { return width; }

	public char getItem(int x, int y) {
		if(x > width || x < 0 || y > height || y < 0) { return 0; }
		return board[x][y];
	}
	public void setItem(char a, int x, int y) {
		if(x > width || x < 0 || y > height || y < 0) { return; }
		board[x][y] = a;
	}

  public String search(String word) { // searches the puzzle for the word
    return BFS(word); // use Breadth-first-search to find the word
  }

	private String BFS(String word) {
		int[][] discovered = new int[width][height]; // int matrix to determine if discovered

		Queue<int[]> q = new LinkedList<int[]>(); // Queue of coordinates

		int x = 0, y = 0; // This could be used to adjust where the bfs starts
		q.add(new int[]{x,y}); // add the starting node

		while(!q.isEmpty()) {
			int test = 0; // test for first character
			int[] temp = q.remove(); // get coordinates to search
			x = temp[0]; // put in terms of x and y, cleaner
			y = temp[1];
			discovered[x][y] = 2; // marks the position as discovered

			if(board[x][y] == word.charAt(0)) {
				test = 1; // if the first character of word == the character being looked at, test = 1
			}

      // check all adjacent nodes to the node being searched
			for(int i = x-1; i <= x+1; ++i) {
				for(int j = y-1; j <= y+1; ++j) {
					if((i >= 0 && i < width) && (j >= 0 && j < height) && // if valid coordinate and
							!(i == x && j == y)) { // if not the coordinate being inspected
						if(test == 1 && // if first character == character being looked at and
								board[i][j] == word.charAt(1)) { // next char in word == next char in graph
							if(this.checkDir(word,x,y,i-x,j-y)) { // check that direction
								return this.getResults(word,x,y,i-x,j-y); // if true, return parsed string
							}
						}
						if(discovered[i][j] == 0) { // if undiscovered
							discovered[i][j] = 1; // mark discovered
							q.add(new int[]{i,j}); // add coordinates to queue
						}
					}
				}
			}
		}
    return null; // if word is never found, return null to say word is not in graph
	}

	public Puzzle(int x) { // init a square matrix
		width = x;
		height = x;
		board = new char[width][height];
	}

	public Puzzle(int x, int y) { // init a rectangular matrix
		width = x;
		height = y;
		board = new char[width][height];
	}

	private boolean checkDir(String word, int x, int y, int dx, int dy) { // check direction
		for(int i = 0; i < word.length(); ++i) { // check characters in the given direction
			if((x >= 0 && x < width) && (y >= 0 && y < height)) { // check if within bounds
				if(word.charAt(i) != board[x][y]) { // check if word isn't valid
					return false;
				}
			}
			else { // if the search goes out of bounds, return false.
				return false;
			}
			x += dx; // incrememnt x & y
			y += dy;
		}
		return true; // return true if no flaw was found
	}

  // parse results into a string that can be easily returned
	private String getResults(String word, int x, int y, int dx, int dy) {
		String direction = new String();

    // turn direction into a string
		int dir = dx * dy;
		if(dir == -1) { // dx == -dy, either sw or ne
			if(dx == -1) { direction = "sw"; } // dx = -1, dy = 1, sw
			else { direction = "ne"; } // dx = 1, dy = -1, ne
		}
		else if(dir == 1) { // dx == dy, either nw or se
			if(dx == -1) { direction = "nw"; } // dx = -1, dy = -1, nw
			else { direction = "se"; } // dx = 1, dy = 1, se
		}
		else { // dx == 0 || dy == 0, either n,e,s,w
			if(dx == 0) { // dx == 0, dy != 0, either n,s
				if(dy == -1) { direction = "n"; } // dy = -1, n
				else { direction = "s"; } // dy = 1, s
			}
			else { // dx != 0, dy == 0. either e,w
				if(dx == -1) { direction = "w"; } // dx = -1, w
				else { direction = "e"; } // dx = 1, e
			}
		}

    return (word+"("+(x+1)+","+(y+1)+","+direction+")");
	}
}
