import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;
class BSort
{
	int a[];

	BSort(int n)
	{
		a=new int[n];
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the elements");
		for(int i=0;i<n;i++)
			a[i]=sc.nextInt();
	}

	
	void bubbleSort()
	{
		for(int i=0;i<a.length;i++)
		{
			for(int j=0;j<a.length-1;j++)
			{
				if(a[j]>a[j+1])
				{
					int t = a[j];
					a[j]=a[j+1];
					a[j+1]=t;
				}
			}
		}
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+ "\t");
	}
  
	void modifiedBubbleSort()
	{
		for(int i=0;i<a.length;i++)
		{
			boolean x=true;
			for(int j=0;j<a.length-1;j++)
			{
				if(a[j]>a[j+1])
				{
					x=false;
					int t = a[j];
					a[j]=a[j+1];
					a[j+1]=t;
				}
			}
			if(x)
				break;
		}
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+ "\t");
	}

}
class bubble_sort
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the no of elements for modified bubble sort");
		int n=sc.nextInt();

		BSort b = new BSort(n);
		System.out.println();

		System.out.println("Modified Bubble Sort");
		b.modifiedBubbleSort();
		System.out.println();
		System.out.println();
		
		System.out.println("Enter the no of elements for bubble sort");
		int n1=sc.nextInt();

		BSort b1 = new BSort(n1);
		
		System.out.println("Bubble Sort");
		b1.bubbleSort();
		System.out.println();
		
		
	}
}