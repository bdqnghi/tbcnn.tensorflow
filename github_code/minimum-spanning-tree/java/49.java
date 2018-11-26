package com.brianthetall.cs;

import java.lang.Integer;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.HashSet;

public class MinimumSpanningTree{

    /**
     * MinimumSpanningTree.Cluster<V extends GraphInterface.Vertex> is used by MinimumSpanningTree.kruskal() to group connected vertex's
     * As Clusters connect together, one cluster consumes the other
     */
    public static class Cluster<V extends GraphInterface.Vertex>{

	private Set<V> visited;
	private int clusterId;
	private static Random r;

	public int getId(){
	    return clusterId;
	}

	public Set<V> getSet(){
	    return visited;
	}

	/* 
	 * @param v Vertex to search for inside this Cluster
	 * @return true if this Cluster.visited Set contains this Vertex
	 */
	public boolean contains(V v){
	    return visited.contains(v);
	}

	public void add(V v){
	    visited.add(v);//FOR FAST-FAILURE
	}

	public void merge(Cluster c){
	    if(c!=null){
		this.visited.addAll(c.getSet());
	    }
	}

	public String toString(){
	    return new Integer(clusterId).toString()+" "+visited.toString();

	}

	public Cluster(){
	    if(r==null)
		r=new Random();
	    visited=new HashSet<V>(16,(float)0.5);
	    clusterId=r.nextInt();
	}

    }

    private MinimumSpanningTree(){}
    
    public static List<GraphInterface.Vertex.Edge> kruskal(UndirectedGraph graph){

	GraphInterface.Vertex.Edge[] sorted=graph.getSortedEdges();//SORTED EDGES OF GRAPH
	List<GraphInterface.Vertex.Edge> retval=new ArrayList<GraphInterface.Vertex.Edge>(sorted.length);//List of MST Edges
	List<Cluster<GraphInterface.Vertex>> clusters = new ArrayList<Cluster<GraphInterface.Vertex>>();//List of Clusters
	clusters.add(new Cluster());//Root cluster

	Set<GraphInterface.Vertex> visited=new HashSet<>(16,(float)0.5);//O(1) search will be useful
	retval.add(sorted[0]);//the shortest is always used; helps get things started
	visited.add(sorted[0].getStart());
	visited.add(sorted[0].getTarget());
	clusters.get(0).add(sorted[0].getStart());//the ROOT cluster get these Vertex's
	clusters.get(0).add(sorted[0].getTarget());

	//System.out.println("Edge:"+sorted[0]+" to Cluster:"+clusters.get(0));

	for(int i=2;i<sorted.length;i+=2){//FOR SORTED EDGE LIST, STARTING @ 1
	    
	    List<Cluster<GraphInterface.Vertex>> owners=whoOwns(sorted[i],clusters);//FIND OWNERS FOR THIS EDGE'S VERTEXS
	    if(owners.size()==0){//if neither vertex is owned, create a new cluster, and add these vertexs into it

		//none of the existing clusters can claim the new Vertex
		clusters.add(new Cluster());
		Cluster virginCluster = clusters.get(clusters.size()-1);
		virginCluster.add(sorted[i].getTarget());
		virginCluster.add(sorted[i].getStart());
		visited.add(sorted[i].getTarget());
		visited.add(sorted[i].getStart());
		retval.add(sorted[i]);

		//System.out.println("Edge:"+sorted[i]+" Making new Cluster:"+virginCluster);
		
	    }else if(owners.size()==1){//if one vertex is in this Cluster, add the other vertex to this cluster
		
		owners.get(0).add(sorted[i].getStart());
		owners.get(0).add(sorted[i].getTarget());
		visited.add(sorted[i].getTarget());
		visited.add(sorted[i].getStart());
		retval.add(sorted[i]);

		//System.out.println("Edge:"+sorted[i]+" Causing something to be added into CLuster:"+owners.get(0));
		
	    }else if(owners.size()==2 && owners.get(0).equals(owners.get(1)) ){//if both vertexs are in the same Cluster, this is a garbage-edge
		//System.out.println("WASTE EDGE:"+sorted[i]);
		;
	    }else if(owners.size()==2){//if both vertexs are in different Clusters, merge the clusters into the Cluster with lowest index; converge to ROOT

		retval.add(sorted[i]);//THIS EDGE IS PART OF MST
		//System.out.println("Edge:"+sorted[i]+" Merging Clusters:"+owners.get(0)+" & "+owners.get(1));

		if(owners.contains(clusters.get(0))){//merge to ROOT
		    
		    if(owners.get(0).equals(clusters.get(0))){
			owners.get(0).merge(owners.get(1));
			clusters.remove(owners.get(1));
		    }
		    else{
			owners.get(1).merge(owners.get(0));
			clusters.remove(owners.get(0));
		    }
		    
		}else{//merge to dont care
		    owners.get(0).merge(owners.get(1));

		    clusters.remove(owners.get(1));
		}
		
	    }else{System.err.println("Min-Span-Tree.Kruskal ERROR");}
	    
	}
	
	return retval;
    }
    
    /*
     * Determine which, if any, and all Clusters that currently lay claim to a Vertex tracked in this Edge
     * returns 2 of the same Cluster if both vertexs are owns by the same Cluster
     * @return List<GraphInterface.Vertex> c
     *
     * the old Cluster is being returned, after that cluster has already been merged with some other cluster!!!!
     */
    private static List<Cluster<GraphInterface.Vertex>> whoOwns(GraphInterface.Vertex.Edge e, List<Cluster<GraphInterface.Vertex>> universe){
	
	List<Cluster<GraphInterface.Vertex>> retval=new ArrayList<>(2);//cannot be more than 2 owners
	
	for(int i=0;i<universe.size();i++){//FOR EACH GALAXY:
	    
	    if( universe.get(i).contains(e.getStart()) && universe.get(i).contains(e.getTarget()) ){
		retval.add(universe.get(i));
		retval.add(universe.get(i));
		return retval;
	    }
	    else if( universe.get(i).contains(e.getStart()) || universe.get(i).contains(e.getTarget()) )
		retval.add(universe.get(i));
	}
	
	return retval;
    }
    
    public static void main(String args[]){
	//currently being tested by UndirectedGraph.class
    }

}
