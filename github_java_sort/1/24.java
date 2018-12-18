package sort;


public class Insertionsort {
	private int[] arr;
	
	public Insertionsort(int[] a){
		this.arr = a;
		insertionSort(arr, arr.length);
		printArray(arr);
	}
	private void insertionSort(int[] a, int len) {
		
		for (int i = 1; i < len; i++) {
			int value = a[i];	
			int position = i;	
			
			
			while (position > 0 && a[position-1] > value) {
				a[position] = a[position-1];	
				position--;						
			}
			
			
			a[position] = value;
		}
	}
	
	private void printArray(int[] a) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
	}
	
	public static void main(String[] args) {
		int[]x = new int[]{7,2,1,9,6,8,5,3,4};

		Insertionsort is = new Insertionsort(x);
	}
}
