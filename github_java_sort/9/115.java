package sort;

import static v.ArrayUtils.*;
import static java.lang.reflect.Array.*;
import static java.lang.System.*;
import java.awt.Color;
import java.awt.Font;
import java.util.Arrays;
import java.util.Comparator;

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;



@SuppressWarnings("unused")
public class Selection {

  public static int writes = 0;
  public static double exchanges = 0;
  public static int compares = 0;

  
  public static final Color FIREBRICK = new Color(178, 34, 34);


  public static <T extends Comparable<? super T>> int sort(T[] a) { 
    
    writes = 0;
    int N = a.length; 
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (less(a[j], a[min])) min = j;
      exch(a, i, min);
    }
    return writes;
  }

  public static int sort(Object[] a, Comparator<Object> c) { 
    
    writes = 0;
    int N = a.length; 
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (less(a[j], a[min], c)) min = j;
      exch(a, i, min);
    }
    return writes;
  }

  
  public static <T extends Comparable<? super T>> double[] selectionTestHypo2128(T[] a) { 
    
    compares = 0; exchanges = 0;
    int N = a.length; 
    
    
    for (int i = 0; i < N; i++) { 
      
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (less(a[j], a[min])) {
          min = j;
        }
      exch(a, i, min);
      
      
      
    }
    
    
    
    return new double[]{exchanges,compares};
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  
  public static <T extends Comparable<? super T>> int visualSort(T[] a) { 
    
    if (Number.class.isAssignableFrom(a.getClass().getComponentType()))
      return numberSort((Number[]) a);
    writes = 0;
    int N = a.length; 
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (less(a[j], a[min])) min = j;
      exch(a, i, min);
    }
    return writes;
  }

  
  public static int numberSort(Number[] a) { 
    
    writes = 0;
    int N = a.length; 
    double[] z = new double[a.length];
    for (int i = 1; i < N; i++) z[i] = a[i].doubleValue();
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (z[j] < z[min]) min = j;
      exch(z, i, min);
      visualShow(z);
    }
    return writes;
  }

  
  public static <T extends Comparable<? super T>> int visualSort2(T[] a) { 
    
    if (Number.class.isAssignableFrom(a.getClass().getComponentType()))
      return numberSort2((Number[]) a);
    writes = 0;
    int N = a.length; 
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (less(a[j], a[min])) min = j;
      exch(a, i, min);
    }
    return writes;
  }

  
  public static int numberSort2(Number[] a) { 
    
    writes = 0;
    int N = a.length; 
    double[] z = new double[a.length];
    initializeVisual2(z);
    for (int i = 1; i < N; i++) z[i] = a[i].doubleValue();
    for (int i = 0; i < N; i++) { 
      
      int min = i; 
      for (int j = i+1; j < N; j++)
        if (z[j] < z[min]) min = j;
      exch(z, i, min);
      visualShow2(z,i,min);
    }
    return writes;
  }

  
  
  
  
  
  
  
  
  
  
  
  


  private static <T extends Comparable<? super T>> boolean less(T v, T w) { 
    compares++;
    return v.compareTo(w) < 0; 
  }

  private static boolean less(Object v, Object w, Comparator<Object> c) { 
    compares++;
    return c.compare(v, w) < 0; 
  }

  private static <T extends Comparable<? super T>> void exch(T[] a, int i, int j) {
    T t = a[i]; a[i] = a[j]; a[j] = t;
    writes++; exchanges++;
  }

  private static void exch(Object[] a, int i, int j) {
    Object t = a[i]; a[i] = a[j]; a[j] = t;
    writes++; exchanges++;
  }

  private static void exch(double[] a, int i, int j) { 
    double t = a[i]; a[i] = a[j]; a[j] = t;
    writes++; exchanges++;
  }

  public static <T extends Comparable<? super T>> boolean isSorted(T[] a) { 
    
    for (int i = 1; i < a.length; i++)
      if (less(a[i], a[i-1])) return false;
    return true;
  }

  public static boolean isSorted(Object[] a, Comparator<Object> c) { 
    
    for (int i = 1; i < a.length; i++)
      if (c.compare(a[i], a[i-1]) < 0) return false;
    return true;
  }

  public static <T extends Comparable<? super T>> void show(T[] a) { 
    
    for (int i = 0; i < a.length; i++)
      System.out.print(a[i] + " ");
    System.out.println();
  }

  public static void showObjectArray(Object[] a) { 
    
    for (int i = 0; i < a.length; i++) {
      if (a[i].getClass().isArray()) {
        if (getLength(a[i]) > 1) {
          System.out.print(arrayToString(a[i],10000,1,1)
              .replaceAll(",.*,", ",...,")+" ");
        } else {
          System.out.print(arrayToString(a[i],10000,1,1)+" ");
        }
      } else System.out.print(a[i] + " ");
    }
    System.out.println();
  }

  
  private static void visualShow(double[] a) {
    
    int max = (int) Math.ceil(max(a));
    int n = a.length;
    StdDraw.setXscale(0, n);
    StdDraw.setYscale(0, max);
    StdDraw.setPenColor(StdDraw.BLACK);
    StdDraw.setPenRadius(.002);
    Font font = new Font("Arial", Font.BOLD, 16);
    StdDraw.setFont(font);
    StdDraw.clear();
    for (int k = 0; k < a.length; k++) {
      StdDraw.line(k, 0, k, a[k]);
    }
    StdDraw.textLeft(1.*n/10, 1.*max*7/9, "Selection Sort");

    StdDraw.show();
    StdDraw.show(10);
  }

  
  
  private static void initializeVisual2(double[] a) {
    int n = a.length;
    StdDraw.setCanvasSize(200, 900);
    StdDraw.setXscale(-1, n+1);
    Font font = new Font("SansSerif", Font.PLAIN, 20);
    StdDraw.setFont(font);
    StdDraw.setPenRadius(0.006);
  }

  
  
  private static void visualShow2(double[] a, int i, int min) {
    StdDraw.setYscale(-a.length + i + 1, i+1.5);
    StdDraw.setPenColor(StdDraw.BLACK);
    StdDraw.textLeft(1.5*a.length/10, i+1, "Selection Sort");
    StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
    for (int k = 0; k < i; k++) StdDraw.line(k, 0, k, a[k]*0.5);
    StdDraw.setPenColor(StdDraw.BLACK);
    for (int k = i; k < a.length; k++) StdDraw.line(k, 0, k, a[k]*0.5);
    StdDraw.setPenColor(FIREBRICK);
    StdDraw.line(min, 0, min, a[min]*0.5);
  }




  public static void main(String[] args) {


    
    
    
    
    
    
    

  }

}
