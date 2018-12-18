package sorting;

import java.util.Arrays;

public class bubblesort {

	public static void main(String[] args) {
		
		
		
		
		
        int a[] = {6,1,7,2};
        Arrays.toString(bubbleSort(a));
      
        
        Long.valueOf("300100110974924");
	}
	
	public static int[] bubbleSort(int a[]){
		boolean swapped = true;
		for(int i=0;i<a.length && swapped;i++){
			swapped = false;
			System.out.println(Arrays.toString(a));
			for(int j=0;j<a.length-i-1;j++){
				if(a[j]>a[j+1]){
					int swap = a[j];
					a[j] = a[j+1];
					a[j+1]= swap;
					swapped = true;
				}
			}
		}
		return a;
	}
	
	public static int[] recursivebubble(int a[],int iterCounter){
		if(iterCounter==a.length-1){
			return a;
		}
		for(int j=0; j<a.length-iterCounter-1;j++){
			if(a[j]>a[j+1]){
				int swap = a[j];
				a[j] = a[j+1];
				a[j+1]= swap;
			}
		}
		return recursivebubble(a,iterCounter+1);
	}

}
