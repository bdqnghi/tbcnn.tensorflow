package Sorting;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class bubblesort {
    public List<Integer> sort(List<Integer> list){

        // a bubblesort is essentially a loop in a loop that orders a sortable list.
        // now this can be made poorly for O(N^2)
        // or optimised as this is.
        int n = list.size();
        // the first loop runs until my size of unsorted objects are 0
        while(n != 0){
            // this swappy int will be set to the last object index in the list that is sorted,
            int swappy = 0;
            for (int i = 1;i<n;i++){
                //swap if needed
                if(list.get(i-1) > list.get(i)){
                    int temp = list.get(i-1);
                    list.set(i-1,list.get(i));
                    list.set(i,temp);
                    //set swappy to the last swapped index
                    swappy = i;
                }
            }
            //everything after swappy is already sorted so we remove these from the n variable. so it will not be iterated again
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
        // as you can see the optimization does so it will take negliable time to run through a sorted list,
        // if it was not optimized, the times would be much closer to each other
        sorted.set(0,78);
        startTime = System.nanoTime();
        bob.sort(sorted);
        System.out.println("first changed to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        sorted.set(sorted.size()-1,5);
        startTime = System.nanoTime();
        bob.sort(sorted);
        System.out.println("last changed to sorted: = "+((double)(System.nanoTime()-startTime)/1000000)+" ms");
        //the reason for the big diference lays in the swappy int, in the first changed, it will run through the list once or twice (not sure)
        //while the last changed can only swap once pr. run through the list making it having to run through the list n times.
    }
}
