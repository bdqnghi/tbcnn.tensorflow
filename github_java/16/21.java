package yuanqi;

/**
 * Quicksort class sorts a specific array to an
 * ascending order by having the class quicksort and 
 * a helper class quicksortKernel.
 * @author Govind
 * @author Yuanqi 
 *
 */
public class Quicksort extends Partition{


	/**
	 * Sort the array in an ascending order.
	 * @param a		the array needed to be sorted
	 * @param left	the start index of the subarray which needs to be sorted 
	 * @param right		the end index of the subarray which needs to be sorted
	 */

	public static void quicksortKernel (int a[], int left, int right) {


		//The case when there is not element in the array.
		if(a.length == 0) {
			System.out.println("Error: Empty array!");
		}

		if(right > left) {
			int middle = partition(a,left,right);
			quicksortKernel(a,left,middle-1);
			quicksortKernel(a,middle+1,right);
		}
	}

	/**
	 * Sort the array in an ascending order using the helper function 
	 * qucksortKernel. Applies partition recursively,
	 * until subintervals have no more than one element (and thus are already sorted)
	 * @param a		the array needed to be sorted
	 */
	public static void quicksort (int a[]){
		quicksortKernel (a, 0, a.length-1);
	}

	

	public static void main(String arg[]) {
		//Test quicksort with a random array
		int a[]= {2,4,1,5,2,5,8,0};
		quicksort(a);
		for(int i=0; i<a.length; i++) {
			System.out.println("a: " + a[i]);
		}

		/*Test quicksort with a ascending sorted array
		  to check the handling of out of bound problem*/
		int a2[]= {2,3,4,5};
		quicksort(a2);
		for(int i=0; i<a2.length; i++) {
			System.out.println("a2: " + a2[i]);
		}

		/*Test quicksort with a descending sorted array
		 to check the handling of out of bound problem*/
		int a3[]= {5,4,3,2};
		quicksort(a3);
		for(int i=0; i<a3.length; i++) {
			System.out.println("a3: " + a3[i]);
		}

		//Test quicksort with empty array
		int a4[]= {};
		quicksort(a4);
		for(int i=0; i<a4.length; i++) {
			System.out.println("a4: " + a4[i]);
		}

	}


}
