import java.util.*;
public class Towerofhanoi {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter thr number of discs");
		int n=sc.nextInt();
		TowerOfHanoi(n,'A','C','B');
	}
	public static void TowerOfHanoi(int n, char start, char end, char mid){
	if(n==1)
	{
		System.out.println("Move disk 1 from" + start + "to" + end);	}
	else{
		TowerOfHanoi(n-1,start,mid,end);
		System.out.println("Move disk" + n +"from" + start + "to" + end);
		TowerOfHanoi(n-1,mid,end,start);}
		
	}
}
