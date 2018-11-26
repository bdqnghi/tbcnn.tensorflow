package com.bo.sort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class Bucket {
	public static void bucketSort(double array[]) {
        int length = array.length;
        ArrayList arrList[] = new ArrayList[length];
        /*
         *  每个桶是一个list，存放落在此桶上的元素
         *  上次的基数排序我采用的是计数排序实现的，其实也可以用下面的方法，有兴趣的读者不妨一试(我认为太复杂)
         *  不过效率估计不高(采用了动态数组)
         */
        //划分桶并填元素
        for (int i = 0; i < length; i++) {
            //0.7到0.79放在第8个桶里,编号7；第一个桶放0到0.09
            int temp = (int) Math.floor(10 * array[i]);
            if (null == arrList[temp])
                arrList[temp] = new ArrayList();
            arrList[temp].add(array[i]);
        }
        // 对每个桶中的数进行插入排序
        for (int i = 0; i < length; i++) {
            if (null != arrList[i]) {
                //此处排序方法不定，不过越快越好，除了三大线性排序外，都没有Collections
                //和Arrays里的sort好，因为这是调优后的快拍
                //Arrays里也有，在基数排序里用过copyOf和fill方法
                Collections.sort(arrList[i]);
            }
                
        }
        //输出类似鸽巢排序
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

    /*
     * 每个元素满足0<=array[i]<1,貌似还要长度相同，
     * 若是相同小数位(digit)，则可以把小数搞为整数，最后再除以10^digit
     *  可以Random.nextInt(101)/100
     */
    public static void main(String[] args) {
        double array[] = { 0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12,
                0.23, 0.68 };
        bucketSort(array);
        for (int i = 0; i < array.length; i++)
            System.out.print(array[i] + " ");
        System.out.println();
    }
}
