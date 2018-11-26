package maximumflow;

/*
Find maximum number of edge disjoint paths between two vertices
Given a directed graph and two vertices in it, source ‘s’ and destination ‘t’, find out the maximum number of edge
disjoint paths from s to t. Two paths are said edge disjoint if they don’t share any edge.

This problem can be solved by reducing it to maximum flow problem. Following are steps.
1) Consider the given source and destination as source and sink in flow network. Assign one unit capacity to each edge.
2) Run Ford-Fulkerson algorithm to find the maximum flow from source to sink.
3) The maximum flow is equal to the maximum number of edge-disjoint paths.

When we run Ford-Fulkerson, we reduce the capacity by a unit. Therefore, the edge can not be used again.
So the maximum flow is equal to the maximum number of edge-disjoint paths.
 */

public class EdgeDisjointPaths {
}