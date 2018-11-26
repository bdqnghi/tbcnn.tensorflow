package com.algo3.sort;

import java.util.Arrays;
import java.util.Scanner;

/*
 *  http://www.sorting-algorithms.com/shell-sort
 *  Not stable
	O(1) extra space
	O(n3/2) time as shown (see below)
	Adaptive: O(n�lg(n)) time when nearly sorted
	
	http://en.wikipedia.org/wiki/Shellsort
	The method starts by sorting elements far apart from each other and progressively reducing the gap between them. 
	Starting with far apart elements can move some out-of-place elements into position faster than a simple nearest neighbor exchange. 
	Shellsort is a generalization of insertion sort that allows the exchange of items that are far apart. 
	The idea is to arrange the list of elements so that, starting anywhere, considering every hth element gives a sorted list. 
	Such a list is said to be h-sorted.  reducing large amounts of disorder quickly, and leaving less work for smaller h-sort steps to do. 
	
	
	The worse-case time complexity of shell sort depends on the increment sequence. 
	For the increments 1 4 13 40 121..., which is what is used here, the time complexity is O(n3/2). 
	For other increments, time complexity is known to be O(n4/3) and even O(n�lg2(n)). 
	Neither tight upper bounds on time complexity nor the best increment sequence are known.
 *
 * Used in - embedded systems because of tiny and fixed footprint of code
 * Average case performance
 * fast unless array size is huge	
 */
public class ShellSort {

	
	public static boolean  isLess(int a, int b){
		if(a<b) return true;
				else if(a>b) return false;
						else return false; 
	}

	public static void swap(int[] ary, int posa, int posb){
		
		int swap = ary[posa];
		ary[posa] = ary[posb];
		ary[posb] = swap;
		
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {


		System.out.println("Enter ints seperated by space: ");
		Scanner scn = new Scanner(System.in);
		String str = scn.nextLine();
		
		String[] strary = str.split(" ");
		
		int[] intary = new int[strary.length];

		for (int i = 0; i < strary.length; i++) {
			intary[i] = Integer.parseInt(strary[i]);
		}
		//prep of input done..
		
		//shell sort
		int n = intary.length;
		int h = 1;
		System.out.print("h=1;");
		while(h < n){
			h = 3*h + 1;//increment h by 3x+1 factor - suggested by Knuth, 1973
			System.out.print(h+";");
		}
		
		System.out.println("");
		
		while (h>=1){
			System.out.println("h="+h);
			//h-sort array
			for (int i = h; i < n; i++) 
			{
				for (int j = i; j >= h; j -=h) {//this is most imp loop - uses insertion sort but for h factor
					
					if(isLess(intary[j], intary[j-h] ))
					{
						
						swap(intary, j, j-h);
					}//if
					
				}//for j
				
				System.out.println(Arrays.toString(intary));
				
			}//for i
			
			h = h/3;
		}//while
		
		
			
			
			
	}
}



