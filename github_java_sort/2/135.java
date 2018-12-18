
package me.qcarver.filesorts;

import java.util.Date;


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
