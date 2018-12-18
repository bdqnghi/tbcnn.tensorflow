package Sorting;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class bubblesort {
    public List<Integer> sort(List<Integer> list){

        
        
        
        int n = list.size();
        
        while(n != 0){
            
            int swappy = 0;
            for (int i = 1;i<n;i++){
                
                if(list.get(i-1) > list.get(i)){
                    int temp = list.get(i-1);
                    list.set(i-1,list.get(i));
                    list.set(i,temp);
                    
                    swappy = i;
                }
            }
            
            n = swappy;
        }
        return list;
    }

    public static void main(String[] args) {
        bubblesort bob = new bubblesort();
        Random ran = new Random();
        List<Integer> list = new ArrayList<Integer>();
        for (int i =0;i<1000;i++){
            list.add(ran.nextInt(100));
        }

        System.out.println(list);
        long startTime = System.nanoTime();
        List<Integer> sorted = bob.sort(list);
        System.out.println("unsorted to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        System.out.println(sorted);
        startTime = System.nanoTime();
        System.out.println("sorted to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        
        
        sorted.set(0,78);
        startTime = System.nanoTime();
        bob.sort(sorted);
        System.out.println("first changed to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        sorted.set(sorted.size()-1,5);
        startTime = System.nanoTime();
        bob.sort(sorted);
        System.out.println("last changed to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        
        
    }
}
