package algorithm_introduce;


import java.util.Comparator;


public class MinPriorityQueue<T> {

    private Object[] heap=new Object[100];;
    private HeapSort<Object> heapSort=new HeapSort<>();

    public MinPriorityQueue(Comparator< Object > comparator){
        heapSort.setComparator(comparator);
    }

    public void initial(T[] arrays){
        if (arrays.length>heap.length){
            incrementSize();
        }

        heapSort.heapSize=arrays.length;
        for (int i = 0; i < arrays.length; i++) {
            heap[i]=arrays[i];
        }


        heapSort.buidMinHeap(heap,heapSort.heapSize);
    }

    
    private void incrementSize(){
        Object[] oldheap= heap;
        int newSize = (int)(heap.length*1.5);
        heap =new Object[newSize];
        for (int i = 0; i < heapSort.heapSize; i++) {
            heap[i]=oldheap[i];
        }
    }

    public T getMin(){
        if (heapSort.heapSize<=0) return null;

        T min = (T)heap[0];

        heap[0] =heap[heapSort.heapSize-1];
        heapSort.heapSize--;
        heapSort.minHeapify(heap,1);
        return min;
    }

    public void insert(T value){
        if (heapSort.heapSize==heap.length){
            incrementSize();
        }
        heap[heapSort.heapSize++]=value;

        for (int i=heapSort.heapSize/2;i>=1;i--){
            heapSort.minHeapify(heap,i);
        }
    }



}
