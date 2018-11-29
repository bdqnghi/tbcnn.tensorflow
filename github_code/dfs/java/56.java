/*
 *
 * The DbUnit Database Testing Framework
 * Copyright (C)2005-2008, DbUnit.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

package org.dbunit.util.search;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.SortedSet;

import org.apache.commons.collections.set.ListOrderedSet;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.dbunit.util.CollectionsHelper;

/**
 * Search using depth-first algorithm.<br>
 * <br>
 * An instance of this class must be used only once, as it maintains the
 * internal state of the search.<br>
 * <br>
 * 
 * @author gommma (gommma AT users.sourceforge.net)
 * @author Last changed by: $Author: gommma $
 * @version $Revision: 843 $ $Date: 2008-10-26 11:06:28 +0000 (Sun, 26 Oct 2008) $
 * @since 2.4.0
 */
public class DepthFirstSearch implements ISearchAlgorithm {

  // nodes that were already scanned during the search
  private Set scannedNodes;
  private Set reverseScannedNodes;

  protected final Logger logger = LoggerFactory.getLogger(getClass());
  
  // result of the search
  private ListOrderedSet result;
  
  // input of the search
  private Set nodesFrom;

  // callback used to help the search
  private ISearchCallback callback;

  // flag, as one instance cannot be used more than once
  private boolean searching = false;
  
    /**
     * The search depth to be used when recursing through the child nodes
     */
    private int searchDepth = Integer.MAX_VALUE;

  
    /**
     * Creates a new depth-first algorithm using the maximum search depth for recursing over the nodes.
     */
    public DepthFirstSearch()
    {
        super();
    }

    /**
     * Creates a new depth-first algorithm
     * @param searchDepth The search depth to be used when traversing the nodes recursively. Must be > 0.
     * @since 2.4
     */
    public DepthFirstSearch(int searchDepth)
    {
        super();
        if(searchDepth<=0){
            throw new IllegalArgumentException("The searchDepth must be > 0. Given: " + searchDepth);
        }
        this.searchDepth = searchDepth;
    }

  /**
   * Alternative option to search() that takes an array of nodes as input (instead of a Set)
   * @see ISearchAlgorithm
   */
  public ListOrderedSet search(Object[] nodesFrom, ISearchCallback callback)
      throws SearchException 
  {
      if(logger.isDebugEnabled())
          logger.debug("search(nodesFrom={}, callback={}) - start", nodesFrom, callback);

    return search(CollectionsHelper.objectsToSet(nodesFrom), callback);
  }
  
  /**
   * @see ISearchAlgorithm
   */
  public ListOrderedSet search(Set nodesFrom, ISearchCallback callback)
      throws SearchException {
      if(logger.isDebugEnabled())
          logger.debug("search(nodesFrom={}, callback={}) - start", nodesFrom, callback);

    synchronized (this) {
      if (searching) {
        throw new IllegalStateException("already searching/searched");
      }
      this.searching = true;
    }

    // set of tables that will be returned (i.e, the declared tables and its
    // dependencies)
    this.result = new ListOrderedSet();

    // callback used to help the search
    this.callback = callback;
        
    this.nodesFrom = new ListOrderedSet();
    
    int sizeNodesFromBefore = 0;
    int sizeResultBefore = 0;
    boolean keepSearching = true;
    this.scannedNodes = new HashSet();
    this.reverseScannedNodes = new HashSet();
    this.scannedNodes = new HashSet();
    do {
      
      // In a traditional depth-first search, the getEdges() method should return only
      // edges where this node is the 'from' vertex, as the graph is known in advance.
      // But in our case, the graph is built 'on the fly', so it's possible that the
      // getEdges() also returns edges where the node is the 'to' vertex. 
      // So, before we do the "real" search, we need to do a reverse search to find out
      // all the nodes that should be part of the input.
      Iterator iterator = nodesFrom.iterator();      
      while (iterator.hasNext()) {
        Object node = iterator.next();
        reverseSearch(node, 0);
      }
//        this.nodesFrom = nodesFrom;

        // now that the input is adjusted, do the search
      iterator = this.nodesFrom.iterator();
      
      while (iterator.hasNext()) {
        Object node = iterator.next();
        search(node, 0);
      }
      
      nodesFrom = new HashSet(this.result);
      
      // decides if we continue searching
      boolean sizesDontMatch = this.result.size() != this.nodesFrom.size();
      boolean resultChanged = this.result.size() != sizeResultBefore;
      boolean nodesFromChanged = this.nodesFrom.size() != sizeNodesFromBefore;
      sizeNodesFromBefore = this.nodesFrom.size();
      sizeResultBefore = this.result.size();
      keepSearching = sizesDontMatch && ( resultChanged || nodesFromChanged );
      
    } while ( keepSearching );
    
    return this.result;

  }

