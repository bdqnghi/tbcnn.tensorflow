package sort;

import edu.princeton.cs.algs4.StdRandom;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Quick {

    public static void sort(Comparable[] a){//快速排序
        StdRandom.shuffle(a);//随机化数组，避免切分不平衡
        sort(a,0,a.length-1);
    }

    private static void sort(Comparable[] a,int lo,int hi){
        if(hi<=lo) return;
        int j=partition(a,lo,hi);//切分
        sort(a,lo,j-1);//将左半边排序
        sort(a,j+1,hi);//将右半边排序
    }

    private static int partition(Comparable[] a,int lo,int hi){//切分
        int i=lo,j=hi+1;
        Comparable v=a[lo];//切分元素
        while(true){
            while(less(a[++i],v)) if(i==hi) break;//从数组左端开始扫描，直到找到大于切分元素的元素
            while(less(v,a[--j])) if(j==lo) break;//从数组右端开始扫描，直到找到小于切分元素的元素
            if(i>=j) break;
            exch(a,i,j);//交换两元素
        }
        exch(a,lo,j);//将切分元素放入正确的位置
        return j;
    }

    private static boolean less(Comparable v,Comparable w){//对元素进行比较
        return v.compareTo(w)<0;
    }

    private  static void exch(Comparable[] a,int i,int j){//交换元素位置
        Comparable t=a[i]; a[i]=a[j]; a[j]=t;
    }

    private static void show(Comparable[] a){//打印数组元素
        for(int i=0;i<a.length;i++){
            System.out.print(a[i]+" ");
        }
        System.out.println();
    }

    public static boolean isSorted(Comparable[] a){//判断排序后的数组是否有序
        for(int i=1;i<a.length;i++){
            if(less(a[i],a[i-1])){
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s=new Scanner(new File("F:\\algorithms4\\algs4-data\\algs4-data\\words3.txt"));
        ArrayList<String> arrayList=new ArrayList<>();
        while (s.hasNext()){
            arrayList.add(s.next());
        }
        Iterator<String> iterator=arrayList.iterator();
        String[] arr=new String[arrayList.size()];
        int index=0;
        while (iterator.hasNext()){
            arr[index++]=iterator.next();
        }

        sort(arr);
        assert isSorted(arr);
        show(arr);
    }
}
