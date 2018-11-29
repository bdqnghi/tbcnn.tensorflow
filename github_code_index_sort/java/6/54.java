package com.maddness.sorting;

import java.util.*;
import java.util.stream.IntStream;

import static java.lang.Math.pow;
import static java.lang.System.currentTimeMillis;

/**
 * Radix sort implementation based on queues compared to Java Collections.sort()
 *
 * https://en.wikipedia.org/wiki/Radix_sort
 *
 */
public class Radix {

    private List<Queue<Integer>> queues = createQueues();
    private Queue<Integer> mainQueue = new LinkedList<>();

    private List<Queue<Integer>> createQueues() {
        List<Queue<Integer>> queues = new ArrayList<>();
        IntStream.range(0, 10).forEach(i -> queues.add(new LinkedList<>()));
        return queues;
    }

    public static void main(String[] args) {
        List<Integer> vals = populateList(1000000);

        long timer = currentTimeMillis();
        new Radix().sort(vals);
        System.out.println("Radix sort done: " + (currentTimeMillis() - timer) + " ms");

        timer = currentTimeMillis();
        Collections.sort(vals);
        System.out.println("Quick sort done: " + (currentTimeMillis() - timer) + " ms");

        System.out.println("\nResult - your code sucks");
    }

    private static List<Integer> populateList(int number) {
        List<Integer> vals = new ArrayList<>(number);
        Random rand = new Random();
        IntStream.range(0, number).forEach(i -> vals.add(rand.nextInt(number)));
        return vals;
    }

    private Queue<Integer> sort(List<Integer> vals) {
        int maxLen = getMaxLen(vals);

        IntStream.range(0, vals.size()).forEach(i -> mainQueue.offer(vals.get(i)));

        for (int place = 1; place <= maxLen; place++) {

            while (!mainQueue.isEmpty()) {
                int value = mainQueue.poll();
                queues.get(getDigit(value, place)).offer(value);
            }

            for (Queue<Integer> queue : queues) {
                while (!queue.isEmpty()) {
                    mainQueue.offer(queue.poll());
                }
            }
        }

        return mainQueue;
    }

    public static int getMaxLen(List<Integer> vals) {
        int maxLen = 0;
        for (Integer val : vals) {
            maxLen = Math.max(maxLen, length(val));
        }
        return maxLen;
    }

    public static int length(int val) {
        return (int) (Math.log10(val)+1);
    }

    public static int getDigit(int val, int place) {
        return (int) (val % pow(10, place)) / (int) pow(10, place - 1);
    }
}
