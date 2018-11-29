package datastructures.graph;

import java.util.LinkedHashSet;
import java.util.Set;

public class BFS {
				
	/**
	 * Queue of {@code Node} instances.
	 * @author david
	 * TODO test the queue
	 */
	private class Queue{
		/**
		 * First element of the queue (FIFO)
		 */
		private transient QueueNode first;
		
		/**
		 * Last element of the queue (FIFO)
		 */
		private transient QueueNode last;
		
		/**
		 * Auxiliary class used as node of the queue.
		 * @author david
		 *
		 */
		private class QueueNode{
			
			/**
			 * Link to the next node of the queue
			 */
			public transient QueueNode next;
			
			/**
			 * Value of the actual node
			 */
			//TODO add accessor to this and make this private
			public transient final BFSNode value;
			
			
			/**
			 * Construct the instance with an initial value
			 * @param value
			 */
			public QueueNode(final BFSNode value) {
				this.value = value;
			}
		}
		
		
		/**
		 * Ask if the queue is empty or not
		 * @return true is the queue is empty, otherwise, return false
		 */
		public boolean isEmpty() {
			return this.first == null;
		}
		
		/**
		 * Insert a {@code Node} to the queue.
		 * @param value
		 */
		public void enqueue(final BFSNode value) {
			final QueueNode node = new QueueNode(value);

			//Boundary condition: If the queue is empty we add the 
			//new node as first and last item
			if(this.first == null) {
				this.first = node;
				this.last = node;
				//and it will look like this and we are done:
				/*
				digraph g {
					node [shape = record];
					node0[label = "<data>0 (first and last) |<pointer> next"]
				}
				 */
				return;
			}
			
			/* Typical case: For example, before the insertion we 
			 * could have this:
				digraph g {
					node [shape = record];
					node0[label = "<data>0 (first) |<pointer> next"]
					node1[label = "<data>1 |<pointer> next"]
					node2[label = "<data>2 (last) |<pointer> next"]
					node0:pointer -> node1:data;
					node1:pointer -> node2:data;
				}
			 */
			
			//then we incorporate the node to the queue as the 
			//last item of the linked list
			this.last.next = node;
			
			//and get a reference of that node as the last 
			//item of the queue
			this.last = node;
			/*
				digraph g {
					node [shape = record];
					node0[label = "<data>0 (first) |<pointer> next"]
					node1[label = "<data>1 |<pointer> next"]
					node2[label = "<data>2 (old last) |<pointer> next"]
					node3[label = "<data>3 (new last) |<pointer> next"]
					node0:pointer -> node1:data;
					node1:pointer -> node2:data;
					node2:pointer -> node3:data;
				}
			 */			
		}
	
		
		/**
		 * Remove the first item of queue (FIFO) and return it.
		 * @return
		 */
		public BFSNode dequeue() {
			//Typical scenario: For example, if we have a queue like this:
			/*
				digraph g {
					node [shape = record];
					node0[label = "<data>0 (first) |<pointer> next"]
					node1[label = "<data>1 |<pointer> next"]
					node2[label = "<data>2 |<pointer> next"]
					node3[label = "<data>3 (last) |<pointer> next"]
					node0:pointer -> node1:data;
					node1:pointer -> node2:data;
					node2:pointer -> node3:data;
				}
			*/
			//then we can retrieve the first item
			final QueueNode node = this.first;
			
			//but we return null if the queue is already empty
			if(node == null) {
				return null;
			}
			
			//and mark the second item (node1) as the new "first" (so, we 
			//will lost reference of the 'old' first node (node0)
			this.first = node.next;
			//so the new linked list will look like this:
			/*
			digraph g {
				node [shape = record];
				node1[label = "<data>1 (first) |<pointer> next"]
				node2[label = "<data>2 |<pointer> next"]
				node3[label = "<data>3 (last) |<pointer> next"]
				node1:pointer -> node2:data;
				node2:pointer -> node3:data;
			}
			*/
			
			//Boundary condition: If it was only one node on que queue to begin with
			/*
			digraph g {
				node [shape = record];
				node1[label = "<data>1 (first and last) |<pointer> next"]
			}
			*/
			//then the new this.first will be equal to null and 
			//we should also de-reference 'last' 
			if(this.first == null) {
				this.last = null;
			}
			
			return node.value;
		}
	}

	
	/**
	 * Vertex of the Graph
	 * 
	 * Internally I use a HashMap to store the values, but it is encapsulated
	 * complaining to the Law of Demeter, so I can change the usage of the
	 * HashMap for another kind of collection if required, without changing
	 * the code of the other classes.
	 * 
	 * @author David Perez
	 */
	private class BFSNode implements Comparable<BFSNode> {
		
		/**
		 * The value contained by the graph
		 */
		private final int value;
		
		/**
		 * Mark used to know if a node was already visited
		 * during the search() 
		 */
		private transient boolean visited;
		
		/**
		 * Adjacent vertexs using map to avoid duplicated links.
		 * I need to order the nodes by insert to follow my test examples more easily
		 * that's why I'm using a LinkedHashSet
		 */
		private final Set<BFSNode> adjacents = new LinkedHashSet<BFSNode>();
	
		/**
		 * Add one or more adjacent nodes to the actual node.
		 * @param nodes
		 */
		public void addAdjacents(final BFSNode...nodes) {
			for(final BFSNode node: nodes) {
				if(!adjacents.contains(node)) {
					adjacents.add(node);
				}
			}
		}
	
