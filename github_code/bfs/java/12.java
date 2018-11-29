package Algorithems;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

import algorithem.search.Action;
import algorithem.search.CommonSearcher;
import algorithem.search.Searchable;
import algorithem.search.Solution;
import algorithem.search.State;

// TODO: Auto-generated Javadoc
/**
 * The Class BreadthFirstSearch.
 */
public class BreadthFirstSearch extends CommonSearcher implements Serializable{

/** The Num of Nodes that have developed.. */
private int NumOfEvol=0;
private Solution sol;
	
/** Breadth-first search 
 * Solution to by specific algorithm - Breadth-first search 
 */
	@Override
	public Solution search(Searchable s) {
		openList.add(s.getStartState());
		
		while (!openList.isEmpty()) {
			NumOfEvol=getNumOfEvol()+1;
			State state = openList.poll();
			closedList.add(state);
			
			if (state.equals(s.getGoalState())) 
			{
	
				return backtrace(state);
			}
			HashMap<Action, State> actions = s.getAllPossibleStates(state);
			for (Entry<Action, State> entry: actions.entrySet()) {
				Action action = entry.getKey();
				State successor = entry.getValue();
				
				if (!openList.contains(successor) && !closedList.contains(successor)) {
					successor.setCamFrom(state);
					openList.add(successor);
				}
				else if (state.getCost() + action.getCost() < successor.getCost()) {
					
					successor.setCamFrom(state);
					
					// update priority in queue by removing and adding the state
					openList.remove(successor);
					openList.add(successor);					
				}
			}
		}
		return null; // won't reach this line never
	}
	 
 	/**
 	 * Backtrace.
 	 * this method give the user how the algorithm get to the solution
 	 * @param state the State
 	 * @return the solution
 	 */
 	private Solution backtrace(State state) {
		State s = state;
		ArrayList<State> states = new ArrayList<State>();
		while (s != null) {
			states.add(0, s);	
			s=s.getCamFrom();
			
		}
		
		Solution solution = new Solution();
		solution.setStates(states);
		this.sol=solution;
		return solution;
	}
	
	/**
	 * Gets the num of Nodes that have developed..
	 *
	 * @return the num of Nodes that have developed.
	 */
	public int getNumOfEvol() {
		return NumOfEvol;
	}
	
	/**
	 * Sets the num of Nodes that have developed..
	 *
	 * @param sol the new num of Nodes that have developed.
	 */
	public void setNumOfEvol(int sol) {
		this.NumOfEvol = sol;
	}

	public Solution getSol()
	{
		return this.sol;
	}

}


