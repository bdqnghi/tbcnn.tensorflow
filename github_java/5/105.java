package com.company.google;

import java.util.*;

public class Dfs {
    public class Coordinate {
        private int row;
        private int col;
        private int value;

        public Coordinate(int row, int col, int value) {
            this.row = row;
            this.col = col;
            this.value = value;
        }

        public int getRow() {
            return row;
        }

        public int getCol() {
            return col;
        }

        public int getValue() {
            return value;
        }

        /**
         * Returns a string representation of the object. In general, the
         * {@code toString} method returns a string that
         * "textually represents" this object. The result should
         * be a concise but informative representation that is easy for a
         * person to read.
         * It is recommended that all subclasses override this method.
         * <p>
         * The {@code toString} method for class {@code Object}
         * returns a string consisting of the name of the class of which the
         * object is an instance, the at-sign character `{@code @}', and
         * the unsigned hexadecimal representation of the hash code of the
         * object. In other words, this method returns a string equal to the
         * value of:
         * <blockquote>
         * <pre>
         * getClass().getName() + '@' + Integer.toHexString(hashCode())
         * </pre></blockquote>
         *
         * @return a string representation of the object.
         */
        @Override
        public String toString() {
            return String.format("(%s, %s, value: %s)", row, col, value);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Coordinate that = (Coordinate) o;
            return row == that.row &&
                    col == that.col;
        }

        @Override
        public int hashCode() {
            return Objects.hash(row, col, value);
        }
    }

    public class Graph {
        private int[][] matrix;
        private Map<Coordinate, List<Coordinate>> edges = new HashMap<>();

        Graph(int[][] matrix) {
            this.matrix = matrix;
            int[][] dirs = {
                    {1, 0}, // south
                    {0, 1},  // east
                    {-1, 0}, // north
                    {0, -1}, // west
            };
            // add edges to map
            for (int row = 0; row < matrix.length; row++ ) {
                for (int col = 0; col < matrix[0].length; col++) {
                    edges.put(new Coordinate(row, col, matrix[row][col]), new LinkedList<>());
                }
            }
            // add neighbors
            for (Coordinate node: edges.keySet()) {
                for (int[] dir: dirs) {
                    Coordinate nbr = new Coordinate(node.getRow() + dir[0], node.getCol() + dir[1], node.getValue());
                    if (edges.containsKey(nbr)) {
                        edges.get(node).add(nbr);
                    }
                }
            }
        }

        public List<Coordinate> getNeighbors(Coordinate vertex) {
            return edges.get(vertex);
        }

        @Override
        public String toString() {
            return "Graph{" +
                    "edges=" + edges +
                    '}';
        }
    }

    /**
     * DFS algorithm.
     *
     * @param graph
     * @param root
     * @return
     */
    public int dfs(Graph graph, Coordinate root) {
        List<Coordinate> visited = new LinkedList<>();

        dfsUtil(graph, root, visited);
        return visited.size();
    }

    /**
     * Overloaded dfs.
     *
     * @param graph
     * @param root
     * @param visited
     * @return
     */
    private void dfsUtil(Graph graph, Coordinate root, List<Coordinate> visited) {
        visited.add(root);

        for (Coordinate v : graph.getNeighbors(root)) {
            if (!visited.contains(v)) {
                dfsUtil(graph, v, visited);
            }
        }
    }

    private int findMaxConnected(Graph graph) {
        LinkedList checked = new LinkedList();
        int[][] matrix = graph.matrix;
        int max = 0;

        for (int row = 0; row < matrix.length; row++) {
            for (int col = 0; col < matrix[0].length; col++ ) {
                int currentCount = dfs(graph, new Coordinate(row, col, matrix[row][col]));
                max = Math.max(max, currentCount);
            }
        }

        return max;
    }

    public static void main(String[] args) {
        // input array where colors are represented as integers
        int[][] input = {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
        };

        Dfs d = new Dfs();

        Dfs.Graph graph = d.new Graph(input);
        for (Map.Entry key: graph.edges.entrySet()) {
            //System.out.println(key);
        }

        System.out.println(d.findMaxConnected(graph));
    }
}
