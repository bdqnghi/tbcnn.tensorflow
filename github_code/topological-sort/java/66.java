/*
  Copyright (c) 1999, 2000 Brown University, Providence, RI
  
                            All Rights Reserved
  
  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose other than its incorporation into a
  commercial product is hereby granted without fee, provided that the
  above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation, and that the name of Brown University not be used in
  advertising or publicity pertaining to distribution of the software
  without specific, written prior permission.
  
  BROWN UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
  SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR ANY PARTICULAR PURPOSE.  IN NO EVENT SHALL BROWN
  UNIVERSITY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
  DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
  PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
  TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
  PERFORMANCE OF THIS SOFTWARE.
*/

package nz.ac.waikato.jdsl.graph.algo;

import nz.ac.waikato.jdsl.core.api.Sequence;
import nz.ac.waikato.jdsl.core.ref.NodeSequence;
import nz.ac.waikato.jdsl.graph.api.*;

/**
  * This abstract class is the foundation for both types
  * of topological sorts, that is, the standard variety where
  * each vertex is given a unique number, and the level-numbering
  * variety in which numbers attached to vertices are not unique.
  *
  * The algorithm can be constructed once, and used multiple times.
  * The algorithm object is executed by calling the execute(InspectableGraph)
  * method. After execution, the client can query the algorithm object for
  * the numbers of particular vertices. The client should then call 
  * the cleanup() method, to ensure that all decorations are removed from
  * the graph. The cleanup() method should be called after each execution 
  * of the algorithm.
  *
  * The topological sorts yield useful results only on a directed
  * acyclic graph (DAG).
  *
  * Before querying for results, the client can use the public isCyclic()
  * method to verify whether the graph was acyclic or not.
  *
  * If a graph with undirected edges is passed in to execute(.), an
  * InvalidEdgeException is thrown immediately.
  *
  * If the graph is found to have cycles, the calls to number(Vertex)
  * will result in an InvalidQueryException.
  * 
  * Note that this algorithm will give valid results on disconnected as 
  * well as connected graphs.
  *
 * @author Lucy Perry (lep)
  *
  * @version JDSL 2.1.1 
  *
  * @see TopologicalSort
  * @see UnitWeightedTopologicalNumbering
  */


public abstract class AbstractTopologicalSort {


  /**
    * The Graph that the algorithm executes upon.
    * It is passed in via the constructor.
    */
  protected InspectableGraph graph_;


  /**
    * Whether the graph has cycles or not.
    * Boolean to be calculated during the execute() method.
    */
  protected boolean is_cyclic_;
  


  /**
    * This Object is the key for the numbering Decoration.
    * It is used  to retrieve the topological order-number
    * for a given Vertex. This key can be used by the client as a 
    * an equivalent alternative to the public accessor method number(Vertex).
    *
    * Note that attempting to access a topological number using this key
    * may result in an InvalidAttributeException or an invalid number - 
    * if the graph was found to have cycles, or if execute(.) has not yet
    * been called, or if cleanup() was not called after a previous execution. 
    */
  public Object NUMBER_KEY_;
  
  
  /**
    * Sequence used as a queue by the sort() method.
    */
  protected Sequence queue_;



  /**
    * Constructor.
    */
  public AbstractTopologicalSort(){
  }



  /**
    * The client calls this method to execute the algorithm.
    *
    * Note that if a null InspectableGraph g is passed in to this method,
    * a NullPointerException will result from init(InspectableGraph).
    *
    * After an execution of the algorithm, the cleanup() method should
    * be called before execute() gets called again.
    *
    * @param g the graph upon which the algo is executed
    * @exception InvalidEdgeException if an undirected edge is found in g
    */
  public void execute(InspectableGraph g) throws InvalidEdgeException{
    init(g);//sets up and takes care of the IEE
    sort();//runs the actual algorithm
  }



  /**
    * This helper method is called by the execute(.) method.
    * It performs all setup work, and ensures that all Edges are directed.
    *
    * Takes O(E) time, where E = number of Edges in the Graph.
    *
    * @param g the graph upon which the algo is executed
    * @exception InvalidEdgeException if an undirected Edge is found
    */
  protected void init(InspectableGraph g) throws InvalidEdgeException{
    graph_ = g;
    NUMBER_KEY_ = new Object();
    queue_ = new NodeSequence();

    //make sure all edges are directed
    EdgeIterator ei = graph_.edges();
    while (ei.hasNext()){
      Edge e = ei.nextEdge();
      if (!graph_.isDirected(e)){
	throw new InvalidEdgeException("All edges must be directed");
      }
    }
  }


  /**
    * This abstract method is overridden in the subclasses.
    * It is called from within execute(.).
    *
    * @see TopologicalSort
    * @see UnitWeightedTopologicalNumbering
    */
  protected abstract void sort();



  

  /**
    * Used for retrieving the topological order-number associated with
    * the given Vertex.
    *
    * Takes O(1) time.
    *
    * Note that this method does not check against a null or invalid
    * Vertex v. If a null or invalid Vertex is passed in, the result
    * will be a NullPointerException, or an InvalidAttributeException
    *
    * This should not be called until execute(.) has already been called.
    * Doing so will result in an InvalidAttributeException.
    *
    * @param v a vertex 
    * @return the topological order-number associated with v 
    * @exception InvalidQueryException if the Graph has cycles
    */
  public int number(Vertex v) throws
    InvalidQueryException, InvalidVertexException {
    if (is_cyclic_){
      throw new InvalidQueryException("Can't get the numbering because the "
				       + "graph contains cycles");
    }
    return ((Integer)v.get(NUMBER_KEY_)).intValue();
  }





  /**
    * Query method for asking whether the Graph is cyclic, 
    * (and therefore inappropriate for a topological ordering).
    *
    * Takes O(1) time, since this boolean was already computed during 
    * algorithm execution.
    *
    * This method should not be called until execute(.) has already been 
    * called. Doing so will yield a boolean answer, but a meaningless one.
    *
    * @return boolean
    */
  public boolean isCyclic() throws InvalidQueryException{
    return is_cyclic_;
  }



  /**
    * Cleans up all decorations that this algorithm was storing in the 
    * provided graph. This should be called after the user has completely
    * finished everything resulting from a single DFS execution.
    *
    * Note that calling this method before calling execute(.), while
    * incorrect, will simply do nothing.
    */
  public void cleanup(){
    if (graph_ != null){//if this is called w/ no graph, nothing happens
      VertexIterator vertices = graph_.vertices();
      while(vertices.hasNext()){
	Vertex currentVertex = vertices.nextVertex();
	//Test if the vertex is decorated, because if graph is cyclic,
	//then all vertices may not be visited.
	if (currentVertex.has(NUMBER_KEY_)){
	  currentVertex.destroy(NUMBER_KEY_);
	}
      }
      //set the state to be like pre-execution
      graph_ = null;
    }
  }


}
