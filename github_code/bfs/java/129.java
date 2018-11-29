package edu.berkeley.guir.prefuse.graph;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;

import edu.berkeley.guir.prefuse.collections.BreadthFirstGraphIterator;
import edu.berkeley.guir.prefuse.collections.EdgeNodeComparator;

/**
 * Library of routines for creating or performing operations on graphs
 *  and trees.
 * 
 * @version 1.0
 * @author <a href="http://jheer.org">Jeffrey Heer</a> prefuse(AT)jheer.org
 */
public class GraphLib {

    // ========================================================================
    // == GRAPH SEARCH METHODS ================================================
    
    public static Node[] search(Graph g, String attr, String value) {
        ArrayList nodes = new ArrayList();
        Iterator iter = g.getNodes();
        while ( iter.hasNext() ) {
            Node n = (Node)iter.next();
            String val = n.getAttribute(attr);
            if ( val != null && val.equals(value) ) {
                nodes.add(n);
            }
        }
        return (Node[])nodes.toArray(new Node[nodes.size()]);
    } //
    
    public static Node[] getMostConnectedNodes(Graph g) {
        ArrayList nodes = new ArrayList();
        int size = -1, c;
        Iterator iter = g.getNodes();
        while ( iter.hasNext() ) {
            Node n = (Node)iter.next();
            if ( (c=n.getEdgeCount()) > size ) {
                size = c;
                nodes.clear();
                nodes.add(n);
            } else if ( c == size ) {
                nodes.add(n);
            }
        }
        return (Node[])nodes.toArray(new Node[nodes.size()]);
    } //
    
    // ========================================================================
    // == TREE METHODS ========================================================
    
    /**
     * Returns a Tree object, representing a breadth-first-search tree
     * rooted at the specified node. This is one useful way of imposing
     * a tree structure on a general graph. The only requirement is that
     * the graph nodes are instances of the TreeNode class.
     * @param r the root of the breadth-first-search.
     * @return the breadth-first-search tree.
     */
    public static Tree breadthFirstTree(TreeNode r) {
        if ( r == null ) { return null; }
        
        Iterator iter = new BreadthFirstGraphIterator(r);
        while ( iter.hasNext() ) {
            TreeNode n = (TreeNode)iter.next();
            n.removeAllAsChildren();
        }
        
        HashSet    visited = new HashSet();
        LinkedList queue   = new LinkedList();
        queue.add(r);
        visited.add(r);
        
        r.setParentEdge(null);
        
        while ( !queue.isEmpty() ) {
            TreeNode n = (TreeNode)queue.removeFirst();     
            iter = n.getNeighbors();
            while ( iter.hasNext() ) {
                TreeNode c = (TreeNode)iter.next();
                if ( !visited.contains(c) ) {
                    n.setAsChild(c);
                    queue.add(c);
                    visited.add(c);
                }
            }
        }
        return new DefaultTree(r);
    } //
    
    /**
     * Sorts a tree, ordering each sibling group according to the provided
     * comparator
     * @param tree the Tree to sort
     * @param comp the comparator that determines the sorting order
     */
    public static void sortTree(Tree tree, Comparator comp) {
        TreeNode root = tree.getRoot();
        sortHelper(root, new EdgeNodeComparator(comp));
    } //

    private static void sortHelper(TreeNode node, EdgeNodeComparator c) {
        ArrayList list = new ArrayList();
        
        // copy each child node into the buffer list
        Iterator iter = node.getChildEdges();
        while ( iter.hasNext() )
            list.add(iter.next());
        
        // set up the comparator, sort the list according to it
        c.setIgnoredNode(node);
        Collections.sort(list, c);
        
        // remove all children from the node
        node.removeAllChildren();
        
        // add the children back in their sorted order
        iter = list.iterator();
        while ( iter.hasNext() ) {
            Edge e = (Edge)iter.next();
            node.addChild(e);
            sortHelper((TreeNode)e.getAdjacentNode(node), c);
        }
    } //
    
