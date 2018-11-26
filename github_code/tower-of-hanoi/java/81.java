
public class TowerOfHanoi {
	private static int countMoves = 0;
	public static void main(String[] args){
		Stack stack = new Stack();
		stack.push(6);
		stack.push(5);
		stack.push(4);
		stack.push(3);
		stack.push(2);
		stack.push(1);
		
		Stack target = new Stack();
		Stack extra = new Stack();
		
		moveTowerHelper(stack, target, extra);
		
	}
	
	public static void moveTower(Stack origin, Stack target, Stack extra, int height){ // start with count = height of tower
				
		if (height == 1){
			moveDisk(origin, target);
			countMoves++;
			System.out.println(printStacks(origin, target, extra)+"\n");
			return;
		}
		moveTower(origin, extra, target, height-1);
		moveDisk(origin, target);
		countMoves++;
		System.out.println(printStacks(origin, target, extra)+"\n");
		moveTower(extra,target, origin,height-1);		
		
	}
	
	private static boolean moveDisk(Stack origin, Stack target){
		if (target.peek() == null || target.peek().diskNum > origin.peek().diskNum){
			target.push(origin.pop().diskNum);
			return true;
		}
		System.out.println("Error moving disk");
		return false;
	}
	
	public static void moveTowerHelper(Stack origin, Stack target, Stack extra){
		countMoves = 0;
		moveTower(origin, target, extra, origin.height());
		System.out.println("Number of Moves:"+countMoves);
	}
	
	public static String printStacks(Stack origin, Stack target, Stack extra){
		return "origin:\t"+origin+"\ntarget:\t"+target+"\nextra:\t"+extra;
	}

}
