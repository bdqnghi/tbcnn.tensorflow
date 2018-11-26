import java.util.*;

public class towerofhanoi{

	public static void movetopto(tower from,tower to){
		if(from.isEmpty()){
			System.out.println("empty stack");
		}
		to.add(from.pop());

	}

	public static void movefromto(int n,tower from ,tower through ,tower to){
		if(n==0){
			return;
		}else if(n==1){
			movetopto(from,to);
			return;
		}

		movefromto(n-1,from,to,through);
		movetopto(from,to);
		movefromto(n-1,through,from,to);
	}

	public static void main(String args[]){
		int n = 3 ;
		tower[] tt = new tower[3];
		for(int i =0 ; i <3 ;i++){
			tt[i] = new tower(i);
		}

		for(int i =0; i<5;i++){
			tt[0].add(i);
		}
		System.out.println(tt[0]);
		movefromto(5,tt[0],tt[1],tt[2]);
		System.out.println(tt[0]);
		System.out.println(tt[2]);


	}

}

class tower{
	private int index;
	private Stack<Integer> t;

	public tower(int index){
		t = new Stack<Integer>();
		this.index = index;
	}

	public void add(int data){
		if(!isEmpty() && t.peek() < data){
			System.out.println(t.peek());	
		}
		t.push(data);

	}

	public int pop(){
		return t.pop();
	}


	public int index(){
		return index;
	}

	public boolean isEmpty(){
		return t.empty();

	}

	public String toString() {   //要加toString 不然会是乱码
		return t.toString();
	}


}