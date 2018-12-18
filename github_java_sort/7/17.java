



package applications;

import utilities.*;

public class ShellSort
{
   
   public static void shellSort(Comparable [] a)
   {
      int incr = a.length / 2;  
      while (incr >= 1)
      {
         for (int i = incr; i < a.length; i++)
         {
            Comparable insertElement = a[i];
            int j;
            for (j = i - incr;
                 j >= 0 && insertElement.compareTo(a[j]) < 0;
                 j -= incr)
               a[j + incr] = a[j];
            a[j + incr] = insertElement;
         }
   
         
         if (incr == 2)
            incr = 1;  
         else
            incr = (int) (incr / 2.2);
      }
   }
   
   
   public static void main(String [] args)
   {
      Integer [] a = {new Integer(3),
                      new Integer(2),
                      new Integer(4),
                      new Integer(1),
                      new Integer(6),
                      new Integer(9),
                      new Integer(8),
                      new Integer(7),
                      new Integer(5),
                      new Integer(0)};

      
      System.out.println("The elements are");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + " ");
      System.out.println();

      
      shellSort(a);

      
      System.out.println("The sorted order is");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + " ");
      System.out.println();
   }
}

