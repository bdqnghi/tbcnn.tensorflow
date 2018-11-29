/* SortComparison.java

Joseph Austin
February 26th, 2016

This class compares the runtime of insert sort and shell sort
for various values of N and various gap sequences.

Usage: java SortComparison <input_file_name>
Use -v after specifying the input file to print all sorted arrays (not
recommended for large values of N)

*/

import java.io.*;
import java.util.*;
public class SortComparison
{
	//Define methods for generating gaps
	public static final int EVEN = 0;
	public static final int ODD = 1;
	public static final int HIBBARD = 2;
	public static final int CIURA = 3;
	public static final int SHELL_EVEN = 4;
	public static final int SHELL_ODD = 5;
	public static final int TWOPOINTTWO = 6;
	public static void main(String[] args)
	{
		boolean verbose = false; //Verbose mode will print out the sorted arrays.
		Scanner scan = new Scanner(System.in);
		try { 
			scan = new Scanner(new File(args[0])); 
			if(args.length > 1)
			{
				if(args[1].equals("-v")) verbose = true;
			}
		} //Specify an input file in the command line
		catch(Exception e){
			System.out.println("Usage: java SortComparison <input_file_name>");
			System.out.println("-v | verbose mode");
			System.exit(0);
		}
		
		ArrayList<Long> inputArray = new ArrayList<>();
		while(scan.hasNextLong()) //read in everything from the input file
		{
			inputArray.add(scan.nextLong());
		}
		
		if(verbose){
		System.out.println();
		System.out.println("Read in : ");
		printArray(inputArray);
		System.out.println("\n");
		}	
		
		ArrayList<Long> insertSorted = new ArrayList<>(inputArray);
		ArrayList<Long> shellSorted = new ArrayList<>(inputArray);
		
		long start, end; //Time
		int[] gaps; //Gaps generated
		
		//Perform and time insert sort
		start = System.nanoTime();
		//insertSort(insertSorted);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Insert Sorted : ");
		printArray(insertSorted);
		}
		System.out.println("\n");
		System.out.println("Insertion sort of " + insertSorted.size() + " elements took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println();
		
		//Perform and time shell sort using Shell's even gaps
		gaps = determineGaps(shellSorted.size(), SHELL_EVEN);
		
		start = System.nanoTime();
		shellSorted = shellSort(shellSorted, gaps);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Shell Sorted : ");
		printArray(shellSorted);
		System.out.println();
		}
		
		System.out.println();
		System.out.println("Shell sort of " + shellSorted.size() + " elements using Shell's even gaps: ");
		printArray(gaps);
		System.out.println();
		System.out.print("took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println("\n");
		
		//Perform and time shell sort using Shell's odd gaps
		gaps = determineGaps(shellSorted.size(), SHELL_ODD);
		
		start = System.nanoTime();
		shellSorted = shellSort(shellSorted, gaps);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Shell Sorted : ");
		printArray(shellSorted);
		System.out.println();
		}
		
		System.out.println();
		System.out.println("Shell sort of " + shellSorted.size() + " elements using Shell's odd gaps: ");
		printArray(gaps);
		System.out.println();
		System.out.print("took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println("\n");
		
		//Perform and time shell sort using the 2.2 method
		gaps = determineGaps(shellSorted.size(), TWOPOINTTWO);
		
		start = System.nanoTime();
		shellSorted = shellSort(shellSorted, gaps);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Shell Sorted : ");
		printArray(shellSorted);
		System.out.println();
		}
		
		System.out.println();
		System.out.println("Shell sort of " + shellSorted.size() + " elements using the 2.2 method gaps: ");
		printArray(gaps);
		System.out.println();
		System.out.print("took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println("\n");
		
		//Perform and time shell sort using Hibbard's numbered gaps
		gaps = determineGaps(shellSorted.size(), HIBBARD);
		
		start = System.nanoTime();
		shellSorted = shellSort(shellSorted, gaps);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Shell Sorted : ");
		printArray(shellSorted);
		System.out.println();
		}
		
		System.out.println();
		System.out.println("Shell sort of " + shellSorted.size() + " elements using Hibbard's gaps: ");
		printArray(gaps);
		System.out.println();
		System.out.print("took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println("\n");
		
		//Perform and time shell sort using Ciura's gaps
		gaps = determineGaps(shellSorted.size(), CIURA);
		
		start = System.nanoTime();
		shellSorted = shellSort(shellSorted, gaps);
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Shell Sorted : ");
		printArray(shellSorted);
		System.out.println();
		}
		
