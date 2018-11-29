
//          bucketsort works as follows: The minimum and maximum of the 
//          range of numbers is found.  Then an array of "buckets" is 
//          allocated for each integral value between the minimum and
//          maximum inclusive.  The number of each value in the original
//          array is counted by one pass over the latter, using the datum
//          as an index into the bucket array.
//
//          This method is O(N) where N is the number of elements to be sorted;
//          a prime example of the use of the linear-addressing principle.
//
//          If the range of numbers is to large, the bucket array can't be
//          allocated and the method will fail.

public void bucketsort(int array[], int N) {
    if( N <= 0 )
      return;                                   // Case of empty array

    int min = array[0];
    int max = min;
    for( int i = 1; i < N; i++ )                // Find the minimum and maximum
      if( array[i] > max )
        max = array[i];
      else if( array[i] < min )
        min = array[i];

    int bucket[] = new int[max-min+1];          // Create buckets
    
    for( int i = 0; i < N; i++ )                // "Fill" buckets
      bucket[array[i]-min]++;                   // by counting each datum

    int i = 0;                                  
    for( int b = 0; b < bucket.length; b++ )    // "Empty" buckets
      for( int j = 0; j < bucket[b]; j++ )      // back into array
        array[i++] = b + min;                     // by creating one per count
}

public static void sort(int[] a, int maxVal) {
    int [] bucket=new int[maxVal+1];
 
    for (int i=0; i<bucket.length; i++) {
         bucket[i]=0;
    }
 
    for (int i=0; i<a.length; i++) {
         bucket[a[i]]++;
    }
 
    int outPos=0;
    for (int i=0; i<bucket.length; i++) {
        for (int j=0; j<bucket[i]; j++) {
           a[outPos++]=i;
        }
    }
}










