

package Algorithms;

import java.util.ArrayList;
import java.util.Collections;

public class bucketsort {

	public static void main(String[] args) {
		
		

		double arr[] = {0.89, 0.565, 0.656, 0.1234, 0.665, 0.3434};
		bucketSort ( arr, arr.length );

	}

	public static void bucketSort(double arr[], int n) {
		
		ArrayList<ArrayList<Double>> b = new ArrayList<ArrayList<Double>> ( );

		for (int i = 0; i < n; ++i) {
			b.add ( new ArrayList<Double> ( ) );


		}

		
		for (int i = 0; i < n; i++) {
			int bi = (int) (n * arr[i]); 
			b.get ( bi ).add ( arr[i] );
		}

		
		for (int i = 0; i < n; i++) {
			Collections.sort ( b.get ( i ) );
		}

		
		int index = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < b.get ( i ).size ( ); j++) {
				arr[index++] = b.get ( i ).get ( j );
			}
		}

		for (int i = 0; i < arr.length; ++i) {
			System.out.println ( arr[i] );
		}

	}

}
