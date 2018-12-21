

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class Bubble{

    public static void main(String[] args) throws IOException{
        
        Scanner in = new Scanner(Paths.get("../input/input_integers.txt"), "UTF-8");
        PrintWriter outTime = new PrintWriter("../output/bubble_sort/time.txt", "UTF-8");
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
            PrintWriter outSort = new PrintWriter("../output/bubble_sort/result_"+index+".txt", "UTF-8");
            for(int j = 0; j < 1<<index; j++){
                outSort.println(partArray[j]);
                outSort.flush();
            }
        }
    }
    
    
    public static long sort(int[] A){
        
        long startTime = System.nanoTime();
        
        
        bubble_sort(A);

        
        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    public static void bubble_sort(int[] A){
        int tmp;
        int l = A.length;
        for(int i = 0; i < l - 1; i++){
            for(int j = 1; j < l; j++){
                if(A[j - 1] > A[j]){
                    
                    tmp = A[j];
                    A[j] = A[j - 1];
                    A[j - 1] = tmp;
                }
            }
        }
    }
}

