package sort.divide;

import sort.insertion.InsertionSort;

/**
 * @autthor Mchi
 * @since 2017/11/16
 */

public abstract class DivideAndConquer {



    //-------------------------------------------------------------------
    //
    //MERGE(A,p,q,r)
    //     n1 <- q-p+1
    //     n2 <- r-q
    //     create arrays L[1...n1+1] and R[1...n2+1]
    //     for i<- 1 to n1
    //         do L[i] <- A[p+i-1]
    //     for j<- 1 to n2
    //         do R[j] <- A[q+j]
    //     L[n1+1] <- ∞
    //     R[n2+1] <- ∞
    //     i <- 1
    //     j <- 1
    //     for k <- p to r
    //         do if L[i]<=R[j]
    //               then  A[k] <- L[i]
    //                     i <- i+1
    //               else  A[k] <- R[j]
    //                     j <- j+1
    //
    //MERGE-SORT(A,p,r)
    //     if p<r
    //        q <- (p+r)/2
    //        MERGE-SORT(A,p,q)
    //        MERGE-SORT(A,q+1,r)
    //        MERGE(A,p,q,r)
    //-------------------------------------------------------------------

    /**
     * 分治法排序
     * @param arr 排序数组
     * @param p   排序数组下标
     * @param q   排序数组下标
     * @param r   排序数组下标
     *            p=<q<r
     */
    public static void merge(int[] arr,int p,int q,int r){


        int lLen = q-p+1;
        int rLen = r-q;

        int[] L = new int[lLen+1];
        int[] R = new int[rLen+1];

        for (int i = 0; i < lLen; i++) {
            L[i] = arr[p+i];
        }

        for (int j = 0; j < rLen; j++) {
            R[j] = arr[q+j+1];
        }

        L[lLen] = Integer.MAX_VALUE;
        R[rLen] = Integer.MAX_VALUE;


        int i=0,j=0;

        for(int k=p;k<=r;k++){
            if(L[i]<=R[j]){
                arr[k]=L[i];
                i++;
            }else {
                arr[k]=R[j];
                j++;
            }
        }
    }

    //-------------------------------------------------------------------
    //MERGE-SORT(A,p,r)
    //     if p<r
    //        q <- (p+r)/2
    //        MERGE-SORT(A,p,q)
    //        MERGE-SORT(A,q+1,r)
    //        MERGE(A,p,q,r)
    //-------------------------------------------------------------------
    public static void mergeSort(int[] arr,int p,int r){

        if(p<r){
            int q=(p+r)/2;
            mergeSort(arr,p,q);
            mergeSort(arr,q+1,r);
            merge(arr,p,q,r);
            print(arr);
        }
    }


    static void print(int[] arr){

        for (int i=0;i<arr.length;i++){
            System.out.print(arr[i]+"  ");
        }
        System.out.println();
    }
}
