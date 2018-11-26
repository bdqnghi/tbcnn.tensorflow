/**
* Sorts a sequence of items using shellsort.
*
* Shellsort is a generalization of insertion sort that allows the exchange of items that are 
* far apart. The idea is to arrange the list of elements so that, starting anywhere, considering 
* every hth element gives a sorted list. Such a list is said to be h-sorted. Equivalently, it can 
* be thought of as h interleaved lists, each individually sorted. Beginning with large values 
* of h, this rearrangement allows elements to move long distances in the original list, reducing 
* large amounts of disorder quickly, and leaving less work for smaller h-sort steps to do. If 
* the file is then k-sorted for some smaller integer k, then the file remains h-sorted. Following 
* this idea for a decreasing sequence of h values ending in 1 is guaranteed to leave a sorted list 
* in the end.
*
* Shellsort is similar to insertion sort; the idea is to move entries more than one position
* at a time by h-sorting the array. H-sorting is like insertion sort, but instead of going 1 
* back we go h back. Insertion sort is used as model because: big increments = small subarray
* and small increments are used when the array is nearly in order, which is good for the
* insertion sort algorithm. 
*
* We have to do a few extra passes to do the higher sorts, but each elements moves only a 
* little bit on each pass and that’s how shellsort gains its efficiency. The algorithm 
* eventually reaches 1-sort, which is like insertion sort but on a partially sorted array 
* thanks to the previous h-sorts. 
*
* The sequence used on this algorithm is 3x+1. It's used because it is easy to compute.
* Other sequences can be used. It's not known which sequence is the best. One sequence
* tough to beat in empirical studies is the Sedgewick sequence: 1, 5, 19, 41, 109, 209, 
* 505, 929, 2161, 3905, ...
*
* Shellsort is specially interesting because it is an example of a simple idea leading to 
* substantial performance gains. It's very useful in practice: 1) Fast unless array size
* is huge 2) Tiny, fixed footprint for code (used in embedded systems, because there is
* so little code) 3) Hardware sort prototype.
*  
* Performance:
* The analysis of shellsort is still open. There's a few thinggs we can say:
* Worst-case number of compares with 3x+1 increments is O(n^3/2). In practice it's much less
* than that. The problem is that nobody knows an accurate model for describing the number of 
* compares taken by shellsort. 
*
* Demo:
* You can see an animation of this sorting algorithm at: www.sorting-algorithms.com/shell-sort
*/
public class Shell{
    
    // =================================================
    //                   The Algorithm
    // =================================================

    /**
    * Shell sort algorithm.
    * @param a The array to be sorted.
    */
    public static void sort(Comparable[] a){
        int N = a.length;               // length of the array
        int h = 1;                      // Will be highest sequence value in next line:
        while(h < N / 3) h = 3*h + 1;   // 3x+1 increment sequence: 1, 4, 13, 40, 121...
        while(h >= 1){                  // sort the array
            for(int i = h; i < N; i++){
                // insertion sort, but the decrements are in h
                for(int j = i; j >= h && less(a[j], a[j - h]); j-= h)
                    exch(a, j, j - h);
            } 
            h = h / 3;                  // move to next increment
        }                              
    }
    
    // =================================================
    //                 Helper Methods
    // =================================================
    
    /**
    * Is v less than w?
    * @param v Item to be compared to.
    * @param w Item to be compared.
    */
    public static boolean less(Comparable v, Comparable w)
    {    return v.compareTo(w) < 0; }
    
    /**
    * Swaps two items in an array.
    * @param i Index of item to be swaped.
    * @param j Index of item to be swaped.
    * @param a Array where the items will be swaped.
    */
    private static void exch(Comparable[] a, int i, int j){
        Comparable swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
}