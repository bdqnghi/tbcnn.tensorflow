
package selectionsortjava;
import java.util.*;
class Sort<T extends Comparable<T>>{
 int counter;
    T arr[];
    Sort(int s){
    arr = (T[])new Comparable[s];
  counter=0;
    }
    void Insert(T ins){
        if (counter<arr.length) {
            arr[counter++]= ins;
        }
    }
    
 void Selection (T arr[]){
     for (int out = 0; out < arr.length; out++) {
         int min = out;
         for (int in = out; in < arr.length; in++) {
             if (arr[in].compareTo(arr[min])<0) {
                 min=in;
             }
         }
         Swap(min,out);
     }
 
 }   
    
    
  public void Swap(int a, int b){
T temp = arr[a];
arr[a]= arr[b];
arr[b]= temp;
}  
    
    
    void Display(T arr[]){
    for (int i = 0; i < arr.length; i++) {
        System.out.print(arr[i] +  " ");
    }
}
    
}
public class SelectionSortJava {

    public static void main(String[] args) {
   Scanner in = new Scanner(System.in);
    Sort<Integer> a = new Sort<>(10);
   int i=0;
        System.out.println(" Enter 10 Integer Values: ");
        while(i<10){
         int val  = in.nextInt();
        a.Insert(val);
        i++;
    }
       a.Selection(a.arr);
       a.Display(a.arr);
    
    }
    
}
