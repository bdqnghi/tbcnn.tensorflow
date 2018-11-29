import java.util.ArrayList;

/**
 * This program is to simulate the puzzle the Tower of Hanoi
 * @author cccc1
 * @author derickboss1
 */
public class TowerOfHanoi {
    
    /**
     * Initialize class fields.
     */
    private ArrayList<Integer> start, startClone, mid, end;
    private ArrayList<ArrayList<Integer>> allLists = new ArrayList<ArrayList<Integer>>();
    private static int steps;
    private static int numberOfDisks;
    private static final int NUMBER_OF_STACKS = 3;


    /**
     * Fill in the starting ArrayList with values
     * busts if n less than or equals 0
     * @param n number of discs
     */
    public TowerOfHanoi(int n){
        start = new ArrayList<Integer>();
        startClone = new ArrayList<Integer>();
        mid = new ArrayList<Integer>();
        end = new ArrayList<Integer>();
            
        if(n > 0){           
            numberOfDisks = n;                  
            steps = 0;

            for(int i = n; i > 0; i--){
                start.add(i);
                startClone.add(i);
            }

        }
        else{
            
        }    
        
        allLists.add(start);
        allLists.add(mid);
        allLists.add(end);
    }

    /**
     * Returns the starting ArrayList
     * @return start
     */
    private ArrayList<Integer> getStart(){

        return start;
    }

    /**
     * Returns the target ArrayList
     * @return end
     */
    private ArrayList<Integer> getEnd(){

        return end;
    }   
    
    /**
     * Returns the target ArrayList
     * @return mid
     */
    private ArrayList<Integer> getMid(){
        return mid;
    }
    
    /**
     * gets the number of disks
     * @return the number of disks
     */
    public int getNumberOfDisks(){
        return numberOfDisks;
    }
    
    /**
     * gets the number of steps
     * @return the number of steps
     */
    public int getSteps(){
        return steps;
    }
    
    /**
     * gets the entire game
     * @return allLists
     */
    public ArrayList<ArrayList<Integer>> getAllLists(){
        return allLists;
    }
    
    
    /**
     * Move the top element to the designated list and removes the moved value
     * @param from target ArrayList
     * @param to designated ArrayList
     */
    public void moveTo(ArrayList<Integer> from, ArrayList<Integer> to){
        
        if(from.size() > 0){
            ArrayList <Integer> cloneTo = new ArrayList<Integer>(to);
            cloneTo.add(from.get(from.size()-1));
            
            if(validPosition(cloneTo)){
                to.add(from.get(from.size()-1));
                from.remove(from.size()-1);
                steps++;
            }
            else{
                System.out.println("Unable to perform operation!");
            }
        }
        else{
            System.out.println("Invalid selection!");
        }
    }
    
    
    /**
     * to be used to check if an operation is permissible (bigger cannot be on top of smaller)
     * This is only as a helper to the moveTo() method
     * @param arr1 array from which we plan to move the top disk
     * @param arr2 array to which we move the top disk
     * @return the validity of the position (true/false)
     */
    private static boolean validPosition(ArrayList<Integer> arr){
        for(int i = 0; i < arr.size() - 1; i++){
            if (arr.get(i) < arr.get(i+1)){
                return false;
            }
        }
        return true;
    }


    /**
     * Solves the puzzle recursively
     * @param from starting ArrayList
     * @param to target ArrayList
     * @param n number of elements
     */
    public void solve(ArrayList<Integer> from, ArrayList<Integer> to, int n){

        if(n == 2){
            moveTo(from, getNot(from, to));
            print();
            moveTo(from, to);
            print();
            moveTo(getNot(from, to), to);
            print();
        }
        else{
            solve(from, getNot(from, to), n-1);
            moveTo(from, to);
            print();
            solve(getNot(from, to), to, n-1);
        }

    }


    /**
     * overloads the solve method.  No parameters and solve the whole thing
     */
    public void solve(){
        solve(start,end,numberOfDisks);
    }

    
    /**
     * Returns the ArrayList that is not specified in the parameter
     * @param list1 the start list that is not specified
     * @param list2 the mid list that is not specified
     * @return the list that is neither list1 nor list2
     */
    public ArrayList<Integer> getNot(ArrayList<Integer> list1, ArrayList<Integer> list2){

        for(int i = 0 ; i < NUMBER_OF_STACKS; i++)
            if(allLists.get(i) != list1 && allLists.get(i) != list2)
                return allLists.get(i);
        return null;
    }

    /**
     * To print out the current state of the puzzle.
     */
    public void print(){

        System.out.println("Steps :" + steps);
        System.out.println("start :" + start);
        System.out.println("Mid   :" + mid);
        System.out.println("End   :" + end);
        System.out.println("Solved:" + this.isSolved() + "\n");

    }
    
    
    /**
     * prints the formatted puzzle
     */
    public void printPuzzle(){
        System.out.println("Stick 1: " + start);
        System.out.println("Stick 2: " + mid);
        System.out.println("Stick 3: " + end + "\n");
    }


    /**
     * Checks if the puzzle is in the solved state (end peg is in the right order)
     * @return true if the puzzle is solved.  False otherwise
     */
    public boolean isSolved(){
        if(startClone.size() != end.size()){
            return false;
        }
        else{
            for(int i = 0; i < end.size(); i++)
            {
                if(startClone.get(i) != end.get(i))
                {
                    return false;
                }
            }
            return true;
        }
    }


    /**
     * checks if the puzzle is in a valid position (no higher disk on top of lower one)
     * @return true if position is valid.  False otherwise
     */
    public boolean validPosition(){
        for(int i = 0; i < start.size() - 1; i++){
            if (start.get(i) < start.get(i+1)){
                return false;
            }
        }
        for(int i = 0; i < mid.size() - 1; i++){
            if(mid.get(i) < mid.get(i+1)){
                return false;
            }
        }
        for(int i = 0; i < end.size() - 1; i++){
            if(end.get(i) < end.get(i+1)){
                return false;
            }
        }
        return true;
    }
    
}
