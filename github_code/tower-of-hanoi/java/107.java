      //                      Towers Of Hanoi using recursion.
import java.util.*;           
class TowerOfHanoi
{
	//function of tower of hanoi
	static void TowerOfHanoi(int n,char Source,char Auxilary,char Target)
	{
		if(n==1)
			System.out.println("Shift "+n+" from "+Source+" to "+Target);
		else
		{
			TowerOfHanoi(n-1,Source,Target,Auxilary);
				System.out.println("Shift "+n+" from "+Source+" to "+Target);
			TowerOfHanoi(n-1,Auxilary,Source,Target);
		}
	}
	public static void main(String args[])
	{	
		Scanner sc=new Scanner(System.in);
		    System.out.print("Enter number of rings : ");
               	   int n =sc.nextInt();	
		            TowerOfHanoi(n,'A','B','C');
	}
}