import java.io.*;
import java.util.*;
 
public class radixsort {
 
	
    static String getMax(String arr[], int n)
    {
        String mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i].charAt(0) > mx.charAt(0))
                mx = arr[i];
        return mx;
    }
 
    static void countingsort(String arr[], int n, int exp)
    {
        String output[] = new String[n]; 
        int i;
        int count[] = new int[arr.length];
        Arrays.fill(count, 0);
 
        
        for (i = 0; i < n; i++)
            count[ (arr[i].charAt(0)/exp)%10 ]++;
 
        
        for (i = 1; i < count.length; i++)
            count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--)
        {
            output[count[ (arr[i].charAt(0)/exp)%10 ] - 1] = arr[i];
            count[ (arr[i].charAt(0)/exp)%10 ]--;
        }
 
        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }
 
    
    static void radixsort(String arr[], int n)
    {
        
        String m = getMax(arr, n);
 
		
        for (int exp = 1; m.charAt(0)/exp > 0; exp *= 10)
            countingsort(arr, n, exp);
			
    }
 
	
    static void print(String arr[], int n)
    {
		System.out.println("Lista ordinata: ");
        for (int i=0; i<n; i++)
            System.out.print(arr[i]+" ");
		System.out.println();
    }
 
    public static void main (String[] args)
    {
        String arr[] = {"all", "bad", "zoo", "one", "car", "bug", "dad", "two", "lan", "yes", "sin", "yet"};
        int n = arr.length;
        radixsort(arr, n);
        print(arr, n);
    }
}