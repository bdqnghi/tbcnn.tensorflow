/**
 * BFS use
 * finding the shortest route from point A to point B (e.g. directions from “Google Maps”)
 * finding how many “friend links” you are from someone on Facebook.
 * 
 * The breadth-first search, or BFS, is the counterpart to DFS in tree traversing techniques. 
 * It is a search algorithm that traverses down a tree using a queue as its data array, 
 * where elements are visited in a FIFO, first-in first-out, mechanism. 
 * This strategy is also called level-order traversal, 
 * as all nodes on a level are visited before proceeding to the next level.
 * 
 * 1) Shortest Path and Minimum Spanning Tree for unweighted graph In an unweighted graph, 
 *    the shortest path is the path with least number of edges. 
 *    With Breadth First, we always reach a vertex from given source using the minimum number of edges. 
 *    Also, in case of unweighted graphs, any spanning tree is Minimum Spanning Tree 
 *    and we can use either Depth or Breadth first traversal for finding a spanning tree.
 * 2) Peer to Peer Networks. In Peer to Peer Networks like BitTorrent, 
 *    Breadth First Search is used to find all neighbor nodes.
 * 3) Crawlers in Search Engines: Crawlers build index using Breadth First. 
 *    The idea is to start from source page and follow all links from source and keep doing same. 
 *    Depth First Traversal can also be used for crawlers, 
 *    but the advantage with Breadth First Traversal is, 
 *    depth or levels of the built tree can be limited.
 * 4) Social Networking Websites: In social networks, we can find people 
 *    within a given distance ‘k’ from a person using Breadth First Search till ‘k’ levels.
 * 5) GPS Navigation systems: Breadth First Search is used to find all neighboring locations.
 * 6) Broadcasting in Network: In networks, a broadcasted packet follows Breadth First Search 
 *    to reach all nodes.
 * 7) In Garbage Collection: Breadth First Search is used in copying garbage collection 
 *    using Cheney’s algorithm. Refer this and for details. 
 *    Breadth First Search is preferred over Depth First Search 
 *    because of better locality of reference:
 * 8) Cycle detection in undirected graph: In undirected graphs, either Breadth First Search  
 *    or Depth First Search can be used to detect cycle. 
 *    In directed graph, only depth first search can be used.
 * 9) Ford–Fulkerson algorithm In Ford-Fulkerson algorithm, 
 *    we can either use Breadth First or Depth First Traversal to find the maximum flow. 
 *    Breadth First Traversal is preferred as it reduces worst case time complexity to O(VE2).
 * 10) To test if a graph is Bipartite We can either use Breadth First or Depth First Traversal.
 * 11) Path Finding We can either use Breadth First or Depth First Traversal 
 *     to find if there is a path between two vertices.
 * 12) Finding all nodes within one connected component: 
 *     We can either use Breadth First or Depth First Traversal 
 *     to find all nodes reachable from a given node.
 * Many algorithms like Prim’s Minimum Spanning Tree and Dijkstra’s Single Source Shortest 
 * Path use structure similar to Breadth First Search.
 */