		/**
		 * Get the adjacent nodes for this node instance
		 * @return
		 */
		public BFSNode[] getAdjacents(){
			final BFSNode[] arr = new BFSNode[this.adjacents.size()];
			return this.adjacents.toArray(arr);
		}
		
		/**
		 * Get the value of the node
		 * @return
		 */
		public int getValue() {
			return this.value;
		}
		
		/**
		 * Mark the node as visited
		 * @return
		 */
		public void markAsVisited() {
			this.visited = true;
		}
		
		/**
		 * Ask if the node was already visited
		 * @return
		 */
		public boolean hasVisited() {
			return this.visited;
		}
		
		/**
		 * Construct the node instance with an initial value.
		 * @param value
		 */
		public BFSNode(final int value) {
			this.value = value;
		}

		@Override
		public int compareTo(BFSNode o) {
			if(this.value > o.value) {
				return 1;
			}else if(this.value < o.value) {
				return -1;
			}else {
				return 0;
			}
		}
				
	}		
	
	
	/**
	 * Traverse the graph
	 * @param base
	 * @return The order of the traverse
	 */
	public String search(final BFSNode root) {
		final StringBuffer order = new StringBuffer();
		
		final Queue queue = new Queue();
		queue.enqueue(root);
		
		while(!queue.isEmpty()) {
			final BFSNode node = queue.dequeue();
			order.append(visit(node));
			for(final BFSNode child : node.getAdjacents()) {
				if(!child.hasVisited()) {
					child.markAsVisited();
					queue.enqueue(child);					
				}
			}
		}
		
		return order.toString();		
	}

	private String visit(final BFSNode node) {
		return (node.getValue() + "->");		
	}
	
	/**
	 * Test cases
	 * @param args
	 */
	public static void main(String[] args) {
		final BFS bfs = new BFS();

		final Queue queue = bfs.new Queue();
		assertTrue(queue.dequeue() == null, "Dequeue empty queue returns null");
		queue.enqueue(bfs.new BFSNode(1000));
		final BFSNode retrieved1 = queue.dequeue();
		assertTrue(retrieved1 != null && retrieved1.getValue() == 1000, "Dequeue one item returns that item");
		assertTrue(queue.dequeue() == null, "and then queue becomes empty");
		queue.enqueue(bfs.new BFSNode(1));
		queue.enqueue(bfs.new BFSNode(2));
		queue.enqueue(bfs.new BFSNode(3));
		final BFSNode retr1 = queue.dequeue();
		final BFSNode retr2 = queue.dequeue();
		final BFSNode retr3 = queue.dequeue();
		final BFSNode retr4 = queue.dequeue();
		assertTrue(retr1 != null && retr1.getValue() == 1, "Dequeue (1)");
		assertTrue(retr2 != null && retr2.getValue() == 2, "Dequeue (2)");
		assertTrue(retr3 != null && retr3.getValue() == 3, "Dequeue (3)");
		assertTrue(retr4 == null, "Dequeue empty queue after long queue returns null");	
		
		/*		
			digraph{
			 0->"1 visited=true"
			 0->"2 visited=false"
			 "2 visited=false"->"1 visited=true"
			 "1 visited=true"->null;
		}		
		*/	
		final BFSNode n0 = bfs.new BFSNode(0);
		final BFSNode n1 = bfs.new BFSNode(1);
		final BFSNode n2 = bfs.new BFSNode(2);
		n0.addAdjacents(n1);
		n0.addAdjacents(n2);
		n2.addAdjacents(n1);
		
		final String result = bfs.search(n0);
		final String msg1 = "0->1->2->";
		assertEqual(result, msg1, "BFS " + msg1);
		
		/*
			digraph{
				 0;1;2;3;4;5;
				//visit first children of root node (0)
				0->1 
				//visiting first child (1) of (0)
				1->3
				//visiting first child (3) of (1)
				3->2
				2->1 //skip the visited child (1) 
				3->4 //node (4) have no links, so, end and go up (to parent)
				1->4 //skip visited child (4)
				0->4 //skip visited child (4)
				0->5
			}	
		 */
		final BFSNode x0 = bfs.new BFSNode(0);
		final BFSNode x1 = bfs.new BFSNode(1);
		final BFSNode x2 = bfs.new BFSNode(2);
		final BFSNode x3 = bfs.new BFSNode(3);
		final BFSNode x4 = bfs.new BFSNode(4);
		final BFSNode x5 = bfs.new BFSNode(5);
		x0.addAdjacents(x1, x4, x5);
		x1.addAdjacents(x3, x4);
		x2.addAdjacents(x1);
		x3.addAdjacents(x2);
		final String result2 = bfs.search(x0);
		final String msg2 = "0->1->4->5->3->2->";
		assertEqual(result2, msg2, "BFS " + msg2);
		
	}

	private static void assertEqual(final String result, final String expect, final String msg) {
		if(result.equals(expect)) {
			System.out.println("Success: "+msg);
		}else {
			System.err.println("Failure: "+msg+". Expected "+expect+" but got "+ result);
		}
	}
	
	private static void assertTrue(final boolean assertion, final String msg) {
		if(assertion) {
			System.out.println("Success: " + msg);
		}else {
			System.err.println("Failure :" + msg);
		}
	}

}
