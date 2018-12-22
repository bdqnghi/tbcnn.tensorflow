

/** Shell sort */

package applications;

import utilities.*;

public class ShellSort
{
   /** sort the elements a[0 : a.length - 1] using
     * the shaker sort method */
   public static void shellSort(Comparable [] a)
   {
      int incr = a.length / 2;  // initial increment
      while (incr >= 1)
      {// insertion sort all sequences spaced by incr
         for (int i = incr; i < a.length; i++)
         {// insert a[i] into a[i - incr], a[i - 2*incr], ...
            Comparable insertElement = a[i];
            int j;
            for (j = i - incr;
                 j >= 0 && insertElement.compareTo(a[j]) < 0;
                 j -= incr)
               a[j + incr] = a[j];
            a[j + incr] = insertElement;
         }
   
         // reduce increment by a factor of 2.2
         if (incr == 2)
            incr = 1;  // last increment must be 1
         else
            incr = (int) (incr / 2.2);
      }
   }
   
   /** test program */
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

      // output elements to be sorted
      System.out.println("The elements are");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + " ");
      System.out.println();

      // sort the elements
      shellSort(a);

      // output in sorted order
      System.out.println("The sorted order is");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + " ");
      System.out.println();
   }
}

