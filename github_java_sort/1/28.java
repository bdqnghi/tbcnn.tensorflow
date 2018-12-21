
package algorithms;


public class InsertionSort {

	
	
	static int a[] = {5,2,4,6,1,3};
		
	public static void main(String[] args) {
		InsertionSort insertionSort = new InsertionSort();
		insertionSort.printArray(a);
		insertionSort.insetionSortAscending(a);
		insertionSort.printArray(a);
		insertionSort.insetionSortDescending(a);
		insertionSort.printArray(a);
	}
	
	public void printArray(int a[]){
		for(int i=0;i<a.length;i++){
			System.out.print(" " + a[i]);
		}
		System.out.println();
	}
	
	public void insetionSortAscending(int a[]){
		for(int i=1;i<a.length;i++){
			int key = a[i];
			int j = i-1;
			while(j >= 0 && a[j]>key){
				a[j+1]=a[j];
				j--;
			}
			a[j+1] = key;
		}
	}
	public void insetionSortDescending(int a[]){
		for(int i=a.length-2;i>=0;i--){
			int key = a[i];
			int j = i+1;
			while(j < a.length && a[j] > key){
				a[j-1]=a[j];
				j++;
			}
			a[j-1] = key;
		}
	}

}
