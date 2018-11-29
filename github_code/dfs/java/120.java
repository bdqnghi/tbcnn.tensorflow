/*
 * Depth first search composed of strongly connected component (SCC) trees.
 * 
 * Copyright (c) 2008 Brigham Young University
 * 
 * This file is part of the BYU EDIF Tools.
 * 
 * BYU EDIF Tools is free software: you may redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option) any
 * later version.
 * 
 * BYU EDIF Tools is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * A copy of the GNU General Public License is included with the BYU EDIF Tools.
 * It can be found at /edu/byu/edif/doc/gpl2.txt. You may also get a copy of the
 * license at <http://www.gnu.org/licenses/>.
 * 
 */
package edu.byu.ece.graph.dfs;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import edu.byu.ece.edif.util.graph.GraphNodeSizeComparator;
import edu.byu.ece.graph.DirectedGraph;

/**
 * A depth first search object that is composed of strongly connected component (SCC)
 * trees.
 * 
 * This object creates the SCCs by performing two depth-first searches as described by
 * the Tarjan's SCC decomposition algorithm.
 * 
 * @author Mike Wirthlin
 */
public class SCCDepthFirstSearch extends DepthFirstSearchForest {

    public SCCDepthFirstSearch(DirectedGraph graph) {
        List nodesInOrder = new ArrayList();
        nodesInOrder.addAll(graph.getNodes());
        _init(graph, nodesInOrder);
    }
    
    public SCCDepthFirstSearch(DirectedGraph graph, List nodesInOrder) {
        _init(graph, nodesInOrder);
    }
    
    public void _init(DirectedGraph graph, List nodesInOrder) {
        _graph = graph;

        Date startTime = new Date();
        if (localDEBUG)
            System.out.print("Starting DFS1 . . . ");

        // 1. Perform the search first on the inverted graph 
        DepthFirstSearchForest dfs1 = new DepthFirstSearchForest(graph.invert(), nodesInOrder);
        long seconds = (new Date().getTime() - startTime.getTime()) / 1000;
        if (localDEBUG)
            System.out.println("finished in " + seconds + " seconds. " + dfs1.getTrees().size() + " trees.");

        startTime = new Date();
        if (localDEBUG)
            System.out.print("Starting DFS2 . . . ");

        _search(dfs1.getReveresedFinishList());

        seconds = (new Date().getTime() - startTime.getTime()) / 1000;
        if (localDEBUG)
            System.out.println("finished in " + seconds + " seconds." + this.getTrees().size() + " trees.");

        if (localDEBUG)
            System.out.println("SCCs found:" + this.getTrees().size());
    }

    /**
     * @deprecated Use SCCDepthFirstSearch(DirectedGraph)
     * @param firstDFS
     */
    @Deprecated
    public SCCDepthFirstSearch(DepthFirstSearchForest firstDFS) {
        super(firstDFS._graph.invert(), firstDFS.getReveresedFinishList());
    }

    /*
     * (non-Javadoc)
     * 
     * @see edu.byu.ece.graph.dfs.DepthFirstSearchForest#containsNode(java.lang.Object)
     */
    @Override
    public boolean containsNode(Object node) {
        if (super.containsNode(node))
            return true;
        if (_singleNodes.contains(node))
            return true;
        return false;
    }

    /**
     * Return a List of the DFS trees in topologically sorted order.
     * 
     * @return List of topologically-sorted trees.
     */
    public List<DepthFirstTree> getTopologicallySortedTreeList() {
        /*
         * By the nature of the SCC Depth First Search, the default ordering of
         * the DFS trees is in topological order
         */
        return new ArrayList(_trees);
    }

    /**
     * Return a List of the DFS trees in order of size (nodes) with the largest tree
     * appearing first.
     * 
     * @return List of topologically-sorted trees.
     */
    public List<DepthFirstTree> getSizeSortedTreeList() {
    	
    	ArrayList<DepthFirstTree> sortedTrees = new ArrayList<DepthFirstTree>(_trees);
    	Collections.sort(sortedTrees, new GraphNodeSizeComparator());
    	Collections.reverse(sortedTrees);
    	return sortedTrees; 
    }

    /*
     * (non-Javadoc)
     * 
     * @see edu.byu.ece.graph.dfs.DepthFirstSearchForest#_search(java.util.List)
     */
    @Override
    protected void _search(List cellsInorder) {
        _singleNodes = new ArrayList();
        _trees = new ArrayList();
        Iterator i = cellsInorder.iterator();

        // Iterate over all cells in the collection
        for (; i.hasNext();) {
            Object node = i.next();

            // If the cell has been visited, skip it. Otherwise,
            // the cell is a root of a new depth first search tree.
            if (containsNode(node))
                continue;

            if (DEBUG)
                System.out.println("New Tree Node " + node);
            /*
             * Decide what type of tree to create. If the tree has successors,
             * create a DFSTree2. If not, create a SingleNodeDepthFirstTree
             */
            boolean singleTree = true;
            int succ = 0;
            Collection successors = _graph.getSuccessors(node);
            for (Iterator j = successors.iterator(); j.hasNext() && singleTree;) {
                Object successor = j.next();
                if (containsNode(successor))
                    succ++;
            }

            //System.out.print("successors="+successors.size() + " visited="+succ);
            DepthFirstTree tree = null;
            if (successors.size() == succ) {
                //System.out.println(" SINGLE");
                _singleNodes.add(node);
            } else {
                tree = new BasicDepthFirstSearchTree(this, _graph, node);
                _trees.add(tree);
                //System.out.println(" tree size=" + tree.getNodes().size());
            }
        }
    }

    public Collection getSingleNodes() {
        return new ArrayList(_singleNodes);
    }

    public void printSCCs() {
        System.out.println(getTopologicallySortedTreeList().size() + " trees");
        int j = 1;
        for (Iterator i = getTopologicallySortedTreeList().iterator(); i.hasNext();) {
            BasicDepthFirstSearchTree tree = (BasicDepthFirstSearchTree) i.next();
            System.out.println("Tree " + j++);
            for (Iterator k = tree.getNodes().iterator(); k.hasNext();) {
                System.out.println("\t" + k.next());
            }
        }
    }

    public String createSCCString() {
        String retVal = getTopologicallySortedTreeList().size() + " trees\n\n";
        List<String> treeStrings = new LinkedList<String>();
        for (DepthFirstTree t : getTopologicallySortedTreeList()) {
            String treeString = "Tree has " + t.getNodes().size() + " nodes\n";
            List<String> nodeStrings = new LinkedList<String>();
            for(Object o : t.getNodes()) {
                nodeStrings.add(o.toString());
            }
            Collections.sort(nodeStrings);
            for (String s : nodeStrings) {
                treeString += "\t" + s + "\n";
            }
            treeStrings.add(treeString+"\n");
        }
        Collections.sort(treeStrings);
        
        for(String treeString : treeStrings) {
            retVal += treeString;
        }
        return retVal;
    }
    
    boolean localDEBUG = false;

    Collection _singleNodes;
}

class SizeOrderedDepthFirstSearchTree implements Comparable {
	DepthFirstTree _tree;
	public SizeOrderedDepthFirstSearchTree(DepthFirstTree tree) {
		_tree = tree;
	}
	public DepthFirstTree getTree () { return _tree; }
	public int compareTo(Object o) {
		SizeOrderedDepthFirstSearchTree tree = (SizeOrderedDepthFirstSearchTree) o;
		int treeSize = tree._tree.getNodes().size();
		int mySize = _tree.getNodes().size();
		if (treeSize > mySize)
			return 1;
		if (treeSize < mySize)
			return -1;
		return 0;
	}
}

