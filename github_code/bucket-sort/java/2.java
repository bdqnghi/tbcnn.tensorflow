package sorting;


//http://www.javacodex.com/Sorting/Bucket-Sort

public class BucketSort {

	static int[] array = { 2, 4, 1, 7, 9, 8, 3 };

	public static void main(String[] args) {
		System.out.println("Initial array: ");
		display(array);
		bucketSort(array,9);
		System.out.println("\nSorted array: ");
		display(array);
	}
	
	public static void bucketSort(int[] array,int max_value){
		int[] bucket=new int[max_value+1];
		for(int i=0;i<array.length;i++){
			bucket[array[i]]=bucket[array[i]]+1;
		}
		
		int index=0;
		for(int i=0;i<bucket.length;i++){
			for(int j=0;j<bucket[i];j++){
				array[index++]=i;
			}
		}
	}
	


	public static void display(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
	}
}
