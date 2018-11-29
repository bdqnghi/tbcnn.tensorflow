package sort.heapify;

/**
 * @autthor Mchi
 * @since 2017/11/22
 */

public abstract class HeapSort {


    //-------------------------------------------------------------------
    // STRUCT HEAP{
    //      heap-size[A]
    //      length[A]
    // }
    //
    // PARENT(i)
    //      return i/2
    // LEFT(i)
    //      return 2*i
    // RIGHT(i)
    //      return 2*i+1
    //
    //
    //
    //MAX-HEAPIFY(A,i)
    //    l<-LEFT(i)
    //    r<-RIGHT(i)
    //    if l<=heap-size[A] and A[l]>A[i]
    //       then largest<-l
    //       else largest<-i
    //    if r<=heap-size[A] and A[r]>A[largest]
    //        largest<-r
    //    if largest!=i
    //       then exchange A[i]<->A[largest]
    //            MAX-HEAPIFY(A,largest)
    //
    //
    //BUILD-MAX-HEAP(A)
    //      heap-size[A] <- length[A]
    //      for i <- length[A]/2 downto 1
    //          do MAX-HEAPIFY(A,i)
    //
    //
    //HEAP-SORT(A)
    //      BUILD-MAX-HEAP(A)
    //      for i <- length[A] downto 1
    //          do exchange A[i] <-> A[0]
    //             heap-size[A] = heap-size[A]-1
    //             MAX-HEAPIFY(A,1)
    //-------------------------------------------------------------------

    static int heapSize = 0;
    //-------------------------------------------------------------------
    //HEAP-SORT(A)
    //      BUILD-MAX-HEAP(A)
    //      for i <- length[A] downto 1
    //          do exchange A[i] <-> A[0]
    //             heap-size[A] = heap-size[A]-1
    //             MAX-HEAPIFY(A,1)
    //-------------------------------------------------------------------

    public static void sort(int[] arr){

        buildMaxHeap(arr);
        print(arr);

        for(int i=arr.length-1;i>0;i--){
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
            heapSize--;
            maxHeapify(arr,0);
        }
    }
    //-------------------------------------------------------------------
    //BUILD-MAX-HEAP(A)
    //      heap-size[A] <- length[A]
    //      for i <- length[A]/2 downto 1
    //          do MAX-HEAPIFY(A,i)
    //-------------------------------------------------------------------
    static void buildMaxHeap(int[] arr){
        heapSize = arr.length;
        //heapSize/2  是最后一个有叶节点的根节点（找最后一个元素的父节点i/2）,构建最大堆的层次顺序是从下往上
        for(int i=arr.length/2;i>=0;i--){
            maxHeapify(arr,i);
        }

        //error
      /*  for(int i=0;i<=heapSize/2;i++){
            maxHeapify(arr,i);
        }*/
    }


    //-------------------------------------------------------------------
    //MAX-HEAPIFY(A,i)
    //    l<-LEFT(i)
    //    r<-RIGHT(i)
    //    if l<=heap-size[A] and A[l]>A[i]
    //       then largest<-l
    //       else largest<-i
    //    if r<=heap-size[A] and A[r]>A[largest]
    //        largest<-r
    //    if largest!=i
    //       then exchange A[i]<->A[largest]
    //            MAX-HEAPIFY(A,largest)
    //-------------------------------------------------------------------

    /**
     * immustabale loop body
     * create max heap
     * @param arr sorted array
     * @param i   index of arr
     */
    static void maxHeapify(int[] arr,int i){

        int largest = 0;
        int left = (i<<1)+1;
        int right = left+1;

        if(left<heapSize && arr[left]>arr[i]){
            largest = left;
        }else{
            largest = i;
        }

        if(right<heapSize && arr[right]>arr[largest]){
            largest = right;
        }


        if(largest!=i){
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            maxHeapify(arr,largest);
        }

    }

    static void print(int[] arr){

        for (int i=0;i<arr.length;i++){
            System.out.print(arr[i]+"  ");
        }
        System.out.println();
    }

}
