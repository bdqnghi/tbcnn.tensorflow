import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
/**
 * http://www.geeksforgeeks.org/bucket-sort-2/
 * http://www.geeksforgeeks.org/bucket-sort/
 */

/**
 * @author rakshith
 *
 */
public class Main {
	
	public static void main(String[] args){
		double[] array = {0.0, 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
		System.out.println(Arrays.toString(array));
		bucketSort(array);
		System.out.println(Arrays.toString(array));
	}
	
	public static void bucketSort(double[] array){
		@SuppressWarnings("unchecked")
		ArrayList<Double>[] buckets = new ArrayList[10];
		
		for(int i=0; i<10 ;i++){
			buckets[i] = new ArrayList<Double>();
		}
		
		for(int i=0; i<array.length; i++){
			int index = (int)array[i]*10;
			buckets[index].add(array[i]);
		}
		
		for(int i=0; i<10; i++){
			Collections.sort(buckets[i]);
		}
		
		int index = 0;
		for(int i=0; i<10; i++){
			for(int j=0; j<buckets[i].size(); j++){
				array[index++] = buckets[i].get(j);
			}
		}
	}
}
