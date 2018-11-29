package com.bfs;

import java.util.ArrayList;
import java.util.List;
import java.util.AbstractMap.SimpleEntry;

public class BfsUtil {
	
	private List<List<BfsNode>> bfsMatrix;
	
	/**
	 * Find shortest distance between two nodes in a 2D matrix
	 * @param twoDTextMatrix
	 * @return
	 */
	public void breadthFirstSearch(List<List<String>> twoDTextMatrix, String startNodeValue) {
		buildBfsMatrix(twoDTextMatrix);
		
		SimpleEntry<Integer, Integer> startLocation = locateNode(startNodeValue);
		
		// If start node is found in matrix
		if(startLocation != null) {
			visitNodes(startLocation);
		}
	}
	
	public String getPath(String nodeValue) {
		String path = null;
		
		SimpleEntry<Integer, Integer> node = locateNode(nodeValue);
		
		// If node is found in matrix
		if(node != null) {
			path = this.bfsMatrix.get(node.getKey()).get(node.getValue()).getPath().toString();
		}
		
		return path;
	}
	
	private void buildBfsMatrix(List<List<String>> twoDTextMatrix) {
		this.bfsMatrix = new ArrayList<List<BfsNode>>();
		for(List<String> column : twoDTextMatrix) {
			
			List<BfsNode> bfsColumn = new ArrayList<BfsNode>();
			for(String value : column) {
				BfsNode bfsNode = new BfsNode(value);
				bfsColumn.add(bfsNode);
			}
			
			this.bfsMatrix.add(bfsColumn);
		}
	}
	
	private SimpleEntry<Integer, Integer> locateNode(String value) {
		for(int idxRow = 0; idxRow < this.bfsMatrix.size(); ++idxRow) {
			List<BfsNode> bfsColumn = this.bfsMatrix.get(idxRow);
					
			for(int idxColumn = 0; idxColumn < bfsColumn.size(); ++idxColumn) {
				BfsNode bfsNode = bfsColumn.get(idxColumn);
						
				if(bfsNode.getValue().equalsIgnoreCase(value)) {
					return new SimpleEntry<Integer, Integer>(idxRow, idxColumn);
				}
			}
		}
		
		return null;
	}

	private void visitNodes(SimpleEntry<Integer, Integer> startLocation) {
		this.bfsMatrix.get(startLocation.getKey()).get(startLocation.getValue()).setStartNode(true);
		this.bfsMatrix.get(startLocation.getKey()).get(startLocation.getValue()).addToPath(startLocation);
		this.bfsMatrix.get(startLocation.getKey()).get(startLocation.getValue()).setVisited(true);
		
		List<SimpleEntry<Integer, Integer>> currentNodes = new ArrayList<SimpleEntry<Integer, Integer>>();
		currentNodes.add(startLocation);
		
		List<SimpleEntry<Integer, Integer>> nextNodes = new ArrayList<SimpleEntry<Integer, Integer>>();
		
		do {
			for(SimpleEntry<Integer, Integer> currentNode : currentNodes) {
				List<SimpleEntry<Integer, Integer>> path = this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue()).getPath();
				
				if(currentNode.getKey() < this.bfsMatrix.size() - 1) {
					if(!this.bfsMatrix.get(currentNode.getKey() + 1).get(currentNode.getValue()).isVisited()) {
						
						SimpleEntry<Integer, Integer> node = new SimpleEntry<Integer, Integer>(currentNode.getKey() + 1, currentNode.getValue());
						this.bfsMatrix.get(currentNode.getKey() + 1).get(currentNode.getValue()).setVisited(true);
						this.bfsMatrix.get(currentNode.getKey() + 1).get(currentNode.getValue()).addToPath(path, node);
						
						nextNodes.add(node);
					}
				}
				
				if(currentNode.getValue() < this.bfsMatrix.get(currentNode.getValue()).size() - 1) {
					if(!this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() + 1).isVisited()) {
						
						SimpleEntry<Integer, Integer> node = new SimpleEntry<Integer, Integer>(currentNode.getKey(), currentNode.getValue() + 1);
						this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() + 1).setVisited(true);
						this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() + 1).addToPath(path, node);
						
						nextNodes.add(node);
					}
				}
				
				if(currentNode.getKey() > 0) {
					if(!this.bfsMatrix.get(currentNode.getKey() - 1).get(currentNode.getValue()).isVisited()) {
						
						SimpleEntry<Integer, Integer> node = new SimpleEntry<Integer, Integer>(currentNode.getKey() - 1, currentNode.getValue());
						this.bfsMatrix.get(currentNode.getKey() - 1).get(currentNode.getValue()).setVisited(true);
						this.bfsMatrix.get(currentNode.getKey() - 1).get(currentNode.getValue()).addToPath(path, node);
						
						nextNodes.add(node);
					}
				}
				
				if(currentNode.getValue() > 0) {
					if(!this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() - 1).isVisited()) {
						
						SimpleEntry<Integer, Integer> node = new SimpleEntry<Integer, Integer>(currentNode.getKey(), currentNode.getValue() - 1);
						this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() - 1).setVisited(true);
						this.bfsMatrix.get(currentNode.getKey()).get(currentNode.getValue() - 1).addToPath(path, node);
						
						nextNodes.add(node);
					}
				}
			}
			
			currentNodes.clear();
			currentNodes.addAll(nextNodes);
			nextNodes.clear();
			
		} while(currentNodes.size() > 0);
	}
	
}
