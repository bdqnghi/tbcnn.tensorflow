//http://www.growingwiththeweb.com/2015/06/bucket-sort.html
//The best/average complexity is O(n + k), when elements fairly distributed over the buckets
//the worst case is all elements are in a single bucket, and it needs another sorting algorithm to sort the bucket
//the worst one is O(n^2), so the worst case is O(n^2)
//the space complexity is O(n + k)
//the difference between bucket and counting sort, counting is to count the frequency in the bucket
//but bucket sort use buckets (as you want)to save the value directly or frequency
//it's comfusing here it's very similar with count sort, I will update it later
    public static void sort(int[] a, int maxVal){
        int [] bucket=new int[maxVal+1];
        for (int i=0; i<bucket.length; i++){
            bucket[i]=0;
        }
        for (int i=0; i<a.length; i++){
            bucket[a[i]]++;
        }
        int outPos=0;
        for (int i=0; i<bucket.length; i++){
            for (int j=0; j<bucket[i]; j++){
                a[outPos++]=i;
            }
        }
    }
