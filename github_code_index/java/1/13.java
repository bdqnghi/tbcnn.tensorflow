
import java.awt.Point;
import java.util.*;

public class BFS {

    private static final int[][] dirs = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    private static boolean inBounds(char[][] mat, Point p) {
        return Math.min(p.x, p.y) >= 0 && p.x < mat.length && p.y < mat[0].length;
    }

    public static List<Point> solve(char[][] mat, Point start, Point end) {

        Set<Point> visited = new HashSet<>();
        Map<Point, Point> parents = new HashMap<>();

        Queue<Point> q = new LinkedList<>();
        q.add(start);

        while (!q.isEmpty()) {

            Point cur = q.remove();
            visited.add(cur);

            if (cur.equals(end)) {

                LinkedList<Point> path = new LinkedList<>();
                Point node = cur;

                while (node != null) {

                    path.addFirst(node);
                    node = parents.get(node);

                }

                return path;

            } else {

                for (int[] dir : dirs) {

                    Point n = new Point(cur.x + dir[0], cur.y + dir[1]);

                    if (inBounds(mat, n) && !visited.contains(n) && mat[n.x][n.y] == '.') {

                        q.add(n);
                        parents.put(n, cur);

                    }

                }

            }

        }

        return null;

    }

    public static List<Point> solve2(char[][] mat, Point start, Point end) {

        Queue<Point> q = new LinkedList<>();

        q.add(start);

        return recur(mat, end, new HashSet<Point>(), new HashMap<Point, Point>(), q);

    }

    private static List<Point> recur(char[][] mat, Point end, Set<Point> visited, HashMap<Point, Point> parents, Queue<Point> q) {

        if(q.isEmpty()) return null;

        Point cur = q.remove();

        visited.add(cur);

        if (cur.equals(end)) {

            LinkedList<Point> path = new LinkedList<>();
            Point node = cur;

            while (node != null) {

                path.addFirst(node);
                node = parents.get(node);

            }

            return path;

        } else {

            for (int[] dir : dirs) {

                Point n = new Point(cur.x + dir[0], cur.y + dir[1]);

                if (inBounds(mat, n) && !visited.contains(n) && mat[n.x][n.y] == '.') {

                    parents.put(n, cur);

                    q.add(n);

                    List<Point> p = recur(mat, end, visited, parents, q);

                    if (p != null) {

                        return p;

                    }

                }

            }
        }

        return null;
    }

    public static void main(String[] args) {

        char[][] grid = new char[][]{
            {'.', '#', '#', '#', '#'},
            {'.', '#', '.', '.', '.'},
            {'.', '#', '.', '#', '.'},
            {'.', '.', '.', '#', '.'},
            {'.', '#', '#', '.', '.'}
        };

        for (Point point : solve(grid, new Point(0, 0), new Point(4, 4))) {
            System.out.println(point);
        }

        System.out.println("------");

        for (Point point : solve2(grid, new Point(0, 0), new Point(4, 4))) {
            System.out.println(point);
        }

    }

}
