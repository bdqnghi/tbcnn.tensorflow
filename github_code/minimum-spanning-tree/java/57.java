/**************************************************************************************
Copyright (C) Gerardo Huck, 2011


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************************/

package cytoscape.plugins.igraph;

import java.awt.event.ActionEvent;
import javax.swing.JOptionPane;
import java.util.*;

import cytoscape.Cytoscape;
import cytoscape.*;
import cytoscape.data.*;
import cytoscape.plugin.CytoscapePlugin;
import cytoscape.util.CytoscapeAction;
import cytoscape.logger.CyLogger;
import giny.model.*;

import giny.view.NodeView;
import cytoscape.view.CyNodeView;
import cytoscape.view.CyNetworkView;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;


public class MinimumSpanningTree extends CytoscapeAction {
    
    Boolean selectedOnly;
    Boolean isWeighted;
    
    public MinimumSpanningTree(IgraphPlugin myPlugin, 
					 String name, 
					 boolean selectedOnly, 
					 boolean isWeighted) {
	super(name);
	this.selectedOnly = new Boolean(selectedOnly);
	this.isWeighted = new Boolean(isWeighted);
	if (isWeighted)
	    setPreferredMenu("Plugins.Igraph.Minimum Spanning Tree (Weighted)");
	else
	    setPreferredMenu("Plugins.Igraph.Minimum Spanning Tree (Unweighted)");

    }
	
    public void actionPerformed(ActionEvent e) {

	CyLogger logger = CyLogger.getLogger(MinimumSpanningTree.class);

	try {
	    CyNetwork network = Cytoscape.getCurrentNetwork();
	    int numNodes;
	    if (selectedOnly)
		numNodes = network.getSelectedNodes().size();
	    else
		numNodes = network.getNodeCount();

	    /*          Check that there are any nodes          */
	    if (numNodes == 0) {
		JOptionPane.showMessageDialog(Cytoscape.getDesktop(), "ERROR: No nodes selected or empty network!");
		return;
	    }

	    /*          Load graph into Igraph library          */
	    HashMap<Integer,Integer> mapping = IgraphAPI.loadGraph(selectedOnly, false);

	    /*          Prepare variables to hold results from native call          */
	    int[] mst = new int[2 * numNodes - 2];	
	    int numEdges;	   

	    /*          Compute MST          */
	    if (isWeighted) {			       		
		String attribute = chooseEdgeAttribute();
		if (attribute == "") {
		    // This means that no suitable attribute was found, so we fall back to the unweighted computation
		    numEdges = IgraphInterface.minimum_spanning_tree_unweighted(mst);
		} else {
		    double[] weights = IgraphAPI.computeWeights(attribute, 
								mapping, 
								selectedOnly);
		
		    numEdges = IgraphInterface.minimum_spanning_tree_weighted(mst, weights);
		}
	    } else { // Unweighted case
		numEdges = IgraphInterface.minimum_spanning_tree_unweighted(mst);
	    }


	    /*          Create new network & networkView          */
	    CyNetworkView oldView = Cytoscape.getCurrentNetworkView();

	    // Prepare nodes
	    int[] nodes = new int[numNodes];	
	    int j = 0;
	    Iterator<Node> nodeIt;
	    if(selectedOnly) {
		nodeIt = network.getSelectedNodes().iterator();
	    } else {
		nodeIt = network.nodesIterator();
	    }
		
	    while(nodeIt.hasNext()){            
		Node node = nodeIt.next();
		nodes[j] = node.getRootGraphIndex();
		j++;
	    }

	    // Prepare edges
	    int[] edges = new int[numEdges];
	    int i = 0;


	    // create node reverse mapping (igraphId -> rootGraphIndex)
	    HashMap<Integer,Integer> reverseMapping = new HashMap<Integer,Integer>(mapping.size());

	    Iterator<Map.Entry<Integer,Integer>> mapIter = mapping.entrySet().iterator();
	    while (mapIter.hasNext()) {
		Map.Entry entry = (Map.Entry) mapIter.next();
		reverseMapping.put((Integer) entry.getValue(), (Integer) entry.getKey());
	    }


	    for (int k = 0; k < 2 * numEdges; k += 2) {

		// get rootGraphId's for both nodes of this edge
		int n1 = reverseMapping.get(mst[k]);
		int n2 = reverseMapping.get(mst[k + 1]);

		// Get edges starting or ending in n1
		int[] adjacentEdgesArray = network.getAdjacentEdgeIndicesArray(n1,
									       true,  // undirected edges
									       true, // incoming edges
									       true); // outgoing edges
		
		for (int l = 0; l < adjacentEdgesArray.length; l++) {
		    Edge edge = network.getEdge(adjacentEdgesArray[l]);
		    int edgeSource = edge.getSource().getRootGraphIndex();
		    int edgeTarget = edge.getTarget().getRootGraphIndex();

		    if (edgeSource == n2 || edgeTarget == n2) {
			// This edge is in the MST!
			edges[i] = edge.getRootGraphIndex();
			i++;
			break;
		    }		    
		}
	    }

	    if (i != numEdges) {
		JOptionPane.showMessageDialog(Cytoscape.getDesktop(), "ERROR! Edges found: " + i + " , should be: " + numEdges);		
		return;
	    }
					
	    String newNetworkName = "Minimum Spanning Tree (" + network.getTitle() + ")";

	    CyNetwork newNetwork = Cytoscape.createNetwork(nodes,
							   edges,
							   newNetworkName,
							   network,
							   true);


	    /*          Set node positions          */
	    CyNetworkView newView = Cytoscape.getCurrentNetworkView();	    

	    Iterator<Node> newNodesIt = newNetwork.nodesIterator();

	    while(newNodesIt.hasNext()){            
		Node node = newNodesIt.next();
		NodeView newNodeView = newView.getNodeView(node);
		NodeView oldNodeView = oldView.getNodeView(node);

		//oldNodeView.;

		// Set X and Y positions
		newNodeView.setXPosition(oldNodeView.getXPosition());
		newNodeView.setYPosition(oldNodeView.getYPosition());

		// Set label position
		newNodeView.setLabelPosition(oldNodeView.getLabelPosition());
	    }

	    // Redraw the whole network
	    newView.updateView();
	    newView.redrawGraph(true, true);	    
	    newView.fitContent();
	    

	} catch (Exception ex) {
	    ex.printStackTrace();
	    String message = "Error:\n" + ex.getMessage(); 
	    JOptionPane.showMessageDialog( Cytoscape.getDesktop(), message);
	}

    }


