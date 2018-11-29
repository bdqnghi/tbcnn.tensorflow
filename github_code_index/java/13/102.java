package Sort_func.arraySort.arraySort;

/**
 * 希尔排序是插入排序的改进版，它的作法不是每次一个元素挨一个元素的比较。
 * 而是初期选用大跨步（增量较大）间隔比较，使记录跳跃式接近它的排序位置；
 * 然后增量缩小；最后增量为 1 ，这样记录移动次数大大减少，提高了排序效率。
 * 希尔排序对增量序列的选择没有严格规定。
 * 这样做的好处是每次排序完成，数组都会趋近于有序的，而最后一步就是简单插入排序，
 * 插入排序对有序数组效率极高，几乎是线性的，所以效率提升
 * 参考链接：http://bubkoo.com/2014/01/15/sort-algorithm/shell-sort/
 * Created by liuchong on 2017/6/27.
 */
public class ShellSort {

    public void ShellSort(int[] nums){
        int gap = nums.length/2;
        while(gap > 0){
            for(int i=gap; i<nums.length; i++){
                for(int j=i; j>=gap; j-=gap){
                    if(nums[j] < nums[j-gap])
                        swap(nums, j, j-gap);
                    else
                        break;
                }
            }
            gap = gap/2;
        }
    }

    public void swap(int[] nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
