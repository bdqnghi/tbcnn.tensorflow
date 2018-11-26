/*
 * From page 31 of Cormen ...bear in mind this psuedo is 1-based, we won't be
 * MERGE(A, p, middle, r)
 *  n1 = middle-p+1
 *  n2 = r-middle
 *  let L[1..n1+1] and R[1..n2+1] be new arrays
 *  for i = 1 to n1
 *      L[i] = A[p+i-1]
 *  for j = 1 to n2
 *      R[j] = A[middle+j]
 *  L[n1+1] = INFINITY
 *  R[n2+1] = INFINITY
 *  i = 1
 *  j = 1
 *  for k = p to r
 *      if L[i] <= R[j]
 *          A[k]=L[i]
 *          i=i+1
 *      else A[k] = R[j]
 *          j=j+1
 * 
 * 
 * From pg 34 of Cormen
 * MERGE-SORT(A,p,r)
 *  if p<r
 *      middle = floor((p+r)/2)
 *      MERGE-SORT(A,p,middle)
 *      MERGE-SORT(A,middle+1,r)
 *      MERGE(A,p,middle,r)
 */
package me.qcarver.filesorts;

import java.util.Date;

/**
 *
 * @author Quinn
 */
public class MergeSort implements Sorter {
    private A A = null;
    private long sortingTime = 0;
    
    @Override
    public void sort(int[] A){
        Date date = new Date();
        long timeStart = date.getTime();
        this.A = new A(A);
        mergeSort(0, A.length-1);  
        date = new Date();
        long timeEnd = date.getTime();
        sortingTime = timeEnd - timeStart;
    }
    
    /**
     * as per psuedo code from Cormen.. only zero based
     * @param start the beginning index
     * @param end the ending index
     */
    private void mergeSort(int start, int end){
        if (start<end){
            int middle=(start+end)/2;
                mergeSort(start,middle);
                mergeSort(middle + 1, end);
                merge(start,middle,end);
        }
    }
    
    private void merge(int start, int middle, int end) {
        int n1 = middle - start + 1;
        int n2 = end - middle;
        int L[] = new int[n1 + 1];
        int R[] = new int[n2 + 1 ];
        for (int i = 0; i < n1; i++) {
            L[i] =  A.get(start + i);
        }
        for (int j = 0; j < n2; j++) {
            R[j] =  A.get(middle + 1 + j);
        }
        L[n1] = Integer.MAX_VALUE;
        R[n2] = Integer.MAX_VALUE;
        int i = 0;
        int j = 0;
        for (int k = start; k < end + 1; k++) {
            if (L[i] <= R[j]) {
                A.set(k, L[i]);
                i = i + 1;
            } else{ 
                A.set(k, R[j]);
                j = j + 1;
            }
        }
    }

    public int[] getA(){
        return A.get();
    }
    
    @Override
    public Stats getStats(){
        return new Stats(SortMode.MERGE_SORT, A.length(),
                sortingTime, A.getNumReads(), A.getNumWrites());
    }
}
