package org.totalboumboum.ai.v201011.ais.akbulutkupelioglu.v6.breadthfirstsearch;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

import org.totalboumboum.ai.v201011.adapter.communication.StopRequestException;
import org.totalboumboum.ai.v201011.adapter.data.AiTile;
import org.totalboumboum.ai.v201011.ais.akbulutkupelioglu.v6.AkbulutKupelioglu;
import org.totalboumboum.ai.v201011.ais.akbulutkupelioglu.v6.util.Coordinate;

/**
 * Class used to find out the distances of accessible tiles from a given tile,
 * using breadth-first search. 
 * @author Yasa Akbulut
 * @author Burcu Küpelioğlu
 *
 */
@SuppressWarnings("deprecation")
public class BreadthFirstSearch
{
	/** */
	private AkbulutKupelioglu monIa;
	
	/**
	 * Creates a new BreadthFirstSearch instance.
	 * @param ia the AkbulutKupelioglu using this BreadthFirstDistance
	 * @throws StopRequestException
	 * 		description manquante !
	 */
	public BreadthFirstSearch(AkbulutKupelioglu ia) throws StopRequestException
	{
		ia.checkInterruption();
		monIa = ia;
	}
	
	/**
	 * Performs a breadth-first search starting from a given tile, and returns the distances of each tile.
	 * @param tile The starting tile.
	 * @return A coordinate list containing all the accessible tiles and their respective distances.
	 * @throws StopRequestException
	 * 		description manquante !
	 */
	public ArrayList<Coordinate> search(AiTile tile) throws StopRequestException
	{
		monIa.checkInterruption();
		Queue<BreadthFirstSearchNode> queue = new LinkedList<BreadthFirstSearchNode>();
		ArrayList<BreadthFirstSearchNode> processed = new ArrayList<BreadthFirstSearchNode>();
		ArrayList<Coordinate> result = new ArrayList<Coordinate>(); 
		BreadthFirstSearchNode rootNode = new BreadthFirstSearchNode(tile, null, monIa);
		rootNode.setValue(0);
		queue.add(rootNode);
		while(!queue.isEmpty())
		{
			monIa.checkInterruption();
			BreadthFirstSearchNode currentNode = queue.poll();
			ArrayList<BreadthFirstSearchNode> children = currentNode.getChildren();
			for(BreadthFirstSearchNode childNode : children)
			{
				monIa.checkInterruption();
				childNode.setValue(childNode.getParent().getValue()+1);
				if(!queue.contains(childNode)&&!processed.contains(childNode))
					queue.add(childNode);
			}
			processed.add(currentNode);
			result.add(new Coordinate(currentNode.getCurrentTile(), currentNode.getValue(), monIa));
		}
		return result;
		
	}
	
}
