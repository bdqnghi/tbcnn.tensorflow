/**
 * Refer to
 * http://www.lintcode.com/en/problem/topological-sorting/
 * Given an directed graph, a topological order of the graph nodes is defined as follow:
 * For each directed edge A -> B in graph, A must before B in the order list.
 * The first node in the order can be any node in the graph with no nodes direct to it.
 * Find any topological order for the given graph.
 * Notice
    You can assume that there is at least one topological order in the graph.
    Have you met this question in a real interview? Yes
    Clarification
    Learn more about representation of graphs
    Example
    For graph as follow:
    picture
    The topological order can be:
    [0, 1, 2, 3, 4, 5]
    [0, 2, 3, 1, 5, 4]
    ...
 * 
 * Solution
 * https://songlee24.github.io/2015/05/07/topological-sorting/
 * http://www.jiuzhang.com/solutions/topological-sorting/
 * 本题看视频的模板
*/
/**
 * Definition for Directed graph.
 * class DirectedGraphNode {
 *     int label;
 *     ArrayList<DirectedGraphNode> neighbors;
 *     DirectedGraphNode(int x) { label = x; neighbors = new ArrayList<DirectedGraphNode>(); }
 * };
 */
public class Solution {
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */    
    public ArrayList<DirectedGraphNode> topSort(ArrayList<DirectedGraphNode> graph) {
        ArrayList<DirectedGraphNode> order = new ArrayList<DirectedGraphNode>();
        if(graph == null) {
            return order;
        }
        // Count indegree for all nodes
        Map<DirectedGraphNode, Integer> indegree = getIndegree(graph);
        // Get start nodes, which indegree = 0, and it means current node
        // not depend on previous nodes, can be used as start nodes
        ArrayList<DirectedGraphNode> startNodes = getStartNodes(indegree, graph);
        // Topological sort with BFS
        order = bfs(indegree, startNodes);
		// If final DirectedGraphNode list order size equal to given
		// graph size, it means all nodes can be used for create valid
		// path of Directed Acyclic Graph(DAG)
		// Refer to
		// https://songlee24.github.io/2015/05/07/topological-sorting/
        if(order.size() == graph.size()) {
            return order;
        }
        return null;
    }
    
    private Map<DirectedGraphNode, Integer> getIndegree(ArrayList<DirectedGraphNode> graph) {
        Map<DirectedGraphNode, Integer> indegree = new HashMap<DirectedGraphNode, Integer>();
		// Initialize all nodes indegree as 0
        for(DirectedGraphNode node : graph) {
            indegree.put(node, 0);
        }
        for(DirectedGraphNode node : graph) {
            for(DirectedGraphNode neighbor : node.neighbors) {
                // node -> neighbors
                indegree.put(neighbor, indegree.get(neighbor) + 1);
            }
        }
        return indegree;
    }
    
    private ArrayList<DirectedGraphNode> getStartNodes(Map<DirectedGraphNode, Integer> indegree, ArrayList<DirectedGraphNode> graph) {
        ArrayList<DirectedGraphNode> nodes = new ArrayList<DirectedGraphNode>();
        for(DirectedGraphNode node : graph) {
            // If current node's indegree is 0, we select out
            if(indegree.get(node) == 0) {
                nodes.add(node);
            }
        }
        return nodes;
    }
    
    private ArrayList<DirectedGraphNode> bfs(Map<DirectedGraphNode, Integer> indegree, ArrayList<DirectedGraphNode> startNodes) {
        ArrayList<DirectedGraphNode> order = new ArrayList<DirectedGraphNode>();
        Queue<DirectedGraphNode> queue = new LinkedList<DirectedGraphNode>();
        for(DirectedGraphNode startNode : startNodes) {
            order.add(startNode);
            queue.offer(startNode);
        }
	// Note: The time complexity of this nested while loop is not O(V * E),
	// but O(V + E), the critical issue is the inner for loop is only
	// execute one time when preceed node (dependency node) been removed
	// from queue, so it is not mulitply relation, its linear realtion
        while(!queue.isEmpty()) {  // O(V)
            DirectedGraphNode startNode = queue.poll();
            for(DirectedGraphNode neighbor : startNode.neighbors) {  // O(E)
                // startNode -> neighbors
                // When we move current node out of queue, which means move
                // current node out of Topological graph, all its neighbors
                // indegree value must minus 1
                indegree.put(neighbor, indegree.get(neighbor) - 1);
                if(indegree.get(neighbor) == 0) {
                    queue.offer(neighbor);
                    order.add(neighbor);
                }
            }
        }
        return order;
    }
    
}
