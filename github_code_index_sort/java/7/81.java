/*
ShellSort
ShellSort is mainly a variation of Insertion Sort. In insertion sort, we move elements only one position ahead.
When an element has to be moved far ahead, many movements are involved. The idea of shellSort is to allow exchange of far items. 
In shellSort, we make the array h-sorted for a large value of h. We keep reducing the value of h until it becomes 1. 
An array is said to be h-sorted if all sublists of every h’th element is sorted.
*/

// Java implementation of ShellSort
class ShellSort
{
    /* An utility function to print array of size n*/
    static void printArray(int arr[])
    {
        int n = arr.length;
        for (int i=0; i<n; ++i)
            System.out.print(arr[i] + " ");
        System.out.println();
    }
 
    /* function to sort arr using shellSort */
    int sort(int arr[])
    {
        int n = arr.length;
 
        // Start with a big gap, then reduce the gap
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already
            // in gapped order keep adding one more element
            // until the entire array is gap sorted
            for (int i = gap; i < n; i += 1)
            {
                // add a[i] to the elements that have been gap
                // sorted save a[i] in temp and make a hole at
                // position i
                int temp = arr[i];
 
                // shift earlier gap-sorted elements up until
                // the correct location for a[i] is found
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
 
                // put temp (the original a[i]) in its correct
                // location
                arr[j] = temp;
            }
        }
        return 0;
    }
 
    // Driver method
    public static void main(String args[])
    {
        int arr[] = {12, 34, 54, 2, 3};
        System.out.println("Array before sorting");
        printArray(arr);
 
        ShellSort ob = new ShellSort();
        ob.sort(arr);
 
        System.out.println("Array after sorting");
        printArray(arr);
    }
} 
/*
Output:
Array before sorting:
12 34 54 2 3
Array after sorting:
2 3 12 34 54
*/

V.IMP:- complexity analysis of shell sort
https://stackoverflow.com/questions/12767588/time-complexity-for-shell-sort?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
The worst-case of your implementation is Θ(n^2) and the best-case is O(nlogn) which is reasonable for shell-sort.

##The best case ∊ O(nlogn):
The best-case is when the array is already sorted. The would mean that the inner if statement will never be true, 
making the inner while loop a constant time operation. Using the bounds you've used for the other loops gives O(nlogn).
The best case of O(n) is reached by using a constant number of increments.

##The worst case ∊ O(n^2):
Given your upper bound for each loop you get O((log n)n^2) for the worst-case. But add another variable for the gap size g.
The number of compare/exchanges needed in the inner while is now <= n/g. The number of compare/exchanges of the middle 
while is <= n^2/g. 
Add the upper-bound of the number of compare/exchanges for each gap together: n^2 + n^2/2 + n^2/4 + ... <= 2n^2 ∊ O(n^2).
This matches the known worst-case complexity for the gaps you've used.

The worst case ∊ Ω(n^2):

Consider the array where all the even positioned elements are greater than the median.The odd and even elements are not 
compared until we reach the last increment of 1. The number of compare/exchanges needed for the last iteration is Ω(n^2).
