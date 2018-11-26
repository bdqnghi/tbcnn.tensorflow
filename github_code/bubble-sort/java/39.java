package com.compit.programming.basics.sort;

import java.util.Random;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.BufferedWriter;
import java.io.FileWriter;

/**
 * @author: chaudharimehul
 * @date:	Jun 1, 2017
 * 
 * Bubble Sort
 * 
 * Time taken to sort 1000000 random numbers 2511233 milliseconds = 41.85388333 minutes
 * Sorted txt file size on MAC - 8.5M
 */
public class Bubble {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//int[] arrayToBeSorted = {20, 29, 2, 3, 6, 1, 9, 2, 90, 35, 100, 55, 200, 75, 25, 32};
		//FileWriter 
		int[] arrayToBeSorted = new int[1000000];
		
		Random rand = new Random();
		
		String fileName = "bubbleSortedValues" + new SimpleDateFormat("yyyy-MM-dd").format(new Date()) +".txt";
		BufferedWriter bfw = null;
		FileWriter fwr = null;
				
		
		System.out.println("Random Number generation started:");
		for(int i = 0 ; i < arrayToBeSorted.length ; i ++){
			arrayToBeSorted[i] = rand.nextInt(1000000);
		}
		System.out.println("Random number generation complete:");
		
		int swap;
		boolean bSortingTakenPlace;
		long startTime = System.currentTimeMillis();

		for(int i = 0; i < arrayToBeSorted.length ; i++ ){
			
			bSortingTakenPlace = false;
			
			for(int j = 0 ; j < arrayToBeSorted.length-1 ; j++){
				if( arrayToBeSorted[j] > arrayToBeSorted[j+1]){
					swap	=	arrayToBeSorted[j+1];
					arrayToBeSorted[j+1] = arrayToBeSorted[j];
					arrayToBeSorted[j] = swap;
					bSortingTakenPlace = true; 
				}
			}
			
			if(!bSortingTakenPlace){
				System.out.println("Iteration taken for sorting: " + i);
				break;
			}
		}
		System.out.println("Time Taken to bubble sort array:" + (System.currentTimeMillis() - startTime) );
		try{
			fwr = new FileWriter(fileName);
			bfw = new BufferedWriter(fwr);
			for(int  i = 0 ; i < arrayToBeSorted.length ; i++){
				bfw.write("[" + arrayToBeSorted[i] + "],");
			}
			bfw.write("\n");
			bfw.close();
			fwr.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

}
