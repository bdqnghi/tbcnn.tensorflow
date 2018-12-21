package cs111c;

import java.util.*;

public class Sorts {

	   public static void main(String[] args) {
		
		Integer[] test1 = generateRandomArrayWithLength(200);
		Integer[] test2 = generateRandomArrayWithLength(200);
		
		int selection = numberOfComparsionInSelectionSort(test1);
		
		System.out.println("The number of comparison for Selection Sort is :" + selection);
		System.out.println("The number of swap for Selection Sort is :"+numberOfSwapInSelectionSort);
		        for (int i =0;i< test1.length;i++)
		        {
			        System.out.print(test1[i]+"");
		        }
		        System.out.println("");        
		int shell = numberOfComparisonInShellSort(test2);
		System.out.println("The number of comparison for Shell Sort is :" + shell);
		System.out.println("The number of swap for Shell Sort is :"+ numberOfSwapInShellSort);
				for (int j=0;j<test2.length;j++)
				{
					System.out.print(test2[j]+"");
				}
	    
	   }


  
       public static int numberOfComparsionInSelectionSort=0;
	   public static int numberOfComparisonInShellSort=0;
       public static int numberOfSwapInSelectionSort=0;
	   public static int numberOfSwapInShellSort=0;
	   
	   public static <T extends Comparable<? super T>> void selectionSort(T[] a, int n)
	   {

	       for (int index = 0; index < n - 1; index++)
	       {
	          int indexOfNextSmallest = getIndexOfSmallest(a, index, n - 1);
	          swap(a, index, indexOfNextSmallest);
	         
	       } 
	   } 
	   
	   
	   
	   
	   
	   private static <T extends Comparable<? super T>>
	           int getIndexOfSmallest(T[] a, int first, int last)
	   {

	       T min = a[first];
	       int indexOfMin = first;
	       for (int index = first + 1; index <= last; index++)
	       {
	          if (a[index].compareTo(min) < 0)
	          {
	             min = a[index];
	             indexOfMin = index;
	          }
	          numberOfComparsionInSelectionSort++;
	          
	       } 
	      
	       return indexOfMin;
	   } 

	   
	   private static void swap(Object[] a, int i, int j)
	   {
	      Object temp = a[i];
	      a[i] = a[j];
	      a[j] = temp; 
	      numberOfSwapInSelectionSort++;
	   }
	   
	   public static <T extends Comparable<? super T>>
	          int numberOfComparsionInSelectionSort(T[] a)
	   {
		   selectionSort(a, a.length);
		   return numberOfComparsionInSelectionSort;
	   }
	   
	   
	   public static <T extends Comparable<? super T>>
       void betterShellSort(T[] a, int n)
       {
		   betterShellSort(a,0,n-1);
       }
	   
	   public static <T extends Comparable<? super T>>
	       void betterShellSort(T[] a, int first, int last)
	   {		
		
		   int n = last - first + 1; 
		   for (int space = n / 2; space > 0; space = space / 2)		
		   {			
			   if (space % 2 == 0) 
				space++;			
			   for (int begin = first; begin < first + space; begin++)				
				   incrementalInsertionSort(a, begin, last, space);		
		   } 
	   } 
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   private static <T extends Comparable<? super T>>
       void incrementalInsertionSort(T[] a, int first, int last, int space)
	   {  
		   int unsorted, index; 
		   for (unsorted = first + space; unsorted <= last; 
                unsorted = unsorted + space)  
		   {     
			   T nextToInsert = a[unsorted];     
			   index = unsorted - space;     
			   while ((index >= first) && (nextToInsert.compareTo(a[index]) < 0))    
			   {                  
				   a[index + space] = a[index];     
				   index = index - space;  
				   numberOfSwapInShellSort++;
			   } 
			   a[index + space] = nextToInsert; 
			   numberOfComparisonInShellSort++;
		   } 
	   } 
	   
	   public static <T extends Comparable<? super T>>
               int numberOfComparisonInShellSort(T[] a)
       {
		   betterShellSort(a,a.length);
		   return numberOfComparisonInShellSort;		   
       }
	   
	   public static Integer[] generateRandomArrayWithLength(int length)
	   {
		   if(length>100 && length<10000)
		   {		   
			   Random generate = new Random();		   
			   Integer[] a = new Integer[length];
			   for (int i=0;i<length;i++)		   
			   {			   
				   a[i]=generate.nextInt(length);		   
			   }
			   return a;
		   }
		   else
			   throw new IndexOutOfBoundsException();
	   }
	   

}
