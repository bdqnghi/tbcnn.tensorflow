/* ***** BEGIN LICENSE BLOCK *****
 * Copyright (C) 2010-2011, The VNREAL Project Team.
 * 
 * This work has been funded by the European FP7
 * Network of Excellence "Euro-NF" (grant agreement no. 216366)
 * through the Specific Joint Developments and Experiments Project
 * "Virtual Network Resource Embedding Algorithms" (VNREAL). 
 *
 * The VNREAL Project Team consists of members from:
 * - University of Wuerzburg, Germany
 * - Universitat Politecnica de Catalunya, Spain
 * - University of Passau, Germany
 * See the file AUTHORS for details and contact information.
 * 
 * This file is part of ALEVIN (ALgorithms for Embedding VIrtual Networks).
 *
 * ALEVIN is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License Version 3 or later
 * (the "GPL"), or the GNU Lesser General Public License Version 3 or later
 * (the "LGPL") as published by the Free Software Foundation.
 *
 * ALEVIN is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * or the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * GNU Lesser General Public License along with ALEVIN; see the file
 * COPYING. If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */
package vnreal.algorithms.utils.breadthfirstsearch;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import vnreal.algorithms.utils.MiscelFunctions;
import vnreal.algorithms.utils.tree.GenericTree;
import vnreal.algorithms.utils.tree.GenericTreeNode;
import vnreal.network.Link;
import vnreal.network.Network;
import vnreal.network.Node;
import vnreal.network.substrate.SubstrateLink;
import vnreal.network.substrate.SubstrateNetwork;
import vnreal.network.substrate.SubstrateNode;
import vnreal.network.virtual.VirtualLink;
import vnreal.network.virtual.VirtualNetwork;
import vnreal.network.virtual.VirtualNode;

/**
 * Modification of the Breadth First search algorithm implementation from
 * http://blog.konem.net/java//index.php/2007/11/15/
 * breadth_first_search_algorithm_in_java_w?blog=1
 * 
 * To find a path inside a subgraph of the Substrate Network by:
 * 
 * @author Juan Felipe Botero
 * @author Lisset Diaz
 * @since 2011-2-15
 * 
 */

public class BFS {
	private NodesQueueGeneral queue;
	private Network<?, ?, ?> net;
	private Map<Node<?>, Double> sortedNR;
	private List<Node<?>> bfsTree;
	private GenericTree<Node<?>> nodeTree;

	public GenericTree<Node<?>> getNodeTree() {
		return nodeTree;
	}

	public BFS(Node<?> sourceNode, Network<?, ?, ?> net,
			Map<Node<?>, Double> sortedNR) {
		this.queue = new NodesQueueGeneral();
		this.nodeTree = new GenericTree<Node<?>>();
		this.queue.addToQueue(sourceNode);
		GenericTreeNode<Node<?>> root = new GenericTreeNode<Node<?>>(sourceNode);
		this.nodeTree.setRoot(root);
		this.net = net;
		this.sortedNR = sortedNR;
	}

	public List<Node<?>> search() {
		bfsTree = new LinkedList<Node<?>>();
		while (queue.getSize() > 0) {
			Node<?> node = queue.getFromQueue();
			if (node != null) {
				if (!bfsTree.contains(node))
					bfsTree.add(node);

				addToQueue(node);
			}
			if (sortedNR.size() == bfsTree.size())
				return bfsTree;

		}
		return null;
	}

	/**
	 * All children are in stored in String and are separated by comma.
	 **/
	private void addToQueue(Node<?> node) {
		List<Node<?>> childrenNodes;
		GenericTreeNode<Node<?>> tempNode;
		childrenNodes = getChildrenFromNode(node);
		tempNode = nodeTree.find(node);
		if (childrenNodes != null) {
			for (Iterator<Node<?>> itt = childrenNodes.iterator(); itt
					.hasNext();) {
				Node<?> child = itt.next();
				if (!bfsTree.contains(child)) {
					if (!queue.containsNode(child))
						tempNode.addChild(new GenericTreeNode<Node<?>>(child));
					queue.addToQueue(child);

				}
			}
		}
	}

	@SuppressWarnings("unchecked")
	private List<Node<?>> getChildrenFromNode(Node<?> node) {
		ArrayList<Node<?>> children = new ArrayList<Node<?>>();
		Map<Node<?>, Double> tempSortNR = new LinkedHashMap<Node<?>, Double>();
		if (net instanceof SubstrateNetwork) {
			for (Link<?> l : ((SubstrateNetwork) net)
					.getOutEdges((SubstrateNode) node))
				tempSortNR.put(((SubstrateNetwork) net)
						.getDest((SubstrateLink) l), sortedNR
						.get(((SubstrateNetwork) net)
								.getDest((SubstrateLink) l)));

			for (Link<?> l : ((SubstrateNetwork) net)
					.getInEdges((SubstrateNode) node)) {
				if (!tempSortNR.containsKey(((SubstrateNetwork) net)
						.getSource((SubstrateLink) l))) {
					tempSortNR.put(((SubstrateNetwork) net)
							.getSource((SubstrateLink) l), sortedNR
							.get(((SubstrateNetwork) net)
									.getSource((SubstrateLink) l)));
				}
			}

		}
		if (net instanceof VirtualNetwork) {
			for (Link<?> l : ((VirtualNetwork) net)
					.getOutEdges((VirtualNode) node)) {
				if (!tempSortNR.containsKey(((VirtualNetwork) net)
						.getDest((VirtualLink) l)))
					tempSortNR.put(((VirtualNetwork) net)
							.getDest((VirtualLink) l), sortedNR
							.get(((VirtualNetwork) net)
									.getDest((VirtualLink) l)));
			}
			for (Link<?> l : ((VirtualNetwork) net)
					.getInEdges((VirtualNode) node)) {
				if (!tempSortNR.containsKey(((VirtualNetwork) net)
						.getSource((VirtualLink) l)))
					tempSortNR.put(((VirtualNetwork) net)
							.getSource((VirtualLink) l), sortedNR
							.get(((VirtualNetwork) net)
									.getSource((VirtualLink) l)));
			}

		}
		for (Iterator<Node<?>> tempNeighbour = MiscelFunctions.sortByValue(
				tempSortNR).keySet().iterator(); tempNeighbour.hasNext();) {
			Node<?> tempChild = tempNeighbour.next();
			children.add(tempChild);
		}

		if (children.isEmpty()) {
			return null;
		}
		return children;

	}
}
