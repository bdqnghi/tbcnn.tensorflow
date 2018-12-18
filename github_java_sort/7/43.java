package com.Basic.Algorithm;

public class Sort_ShellSort extends CommonUtil{

	
	static void ShellInsertSort(int a[], int n, int dk)  
	{  
		for(int i= dk; i<n; ++i){  
			if(a[i] < a[i-dk]){          
				int j = i-dk;     
				int x = a[i];           
				a[i] = a[i-dk];         
				while(x < a[j]){     
					a[j+dk] = a[j];  
					j -= dk;             
					
					if(j<0) break;
				}  
				a[j+dk] = x;            
			}  
			printArray(a, n,i );  
		}  

	}  

	  
	static void shellSort(int a[], int n){  
		int dk = n/2;  
		while( dk >= 1  ){  
			ShellInsertSort(a, n, dk);  
			dk = dk/2;  
		}  
	}  
	public static void main(String[] args) {
		int[] a = {3,1,5,7,2,4,9,6};  
		shellSort(a,8);  
		printArray(a,8,8);  
	}

}
