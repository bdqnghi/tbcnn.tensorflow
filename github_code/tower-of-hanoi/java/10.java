

import java.util.Scanner;
import java.util.Stack;
/**
 * @author Dillon Nagele
 */

/**
 * Class representing a tower
 */
class HanoiStack extends Stack<Integer>{
	
	//Tower name
	private char tower;
	
	//Constructor
	public HanoiStack(char tower){
		super();
		this.tower=tower;
	}
	
	//gets tower name
	public char getTower(){
		return tower;
	}
}

/**
 * Class running the tower 
 */
public class TowersOfHanoi {

	
	public static void main(String[] args) {
		//user input
		Scanner input=new Scanner(System.in);
		
		HanoiStack startA = new HanoiStack('A'); // start tower in output
        HanoiStack endC = new HanoiStack('C'); // end tower in output
        HanoiStack tempB = new HanoiStack('B'); // temporary tower in output
        int totalDisks; // number of disks
        
        System.out.println("Enter number of disks for Tower of Hanoi:");
        
        totalDisks=input.nextInt();
        
        //adds disks to start tower based on user input
        for(int i=totalDisks;i>0;i--){
    	    startA.add(i);
        }
        
        //Executes Tower of Hanoi
        solveTowers(totalDisks,startA,endC,tempB);
        input.close();
	}
	
	/**
	 * Method executing Tower of Hanoi
	 * @param n number of towers
	 * @param startA
	 * @param endC
	 * @param tempB
	 */
	 private static void solveTowers(int n, HanoiStack startA, HanoiStack endC,
	            HanoiStack tempB) {
	        if (n > 0) {
	        	//Recursion for next move
	            solveTowers(n - 1, startA, tempB, endC);
	            //Current disk
	            Integer d = (Integer) startA.pop(); 
                // to top of tower C
                endC.push(d); 
                //Prints current move
                System.out.println("Move disk " + d + " from tower "+ startA.getTower() + " to tower " + endC.getTower());
                //Recursion for next move
	            solveTowers(n - 1, tempB, endC, startA);
	        }
	 
	    }
}

