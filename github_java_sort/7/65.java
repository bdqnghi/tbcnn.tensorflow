import java.io.*;
import java.util.*;
class Shellsort{
	public static int gap = 0;
	public static int getGap(){
		gap = gap/2;
		return gap;
	}
	public static void display(int a[],int n){
		for(int i=0;i<n;i++){

			System.out.print(a[i]+" ");
		}
	}
	public static void shellSorting(int a[],int n){
		int g = getGap();
		if(g==0){
			if(n>=2 && a[0]>a[1])
			{
				int temp = a[0];
				a[0] = a[1];
				a[1] = temp;	
			}
			display(a,n);
		}
		else{
		for(int i=0;i<n-g;i++){
			if(a[i]>a[i+g])
			{
				int temp = a[i];
				a[i] = a[i+g];
				a[i+g] = temp;
			}
		}
		shellSorting(a,n);
	}
}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the elements :");
		int n = sc.nextInt();
		int a[] = new int[n];
		for(int i=0;i<n;i++)
			a[i] = sc.nextInt();
		gap = a.length;
		shellSorting(a,n);
	}
}