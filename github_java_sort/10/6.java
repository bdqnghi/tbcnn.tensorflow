
import java.util.ArrayList;
import java.util.ArrayDeque;

public class Bucketsort {

    public static final int MAX_VALUE = 10000;
    public static final int MIN_VALUE = 0;

    public static int[] bucketsort(int[] vec , int nBuckets){
        
        int [] sortedVec = new int[vec.length];

        
        ArrayList<ArrayDeque<Integer>> buckets = new ArrayList<ArrayDeque<Integer>>(nBuckets);
        for(int i = 0; i < nBuckets; i++ ){
            buckets.add(new ArrayDeque<Integer>() );
        }

        
        for(Integer x: vec){
            buckets.get( chooseBucket(x, nBuckets) ).push(x);
        }

        
        int idx = 0;
        for(ArrayDeque<Integer> bucket: buckets){
            while( ! bucket.isEmpty() )
                sortedVec[idx++] = bucket.remove();
        }
        
        inplace_insertionSort(sortedVec);

        return sortedVec;
    }

    public static void inplace_insertionSort(int[] vec){
        int cmp_counter = 0;
        int swap_counter = 0;
        int tmp = 0;
        for(int i = 0; i < vec.length ; i++){
            cmp_counter++;
            for(int j  = i ; j >0 && (vec[j-1] > vec[j])  ; j-- ){
                cmp_counter++;
                if(vec[j-1] > vec[j] ){
                    swap_counter++;
                    tmp = vec[j-1];
                    vec[j-1] = vec[j];
                    vec[j] = tmp;
                }
            }
        }
        System.out.println("Insertion sort");
        System.out.println("# of comparisons "+Integer.toString(cmp_counter));
        System.out.println("# of swaps "+Integer.toString(swap_counter));
        System.out.println();
    }


    
    public static int chooseBucket(int value, int nBuckets){
        int bucketLimit = (MAX_VALUE-MIN_VALUE+1)/nBuckets;
        int bucket = (value - MIN_VALUE) / bucketLimit;
        
        if(bucket == nBuckets)
            bucket = nBuckets - 1;
        return bucket;
    }

    public static boolean isSorted(int [] vec){
        boolean sorted = true;
        int i;
        for( i = 1; i< vec.length && sorted;i++){
            sorted = vec[i-1] <= vec[i];

        }
        return sorted;
    }

    
    public static void main(String[] args) {

        int nBuckets = 50;

        int[] vec = new int[100];
        for(int i = 0;i<100; i++){
            vec[i] = (int)(Math.random() * 10000);
        }
        System.out.println("Bucket sort for normal array");
        int[] vec_sorted = bucketsort(vec, nBuckets);

        for(Integer x: vec_sorted){
            System.out.print(Integer.toString(x)+" ");
        }
        System.out.println("\nSorted: "+Boolean.toString(isSorted(vec_sorted)));

        System.out.println();
        System.out.println("Insertion sort for normal array");
        inplace_insertionSort(vec);
        for(Integer x: vec){
            System.out.print(Integer.toString(x)+" ");
        }


    }

}
