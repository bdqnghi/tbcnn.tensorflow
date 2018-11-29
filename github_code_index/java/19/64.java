/*
 * Copyright (c) 2017. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Morbi non lorem porttitor neque feugiat blandit. Ut vitae ipsum eget quam lacinia accumsan.
 * Etiam sed turpis ac ipsum condimentum fringilla. Maecenas magna.
 * Proin dapibus sapien vel ante. Aliquam erat volutpat. Pellentesque sagittis ligula eget metus.
 * Vestibulum commodo. Ut rhoncus gravida arcu.
 */

package Algorithms;

import java.util.ArrayList;
import java.util.Collections;

public class bucketsort {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//float[] arr={1,9,4,7,2,8};

		double arr[] = {0.89, 0.565, 0.656, 0.1234, 0.665, 0.3434};
		bucketSort ( arr, arr.length );

	}

	public static void bucketSort(double arr[], int n) {
		// 1) Create n empty buckets
		ArrayList<ArrayList<Double>> b = new ArrayList<ArrayList<Double>> ( );

		for (int i = 0; i < n; ++i) {
			b.add ( new ArrayList<Double> ( ) );


		}

		// 2) Put array elements in different buckets
		for (int i = 0; i < n; i++) {
			int bi = (int) (n * arr[i]); // Index in bucket
			b.get ( bi ).add ( arr[i] );
		}

		// 3) Sort individual buckets
		for (int i = 0; i < n; i++) {
			Collections.sort ( b.get ( i ) );
		}

		// 4) Concatenate all buckets into arr[]
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
