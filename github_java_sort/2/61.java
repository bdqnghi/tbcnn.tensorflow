



public class Solution {
    
    public void sortIntegers2(int [] A) {
        int n = A.length;
        if (n > 0) {
            int [] temp = new int[n];
            mergeSort(A, 0, n - 1, temp);
        }
    }
    

    private void mergeSort(int [] A, int start, int end, int [] temp) {
        
        if (start < end) {
            int mid = start + (end - start) / 2;
            mergeSort(A, start, mid, temp);
            mergeSort(A, mid + 1, end, temp);
            
            
            merge2(A, start, mid, end, temp);
        }
    }
    
    private void merge2(int [] A, int start, int mid, int end, int [] temp) {
        int i = mid, j = end, k = end; 
        
        while (i >= start && j >= mid+1) {
            if (A[i] > A[j]) {
                temp[k--] = A[i--];
            }
            else {
                temp[k--] = A[j--];
            }
        }
        
        if (i < start) {
            while (j >= mid+1) temp[k--] = A[j--];
        }
        if (j < mid+1) {
            while (i >= start) temp[k--] = A[i--];
        }
        
        for (int p = start; p <= end; ++p) {
            A[p] = temp[p];
        }
    }
    
    private void merge(int [] A, int start, int mid, int end, int [] temp) {
        int i = start, j = mid + 1, k = start;
        
        while (i <= mid || j <= end) {
            if (j > end || (i <= mid && A[i] <= A[j])) {
                temp[k++] = A[i++];
            }
            else {
                temp[k++] = A[j++];
            }
        }
        
        for (int p = start; p <= end; ++p) {
            A[p] = temp[p];
        }
    }
};
