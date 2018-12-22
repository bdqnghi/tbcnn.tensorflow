package chapter2;

import java.util.Arrays;

/**
 * @Author : jnu_mrc jnu_mrc1990@163.com
 * @Date : Created in 14:45 2017/11/14
 */
public class MergeSort {
    public static void main(String[] args) {
        int[] arr = {4,1,8,6,3,9,7,5,2};
        mergeSort(arr,0,arr.length-1);
        System.out.println(Arrays.toString(arr));
    }

    /**
     * //MERGE(A,p,q,r)
     * n1 = q - p + 1
     * n2 = r - q
     * let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
     * for i = 1 to n1
     *     L[i] = A[p + i - 1]
     * for j = 1 to n2
     *     R[j] = A[q + j]
     * L[n1 + 1] = ∞
     * R[n2 + 1] = ∞
     * i = 1
     * j = 1
     * for k = p to r
     *     if L[i] <= R[j]
     *         A[k] = L[i]
     *         i = i + 1
     *     else
     *         A[k] = R[j]
     *         j = j + 1
     * @param arr
     * @param p
     * @param q
     * @param r
     */
    private static void merge(int[] arr, int p, int q, int r){
        int n1 = q - p + 1;
        int n2 = r - q;
        int[] left = new int[n1+1];
        int[] right = new int[n2+1];
        for (int i = 0; i < n1; i++) {
            left[i] = arr[p + i];
        }
        for (int i = 0; i < n2; i++) {
            right[i] = arr[q + i + 1];
        }
        left[n1] = Integer.MAX_VALUE;
        right[n2] = Integer.MAX_VALUE;
        int a = 0,b = 0;
        for (int i = p; i <= r; i++) {
            if(left[a] <= right[b]){
                arr[i] = left[a++];
            }else{
                arr[i] = right[b++];
            }
        }
    }

    /**
     * //MERGE-SORT(A,p,r)
     * if p < r
     *     q = (p+r)/2
     *     MERGE-SORT(A,p,q)
     *     MERGE-SORT(A,q+1,r)
     *     MERGE(A,p,q,r)
     * @param arr
     * @param p
     * @param r
     */
    public static void mergeSort(int[] arr, int p, int r){
        if(p < r){
            int q = (p + r) / 2;
            mergeSort(arr,p,q);
            mergeSort(arr,q + 1,r);
            merge(arr,p,q,r);
        }
    }
}
