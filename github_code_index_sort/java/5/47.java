package HackerRank;

public class Bubblesort {

	/**
	 * @param args
	 */
	static void bubble(int arr[]){
		boolean swapped = true ;
		while(swapped){
			swapped =false;
		for(int i=0;(i<arr.length)&&(i+1<arr.length);i++){
			if(arr[i] > arr[i+1]){
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = true;
			}
		}
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int arr[] = {5,4,4,2,2,8};
		bubble(arr);
		for(int v : arr){
			System.out.println(v);
		}
		
	}

}
