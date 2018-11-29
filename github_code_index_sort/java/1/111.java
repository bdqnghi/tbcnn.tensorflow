package com.interview.prep.sorting;

public class Insertionsort {
	
	/**
	 * PSEUDO CODE :
	 * Start from index No :1 
	 *if (index1 < index 0){swap the indexes;
	 *increment the index by 1
	 *}
	 *
	 *now see: index 2 
	 *if(index2 < index 1)
	 * swap
	 * 
	 * This way we sort the index each time and at a given time , till a given index the lists we have is sorted
	 * @param args
	 */
	static int [] array;
	void insertionsort(){
		
		int arrayLength = array.length;
		for(int i =0; i<arrayLength-1;i++){
			
			for(int j =1; j<arrayLength-1 ;j++ ){
				if(array [j-1] < array[j] ){
					swapElements(j, j-1);
					
				}
			}
		}
		
	}
	
	void swapElements(int currentIndex, int indexToswap){
		
		int temp;
		temp = array[currentIndex];
		array[currentIndex] = array[indexToswap];
		array[indexToswap] = temp;
	}
	
	public static void main(String args[]){
		
		Insertionsort sort = new Insertionsort();
		array = new int [11];
		array[0] = 7;
		array[1] = 1;
		array[2] = 2;
		array[3] = 5;
		array[4] = 8;
		array[5] = 15;
		array[6] = 100;
		array[7] = 45;
		array[8] = 32;
		array[9] = 4;
		array[10] = 0;
		sort.insertionsort();
	}

}
