/**
* 快速排序：
*/

public class QuickSort {   
  
    /**  
     * 排序算法的实现，对数组中指定的元素进行排序  
     * @param array 待排序的数组  
     * @param from 从哪里开始排序  
     * @param end 排到哪里  
     * @param c 比较器  
     */  
    //定义了一个这样的公有方法sort，在这个方法体里面执行私有方法quckSort（这种方式值得借鉴）。
    public void sort(Integer[] array, int from, int end) {   
        quickSort(array, from, end);   
    }   
  
    /**  
     * 递归快速排序实现  
     * @param array 待排序数组  
     * @param low 低指针  
     * @param high 高指针  
     * @param c 比较器  
     */  
    private void quickSort(Integer[] array, int low, int high) {   
        /*  
         * 如果分区中的低指针小于高指针时循环；如果low=higth说明数组只有一个元素，无需再处理；  
         * 如果low > higth，则说明上次枢纽元素的位置pivot就是low或者是higth，此种情况  
         * 下分区不存，也不需处理  
         */  
        if (low < high) {   
            //对分区进行排序整理   
            
            //int pivot = partition1(array, low, high);
            int pivot = partition2(array, low, high);   
            //int pivot = partition3(array, low, high);      
            
            /*  
             * 以pivot为边界，把数组分成三部分[low, pivot - 1]、[pivot]、[pivot + 1, high]  
             * 其中[pivot]为枢纽元素，不需处理，再对[low, pivot - 1]与[pivot + 1, high]  
             * 各自进行分区排序整理与进一步分区  
             */  
            quickSort(array, low, pivot - 1);   
            quickSort(array, pivot + 1, high);   
        }   
  
    }   
  
    /**  
     * 实现一  
     *   
     * @param array 待排序数组  
     * @param low 低指针  
     * @param high 高指针  
     * @param c 比较器  
     * @return int 调整后中枢位置  
     */  
    private int partition1(Integer[] array, int low, int high) {   
        Integer pivotElem = array[low];//以第一个元素为中枢元素   
        //从前向后依次指向比中枢元素小的元素，刚开始时指向中枢，也是小于与大小中枢的元素的分界点   
        int border = low;   
  
        /*  
         * 在中枢元素后面的元素中查找小于中枢元素的所有元素，并依次从第二个位置从前往后存放  
         * 注，这里最好使用i来移动，如果直接移动low的话，最后不知道数组的边界了，但后面需要  
         * 知道数组的边界  
         */  
        for (int i = low + 1; i <= high; i++) {   
            //如果找到一个比中枢元素小的元素   
            if ((array[i].compareTo(pivotElem)) < 0) {   
                swap(array, ++border, i);//border前移，表示有小于中枢元素的元素   
            }   
        }   
        /*  
         * 如果border没有移动时说明说明后面的元素都比中枢元素要大，border与low相等，此时是  
         * 同一位置交换，是否交换都没关系；当border移到了high时说明所有元素都小于中枢元素，此  
         * 时将中枢元素与最后一个元素交换即可，即low与high进行交换，大的中枢元素移到了 序列最  
         * 后；如果 low <minIndex< high，表 明中枢后面的元素前部分小于中枢元素，而后部分大于  
         * 中枢元素，此时中枢元素与前部分数组中最后一个小于它的元素交换位置，使得中枢元素放置在  
         * 正确的位置  
         */  
        swap(array, border, low);   
        return border;   
    }   
  
    /**  
     * 实现二  
     *   
     * @param array 待排序数组  
     * @param low 待排序区低指针  
     * @param high 待排序区高指针  
     * @param c 比较器  
     * @return int 调整后中枢位置  
     */  
    private int partition2(Integer[] array, int low, int high) {   
        int pivot = low;//中枢元素位置，我们以第一个元素为中枢元素   
        //退出条件这里只可能是 low = high   
        while (true) {   
            if (pivot != high) {//如果中枢元素在低指针位置时，我们移动高指针   
                //如果高指针元素小于中枢元素时，则与中枢元素交换   
                if ((array[high].compareTo(array[pivot])) < 0) {   
                    swap(array, high, pivot);   
                    //交换后中枢元素在高指针位置了   
                    pivot = high;   
                } else {//如果未找到小于中枢元素，则高指针前移继续找   
                    high--;   
                }   
            } else {//否则中枢元素在高指针位置   
                //如果低指针元素大于中枢元素时，则与中枢元素交换   
                if ((array[low].compareTo(array[pivot])) > 0) {   
                    swap(array, low, pivot);   
                    //交换后中枢元素在低指针位置了   
                    pivot = low;   
                } else {//如果未找到大于中枢元素，则低指针后移继续找   
                    low++;   
                }   
            }   
            if (low == high) {   
                break;   
            }   
        }   
        //返回中枢元素所在位置，以便下次分区   
        return pivot;   
    }   
  
    /**  
     * 实现三  
     *   
     * @param array 待排序数组  
     * @param low 待排序区低指针  
     * @param high 待排序区高指针  
     * @param c 比较器  
     * @return int 调整后中枢位置  
     */  
    private int partition3(Integer[] array, int low, int high) {   
        int pivot = low;//中枢元素位置，我们以第一个元素为中枢元素   
        low++;   
        //----调整高低指针所指向的元素顺序，把小于中枢元素的移到前部分，大于中枢元素的移到后面部分   
        //退出条件这里只可能是 low = high   
  
        while (true) {   
            //如果高指针未超出低指针   
            while (low < high) {   
                //如果低指针指向的元素大于或等于中枢元素时表示找到了，退出，注：等于时也要后移   
                if ((array[low].compareTo(array[pivot])) >= 0) {   
                    break;   
                } else {//如果低指针指向的元素小于中枢元素时继续找   
                    low++;   
                }   
            }   
  
            while (high > low) {   
                //如果高指针指向的元素小于中枢元素时表示找到，退出   
                if ((array[high].compareTo(array[pivot])) < 0) {   
                    break;   
                } else {//如果高指针指向的元素大于中枢元素时继续找   
                    high--;   
                }   
            }   
            //退出上面循环时 low = high   
            if (low == high) {   
                break;   
            }   
  
            swap(array, low, high);   
        }   
  
        //----高低指针所指向的元素排序完成后，还得要把中枢元素放到适当的位置   
        if ((array[pivot].compareTo(array[low])) > 0) {   
            //如果退出循环时中枢元素大于了低指针或高指针元素时，中枢元素需与low元素交换   
            swap(array, low, pivot);   
            pivot = low;   
        } else if ((array[pivot].compareTo(array[low])) <= 0) {   
            swap(array, low - 1, pivot);   
            pivot = low - 1;   
        }   
  
        //返回中枢元素所在位置，以便下次分区   
        return pivot;   
    }   
  
		/**  
     * 交换数组中的两个元素的位置  
     * @param array 待交换的数组  
     * @param i 第一个元素  
     * @param j 第二个元素  
     */  
    public void swap(Integer[] array, int i, int j) {   
        if (i != j) {//只有不是同一位置时才需交换   
            Integer tmp = array[i];   
            array[i] = array[j];   
            array[j] = tmp;   
        }   
    } 
	
    /**   
    * 测试   
    * @param args   
    */  
    public static void main(String[] args) {   
        Integer[] intgArr = { 5, 9, 1, 4, 2, 6, 3, 8, 0, 7 };  
        QuickSort quicksort = new QuickSort();   
        quicksort.sort(intgArr,0,intgArr.length-1);
        for(Integer intObj:intgArr){
			System.out.print(intObj + " ");
        }
    }   
}   
