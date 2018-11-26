import java.util.*;
import java.lang.*;

class Insertion
{
	public static void main(String args[])
	{
		int arr[],i,j,size,temp;
		long start, end;
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the size");
		size = sc.nextInt();
		
		arr = new int[size];
		//Filling the array with Random numbers
		Random r = new Random();
		for(i = 0; i < size; i++)
		{
			arr[i] = r.nextInt(10000);
		}
		
		/*for(i = 0;i<size;i++){
			System.out.println(arr[i]);
		}*/
		start = System.currentTimeMillis();
		
		for(i = 1; i < size; i++)
		{
			temp = arr[i];
			for(j=i-1; j>=0 && temp<arr[j];j--)
				arr[j+1] = arr[j];
			arr[j+1] = temp;
		}
		
		
		/*for(i = 0;i<size;i++){
			System.out.println(arr[i]);
		}*/
		end = System.currentTimeMillis();
		
		System.out.println("Time Taken = " + (end - start) + "Milliseconds");
	}
}