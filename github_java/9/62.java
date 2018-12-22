import java.util.*;
import java.io.*;

public class heapsort
{
	public static void insert(int a[],int data,int m,int n)
	{
		int last,j=0,t;
		if(a[0]==0)
		{
		 a[0]=a[0]+1;       //a[0] is used to store the no. of Elements stored in the heap
		 a[m]=data;         
	    }
	    else
	    {
          last=a[0];
          if(last>=n)
          {
          	System.out.println("Heap is Full");
          }
          else
          {
          a[0]++;
          a[m]=data;
          j=m;

          //Reheapify....Comparing the Parent with child, so as to make it a max heap
          while(true)
          {
          	j=j/2;   //The parent of the current Element will be on i/2th position if the element is on ith position
          	if(j>=1)
          	{
          		if(a[j]<a[m])
          		{
                  t=a[j];
                  a[j]=a[m];
                  a[m]=t;
          		}
          		m=j;    //Now we have set m to it's parent's position
          	}
          	else
          		break;
          }
	    }
	    return;
	}
	}   //Insertion Ends


	//Driver Program to Display Heap
	public static void displayHeap(int a[])
	{
		for(int i=1;i<=a[0];i++)     //We are printing the heap in the form of a complete binary tree
		{
			System.out.println(a[i]+" ");
		}
	}

  //Driver Program to Check Max Heap Property
  public static void check(int a[],int i,int n)
  {
    int t;
    if(i==n)                          //If all the Elements are compared with the root then return
      return;
    else
    {
       if((2*i)<=n)     //Checking for Array out of Bound     
       if(a[i]<a[2*i])     //Comparing the left child with the root and swapping if root is smaller than the left child
       {
          t=a[i];
          a[i]=a[2*i];
          a[2*i]=t;

       }
       if((2*i+1)<=n)     //Checking for Array out of bound
       if(a[i]<a[2*i+1])   //Comparing the right child with the root and swapping if root is smaller than the right child
       {
          t=a[i];
          a[i]=a[2*i+1];
          a[2*i+1]=t;

       }
       if(2*i<=n)         //Checking for Array out of bound
       check(a,2*i,n);   //Recursively Checking the max heap property in left child
       if(2*i+1<=n)       //Checking for Array out of bound
       check(a,2*i+1,n);  //Recursively Checking the max heap property in right child
    }
  }


  //Driver Program to Heap Sort by recursively deleting the root i.e a[1] element of the heap
  public static void heapSort(int a[])
  { 
    //System.out.println(a[0]+"  ");
    while(a[0]!=0)                      //Checking whether the heap is empty or not
    {
    System.out.print(a[1]+", ");         //Printing the root element
    a[1]=a[a[0]];                       //Swapping the last Inserted Element to the root
    --a[0];                           //Decreasing the size of heap as one Element is printed (deleted virtually) 
    int i=1;
    check(a,i,a[0]);             //Check function call to check for Max Heap Property after Swapping
    }
  }
  
  public static void main(String args[])
  {
    int data;
    int m=1;
    Scanner in=new Scanner(System.in);
    System.out.print("Enter the no. of Elements : ");
    int n=in.nextInt();
    int a[]=new int[n+1];   //n+1 elements since the insertion in array is starting from 1st index
    a[0]=0;
    System.out.println("Enter the Elements : ");
    for(;m<=n;m++)
    {
    	data=in.nextInt();
    	insert(a,data,m,n);
    } 
    System.out.println("\n");
    displayHeap(a);              //Function Call to display heap

    System.out.println("The Sorted Array in descending order using Heap Sort is : ");
    heapSort(a);	               //Function call to do heap Sort
   }
  }
