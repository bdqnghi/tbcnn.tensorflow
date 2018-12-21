

import java.util.Comparator;

public class Shell
{   
    public static void sort(Comparable[] a)
    {
        int N = a.length;
        
        int h = 1;
        
        
        while (h < N/3)
        {
            h = 3*h + 1;
        }
        
        while (h >= 1)
        {
            
            System.out.println(h);
            for (int i = h; i < N; i++)
            {
                for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
                {
                    exch(a, j, j-h);
                    print(a);
                }                   
            }

            h = h/3;
        }

    }
    
    private static boolean less(Comparable v, Comparable w)
    {
        return v.compareTo(w) < 0;
    }
    
    private static void exch(Comparable[] a, int i, int j)
    {
        Comparable swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
    
    public static void print(Comparable[] a)
    {
        StringBuilder temp = new StringBuilder();
        temp.append("");
        
        for (int i = 0; i < a.length; i++)
        {
            temp.append(a[i]);
            temp.append(" ");
        }
        String strI = temp.toString();
        System.out.println(strI);
    }
    
    public static void main(String[] args) 
    { 
        Integer[] intArray = {53,26,94,25,99,14,54,75,17,20};
 
        print(intArray);
        
        sort(intArray);
    }
}