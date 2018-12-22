/*
	Program : Implementation of Insertion Sort Algorithm in Java
	Author : Sarthak Yadav
	
	Principles: 
		- Insertion Sort is a sorting algorithm with a average case complexity of O(n^2)
		- For more details about Insertion Sort visit
				 https://www.topcoder.com/community/data-science/data-science-tutorials/sorting/
				 https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort
		
	Instructions:
		- just compile from command line
*/

import java.util.Scanner;

public class InsertionSortDemo {

	public static void insertion_sort(int[] arr)
	{
		for(int j=1;j<=arr.length-1;j++)						//iterates from the 2nd element of the array (index no: 1)
		{
			int key=arr[j];										//sets key as the value on the current index
			int i=j-1;	
			while(i>=0 && arr[i]>key)							//keeps check if i is non negative and the other test condition
			{
				arr[i+1]=arr[i];
				i-=1;
			}
			arr[i+1]=key;
		}
	}
	
	public static void main(String[] args) 
	{
		// Implementation of Insertion Sort
		
		
		Scanner scanner=new Scanner(System.in);												//to get input from Console
		System.out.println("---- Implementing Insertion Sort Algorithm ----");
		
		System.out.println("Enter the num of elements in the array");
		
		
		int _num=scanner.nextInt();														//gets the next integer from the console
		int[] arr=new int[_num];
		System.out.println("Now enter the elements in the array");
		for (int i = 0; i < arr.length; i++) 
		{
			arr[i]=scanner.nextInt();
		}
		scanner.close();															//close the scanner stream
		System.out.println("Now we will print the sorted array \n");

		insertion_sort(arr);
		
		for (int q : arr) 
		{
			System.out.println(q);
		}
		System.out.println("\n\n------------ End ------------ \n\n");
		
	}


}
