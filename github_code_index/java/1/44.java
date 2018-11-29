/**
 *  File: SAP.java
 *  Package: 
 *  Project: alg-ass-WordNet
 *  Created on: Apr 3, 2013
 * 
 *  Description: Programming Assignment 1, Algorithms II
 *
 *  @author: Huang Zhu
 *  Department of Computing and Information Sciences
 *  Kansas State University
 */

import java.util.Iterator;

public class SAP {
	private int V;
	
	//keep a path for each vertex
	//Problem: cause out of memory exception
	//private BreadthFirstDirectedPaths[] sp;
	
	//the associated digraph
	private final Digraph digraph;
	
	//cache of existing BFS Paths of vertices
	//Problem: may cause out of memory exception
	//private ST<Integer, DeluxeBFS> idToBFS;

	// constructor takes a digraph (not necessarily a DAG)
	public SAP(Digraph G) {
		//make a defensive copy using copy constructor
		digraph = new Digraph(G); 
		//idToBFS =  new ST<Integer, DeluxeBFS>();
		
		V = G.V();
		//sp = new BreadthFirstDirectedPaths[V];
		//for (int i = 0; i < V; i++) 
			//sp[i] = new BreadthFirstDirectedPaths(G, i);
	}
	
	// length of shortest ancestral path between v and w;
	// -1 if no such path
	public int length(int v, int w) {
	    if (v < 0 || v >= V) 
	    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
	    if (w < 0 || w >= V) 
	    	throw new IndexOutOfBoundsException("vertex " + w + " is not between 0 and " + (V-1));
	    
	    //if (!idToBFS.contains(v))
	    	//idToBFS.put(v, new DeluxeBFS(digraph, v));
	    //if (!idToBFS.contains(w))
	    	//idToBFS.put(w, new DeluxeBFS(digraph, w));
	    DeluxeBFS vBFS = new DeluxeBFS(digraph, v); //idToBFS.get(v);
	    DeluxeBFS wBFS = new DeluxeBFS(digraph, w); //idToBFS.get(w);
		SET<Integer> vAncestor = (SET<Integer>)(vBFS).destinations();
		SET<Integer> wAncestor = (SET<Integer>)(wBFS).destinations();
		SET<Integer> common = vAncestor.intersects(wAncestor);
		
		int minDistance = V;
		int minAncestor = V;
		for (int temp : common) {
			int tempDistance = vBFS.distTo(temp) + wBFS.distTo(temp);
			if (tempDistance < minDistance) {
				minDistance = tempDistance;
				minAncestor = temp;
			}
		}
		
		if (minDistance != V)
			return minDistance;
		else
			return -1;
	}
	
	// a common ancestor of v and w that participates in a shortest
	// ancestral path; -1 if no such path
	public int ancestor(int v, int w) {
	    if (v < 0 || v >= V) 
	    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
	    if (w < 0 || w >= V) 
	    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
	    
	    //if (!idToBFS.contains(v))
	    	//idToBFS.put(v, new DeluxeBFS(digraph, v));
	    //if (!idToBFS.contains(w))
	    	//idToBFS.put(w, new DeluxeBFS(digraph, w));
	    DeluxeBFS vBFS = new DeluxeBFS(digraph, v); //idToBFS.get(v);
	    DeluxeBFS wBFS = new DeluxeBFS(digraph, w); //idToBFS.get(w);
		SET<Integer> vAncestor = (SET<Integer>)(vBFS).destinations();
		SET<Integer> wAncestor = (SET<Integer>)(wBFS).destinations();
		SET<Integer> common = vAncestor.intersects(wAncestor);
		
		int minDistance = V;
		int minAncestor = V;
		for (int temp : common) {
			int tempDistance = vBFS.distTo(temp) + wBFS.distTo(temp);
			if (tempDistance < minDistance) {
				minDistance = tempDistance;
				minAncestor = temp;
			}
		}
		
		if (minDistance != V)
			return minAncestor;
		else
			return -1;
	}
	
	// length of shortest ancestral path between any vertex in v and any vertex in w
	// -1 if no such path
	public int length(Iterable<Integer> v, Iterable<Integer> w) {
		for (int a : v) {
		    if (a < 0 || a >= V) 
		    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
		}
		
		for (int b : w) {
		    if (b < 0 || b >= V) 
		    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
		}
		
		DeluxeBFS vBFS = new DeluxeBFS(digraph, v);
		DeluxeBFS wBFS = new DeluxeBFS(digraph, w);

		SET<Integer> vAncestor = (SET<Integer>)(vBFS).destinations();
		SET<Integer> wAncestor = (SET<Integer>)(wBFS).destinations();
		
		SET<Integer> common = vAncestor.intersects(wAncestor);
		
		int minDistance = V;
		int minAncestor = V;
		for (int temp : common) {
			int tempDistance = vBFS.distTo(temp) + wBFS.distTo(temp);
			if (tempDistance < minDistance) {
				minDistance = tempDistance;
				minAncestor = temp;
			}
		}
		
		if (minDistance != V)
			return minDistance;
		else
			return -1;
	}

	// a common ancestor that participates in shortest ancestral path;
	// -1 if no such path
	public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
		for (int a : v) {
		    if (a < 0 || a >= V) 
		    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
		}
		
		for (int b : w) {
		    if (b < 0 || b >= V) 
		    	throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
		}
		
		DeluxeBFS vBFS = new DeluxeBFS(digraph, v);
		DeluxeBFS wBFS = new DeluxeBFS(digraph, w);

		SET<Integer> vAncestor = (SET<Integer>)(vBFS).destinations();
		SET<Integer> wAncestor = (SET<Integer>)(wBFS).destinations();
		
		SET<Integer> common = vAncestor.intersects(wAncestor);
		
		int minDistance = V;
		int minAncestor = V;
		for (int temp : common) {
			int tempDistance = vBFS.distTo(temp) + wBFS.distTo(temp);
			if (tempDistance < minDistance) {
				minDistance = tempDistance;
				minAncestor = temp;
			}
		}
		
		if (minDistance != V)
			return minAncestor;
		else
			return -1;
	}
	
	// unit test
	public static void main(String[] args) {
		In in = new In("./wordnet/digraph1.txt");
		Digraph G = new Digraph(in);
		SAP sap = new SAP(G);
		while(!StdIn.isEmpty()) {
			int v = StdIn.readInt();
			int w = StdIn.readInt();
			int length = sap.length(v, w);
			int ancestor = sap.ancestor(v, w);
			StdOut.printf("length = %d,  ancestor = %d\n", length, ancestor);
		}
	}

}
