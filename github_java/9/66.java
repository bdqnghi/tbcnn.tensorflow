/*
 * Daniel Delago
 * Heap and Heap-Sort O(n lgn)
 */

package Data_Structures;
import java.util.*;

public class Heap {

    int[] heap;
    int heapSize = 0;

    public Heap(int n){
        heap = new int[n];
    }

    //Get the Parent of node at index i
    public int parent(int i) {
        return (i-1)/2;
    }

    //Get index of left child of node at index i
    public int left(int i) {
        return (2*i + 1);
    }

    //Get index of right child of node at index i
    public int right(int i) {
        return (2*i + 2);
    }

    /*** Inserting into a Max-Heap ***/
    public void insertMax(int k){

        //Increase the Heap Size by 1
        heapSize++;

        //i is last slot in the heap
        int i = heapSize-1;

        //Insert k into the last slot in the heap
        heap[i] = k;

        //While the new node is greater than its parent and not at the root
        //For min-heap change to >
        while(i!=0 && heap[parent(i)] < heap[i]){

            //Swap the values
            int temp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = temp;

            //Set i to the parent's index and continue swapping if needed
            i = parent(i);

        }
    }

    /*** Fixing a Max-Heap ***/
    public void MaxHeapify(int i){

        //Get index of left child
        int leftChild = left(i);

        //Get index of right child
        int rightChild = right(i);

        //Set Largest to current index
        int largest = i;

        //If left child is in the heap and greater then the current value
        if (leftChild < heapSize && heap[leftChild] > heap[i])
            largest = leftChild;

        //If right child is in the heap and greater then the current and/or the left child
        if (rightChild < heapSize && heap[rightChild] > heap[largest])
            largest = rightChild;

        //If one of the child's were larger
        if (largest != i)
        {
            //Swap the value with the larger child
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;

            //Fix the heap with the new position of the value
            MaxHeapify(largest);
        }
    }

    /*** Extracting the max/min value of a heap ***/
    public void extractMaxMin(){

        //Get the Max/Min value of the heap which is heap[0] (the root)
        int root = heap[0];

        //get the last(smallest/largest) value of the heap
        int last = heap[heapSize-1];

        //Place the max/min value outside of the heap, which is at the front of the output array
        heap[heapSize-1] = root;

        //Swap the root with the last value
        heap[0] = last;

        //Reduce size of the heap
        heapSize--;

        //Fix heap with the last value at the root
        //MaxHeapify(0);
        //    OR
        //MinHeapify(0);

    }

    /*** Inserting into a Min-Heap ***/
    public void insertMin(int k){

        //Increase the Heap Size by 1
        heapSize++;

        //i is last slot in the heap
        int i = heapSize-1;

        //Insert k into the last slot in the heap
        heap[i] = k;

        //While the new node is less than its parent and not at the root
        //For max-heap change to <
        while(i!=0 && heap[parent(i)] > heap[i]){

            //Swap the values
            int temp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = temp;

            //Set i to the parent's index and continue swapping if needed
            i = parent(i);

        }
    }

    /*** Fixing a Min-Heap ***/
    public void MinHeapify(int i){

        //Get index of left child
        int leftChild = left(i);

        //Get index of right child
        int rightChild = right(i);

        //Set Smallest to current index
        int smallest = i;

        //If left child is in the heap and smaller then the current value
        if (leftChild < heapSize && heap[leftChild] < heap[i])
            smallest = leftChild;

        //If right child is in the heap and smaller then the current and/or the left child
        if (rightChild < heapSize && heap[rightChild] < heap[smallest])
            smallest = rightChild;

        //If one of the child's were smaller
        if (smallest != i)
        {
            //Swap the value with the smaller child
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;

            //Fix the heap with the new position of the value
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


        /*** Heap-Sort on Max-Heap ***/
        for(int i=0;i<7;i++){
            maxHeap.extractMaxMin();
            maxHeap.MaxHeapify(0);
        }
        System.out.print("\nHeap Sort on Max-Heap ");
        System.out.println(Arrays.toString(maxHeap.heap));

        /*** Heap-Sort on Min-Heap ***/
        for(int i=0;i<7;i++){
            minHeap.extractMaxMin();
            minHeap.MinHeapify(0);
        }
        System.out.print("\nHeap Sort on Min-Heap ");
        System.out.println(Arrays.toString(minHeap.heap));

    }

}
