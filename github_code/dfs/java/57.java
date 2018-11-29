/**
 * The DFS class extends CommonSearcher<T> class ass Class that get Searchable object and return a solution
 * itarative algorithem
 */
package algorithms.search;
import java.util.ArrayList;
import java.util.*;

/**
 * Created by orrko_000 on 29/08/2016.
 */

public class DFS<T> extends CommonSearcher<T> {

    private Random rand = new Random(); // create random number
    private List<State<T>> statesList = new ArrayList<State<T>>(); // list of solution stateT
    private List<State<T>> statesMade = new ArrayList<State<T>>(); // list of made states

    /**
     * @return Solution object after do back trace from one coor' to a other coor' object
     */
    @Override
    public Solution<T> search(Searchable s) { // method to find solution for a search-able type using depth first search
        State<T> startState = s.getStartState();
        statesList.add(startState); // add the start state to the list
        statesMade.add(startState);
        DFS(startState, s);   // recursively using depth first search
        Solution<T> sol = new Solution<T>();
        sol.setStates(statesList);   // set the solution
        return sol;
    }

    /**
     * The recurscive algo'
     */
    private void DFS(State<T> currState, Searchable s) {
        while (!statesList.isEmpty()) {

            evaluatedNodes++; // add a node when going to a new state
            List<State<T>> moves = s.getAllPossibleStates(currState); // get the possible moves
            moves.remove(currState.getCameFrom()); // removes the states we have already been at
            moves.removeAll(statesMade);

            if (moves.size() > 0) { // if we got a direction to go to
                int randomNum = rand.nextInt(moves.size()); // random direction
                State<T> nextState = moves.get(randomNum); // the next state
                nextState.setCameFrom(currState); // set who it came from
                statesList.add(nextState); // add it to the list
                statesMade.add(nextState);
                if (nextState.equals(s.getGoalState()))
                    return;

                else
                    currState = nextState;
            } else { //if it is a dead end
                statesList.remove(currState);
                if (statesList.size() > 0)
                    currState = statesList.get(statesList.size() - 1);
            }
        }
    }



}
