import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import java.util.Scanner;
import java.util.Set;


//this is the implementation of Depth first search algorithm//
public class Depthfirstsearch {

	
	public State execDFS(State initialState)
	{		//Checks for initial state being the goal state or not, 
			//if yes then it will return the initial state and print solution//
			if (initialState.isGoal()) {
				return initialState;
			}
			//Use of stack for the depth first search// 
			Stack<State> searchlist = new Stack<State>();
			Set<State> visited = new HashSet<State>();
			
			//adding the initial state to the stack//
			searchlist.add(initialState);
			while (true) 
			{
				if (searchlist.isEmpty()) 
				{
					return null;	// failure
				}
				State state = searchlist.pop();
				visited.add(state);
				
				//new sucessor state is generated//
				List<State> successors = state.generateSuccessors();
				for (State child : successors) 
				{
					if (!visited.contains(child) || !searchlist.contains(child)) 
					{
						if (child.isGoal()) 
						{
							return child;
						}
						//adding new child state to the searchlist stack//
						searchlist.add(child);
					}
				}
			}
		}
	}
