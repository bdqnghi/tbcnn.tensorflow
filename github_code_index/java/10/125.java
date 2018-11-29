package com.mycompany.app.sortingalgos;

import java.util.Scanner;

public class bubblesort {
	//this method sorts the array
	int [] sort(int array[])
			{
				for(int index=0;index<array.length;index++)
				{
					for(int index2=index+1;index2<array.length;index2++)
					{
						if(array[index]>array[index2])
						{
							int temp=array[index];
							array[index]=array[index2];
							array[index2]=temp;
						}
					}
				}
				return array;
		
			}
	//this method displays the sorted array
	void display(int array[])
	{
		System.out.println("The sorted array is:");
		for(int element:array)
		{
			System.out.print(element+" ");
		}
	}
	//this is main method
	public static void main(String[] args) 
	{
		Scanner scan=new Scanner(System.in);
		System.out.println("Enter the no of elements in the array:");
		int no_of_elements=scan.nextInt();
		int array[]=new int[no_of_elements];
		System.out.println("Enter the elements in the array:");
		for(int i=0;i<no_of_elements;i++)//here i is index
		{
			array[i]=scan.nextInt();
		}
		bubblesort object=new bubblesort();
		object.display(object.sort(array));
		
		
	}
}
