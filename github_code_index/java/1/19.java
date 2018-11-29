package gradletest;

import java.util.LinkedList;
import java.util.Queue;

public class Bfs {
    
    public int longestExit(String[] maze, int startRow, int startCol, int[] moveRow, int[] moveCol) {
        
        int max = 0;
        int width = maze[0].length();
        int height = maze.length;
        int[][] chk = new int[height][width];
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                chk[i][j] = -1;
            }
        }
        
        chk[startRow][startCol] = 0;
        
        Queue<Integer> queueX = new LinkedList<>();
        Queue<Integer> queueY = new LinkedList<>();
        queueX.add(startRow);
        queueY.add(startCol);
        
        while (!queueX.isEmpty()) {
            int x = queueX.poll();
            int y = queueY.poll();
            
            for (int i = 0; i < moveRow.length; i++) {
                int nextX = x + moveRow[i];
                int nextY = y + moveCol[i];
                
                if (nextX < 0 || nextX >= height) continue;
                if (nextY < 0 || nextY >= width) continue;
                if (chk[nextX][nextY] != -1) continue;
                if (maze[nextX].charAt(nextY) == 'X') continue;
                
                queueX.add(nextX);
                queueY.add(nextY);
                chk[nextX][nextY] = chk[x][y] + 1;
            }
        }
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze[i].charAt(j) == '.' && chk[i][j] == -1) return -1;
                if (chk[i][j] > max) max = chk[i][j];
            }
        }
        
        return max;
    }

    public static void main(String[] args) {
        
        String[] maze = {".......","X.X.X..","XXX...X","....X..","X....X.","......."};
        int startRow = 5;
        int startCol = 0;
        int[] moveRow = {1,0,-1,0,-2,1};
        int[] moveCol = {0,-1,0,1,3,0};
        
        System.out.println(new Bfs().longestExit(maze, startRow, startCol, moveRow, moveCol));
    }
}