  /**
   * This is the real depth first search algorithm, which is called recursively.
   * 
   * @param node node where the search starts
   * @param currentSearchDepth the search depth in the recursion
   * @return true if the node has been already searched before
   * @throws Exception if an exception occurs while getting the edges
   */
  private boolean search(Object node, int currentSearchDepth) throws SearchException {
    if ( this.logger.isDebugEnabled() ) {
      this.logger.debug( "search:" + node );
    }
    if (this.scannedNodes.contains(node)) {
      if ( this.logger.isDebugEnabled() ) {
        this.logger.debug( "already searched; returning true" );
      }
      return true;
    }
    if (!this.callback.searchNode(node)) {
      if ( this.logger.isDebugEnabled() ) {
        this.logger.debug( "Callback handler blocked search for node " + node );
      }
      return true;
    }
    
    if ( this.logger.isDebugEnabled() ) {
      this.logger.debug("Pushing " + node);      
    }
    this.scannedNodes.add(node);

    if(currentSearchDepth < this.searchDepth) {
        // first, search the nodes the node depends on
        SortedSet edges = this.callback.getEdges(node);
        if (edges != null) {
            Iterator iterator = edges.iterator();
            while (iterator.hasNext()) {
              // and recursively search these nodes
              IEdge edge = (IEdge) iterator.next();
              Object toNode = edge.getTo();
              search(toNode, currentSearchDepth++);
            }
          }
    }

    // finally, add the node to the result
    if ( this.logger.isDebugEnabled() ) {
      this.logger.debug( "Adding node " + node + " to the final result" );
    }
    // notify the callback a node was added
    this.callback.nodeAdded(node);
    result.add(node);
    
    return false;
  }

  /**
   * Do a reverse search (i.e, searching the other way of the edges) in order
   * to adjust the input before the real search.
   * @param node node where the search starts
   * @param currentSearchDepth the search depth in the recursion
   * @return true if the node has been already reverse-searched before
   * @throws Exception if an exception occurs while getting the edges
   */
  private boolean reverseSearch(Object node, int currentSearchDepth) throws SearchException {
    if ( this.logger.isDebugEnabled() ) {
      this.logger.debug( "reverseSearch:" + node );
    }
    if (this.reverseScannedNodes.contains(node)) {
      if ( this.logger.isDebugEnabled() ) {
        this.logger.debug( "already searched; returning true" );
      }
      return true;
    }
    
    if (!this.callback.searchNode(node)) {
      if ( this.logger.isDebugEnabled() ) {
        this.logger.debug( "callback handler blocked reverse search for node " + node );
      }
      return true;
    }
    
    if ( this.logger.isDebugEnabled() ) {
      this.logger.debug("Pushing (reverse) " + node);      
    }
    this.reverseScannedNodes.add(node);

    if(currentSearchDepth < this.searchDepth) {
        // first, search the nodes the node depends on
        SortedSet edges = this.callback.getEdges(node);    
        if (edges != null) {
          Iterator iterator = edges.iterator();
          while (iterator.hasNext()) {
            // and recursively search these nodes if we find a match
            IEdge edge = (IEdge) iterator.next();
            Object toNode = edge.getTo();
            if ( toNode.equals(node) ) {
              Object fromNode = edge.getFrom();
              reverseSearch(fromNode, currentSearchDepth++);
            }
          }
        }
    }
    
    // finally, add the node to the input
    this.nodesFrom.add(node);

    return false;

  }
  
  
}
