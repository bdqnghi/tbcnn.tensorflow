package string.definition;

import java.util.Arrays;

/**
 * 桶排序/计数排序   是一些 字符串排序算法的 基础
 * 适用于 key或value 取值范围较小的情况  
 * 取值范围取做 桶数组的容量m
 * 排序步骤:
 * 1、频率统计  即 分配过程 完成count[]计数
 * 2、将频率转换为索引  即累计更新过程   即累计值+当前count值即更新为当前accum累计的索引值   索引为以排序结果在数组中的索引
 * 3、数据分类排序
 * @author wjs13
 *
 */
public class BucketSort {
    //不好写通用的 排序算法    就写了一个用例  参照了《算法》第四版  P458 键索引计数法的 用例
    //用例代码
    private  class Person{//人名+该人分组的编号 
        private String name;
        private int key;//编号为0-4  即key取值范围很小 为5   则表示 桶排序  的 容量m为5
        public Person(String name, int key) {
            super();
            this.name = name;
            this.key = key;
        }
        @Override
        public String toString() {
            return "Person [name=" + name + ", key=" + key + "]";
        }
        
    }
    public static void sort(Person[] a){
       int[] count = new int[5];
       int[] accum = new int[6];//为方便 累加更新 表示有序序列的索引值 此处需要多设计一位累加数组 且accum[0] = 0初始为0
       int n = a.length;//待排对象的个数
       Person[] aux = new Person[n];//辅助数组 用以 计数排序 结果的 分类 排序
       for (int i = 0; i < n; i++){//扫描输入待排数组  分配  统计频率
           count[a[i].key]++;
       }
       accum[0] = 0;
       for (int i = 0; i < 5; i++){//频率转换为索引 过程
           accum[i + 1]  = count[i] + accum[i];//累计 更新   过程
//          则累计数组accum数组 既可以表示索引数组 即key为i的键在有序序列中索引为[accum[i],accum[i+1])
       }
       for (int i = 0; i < n; i++){//分类 按 桶中频率的计数值 和 由计数值转换为索引  来 排序
           aux[accum[a[i].key]++] = a[i];//没分类排序一个  则对应下一个元素的索引就要自增1
       }
       for (int i = 0; i < n; i++){
           a[i] = aux[i];//回写排序结果
       }
    }
    
    public static void main(String[] args) {
      //实例内部成员 类Person 要在类的外部使用 必须先要创建外部类的对象 用来创建内部类对象
        Person p1 = new BucketSort().new Person("wilson1", 1);
//      Person p1 = new Person("wilson1", 1);或者 把内部类 设计成 static class 静态内部类 就不需要用外部类对象来创建内部类对象了
        Person p2 = new BucketSort().new Person("wilson2", 2);
        Person p3 = new BucketSort().new Person("wilson3", 2);
        Person p4 = new BucketSort().new Person("wilson4", 3);
        Person p5 = new BucketSort().new Person("wilson5", 4);
        Person p6 = new BucketSort().new Person("wilson6", 1);
        Person p7 = new BucketSort().new Person("wilson7", 0);
        Person p8 = new BucketSort().new Person("wilson8", 0);
        Person p9 = new BucketSort().new Person("wilson9", 4);
        Person p10 = new BucketSort().new Person("wilson10", 4);
        Person p11 = new BucketSort().new Person("wilson11", 1);
        Person p12 = new BucketSort().new Person("wilson11", 3);
        Person[] a = new Person[]{p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12};
        System.out.println(Arrays.toString(a));
        sort(a);//桶排序
        System.out.println(Arrays.toString(a));
        
    }
    
}
