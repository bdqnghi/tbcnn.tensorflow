package chapter2.beginner.example6;

import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created by jsong on 11/04/2017.
 *
 * @hackerrank https://www.hackerrank.com/jsong00505
 * @backjoon https://www.acmicpc.net/user/jsong00505
 * @github https://github.com/jsong00505
 * @linkedin https://www.linkedin.com/in/junesongskorea/
 * @email jsong00505@gmail.com
 * @challenge Lake Counting(POJ No.2386)
 */
public class Solution {
  static char POOL = 'W';
  static char GROUND = '.';

  /**
   * find if there is a pool or not by dfs
   *
   * @param n
   * @param m
   * @param x
   * @param y
   * @param map
   * @param visited
   * @return an updated visited map
   */
  static boolean[][] depthFirstSearch(
      int n, int m, int x, int y, char[][] map, boolean[][] visited) {
    visited[x][y] = true;

    // upside
    if (x > 0) {
      // left
      if (y > 0) {
        if (map[x - 1][y - 1] == POOL && !visited[x - 1][y - 1]) {
          visited = depthFirstSearch(n, m, x - 1, y - 1, map, visited);
        }
      }

      // middle
      if (map[x - 1][y] == POOL && !visited[x - 1][y]) {
        visited = depthFirstSearch(n, m, x - 1, y, map, visited);
      }

      //right
      if (y < m - 1) {
        if (map[x - 1][y + 1] == POOL && !visited[x - 1][y + 1]) {
          visited = depthFirstSearch(n, m, x - 1, y + 1, map, visited);
        }
      }
    }

    // downside
    if (x < n - 1) {
      // left
      if (y > 0) {
        if (map[x + 1][y - 1] == POOL && !visited[x + 1][y - 1]) {
          visited = depthFirstSearch(n, m, x + 1, y - 1, map, visited);
        }
      }
      // middle
      if (map[x + 1][y] == POOL && !visited[x + 1][y]) {
        visited = depthFirstSearch(n, m, x + 1, y, map, visited);
      }

      // right
      if (y < m - 1) {
        if (map[x + 1][y + 1] == POOL && !visited[x + 1][y + 1]) {
          visited = depthFirstSearch(n, m, x + 1, y + 1, map, visited);
        }
      }
    }

    // left
    if (y > 0) {
      if (map[x][y - 1] == POOL && !visited[x][y - 1]) {
        visited = depthFirstSearch(n, m, x, y - 1, map, visited);
      }
    }

    // right
    if (y < m - 1) {
      if (map[x][y + 1] == POOL && !visited[x][y + 1]) {
        visited = depthFirstSearch(n, m, x, y + 1, map, visited);
      }
    }

    return visited;
  }

  /**
   * get a number of pools by dfs
   *
   * @param n
   * @param m
   * @param map
   * @return a number of pools
   */
  static int getNumberOfPools(int n, int m, char[][] map) {
    int pools = 0;

    boolean[][] visited = new boolean[n][m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (map[i][j] == POOL && !visited[i][j]) {
          visited = depthFirstSearch(n, m, i, j, map, visited);
          pools++;
        }
      }
    }

    return pools;
  }

  public static void main(String[] args) {
    try (Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out); ) {
      int n = in.nextInt();
      int m = in.nextInt();

      assert (n >= 1 && n <= 100 && m >= 1 && m <= 100);

      char[][] map = new char[n][m];

      for (int i = 0; i < n; i++) {
        String line = in.next();

        assert (line.length() == m);

        for (int j = 0; j < m; j++) {
          map[i][j] = line.charAt(j);

          assert (map[i][j] == GROUND || map[i][j] == POOL);
        }
      }

      out.println(getNumberOfPools(n, m, map));
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
