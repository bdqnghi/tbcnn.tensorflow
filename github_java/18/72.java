package sort;

/*
 * Selection sort algorithm
 * Time complexity:
 * Average case, Worst case, Best case - O(n^2)
 */
public class Selectionsort {
private int[] arr;
	
	public Selectionsort(int[] a){
		this.arr = a;
		selectionsort(arr, arr.length);
		printArray(arr);
	}
	
	private void selectionsort(int[] a, int len) {
		//Loop to length - 2 because the next element will be looked at in the following loop
		for (int i = 0; i < len-1; i++) {
			int min = i;	//assume that the current index has the minimum element
			
			//Loop from the next index till the end
			for (int j = i+1; j < len; j++) {
				//If an element is less, mark it's index as minimum
				if (a[j] <= a[min]) {
					min = j;
				}
			}
			
			//Swap the current element with the minimum element
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
