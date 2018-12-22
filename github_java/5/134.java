/*
 * Depth-first search on a DirectedGraph: a Collection of DepthFirstTrees.
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
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;

import edu.byu.ece.graph.DirectedGraph;
import edu.byu.ece.graph.Edge;
import edu.byu.ece.graph.GraphForest;

/**
 * This class performs a depth-first search on a DirectedGraph. A depth first
 * search is represented as a Collection of {@link DepthFirstTree}s.
 * <p>
 * TODO: all of the graph operations need to be defined.
 */
public class DepthFirstSearchForest implements GraphForest {

    /**
     * Create an empty search.
     */
    public DepthFirstSearchForest() {
    }

    /**
     * Create a depth-first search with the nodes contained in the given
     * DirectedGraph
     * 
     * @param graph DirectedGraph containing nodes to be added to the search
     */
    public DepthFirstSearchForest(DirectedGraph graph) {
        this(graph, new ArrayList(graph.getNodes()));
    }

    /**
     * Create a depth-first search with the nodes contained in the given
     * DirectedGraph
     * 
     * @param graph DirectedGraph containing nodes to be added to the search
     * @param nodesInOrder A List of the nodes in order
     */
    public DepthFirstSearchForest(DirectedGraph graph, List nodesInOrder) {
        _graph = graph;
        _search(nodesInOrder);
    }

    public DepthFirstSearchForest(DirectedGraph graph, Object root) {
        //_invert = invertDirection;
        _graph = graph;
        ArrayList visitOrder = new ArrayList(graph.getNodes());
        visitOrder.remove(root);
        visitOrder.add(0, root);
        _search(visitOrder);
    }

    /**
     * Search all the DepthFirstTree objects in the current DepthFirstSearch
     * object for the given node and return true if found.
     * 
     * @param node The given node
     * @return true if the DepthFirstSearch object contains the node in any of
     * the DepthFirstTree objects. Otherwise, false.
     */
    public boolean containsNode(Object node) {
        for (DepthFirstTree tree : _trees) {
            if (tree.getNodes().contains(node))
                return true;
        }
        return false;
    }

    /**
     * @return List of trees in ascending order (DepthFirstTree)
     */
    public List getAscendingTreeList() {
        return _getSortedTreeList(true);
    }

    /**
     * @return List of trees in descending order
     */
    public List getDescendingTreeList() {
        return _getSortedTreeList(false);
    }

    public Collection getEdges() {
        throw new RuntimeException("getEdges currently not supported");
    }

    public List getFinishList() {
        List list = new ArrayList();
        for (DepthFirstTree tree : _trees) {
            list.addAll(tree.getFinishList());
        }
        return list;
    }

    public DirectedGraph getGraph() {
        return _graph;
    }

    public Collection getNodes() {
        throw new RuntimeException("getNodes currently not supported");
    }

    public List getReveresedFinishList() {
        ArrayList list = new ArrayList();
        List<DepthFirstTree> reversedTreeList = BasicDepthFirstSearchTree.reverseList(_trees);
        for (DepthFirstTree tree : reversedTreeList) {
            list.addAll(tree.getTopologicalSort());
        }
        return list;
    }

    public Collection<DepthFirstTree> getTrees() {
        return new ArrayList<DepthFirstTree>(_trees);
    }

    public void removeSingleNodeTrees() {
        Collection<DepthFirstTree> multiNodeTrees = new ArrayList<DepthFirstTree>(_trees.size());
        //System.out.println("Date "+new Date());
        for (DepthFirstTree tree : _trees) {
            if (tree.getNodes().size() > 1)
                multiNodeTrees.add(tree);
        }
        //System.out.println("Date "+new Date());
        _trees = new ArrayList<DepthFirstTree>(multiNodeTrees);
        //_trees.removeAll(removeTrees);
        //System.out.println("Date "+new Date());
    }

    public Edge getEdge(Object source, Object sink) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getSuccessors(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getPredecessors(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getDescendents(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public DirectedGraph getSubGraph(Collection nodes) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getAncestors(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getInputEdges(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public Collection getOutputEdges(Object node) {
        throw new RuntimeException("getEdges currently not supported");
    }

    public DirectedGraph invert() {
        throw new RuntimeException("invert currently not supported");
    }

    /**
     * Return a List of the DFS trees in sorted order where the trees are sorted
     * on a basis of size.
     * 
     * @param ascending If true, sort the trees in ascending order. If false,
     * sort the trees in descending order.
     * @return List of sorted trees.
     */
    protected List _getSortedTreeList(boolean ascending) {
        TreeMap sortedSCCs = new TreeMap();
        for (DepthFirstTree tree : getTrees()) {
            // put the collection into the "tree sort sorter"
            sortedSCCs.put(tree, null);
        }

        // The key set is sorted in ascending order.
        Collection ascendingSCCList = sortedSCCs.keySet();
        if (ascending)
            return new ArrayList(ascendingSCCList);

        // Reverse the order
        List descendingSCCList = new ArrayList();
        for (Iterator i = ascendingSCCList.iterator(); i.hasNext();) {
            descendingSCCList.add(0, i.next());
        }
        return descendingSCCList;
    }

    protected DirectedGraph _graph;

    /**
     * This method performs the top-level depth first search on directed graph.
     * The order in which the graph Nodes are visited is determined by the List
     * parameter. This method will sequentially visit each Node in the list and
     * call the recursive _visit method. The _visit method will visit all
     * "successor" Nodes of the chosen Node (excluding feedback). When visit is
     * completed, this method will choose the next unvisited item in the list.
     * Each call to _visit from this method will create a new spanning tree in
     * the depth first search.
     * 
     * @param nodesInorder A List of the nodes which will be traverse in the
     * order given. Any necessary sorting should be done by the caller.
     */
    protected void _search(List nodesInorder) {

        _trees = new ArrayList<DepthFirstTree>();
        Iterator i = nodesInorder.iterator();

        // Iterate over all nodes in the collection
        while (i.hasNext()) {
            Object node = i.next();

            /*
             * If the node has been visited, skip it. Otherwise, the node is a
             * root of a new depth first search tree.
             */
            if (containsNode(node))
                continue;

            if (DEBUG)
                System.out.println("New Tree Node " + node);

            DepthFirstTree tree = null;
            tree = new BasicDepthFirstSearchTree(this, _graph, node);
            _trees.add(tree);

        }
    }

    //protected boolean _invert;
    protected List<DepthFirstTree> _trees;

    protected static boolean DEBUG = false;

}
