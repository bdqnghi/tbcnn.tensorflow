package graphs;

import java.util.Stack;

public class TopologicalSort {

    public static void main(String[] args) {
        Graph g = new Graph(6, true);
        /*g.addEdge(1, 2, true);
        g.addEdge(2, 3, true);
        g.addEdge(3, 4, true);
        g.addEdge(4, 5, true);
        g.addEdge(5, 6, true);
        g.addEdge(6, 7, true);
        g.addEdge(7, 8, true);
        g.addEdge(7, 9, true);
        g.addEdge(8, 9, true);
        g.addEdge(9, 5, true);*/
        //g.addEdge(7, 7, true);
        g.addEdge(1, 2, true);
        g.addEdge(2, 3, true);
        g.addEdge(4, 2, true);
        g.addEdge(4, 5, true);
        g.addEdge(5, 6, true);
        g.addEdge(6, 3, true);
        TopologicalSort ts = new TopologicalSort();
        ts.topSort(g);
    }

    public void topSort(Graph g) {
        initDfs(g);
        for (int i = 1; i <= g.numV; i++) {
            if (!mDiscovered[i]) {
                idfs(i, g);
            }
            if (mFinished) return;
        }
        while (mSorted.size() > 0) {
            out(mSorted.pop() + " ");
        }
        outln("");
    }

    private Stack<Integer> mSorted;
    private boolean[] mDiscovered;
    private boolean[] mProcessed;
    private int[] mParent;
    private int[] mEntryTime;
    private int[] mExitTime;
    private int mTime;
    private boolean mFinished;

    private void initDfs(Graph g) {
        mSorted = new Stack<>();
        mDiscovered = new boolean[g.numV + 1];
        mProcessed = new boolean[g.numV + 1];
        mParent = new int[g.numV + 1];
        mEntryTime = new int[g.numV + 1];
        mExitTime = new int[g.numV + 1];
        mFinished = false;
        for (int i = 0; i <= g.numV; i++) {
            mDiscovered[i] = mProcessed[i] = false;
            mParent[i] = -1;
        }
    }

    /* call initDfs() before this function */
    private void idfs(int start, Graph g) {
        Stack<Vertex> stack = new Stack<>();
        stack.push(new Vertex(start, g.adjacents[start]));
        mDiscovered[start] = true;
        mEntryTime[start] = ++mTime;
        processVertexEarly(start);

        while (!stack.isEmpty()) {
            Vertex vertex = stack.peek();
            if (vertex.adj != null) {
                int end = vertex.adj.end;
                if (!mDiscovered[end]) {
                    mParent[end] = vertex.v;
                    processEdge(vertex.v, end, g);

                    stack.push(new Vertex(end, g.adjacents[end]));
                    mDiscovered[end] = true;
                    mEntryTime[end] = ++mTime;
                    processVertexEarly(end);
                } else if ((!mProcessed[end] && mParent[vertex.v] != end) || g.directed) {
                    processEdge(vertex.v, end, g);
                }
                vertex.adj = vertex.adj.next;
            } else {
                stack.pop();
                processVertexLate(vertex.v);
                mExitTime[vertex.v] = ++mTime;
                mProcessed[vertex.v] = true;
            }
            if (mFinished) return;
        }
    }

    private void processVertexEarly(int vertex) {}

    private void processVertexLate(int vertex) {
        mSorted.push(vertex);
    }

    private void processEdge(int vertex, int end, Graph g) {
        if (classifyEdge(vertex, end) == EdgeType.BACK) {
            outln("Not a DAG! Cycle detected " + vertex + " -> " + end);
            mFinished = true;
        }
    }

    private EdgeType classifyEdge(int x, int y) {
        if (mParent[y] == x) return EdgeType.TREE;
        if (mDiscovered[y] && !mProcessed[y]) return EdgeType.BACK;
        if (mProcessed[y] && mEntryTime[y] > mEntryTime[x]) return EdgeType.FORWARD;
        if (mProcessed[y] && mEntryTime[y] < mEntryTime[x]) return EdgeType.CROSS;
        outln("Warning: self loop " + x + ", " + y);
        return EdgeType.TREE;
    }

    private enum EdgeType { TREE, BACK, FORWARD, CROSS };

    private class Vertex {
        int v;
        Graph.Adjacent adj;
        public Vertex(int v, Graph.Adjacent adj) {
            this.v = v;
            this.adj = adj;
        }
    }

    private static void out(String str) {System.out.print(str);}
    private static void outln(String str) {System.out.println(str);}
}
