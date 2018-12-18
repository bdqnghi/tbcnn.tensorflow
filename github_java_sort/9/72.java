package sort;


public class Selectionsort {
private int[] arr;
	
	public Selectionsort(int[] a){
		this.arr = a;
		selectionsort(arr, arr.length);
		printArray(arr);
	}
	
	private void selectionsort(int[] a, int len) {
		
		for (int i = 0; i < len-1; i++) {
			int min = i;	
			
			
			for (int j = i+1; j < len; j++) {
				
				if (a[j] <= a[min]) {
					min = j;
				}
			}
			
			
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}

	private void printArray(int[] a) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
	}
	public static void main(String[] args) {
		int[]x = new int[]{7,2,1,6,9,8,5,3,4};

		Selectionsort ss = new Selectionsort(x);
	}
}
