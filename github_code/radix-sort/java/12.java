
package sorting;

// Radix sort Java implementation
import java.io.*;
import java.util.*;
 
class Radix {
 
    // A utility function to get maximum value in arr[]
    static int getMax(int arr[], int n)
    {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }
 
    // A function to do counting sort of arr[] according to
    // the digit represented by exp.
    static void countSort(int arr[], int n, int exp)
    {
        //System.out.println("");
        int output[] = new int[n]; // output array
        int i;
        int count[] = new int[10];
//       
//       
//        for(int j=0;j<count.length;j++)
//        {
//            System.out.print(count[j] + " ");
//        }
        // Store count of occurrences in count[]
        for (i = 0; i < n; i++)
        {
//            System.out.println("last " + (arr[i]/exp)%10 );
            count[ (arr[i]/exp)%10 ]++;
        }
 
        // Change count[i] so that count[i] now contains
        // actual position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
 
        // Build the output array
      //  for (i = n - 1; i >= 0; i--)
        for (i = 0; i <n; i++)
        {
            output[--count[ (arr[i]/exp)%10 ]] = arr[i];
        }
 
        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to curent digit
        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }
 
    // The main function to that sorts arr[] of size n using
    // Radix Sort
    static void radixsort(int arr[], int n)
    {
        // Find the maximum number to know number of digits
        print(arr, n);
        reduceBy1(arr, n);
        int m = getMax(arr, n);
        
        // Do counting sort for every digit. Note that instead
        // of passing digit number, exp is passed. exp is 10^i
        // where i is current digit number
        for (int exp = 1; m/exp > 0; exp *= 10)
        {
            System.out.println("exp :: " + exp);
            countSort(arr, n, exp);
              print(arr, n);
              System.out.println("--");
        }
         increaseBy1(arr, n);
    }
 
    // A utility function to print an array
    static void print(int arr[], int n)
    {
        for (int i=0; i<n; i++)
        {
            System.out.print(arr[i]+" ");
        }
    }
    
     static void reduceBy1(int arr[], int n)
    {
        for (int i=0; i<n; i++)
        {
            arr[i]--;
        }
    }
     
     static void increaseBy1(int arr[], int n)
    {
        for (int i=0; i<n; i++)
        {
            arr[i]++;
        }
    }
 
 
    /*Driver function to check for above function*/
    public static void main (String[] args)
    {
        int arr[] = {40, 12, 45, 32, 33, 1, 22, 99, 98,100 };
        int n = arr.length;
        radixsort(arr, n);
        print(arr, n);
    }
}