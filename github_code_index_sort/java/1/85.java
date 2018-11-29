import java.util.*;
import java.lang.*;
import java.io.*;

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
		ideone.insertionSort(a);
		for(int i = 0 ;i < a.length; i++)
		System.out.print(a[i] + " ");
	}
	
	public void insertionSort(int a[]){
		int i, key;
		for(int j = 1; j < a.length;j++){
			key = a[j];
			i = j - 1;
			while(i>=0 && a[i] > key) {
				a[i+1] = a[i];
				i = i - 1;
			}
			a[i + 1] = key;
		}	
	}
}


// 6/27/18 - Inserion Sort
/*
		int a[] = new int[]{4,5,7,2,4};
		for( int i = 1; i < a.length; i++) {
			int temp = a[i];
			for(j = i; j > 0; j--) {
				if(temp > a[j - 1]) {
					break;
				} else {
					a[j] = a[j - 1];
				}
			}
			a[j] = temp;
		}
		for(int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
*/