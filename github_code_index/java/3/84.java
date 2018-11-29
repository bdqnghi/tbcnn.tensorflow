/**
 * 
 * @author Shivam
 * @date 19-09-2017
 * @description Class Tower of hanoi deals with a problem 'TOWER OF HANOI',
 * in this problem we have given the number of disks(number of pole is constant).
 * Initially, all the disks are placed in first pole (source pole), all these disks has to be move
 * in destination poll via auxillary pole.There are following rules :-
 * 1.Only one disk should be moved at a time.
 * 2.Disks in destination pole should be in same order as that of Source Pole.
 */
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

//class to solve Tower of hanoi problrm
public class TowerOfHanoi {
	static ArrayList<String> list = new ArrayList<String>();
	static String str="";
	public static ArrayList<String> towerOfHanoi(String source, String destination, String temp, int numOfDisk) {
		if(numOfDisk == 1) {
			str= "Move disk "+numOfDisk +" from " +source+" to "+destination;
			list.add(str);	//addition of string in List<String>			
		}else {
			towerOfHanoi( source, temp, destination, numOfDisk-1 );
			str= "Move disk "+numOfDisk +" from " +source+" to "+destination;
			list.add(str);	//addition of string in List<String>	
			towerOfHanoi( temp, destination, source, numOfDisk-1 );
		}
		return list;
	}
	
	public static void main(String args[]) {
		System.out.println("Enter a number");
		Scanner sc = new Scanner(System.in);	//to take number of disks
		int numberOfDisk = sc.nextInt();
		sc.close();
		ArrayList<String> al=towerOfHanoi("A", "B", "C", numberOfDisk);	//method called to solve the problem
		Iterator<String> itr=al.iterator();  //Iterator to iterate in List
		while(itr.hasNext()){  
		   System.out.println(itr.next()); 
	    }  
	}
}
