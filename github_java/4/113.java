package SortingProgrammms;

public class insertionsort {
	
	public class MyInsertionSort {
		 
	    public  void main(String[] args) {
	         
	        int[] input = { 4, 2, 9, 6, 23, 12, 34, 0, 1 };
	        insertionSort(input);
	    }
	     
	    private  void printNumbers(int[] input) {
	         
	        for (int i = 0; i < input.length; i++) {
	            System.out.print(input[i] + ", ");
	        }
	        System.out.println("\n");
	    }
	 
	    public  void insertionSort(int array[]) {
	        int n = array.length;
	        for (int j = 1; j < n; j++) {
	            int key = array[j];
	            int i = j-1;
	            while ( (i > -1) && ( array [i] > key ) ) {
	                array [i+1] = array [i];
	                i--;
	            }
	            array[i+1] = key;
	            printNumbers(array);
	        }
	    }
	

	}}
