package algorithms.graph;

import java.util.HashSet;

import algorithms.sorting.Sorting;
import datastructures.graph.AdjacencyListGraph;
import datastructures.graph.Edge;
import datastructures.graph.Graph;
import datastructures.graph.Vertex;
import datastructures.set.DisjointSet;
import datastructures.set.DisjointSetForest;
import datastructures.tree.GenericHeap;

// assumes connected undirected graph
public class MinimumSpanningTree {

	// O(V^2LogV)
	//Can improve this using a Fibonacci heap to O(V^2 + VLogV)
	public static <T> HashSet<Edge> Prims(AdjacencyListGraph<T> graph, Vertex<T> root)
	{
		HashSet<Edge> mst = new HashSet<Edge>();
		
		// O(V)
		for(int i = 0; i < graph.GetVertices().length; i++)
		{
			graph.GetVertices()[i].distanceFromSource = Integer.MAX_VALUE;
			graph.GetVertices()[i].predecessor = null;
		}
		
		root.distanceFromSource = 0;
		GenericHeap<Vertex<T>> minHeap = new GenericHeap<Vertex<T>>(graph.GetVertices(), false); 
		HashSet<Vertex<T>> notInQueue = new HashSet<Vertex<T>>();
		
		// O(V^2LogV)
		while(minHeap.Size() > 0)
		{
			Vertex<T> current = minHeap.RemoveHead();
			notInQueue.add(current);
			
			// O(V)
			for(Integer key : current.adjMap.keySet())
			{
				int weight = key;
				Vertex<T> neighbor = graph.GetVertices()[current.adjMap.get(key)];
				
				//if the neighbor is in the queue and has a greater weight than weight(current, neighbor)
				if(!notInQueue.contains(neighbor) && weight < neighbor.distanceFromSource)
				{
					neighbor.predecessor = current;
					neighbor.distanceFromSource = weight;
				}
			}
		}
		
		// O(LogV)
		for(int i = 0; i < graph.GetVertices().length; i++)
		{
			if(i != root.vertex)
			{
				Vertex<T> vertex = graph.GetVertices()[i];
				mst.add(new Edge(vertex.vertex, vertex.predecessor.vertex, 0));
			}
		}
		
		return mst;
	}
	
	// O(ELogE) = O(V^2LogV)
	public static <T> HashSet<Edge> Kruskal(Graph<T> graph)
	{
		HashSet<Edge> mst = new HashSet<Edge>();
		DisjointSetForest<Vertex<T>> set = new DisjointSetForest<Vertex<T>>();
		@SuppressWarnings("unchecked")
		DisjointSet<Vertex<T>>[] sets = new DisjointSet[graph.GetVertices().length];
		
		// O(V)
		for(int i = 0; i < graph.GetVertices().length; i++)
		{
			DisjointSet<Vertex<T>> singleVertexSet = set.MakeSet(graph.GetVertices()[i]);
			sets[i] = singleVertexSet;
		}
		
		// O(ELogE) = O(V^2LogV)
		Edge[] edges =  new Edge[10];
		edges = graph.GetEdges().toArray(edges);
		Sorting.MergeSort(edges);
		
		//O(E) = O(V^2)
		for(int i = 0; i < edges.length; i++)
		{
			DisjointSet<Vertex<T>> set1 = sets[edges[i].Start];
			DisjointSet<Vertex<T>> set2 = sets[edges[i].End];
			
			if(set1 != set2)
			{
				mst.add(edges[i]);
				set.Union(set1, set2);
			}
		}
		
		return mst;
	}
}