    /**
     * Helper method for index hunting.
     */
    public static int nearestIndex(TreeNode n, TreeNode p) {
        int idx = 0;
        for ( int i=0; i<n.getEdgeCount(); i++ ) {
            TreeNode c = (TreeNode)n.getNeighbor(i);
            if ( c == p )
                return idx;
            else if ( c.getParent() == n ) {
                idx++;
            }
        }
        return n.getChildCount();       
    } //
    
    public static int getTreeHeight(Tree t) {
        TreeNode r = t.getRoot();
        return getTreeHeightHelper(r,0);
    } //
    
    private static int getTreeHeightHelper(TreeNode n, int height) {
        int h = height;
        if ( n.getChildCount() > 0 ) {
            Iterator childIter = n.getChildren();
            while ( childIter.hasNext() ) {
                TreeNode c = (TreeNode)childIter.next();
                h = Math.max(h, getTreeHeightHelper(c,height+1));
            }
        }
        return h;
    } //
    
    
    // ========================================================================
    // == GRAPH CREATION ROUTINES =============================================
    
    /**
     * Builds a completely unconnected (edge-free) graph with the given 
     * number of nodes
     * @param n the number of nodes
     * @return a graph with n nodes and no edges
     */
    public static Graph getNodes(int n) {
        Graph g = new DefaultGraph();
        for ( int i=0; i < n; i++ ) {
            Node nn = new DefaultTreeNode();
            nn.setAttribute("label",String.valueOf(i));
            g.addNode(nn);
        }
        return g;
    } //
    
    /**
     * Builds a "star" graph with one central hub connected to the given
     * number of satellite nodes.
     * @param n the number of points of the star
     * @return a "star" graph with n points, for a total of n+1 nodes
     */
    public static Graph getStar(int n) {
        Graph g = new DefaultGraph();
        Node r = new DefaultTreeNode();
        r.setAttribute("label","0");
        g.addNode(r);
        for ( int i=1; i <= n; i++ ) {
            Node nn = new DefaultTreeNode();
            nn.setAttribute("label",String.valueOf(i));
            g.addNode(nn);
            Edge e = new DefaultEdge(nn, r);
            g.addEdge(e);
        }
        return g;
    } //
    
    /**
     * Returns a clique of given size. A clique is a graph in which every node
     * is a neighbor of every other node.
     * @param n the number of nodes in the graph
     * @return a clique of size n
     */
    public static Graph getClique(int n) {
        Graph g = new DefaultGraph();
        Node nodes[] = new Node[n];
        for ( int i = 0; i < n; i++ ) {
            nodes[i] = new DefaultTreeNode();
            nodes[i].setAttribute("label", String.valueOf(i));
            g.addNode(nodes[i]);
        }
        for ( int i = 0; i < n; i++ ) {
            for ( int j = i; j < n; j++ )
                if ( i != j )
                    g.addEdge(new DefaultEdge(nodes[i], nodes[j]));
        }
        return g;
    } //
    
    /**
     * Returns a graph structured as an m-by-n grid.
     * @param m the number of rows of the grid
     * @param n the number of columns of the grid
     * @return an m-by-n grid structured graph
     */
    public static Graph getGrid(int m, int n) {
        Graph g = new DefaultGraph();
        Node[] nodes = new Node[m*n];
        for ( int i = 0; i < m*n; i++ ) {
            nodes[i] = new DefaultTreeNode();
            nodes[i].setAttribute("label", String.valueOf(i));
            g.addNode(nodes[i]);
            if ( i >= n )
                g.addEdge(new DefaultEdge(nodes[i-n], nodes[i]));
            if ( i % n != 0 )
                g.addEdge(new DefaultEdge(nodes[i-1], nodes[i]));
        }
        return g;
    } //
    
} // end of class GraphLib
