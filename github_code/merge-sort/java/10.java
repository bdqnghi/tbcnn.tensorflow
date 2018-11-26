/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package cs566.hw02;

import static java.lang.System.out;

/**
 *
 * @author Chenghsien "Jason" Lu
 */
public class Sort {
    public static Integer[] Insertion(Integer[] A) {
        /* pseudocode
        for j = 2 to n 
                key = A[ j ]; 
                // Insert A[ j ] into the sorted sequence A[1 . . j − 1] 
                i = j – 1; 
                count++; // increment count 
                while i > 0 and A[i ] > key 
                        count++; // increment count 
                        A[i + 1] = A[i ]; 
                        i = i – 1; 
                A[i + 1] = key;

        */
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
        /*
        MERGE-SORT(A, p, r) 
        if p < r 
                q = |(p + r)/2|
                MERGE-SORT(A, p, q) 
                MERGE-SORT(A, q + 1, r) 
                MERGE(A, p, q, r) 
        */
        
        return null;
    }
    
    private static Integer[] Merge(Integer[] A, int p, int q) {
        /*
        MERGE(A, p, q, r) 
        n1 = q − p + 1 
        n2 =r − q 
        // create arrays L[1 . . n1 + 1] and R[1 . . n2 + 1] 
        for i = 1 to n1 
                L[i ] = A[p + i − 1] 
        for j = 1 to n2 
                R[ j ] = A[q + j ] 
                L[n1 + 1] = ∞; R[n2 + 1] = ∞ 
        i = 1; j = 1 
        count++; // count is incremented 
        for k = p to r 
                count++; // count is incremented 
                if L[i ] ≤ R[ j ] 
                        A[k] = L[i ] 
                        i = i + 1 
                else A[k] = R[ j ] 
                        j = j + 1 

        

        */
        return null;
    }
    
    
}
