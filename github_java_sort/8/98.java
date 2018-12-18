

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class Quick{

    public static void main(String[] args) throws IOException{
        
        Scanner in = new Scanner(Paths.get("../input/input_integers.txt"), "UTF-8");
        PrintWriter outTime = new PrintWriter("../output/quick_sort/time.txt", "UTF-8");
        int[] origin=new int[1<<17];
        for(int i = 0; i < 1<<17; i++){
            origin[i] = in.nextInt();
        }

        int[] exp={2, 5, 8, 11, 14, 17};
        
        for(int index : exp){
            int[] partArray = Arrays.copyOf(origin, 1<<index);
            
            
            long enduration = sort(partArray)/1000;
            
            
            outTime.println("index: " + index + "\ntime: " + enduration + "\tmicroseconds.");
            outTime.flush();

            
            System.out.println("index: " + index + "\ntime: " + enduration + "\tmicroseconds.");
            PrintWriter outSort = new PrintWriter("../output/quick_sort/result_"+index+".txt", "UTF-8");
            for(int j = 0; j < 1<<index; j++){
                outSort.println(partArray[j]);
                outSort.flush();
            }
        }
    }
    
    
    public static long sort(int[] A){
        
        long startTime = System.nanoTime();
        
        
        quick_sort(A, 0, A.length - 1);

        
        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    
    public static int partition(int[] A, int p, int r){
        int x = A[r];
        int tmp;
        int i = p - 1;
        for(int j = p; j < r; j++){
            if(A[j] <= x){
                i++;
                
                
                tmp = A[j];
                A[j] = A[i];
                A[i] = tmp;
            }
        }
        i++;
        A[r] = A[i];
        A[i] = x;
        return i;
    }

    public static void quick_sort(int[] A, int p, int r){
        if(p < r){
            int q = partition(A, p, r);
            quick_sort(A, p, q-1);
            quick_sort(A, q+1, r);
        }
    }
}

