/*
 * Created on 08.03.2005
 */
package jku.ss09.mir.lastfmecho.comirva.utils;

import java.util.*;

/**
 * This class implements special algorithms needed for sorting data vectors 
 * and updating their accompanying meta-data vectors.
 * 
 * @author Markus Schedl
 */
public class VectorSort {
	
	/**
	 * Sorts the Vector <code>sort</code> in decreasing order and also updates
	 * the Vector <code>metaData</code>. Each element in Vector <code>sort</code> is
	 * considered to have a meta-data element in Vector <code>metaData</code> at
	 * the same position. For example, <code>metaData.elementAt[i]</code> is considered to
	 * be a String describing the value <code>sort.elementAt[i]</code>. After the sort,
	 * the Vector <code>sort</code> is sorted and the Vector <code>metaData</code> is
	 * adapted according to the new positions of the values in <code>sort</code>.
	 * 
	 * @param sort		a Vector containing Doubles that represent a distance vector
	 * @param metaData	a Vector containing Strings that represent the meta-data to be adapted
	 */
	public static void sortWithMetaData(Vector sort, Vector metaData) {
		// convert data vector to array
		Object sortArrayTemp[] = sort.toArray();
		double sortArray[] = new double[sortArrayTemp.length];
		for (int i=0; i<sortArrayTemp.length; i++)
			sortArray[i] = ((Double)sortArrayTemp[i]).doubleValue();
		// convert meta-data vector to array
		Object metaDataArrayTemp[] = metaData.toArray();
		String metaDataArray[] = new String[sortArrayTemp.length];
		for (int i=0; i<metaDataArrayTemp.length; i++)
			metaDataArray[i] = (String)metaDataArrayTemp[i];
		// start quick-sort
		doQuickSort(0, sortArray.length-1, sortArray, metaDataArray);
		// clear original Vectors
		sort.clear();
		metaData.clear();
		// insert sorted values
		for (int i=0; i<sortArray.length; i++) {
			sort.addElement(new Double(sortArray[i]));
			metaData.addElement(metaDataArray[i]);
		}
	}
	
    /**
     * Uses Quick-Sort to sort the array <code>sortArray</code> and adapt the array
     * <code>metaDataArray</code> accordingly. Sorting is performed in decreasing order. 
     * 
     * @param leftBorder		the left border for the Quick-Sort algorithm
     * @param rightBorder		the right border for the Quick-Sort algorithm
     * @param sortArray			a double[] representing the values to be sorted
     * @param metaDataArray		a String[] representing the meta-data to be updated according to new order after the sort
     */
    static void doQuickSort(int leftBorder, int rightBorder, double[] sortArray, String[] metaDataArray) {
    	int i, j;				// borders
		double x;				// actual value
        double swapTempDouble;	// temporary double for swap
        String swapTempString;	// temporary String for swap

        i = leftBorder;
        j = rightBorder;
        x = sortArray[(leftBorder+rightBorder)/2];
        do {
            while (sortArray[i] > x) 
            	i++;
            while (x > sortArray[j])
            	j--;
            if (i<=j) {
            	// swap data-elements
                swapTempDouble = sortArray[i]; 
                sortArray[i] = sortArray[j];
                sortArray[j] = swapTempDouble;
                // swap meta-data-elements the same way
                swapTempString = metaDataArray[i];
                metaDataArray[i] = metaDataArray[j];
                metaDataArray[j] = swapTempString;
                i++;
                j--;
            }
        }
        while (!(i > j));
        if ( leftBorder < j ) doQuickSort(leftBorder, j, sortArray, metaDataArray);
        if ( i < rightBorder ) doQuickSort(i, rightBorder, sortArray, metaDataArray);
    }
	
}
