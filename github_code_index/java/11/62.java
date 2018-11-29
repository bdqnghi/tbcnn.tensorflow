//https://www.youtube.com/watch?v=YXFI4osELGU
//http://www.thecrazyprogrammer.com/2015/06/radix-sort-java-program-and-algorithm.html
//http://www.geeksforgeeks.org/radix-sort/
//Average, best, worst case all O(kn) where k is the number of digits
//and space complexity is O(n + k)
    static void sort( int[] a)
    {
        int i, m = a[0], exp = 1, n = a.length;
        int[] b = new int[10];
        for (i = 1; i < n; i++)
            if (a[i] > m)
                m = a[i];
        while (m / exp > 0)
        {
            int[] bucket = new int[10];
 
            for (i = 0; i < n; i++)
                bucket[(a[i] / exp) % 10]++;
            for (i = 1; i < 10; i++)
                bucket[i] += bucket[i - 1];
            for (i = n - 1; i >= 0; i--)
                b[--bucket[(a[i] / exp) % 10]] = a[i];
            for (i = 0; i < n; i++)
                a[i] = b[i];
            exp *= 10;        
        }
    }    
