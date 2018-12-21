package com.bo.sort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class Bucket {
	public static void bucketSort(double array[]) {
        int length = array.length;
        ArrayList arrList[] = new ArrayList[length];
        
        
        for (int i = 0; i < length; i++) {
            
            int temp = (int) Math.floor(10 * array[i]);
            if (null == arrList[temp])
                arrList[temp] = new ArrayList();
            arrList[temp].add(array[i]);
        }
        
        for (int i = 0; i < length; i++) {
            if (null != arrList[i]) {
                
                
                
                Collections.sort(arrList[i]);
            }
                
        }
        
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (null != arrList[i]) {
                Iterator iter = arrList[i].iterator();
                while (iter.hasNext()) {
                    Double d = (Double) iter.next();
                    array[count] = d;
                    count++;
                }
            }
        }
    }

    
    public static void main(String[] args) {
        double array[] = { 0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12,
                0.23, 0.68 };
        bucketSort(array);
        for (int i = 0; i < array.length; i++)
            System.out.print(array[i] + " ");
        System.out.println();
    }
}
