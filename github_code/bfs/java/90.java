import java.util.Comparator;
import java.util.LinkedList;
import java.util.Queue;


public class breadthfirstsearch {
	
	
	private void DFS(int[][] relation,int start)
	{
		start=start-1;
		Queue<Node> queueofNodes= new LinkedList<Node>();
		queueofNodes.add(new Node(start));
		while(queueofNodes!=null)
		{
			queueofNodes.peek().color
			
			
		}
		
		
	}
	
	
	
	
	
	

}


class Node
{
	int  name;
	String color;
	Node prev;
	int level;

	public Node(int name) {
		this.name =name;
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return ""+this.name;
	}
	
}


class comparingNodes implements Comparator<Node>
{

	@Override
	public int compare(Node arg0, Node arg1) {
		// TODO Auto-generated method stub
		return arg0.level-arg1.level;
	}

	
	
	
}
