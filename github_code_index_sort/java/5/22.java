package sorting;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class Bubble {

	public static void bubbleSort(float [] unsorted) {
		System.out.print("\n");
		
		for (int iter = 1; iter < unsorted.length; iter++) {
			for (int inner = 0; inner < (unsorted.length - iter); inner++) {
				if ((((Comparable) (unsorted[inner])).compareTo(unsorted[inner + 1])) > 0) {
					/**Compare in order to sort
					 * 
					 */
					float tmp = unsorted[inner];
					unsorted[inner] = unsorted[inner + 1];
					unsorted[inner + 1] = tmp;
				}
			}
		}
	}

	public static void bubble(float [] unsorted) {
		for (int iter = 1; iter < unsorted.length; iter++) {
			for (int inner = 0; inner < (unsorted.length - iter); inner++) {
				if ((((Comparable) (unsorted[inner])).compareTo(unsorted[inner + 1])) > 0) {
					/**Compare in order to sort
					 * 
					 */
					float tmp = unsorted[inner];
					unsorted[inner] = unsorted[inner + 1];
					unsorted[inner + 1] = tmp;
				}
			}
		}

	}
				

}
