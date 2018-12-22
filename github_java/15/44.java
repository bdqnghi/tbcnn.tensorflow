// https://www.interviewbit.com/problems/rod-cutting/
// INCOMPLETE SOLUTION.

import java.util.*;

public class RodCut {
    TreeMap<Integer, ArrayList<Integer>> costToCuts = new TreeMap<>();

    public static ArrayList<Integer> rodCut(int rodSize, ArrayList<Integer> weakPoints) {

        rodCutHelper(0, weakPoints, new ArrayList<Integer>());

        return new ArrayList<>();
    }

    public static void rodCutHelper(int cost, ArrayList<Integer> weakPoints, ArrayList<Integer> cutsMade) {
        printTabs(cutsMade.size());
        System.out.print("cuts made: ");
        for(int n : cutsMade) {
            System.out.print(n + " ");
        }
        System.out.println();
        if(weakPoints.isEmpty()) {
            // if(!costToCuts.containsKey(cost)) {
            //     costToCuts.put(cost, new ArrayList<Integer>(cutsMade));
            // }
            // for(int n : cutsMade) {
            //     System.out.print(n + " ");
            // }
            // System.out.print(" | ");
            return;
        }

        for(int i = 0; i < weakPoints.size(); i++) {
            // choose
            Integer chosen = weakPoints.get(i);
            cutsMade.add(chosen);

            ArrayList<Integer> newWeakPoints = new ArrayList<Integer>(weakPoints);
            newWeakPoints.remove(chosen);

            // cost = subrod that we're cutting

            // explore
            rodCutHelper(cost, newWeakPoints, new ArrayList<Integer>(cutsMade));

            // unchoose
            cutsMade.remove(chosen);
        }
    }

    public static void printTabs(int n) {
        for(int i = 0; i < n; i++) {
            System.out.print("    ");
        }
    }

    public static void main(String[] args) {
        ArrayList<Integer> weakPoints = new ArrayList<>();
        weakPoints.add(1);
        weakPoints.add(2);
        weakPoints.add(4);
        weakPoints.add(6);
        rodCut(7, weakPoints);
    }
}
