import java.util.Stack;

public class TowerOfHanoiUsingStack {
	
	private Stack<Integer> s;
	private String name;
	
	// we really need the name 
	// to identify which tower are we at
	TowerOfHanoiUsingStack(String abc) {
		s= new Stack<Integer>();
		name = abc;
	}
	
	// Adding in the stack (or maybe the tower)
	public void push(int value) {
		// push in the stack if either the stack is empty or the value beneath is bigger
		if(s.isEmpty()|| s.peek()>value) {
			s.push(value);
		}
		else {
			System.out.println("The is is some error");
		}
	}
	
	// The original function
	public void recurse(int n, TowerOfHanoiUsingStack destination, TowerOfHanoiUsingStack buffer) {
		if(n<=0)
			return;
		// move n-1 disks to buffer
		recurse(n-1, buffer, destination);
		// move the last disk to destination
		move(destination);
		// move n-1 remaining to destination from buffer
		buffer.recurse(n-1, destination, this);
	}
	

	// pop from current stack and push to the argument tower
	private void move(TowerOfHanoiUsingStack destination) {
		int val = s.pop();
		destination.push(val);
		System.out.println("Moved "+val+ " from "+name+ " to "+destination.name);
		
	}

	public static void main(String[] args) {
		// Ideally I should have made another class for main
		
		TowerOfHanoiUsingStack t1 = new TowerOfHanoiUsingStack("Source");
		TowerOfHanoiUsingStack t2 = new TowerOfHanoiUsingStack("Destination");
		TowerOfHanoiUsingStack t3 = new TowerOfHanoiUsingStack("Buffer");
		
		// push as many disks as you want in 1st tower but in descending order
//		t1.push(5);
//		t1.push(4);
		t1.push(3);
		t1.push(2);
		t1.push(1);
	
		t1.recurse(3, t2, t3);

	}

}
