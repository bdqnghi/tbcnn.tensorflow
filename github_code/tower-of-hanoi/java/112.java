package stacks_queues;

public class TowerOfHanoi {
	Stack disks = new Stack();
	public void add(int i) throws Exception{
		if(disks.isEmpty()){
			disks.push(i);
			return;
		}
		if(disks.peek() <= i){
			throw new Exception("Larger disk cannot be added!");
		}
		disks.push(i);
	}
	
	public static void moveTop(TowerOfHanoi i, TowerOfHanoi j) throws Exception{
		if(i.disks.isEmpty()) throw new Exception("Source is empty!");
		j.add(i.disks.pop());
	}
	
	public static void moveAllDisks(int n, TowerOfHanoi source, TowerOfHanoi destination, TowerOfHanoi buffer) throws Exception{
		if(n <= 0) return;
		moveAllDisks(n-1, source, buffer, destination);
		moveTop(source, destination);
		moveAllDisks(n-1, buffer, destination, source);		
	}
	
	public static void main(String args[]) throws Exception{
		TowerOfHanoi source = new TowerOfHanoi();
		TowerOfHanoi destination = new TowerOfHanoi();
		TowerOfHanoi buffer = new TowerOfHanoi();
		
		for(int i=10; i>0; i--){
			source.add(i);
			System.out.print(i+" | ");
		}
		
		moveAllDisks(10, source, destination, buffer);
		System.out.println();
		for(int i=10; i>0; i--){
			System.out.print(destination.disks.pop()+" | ");
		}
	}
}
