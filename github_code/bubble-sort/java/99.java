
package bubblesortjava;
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
public void Bubble(T arr[]){
    for (int out = arr.length-1; out > 1; out--) {
        for (int in = 0; in < out; in++) {
            if (arr[in].compareTo(arr[in+1])>0) {
                Swap(in,in+1);
            }
        }
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
class BubbleSortJava<T extends Comparable<T>>{
 
    public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    
   Sort<String> a = new Sort<>(10);
   int i=0;
        System.out.println(" Enter 10 String Values: ");
        while(i<10){
         String val  = in.next();
        a.Insert(val);
        i++;
    }
       a.Bubble(a.arr);
       a.Display(a.arr);
        
    }
}