		System.out.println();
		System.out.println("Shell sort of " + shellSorted.size() + " elements using Ciura's gaps: ");
		printArray(gaps);
		System.out.println();
		System.out.print("took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println("\n");
		
	}
	public static void insertSort(ArrayList<Long> toSort)
	{
		for(int i = 1; i<toSort.size(); i++)//Starting at the second position
		{
			boolean move = false; //should a swap/movement occur?
			int j;
			for(j=i-1; j>=0; j--) //starting one value behind i, compare the value at i to everything before it at j until the value at i is greater than the value at j
			{
				if(toSort.get(i).longValue() > toSort.get(j).longValue()) break;
				else move = true; //if the value at i is less than a value at any j, a move needs to occur
			}
			if (move) 
			{
				toSort.add(j+1, toSort.get(i)); //add the value in at the spot where the loop stopped
				toSort.remove(i+1);//remove the old value, because adding duplicated it
			}
		}
	}
	public static ArrayList<Long> shellSort(ArrayList<Long> toSort, int[] gaps)
	{
		
		ArrayList<Long> gapSorted = new ArrayList<>(toSort); //Two arrays are used to prevent conflicts while sorting
		for(int gap : gaps) //for each gap in the list of gaps
		{
			for(int i = 0; i<gap; i++) //for each starting position
			{
				ArrayList<Long> subArray = new ArrayList<>(); //make a sub-array for this starting position and gap size
				for(int j = 0; i+(j*gap)<toSort.size(); j++) //for each position in the subArray
				{
					subArray.add(toSort.get(i+(j*gap))); //add each corresponding element from the array to be sorted each gap away from the starting position
				}
				insertSort(subArray); //insert sort the sub-array
				for(int j = i, k=0; k < subArray.size(); j+=gap, k++)
				{
					gapSorted.set(j, subArray.get(k)); //place the now sorted elements back into their positions in the array
				}
			}
			toSort = new ArrayList<>(gapSorted); //copy the sorted array over
		}
		return toSort;
	}
	public static int[] determineGaps(int size, final int METHOD)
	{
		int[] gaps = new int[0];
		int numGaps = 0;
		if (METHOD == EVEN)
		{
			//int numGaps = (size+1)/2;
			numGaps = ((size/2)+1)/2;
			gaps = new int[numGaps];
			gaps[numGaps-1] = 1;
			for(int i = numGaps - 2, k = 2; i>=0; i--, k+=2)
			{
				gaps[i] = k;
			}
			//printArray(gaps);
		}
		if (METHOD == ODD)
		{
			//int numGaps = (size-1)/2;
			numGaps = ((size/2)-1)/2;
			gaps = new int[numGaps];
			gaps[numGaps-1] = 1;
			for(int i = numGaps - 2, k = 3; i>=0; i--, k+=2)
			{
				gaps[i] = k;
			}
			//printArray(gaps);
		}
		if (METHOD == HIBBARD)
		{
			numGaps = 1;
			for(numGaps = 1; (Math.pow(2, numGaps) - 1) < size; numGaps++){}
			if((Math.pow(2, numGaps) - 1) >= size/2) numGaps--;
			gaps = new int[numGaps];
			gaps[numGaps-1] = 1;
			for(int i = numGaps - 2, k = 2; i>=0; i--, k++)
			{
				gaps[i] = (int)Math.pow(2, k)-1;
			}
			//printArray(gaps);
		}
		if (METHOD == CIURA)
		{
			int[] ciura = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
			for(int i = 0; i<ciura.length; i++) 
			{
				if (ciura[i] < size/2) numGaps++;
			}
			gaps = new int[numGaps];
			for(int i = numGaps-1; i>=0; i--)
			{
				gaps[i] = ciura[numGaps-i-1];
			}
			//printArray(gaps);
		}
		if (METHOD == SHELL_EVEN)
		{
			int n = size;
			while(n>1)
			{
				n /= 2;
				numGaps++;
			}
			n = size;
			gaps = new int[numGaps];
			for(int i = 0; i<numGaps; i++)
			{
				n /= 2;
				gaps[i] = n;
			}
			//printArray(gaps);
		}
		if (METHOD == SHELL_ODD)
		{
			int n = size;
			while(n>1)
			{
				n /= 2;
				numGaps++;
			}
			n = size;
			gaps = new int[numGaps];
			for(int i = 0; i<numGaps; i++)
			{
				n /= 2;
				if(n%2 == 0) n++;
				gaps[i] = n;
			}
			//printArray(gaps);
		}
		if (METHOD == TWOPOINTTWO)
		{
			double n = (double)size;
			while(n>1)
			{
				n /= 2.2;
				numGaps++;
			}
			n = (double)size;
			gaps = new int[numGaps];
			for(int i = 0; i<numGaps; i++)
			{
				n /= 2.2;
				if(n%2 == 0) n++;
				gaps[i] = (int)n;
			}
			//printArray(gaps);
		}
		return gaps;
	}
	public static void printArray(ArrayList<Long> toPrint)
	{
		System.out.print("[");
		for(int i = 0; i<toPrint.size(); i++)
		{
			System.out.print(toPrint.get(i));
			if(i!=toPrint.size()-1) System.out.print(",");
			if((i>9)&&(i%10 == 0)) System.out.println();
		}
		System.out.print("]");
	}
	public static void printArray(int[] toPrint)
	{
		System.out.print("[");
		for(int i = 0; i<toPrint.length; i++)
		{
			System.out.print(toPrint[i]);
			if(i!=toPrint.length-1) System.out.print(",");
			if((i>9)&&(i%10 == 0)) System.out.println();
		}
		System.out.print("]");
	}
}