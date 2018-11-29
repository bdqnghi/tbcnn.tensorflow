import java.util.Scanner;
import java.util.Stack;


public class Towerofhanoi {
	
		public static void main(String[] args) {
	Scanner s=new Scanner(System.in);
	int numofDisks=s.nextInt();
		System.out.println("Tower of Hanoi" );
		toh(numofDisks,'A','B','C');
		}
		public static void toh(int d,char f,char m,char l){
			if(d==1){
				System.out.println("Disk 1 from "+f+" to "+l);
			}
			else{
				toh(d-1, f,l,m);
				System.out.println("Disk "+d+" from "+f+" to "+l);
				toh(d-1,m, f,l);
			}
		}
	}
	
	
		

