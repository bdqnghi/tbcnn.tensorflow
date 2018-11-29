package sorting;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class MinHeapSort {
    
    public static void main(String[] args) {
        
        int size = 100000;
        int[] arr = new int[size];
        
        Random rand = new Random();
        for(int i = 0; i < size; i++) 
            arr[i] = rand.nextInt(10*size);
        
        // sort using methods
        int[] copyOf = Arrays.copyOf(arr, arr.length);
        Arrays.sort(copyOf);
        
        // sort using heap
        MinHeapSort minHeap = new MinHeapSort();
        for(int i = 0; i < size; i++) 
            minHeap.add(arr[i]);
        for(int i = 0; i < size; i++) 
            arr[i] = minHeap.removeMin();
        
        // verify that the two results are equal
        for(int i = 0; i < size; i++) 
            if(arr[i] != copyOf[i]) {
                System.out.println("arr:" + Arrays.toString(arr));
                throw new IllegalStateException("Not equal for i:" + i + " arr val:" + arr[i] + " copyOfVal:" + copyOf[i]);
            }
        
        System.out.println("good result.");
    }
    
    List<Integer> heap = new ArrayList<Integer>();
    
    
    public int removeMin() {
        if(this.heap == null || this.heap.size() == 0) throw new IllegalStateException();
        
        int toReturn = this.heap.get(0);
        
        // swap and and the current element.
        swap(0, this.heap.size()-1);
        
        // remove the last element
        this.heap.remove(this.heap.size()-1);
        
        // heapify down, i.e move this guy as far down as possible. 
        this.heapifyDown(0);
        
        return toReturn;
    }
    private void heapifyDown(int parentIndex) {
        if(parentIndex < 0 || parentIndex >= this.heap.size()) return;
        
        int childIndex1 = parentIndex * 2 + 1;
        int childIndex2 = parentIndex * 2 + 2;
        
        
        
        if(childIndex1 < this.heap.size() && this.heap.get(childIndex1) < this.heap.get(parentIndex) && 
                (childIndex2 >= this.heap.size() || this.heap.get(childIndex1) <= this.heap.get(childIndex2))) {
            this.swap(childIndex1, parentIndex);
            heapifyDown(childIndex1);
        } 
        else if(childIndex2 < this.heap.size() && this.heap.get(childIndex2) < this.heap.get(parentIndex) && this.heap.get(childIndex2) <= this.heap.get(childIndex1)) {
            this.swap(childIndex2, parentIndex);
            heapifyDown(childIndex2);
        }
    }
    
    public void add(int toAdd) {
        // updates the size automatically.
        heap.add(toAdd);
        heapifyUp(heap.size()-1);
    }

    /**
     * Heapifies up from the given index.
     * @param index
     */
    private void heapifyUp(int index) {
        if(index == 0) return;
        
        // get parent value.
        int parentIndex = (index-1)/2;
        int parentVal = heap.get(parentIndex);
        int childVal = heap.get(index);
        
        if(parentVal > childVal) {
            swap(parentIndex, index);
            heapifyUp(parentIndex);
        }
    }

    private void swap(int i, int j) {
        int temp = this.heap.get(i);
        this.heap.set(i, this.heap.get(j));
        this.heap.set(j, temp);
    }

}
