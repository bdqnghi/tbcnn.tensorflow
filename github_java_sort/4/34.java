import java.time.*;

class heapsort {

    public static void main(String[] args) 
    {
        tester(1000);
        tester(1000000);
        tester(10000000);
        tester(100000000);
        tester(1000000000);
    }

    private static double[] makeRandom(int n) 
    {
        double[] toBeSorted = new double[n+1];
        for(int k = 1; k < toBeSorted.length; k++)	
            toBeSorted[k] = Math.random() * (n); 
        return toBeSorted;
    }

    private static void sort(double[] A) 
    {
        buildHeap(A);
        for(int k = A.length; k > 1; k--)
        {
        	heapify(A, 1, k);
        	swap(A,1,k-1);
        }    
	}

    private static void buildHeap(double[] A) 
    {
        for(int k = A.length/2; k >0; k--)
        {
            heapify(A, k, A.length); 
        }
    }

    private static void heapify(double[] A, int k, int index) 
    
    {
        int lchild = 2*k; 
        int rchild = 2*k+1;
        int max;
        if((lchild < index) && (A[lchild]>A[k])) 
        {
        	max = lchild;
        } else {
        	max = k;
        }
        if(rchild < index && A[rchild]>A[max]) 
           	max = rchild;
        if(max != k) 
        {
        	swap(A,max,k);
        	heapify(A, max, index);
        }
    }

    private static boolean isSorted(double[] A) 
    
    {
        for(int k = 1; k < A.length; k++)
        {
            if(A[k]<A[k-1])
                return false;
        }
        return true;
    }

    private static void swap(double[] A, int p, int q) 
    {
        double temp = A[p];
        A[p] = A[q];
        A[q] = temp;
    }

    private static int tester(int n) 
    {
        double[] test = makeRandom(n);  
        long startTime = System.currentTimeMillis(); 
        sort(test);
        long endTime = System.currentTimeMillis();
        long timeElapsed = endTime-startTime;
        if(!isSorted(test)) 
        {
            System.out.println("Sort failed");
        	return 1;
        }
        System.out.println("Sorting of "+n+" integers completed successfully in " +timeElapsed+ " milliseconds");
        
        return 0;
    }
}
