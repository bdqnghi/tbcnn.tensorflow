package com.jerry.aiproject.aialgorithms;

import java.util.ArrayList;

import com.jerry.aiproject.core.TileMap;
import com.jerry.aiproject.gameobjects.GameObject;
import com.jerry.aiproject.utils.Path;

/**
 * This class will implement the Breadth
 * First search algorithm, it uses a queue
 * which is "first in, first out" type of 
 * list. It is similar to A*, but the open 
 * list isn't sorted by a heuristic, and
 * every parent is checked before checking
 * the children nodes. Implementation was
 * broken down in pseudo code by David 
 * Brackeen author of Developing Games in
 * Java and Alexander Useche, owner of
 * http://www.alexanderuseche.com/
 * @author Jerry
 */
public class BreadthFirstSearch {

	private ArrayList<Node> openList = new ArrayList<Node>();
	private ArrayList<Node> closedList = new ArrayList<Node>();
	private Node[][] nodes;
	private TileMap tileMap;
	private int maxDepth;
	//private boolean diagonalMoves = false;
	
	public BreadthFirstSearch(TileMap map, int depth) {
		tileMap = map;
		maxDepth = depth;
		
		//Create nodes for every tile on the map. 
		nodes = new Node[tileMap.getRows()][tileMap.getCols()];
		for(int row = 0; row < tileMap.getRows(); row++)
		{
			for(int col = 0; col < tileMap.getCols(); col++)
			{
				nodes[row][col] = new Node(row, col);
			}
		}
	}
	
	public Path findPath(GameObject objectSearching, GameObject objectToFind) {
		openList.clear();
		closedList.clear();

        //Get the coordinates of each object.
        int startR = tileMap.getRow(objectSearching.getY()),
            startC = tileMap.getCol(objectSearching.getX());
        int goalR = tileMap.getRow(objectToFind.getY()),
            goalC = tileMap.getCol(objectToFind.getX());

		nodes[startR][startC].depth = 0;
		nodes[startR][startC].cost = 0;
		
		//Add the first node to the open list. 
		openList.add(nodes[startR][startC]);
		//The first node doesn't have a parent, so null. 
		nodes[startR][startC].parent = null;
		
		int treeDepth = 0;
		while(treeDepth < maxDepth && !openList.isEmpty())
		{
			Node currentNode = openList.get(0);
			if(currentNode == nodes[goalR][goalC])
				break;

			//First in, first out, Queue style removal in Breadth First Search.
			openList.remove(0);
			closedList.add(currentNode); //The node has been explored, add to the closed list. 
			//Begin searching through the neighbors of the current node.
			for(int dex = 0; dex < 4; dex++)
			{
				/*
				 * Go through each neighbor of the node, add unexplored nodes to the open list. 
				 * Skip the nodes already explored in the closed list. Also make sure that the
				 * node is within the map. 
				 */
				try{
					if(dex == 0 && !closedList.contains(nodes[currentNode.row + 1][currentNode.col]))
					{
						nodes[currentNode.row + 1][currentNode.col].parent = currentNode;
						openList.add(nodes[currentNode.row + 1][currentNode.col]);
						closedList.add(nodes[currentNode.row + 1][currentNode.col]);
					}
					else if(dex == 1 && !closedList.contains(nodes[currentNode.row - 1][currentNode.col]))
					{
						nodes[currentNode.row - 1][currentNode.col].parent = currentNode;
						openList.add(nodes[currentNode.row - 1][currentNode.col]);
						closedList.add(nodes[currentNode.row - 1][currentNode.col]);
					}
					else if(dex == 2 && !closedList.contains(nodes[currentNode.row][currentNode.col + 1]))
					{
						nodes[currentNode.row][currentNode.col + 1].parent = currentNode;
						openList.add(nodes[currentNode.row][currentNode.col + 1]); 
						closedList.add(nodes[currentNode.row][currentNode.col + 1]); 
					}
					else if(dex == 3 && !closedList.contains(nodes[currentNode.row][currentNode.col - 1]))
					{
						nodes[currentNode.row][currentNode.col - 1].parent = currentNode;
						openList.add(nodes[currentNode.row][currentNode.col - 1]);
						closedList.add(nodes[currentNode.row][currentNode.col - 1]);
					}
				}catch(ArrayIndexOutOfBoundsException e){
					continue;
				}
			}
		}
		
		//Create the path. 
		Path path = new Path();
		Node goalNode = nodes[goalR][goalC];
		while(goalNode != nodes[startR][startC])
		{	
			path.newStartStep(goalNode);
			goalNode = goalNode.parent;
		}
		
		path.newStartStep(goalNode);
		path.printPath();
		return path;
	}
}