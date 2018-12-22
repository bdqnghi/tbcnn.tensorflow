/**
 * 快速排序
 */
public static void quickSort(int[] nums, int left, int right) {
    if (left >= right) {
        return;
    }
    // 取第一个元素作为比较基数
    int pivot = nums[left];
    int i = left;
    int j = right;
    while (i < j) {
        // 从右往左找到第一个小于 pivot 的元素
        while (nums[j] >= pivot && i < j) {
            j--;
        }
        // 从左往右找到第一个大于 pivot 的元素
        while (nums[i] <= pivot && i < j) {
            i++;
        }
        // 两个元素在基数左右两边时交换位置
        if (i < j) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }

    // 一趟之后，比基数小的交换到了左边，比基数大的交换到了右边
    // 将基数交换到 i 和 j 相遇的位置
    nums[left] = nums[i];
    nums[i] = pivot;

    //递归继续处理
    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}
