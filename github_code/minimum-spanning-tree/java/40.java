import java.util.*;
import java.lang.*;
import java.io.*;

class Codechef
{
    private static final int vertex=5;
    int minEdge(Boolean mstSet[], int key[]){
        int u = Integer.MAX_VALUE;
        for(int i=0;i<vertex;i++){
            if(mstSet[i]==false && u>key[i]){
                u = i;
            }
        }
        return u;
    }
    void printMST(int parent[], int n, int graph[][])
    {
        System.out.println("Edge   Weight");
        for (int i = 1; i < vertex; i++)
            System.out.println(parent[i]+" - "+ i+"    "+
                               graph[i][parent[i]]);
    }
    void primMST(int graph[][]){
        int[] key = new int[vertex];
        int[] parent = new int[vertex];
        Boolean[] mstSet = new Boolean[vertex];
        for(int i=0;i<vertex;i++){
            key[i] = Integer.MAX_VALUE;
            mstSet[i] = false;
        }
        key[0] = 0;
        parent[0] = -1;

        for(int i=0;i<vertex-1;i++){
            int u = minEdge(mstSet, key);
            mstSet[u] = true;
            for(int j=0;j<vertex;j++){
                if(graph[i][j]!=0 && mstSet[j]==false && graph[i][j]<key[j]){
                    parent[j] = i;
                    key[j] = graph[i][j];
                }
            }
        }
        printMST(parent,vertex,graph);
    }
	public static void main (String[] args) throws java.lang.Exception
	{
	    int graph[][] = new int[][] {{0, 2, 0, 6, 0},
                                    {2, 0, 3, 8, 5},
                                    {0, 3, 0, 0, 7},
                                    {6, 8, 0, 0, 9},
                                    {0, 5, 7, 9, 0},
                                   };
        Codechef c = new Codechef();
        c.primMST(graph);
	}
}
