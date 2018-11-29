/**
参见《算法》P205-P209
*/

public class Sort_HeapSort<Key extends  Comparable<Key>>  {


    private boolean less(Comparable a[], int i, int j){
        return a[i].compareTo(a[j]) < 0;
    }

    private void exch(Comparable a[], int i, int j){
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    /**
     * 下沉(sink)
     * @param k
     */
    private void sink(Comparable a[], int k, int N){
        while(2*k <= N){
            int j = 2*k;
            if(j < N && less(a, j,j+1))
                j++;
            if(!less(a, k,j))
                break;
            exch(a, k,j );
            k=j;
        }
    }


    /*
    堆排序
     */
    public void sort(Comparable a[]){
        int N = a.length;
        for(int k=N/2; k>=1; k--)  //构建堆
        {
            sink(a, k, N);
        }

        while(N>1){
            exch(a, 1, N--);  //将最大与最小交换，会导致堆平衡被破坏
            sink(a, 1, N);  // 修复堆
        }

    }
}
