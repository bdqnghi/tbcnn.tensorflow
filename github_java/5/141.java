import java.util.ArrayList;
import java.util.Collections;
import java.util.Stack;


public class DFS {
	Stack<Node> s = new Stack<Node>();
	Node root = new Node();
	//Node child=new Node();
	public void depthfirst(String source, String destination, int[][] graphmatrix,ArrayList<String> nodelist ,int start_time)
	{
		//Initialization of Root Node
				root.state=source;
				root.cost=start_time;
				root.depth=0;
				root.parent=null;
				int flag=0;
		//Pushing the Root to the Stack
		s.push(root);
		root.setVisited(true);
//		ArrayList<String> explored = new ArrayList<String>();
//		explored.add(root.state);
		
		//setting all the nodes to visited=false and root to true
		boolean[] visit = new boolean[nodelist.size()];
		//visit[nodelist.indexOf(root.state)] =true;
		
		while(!s.isEmpty() && flag==0)
		{
			Node n=(Node)s.pop();
			if(n.getState()!=null)
			{
				if(destination.contains(n.getState()))
				{
					System.out.println(n.getState()+" "+n.getCost()%24);
					flag=1;
					break;
				}
				
			}

			else{
				continue;
			}
			visit[nodelist.indexOf(n.state)] = true;
			// getting the parentindex and defining a new array for adding the children of parents
			int parentindex = nodelist.indexOf(n.getState().trim());
			ArrayList<String> found = new ArrayList<String>();
			
			
			for (int g=0;g<nodelist.size();g++)
				{
				
				
					if(graphmatrix[parentindex][g]!=0 && visit[g]==false)
					{
						
						String children = nodelist.get(g);
						found.add(children);
						
					}
				}
					Collections.sort(found);
					//System.out.println(found);
					
					//Adding the elements to the stack in reverse order
					for(int qf=found.size()-1;qf>=0;qf--)
					{
						Node child=new Node();
						
						child.setState(found.get(qf));
						child.setParent(n);
						child.setDepth((n.depth)+1);
						child.setCost(n.getCost()+1);
						//System.out.println(child.getState());
						//visit[nodelist.indexOf(child.state)]=true;
						//explored.add(children);
						//child.setVisited(true);
						s.push(child);
						
						
						
					}
						
					
				}

		}
		
	
		
	}
		
