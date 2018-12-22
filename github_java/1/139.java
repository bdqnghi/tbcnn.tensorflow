package mk1;
/*
 * Darren Kong 
 * AP-Java 
 * Mr.Levin
 */
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
/*
 * Breadth First Search in Java
 */
public class BreadthFirstSearch extends AbstractSearch{
	
	/*
	 * Constructor
	 */
	public BreadthFirstSearch(Node start, Node goal){
		super(start, goal);
	}
	
	public boolean search(){
		System.out.println("BreadthFirst Search:");
		if (this.startNode.equals(this.goalNode))
		{
			System.out.println("Goal Node Found!");
			System.out.println(startNode);
		}
		
		Queue <Node> queue = new LinkedList<>();
		ArrayList<Node> explored = new ArrayList<>();
		queue.add(this.startNode);
        explored.add(startNode);
        
        while(!queue.isEmpty())
        {
        	Node current = queue.remove();
        	if(current.equals(this.goalNode))
        	{
        		explored.add(current);
        		System.out.println(explored);
				System.out.println("Goal Node Found!");
                return true;
        	}
        	else
        	{
        		for (Node x : current.getChildren()){
        			if (!explored.contains(x) && !queue.contains(x)){
        				queue.add(x);
        			}
        		}
        	}
        	explored.add(current);
        }
		System.out.println("No Path Found!");
        return false;
	}
}
