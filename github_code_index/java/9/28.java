/**
 * Class for implementing heapsort algorithm.
 *
 */
public class Heapsort {
	
	/**
	 * Method for using heapsort algorithm to arrange elements in an array to increasing order.
	 * Takes an input array as a parameter and sorts it.
	 * @param inputArr
	 */
    public static void heapsort (int inputArr[]) {
        int length = inputArr.length;
 
        //First the algorithm will build the heap, the arrays is rearranged to implement this.
        //The heapify -method is called to make sure the heap is a maximum heap.
        for (int i = length / 2 - 1; i >= 0; i--) {
            heapify(inputArr, length, i);
        }
 
        //Then take each element one by one and remove them from the heap.
        //The removed element will take the first place in the array.
        //Call heapify -method after each removal to make sure the heap is still a maximum heap.
        for (int i = length - 1; i >= 0; i--) {
            int tmp = inputArr[0];
            inputArr[0] = inputArr[i];
            inputArr[i] = tmp;
            heapify(inputArr, i, 0);
        }
    }
 
    /**
     * Method to heapify a subtree.
     * @param inputArr The subtree as an array.
     * @param heapSize The size of the heap.
     * @param node The subtree's current root node.
     */
    private static void heapify (int inputArr[], int heapSize, int node) {
    	
        int max = node;  				//The maximum value is now the root of the tree
        int leftChild = 2 * node + 1;  	//Left child of the root node = 2 * i + 1
        int rightChild = 2 * node + 2;  	//Right child of the root node = 2 * i + 2
 
        //Check if left child has a greater value than the root node.
        //If so, left child becomes the maximum.
        if (leftChild < heapSize && inputArr[leftChild] > inputArr[max]) {
        	max = leftChild;
        }
 
        //Check if right child has a greater value than the current maximum node.
        //If so, right child becomes the maximum.
        if (rightChild < heapSize && inputArr[rightChild] > inputArr[max]) {
        	max = rightChild;
        }
 
        //If root is not the greatest, the heap is not a maximum heap and it needs to be fixed:
        //Heapify will call itself recursively for all its subtrees until the whole tree is a maximum heap.
        if (max != node) {
        	int swap = inputArr[node];
            inputArr[node] = inputArr[max];
            inputArr[max] = swap;
            heapify(inputArr, heapSize, max);
        }
    }
}