

package Data_Structures;
import java.util.*;

public class Heap {

    int[] heap;
    int heapSize = 0;

    public Heap(int n){
        heap = new int[n];
    }

    
    public int parent(int i) {
        return (i-1)/2;
    }

    
    public int left(int i) {
        return (2*i + 1);
    }

    
    public int right(int i) {
        return (2*i + 2);
    }

    
    public void insertMax(int k){

        
        heapSize++;

        
        int i = heapSize-1;

        
        heap[i] = k;

        
        
        while(i!=0 && heap[parent(i)] < heap[i]){

            
            int temp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = temp;

            
            i = parent(i);

        }
    }

    
    public void MaxHeapify(int i){

        
        int leftChild = left(i);

        
        int rightChild = right(i);

        
        int largest = i;

        
        if (leftChild < heapSize && heap[leftChild] > heap[i])
            largest = leftChild;

        
        if (rightChild < heapSize && heap[rightChild] > heap[largest])
            largest = rightChild;

        
        if (largest != i)
        {
            
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;

            
            MaxHeapify(largest);
        }
    }

    
    public void extractMaxMin(){

        
        int root = heap[0];

        
        int last = heap[heapSize-1];

        
        heap[heapSize-1] = root;

        
        heap[0] = last;

        
        heapSize--;

        
        
        
        

    }

    
    public void insertMin(int k){

        
        heapSize++;

        
        int i = heapSize-1;

        
        heap[i] = k;

        
        
        while(i!=0 && heap[parent(i)] > heap[i]){

            
            int temp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = temp;

            
            i = parent(i);

        }
    }

    
    public void MinHeapify(int i){

        
        int leftChild = left(i);

        
        int rightChild = right(i);

        
        int smallest = i;

        
        if (leftChild < heapSize && heap[leftChild] < heap[i])
            smallest = leftChild;

        
        if (rightChild < heapSize && heap[rightChild] < heap[smallest])
            smallest = rightChild;

        
        if (smallest != i)
        {
            
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;

            
            MinHeapify(smallest);
        }
    }

    public static void main(String args[]){

        Heap maxHeap = new Heap(7);
        maxHeap.insertMax(4);
        maxHeap.insertMax(3);
        maxHeap.insertMax(6);
        maxHeap.insertMax(5);
        maxHeap.insertMax(7);
        maxHeap.insertMax(2);
        maxHeap.insertMax(1);

        Heap minHeap = new Heap(7);
        minHeap.insertMin(4);
        minHeap.insertMin(3);
        minHeap.insertMin(6);
        minHeap.insertMin(5);
        minHeap.insertMin(7);
        minHeap.insertMin(2);
        minHeap.insertMin(1);

        System.out.print("Max-Heap after Insertions: ");
        System.out.println(Arrays.toString(maxHeap.heap));

        System.out.print("Min-Heap after Insertions: ");
        System.out.println(Arrays.toString(minHeap.heap));


        
        for(int i=0;i<7;i++){
            maxHeap.extractMaxMin();
            maxHeap.MaxHeapify(0);
        }
        System.out.print("\nHeap Sort on Max-Heap ");
        System.out.println(Arrays.toString(maxHeap.heap));

        
        for(int i=0;i<7;i++){
            minHeap.extractMaxMin();
            minHeap.MinHeapify(0);
        }
        System.out.print("\nHeap Sort on Min-Heap ");
        System.out.println(Arrays.toString(minHeap.heap));

    }

}
