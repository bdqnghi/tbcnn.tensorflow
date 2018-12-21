package sort;

import static java.lang.Math.pow;
import static v.ArrayUtils.arrayToString;
import static v.ArrayUtils.max;
import static v.ArrayUtils.unbox;

import java.awt.Font;
import java.util.ArrayList;
import java.util.List;

import edu.princeton.cs.algs4.StdDraw;

@SuppressWarnings("unused")
public class Shell {
  
  public static int writes = 0;
  public static int compares = 0;
  
  public static  <T extends Comparable<? super T>> int sort(T[] a) { 
    
    writes = 0;
    int N = a.length;
    int h = 1;
    while (h < N/3) h = 3*h + 1; 
    while (h >= 1) { 
      for (int i = h; i < N; i++) { 
        for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
          exch(a, j, j-h);
      }
      h = h/3;
    }
    return writes;
  }
  
  public static  <T extends Comparable<? super T>> int[] sortMod(T[] a) { 
    
    writes = 0; compares = 0;
    int N = a.length;
    int h = 1;
    while (h < N/3) h = 3*h + 1; 
    while (h >= 1) { 
      for (int i = h; i < N; i++) { 
        for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
          exch(a, j, j-h);
      }
      h = h/3;
    }
    return new int[]{compares,writes};
  }

  public static  <T extends Comparable<? super T>> int visualSort(T[] a) { 
    
    if (Number.class.isAssignableFrom(a.getClass().getComponentType()))
      return numberSort((Number[]) a);
    writes = 0;
    int N = a.length;
    int h = 1;
    while (h < N/3) h = 3*h + 1; 
    while (h >= 1) { 
      for (int i = h; i < N; i++) { 
        for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
          exch(a, j, j-h);
      }
      h = h/3;
    }
    return writes;
  }
  
  public static <U extends Number> int numberSort(U[] a) { 
    
    writes = 0;
    int N = a.length;
    double[] z = new double[a.length];
    for (int i = 1; i < N; i++) z[i] = a[i].doubleValue();
    int h = 1;
    while (h < N/3) h = 3*h + 1; 
    while (h >= 1) { 
      for (int i = h; i < N; i++) { 
        for (int j = i; j >= h && z[j] < z[j-h]; j -= h) {
          doubleExch(z, j, j-h);
          visualShow(z);
        }
      }
      h = h/3;
    }
    return writes;
  }
  













  
  public static int[] createIncrementArray() {
    
    
    List<Integer> list = new ArrayList<>();
    int k = 0; long r = 0;
    list.add(1);
    
    while(true) {
      r = (long) (pow(4,k) + 3.*pow(2,k-1) + 1);
      if (r >= Integer.MAX_VALUE) break;
      if (r > 0) list.add((int)r);
      k++;
    }
    
    int[] z = (int[]) unbox(list.toArray(new Integer[0]));
    v.ArrayUtils.shellSort(z);
    return z;
  }
  
  public static  <T extends Comparable<? super T>> void shellSortWithIncrementArray(T[] a) { 
    
    int N = a.length;
    int k = 0;
    int h = 1;
    int[] increments = {1, 3, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913, 1050113, 
        4197377, 16783361, 67121153, 268460033, 1073790977};
    while (h < N/3) h = increments[++k];
    while (true) { 
      for (int i = h; i < N; i++) { 
        for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
          exch(a, j, j-h);
      }
      if (k == 0) {
        break;
      } else h = increments[--k];
    }
  }

  private static <T extends Comparable<? super T>> boolean less(T v, T w) {
    compares++;
    return v.compareTo(w) < 0;
  }

  private static <T extends Comparable<? super T>> void exch(T[] a, int i, int j) { 
    T t = a[i]; a[i] = a[j]; a[j] = t;
    writes++;
  }
  
  private static void doubleExch(double[] a, int i, int j) { 
    double t = a[i]; a[i] = a[j]; a[j] = t;
    writes++;
  }




  
  public static <T extends Comparable<? super T>> boolean isSorted(T[] a) { 
    
    for (int i = 1; i < a.length; i++)
      if (less(a[i], a[i-1])) return false;
    return true;
  }

  private static <T extends Comparable<? super T>> void show(T[] a) { 
    
    for (int i = 0; i < a.length; i++)
      System.out.print(a[i] + " ");
    System.out.println();
  }
  
  private static void visualShow(double[] a) {
    
    int max = (int) Math.ceil(max(a));
    int n = a.length;
    StdDraw.setXscale(0, n);
    StdDraw.setYscale(0, max);
    StdDraw.setPenColor(StdDraw.BLACK);
    StdDraw.setPenRadius(.004);
    Font font = new Font("Arial", Font.BOLD, 16);
    StdDraw.setFont(font);
    StdDraw.clear();
    for (int k = 0; k < a.length; k++) {
      StdDraw.line(k, 0, k, a[k]);
    }
    StdDraw.textLeft(1.*n/10, 1.*max*7/9, "Shell Sort");
    StdDraw.show();
    StdDraw.show(1);
  }

  public static void main(String[] args) {

  }

}
