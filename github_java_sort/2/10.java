

package cs566.hw02;

import static java.lang.System.out;


public class Sort {
    public static Integer[] Insertion(Integer[] A) {
        
        int count = 0;
        for(int j = 1; j < A.length; j++) {
            int key = A[j];
            int i = j - 1;
            count++;
            while(i >= 0 && A[i] > key) {
                count++;
                A[i + 1] = A[i];
                i = i - 1;
            }
            A[i + 1] = key;
        }
        out.println("\tCount: " + count);
        return A;
    }
    
    public static Integer[] MergeSort(Integer[] A, int p, int q, int r) {
        
        
        return null;
    }
    
    private static Integer[] Merge(Integer[] A, int p, int q) {
        
        return null;
    }
    
    
}