    protected static String chooseEdgeAttribute() {

	String attribute;

	// Create a list with all Integer or Double edge attributes
	CyAttributes edgeAttributes = Cytoscape.getEdgeAttributes();
	String[] attrArr = edgeAttributes.getAttributeNames();
	Vector attrVector = new Vector();
	
	for (int i = 0; i < attrArr.length; i++) {
	    byte type = edgeAttributes.getType(attrArr[i]);
	    if (type == CyAttributes.TYPE_INTEGER || type == CyAttributes.TYPE_FLOATING)
		attrVector.add(attrArr[i]);
	}
 
	if (attrVector.size() == 0) {
	    JOptionPane.showMessageDialog(Cytoscape.getDesktop(), "No suitable (numeric) edge attribute found.\nWill perform unweighted Minimum Spanning Tree computation instead.");
	    attribute = "";
	} else {
	    Object[] possibleValues = attrVector.toArray();
	    attribute = (String) JOptionPane.showInputDialog(Cytoscape.getDesktop(),
							     "Choose which edge attribute will be used as weight", 
							     "Minimum Spanning Tree (Weighted)",
							     JOptionPane.INFORMATION_MESSAGE, null,
							     possibleValues, possibleValues[0]);	    
	}
	
	// JOptionPane.showMessageDialog(Cytoscape.getDesktop(), "Edge attributes:\n" +  attribute);

	return attribute;
    }

}