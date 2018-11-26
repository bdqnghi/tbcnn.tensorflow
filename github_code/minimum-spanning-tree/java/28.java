package algorithm.code.graph;

import algorithm.code.utils.unionfindsets.UnionFindSet;

import java.util.PriorityQueue;

/**
 * 判断强连通图
 * 判断联通性（有向 无向）
 * 判断一个图是存在欧拉回路（环）
 * 判断一个图是存在欧拉路径（线）
 * 求出欧拉回路
 * 求出欧拉路径
 */
public class MinimumSpanningTree {
    public static int[][] graph = new int[][]{
            {0,4,8,9,4},
            {4,0,9,9,10},
            {8,9,0,1,9},
            {9,9,1,0,2},
            {4,10,9,2,0}};

    /**
     * 判断 无向图是否联通
     */
    public static boolean isConnectedGraph(int[][] graph){
        int len = graph.length;
        UnionFindSet set = new UnionFindSet(len);
        int points[] = new int[len];
        for(int i=0;i<len;i++){
            for(int j = 0;j<len;j++){
                if(graph[i][j]!=0){
                    set.union(i,j);
                }
            }
        }
        return set.count()==1?true:false;
    }

    /**
     * 求 连通图最小生成树prim算法
     * 需要首先确保图为连通图
     * Prim算法步骤：
     * 1、任选一点作为起点，加入已遍历集合(finished)
     * 2、使用另外一个集合待遍历集合存储与起点相连的边的 起点，距离，终点
     * 3、每次从带待遍历集合中取出一个距离最小且终点不在已遍历集合中，
     * 将终点加入已遍历集合，将与终点相连的边加入待遍历集合
     * 4、已遍历集合中点的个数达到n,停止
     */
    public static int[][] generateMinTree_Prim(int[][] graph){
        if(!isConnectedGraph(graph)) return null;
        int start = 0;
        int len = graph.length;
        int[] finished = new int[len];
        finished[0]=1;
        PriorityQueue<Line> queue = new PriorityQueue<Line>();
        int res[][] = new int[len-1][2];
        for(int j=0;j<len;j++){
            if(graph[0][j]!=0){
                queue.offer(new Line(0,j,graph[0][j]));
            }
        }
        for(int i=0;i<len-1;i++) {
            while (finished[queue.peek().end] == 1) queue.poll();
            Line line = queue.poll();
            res[i][0]=line.start;
            res[i][1]=line.end;
            finished[line.end] = 1;
            for (int j = 0; j < len; j++) {
                if (graph[line.end][j] != 0 && finished[j] == 0) {
                    queue.offer(new Line(line.end, j, graph[line.end][j]));
                }
            }
        }
        return res;
    }
    public static class Line implements Comparable<Line>{
        int start;
        int end;
        int length;

        public Line(int start, int end, int length) {
            this.start = start;
            this.end = end;
            this.length = length;
        }

        @Override
        public int compareTo(Line l) {
            return length-l.length;
        }
    }
    /**
     * 求 连通图最小生成树Kruskal算法
     * 依赖并查集
     */
    public static int[][] generateMinTree_Kruskal(int[][]graph){
        PriorityQueue<Line> queue = new PriorityQueue<Line>();
        int len = graph.length;
        int res[][] = new int[len-1][2];
        //int[] root = new int[len]; //并查集 判断两个点是否属于同一集合
        UnionFindSet set = new UnionFindSet(len);

        for(int i=0;i<len;i++){
            for(int j=i;j<len;j++){
                if(graph[i][j]!=0){
                    queue.offer(new Line(i,j,graph[i][j]));
                }
            }
        }
        for(int i=0;i<len-1;i++){
            while(set.find(queue.peek().start) == set.find(queue.peek().end)) queue.poll();
            Line line = queue.poll();
            res[i][0]=line.start;
            res[i][1]=line.end;
            set.union(line.start,line.end);
        }
        return res;
    }

    /**
     * 最短路径
     * @param args
     */

    public static void main(String[] args) {
        System.out.println(MinimumSpanningTree.isConnectedGraph(graph));
        int[][] res = MinimumSpanningTree.generateMinTree_Prim(graph);
        for(int i=0;i<res.length;i++){
            for(int j=0;j<res[0].length;j++){
                System.out.print(res[i][j]);
            }
            System.out.println();
        }
    }
}
