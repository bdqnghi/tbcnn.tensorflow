package 算法.几种常见的排序算法;

import java.util.Arrays;

/**
 * 用一个flag标记每次循环找到的最小值。按顺序放在前面
 */
public class SelectionSort {
    public static void main(String[] args) {
        int selectionSort[]= new int[]{5,2,8,4,9,1};
        for (int i=0;i<selectionSort.length-1;i++){
            int flag=i;
            for (int j=i;j<selectionSort.length;j++){
                if (selectionSort[j]<selectionSort[flag]){//每个小循环后flag都会变。
                    flag=j;
                }
            }
            int temp=selectionSort[flag];
            selectionSort[flag]=selectionSort[i];
            selectionSort[i]=temp;
        }
        System.out.println(Arrays.toString(selectionSort));
    }
}
/**
 * 输出结果
 *[1, 2, 4, 5, 8, 9]
 */
