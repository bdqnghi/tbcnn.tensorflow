package com.dredom.graph;

import static java.lang.System.out;

import java.util.ArrayDeque;

/**
 * Given a board consisting of empty space, walls, and the starting positions of two players A and B,
 * determine the minimum number of turns it will take for players A and B to switch positions on the board.
 * <p>
 * A quick summary of the problem is that we want to exchange the positions of two players on a grid.
 * There are impassable spaces represented by 'X' and spaces that we can walk in represented by ' '.
 * <p>
 * Since we have two players our node structure becomes a bit more complicated, we have to represent the
 * positions of person A and person B.
 * Also, we won't be able to simply use our array to represent visited positions any more,
 * we will have an auxiliary data structure to do that.
 * Also, we are allowed to make diagonal movements in this problem, so we now have 9 choices,
 * we can move in one of 8 directions or simply stay in the same position.
 *
 * Another little trick that we have to watch for is that the players can not just swap positions in a single turn,
 * so we have to do a little bit of validity checking on the resulting state.
 * <p>
 * Queue Theory:
 * When we visit a node and add all the neighbors into the queue, then pop the next thing off of the queue,
 * we will get the neighbors of the first node as the first elements in the queue.
 * This comes about naturally from the FIFO property of the queue and ends up being an extremely useful property.
 * <p>
 * Uses FIFO property of the queue to traverse breadth-wise.
 * <p>
 * Input: Rectangles which are already filled (true).
 * <p>
 * Output: Sizes of unfilled rectangles;
 * <p>
 * Big O time O(64 * height * width) worst, 2 positions A and B, size of grid. ??
 * All combinations of A and B in grid and steps to get there.
 * One move generates potentially 8 x 8 nodes (A and B combinations with 8 positions around each).
 */
public class BreadthFirstSearch {


    static String[] board = {
        "....",
        ".A..",
        "..B.",
        "...."
    };    // result 2
    static int expectedTurns = 2;

//            "XXXXXXXXX",
//            "A...X...B",
//            "XXXXXXXXX"
//        };  // result -1

//            "XXXXXXXXX",
//            "A.......B",
//            "XXXX.XXXX"
//        };  // result 8

    static int gridlen = board.length;

    // [pAy][pAx] [pBy][pBx]
    static boolean[][][][] visited = new boolean[gridlen][gridlen][gridlen][gridlen];



    /**
     * The Node is used to "travel" the grid for both A and B, with new instances
     * representing new positions as we attempt to find how many steps it would
     * take to swap positions for A and B.
     */
    static class Node {
        public int pAx;
        public int pAy;
        public int pBx;
        public int pBy;
        public int steps;   // steps taken to reach this step
        @Override
        public String toString() {
            return "A[" + pAy + "," + pAx + "],B[" + pBy + "," + pBx + "]"
                    + "," + steps;
        }
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        int steps = search(board);
        out.println("Steps = " + steps);
        out.println(System.currentTimeMillis() - start + "ms");
    }


    /**
     * Search for players and find the turns to swap them.
     * @return minimum number of turns needed
     */
    static int search(String[] boardin) {
        int width = boardin[0].length();
        int height = boardin.length;

        int xA = -1;
        int yA = -1;
        int xB = -1;
        int yB = -1;

        // Convert to bytes for convenience
        byte[][] board = new byte[height][width];
        for (int y = 0; y < height; y++) {
            byte[] line = boardin[y].getBytes();
            for (int x = 0; x < width; x++) {
                board[y][x] = line[x];

                // Find positions for A and B
                if (board[y][x] == 'A') {
                    xA = x;
                    yA = y;
                }
                if (board[y][x] == 'B') {
                    xB = x;
                    yB = y;
                }
            }
        }

        if (xA == -1 || yA == -1 || xB == -1 || yB == -1) {
            out.println("Misssing player position in input");
            return -1;
        }
        out.printf(" Player A[%d, %d], Player B[%d, %d] \n", yA, xA, yB, xB);

        Node start = new Node();
        start.pAx = xA;
        start.pAy = yA;
        start.pBx = xB;
        start.pBy = yB;
        start.steps = 0;

        ArrayDeque<Node> queue = new ArrayDeque<>();
        queue.push(start);

        int iteration = 1;
        while (queue.isEmpty() == false) {
            // * Get from the first added to the queue (closest neighbors to first node)
            Node top = queue.removeFirst();

            // Check if player 1 or player 2 is out of bounds, or on an X square, if so continue
            if (top.pAx < 0 || top.pAy < 0
                    || top.pAx >= width || top.pAy >= height
                    || board[top.pAy][top.pAx] == 'X') {
                continue;
            }
            if (top.pBx < 0 || top.pBy < 0
                    || top.pBx >= width || top.pBy >= height
                    || board[top.pBy][top.pBx] == 'X') {
                continue;
            }
            // Check if player A and player B are on top of each other, if so continue
            if (top.pAx == top.pBx && top.pAy == top.pBy) {
                continue;
            }

            // Make sure we have not visited this state before
            if (visited[top.pAy][top.pAx][top.pBy][top.pBx]) {
                continue;
            }
            // Mark top as visited;
            visited[top.pAy][top.pAx][top.pBy][top.pBx] = true;

            // * Check for termination condition (have we reached the node we want to?)
            // If the positions of initial A and B have swapped then we are done!
            if (top.pAx == start.pBx && top.pAy == start.pBy
                    && top.pBx == start.pAy && top.pBy == start.pAy) {
                return top.steps;
            }

            // * Add all of top's unvisited neighbors to the stack
            // Now we need to generate all of the transitions between nodes, we can do this quite easily using some
            // nested for loops, one for each direction that it is possible for one player to move.  Since we need
            // to generate the following deltas: (-1,-1), (-1,0), (-1,1), (0,-1), (0,0), (0,1), (1,-1), (1,0), (1,1)
            // we can use a for loop from -1 to 1 to do exactly that.
            int count = 0;
            for (int pAxDelta = -1; pAxDelta <= 1; pAxDelta++) {
                for (int pAyDelta = -1; pAyDelta <= 1; pAyDelta++) {
                    for (int pBxDelta = -1; pBxDelta <= 1; pBxDelta++) {
                        for (int pByDelta = -1; pByDelta <= 1; pByDelta++) {
                            // Careful though! We have to make sure that player
                            // 1 and 2 did not swap positions on this turn
                            if (top.pAx == top.pBx + pBxDelta && top.pAy == top.pBy + pByDelta
                                    && top.pBx == top.pAx + pAxDelta && top.pBy == top.pAy + pAyDelta) {
                                continue;
                            }

                            // Add the new node to the end of the queue
                            Node node = new Node();
                            node.pAx = top.pAx + pAxDelta;
                            node.pAy = top.pAy + pAyDelta;
                            node.pBx = top.pBx + pBxDelta;
                            node.pBy = top.pBy + pByDelta;
                            node.steps = top.steps + 1;
                            queue.add(node);
                            count++;
                        }
                    }
                }
            }
//            out.println(Arrays.deepToString(queue.toArray()));
            out.printf("%d %d queue.first=%s queue.last=%s size=%d \n", iteration++, count, queue.getFirst(), queue.getLast(), queue.size());
        }   // while

          // It is not possible to exchange positions, so
          // we return -1.  This is because we have explored
          // all the states possible from the starting state,
          // and haven't returned an answer yet.
         return -1;
    }

}
