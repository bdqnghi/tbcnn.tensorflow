import java.util.*;
import java.io.*;

public class Bubble{
    private ArrayList[] buckets = new ArrayList[10];
    public int[] ran = new int[10];
    private int compares,swaps = 0;

    public void bSort(int[] toSort){
        for(int i=0;i<toSort.length;i++){
            for(int n=0;n<toSort.length-1;n++){
		compares++;
                if(toSort[n]>toSort[n+1]){
                    swaps++;
                    int tmp = toSort[n];
                    toSort[n] = toSort[n+1];
                    toSort[n+1]=tmp;
                }
            }
        }
    }
}