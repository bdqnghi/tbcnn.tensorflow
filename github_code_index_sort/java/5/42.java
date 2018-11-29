package algorithm;

/*
*  Created by WangDi on 2017/10/31 0031
*/

public class BubbleSort {

    public static void main(String[] args) {

        int[] bubbleSort = {66,42,3,12,7,8,2};

        for (int bubble:bubbleSort) {

            System.out.println(bubble);
        }
        System.out.println("--------以下为下沉法---------");

//        下沉法，每进行一次排序比较的次数将会减少
        for (int i = 0; i < bubbleSort.length; i++) {

            for (int j = 0; j < bubbleSort.length - i - 1; j++) {

                int temp;
                if(bubbleSort[j] > bubbleSort[j + 1]){

                    temp = bubbleSort[j];
                    bubbleSort[j] = bubbleSort[j + 1];
                    bubbleSort[j + 1] = temp;
                }

            }
        }

        for (int bubble:bubbleSort) {

            System.out.println(bubble);
        }

        System.out.println("--------以下为上浮法---------");

        for (int m = 0; m < bubbleSort.length; m++) {

            for (int n = m; n < bubbleSort.length - 1; n++) {

                int temp;
                if(bubbleSort[n] > bubbleSort[n + 1]){

                    temp = bubbleSort[n];
                    bubbleSort[n] = bubbleSort[n + 1];
                    bubbleSort[n + 1] = temp;
                }
            }
        }

        for (int bubble:bubbleSort) {

            System.out.println(bubble);
        }
    }
}
