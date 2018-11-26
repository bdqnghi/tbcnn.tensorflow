package dynamic.linkedList.graph;


/**
 * A minimum spanning tree between in a Graph of n vertices is a tree of (n-1) edges which has the least 
 * sum of edges.A min spanning tree may not necessarily give the shortest path between two vertices.
 * 
 *  Consider the following undirected graph:
 *  vertex A - Edges AD=5,  AE=2
 *  vertex B - Edges BC=58, BE=5 	
 *  vertex C - Edges CD=34, CE=4
 *  vertex D - Edges        DE=14
 *  vertex E - Edges AE,BE,CE,DE	   
 * 
 * In this graph the minimum spanning tree is a cross-like shape with node 2 in the center. 
 * This is because that clearly gives the least total cost: 2+5+14+4=25.
 *	
 * What you might notice is that, this doesn't mean that the spanning tree is the most cost-efficient path 
 * between two nodes (even if that happens to be in many cases). For example going from node 1 to 4 could be 
 * done with a cost of 5 in Dijkstra's algorithm (the nodes are next to each other!). However with the minimum 
 * spanning tree they are forced to go through node 2 yielding a cost of 7.
 * 
 * Minimum spanning tree is based on cut property. 
 * A cut splits a graph into two components. It may involve multiple edges. 
 * In MST, we select the edge with the least weight.
 * 
 * There are 2 ways to find the MST 
 * 	- One with the Prim's algorithm.
 * 	- the second one with the Kruskal's algorithm.
 * 
 * https://www.thestudentroom.co.uk/showthread.php?t=232168
 * https://stackoverflow.com/questions/14144279/difference-between-prims-and-dijkstras-algorithms/25800210
 * 
 * The concept of an MST assumes that graphs are inherently undirected.
 * 
 * https://github.com/SethosII/minimum-spanning-tree
 * https://github.com/yugantjoshi/Minimum-Spanning-Tree/blob/master/src/apps/MST.java
 * https://github.com/jiaqi-gu/Minimum_Spanning_Tree/tree/master/src
 * 
 * https://github.com/search?l=Java&q=minimum+spanning+tree&type=Repositories&utf8=%E2%9C%93
 * 
 * Prim's algo:
 * https://www.youtube.com/watch?annotation_id=annotation_2492575683&feature=iv&src_vid=lAXZGERcDf4&v=oP2-8ysT3QQ#t=1m16s
 * 
 * Kruskal's algorithm:
 * https://www.youtube.com/watch?v=fAuF0EuZVCk&t=78s
 * 
 * 
 */
public class MinSpanningTree {

}
