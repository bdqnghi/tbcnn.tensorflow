import structs.graphs.Edge;
import structs.graphs.Graph;
import structs.graphs.Vertex;
import structs.lists.LinkedPositionalList;
import structs.lists.Position;
import structs.lists.PositionalList;
import structs.maps.ProbeHashMap;
import structs.priorityqueue.Entry;
import structs.priorityqueue.HeapPriorityQueue;
import structs.priorityqueue.PriorityQueue;

public class MinimumSpanningTree {
	
	/* Computes a minimum spanning tree of graph g using Krushkal's algorithm */
	public static <V> LinkedPositionalList<Edge<Integer>> MST(Graph<V, Integer> g){
		
		// tree is where we will store result as it is computed
		LinkedPositionalList<Edge<Integer>> tree = new LinkedPositionalList<>();
		
		// pq entries are edges of graph, with weights as keys
		PriorityQueue<Integer, Edge<Integer>> pq = new HeapPriorityQueue<>();
		
		// union-find forest of components of the graph
		Partition<Vertex<V>> forest = new Partition<>();
		
		// map each vertex to the forest position
		ProbeHashMap<Vertex<V>, Position<Vertex<V>>> positions = new ProbeHashMap<>();
		
		for(Vertex<V> v : g.vertices()){
			positions.put(v, forest.makeCluster(v));
		}
		
		for(Edge<Integer> e : g.edges()){
			pq.insert(e.getElement(), e);
		}
		
		int size = g.numVertices();
		
		// while tree not spanning and unprocessed edges remain...
		
		while(tree.size() != size - 1 && !pq.isEmpty()){
			Entry<Integer, Edge<Integer>> entry = pq.removeMin();
			Edge<Integer> edge = entry.getValue();
			Vertex<V>[] endpoints = g.endVertices(edge);
			Position<Vertex<V>> a = forest.find(positions.get(endpoints[0]));
			Position<Vertex<V>> b = forest.find(positions.get(endpoints[1]));
			
			if(a != b){
				tree.addLast(edge);
				forest.union(a,b);
			}
			
		}
		
		return tree;
	}
	
	/* A Union-Find structure for maintaining disjoints sets */
	public static class Partition<E>{
		
		/* Makes a new cluster containing element e and returns its position */
		public Position<E> makeCluster(E e){
			return new Locator<E>(e);
		}
		
		/* Finds the cluster containing the element identified by Position p
		 * and returns the Position of the cluster's leader
		 */
		public Position<E> find(Position<E> p){
			Locator<E> loc = validate(p);
			if(loc.parent != loc){
				loc.parent = (Locator<E>) find(loc.parent);
			}
			
			return loc.parent;
		}
		
		/* Merges the clusters containing elements with positions p and q (if distinct) */
		public void union(Position<E> p, Position<E> q){
			Locator<E> a = (Locator<E>) find(p);
			Locator<E> b = (Locator<E>) find(q);
			
			if(a != b){
				if(a.size > b.size){
					b.parent = a;
					a.size += b.size; 
				} else{
					a.parent = b;
					b.size += a.size;
				}
			}
		}
		private Locator<E> validate(Position<E> p) {
			// TODO Auto-generated method stub
			return null;
		}

		/* ---- nested Locator class ---- */
		private class Locator<E> implements Position<E>{
			public E element;
			public int size;
			public Locator<E> parent;
			
			public Locator(E elem){
				element = elem;
				size = 1;
				parent = this;				// convention for a cluster leader
			}
			
			public E getElement(){
				return element;
			}
		}
	}
}
