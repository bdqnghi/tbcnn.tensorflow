package vasanth;

import java.util.Scanner;

public class TowerOfHanoi {

	public static void main(String[] args) {
		
		Scanner s=new Scanner(System.in);
		
		System.out.print("Enter the number of disks : ");
		int x=s.nextInt();
		
		tower(x,'A','C','B');
		
	}
	
	static void tower(int a,char from,char to,char aux)
	{
		if(a==1)
		{
			System.out.println("Move disk 1 from "+from+" to "+to);
			return;
		}
		tower(a-1,from,aux,to);
		System.out.println("Move disk "+a+" from "+from+" to "+to);
		tower(a-1,aux,to,from);
	}

}
