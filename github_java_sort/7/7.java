

import java.io.*;
import java.util.*;
public class SortComparison
{
	
	public static final int EVEN = 0;
	public static final int ODD = 1;
	public static final int HIBBARD = 2;
	public static final int CIURA = 3;
	public static final int SHELL_EVEN = 4;
	public static final int SHELL_ODD = 5;
	public static final int TWOPOINTTWO = 6;
	public static void main(String[] args)
	{
		boolean verbose = false; 
		Scanner scan = new Scanner(System.in);
		try { 
			scan = new Scanner(new File(args[0])); 
			if(args.length > 1)
			{
				if(args[1].equals("-v")) verbose = true;
			}
		} 
		catch(Exception e){
			System.out.println("Usage: java SortComparison <input_file_name>");
			System.out.println("-v | verbose mode");
			System.exit(0);
		}
		
		ArrayList<Long> inputArray = new ArrayList<>();
		while(scan.hasNextLong()) 
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
		
		long start, end; 
		int[] gaps; 
		
		
		start = System.nanoTime();
		
		end = System.nanoTime();
		
		if(verbose){
		System.out.println("Insert Sorted : ");
		printArray(insertSorted);
		}
		System.out.println("\n");
		System.out.println("Insertion sort of " + insertSorted.size() + " elements took " + ((double)(end-start))/1000000000 + " seconds.");
		System.out.println();
		
		
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
		for(int i = 1; i<toSort.size(); i++)
		{
			boolean move = false; 
			int j;
			for(j=i-1; j>=0; j--) 
			{
				if(toSort.get(i).longValue() > toSort.get(j).longValue()) break;
				else move = true; 
			}
			if (move) 
			{
				toSort.add(j+1, toSort.get(i)); 
				toSort.remove(i+1);
			}
		}
	}
	public static ArrayList<Long> shellSort(ArrayList<Long> toSort, int[] gaps)
	{
		
		ArrayList<Long> gapSorted = new ArrayList<>(toSort); 
		for(int gap : gaps) 
		{
			for(int i = 0; i<gap; i++) 
			{
				ArrayList<Long> subArray = new ArrayList<>(); 
				for(int j = 0; i+(j*gap)<toSort.size(); j++) 
				{
					subArray.add(toSort.get(i+(j*gap))); 
				}
				insertSort(subArray); 
				for(int j = i, k=0; k < subArray.size(); j+=gap, k++)
				{
					gapSorted.set(j, subArray.get(k)); 
				}
			}
			toSort = new ArrayList<>(gapSorted); 
		}
		return toSort;
	}
	public static int[] determineGaps(int size, final int METHOD)
	{
		int[] gaps = new int[0];
		int numGaps = 0;
		if (METHOD == EVEN)
		{
			
			numGaps = ((size/2)+1)/2;
			gaps = new int[numGaps];
			gaps[numGaps-1] = 1;
			for(int i = numGaps - 2, k = 2; i>=0; i--, k+=2)
			{
				gaps[i] = k;
			}
			
		}
		if (METHOD == ODD)
		{
			
			numGaps = ((size/2)-1)/2;
			gaps = new int[numGaps];
			gaps[numGaps-1] = 1;
			for(int i = numGaps - 2, k = 3; i>=0; i--, k+=2)
			{
				gaps[i] = k;
			}
			
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