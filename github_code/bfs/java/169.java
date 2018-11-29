//Given a 2d grid map of '1's (land) and '0's (water), 
//count the number of islands. An island is surrounded by water and
// is formed by connecting adjacent lands horizontally or vertically. 
//You may assume all four edges of the grid are all surrounded by water.

//Example 1:

//11110
//11010
//11000
//00000
//Answer: 1

//Example 2:

//11000
//11000
//00100
//00011
//Answer: 3

//Credits:
//Special thanks to @mithmatt for adding this problem and creating all test cases.

public class Solution {
    public int numIslands(char[][] grid) {
        //key idea: breadth-first-search to start from the first 1,
        //then go for its 1-connection nb, from those 1-connection nbs
        //go to unvisited 2-connection nbs, and so on, 
        //until there is no more 1 to be added to that island,
        //change that island to a number other than 1 and 0.
        //Continue this for the next available island.
        if (grid.length == 0) //empty grid
           return 0;
        
        int numIslands = 0;
        int mark = 2;
        Integer[] position = getFirstOne(grid);
        while (position != null) {
              //identify an island starting with row and col stored in position
              identifyIsland(grid, position, mark);
              numIslands++;
              mark++;
              position = getFirstOne(grid);
        }
        return numIslands;
    }
    
    //we can also put the coordinates of the 1s of an island to
    //a linked list of pair object.
    void identifyIsland(char[][] grid, Integer[] start, int mark) {
        int row = start[0];
        int col = start[1];
        grid[row][col] = (char)(mark + '0');
        
        //queue is abstract and cannot be instantiated
        Queue<Integer[]> island = new LinkedList<Integer[]>();
        island.add(start); //island is like a queue
        //find the island starting from start using breadth-first-search
        
        Integer[] position; //unit means a single 1
        //difficulty: how to efficiently remove an 1 once it belongs to
        //an island? how to efficiently finding the remaining 1s?
        while (island.size() > 0) {
            //search for fresh 1s in the nbs
            position = island.remove();
            row = position[0];
            col = position[1];
            
            if (row > 0 && grid[row-1][col] == '1') //up nb
               process(grid, island, row-1, col, mark);
            if (row+1 < grid.length && grid[row+1][col] == '1') //down nb
               process(grid, island, row+1, col, mark);
            if (col > 0 && grid[row][col-1] == '1') //left nb
               process(grid, island, row, col-1, mark);
            if (col+1 < grid[0].length && grid[row][col+1] == '1')
               process(grid, island, row, col+1, mark);
        }
    }
    
    void process(char[][] grid, Queue<Integer[]> island, 
                int row, int col, int mark) {
         grid[row][col] = (char)(mark + '0');
         island.add(new Integer[]{row, col});
    }
   
    //Find the first one in the grid 
    Integer[] getFirstOne(char[][] grid) {
        for (int row = 0; row < grid.length; row++)
            for (int col = 0; col < grid[row].length; col++) {
                if (grid[row][col] == '1')
                   return new Integer[]{row, col};
            }
         return null;
    }
}
