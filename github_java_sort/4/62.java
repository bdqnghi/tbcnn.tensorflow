import java.util.*;
import java.io.*;

public class heapsort
{
	public static void insert(int a[],int data,int m,int n)
	{
		int last,j=0,t;
		if(a[0]==0)
		{
		 a[0]=a[0]+1;       
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

          
          while(true)
          {
          	j=j/2;   
          	if(j>=1)
          	{
          		if(a[j]<a[m])
          		{
                  t=a[j];
                  a[j]=a[m];
                  a[m]=t;
          		}
          		m=j;    
          	}
          	else
          		break;
          }
	    }
	    return;
	}
	}   


	
	public static void displayHeap(int a[])
	{
		for(int i=1;i<=a[0];i++)     
		{
			System.out.println(a[i]+" ");
		}
	}

  
  public static void check(int a[],int i,int n)
  {
    int t;
    if(i==n)                          
      return;
    else
    {
       if((2*i)<=n)     
       if(a[i]<a[2*i])     
       {
          t=a[i];
          a[i]=a[2*i];
          a[2*i]=t;

       }
       if((2*i+1)<=n)     
       if(a[i]<a[2*i+1])   
       {
          t=a[i];
          a[i]=a[2*i+1];
          a[2*i+1]=t;

       }
       if(2*i<=n)         
       check(a,2*i,n);   
       if(2*i+1<=n)       
       check(a,2*i+1,n);  
    }
  }


  
  public static void heapSort(int a[])
  { 
    
    while(a[0]!=0)                      
    {
    System.out.print(a[1]+", ");         
    a[1]=a[a[0]];                       
    --a[0];                           
    int i=1;
    check(a,i,a[0]);             
    }
  }
  
  public static void main(String args[])
  {
    int data;
    int m=1;
    Scanner in=new Scanner(System.in);
    System.out.print("Enter the no. of Elements : ");
    int n=in.nextInt();
    int a[]=new int[n+1];   
    a[0]=0;
    System.out.println("Enter the Elements : ");
    for(;m<=n;m++)
    {
    	data=in.nextInt();
    	insert(a,data,m,n);
    } 
    System.out.println("\n");
    displayHeap(a);              

    System.out.println("The Sorted Array in descending order using Heap Sort is : ");
    heapSort(a);	               
   }
  }
