
package insertionsortjava;
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
    
void Insertion(T arr[]){
    for (int out = 1; out < arr.length; out++) {
       T key = arr[out];
       int j = out-1;
       while(j>=0 && key.compareTo(arr[j])<0 ){
           Swap(j,j+1);
           j--;
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
public class InsertionSortJava {

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
       a.Insertion(a.arr);
       a.Display(a.arr);
    
    }
    
}
