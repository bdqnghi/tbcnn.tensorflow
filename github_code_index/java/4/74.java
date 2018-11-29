package datastructures;
/***
 * Implementation of Insertion sort
 * @author Mohua
 *
 */


public class Insertionsort {
	public static void sort(int[] arr){
		for (int j=1;j<arr.length-1;j++){
			int key=arr[j];
			System.out.println("The key is "+key);
			int i=j-1;
			while(i>=0 && arr[i]>key){
				arr[i+1]=arr[i];
				i=i-1;
			}
			arr[i+1]=key;
			show(arr);
		}
	}
private static void show(int[] arr){
	for (int x: arr){
	System.out.print(x+" ");
	}
	System.out.println();
}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] arr={3, 41, 52, 26, 38, 57, 9, 49};
		sort(arr);
	}

}
