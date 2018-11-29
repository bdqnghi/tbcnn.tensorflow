package sort.complexsort;

import Util.RandomUtil;
import Util.SortUtil;

/**
 * Created by 10353 on 2018/2/7.
 * 堆排序思想及其优化 说明实例为最大堆
 * 思想：使用最大堆完成无序序列的序列化
 * 堆性质：1.任意节点大于（或小于）它的所有后裔，最大元（或最小元）在堆的根上（堆序性）
 *        2.堆总是一棵完全树。即除了最底层，其他层的节点都被元素填满，且最底层尽可能地从左到右填入（结构性）
 * 本实例为最大堆
 */
public class HeapSort<E extends Comparable> {

    protected E[] data;    //底层存储元素

    protected int count;   //当前堆元素数量

    protected int capacity;  //堆容量

    private static int DEFALUT_CAPACITY = 11; //默认堆容量

    /**
     * 默认构造函数
     */
    public HeapSort(){
        initHeap(DEFALUT_CAPACITY);
    }

    /**
     * 构造一个容量为capacity的空堆
     * @param capacity
     */
    public HeapSort(int capacity){
        initHeap(capacity);
    }

    //优化堆的构造过程
    //heapify思想:每一个节点都看做一个堆则组合起来仍然是一个堆
    //说明最后一个节点的索引为 count / 2
    public HeapSort(Comparable[] array){
        count = array.length;

        data = (E[])new Comparable[count + 1];

        for(int i = 0; i < count; i++)
            data[i + 1] = (E) array[i];

        for(int i = count / 2; i >= 1; i--)
            shiftDown(i);
    }

    /**
     * 初始化堆
     * @param capacity
     */
    public void initHeap(int capacity){
        data = (E[])new Comparable[capacity + 1];
        count = 0;
        this.capacity = capacity;
    }

    /**
     * 返回堆元素数量
     * @return count 堆元素数量
     */
    public int size(){
        return count;
    }

    /**
     * 判断堆是否为空
     * @return
     */
    public boolean isEmpty(){
        return count == 0;
    }


    /**
     * 堆中添加一个元素
     * 流程：
     * 1.元素空指针检查
     * 2.数组越界检查
     * 3.当前堆元素数量递增
     * 4.将元素添加到数组末尾
     * 5.堆序向上调整
     * 说明：数组中第一个位置不放置元素
     * @param e
     * @return
     */
    public boolean add(E e){
        if(e == null)
            throw new NullPointerException();
        checkArrayIndexOutOfBounds();
        //data[++count] = e;
        count ++;
        data[count] = e;
        shiftUp(count);
        return true;
    }

    /**
     * 堆序向上调整
     * @param index
     */
    private void shiftUp(int index) {
        E e = data[index];
        //调整堆序需要满足的两个条件：1.到达根节点停止 2.父节点小于子节点
        while(index > 1 && data[index / 2].compareTo(e) < 0){
            data[index] = data[index / 2];
            index /= 2;
        }
        data[index] = e;
    }

    /**
     * 从最大堆中返回堆顶元素及最大元
     * 1.数组越界检查
     * 2.将数组最后一个元素置换到堆顶
     * 3.当前堆元素数量递减
     * 4.堆序向下调整
     * @return 最大元
     */
    public E extractMax(){
        assert count > 0;
        E e = data[1];
        SortUtil.swap(data,1,count);

        count--;
        shiftDown(1);

        return e;
    }

    /**
     * 堆序向下调整（开始时的顶点用e表示）
     * 1.寻找当前堆顶点两个子节点中最大的一个
     * 2.将找到的最大孩子上调
     * 3.继续向下寻找直到e大于当前节点
     * 4.将当前节点的值置为e
     *
     * Warn:寻找时的数组越界问题
     * @param index
     */
    private void shiftDown(int index) {
        E e = data[index];
        while( 2 * index <= count){
            int j = index * 2;
            //j + 1 <= count防止越界
            //data[j + 1].compareTo(data[j])从两个孩子中寻找最大的那个
            if(j + 1 <= count && data[j + 1].compareTo(data[j]) > 0){
                j += 1;
            }

            if(e.compareTo(data[j]) >= 0)
                break;
            data[index] = data[j];
            index = j;
        }

        data[index] = e;
    }


    /**
     * 判断底层元素数组是否为越界
     */
    public void checkArrayIndexOutOfBounds(){
        if(count + 1 > capacity)
            throw new ArrayIndexOutOfBoundsException();
    }

    /**
     * 堆排序逻辑
     * 1.构造堆
     * 2.依次获取堆中的最大元
     * @param array
     * @param n
     */
    public static void sort(Comparable[] array, Integer n){

//        HeapSort<Comparable> heapSort = new HeapSort<Comparable>(n);
//        for( int i = 0 ; i < n ; i ++ )
//            heapSort.add(array[i]);
        HeapSort<Comparable> heapSort = new HeapSort<Comparable>(array);

        for( int i = n-1 ; i >= 0 ; i -- )
            array[i] = heapSort.extractMax();
    }


    public static void main(String[] args) {
//        HeapSort<Integer> maxHeap = new HeapSort<Integer>(100);
//        System.out.println(maxHeap.size());
//        HeapSort<Integer> maxHeap = new HeapSort<Integer>(100);
//        int N = 50; // 堆中元素个数
//        int M = 100; // 堆中元素取值范围[0, M)
//        for( int i = 0 ; i < N ; i ++ ){
//            maxHeap.add( new Integer((int)(Math.random() * M)) );
//        }
//        重复率高，有序度低
//        MergeSort running time : 284ms
//        DoubleStandardQuickSort running time : 383ms
//        ThreeWayQuickSort running time : 120ms
//        HeapSort running time : 341ms
//        Integer[] array = RandomUtil.generateRandomData(1000000,0,10);
//        重复率低，有序度低
//        MergeSort running time : 328ms
//        DoubleStandardQuickSort running time : 534ms
//        ThreeWayQuickSort running time : 767ms
//        HeapSort running time : 888ms
//        Integer[] array = RandomUtil.generateRandomData(1000000,0,100000);
//        重复率低，有序度高
//        MergeSort running time : 352ms
//        DoubleStandardQuickSort running time : 210ms
//        ThreeWayQuickSort running time : 402ms
//        HeapSort running time : 264ms
        Integer[] array = RandomUtil.generateNearlyOrderdData(1000000,10);
        Integer[] copyArray1 = RandomUtil.copyGenerateRandomData(array);
        Integer[] copyArray2 = RandomUtil.copyGenerateRandomData(array);
        Integer[] copyArray3 = RandomUtil.copyGenerateRandomData(array);
        SortUtil.testSortTime("sort.complexsort.MergeSort",null,array);
        SortUtil.testSortTime("sort.complexsort.DoubleStandardQuickSort",null,copyArray1);
        SortUtil.testSortTime("sort.complexsort.ThreeWayQuickSort",null,copyArray2);
        SortUtil.testSortTime("sort.complexsort.HeapSort",null,copyArray3);

    }

}
