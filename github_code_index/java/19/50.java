package _01_Array.Finding_a_Number;
/*
LeetCode – First Missing Positive (Java)

Given an unsorted integer array, find the first missing positive integer. For example, given [1,2,0] return 3 and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

Analysis

This problem can solve by using a bucket-sort like algorithm. Let's consider finding first missing positive and 0 first. The key fact is that the ith element should be i, so we have:
i==A[i]
A[i]==A[A[i]]

For example, given an array {1,2,0,4}, the algorithm does the following:
 */

public class First_Missing_Positive {

    int firstMissingPositiveAnd0(int A[]) {
        int n = A.length;
        for (int i = 0; i < n; i++) {
            // when the ith element is not i
            while (A[i] != i) {
                // no need to swap when ith element is out of range [0,n]
                if (A[i] < 0 || A[i] >= n)
                    break;

                //handle duplicate elements
                if(A[i]==A[A[i]])
                    break;
                // swap elements
                int temp = A[i];
                A[i] = A[temp];
                A[temp] = temp;
            }
        }

        for (int i = 0; i < n; i++) {
            if (A[i] != i)
                return i;
        }

        return n;
    }

//-------------------------------------------------------------------------------


//Java Solution

    //This problem only considers positive numbers, so we need
    // to shift 1 offset. The ith element is i+1.

    public int firstMissingPositive2(int[] A) {
        int n = A.length;

        for (int i = 0; i < n; i++) {
            while (A[i] != i + 1) {
                if (A[i] <= 0 || A[i] >= n)
                    break;

                if(A[i]==A[A[i]-1])
                    break;

                int temp = A[i];
                A[i] = A[temp - 1];
                A[temp - 1] = temp;
            }
        }

        for (int i = 0; i < n; i++){
            if (A[i] != i + 1){
                return i + 1;
            }
        }

        return n + 1;
    }

//-------------------------------------------------------------------------------






//-------------------------------------------------------------------------------






//-------------------------------------------------------------------------------






//-------------------------------------------------------------------------------







}
