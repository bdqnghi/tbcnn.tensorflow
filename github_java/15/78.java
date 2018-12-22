package com.student.practice.done.practiceDP.typeC;

import java.util.ArrayList;
import java.util.List;

public class RodCutting {

    public static void main(String[] args) {
        RodCutting app = new RodCutting();
        Cutting[] arr = new Cutting[]{app.new Cutting(1, 2), app.new Cutting(2, 5), app.new Cutting(3, 7), app.new Cutting(4, 8)};
        int rodLength = 5;
        app.getPrintRodCuttingList2(arr, rodLength);
    }

    private void getPrintRodCuttingList2(Cutting[] arr, int rodLength) {

        int[][] maxValueDP = getMaxValueDP2(arr, rodLength);

        List<Integer> cuttingIndexList = getCuttingIndexListFromMaxValueDP1(arr, rodLength, maxValueDP);

        cuttingIndexList.stream()
                .map(index -> arr[index])
                .forEach(cutting -> System.out.println("length = " + cutting.getLength() + ", value = " + cutting.getValue()));
    }

    private List<Integer> getCuttingIndexListFromMaxValueDP1(Cutting[] arr, int rodLength, int[][] maxValueDP) {

        List<Integer> cuttingIndexList = new ArrayList<>();

        int current = arr.length - 1;
        int length = rodLength;

        while (maxValueDP[current][length] > 0) {
            if ((current == 0) || ((length - arr[current].getLength() >= 0) && (maxValueDP[current][length] != maxValueDP[current - 1][length]))) {
                cuttingIndexList.add(current);
                length = length - arr[current].getLength();
            } else {
                current = current - 1;
            }
        }

        return cuttingIndexList;
    }

    private int[][] getMaxValueDP2(Cutting[] arr, int rodLength) {

        int[][] maxValueDP = new int[arr.length][rodLength + 1];

        // row : length = 0
        for (int current = 0; current <= arr.length - 1; current++) {
            maxValueDP[current][0] = 0;
        }

        // column : current = 0
        for (int length = 1; length <= rodLength; length++) {
            //maxValueDP[0][length] = (length / arr[0].getProduct()) * arr[0].getMaximumValue();
            maxValueDP[0][length] = arr[0].getValue() + maxValueDP[0][length - arr[0].getLength()];
        }

        for (int current = 1; current <= arr.length - 1; current++) {
            for (int length = 1; length <= rodLength; length++) {
                int excludingCurrent = maxValueDP[current - 1][length];
                int includingCurrent = 0;
                if (length - arr[current].getLength() >= 0) {
                    includingCurrent = arr[current].getValue() + maxValueDP[current][length - arr[current].getLength()];
                }
                maxValueDP[current][length] = Integer.max(excludingCurrent, includingCurrent);
            }
        }

        return maxValueDP;
    }

    private class Cutting {

        private final int length;
        private final int value;

        Cutting(int length, int value) {
            this.length = length;
            this.value = value;
        }

        int getLength() {
            return length;
        }

        int getValue() {
            return value;
        }

    }

}
