import java.io.BufferedReader;
import java.io.InputStreamReader;


import java.util.*;

public class Insertion {
    public static void main(String args[] ) throws Exception {
        
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int[] ar = new int[N];
        int[] ar1 = new int[N];
        for (int i = 0; i < N; i++) {
            ar[i] = in.nextInt();
            ar1[i] = ar[i];
        }
        InsertionSort sorter = new InsertionSort(ar);
        sorter.sort();

        for(int into : ar1)
          for(int l = 0; l<ar1.length; l++){
            if(into == sorter.Ar[l])
              System.out.print(l+1+" ");
          }
    }
}
class InsertionSort{
  int[] Ar;
  InsertionSort(int[] a){
    Ar = a;
  }
  void sort(){
    for(int i = 1; i<Ar.length; i++){
      int j = i-1;
      int temp = Ar[i];
      while(j>=0 && temp<Ar[j]){
        Ar[j+1] = Ar[j];
        j--;
      }
      Ar[j+1] = temp;
    }
  }
}
