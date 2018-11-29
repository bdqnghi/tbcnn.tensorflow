package algorithm.sort.shell;

import algorithm.sort.SortUtil;
import common.Utils;

/**
 * �Ƚ���������Ԫ�����зָ����ɸ������У������ĳ������������Ԫ����ɵģ��ֱ����ֱ�Ӳ�������
 * Ȼ���������������ٽ�������
 * �����������е�Ԫ�ػ������������㹻С��ʱ���ٶ�ȫ��Ԫ�ؽ���һ��ֱ�Ӳ�������
 * http://blog.csdn.net/morewindows/article/details/6668714
 * http://bubkoo.com/2014/01/15/sort-algorithm/shell-sort/
 * Created by better on 2017/7/18.
 */
public class ShellSort {
    static int[] arr0 = new int[]{100, 70, 80, 1, 60, 88, 60, 77, 10, 30, 7,};
    static int[] arr3 = new int[]{100, 70, 80, 1, 60, 88, 60, 77, 10, 30, 7,};

    public static void main(String[] args) {
        shellSort0(arr0);
        shellSort3(arr3);

    }

    public static void shellSort0(int[] array) {
        Utils.log("���룺");
        SortUtil.logArray(array);
        int step;
        //������ÿ�μ�Ϊԭ����һ��
        for (step = array.length / 2; step > 0; step /= 2) {
            //��������ÿ��С�������
            for (int i = 0; i < step; i++) {
                //ֱ�Ӳ�������
                for (int j = i; j < array.length - step; j += step) {
                    for (int k = j + step; k - step >= 0; k -= step) {
                        if (array[k - step] > array[k]) {
                            int temp = array[k - step];
                            array[k - step] = array[k];
                            array[k] = temp;
                        } else {
                            break;
                        }
                    }
                }
            }
            SortUtil.logArray(step, array);
        }
        Utils.log("�����");
        SortUtil.logArray(array);
    }

    public static void shellSort3(int[] array) {
        SortUtil.logArray("���룺", array);

        int step, i, j, length = array.length;
        int temp;
        for (step = length / 2; step > 0; step /= 2) {
            Utils.log("step=" + step);
            for (i = step; i < length; i++) {
                temp = array[i];
                j = i - step;
                while (j >= 0 && temp < array[j]) {
                    array[j + step] = array[j];
                    j -= step;
                    SortUtil.logArray("����j" + i + "=", array);
                }
                array[j + step] = temp;
                SortUtil.logArray("i" + i + "=", array);
            }
        }

        SortUtil.logArray("�����", array);
    }
}
