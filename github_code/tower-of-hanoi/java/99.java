package practise.com;

import java.util.Stack;
/* Name:Tower of Hanoi
 * Parameters: List of String, Stringbuffer Variable, Left Counter, Right Counter
 * Return :Void
 * Function: Tower of Hanoi
 */

public class TowerOfHanoi {
	private Stack<Integer> disks;
	private int index;
	public TowerOfHanoi(int i){
		disks = new Stack<Integer>();
		index = i;
	}
	public int index(){
		return index;
		
	}
	public void add(int d){
		if( !disks.isEmpty() && disks.peek() <= d ){
			System.out.println("Error placing disks "+ d);
			return;
		}else
			disks.push(d);
	}
	public void moveTopTo( TowerOfHanoi t){
		System.out.println("MoveTopTo  disks "+disks);
		int top = disks.pop();
		System.out.println("MoveTopTo  top  "+top);
		t.add(top);
		System.out.println("Move disk "+top + " from "+index() + " to "+t.index());
	}
	public void print(){
		System.out.println("Contents of Tower " + index());
		for (int i = disks.size() - 1; i >= 0; i--) 
			System.out.println(" " + disks.get(i)); 
		
	}
	public void moveDisks(int n, TowerOfHanoi destination, TowerOfHanoi buffer){
		System.out.println("moveDisks "+n);
		if(n > 0){
			moveDisks(n-1, buffer, destination);
			moveTopTo(destination);
			buffer.moveDisks(n-1, destination, this);
		}
	}
	public static void main(String args[]){
		int n = 3;// Number of Discs
		TowerOfHanoi towers[] = new TowerOfHanoi[n];
		// Initalize 3  pegs
		for(int i=0; i<3; i++)
				towers[i] = new TowerOfHanoi(i);
		// Add Initial disks which is equal to n(input value)
		for(int i= n-1; i>=0; i--)
			towers[0].add(i);
		// Actual Function to move the discs
		towers[0].moveDisks(n, towers[2], towers[1]);
	}

}
