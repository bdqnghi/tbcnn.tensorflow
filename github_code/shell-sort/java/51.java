//Solution 1: gap = n/2

/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc = new Scanner(System.in);
		int size = sc.nextInt();
		int a[] = new int[size];
		for(int i = 0; i < size; i++)
			a[i] = sc.nextInt();
		Ideone ideone = new Ideone();
		ideone.shellSort(a, a.length);
		for(int i = 0 ;i < a.length; i++)
		System.out.print(a[i] + " ");
	}
	
	public void shellSort(int a[], int n){
		for(int gap = n/2; gap > 0; gap/=2){
			for(int i = gap; i<n; i++){
				int temp = a[i];
				int j;
			for(j = i; j>= gap && a[j-gap] > temp; j-=gap)
				a[j] = a[j - gap];
			a[j] = temp;
			}	
		}	
	}
}

//Solution 2: gap = 3n + 1

/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc = new Scanner(System.in);
		int size = sc.nextInt();
		int a[] = new int[size];
		for(int i = 0; i < size; i++)
			a[i] = sc.nextInt();
		Ideone ideone = new Ideone();
		ideone.shellSort(a, a.length);
		for(int i = 0 ;i < a.length; i++)
		System.out.print(a[i] + " ");
	}
	
	public void shellSort(int a[], int n){
		int h = 1;
		while(h<n/3) h = 3*h + 1; // 1, 4, 13, 40, 121, 364, ...
		
		while(h >=1){
			for(int i = h; i< n ; i++){
				int temp = a[i];
				int j;
				for(j = i; j>= h && a[j-h] > temp; j-=h)
					a[j] = a[j - h];
				a[j] = temp;
			}	
			
			h = h/3;
		}
		
	}
}