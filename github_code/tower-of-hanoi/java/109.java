import java.util.Scanner;

public class TowerOfHanoi {

	/**
	 * @param args
	 */
	static int count = 0;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Stack[] Stacks = new Stack[3];
		for(int i = 0; i < Stacks.length; i++){
			Stacks[i] = new Stack();
		}
		
		System.out.println("Input number of disk (under 100) :");
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		
		for(int i = 0; i < n; i++){
			Stacks[0].push_back(i + 1);
		}
		
		TowerOfHanoi(n, Stacks[0], Stacks[1], Stacks[2]);

		int x = 0;
		for(Stack s : Stacks){
			x++;
			System.out.print(s.getClass().getName() + x +  " : ");
			s.toString();
		}
		
		System.out.println("\nNumber of movement : " + count);
		
		sc.close();
	}

	public static void TowerOfHanoi(int n, Stack From, Stack Tmp, Stack To){
		
		if( n == 1){
			To.push_back(From.pop());
		}
		else{
			TowerOfHanoi(n-1, From, To, Tmp);
			To.push_back(From.pop());
			TowerOfHanoi(n-1, Tmp, From, To);
		}
		count++;
	}
}
