import java.time.*;

class heapsort {

    public static void main(String[] args) //main method that calls our tester
    {
        tester(1000);
        tester(1000000);
        tester(10000000);
        tester(100000000);
        tester(1000000000);
    }

    private static double[] makeRandom(int n) //makeRandom generates our random doubles array of size n+1, index 0 empty
    {
        double[] toBeSorted = new double[n+1];
        for(int k = 1; k < toBeSorted.length; k++)	
            toBeSorted[k] = Math.random() * (n); //multiplied by n so our numbers are spaced apart some more
        return toBeSorted;
    }

    private static void sort(double[] A) //our actual heapsort call, contains buildHeap, heapify, and removeMax.
    {
        buildHeap(A);
        for(int k = A.length; k > 1; k--)
        {
        	heapify(A, 1, k);
        	swap(A,1,k-1);
        }    
	}

    private static void buildHeap(double[] A) //Turns our random generated array into a heap
    {
        for(int k = A.length/2; k >0; k--)
        {
            heapify(A, k, A.length); //call heapify on all elements from index/2 all the way to top element to ensure heap property.
        }
    }

    private static void heapify(double[] A, int k, int index) //heapify checks left and right child.
    //essentially swaps our newest value down the heap until we've re-satisfied the heap property.
    {
        int lchild = 2*k; //indices of left and right child of the current index k
        int rchild = 2*k+1;
        int max;
        if((lchild < index) && (A[lchild]>A[k])) //make sure that left child actually exists, otherwise we should get out of heapify
        {
        	max = lchild;
        } else {
        	max = k;
        }
        if(rchild < index && A[rchild]>A[max]) //check if right child exists, compare to the current max value's index
           	max = rchild;
        if(max != k) //perform swaps and recursive calls if we aren't done and we need to move k down the heap
        {
        	swap(A,max,k);
        	heapify(A, max, index);
        }
    }

    private static boolean isSorted(double[] A) //simple check to see if array is sorted
    //strictly less than is enforced because we have a very small chance (read:0) of 2 random doubles being equal
    {
        for(int k = 1; k < A.length; k++)
        {
            if(A[k]<A[k-1])
                return false;
        }
        return true;
    }

    private static void swap(double[] A, int p, int q) //simple swap function
    {
        double temp = A[p];
        A[p] = A[q];
        A[q] = temp;
    }

    private static int tester(int n) //tester method on Heapsort
    {
        double[] test = makeRandom(n);  //create random array
        long startTime = System.currentTimeMillis(); //stuff used for timing the sort
        sort(test);
        long endTime = System.currentTimeMillis();
        long timeElapsed = endTime-startTime;
        if(!isSorted(test)) //check if sorted, print error message if failed
        {
            System.out.println("Sort failed");
        	return 1;
        }
        System.out.println("Sorting of "+n+" integers completed successfully in " +timeElapsed+ " milliseconds");
        //if sort is sucessful, print a success statement and time taken.
        return 0;
    }
}
