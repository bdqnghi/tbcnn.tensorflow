package algorithms.search;

import algorithms.mazeGenerators.Maze;
import algorithms.mazeGenerators.Position;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearch extends ASearchingAlgorithm implements ISearchingAlgorithm {

    boolean[][] visited;    // F - not visited, T - visited.
    Queue<Integer> bfsQueue;   //Queue for neighbors.

    /**
     * Constructor
     */
    public BreadthFirstSearch(){
        bfsQueue = new LinkedList<>();
    }

    @Override
    public int getNumberOfNodesEvaluated() {
        return numOfEvaluatedNodes;
    }

    /**
     * Solves the given searchable maze
     * @param searchable - Searchable maze
     * @return - Solution
     */
    @Override
    public Solution solve(ISearchable searchable) {
        SearchableMaze domain = (SearchableMaze) searchable;
        initializeMembers(domain);
        scanSearchableMaze(domain);
        Solution ans = traceSolution(domain.getMaze().getGoalPosition());
        return ans;
    }


    /**
     * This function implements BFS.
     * @param domain - Searchable maze.
     */
    protected void scanSearchableMaze(SearchableMaze domain){
        int currentNode = 0;
        numOfEvaluatedNodes = 1;
        Position currentPosition, mazeStartingPosition = domain.getMaze().getStartPosition();
        MazeState[] possibleStates;
        visited[mazeStartingPosition.getRowIndex()][mazeStartingPosition.getColumnIndex()] = true;
        bfsQueue.add(domain.getCellID(mazeStartingPosition.getRowIndex(), mazeStartingPosition.getColumnIndex()));
        while(!bfsQueue.isEmpty()){     //As long as we have nodes to check.
            currentNode = bfsQueue.remove();
            possibleStates = domain.getAllPossibleStates(new MazeState(fromIntToPosition(currentNode, domain.getWidth())));
            if(possibleStates == null){
                continue;
            }
            for (MazeState aPossibleState: possibleStates) {   //Foreach node from currentNode's neighbors
                currentPosition = aPossibleState.getStatePosition();
                if(!visited[currentPosition.getRowIndex()][currentPosition.getColumnIndex()]){
                    numOfEvaluatedNodes++;
                    visited[currentPosition.getRowIndex()][currentPosition.getColumnIndex()] = true;    //Mark as visited.
                    solutionGrid[currentPosition.getRowIndex()][currentPosition.getColumnIndex()] = fromIntToPosition(currentNode, domain.getWidth());  //Set path (pi)
                    bfsQueue.add(domain.getCellID(currentPosition.getRowIndex(),currentPosition.getColumnIndex()));                                     //To the current node the lead to this node.
                    if(currentPosition.equals(domain.getMaze().getGoalPosition())){  //If we've reached goal position.
                        return; //quit the search.
                    }//if
                }//if
            }//for
        }//while
    }




    /**
     * We want to decrypt the hash code for each node to know its' position: Hash = ((RowIndex * MazeWidth) + ColumnIndex)
     * @param positionHash - Node's hash code
     * @param mazeWidth - The mazes width
     * @return - Position of node.
     */
    private Position fromIntToPosition(int positionHash, int mazeWidth){
        int row = positionHash / mazeWidth;
        int column = positionHash - mazeWidth*row;      //same as %
        return new Position(row, column);
    }

    /**
     * Since our constructor is required to have no arguments here we initialize members that require some args.
     * @param domain - Searchable maze.
     */
    protected void initializeMembers(SearchableMaze domain){
        solutionGrid = new Position[domain.getHeight()][domain.getWidth()];
        visited = new boolean[domain.getHeight()][domain.getWidth()];
        for(int i=0; i < domain.getHeight(); i++){      //Loops to initialize helping matrix.
            for(int j=0; j < domain.getWidth(); j++){
                visited[i][j] = false;
                solutionGrid[i][j] = new Position();
            }
        }
    }

    /**
     * get name of this scan
     * @return - Name of class.
     */
    @Override
    public String getName() {
        return "Breadth First Search.";
    }
}
